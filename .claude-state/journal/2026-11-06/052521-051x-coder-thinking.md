---
ts: 2026-11-06T12:25:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NcTp26o6xppPWeFMmvuF
---
None better than 2. The residual is the lui/ori hoist above the y store.

Idea: make the y store's address/value depend on something so it can't be moved... Actually the problem is the opposite: the constant build (lui/ori) moves ABOVE the y store. To keep the y store earlier, make the lui/ori later: i.e., make the constant be needed later.

What if I write the store as `*((u32 *)(q - 0x10)) = 0x64808080;` but compute the constant from a variable that's assigned right before? o5 did that (same).

What if I swap the ORDER of the two masks so that the store at 149 uses a different construction... 

Alternatively, make the y store not schedulable later: give the y store a dependency on something computed right at that point. `y = D_801BB632 + 1;` then `*(s16 *)(q - 10) = y;`. In target the sh is at 141 immediately after addiu at 140.

In mine, the sh is at 143 — after the lui/ori pair. So the scheduler put 2 independent insns (lui/ori) between the addiu and the sh. Both are ready.

The scheduling priority: the y store's priority vs the lui/ori's. Since the lui/ori feed a store 6 slots later, their chain to the end is long → high priority.

Real-C trick: make the y store's value a memory load... no.

What if I move the y store earlier in C, e.g. right after `y = D_801BB632 + 1;` — it already is.

Hmm. What if I restructure so that the 0x64808080 store happens LATER in C (after the 0x4056 store)? o2 = 4 (worse).

What about a do-while around the y store + the following statements? C0535: a do-while splits the EBB; but sched1 works per EBB, so wrapping the y store in a do{}while(0) would end the EBB before it... The lui/ori are in the block after the y store. If the y store is the LAST insn of its EBB, the lui/ori can't be hoisted above it (different EBB). That's exactly the mechanism that worked in item 1!

Let me try: wrap the y store in a do-while: `do { *(s16 *)(q - 10) = y; } while (0);` — but wait, in item 1 the do-while was around the store that needed to stay BEFORE other insns. Here we need the y store before the lui/ori pair, i.e. the y store must be at the end of its EBB. A do-while creates LOOP_BEG before its body, so the body is a new EBB... The scheduler would then schedule the body (the store) as its own EBB and the following statements as another. The y store would be alone in the loop EBB → placed right where the loop starts, i.e. after the addiu. That should work!

But careful: a do-while adds loop notes → changes flow's ref weights for y, q (loop_depth +1). Risky but let's measure.

Alternative without a loop: `if (1) { ... }` — no, that's fake.

Let me test the do-while around the y store (and maybe around the block of 4 stores).

q1: do-while around the y store only.
q2: do-while around the y store + the next 3 stores.
q3: do-while around the 0x64808080 store (to keep it from hoisting? no, we want the constant build after the y store).

Let me test q1, q2.
