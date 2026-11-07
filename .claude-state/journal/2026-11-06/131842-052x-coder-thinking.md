---
ts: 2026-11-06T20:18:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RuitJZCXH621XLe17h3b
---
Hard regs do get reg_n_sets counted. But in the pinned body, `pv = *(u32*)p` sets $3 — reg_n_sets[3] would be incremented for every set of $3 in the whole function. Are there other sets of $3? Yes, calls clobber $3? No — reg_n_sets counts explicit sets in RTL, not call clobbers. Other code may set $3 (e.g., other functions in this function using v1 as a scratch — but those are pseudos allocated to $3 only after reload; pre-reload they're pseudos, so reg_n_sets[3] counts only hard-reg $3 sets = the pinned pv set). So reg_n_sets[3] = 1 in nolau, = 2 with the launder. Confirmed.

So the boost on the $3 set requires: $3 live at block entry, reg_n_sets[3]==1.

Alternative to kill the boost: make $3 NOT live at the block entry! bb_live_regs is computed from the CFG. If $3's value from an earlier block were dead at entry... it's about the hard reg being live. Hard reg $3 is call-clobbered; after a call, is $3 live at the next block's entry? bb_live_regs for hard regs is computed by flow: regs live across blocks. Since $3 is set in this block and used, it's not live at entry unless there's a path from a set before. Hmm, but empirically the boost happens.

Wait, re-read: `if (bb_live_regs[offset] & bit) return (reg_n_sets[i] == 1); return 0;`. If $3 is NOT live at block entry, returns 0 → no boost. So the boost requires $3 live at entry. Since $3 is set by... the pinned pv is set inside this block; at block entry $3 might be live because the previous block (a call site) has $3 live? Hmm.

This is getting deep. Let me just try real-C variants empirically:

A. `pv = 0;` at the end (dead reset). Expect +1 insn (li $3,0) → 178, but maybe the schedule improves enough to score low. Test.
B. `pv = pv;` at the end (self-copy, deleted by delete_dead_from_cse, but maybe reg_n_sets... it's deleted before loop/sched, so no effect).
C. Reuse pv in the second half: 
```
ot = ...;
pv = ((Unk*)ot)->unk40;
((Unk*)ot)->unk40 = (pv & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
This gives a real second set of $3 with an instruction (lw $3,0x40(v1)) — target has that load in v0. So mismatch.

D. Give pv a second set that combine deletes: e.g., `pv = pv + 0;`? combine folds to a copy → deleted as self-copy.

E. Change the variable: make pv `u32` and do `pv &= 0xFF000000;` then use pv in the or: 
```
pv = *(u32 *)p;
pv &= 0xFF000000;
*(u32 *)p = pv | (...);
```
That's a real second set (`and $3,$3,0xff00<<16`)! Target: `and v1,v1,a0` then `or v1,v1,v0` then `sw v1,0(s1)`. That's exactly 2 sets of v1 in the target! Look at target:
```
lw v1,0(s1)
...
lui a0,0xff00
lw v0,0x40(v0)
and v1,v1,a0      <- set 2 of v1
and v0,v0,a3
or v1,v1,v0
sw v1,0(s1)
```
So the target DOES have 2 sets of $3: the lw and the `and`. So reg_n_sets[3] = 2 in the target naturally! That's why no boost in the target.

In mine, the `and` is `and v1,v1,a2` — also a set of $3 (v1). Wait, mine also has `and v1,v1,a2`. So mine also has 2 sets of $3. Then why the boost difference?

Hmm, but the launder adds a THIRD set. Hmm, then the boost in nolau isn't about reg_n_sets... unless the C source's `(pv & 0xFF000000)` gets combined differently.

Wait: in the C source, `*(u32 *)p = (pv & 0xFF000000) | (...)` — the `and` is a separate insn setting a new pseudo (not pv!). Since pv is pinned to $3, `pv & 0xFF000000` creates a *pseudo* result, which local-alloc may assign to $3 or another reg. In the target, the and's result is v1=$3 (reusing pv's reg after pv dies). In mine, the and's result is v1 too (`and v1,v1,a2`). So both have `and v1,v1,...`.

But reg_n_sets[3]: the `and` writes a *pseudo*, not hard $3, before reload. So reg_n_sets[3] counts only hard-reg sets: the pinned pv load = 1. The `and` writes a pseudo, so reg_n_sets of the pseudo is 1 (the and's dest pseudo) — and that pseudo is born... The boost applies to the *and* insn's dest pseudo? The and's dest is a pseudo with 1 set, live-before? Probably not live before (born there).

Hmm, so which insn gets boosted? The notes say the `lw $v1,0($s1)` (pv) got boosted. With reg_n_sets[3]==1 and $3 live at block entry.

OK. The launder gives $3 a 2nd set (at the end), so reg_n_sets[3]=2 → no boost on the lw.

So we need a second set of hard $3 that emits no insn... 

OR: we could avoid the boost by making $3 not live at block entry. bb_live_regs is the live-at-block-start set. $3 is live at the start of the tail block because the *previous* block (the last ApplyMatrixSV call) leaves $3 live? Hard regs live across block boundaries: after a call, $3 is clobbered but GCC's flow treats call-clobbered regs as... bb_live_regs for hard regs is computed in `flow_analysis` with `regs_live_at`? Hmm.

Actually the block in question: the tail block starts after the last ApplyMatrixSV call. $3 would not be live at entry unless something before sets it and it's used here. Hmm, but the boost DID apply, so $3 is live at entry. Maybe because `pv` (hard $3) is assigned in this block and flow's liveness for hard regs is whole-function (`regs_live` propagation)? For hard regs, flow tracks per-block liveness too.

Let me not theorize; test variants.

Variant A: `pv = 0;` at the end. Score?
Variant B: `pv &= 0xFF000000;` split the and into its own statement (a real live 2nd set — like the W47 crack "split `pv = pv & 0xFF000000` into its own stmt — a real live 2nd SET (reg_n_sets=2) demotes sched1 birthing boost; bytes identical"). That's EXACTLY the moves.md entry: "launder | func_8018AB20 | MATCH: split `pv = pv & 0xFF000000` into its own stmt — a real live 2nd SET (reg_n_sets=2) demotes sched1 birthing boost; bytes identical (W47)".

But that's for a different function. Here, pv is the loaded value and `pv & 0xFF000000` is used in the or. If I split: `pv = *(u32*)p; pv &= 0xFF000000;` then pv (hard $3) has 2 sets! And the second set is a real insn (and $3,$3,...) that the target already has (as `and v1,v1,a0` where the and's dest is v1=$3 in target). But would the C produce the and's dest as $3? In target, yes, the and writes v1. In mine, the and writes v1 too (a pseudo allocated v1). Hmm, but if pv is hard $3 and we do `pv &= 0xFF000000`, the RTL is `set $3 = and($3, 0xFF000000)`. Then the or: `*(u32*)p = pv | (...)`. Target: `and v1,v1,a0; and v0,v0,a3; or v1,v1,v0; sw v1,0(s1)` — exactly.

So variant B: replace
```
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (CAST_NONSTRUCT(u32, *(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)), 0x40) & 0xFFFFFF);
```
with
```
    pv = *(u32 *)p;
    pv &= 0xFF000000;
    *(u32 *)p = pv |
                (CAST_NONSTRUCT(u32, *(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)), 0x40) & 0xFFFFFF);
```
and drop the launder.

This is exactly the W47 move. Let me test it.

Also variant C: `pv = 0;` at the end.

Let me score both.
