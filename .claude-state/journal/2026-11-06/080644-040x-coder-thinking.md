---
ts: 2026-11-06T15:06:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UL7dUES5OQxxPbqUiewq
---
C0535: wrap the two statements in do{}while(0) — the block boundary splits cse1's EBB. Note: `do { ... } while (0);` with `// !FAKE: do-while` comment is allowed.

So the move: wrap `s0 = 0; ... a0 = s0 << 10;` in `do { ... } while (0)`? That puts a block boundary at the loop's end. But cse processes the statements inside the do-while in one EBB (no label inside). The label is after the closing brace. Hmm, in C0535 they wrapped the two copies themselves in the do-while so the *whole group* becomes one block and... hmm, the boundary is before and after. The effect was that sched1 keeps birth order.

For our case, cse folds `s0 << 10` because s0=0 is known in the same EBB. Putting the init and the shift in different basic blocks requires a label between them. A do-while(0) wrapping only the init: `do { s0 = 0; } while (0); a0 = s0 << 10;` — the label is between them, but gcc might delete the empty loop entirely (the loop has no side effects except the assignment; the loop body executes once; gcc's jump optimization could collapse it). d4 scored 5, so something happened. Let me check d4's diff.

Actually let's think again: maybe the correct move is different. Since `s0 = 0` is followed by `s2 = (s32)D_8019B538;` (a lui/addiu) and then the shift — all in one EBB. cse folds. To prevent cse from tracking s0's constant, insert a label *between* the init and the shift. A label in C comes from a goto label or a loop. 

Option: 
```
s0 = 0;
if (s1 == 0) goto skip;   // creates a label
skip:
a0 = s0 << 10;
```
But the goto/label may be optimized away. A label that is actually jumped to... The `do{}while(0)` trick works because gcc keeps the label? Apparently in C0535 it emitted 0 bytes, so the label must have been removed by later passes but still affected cse1.

Let me test wrapping init+shift:
```
do { s0 = 0; } while (0);
a0 = s0 << 10;
```
vs
```
s0 = 0;
do { a0 = s0 << 10; } while (0);
```
vs
```
do { s0 = 0; a0 = s0 << 10; } while (0);
```
The last one keeps them in the same EBB inside the do-while → cse still folds? The label is after the shift, so no.

Hmm, C0535's mechanism: "wrap the two copies in do{}while(0) — the block boundary splits cse1's extended basic block, so the copies are not merged/re-ordered there". In their case, the two copies were inside; the split prevented merging with surrounding code.

For us, we need a boundary between the init and the shift. d4 (do{s0=0;}while(0); then shift outside) — the boundary after the init is exactly right, but score 5. Let me see what d4 produced.

Let me dump d4.
