---
ts: 2026-11-06T18:50:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yUuAnUby60s2hGEuS7FJ
---
The .lreg dump (after local-alloc) shows insn 14 sets pseudo 76 and insn 17 sets 74 — the reverse of the initial .rtl (which had 14 → 74, 17 → 76). So cse/combine swapped them (copy propagation renamed the pseudos).

So after cse: 76 = a7 (the symbol), 74 = v1. Then the dispositions (74 in 7, 76 in 3) mean: a7(76) → $3, v1(74) → $7. That matches the asm: `la $3` (a7=$3), `move $7,$3` (v1=$7).

And the loop's load address: the RTL uses 77 = 74 (v1) → $7? But the asm's `lhu $2,0($3)` uses $3... Hmm, let me check the .lreg RTL for the load: insn 27 `(set 77 (reg 76))`? In the initial RTL, insn 27 was `(set 77 (reg 76))` where 76 was v1. After cse's renaming, v1 = 74. Let me look at the .lreg's insn 27.

I'm burning time. The bottom line: the candidate has a7=$3, v1=$7; the target a7=$7, v1=$3. The allocnos: 76 (a7 after cse) pri 20000 → allocated before 74 (v1) pri 5833. So a7 is allocated first → gets $3 (the lowest free after $2); v1 later → $7.

To flip: make v1's allocno priority higher than a7's, so v1 is allocated first and takes $3, and a7 takes $7. OR give a7 a preference for $7? No.

Priorities: 76 (a7) refs 10, live 15 → pri 20000; 74 (v1) refs 7, live 24 → pri 5833.

v1's refs 7, live 24 (long loop live range). a7's refs 10, live 15.

If v1's refs increased (more uses), its pri would rise. v1 is used: v0 = v1 (1), *v1 = *a0 (1), v1 += 0x68 (1)... and the loop. a7: incremented, returned.

To raise v1's pri above 20000: refs 7 → floor_log2(7)=2; 2*7/24 = 0.583 → 5833. To reach 20000: need 2*refs/live*10000 ≥ 20000 → refs/live ≥ 1 → refs ≥ live (24). Hmm, hard.

Alternatively lower a7's pri below 5833: refs 10, live 15 → 2*10/15=1.33 → 13333? The table said 20000 (floor_log2(10)=3, 3*10/15=2 → 20000). To get below 5833: 3*10/live < 0.583 → live > 51. No.

Alternatively: make the two allocnos CONFLICT with different orders? no.

Alternative: change the *order* by making a7 not a global allocno? a7 is live across the loop → global.

Alternative: **make a7 block-local**? impossible.

Alternative: make v1 get a *preference* for $3? The pref would come from a copy from a hard reg $3 — no.

Hmm, what about the C-level trick from moves.md: "split reused ptr var into tbl + t2: tbl wins s0 in greg" (func_80186DDC). Or "reused xt/lim split per axis: shorter pseudos flip greg order".

Here: a7 and v1 are two equal pointers. What if we eliminate one of them in the source, e.g., use only ONE variable (a7) for both the return and the current pointer? Then there'd be no copy at all (no `move`), and the asm would differ (no move v1,a3). Target has the move. So no.

What if we introduce a *third* variable or split a7's live range? E.g., a7 is used for the return; v1 for the current. What if we swap their roles in the source: `v1 = &D_8011FD10; a7 = v1;`? Then the initial RTL would be v1 = symbol; a7 = v1, and cse would... The asm would become `la $3; move $7,$3` or `la $7; move $3,$7` depending on the allocation. The allocation priorities might change because the pseudos' refs/lives swap? The pseudos are tied to the variables; the refs/live of each variable are the same regardless of the init order (v1 is used in the loop, a7 is returned). So the allocation would be the same, but the init direction would follow: `v1 = symbol; a7 = v1` → the symbol goes to v1's reg ($7), copy to a7 ($3) → `la $7; move $3,$7` — the TARGET's form!

Wait, let me check: mine currently has a7=$3, v1=$7. If the source is `v1 = &D_8011FD10; a7 = v1;`, then the symbol materializes into v1 ($7) and is copied to a7 ($3): `la $7; move $3,$7`. The target is `lui a3 (=$7); addiu; move v1 (=$3),a3`. YES! That matches!

But hold on: would the rest of the code stay the same? The loop uses v1 ($7) as the current pointer and a7 ($3) as the return pointer. The target uses $3 for the current pointer and $7 for the return. So the roles would be swapped → the loop's lhu/sh would use $7, and the return would be $3 → mismatching the target's loop.

Hmm. Because the register assignment (a7=$3, v1=$7) is fixed by the allocator; swapping the source init order only changes which variable gets the symbol first, but the allocator's assignment stays (the variables keep their uses). So the init would be `la $7; move $3,$7` (matching), but the loop would use v1=$7 for the current pointer (target uses $3) → mismatches elsewhere.

Unless the allocation also flips. Hmm.

OK, so the real task: flip the allocation of the two pointers. The allocator gives a7 (pri 20000) $3 and v1 (pri 5833) $7. Target: a7=$7, v1=$3.

What if we make the return pointer's allocno LOWER priority? a7's refs 10, live 15. If a7's refs were fewer or its live range longer, its pri would drop below v1's 5833. E.g., refs 10, live 15 → pri 20000. To drop below 5833: 3*10/live < 0.583 → live > 51. Not feasible.

What if v1's pri rises? refs 7, live 24. To exceed 20000: 2*7/live > 2 → impossible (max 14/24=0.58).

So the priorities are far apart; the order can't flip via refs/live.

BUT: the *preferences*! a7's allocno has no pref. If a7 had a pref for $7, it would take $7. What gives a preference? A copy from a hard reg. No.

What if a7 CONFLICTS with $3? Then a7 would take $7 (the next free) and v1 would take $3? Order: a7 (76) allocated first with $3 conflicted → takes $4? Hmm, $4 is taken by a0 (72, allocated later). Let me think: if a7's allocno conflicted with $3, its best_reg would be the lowest free: $4 (if free) → a7=$4. Bad.

Alternatively, make v1's allocno conflict with $7? Then v1 (allocated later) takes $3 (if free). And a7 (first) would take $3 unless conflicted. Hmm.

What if we make v1 allocated FIRST by raising its priority via *refs*: v1's refs are 7 (in the C: v0 = v1, *v0 → uses v1 once; *v1 = *a0; v1 += 0x68; plus the loop's uses). Actually the refs count 7 comes from the RTL. If the C used v1 more (e.g., the store `*v1 = *a0` uses v1), it's already counted.

Hmm.

**Alternative approach**: make a7 and v1 the SAME register by eliminating the copy, then reintroduce the move elsewhere? The target has `move v1,a3` — one copy. If the source used only a7 (no v1), there'd be no move. If the source used only v1, same.

**What about a different allocation via a third pointer variable?** E.g., introduce a temp for the load: `v0 = v1;` — already.

**What if v1 is not a separate variable but a pointer computed as `a7` in the loop?** no.

Hmm, let me look at the conflict lists: 74 (v1) conflicts 72 73 75 76 2 3 29 — it conflicts with $3! And 76 (a7) conflicts 72 73 75 76 2 29 — NOT with $3.

So v1's allocno conflicts with $3 (because of some other value in $3?). Hmm, "2 3" = v0 ($2) and v1 ($3). What occupies $3? A block-local pseudo (the load temps in $2, and $3 for...?). The conflict with $3 means v1 can't be in $3! Wait, but the target has v1 in $3.

Hmm, the conflicts are computed for the allocnos; v1's conflicts include hard reg $3, which means some *local* pseudo in $3 overlaps v1's live range. What local pseudo is in $3? From the dispositions: 92 in 3 (a local in block 2). So v1 (a global) conflicts with a block-local pseudo that got $3 (92). If v1 were allocated $3, it would conflict with 92 → 92 would be re-allocated by local-alloc... but global-alloc runs after local-alloc, so the local allocation is fixed.

In the target (pinned a7=$7), v1 would be... the pin forces a7=$7, and v1 gets $3 by global-alloc. But v1's conflict with $3 (the local pseudo 92) would forbid it! Unless in the target the local pseudo 92 doesn't get $3 (it's allocated after global-alloc? No — local-alloc runs BEFORE global-alloc; the local pseudo 92 got $3 in local-alloc, then global-alloc must avoid $3 for the globals).

Hmm, but the target's v1 = $3. So in the target's build, the local pseudo 92 did NOT get $3 — it got something else, because the pin a7=$7 changed the local allocation? No, local-alloc runs first and doesn't know about pins... Actually, `register ... __asm__("7")` makes a7 a *hard register* from the start, which affects local-alloc (the hard reg $7 is reserved, so local pseudos avoid $7). And the local pseudo 92 got $3 in my build; in the target it might get $3 too.

Then how does the target's v1 get $3 if it conflicts with 92? The conflict list is from MY build. In the target's build (with the pin), the conflicts differ.

Hmm! The pin's presence changes the *conflict graph* and the local allocation. So the target's v1=$3 might only be possible because the pin reserved $7 for a7 and the local pseudo 92 took... $3? Then v1 couldn't take $3 either.

Wait, in the target, v1 = $3 and the local pseudo 92 (whatever it is) must be elsewhere. So the pin's presence changed local-alloc's assignment of 92.

This is a deep interaction. Lever-free, local-alloc gives 92 $3, blocking v1 from $3.

So to crack item 2, I need the local pseudo 92 to NOT take $3, so v1 can. What is pseudo 92? "Register 92 used 4 times across 3 insns in block 2" — one of the store temps in the else block. In the RTL, the store block has pseudos 81-92 (the loaded values and addresses). 92 is the last one: `(set 92 (mem (reg 72)))`? Let me look at the .lreg RTL around insn 92.

Given the complexity, maybe item 2 is also a WALL. But let me try the simple C-level variants first:
- w2: swap the init order (`v1 = &D_8011FD10; a7 = v1;`) — see what happens (probably swaps the roles).
- w3: eliminate a7/v1 duplication: use a7 only, then the return a7; but the target has the move.
- w4: use a temp for the load: `v0 = v1` already.
- w5: change the loop increment order.
- w6: use `v1` as the loop variable and `a7` as a copy for the return... 

Let me test w2 (swap init) and a few.
