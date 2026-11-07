---
ts: 2026-11-06T10:19:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_idhAzvduo3dapnVeu0qE
---
Still 2. The store sinks regardless. e5 has `__asm__("")` which is a barrier — wait, that would be a lever! And it still scored 2? Interesting, but it's a lever (barrier kind), so not allowed anyway.

e4 (do-while) still 2. Hmm.

So the store position is stubborn. The barrier with "memory" clobber was what fixed it. A plain `__asm__("")` (e5) didn't.

Let me reconsider: the diff is only the store position. Can I reorder the SOURCE so the store naturally lands at 120? The store is at source before func_8012931C. In target asm it's at 120, right before the address setup (which is after func_8012931C and the if). So the target's store at 120 is BEFORE the address setup but AFTER... wait let me look at the full target order around 114-127:
```
114 j
115 li v0,30
116 andi v0,s3,0x3
117 addiu v0,v0,-10
118 sh v0,22(s2)
119 li v0,18
120 sw v0,28(s2)      <- store
121 addiu a0,sp,48
122 addiu s0,sp,56
123 move a1,s0
124 lh v0,52(sp)
125 li a2,1
126 sll v0,v0,0x9
127 jal func_800D20C0
128 sw v0,24(s2)
```
Hmm wait, this is confusing: 115-118 are the else-branch code (m=0x1E, sh 22(s2)), then 119 li v0,18 (m=0x12), 120 sw v0,28(s2). But where's `unk1C = m`? And func_8012931C call? 

Oh, I think I misidentified. The store `sw v0,28(s2)` at 120 with v0=18 is `unk28 = q`? No... Let me look at the source: `((Unkstruct_800B5CB8 *)a0)->unk28 = q;` where q = r2 & 0x803C. If q were 18... possible for a specific input but not statically.

Hmm, maybe `sw v0,28(s2)` is `unk1C = m`? unk1C is at offset 0x1C=28! Yes! 28 = 0x1C. So `sw v0,28(s2)` is `((Unkstruct_800B5CB8 *)a0)->unk1C = m;` (m in v0). And unk28 is at 0x28=40.

So the store that moves is `unk1C = m`, which is right before the barrier in the source! The barrier `__asm__ __volatile__("" ::: "memory")` is after `unk1C = m`. So it stops this store from sinking. That matches the comment.

So the lever-free body needs the `unk1C = m` store to stay before the address setup. sched1 sinks it.

Real-C fix: make `m` or the store feed something. Or restructure so the store is in a block that ends.

The code after:
```
    ((Unkstruct_800B5CB8 *)a0)->unk1C = m;
    CAST_WIDTH(s32, (u8 *)a0, 0x18) = v.vz << 9;
    func_800D20C0(&v, &v2, 1);
```
The store `unk1C = m` then `a0->unk18 = v.vz << 9` then the call. sched1 sinks the unk1C store below the address setup for the call.

What if I reorder: put `CAST_WIDTH(...0x18) = v.vz << 9;` BEFORE `unk1C = m;`? Then the store is after the 0x18 store... target order: 120 sw v0,28(s2) [unk1C=m], 121-123 address setup, 124 lh v0,52(sp) [v.vz], 126 sll, 127 jal, 128 sw v0,24(s2) [unk18]. So target has unk1C store BEFORE the 0x18 store (128) — matches source order.

If I move the unk1C store after the 0x18 store in source, the asm would differ (sw unk18 before sw unk1C). Not target.

Hmm. What if the unk1C store's value m is used later, raising priority? m is used only there.

What about making the store's address computation depend on something? 

Alternatively: the `if (q == 0) unk1C <<= 1;` before it — if the store were merged with that if... 

Let me look at how sched1 orders. The store unk1C=m is sunk 3 insns. What if we add a real dependency: e.g., `((Unkstruct_800B5CB8 *)a0)->unk1C = m;` and then read it back? No.

What about reordering the source so the store comes AFTER the `CAST_WIDTH(...0x18)` line but before the call? Then sched1 might still sink.

Hmm. Let me try: move the store to just before func_800D20C0 but after the 0x18 store? No, code order changes.

Actually, maybe the answer is the ORDER move from cookbook: statement order affects sched1. What if I move the `CAST_WIDTH(...0x18) = v.vz << 9;` line to AFTER func_800D20C0? No, target has it before.

Let me try a couple of reorderings and a do-while around the store with a dependency.

Actually — C0535 says do{}while(0) splits cse1 EBB. e4 used do-while around the store but still 2. Hmm.

What about the "dead-reset cse-breaker" C0414? Not applicable (that's cse).

Let me think about sched1's priority: rank_for_schedule compares INSN_PRIORITY, then... The store unk1C has priority based on its dependence chain. If I make the store depend on the call's argument setup (e.g., store to a0->unk1C where a0 is also used in the call), that's already the case (same pointer). 

What if the store's value m is computed from something used in the address setup? No.

Alternative: use a different store spelling that produces higher priority: e.g., store via a pointer variable `q2 = (s32*)((u8*)a0 + 0x1C); *q2 = m;` — that might schedule differently (the address computation becomes a separate insn with priority). Let me try.

Also try: `((Unkstruct_800B5CB8 *)a0)->unk1C = m;` written as `*(s32 *)((u8 *)a0 + 0x1C) = m;`.

Let me also try making `m` a different type or computing it later.

Given time (~03:40, item 27 min), let me do one more small batch (e8-e12), then record the best (2) as WALL if no crack.

Actually wait — if I can't crack it, best=2 is a WALL. But maybe 2 is close enough to try a bit more. Let me spend 5 more minutes.

Ideas:
e8: store via pointer temp.
e9: store via cast.
e10: reorder the 0x18 store before the unk1C store.
e11: move the unk1C store inside the if/else branches (where m is set) — i.e., store m in each branch. That would put the store in the branch blocks, changing code significantly.
e12: make m used after (e.g., in the later unk1C--).

Actually! The later code: `if (--((Unkstruct_800B5CB8 *)a0)->unk1C == -1)`. This reads unk1C from memory. If instead we used a variable... no.

Let me try e8-e12.
