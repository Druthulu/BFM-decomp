---
ts: 2026-11-06T21:33:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2bjBHWg9TMyE7ylEsVVS
---
w3 (both gone): the pin removal caused d (arg1) to be allocated to s1 instead of s0, and s1ang (the original s1 user) to s0. Also the prologue order differs (move s1,a1 vs move s0,a1). So the pin $16 forced d into s0; without it, d → s1.

The move needed: d should be in s0 ($16). Without the pin, plain C might allocate d to s0 if... the pin is what forces it. Can real C force d into s0? s0 is callee-saved. d is used across the ratan2 call? d is used in the division later (after the call), so d is live across the ratan2 call → must be callee-saved. Both s0 and s1 are callee-saved. local-alloc/global-alloc picks s1 for d and s0 for s1ang (or vice versa). The target wants d=s0, s1ang=s1.

The func_8012BB3C crack: "do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0)" — i.e., adding refs to the division variable d changes its allocation priority so it takes s0. Let me try that: wrap the div blocks in do-while(0) to boost d's ref count.

The div block:
```
if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; }
else { q = iVar4 / d; if (q == 0) q = -1; }
```
Wrapping each arm in `do { ... } while (0);  // !FAKE: do-while` adds a ref to d? The C0535 mechanism: do-while splits the EBB and adds loop ref weight. Actually, do-while(0) increments the loop_depth for the block, which boosts REG_N_REFS (flow adds refs for loop depth). This raises d's priority → d gets s0.

And "a 2nd do-while on the cast block replaces the keepalive ang anchor" — the keepalive kept the sll order; a do-while around `d = (s16)d;` anchors it.

Let me try:
```
if (iVar4 >= 0) { do { q = iVar4 / d; if (q == 0) q = 1; } while (0); }  // !FAKE: do-while
else { do { q = iVar4 / d; if (q == 0) q = -1; } while (0); }  // !FAKE: do-while
```
and
```
do { d = (s16)d; } while (0);  // !FAKE: do-while
```

Let me build w4 from w3 (both levers gone) with these do-whiles.

Actually, the target's d cast is `sll s0,s0,0x10; sra s0,s0,0x10`. In C, `d = (s16)d;` where d is s32 → sign-extend. GCC emits sll/sra. Good.

Let me write w4.

Also, the prologue order: target:
```
move v0,a0
sw s0,16(sp)
move s0,a1     # d = arg1
sw ra,24(sp)
sw s1,20(sp)
```
Mine (w3):
```
move v0,a0
move s1,a1     # d -> s1
sw ra,24(sp)
sw s0,16(sp)
sw s1,20(sp)
```
So the order of the prologue saves depends on which reg d gets. If d gets s0, the move s0,a1 and sw s0,16(sp) order should match.

Let me try w4 with do-whiles.
