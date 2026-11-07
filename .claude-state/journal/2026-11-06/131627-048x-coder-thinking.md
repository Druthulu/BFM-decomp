---
ts: 2026-11-06T20:16:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0YTb4JYUCq4PydqyWNPk
---
Target tail: 
- lhu a0,0(a2) [bidx]
- lw v1,0(s1) [pv = *p] — in the load delay slot of lhu
- sll/addu/sll, lui at, addu at, lw v0,0(at) [ot]
- lui a0,0xff00
- lw v0,0x40(v0)
- and v1,v1,a0 [pv & 0xFF000000]
- and v0,v0,a3 [ot->unk40 & 0xFFFFFF]
- or v1,v1,v0
- sw v1,0(s1)
- lhu v1,0(a2) [2nd bidx]
- ... recompute ot ...
- lw v0,0x40(v1)
- and s1,s1,a3 [p & 0xFFFFFF]
- and v0,v0,a0
- or v0,v0,s1
- sw v0,0x40(v1)
- lhu v0,0(a2) [3rd bidx]
- ...

Interesting: the target uses v1 for pv's load, and v1 is reused later. And the target's first half: `and v1,v1,a0` where v1 = pv, a0 = 0xff00<<16 = 0xFF000000. Then `sw v1,0(s1)`.

Note: the target has NO `lw v1,0(s1)` in a delay slot issue; the key point from the notes: "The tail's `lw $v1,0($s1)` (`*(u32 *)p`) belongs in the load-delay slot of `lhu $a0,0($a2)`; ours landed 7 insns later with `lui $a0,0xff00` taking the slot."

So without the launder, the pv load lands 7 insns later and `lui a0,0xff00` takes the delay slot.

Let me first score the lever-free baseline (launder removed, pins kept) and see the residual.

Remove the final line `__asm__ __volatile__("" : "=r"(pv));`.
