---
ts: 2026-11-07T00:11:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HmAekPqgE0JWGRplSdiU
---
So local-alloc assigns in order of decreasing pri = floor_log2(refs)*refs*size/(death-birth). Ties by qty number (birth order).

From the alloc_table: the priorities shown are exactly this (pri column). The allocation order is by pri descending:
r73 10000, r91 10000, r92 10000, ... (many ties), r72 7500, r89 7500, r96 2500, r74 1034, r75 1034, r78 967, r79 967, r77 750, r76 714.

But these are across different blocks. local-alloc processes each basic block separately. The block with our variables is block 0.

In block 0, the quantities include: x1, x0, white, y0, y1, base, and the struct stores... The table shows "blk 0" for most.

Order by pri in block 0: r73 10000, r91-93, r98-100 (10000), r72 7500, r89 7500, r96 2500, r74 1034, r75 1034, r78 967, r79 967, r77 750, r76 714.

Hmm, but many of those are small temps (r91, r92...) that die quickly and get a1/v0 etc.

Our variables are r74, r75, r78, r79, r77, r76 with pri 1034, 1034, 967, 967, 750, 714.

The allocation order among them: r74 (1034) and r75 (1034) tie → lower qty number first. Then r78 (967), r79 (967) tie, then r77 (750), r76 (714).

The final assignment: r74=s4, r75=s0, r78=s5, r79=s1, r77=s2, r76=s3.

Hmm, that doesn't look like "first in order gets the lowest free reg". Let me think: find_free_reg tries registers in a preference order. It has copy preferences (prefs) and uses `qty_phys_reg`.

Actually, local-alloc's find_free_reg considers the *hard reg preferences* from copies (e.g., `x1 = a0 + 3` — x1 has no copy pref; but the struct stores...). Hmm.

Also `qty_phys_copy_sugg` — the copy preferences.

Hmm, and the assignment r74=s4 vs r75=s0 (tie) — the tie-break by qty number should give the lower qty the first pick. If r74's qty < r75's, r74 picks first. It got s4 (not s0). Why? Because s0 might be preferred by r75 or by another qty.

Hmm, wait — the alloc_table's "pri" is computed from the dump, but the actual assignment order is by qty_compare. Let me get the qty numbers. Hmm.

This is getting complicated. Let me look at the .lreg dump for the actual "Register N in M" lines or the qty ordering.

Alternatively, empirical: reorder the C statements and see.

Let me think about what changes the pri values:
- pri = floor_log2(refs)*refs*size/(death-birth)
- refs: number of references in the block
- death-birth: live length in the block

For our variables:
- r76 base: refs 3, live 42 (longest) → pri 714
- r77 white?: refs 3, live 40 → 750
- r78, r79: refs 3, live 31 → 967
- r74, r75: refs 3, live 29 → 1034

Wait, these are all refs 3. So the pri differences come from live length.

Target assignment: x1=s0, x0=s1, y1=s2, base=s3, white=s4, y0=s5.

Let me map by live length:
- base (longest live 42) → s3 (4th)
- white (live 40) → s4 (5th)
- the live-31 pair → s5, s1
- the live-29 pair → s4, s0

Hmm, confusing. Let me identify which pseudo is which variable. Let me use the .lreg dump to see the birth/death or the references.

Actually, easier: let me look at the final assembly and the C. In mine:
- x0 = s0
- y1 = s1
- white = s2
- base = s3
- x1 = s4
- y0 = s5

And the pri values: r74=s4 (x1), r75=s0 (x0), r78=s5 (y0), r79=s1 (y1), r77=s2 (white), r76=s3 (base).

pri: r74=1034, r75=1034, r78=967, r79=967, r77=750, r76=714.

So:
- x1 (r74): 1034, live 29
- x0 (r75): 1034, live 29
- y0 (r78): 967, live 31
- y1 (r79): 967, live 31
- white (r77): 750, live 40
- base (r76): 714, live 42

Allocation order (pri desc, ties by qty): r74, r75 (tie), r78, r79 (tie), r77, r76.

Result: r74=s4, r75=s0, r78=s5, r79=s1, r77=s2, r76=s3.

Hmm, that's not monotonic. s0 goes to r75, s1 to r79, s2 to r77, s3 to r76, s4 to r74, s5 to r78.

So the allocation order by resulting reg: r75→s0, r79→s1, r77→s2, r76→s3, r74→s4, r78→s5.

That order is: r75 (1034), r79 (967), r77 (750), r76 (714), r74 (1034), r78 (967).

Hmm! That's weird — r74 has the highest pri but got s4 (allocated late). 

Unless the s0-s5 assignment isn't "first come first served". local-alloc's find_free_reg has *preferences* (from copies and from `qty_phys_sugg`). E.g., the struct stores `line.x0 = x0` — a store to memory, no reg pref.

Hmm, but there are copy preferences: `y0 = a1 - 3` no. The `GsSortLine(&line, &base[...], 0)` call args: a0=&line, a1=base[...], a2=0. Hmm.

Actually, wait: `move s1,a0` — the parameter copy `x0 = a0`? No, target does `move s1,a0` for x0. Hmm, that's a copy from a0, giving x0 a preference for a0? But a0 is caller-saved and x0 is live across the call → needs callee-saved.

The preferences might explain the odd assignment.

Hmm, this is complex. Let me try the empirical route: reorder statements and see if the assignment shifts toward the target.

The C statements before the first call:
```
y0 = a1 - 3;
x1 = a0 + 3;
[launder removed]
y1 = a1 + 3;
white = 0xFF;
x0 = a0 - 3;
line.tag = 0;
line.r = white;
line.g = 0;
line.b = 0;
line.x0 = x0;
line.y0 = y0;
line.x1 = x1;
line.y1 = y1;
GsSortLine(&line, ...);
```
The birth order of the variables is y0, x1, y1, white, x0 (in statement order).

qty numbers are assigned in birth order. So y0's qty < x1's qty < y1's < white's < x0's.

For ties (r74/r75 both 1034; r78/r79 both 967), the lower qty wins. Which are tied? x1 (r74) and x0 (r75) both 1034. x0's qty > x1's qty (x0 born later). So the tie-break "lower qty first" → x1 (r74) allocates before x0 (r75).

Similarly y0 (r78) and y1 (r79) both 967: y0 born first → y0 (r78) allocates before y1 (r79).

So the allocation order: x1, x0, y0, y1, white, base? That would give s0,x1... but the actual assignment is x1=s4.

So the pri order must be different, OR find_free_reg's preferences dominate.

Hmm, the alloc_table's pri column uses the same formula. So the order should be by pri: x1 1034, x0 1034, y0 967, y1 967, white 750, base 714. But the resulting regs (s4, s0, s5, s1, s2, s3) don't match a simple first-fit.

Unless the qtys are in different blocks! The table shows blk 0 for all. Hmm.

Wait, maybe `find_free_reg` is called with `qty_phys_num_sugg` — the "suggested" registers from copy instructions. Let me look: the first loop assigns registers to qtys with suggestions (copy prefs). So a qty with a copy preference gets its preferred reg FIRST, before the main ordering.

The copies: `x1 = a0 + 3` (add, not a copy). `y0 = a1 - 3`. Hmm.

But `line.r = white` etc. are stores.

Hmm, what about the call `GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0)` — base is used to compute an address.

Hmm, the copy prefs might come from `move s1,a0` — the parameter a0 is copied to x0. In the C, `x0 = a0 - 3` is an add, not a copy.

Wait, but the target's assembly does `move s1,a0` then `addiu s1,s1,-3`. That's `x0 = a0 - 3` where the compiler first copies a0 to s1 then subtracts. Why? Because a0 is used... hmm, a0 is used for `x1 = a0 + 3` too. So the compiler keeps a0 and computes both. The `move s1,a0; addiu s1,s1,-3` suggests x0 = a0 then -3.

OK, I'm going too deep. Let me be empirical: try reordering the statements. The allocation order depends on birth order (qty numbers) and pri.

Target assignment: x1=s0, x0=s1, y1=s2, base=s3, white=s4, y0=s5.
Mine: x0=s0, y1=s1, white=s2, base=s3, x1=s4, y0=s5.

Interesting: in mine, the allocation order (by reg) is x0, y1, white, base, x1, y0. In target: x1, x0, y1, base, white, y0.

Hmm, base is 4th in both. y0 is 6th (last) in both. So the middle differs.

The difference: mine allocates x0, y1, white first; target allocates x1, x0, y1 first.

Hmm, white is 3rd in mine, 5th in target. x1 is 5th in mine, 1st in target.

What determines this? Maybe the *live ranges* (death-birth):
- x1 live 29, x0 live 29, y0 live 31, y1 live 31, white live 40, base live 42.

pri: 1034 (x1,x0), 967 (y0,y1), 750 (white), 714 (base).

If allocation were by pri desc: x1, x0, y0, y1, white, base → s0,s1,s2,s3,s4,s5 = x1=s0, x0=s1, y0=s2, y1=s3, white=s4, base=s5. But target has y1=s2, base=s3, white=s4, y0=s5. Close but y0/y1 and base differ.

Hmm, target: x1=s0, x0=s1, y1=s2, base=s3, white=s4, y0=s5.
Expected by pri: x1=s0, x0=s1, y0=s2, y1=s3, white=s4, base=s5.

So target has y1 and base before y0 and white... 

Hmm, the live lengths differ from what I assumed. Let me identify the pseudos properly. Let me look at the .lreg dump with the variable birth/death.

Actually, let me just try reordering the C statements empirically. The lever: statement order. Let me generate permutations of the 5 assignments (y0, x1, y1, white, x0) — 120 permutations. That's a lot but each score is ~1-2s. 120 × 1.5s = 3 min. Feasible.

But the emitted code must match the target's prologue order:
```
sw s1,36(sp); move s1,a0      ; x0 = a0
sw s2,40(sp); move s2,a1      ; y1? = a1
sw s5,52(sp); addiu s5,s2,-3  ; y0 = a1-3
addiu s0,s1,3                 ; x1 = a0+3
addiu s2,s2,3                 ; y1 = a1+3
addiu a0,sp,16
move a2,zero
li s4,255                     ; white = 255
addiu s1,s1,-3                ; x0 = a0-3
```
Hmm, the scheduling reorders. So the C order may differ from the assembly order.

Let me try the 120 permutations of the 5 assignment statements. Actually, the launder's position matters too, but we removed it.

Let me generate and score. I'll write a script.

Actually, note: the assignments are `y0 = a1 - 3; x1 = a0 + 3; y1 = a1 + 3; white = 0xFF; x0 = a0 - 3;`. Permuting these 5 statements (120) — let me do it.

Let me also consider that the target's `x0 = a0 - 3` is last in the C (after white). The current order is y0, x1, y1, white, x0. Hmm, the target assembly has x0 last (addiu s1,s1,-3 at the end).

Let me just run the 120.

To save time, let me write a script that generates all 120 and scores them in a loop, printing only the best.

Actually 120 × tryinc invocations, each ~1.5s = 3 min. The Bash tool timeout is fine (default 600s). Let me do it.

Hmm, but the brief says one action per command... generating and scoring in one script is fine (it's a batch of tries).

Let me write a script that does it in-process (imports delever_search) to be fast. Actually tryinc.py spawns a full python each time (~1s). 120 = 2 min. OK.

Better: write a python script that imports delever_search once and loops over candidates. Let me check how to call it programmatically... The Scorer class is in delever_search. Simpler: use subprocess but that's slow.

Let me look at how ds.main works — it parses sys.argv. I could call the scoring function directly. Let me check the --try path.
