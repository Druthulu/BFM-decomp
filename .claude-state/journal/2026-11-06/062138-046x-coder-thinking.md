---
ts: 2026-11-06T13:21:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ptqxrrlcEwyZJv6CTqO6
---
Target: `addiu a0,s3,4` (aa) and `addiu a1,sp,16` (nn) are placed right after the rand() call's move, BEFORE the s0 computation. In mine, addiu a1,sp,16 is at index 114 (5 insns later).

Note: the pins aa($4) and nn($5) mean aa=... and nn=... are assigned to $4/$5, but the compiler emits `addiu a0,s3,4` (a0=$4) and `addiu a1,sp,16` (a1=$5). The pinned vars' uses: func_80015978(aa, (s32*)nn) with aa in a0, nn in a1.

So the barrier keeps sched1 from sinking the a1 setup. Removing it lets sched1 sink addiu a1,sp,16 by 5 insns.

We need a real-C move that keeps it early. Ideas:
- The address `buf` is a local array; `nn = (s32)buf` is a conversion. The addiu is the address computation. With the barrier gone, sched1 sinks it because its use (the call) is far away and it has no deps.
- Real-C: make `nn` used earlier? E.g. compute `nn` as `(s32)(void*)buf`? Same.
- Or introduce a use of nn before the s0 computation that forces the address earlier but emits nothing... e.g., `nn = (s32)buf;` followed by something that uses nn? Any use would add code.
- C0535 do-while around the two statements? The barrier sat between `nn = (s32)buf;` and `s0 &= 0x1F;`. If we wrap the s0 computation in do{}while(0), cse1's EBB splits — but does sched1 still sink addiu a1? The do-while creates a loop note; sched1's EBB boundaries... A block boundary might keep the addiu in the earlier block? Actually sched1 schedules per basic block; if `nn = (s32)buf` is in one block and the s0 computation in another, the addiu can't be sunk past the block end (scheduling doesn't move insns across basic blocks). So a do{}while(0) around the s0 computation could pin the addiu in the earlier block! That's exactly C0535's mechanism (EBB split).

Where exactly? The source order:
```
            s0 = rand();
            t = rand();
            aa = (s32)(q + 1);
            nn = (s32)buf;
            [barrier]
            s0 &= 0x1F;
            ...
            d[2] = s0;
            func_80015978(aa, (s32 *)nn);
```
The target has: rand; move s0,v0; addiu a0,s3,4; addiu a1,sp,16; then the s0 computation; then jal func_80015978; sh s0,28(sp).

So target order: aa, nn computed before the s0 chain. With a do-while around the s0 chain (from `s0 &= 0x1F;` to `d[2] = s0;`), the block boundary would prevent sched1 from sinking addiu a1 into that block (it stays in the previous block). Then the order within the previous block: rand; move; addiu a0; addiu a1 — matching.

But wait, the store `d[2] = s0` must be after the s0 chain; and `func_80015978` after. If the do-while contains only the s0 computation and `d[2]=s0`, then:
```
do {
  s0 &= 0x1F;
  s0 <<= 2;
  t = (t & 0x1F) - 0x50;
  s0 = s0 + t;
  d[2] = s0;
} while (0);
func_80015978(aa, (s32*)nn);
```
Hmm, but a do-while block boundary is between `nn = ...` and the loop body; sched1 sees the block ending after `nn = ...` (the loop head). The addiu a1 is in the earlier block → stays. 

But the loop note might also affect reorg/dbr. Let's test.

Also alternative: put `d[2] = s0;` inside the do-while or outside.

Let me also consider: maybe simply wrapping the s0 computation in do-while is the standard C0535 move. Let me generate several variants:
v01: do-while around s0..d[2].
v02: do-while around s0..s0+t (not the store).
v03: reorder: move `aa`/`nn` after the s0 computation? No, target has them before.
v04: swap `nn` assignment before `aa`.
v05: do-while around just `s0 &= 0x1F` ... 
v06: use `(s32)(void *)buf` or `(s32)&buf[0]`.
v07: compute nn earlier via a temp? 
v08: do-while around the whole rand block?

Let me look at the mine listing to see exactly where the addiu went.

Mine: addiu a1,sp,16 at index 114 vs target 109. So mine has it 5 insns later. Let me see mine's region.
