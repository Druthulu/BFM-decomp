---
ts: 2026-11-06T13:00:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lQbo4ZobSgH0lKVGrO9p
---
p1 = PARTIAL:launder candidate: score 2, 56/56 ins, only the `sw v0,-4(t0)` position differs (mine at 41, target at 39 — a 1-insn reordering).

So with the launder kept, the only residual is the store placement: mine has `sw v0,-4(t0)` 2 insns later than the target.

Target:
```
63d8: andi v0,a2,0xffff
63dc: or v0,a3,v0
63e0: j 63f4
63e4: or v0,v0,t3     ← delay slot
63e8: move a0,zero    ← (the else path)
63ec: andi v0,a2,0xffff
63f0: or v0,a3,v0
63f4: sw v0,-4(t0)
```
Mine:
```
... j ...
or v0,v0,t3
move a0,zero
andi v0,a2,0xffff
or v0,a3,v0
sw v0,-4(t0)   ← at 41 (2 later)
```
Hmm, the diff says mine has the sw at index 41 and target at 39. Let me look at mine's actual asm region. The difference could be a sched1 placement of the `sw` relative to the `j`.

The keepalive `__asm__ __volatile__("" : : "r"(iVar2) : "memory")` was between `*puVar3 = uVar1` (the -4 store?) and the next block. Hmm, in the C the keepalive is after `puVar3[-1] = uVar1;`:

```
puVar3[-1] = uVar1;
__asm__ __volatile__("" : : "r"(iVar2) : "memory");  // keepalive
{ register uint c6b ...; r = ...; *puVar3 = r; }
```
So the keepalive was between the uVar1 store and the r store, and it prevented sched from moving `sw v0,-4(t0)` (the uVar1 store) later.

Removing it: sched1 moved the store 2 insns later. Lever-free alternatives: a do-while(0) around the store? C0535/C0414 style. Let me try:
- q1: `do { puVar3[-1] = uVar1; } while (0);` at the place of the keepalive.
- q2: do-while around the uVar1 computation.
- q3: put the store after a do-while block boundary.

Let me test a few.

Actually, the residual is exactly the kind C0535 fixes: a block split keeps the store's position. Let me try q1 and a couple more.
