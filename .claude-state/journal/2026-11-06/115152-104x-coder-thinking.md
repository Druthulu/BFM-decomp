---
ts: 2026-11-06T18:51:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3aZX3kdnyE555OrxCO1c
---
Same. So the allocation is fixed: the first pointer ($3) and the copy ($7).

The real issue: in my build, the *first* statement's variable gets $3. In the target, the first statement's variable (a7) gets $7.

So I need the variable that's assigned the symbol first to get $7, not $3. The allocator gives $3 to the higher-priority allocno (a7/v1). Hmm.

Wait, in w2 the source is `v1 = symbol; a7 = v1;` and the asm is STILL `lui v1; addiu v1; move a3,v1` — so v1 (the first statement's dest) = $3. In w1 (a7 = symbol first), the asm is also `lui v1; addiu v1; move a3,v1` — meaning a7 = $3 there. So in both cases the FIRST variable gets $3. Interesting: the allocator gives $3 to whichever pseudo is assigned first? That suggests the priorities differ by which variable is which.

Hmm, in w2, v1 = the symbol (v1 has pri 5833 in w1's build) and a7 = the copy. The asm `lui v1; move a3,v1` → the symbol's pseudo = $3. In w1, a7 = the symbol (pri 20000) and v1 = the copy; the asm `lui v1; move a3,v1` → the symbol's pseudo = $3 again.

So in both cases the symbol's pseudo got $3 — but the *identities* differ (w1: a7=$3; w2: v1=$3). And the loop roles: in w1, the current pointer (v1) = $7; in w2, the current pointer (v1) = $3? The diff for w2 is identical to w1's, which is suspicious: if w2 swapped the roles, the diff would change.

Unless cse canonicalizes: `v1 = symbol; a7 = v1` → cse makes a7 and v1 equivalent and rewrites uses; the RTL ends up identical to w1's (the same canonical pseudo order). So the two bodies are the same after cse. That explains the identical diff.

So cse merges the copies; the pseudo numbering follows the *initial* RTL order, and the allocation gives the canonical/first pseudo $3.

Hmm. So how to get the symbol into $7? 

The allocator's choice: the symbol pseudo (76 in w1) has pri 20000 and gets $3 (the lowest free after $2). The other pointer (74, pri 5833) gets $7. The target has the opposite.

Key: the target's build has the pin, which changes everything. For a lever-free crack, we need the *symbol* pseudo to get $7. Options:
1. Make $3 unavailable for the symbol pseudo (conflict): then it takes $4? or $5? The free regs: $4 (a0's pref, allocated later), $5 (a5), $6 (a6), $7. If $3 were conflicted, the symbol pseudo would take $4 (bad).
2. Make another pseudo take $3 first: e.g., a5 or a6. If a5 (pri 11666) were allocated before the symbol pseudo (20000)? No, order is by pri descending: 75 (28333), 76 (20000), 72 (18000), 73 (11666), 74 (5833). So a6, symbol, a0, a5, v1. a6 got $5? (per the asm: `li $6,8` for a6? hmm, the asm shows a6=$6).

Wait, the asm: `li $6,8` (a6=$6), `li $5,832` (a5=$5). But the order: a6 (75, pri 28333) allocated first → takes $3? $3 is free at that point (no conflicts?). a6's conflicts: 72 73 74 75 76 2 3 7 29 → includes $2 and $3. So a6 can't take $2 or $3 → takes $4? But $4 is a0's pref... a6 got $6 in the asm. Hmm, why $6?

I'm misreading the mapping again. Let me map the asm: 
- `li $6,8` — the variable initialized to 8 = a6 (source: a6 = 0x8). So a6 = $6.
- `li $5,832` = a5 = $5.
- The loop counter `addu $6,$6,1; slt $2,$6,20` = a6 = $6. ✓
- `addu $5,$5,104` = a5 = $5. ✓
- `lw $2,8($4)` = *a0 → a0 = $4. ✓

So: a6=$6, a5=$5, a0=$4, and the two pointers $3/$7.

The allocno order 75 (pri 28333) = ? If 75 = a5 (refs 17): the source a5 = 0x340 and incremented; refs 17 (init + increment + 7 stores?). a5 is used in 7 store addresses → refs 17. Yes, 75 = a5 (pri 28333). And 73 (pri 11666, refs 7) = a6 (init 8, increment, compare → refs 7). 

So the order: a5 (28333), a7/symbol (20000), a0 (18000), a6 (11666), v1 (5833).
- a5 (75) allocated first: conflicts 72 73 74 75 76 2 3 7 29 → $4, $5, $6 free (excluding $2,$3,$7,sp). Lowest = $4? But a5=$5 in the asm. Hmm, why not $4? Because `used` includes `regs_someone_prefers` (a0's pref $4, a lower-priority allocno). So $4 is excluded in pass 0 → a5 takes $5. ✓ (pass 1 would allow $4 but $5 was found in pass 0.)
- symbol (76) allocated second: conflicts 72 73 74 75 76 2 29 → free: $3, $4, $7 (excluding $2, $5). pass 0 excludes $4 (someone prefers: a0) → takes $3. ✓
- a0 (72) third: pref $4 → $4. ✓
- a6 (73) fourth: conflicts → free: $6, $7; takes $6. ✓
- v1 (74) fifth: conflicts 2 3 7 → $7 is in its conflicts! So it takes... $7 is conflicted, so it can't. Hmm, but v1=$7 in the asm. Hmm, the conflict list for 74 includes 3 and 7? Let me re-read: "74 conflicts: 72 73 74 75 76 2 3 29" — includes $3 but NOT $7. So v1 takes $7. ✓

So the order gives the symbol $3. The target needs the symbol in $7 and v1 in $3. But v1 conflicts with $3 in this build (a local pseudo holds $3). In the target (pinned), v1 got $3, so the conflict must be absent there.

What local pseudo occupies $3? From the .lreg dispositions: 92 in 3. Pseudo 92 is a block-local in block 2 (the else/store block). If 92 weren't in $3, v1 could take $3 — but the allocation order would still give the symbol $3 first (the symbol has no conflict with $3). To get the symbol into $7, $3 must be unavailable for it — e.g., if another pseudo takes $3 first.

What if a5 (allocated first) took $3? It conflicts with $3 (per its list). What if the symbol's conflict list included $3? The conflict comes from a local pseudo in $3 overlapping the symbol's live range. The symbol (a7) is live from the init to the return — the whole function. The local pseudo 92 in $3 is in block 2 → overlaps → but the conflict list for 76 doesn't include $3. Hmm, why? Because 92 is a local pseudo and its register ($3) is assigned by local-alloc; global-alloc's conflict recording uses `mark_reg_live_nc` for pseudos that got reg_renumber from local-alloc (a >= 0 → mark_reg_live_nc). So the local pseudo 92 in $3 should conflict with the globals live in block 2. The symbol 76 is live in block 2 → should conflict with $3.

But the dump says 76 conflicts: 72 73 74 75 76 2 29 — no $3. Hmm, and 74 (v1) conflicts with $3. So the local $3 pseudo overlaps v1's range but not a7's? In block 2, both are live...

I'm clearly misreading something (the .greg dump's numbers are inconsistent with the RTL). Let me stop the dump archaeology.

Empirical approach: try C variants that change which pseudo gets $3:
1. Split v1's live range: e.g., use a separate variable for the load temp (v0) — already.
2. Reorder the loop's statements (increment order).
3. Make the else-branch stores use a different variable ordering.
4. Introduce/remove a variable to shift the local allocation in block 2 (pseudo 92).

Given the target's pin changed the local allocation, a lever-free crack may need to change the *else block's* code shape so the local temps don't take $3.

Hmm, this is a deep allocation puzzle. Time: 11:51; item 2 started 11:45 → 6 min. Let me spend up to ~25 more min on it (it's the last item).

Let me try a sweep of variants:
- Loop increment order: a7, v1, a6, a5 (source order) vs others.
- The else-block store order (the 7 stores).
- The load temp (v0) usage.
- `while` vs `do-while` loop shape.
- The return: `return a7;` vs `return v1;`.

The moves.md has a similar crack: "func_800CD894 MATCH: for -> goto loop with explicit e++ (no loop notes, li 0x200 stays in body)" and "func_8018275C MATCH: for -> goto loop (no LOOP notes): loop.c no longer reduces giv bytes+4 into a biv". Our function uses a do-while; maybe converting to a goto loop changes the allocation!

Also "func_80146750" is in the header; the target's loop is a do-while with a6 < 0x14.

Let me try:
- g1: convert the do-while to a `for (;;)` with an explicit break, or a goto loop.
- g2: reorder the increments.
- g3: reorder the stores.

Let me write a batch of ~10 variants.

Actually, the key blocker is the symbol pseudo's priority (20000) > v1's (5833). The symbol pseudo is a7 (the return pointer, refs 10, live 15). If I make a7's live range LONGER (e.g., it's live from the init to the return — already the whole function) or its refs fewer... a7's refs: init, increment (in the loop), return = 3? The table said refs 10. Hmm, the refs count includes the loop's uses.

What if I *remove* a7's separate increment by using the same variable for both? Then no copy.

Alternatively, make v1 the symbol's dest and a7 the copy, so the *symbol* pseudo is v1 (pri 5833, lower) → then the order would be: a5, a0, a6, symbol(v1), a7 — the symbol would be allocated 4th, after a0 and a6 → $3 might be taken by then? Let's see: a5→$5, a0→$4, a6→$6, symbol(v1, 5833) → free $3 → $3. Still $3.

Hmm.

What if the symbol pseudo got a LOWER priority than v1 so v1 (the current pointer) is allocated first and takes $3, then the symbol takes $7? The order: a5, a0, a6, v1(5833), a7(?). If v1 is allocated before a7 and takes $3, then a7 takes $7. For that, v1's pri must exceed a7's.

Currently: a7 (symbol) pri 20000, v1 pri 5833. If I swap which variable holds the symbol and which is the current pointer... The priorities are tied to the variables' uses:
- The symbol/return pointer: refs 10, live 15 → 20000.
- The current pointer: refs 7, live 24 → 5833.

If the source used the CURRENT pointer (v1) as the returned one and the symbol variable as the current... i.e., swap the roles: `a7` becomes the current pointer and `v1` the returned. But the target's asm has $3 = current, $7 = returned. The allocation would still give the high-pri pseudo $3.

Hmm, unless the high-pri pseudo is the *returned* one and it gets $7 because $3 is taken by a local.

OK, let me think about the target's build: with the pin, a7 is a HARD REG $7. The symbol goes into a7 ($7) and is copied to v1 ($3). v1 gets $3 because... the local pseudo 92 must be elsewhere (the pin changes local-alloc). 

Lever-free: the local pseudo 92 takes $3, so v1 can't. The symbol pseudo (a7) takes $3 because it's allocated before v1 and has no conflict with $3.

What if I make the symbol pseudo CONFLICT with $3? The conflict would come from a local pseudo in $3 overlapping a7's live range. Since the symbol pseudo is live across the whole function, ANY local in $3 would conflict... unless the conflict lists are computed per block and the local $3 pseudo (92) is in block 2 where a7 is live. Hmm, the dump says 76 (a7) does NOT conflict with $3. Maybe 92 is not in $3 in the actual allocation (the dispositions may be unreliable).

Let me try a different empirical approach: change the *else block* code so the local temps change, e.g., reorder the stores, use temps, etc. That could shift the local allocation and free $3 for v1... but the symbol would still take $3 first (it's allocated before v1 and $3 would be free).

Hmm! Unless the symbol's conflict list includes $3 (from a local in $3). If a local pseudo in $3 overlaps a7's range, a7 avoids $3 → takes $7 → then v1 takes $3. That's exactly the target! So the crack: make a block-local pseudo occupy $3 across a7's live range, forcing a7 to $7.

But wait, in the current build a7 got $3, so no local conflicts with $3 in a7's range. If I introduce a local temp that lands in $3 and is live where a7 is live... a7 is live everywhere, so any $3 local would conflict.

The local pseudo 92 got $3 in local-alloc (per the dispositions) — but maybe its live range doesn't overlap a7's (e.g., 92 is in block 2 but a7's live range... a7 is live in block 2). Hmm.

Let me look at the .lreg dump's block/live info to see pseudo 92's insns. Actually, let me try the empirical sweep: reorder the else-block stores and the loop statements.

Let me generate variants:
1. Store order permutations (the 7 stores).
2. Loop body order (the 4 increments).
3. do-while → goto/for loop.
4. The load: `v0 = v1; if (*v0 != 0)` vs `if (*v1 != 0)`.
5. v1 increments before a7.

Let me write a generator with ~20 variants.
