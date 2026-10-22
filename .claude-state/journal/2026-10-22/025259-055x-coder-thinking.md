---
ts: 2026-10-22T08:52:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_w8hRTa1P9uSe7xUjvQlE
---
Very useful! The block structure:
- Block 0: insn 4-92 (entry: arg→s0 copy, ptr load, st load, switch dispatch)
- Block 1: insn 94-95 (the bne)
- Block 2: insn 26-31 (case 2's call + const + slt + branch)
- Block 3: insn 35-37 (return 0)
- Block 4: insn 40-48 (case 2's continuation: q load, val=3, jump)
- Block 5: insn 50-62 (case 1's call + const + slt + branch)
- Block 6: insn 66-68 (return 0)
- Block 7: insn 71-79 (case 1's continuation: q load, val=4, jump)
- Block 8: insn 81-86 (default: return 0)
- Block 9: insn 98-110 (join: the two stores, the call, the return value)
- Block 10: insn 120-119 (epilogue)

Note: "Registers live at start: 29 30" — the hard regs live at block start are 29 (sp) and 30 (fp)! So v0/v1/a0 are NOT live at block starts (they're caller-saved and the flow analysis says so). Hmm, so the local allocation's availability of v0/v1 in the blocks isn't restricted by "live at start".

And the register usage summary:
- Register 72 (arg): 4 times, 18 insns, dies in 2 places, crosses 2 calls, POINTER.
- Register 73 (q): 4 times across 8 insns.
- Register 74 (ptr): 4 times across 8 insns; dies in 2 places.
- Register 76 (val): 3 times across 5 insns; 2 bytes.
- Register 78: 2 times across 4 insns in block 2 (the const 36864)
- Register 79: 2 times across 2 insns in block 2 (the slt result)
- Register 81: block 5 (const), 82: block 5 (slt)
- Register 83: 3 times across 5 insns (the switch value)
- Register 84: block 0 (const 1), 85: block 1 (const 2)

Note: r77 and r80 (the call results) are NOT listed → they're not in the lreg table (maybe because they're "used 2 times across 2 insns" — hmm, they should be). Whatever.

Now, priorities (from alloc_table): r73: refs 4, live 8 → pri = floor(log2(4))*4/8*10000 = 2*4/8*10000 = 10000 ✓. r74: same 10000. r76: refs 3, live 5 → floor(log2(3))=1 → 1*3/5*10000 = 6000 ✓. r83: refs 3, live 5 → 6000 ✓. r72: refs 4, live 18 → 2*4/18*10000 = 4444 ✓.

The order: 73 74 76 83 72 — r73 and r74 tie at 10000 → tie broken by allocno order (creation order: r73 < r74) ✓.

Now the KEY: the conflict sets.
- r73 conflicts {73, 76, 29}: NOT v0/v1/a0.
- r74 conflicts {72, 74, 83, 2, 29}: with v0.

So for r73 (q), the scan order (v0, v1, a0, ...) with first-fit: v0 is not in its conflict set → v0?! But the preference overrides → a0.

Hmm, but wait: is v0 really available? r76 (val) also doesn't conflict with v0, and r76 comes later. And r73's preference → a0.

Hmm, so the preference is what gives a0 rather than v0. If the preference were absent, r73 → v0 (first fit) and r76 (val) → v1? But the target has val in v0 and q in v1. So we'd need the ORDER to swap: val allocated before q. That happens if val's priority > q's priority. val's pri = 6000 (refs 3, live 5), q's = 10000 (refs 4, live 8). To make val's priority higher than q's, val would need a higher density: e.g. more refs or a shorter live range.

Alternatively: if the preference of r73 were 3 (v1), then r73 → v1 and r76 → v0 (first fit after v0 is taken? no: r76 is allocated after r73; the scan for r76: v0 (free, no conflict) → v0 ✓). And r74 (ptr) → a0 (preference 4) ✓. r83 → v1? Hmm, r83 (the switch value) conflicts {72,74,83,2,29} → v0 conflict, and v1 would be taken by r73 → r83 → ? In the target, r83 → v1 (the switch value is in v1: `lhu v1,2(a0)`). Hmm! Conflict: in the target, the switch value is in v1 AND q is in v1. Both in v1 — because in the target q is a hard reg ($3) and the switch value is a global allocated to v1.

In the lever-free version, if r73 (q) → v1, then r83 (the switch value) would need another reg (a0? a1?). The target has the switch value in v1 (`lhu v1,2(a0)`) and q in v1 (`lw v1,100(s0)`) — but those don't overlap in life (the switch value dies in block 0/1, q is born in block 4). Hmm! But they're both globals → the conflict computation is block-granular: r83 is live in blocks 0,1 (the dispatch) and r73 in blocks 4,7,9 → disjoint → NO conflict → they can share v1!

But the allocation order matters: r73 comes before r83 in the order. If r73 → v1, then r83 (allocated later) would find v1 taken... unless the conflict check allows sharing. In global.c, a hard reg can be assigned to two globals if they don't conflict — the code checks `conflicts_test` and also whether the reg is already assigned (`reg_renumber[r] >= 0` → skip?). Hmm, in GCC 2.7's global_alloc, the assignment loop:

```c
	  for (i = 0; i < n; i++)
	    {
	      ...
	      r = ...;
	      if (reg_renumber[r] < 0 && ! conflicts)  /* not yet allocated */
```
Hmm, if it requires reg_renumber[r] < 0 (unallocated), then two globals can't share a reg. But the target has the switch value (r83) and... in the target, is there another global in v1? The target's globals: 74 (→a0), 76 (→v0), 83 (→v1), 72 (→s0). Only r83 in v1. And q is hard $3. So no sharing needed.

In the lever-free version, r73 (q) and r83 (switch value) would both want v1 → only one gets it. The order (73 before 83) → r73 gets v1, r83 gets something else (a0? but a0 is r74's... r74 → a0 by preference; hmm, then r83 → a1?).

The target: `lhu v1,2(a0)` — the switch value in v1. If in the lever-free version the switch value went to a1, the asm would differ (`lhu a1,2(a0)`) → score.

Hmm! So we need: q → v1 AND the switch value → v1. Both globals in v1 — impossible if the allocator won't share.

Hmm, wait. Is the switch value (r83) really a global? It's defined in block 0 and used in blocks 0 and 1. Block 1 is the bne block. So it's live across blocks 0→1 → global ✓ (that's why it's in the alloc list).

And q (r73) is live in blocks 4, 7, 9.

If both are in the "regs to allocate" list, they can't share v1 (global.c assigns each global a distinct reg, I believe, since reg_renumber is per hard reg).

Hmm, but in the PINNED version, r83 → v1 and q is hard $3 — the hard reg $3 is used by q (a hard-reg pseudo) and by the local const/st pseudos. So the pinned version has v1 used by both r83 (global) and the locals (const 0x9000, slt) — the locals were allocated v1 by local_alloc (they're block-local and v1 is free at that point in blocks 2/5 since r83's v1 isn't live there).

Hmm OK. So the lever-free version needs: q → v1, switch value → v1, val → v0, ptr → a0, arg → s0. Since q and the switch value are both globals, they can't both be in v1... unless GCC's global.c DOES allow two globals to share a reg when they don't conflict.

Hmm! Let me check: in the lever-free version, r73 → a0 and r74 (ptr) → a0 — TWO globals sharing a0! So YES, global.c allows sharing when there's no conflict.

So in the lever-free version, r73 (q) and r74 (ptr) share a0. And r83 → v1 alone.

So: if r73 → v1, then r83 (allocated later) would find v1 occupied... but does the allocator check "is the reg already taken" or "does it conflict"? The dispositions show r73 in 4 and r74 in 4 → sharing happens. So the allocator checks conflicts only (and "regs_used_so_far").

So r83 could also get v1 if it doesn't conflict with r73. r83's conflicts: {72, 74, 83, 2, 29} — no 73 → no conflict with r73 ✓. And r76 (val): conflicts {73, 76, 29} → conflicts with r73! So val and q conflict (both live in blocks 4,7,9) → they can't share a reg. val → v0 ✓ (v0 not in r76's conflict set... wait, r76's conflict set is {73,76,29} — no 2 (v0) → v0 is free for val ✓).

And the scan order for r76: v0 first → v0 ✓ (matches the target: val in v0).

And r74 (ptr) → a0 by preference ✓ (the target: ptr in a0 ✓).

And r83 (switch value) → v1: scan order v0 (taken by r76? v0 has r76 — does r83 conflict with v0? yes, r83's conflicts include 2 (v0)) → skip; v1: r83 doesn't conflict with v1 (3 not in its conflict set) and r73 (if in v1) doesn't conflict with r83 → so r83 → v1 ✓ (matching the target's `lhu v1,2(a0)`).

So the ONLY missing piece: r73 (q) must get v1 instead of a0. And the preference (73 prefers 4) is what gives it a0.

If the preference were absent: r73's scan → v0 first? Is v0 free for r73? r73's conflict set {73,76,29} — no 2 → v0 is allowed → r73 → v0. Then val (r76) → v1? r76's conflicts {73,76,29} → no 3 → v1 allowed → r76 → v1. That gives q in v0 and val in v1 — wrong (target: q in v1, val in v0). Score would still be 4 (different insns) but different rows.

Hmm! So I need the preference to be v1, OR to change the allocation order so that val is allocated before q.

Option A: make the preference of r73 be 3 (v1).
Option B: make val's priority higher than q's so val is allocated first (→ v0), and then q → v1 (scan: v0 taken by val? the scan checks conflicts: r73 doesn't conflict with v0... hmm, if the reg is already assigned to another global (r76), does global.c allow r73 to take v0 too? r73 and r76 CONFLICT (r73's conflict set includes 76) → so no. Then the scan for r73: v0 → conflicts with r76? The check is "does this global conflict with the global that has this reg" — hmm, or "is the reg already used" (reg_renumber >= 0 → skip). In the case of r73/r74 sharing a0, they don't conflict with each other. So the rule is conflict-based.

So if val (r76) is allocated first → v0, then r73's scan: v0 → conflicts with r76 → skip; v1 → does r73 conflict with r76? The conflict is between the *globals* (r73 vs r76), and the check is whether the *reg* v0 is used by a conflicting global. Hmm, in GCC 2.7's global.c, `conflicts_test[i][j]` is a matrix over *allocnos* and also over *hard regs*. The hard-reg conflict part: r73's conflict list {73, 76, 29} includes 29 (sp) — so the conflict list mixes allocnos and hard regs. So the check for "can r73 take reg 2 (v0)" is: is 2 in r73's conflict list? No. But ALSO: is v0 already allocated to r76? In GCC 2.7's global_alloc, the check is:

```c
	      /* If we already have a reg for this global, ... */
	      if (reg_renumber[r] >= 0) ... 
```
Hmm, but r73 and r74 both got a0 — so reg_renumber[4] must have been -1 for both?! That can't be.

Hmm, maybe in GCC 2.7 the "sharing" works differently: global.c assigns hard regs to globals via `reg_renumber`, and then for the SECOND global that wants the same reg, it checks the conflict matrix: `conflicts_test[j][r]` where r is the hard reg... Hmm, in the dump "72 conflicts: 72 74 83 2 3 4 29" — the numbers include both allocnos (72,74,83) and hard regs (2,3,4,29). So the conflict list for an allocno includes the hard regs it conflicts with. When allocating r73 → a hard reg R, the check is: R must not be in r73's conflict list AND R must not be allocated to a global that conflicts with r73.

Since r73 and r74 don't conflict with each other, they can share a0 ✓. And r73 conflicts with r76 (val) → they can't share.

So: if the allocation order were r76 (val) first → v0, then r73's scan: v0 — is v0 in r73's conflict list? No! But v0 is allocated to r76, and r73 conflicts with r76 → so v0 is excluded ✓. Then v1: in r73's conflict list? No. Allocated to r83? r83 comes later. So r73 → v1 ✓✓✓.

So Option B: make val (r76) allocated BEFORE q (r73). The allocation order is by priority (density): r73 pri 10000 > r76 pri 6000.

To flip: increase val's density or decrease q's.
- val's pri = floor(log2(3))*3/5*10000 = 6000. If val had 4 refs and live 5: floor(log2(4))=2 → 2*4/5*10000 = 16000 > 10000. Hmm! Or if val's live length were smaller: pri = 1*3/live*10000; for pri > 10000 we'd need live < 3. Hmm.
- q's pri = floor(log2(4))*4/8*10000 = 10000. If q's live length were larger (e.g. 10): 2*4/10*10000 = 8000 < val's 6000? No, 8000 > 6000. Need q's pri < 6000: 2*4/live*10000 < 6000 → live > 13.3 → live ≥ 14. Or q's refs fewer: with 3 refs: 1*3/live*10000; for < 6000 → live > 5. q's live is 8 → 1*3/8*10000 = 3750 < 6000 ✓!! So if q had 3 refs instead of 4, q's pri = 3750 < val's 6000 → val allocated first!

q has 4 refs: 2 definitions (the loads) + 2 uses (the stores). Hmm, "refs" in flow.c counts reg_n_refs += loop_depth per mention. 4 = 2 loads + 2 stores.

How to reduce q's refs to 3? E.g., if one of the stores didn't mention q... The two stores: `q->unk2 = val` and `q->unk34 = 0` — both mention q. If the two stores used the same base... they do.

Hmm, but if the *value* of one store were derived from the other? no.

Alternatively increase q's live length to ≥14: q's live is 8 insns (blocks 4,7,9 — from the def in block 4 to the last use in block 9). Hmm.

Alternatively increase val's refs: val (r76) has 3 refs (2 defs + 1 use). If val had 4 refs and live 5 → pri 16000 > 10000 ✓. How to give val a 4th ref? E.g., if the value were used twice in the join: `q->unk2 = val;` and something else with val. Hmm, that changes the code.

Hmm! But wait — what about the *order* rule K1: "creation order (= regno order) is the tie-break". If q's pri and val's pri TIE, the lower allocno wins → q (r73 < r76). So we need val to be strictly higher.

Hmm, what if val's live length were shorter? val is live from its def (block 4/7) to its use in block 9 → live 5 insns. Can't shrink much.

What if val had 4 refs with live 5 → 2*4/5 = 1.6 → 16000. How to get a 4th ref for val? Hmm: `q->unk2 = val;` — 1 use. Plus 2 defs = 3. If the source had `val = 3;` in the arm and ALSO `val` used... hmm.

What about making val a *pointer*? no.

Alternatively: what if the *switch* were restructured so that val is defined ONCE (not twice)? E.g.:
```
case 2: ... val = 3; break;
case 1: ... val = 4; break;
```
2 defs. If instead:
```
val = 3;
if (st == 1) val = 4;
```
hmm, that changes the dispatch code.

Alternatively, what if the value were computed as `val = 3 + (st == 1)`? → different code.

Hmm, what about the *q* side: reduce q's refs from 4 to 3 by having only ONE use of q in the join? The two stores both use q. What if one store used a *copy* of q... no, that's another pseudo (and an extra move).

Hmm, what if the two stores were combined into one? E.g. `q->unk2 = val; q->unk34 = 0;` → 2 mentions of q. Can't reduce.

Hmm, alternatively increase q's live length: q's live = 8 insns (from the def in block 4 to the use in block 9, spanning blocks 4,7,9 — the "live length" is computed as the number of insns between the first def and the last use). If the stores were moved later (e.g. the second store after the call) — the target has the 2nd store in the delay slot (before the call). Hmm, in the source the order is: store unk2, store unk34, call. The target's asm: `sh v0,2(v1); jal; sh zero,52(v1)` — the second store is in the delay slot of the call, i.e., the source order is store, store, call but the scheduler moved the second store into the delay slot. So the source order (both stores before the call) matches.

If the source had the call BETWEEN the stores (store unk2; call; store unk34), the asm would be `sh v0,2(v1); jal; sh zero,52(v1)` — hmm, actually the same asm! Because the scheduler would put the second store in the delay slot anyway. Interesting! But the source order affects the "live length" computation? Not really.

Hmm, what would increase q's live length? The live length = last_use - first_def. q's def is in block 4 (insn 43) and its last use in block 9 (insn 104). The insn numbering: 43 → 104, that's 61 insns, but the "live length" reported is 8. Hmm, the lreg says "Register 73 used 4 times across 8 insns" — that's the "live length across 8 insns" (the number of insns in the live range counted by flow). Hmm, 8.

OK, this is the "density" knob. Let me think about which is easier: making val's priority higher, or q's lower.

Hmm! Alternative idea: what if q's live range were LONGER by using q EARLIER (in the entry block)? E.g., if q were loaded in the entry block... that changes the code.

What if val's live range were SHORTER? val's def is in block 4/7 (right before the jump to 9) and its use in block 9. Live = 5 insns. Hmm.

What if val had 4 refs? Idea: `val` could be used twice if the source were:
```
q->unk2 = val;
q->unk34 = 0;
```
Hmm, what if instead the value 3/4 were stored via a helper: e.g. `((Unkstruct*)q)->unk2 = val;` and also `val` used in a comparison? changes code.

Hmm, alternatively: make q's refs 4 but live 14+. q's live = 8. To lengthen q's live range, q must be live longer: e.g. if q were also live in the *entry* block (defined earlier) — that changes the code (one load instead of two).

Hmm hmm. OK, but WAIT. There's a subtlety: the priority also depends on the *size* factor: `pri = ... * size`. r72 (arg) is a pointer (size 4?). r76 (val) is 2 bytes (HI mode) → size 2! Look: "Register 76 used 3 times across 5 insns; 2 bytes". And the alloc_table's pri for r76 = 6000 = (1*3/5)*10000*1? Hmm, with size 2 it'd be 12000. The alloc_table computed 6000 without a size factor, but the actual gcc formula includes size. Hmm! Let me recompute: pri = (int)(((double)(floor_log2(n_refs) * n_refs) / live_length) * 10000 * size).

For r76: floor_log2(3) = 1, n_refs = 3, live = 5, size = 2 (HI mode = 2 bytes) → (1*3/5)*10000*2 = 12000!! That's > r73's 10000 (size 4: (2*4/8)*10000*4 = 40000?!). Hmm, that doesn't work either: r73's size would be 4 → pri = 2*4/8*10000*4 = 40000. And r72: 2*4/18*10000*4 = 17777.

But the actual order is 73 74 76 83 72 and the alloc_table's pri (without size) is 10000, 10000, 6000, 6000, 4444 — matching the order. If size were included, r73 and r74 (size 4) would have 40000, r76 (size 2) 12000, r83 (size 4, HI→SI?) 24000, r72 (pointer) 17777. Then the order would be 73, 74, 83, 72, 76 — which does NOT match the observed order (73 74 76 83 72).

So the size factor is 1 for all here, or the formula differs. Hmm, but r76 is 2 bytes and r72 is a pointer... The observed order matches the no-size formula. Hmm, but the alloc_table tool says it computes the priority — and it produced the right order. But the tool's docstring says the formula is `floor(log2 refs) * refs / live * 1e4` — no size. And the order matches. So for this function, size doesn't matter (maybe the size factor is only applied in the 2.8 version).

OK so: the order is 73 (q, 10000), 74 (ptr, 10000), 76 (val, 6000), 83 (switch value, 6000), 72 (arg, 4444).

To get val (r76) before q (r73), I need val's pri > q's pri.

val: refs 3, live 5 → 6000. To beat 10000: refs 4 → 2*4/5 = 1.6 → 16000 ✓; or live 3 → 1*3/3 = 1.0 → 10000 (tie → r73 wins by allocno order ✗); or live 2 → 15000 ✓.

q: refs 4, live 8 → 10000. To go below 6000: refs 3 (→ 1*3/8 = 3750 ✓) or live ≥ 14 (→ 2*4/14*10000 = 5714 ✓).

So: make q have 3 refs, or val 4 refs, or q's live ≥ 14.

q's refs: 2 defs + 2 uses. Hmm, how about this: what if the *second* store's base were not q but a *copy*? That adds a pseudo (and a move insn) ✗.

What if one of the stores were done via a *different* expression that doesn't mention q? E.g., store unk2 = val using q, and store unk34 = 0 using... q again. Hmm.

Hmm! What if the *value* stored (val) were stored via q and the *other* store (unk34 = 0) were... it needs the base q.

So q's refs can't drop below 4 without changing the code.

VAL's refs: 3 (2 defs + 1 use). To get 4: hmm, what if val were used in both stores? No (unk34 = 0).

Hmm, what if the *value* were 0 in one case? no.

Hmm, what about val's live length: 5 insns. The def is at insn 46 (block 4) and the use at insn 101 (block 9). The "live length" = 5 insns (counted by flow: the number of insns in the live range?). To reduce it to 2-3, the def must be closer to the use. E.g., if the value were assigned in the join block instead of the arms! But then the arms would need to communicate the value... which is the same problem.

Hmm! What if the value were communicated via the *switch* itself: e.g. `switch (st) { case 2: ... }` — hmm.

OK, alternative approach: change q's live length to ≥14. q's live range: def in block 4 (insn 43) to last use in block 9 (insn 104). The "live length across 8 insns" — hmm, 8 insns. To make it 14+, q must be live over more insns — e.g. if q were used LATER (after the call). The last use is the second store. If the second store came after the call in the source (i.e. `q->unk2 = val; func_80178BF8(); q->unk34 = 0;`), then q's live range would extend past the call → longer live length! And the asm? The target: `sh v0,2(v1); jal func_80178BF8; sh zero,52(v1)` — the second store is in the delay slot of the call. If the source had the call between the stores, the scheduler would likely still put the second store in the delay slot ✓ (it's ready). Actually, would it? The delay slot needs an instruction that doesn't depend on the call's result — the store `sh zero,52(v1)` qualifies. And it's the same instruction. So the asm might be IDENTICAL!

And in the source, the call func_80178BF8() would then be between the stores. Hmm, but wait: does the call clobber v1? Yes, v1 is call-clobbered → the store after the call would need q in a callee-saved reg or reloaded!! That changes the code (q would move to s3 or be reloaded). Hmm, that's bad. Unless the value is reloaded from memory: `lw v1,100(s0)` — an extra insn.

Hmm. So no.

OK, so what about the *other* direction: make val's priority higher by giving it more refs. Hmm.

Hmm, hold on! What about a completely different idea: what if the q pseudo's *live length* is what I can change by moving the q load EARLIER? The q load is in block 4 (after the branch). What if the source loaded q BEFORE the branch (i.e., before the comparison)? Then q's def would be in block 2 (the call block) — but then q would be live across the call → it'd need a callee-saved reg → the asm would change (the load would move before the call). ✗.

OK so, what about the *ptr* pseudo (r74, pri 10000, allocated second)? It's not relevant.

Hmm, hmm. So the allocation-order lever looks hard. Let me reconsider the *preference* lever: the preference for r73 → a0 comes from a copy of r73 into a0. Where?? The .jump dump (pre-alloc) shows NO such copy. So the copy was created between the jump pass and global_alloc — i.e., by local_alloc? or by sched1?

Hmm, wait. Actually, maybe the "preference" isn't from a copy at all! Let me reconsider: maybe the .greg dump's "preferences" line prints something else entirely, e.g. the *copy preferences* of the allocno: `reg_preferred[allocno]` — set by set_preference when a copy connects the allocno to a hard reg. In our function, which globals are connected to hard regs by copies? r74 (ptr) → the call-arg copy into a0 ✓ (that's real).

For r73 (q): a copy into a0... The .jump dump doesn't show one. Hmm! But maybe the .jump dump is BEFORE the "expand" of the store? No, expand is before jump.

Hmm, hold on: maybe the dump's "preferences" line for 73 is not a preference but the *conflict* with a hard reg? Hmm, ";; 73 conflicts: 73 76 29" and ";; 73 preferences: 4" — the number 4 = a0.

Wait a moment! What if the "preferences" print is: ";; %d preferences:" followed by the *hard regs* that this allocno prefers, and the source is `set_preference` from a copy — and the copy is created by LOCAL_ALLOC's coalescing? Per K8: "local-alloc ... TIES (coalesces) op0's dest into a dying input at the dest's FIRST set (combine_regs)". Coalescing merges a copy's operands.

Hmm, in our case: is there a copy whose dest is r73 and whose src is a0? That would be `(set (reg/v:SI 73) (reg:SI 4 a0))` — hmm! Where would that come from? The call-arg copy for func_8012BD14 is `(set (reg:SI 4 a0) (reg/v:SI 74))` (dest a0, src ptr).

Hmm, but for r73 there's no such copy in the .jump dump.

Hmm, so maybe the copy is created by local_alloc (which runs after jump and before global_alloc). local_alloc can create copies? It does "combine_regs" (coalescing) — it merges a copy's src and dest. Hmm.

OR: the copy is created by *sched1* (scheduling)! sched1 can insert copies? Hmm, in GCC 2.7, sched1 does "scheduling" and there's a "pre-RA" scheduling that may create moves? Hmm, actually, gcc 2.7's sched1 does "reorder basic blocks" and "insert copies"? Hmm.

Hmm, what about the *jump* pass creating a copy: the join block (9) is reached from blocks 4 and 7; the value r76 (val) is defined in both → no copy needed.

Hmm, what about this: the *q* pseudo r73 is defined in blocks 4 and 7. In block 4, the def is `lw`; in block 7 also. Fine.

OK, let me just look at the .sched (sched1) dump for the function, or better: let me find the copy by looking at the .lreg dump's later part (it prints the local allocation and maybe the copies).

Actually, easier: let me look at the .greg dump's RTL for the join block in the *post-allocation* form and check the store's base. Hmm.

Alternatively, let me get the RTL between local_alloc and global_alloc: the .lreg dump is printed at the END of local_alloc (or during). Let me look at the .lreg section for the qty allocation details, which may print the copies.

Let me look at more of the .lreg section (the allocation part).
