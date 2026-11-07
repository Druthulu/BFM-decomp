---
ts: 2026-11-06T20:27:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sWNEALWHp06IbwwESHcZ
---
The fill scans from `thread` (the branch target path). The xori is at the join, in the else thread. `stop_search_p(trial, 1)` stops at a CODE_LABEL. Between the branch target (2194) and the xori (2198) there's no label, so it found it.

Now: how to place a CODE_LABEL between the else-arm load and the xori in plain C? A basic block boundary. A CODE_LABEL is emitted at the start of a block that has multiple predecessors. The join after an if/else has a label if both arms jump to it. Here the else arm falls through to the join (no jump), so no label.

If the else arm ended with a jump to the join (e.g., if the else arm were more complex or if we used a goto), there'd be a label. But adding a jump changes code.

Alternatively, use an if/else where both arms set v and then the join has a label... The C is:
```
if (unkFC != 0) { v = unkDC; if (v == 0) { unk2=5; return; } }
else { v = unkDC; }
__asm__("");  v ^= 1;
```
The barrier is at the join. What if we restructure:
```
if (unkFC == 0) { v = unkDC; } else { v = unkDC; if (v == 0) { unk2=5; return; } }
v ^= 1;
```
That swaps the arms (inverted condition). The code shape might change (branch polarity). The notes say the current shape is needed for other reasons.

Hmm. What about `if (...) {...} else {...}` followed by a `do { } while (0);` empty loop? That would create a loop with a label/jump at the join. C0535 says do-while splits cse1 EBB. But we tried do-while around `v ^= 1;` — jump2 removed it. What about `do { } while (0);` as an empty statement before the xori? The loop body is empty; gcc might remove it entirely.

What about `do { v ^= 1; } while (0);` — we tried, no change. The loop was removed before reorg.

Let me check whether the do-while survived to the .dbr in vE. Maybe it survived but didn't stop the search (a NOTE is not a stop; a JUMP_INSN is). If the loop left a JUMP_INSN, stop_search_p would return 1. Let me check vE's dbr dump around the xori.

Actually, in vE, the score didn't change at all, so the code was identical. jump2 removed the loop's jump.

Alternative: make the loop's jump non-removable by making the condition non-constant? e.g., `do { v ^= 1; } while (v & 0);`? That's an identity-ish condition but it's a real loop (may iterate? `v & 0` is always 0 → infinite? no, do-while(v&0) = execute once, condition false). The compiler would fold `v & 0` to 0 → same as while(0) → removed.

What about a loop that the compiler can't prove terminates? Not acceptable (it must not loop).

Hmm.

Let me step back and consider the WALL option for cluster 1, but we still need cluster 2. A WALL is allowed if we can't crack it; we need ≥30 tries and ≥20 min for a wall. But we have 4 items and limited time. Let me focus on getting both clusters if possible.

For cluster 2 (the launder): the volatile asm acts as a sched2 full barrier. Real-C alternative: create a dependency so the const can't sink past the store.

Idea: make the store's source value be derived from r such that the store depends on the const, while keeping the stored value 7. E.g.:
```
((Unkstruct_800B5CB8 *)s0)->unk2 = 7;
```
becomes
```
v = 7;               // v is the local set later to 0x20 anyway
((Unkstruct_800B5CB8 *)s0)->unk2 = v;
func_8012B178(q, r);
v = 0x20;
```
No dependency on r.

What if we write the store as `((Unk*)s0)->unk2 = (s16)(7 + (r & 0));`? identity.

Hmm, what about a real dependency via the *address*: `*(s16*)((u8*)s0 + 2) = 7;` — same.

What if the store's value is computed from the *previous* value: `unk2 = (unk2 & 0) | 7;`? That adds a load (`lh`) — the target doesn't have it.

Hmm.

Alternative for cluster 2: make the const not sinkable by making it a *non-constant* to sched2, i.e., a value that is computed from a register that's live. But the value must be 0xFFF80000.

Wait — what about making the constant depend on the `q` pin (a0 = s0)? `r = 0xFFF80000` can't.

OK, what about a completely different formulation: what if `r` is assigned from a *parameter* of the callee? No.

Hmm, what if we swap the order: put the store BEFORE the r declaration in the source, so the RTL order is move a0, li, sh, const, call — the const is already last, so sched2/reorg gives the same as nolau. No.

What if we put the const definition before the `q` pin (as vD)? RTL: const, move a0, li, sh, call. sched2 could still sink the const. vD scored the same, so it did.

Let me look at vD's sched2 order to see if the const sank again.

Alternatively, maybe I can make the const's *use* have a dependency on the store by writing the call as `func_8012B178(q, r + (v & 0))`? identity.

Hmm, hold on. What about making the stored value 7 come from the *same* pseudo as the const's low bits? Not value-preserving.

Let me look at this from another angle: what if we DON'T need the launder if we change the store/const types or the register allocation? The score is 10 with two clusters. Maybe a different formulation makes sched2 order the const first for a different reason: e.g., if the const and the li target different hard regs with an anti-dependency.

In the target, a1 (the const) and v0 (the li) are different regs. In mine too.

What if we make the constant's register conflict with something? E.g., if the const were assigned to v0 (the same reg as the li), there'd be a dependency forcing an order. The target uses a1 for the const. The pin q is a0. The const pseudo naturally gets a1.

Hmm.

Let me look at the actual sched2 priority computation: all insns have priority 1 in this block, so the tie-break decides. Let me read rank_for_schedule to understand the tie-break, then find a C change that flips it.

rank_for_schedule (sched.c ~ line 700?): compares INSN_PRIORITY, then INSN_LUID, then... let me look.
