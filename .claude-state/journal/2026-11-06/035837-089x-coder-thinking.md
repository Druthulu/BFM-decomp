---
ts: 2026-11-06T10:58:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g9j5ThG1QztdXHUP8pxJ
---
Mine: ..., ori, sw196, li v1,16384, lw v0,32, sb, sw180, sh...
Target: ..., ori, sw196, lw v0,32, li v1,16384, sb, sw180, sh...

So the `li v1,16384` and `lw v0,32` are swapped. The li comes before the lw in mine; the target has the lw first.

The target's order: lw32 (a load) then li (an immediate load). sched1 prefers the load first (loads have higher priority / latency).

In mine, the block after the RMW starts with `v1 = 0x4000;` (li) then the unk20 load. sched1 kept the source order.

Hmm, the source order in my w_split: `v1 = 0x4000;` then the unk18 stores (which load unk20). In the target, the lw comes first — because in the orig, `v1 = 0x4000` is BEFORE the barrier, so it's in the previous block! Look at the orig:

```
unk5C = 0x8000;
__asm__("" ::: "memory");
v1 = 0x4000;
t = unkC4;
```
Wait, the barrier is BEFORE v1 = 0x4000 in the orig. So v1 is after the barrier. Hmm.

But the target's final order has li v1 at 35 AFTER the lw32 at 34. So sched1 moved the li after the lw within the same block.

In my w_split, the li is before the lw. Why? Because in my source, `v1 = 0x4000` is right after the RMW and before the unk18 stores. In the orig, v1 = 0x4000 is before the load! So in the orig's block, the li is born early (before the load), and sched1 schedules it late (after the lw32).

In my w_split I moved v1 to after the RMW. Let me instead keep v1 in its original place (before the load) and see: that was w_dw = 7 (v1 got a0). But with the split structure (w_split's do-whiles), maybe v1 in the original position gets the right register and schedule?

Let me build w_split2: same as w_split but with `v1 = 0x4000;` in its original position (before the load), i.e., don't move it.

w_split with v1 before t:
```
do { unk5C = ...; } while(0);
v1 = 0x4000;
t = unkC4;
a = (s32)&D_801907C4;
unk58 = a;
do { unkC4 = t|2; } while(0);
```
Let me test.
