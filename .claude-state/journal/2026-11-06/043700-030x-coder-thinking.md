---
ts: 2026-11-06T11:37:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_e7JIKNffhZr7QbF5i2RW
---
Interesting. A do{}while(0) around statements creates a block boundary that splits cse1's EBB. But does it split sched1's EBB? The note says it splits cse1's EBB so sched1 sees them in birth order — hmm, actually sched1 EBBs are formed from CFG basic blocks, and a do-while(0) with a constant condition may leave a NOTE? Actually cse1 processes extended basic blocks; the do-while creates a LABEL and conditional jump that jump-optimization removes, but cse1's EBB splitting happens before jump opt. Hmm, and sched1 also forms EBBs similarly (sched1 runs on basic blocks with `NOTE_INSN_BASIC_BLOCK`?). gcc 2.7 sched.c: scheduling is done per basic block, with `sched_analyze` across? Actually sched1 in 2.7.2 schedules "extended basic blocks" too? There's `sched_init` and it processes insns from `NOTE_INSN_BASIC_BLOCK`... Let me not dig; try it.

For our case: wrap the early store group in do{...}while(0) to split the EBB before the tag2 load? The boundary needs to be where the barrier was. Two barriers → two do-while blocks.

Let me try: put `do { ... } while (0);  // !FAKE: do-while` around the group from `p += 8;` to the vx/vy stores (up to before tag2 load). And another around tag2=0xE1000200 + ot store? Let's first try wrapping the second group.

Actually target EBB1 = statements from p += 8 through vx/vy stores. The barrier at 2465 splits before tag2 load. The second barrier at 2478 splits before tag2 = 0xE1000200.

If do-while splits like a barrier, we need two do-whiles:
```
do {
  p += 8; p[3]=8; vx=x; p[7]=0x38; vy=y; ... vx/vy stores;
} while(0);
tag2 = *p; x += w_; ...; pmask; *p = ...;
do {
  tag2 = 0xE1000200;
  ot->unk3FFC = ...;
} while(0);
p += 0x24; ...
```
But wait, target's third group starts at the tag2 const. Mine already matches the tail? mine 38d4..: after sw a0,0(v0) mine has `and a0,v0,a1` (pmask) then lw v1, 38dc addiu v0,36, ... and 3c06e100 lui a2 at 38c4 (before the sw!). In mine the tag2=0xE1000200 lui is at 38c4, before the sw 0(v0) at 38d0. Target has lui a2 at 38d8 after sw 0. So yes the third barrier matters too.

But careful: the do-while is a real C construct allowed with the marker. The brief says "`do{}while(0)` only with `// !FAKE: do-while`". OK.

But note C0535 warns it splits cse1's EBB. Good.

Let me create v1 with do-while blocks and score.

Wait — but do-while(0) might introduce a branch that's optimized away, or it might affect the CFG (a loop). Actually `do { ... } while (0);` is a loop with a constant false condition; jump optimization removes it. But NOTE_INSN_LOOP_BEG notes... In the moves.md, func_801835B0 MATCH "goto loop: no LOOP notes, -1 not hoisted". Hmm, do-while could create LOOP notes affecting loop.c. But for our function there's no loop hoisting concern.

Let me try.
