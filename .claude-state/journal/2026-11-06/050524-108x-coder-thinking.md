---
ts: 2026-11-06T12:05:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bvQkqZPvfGyGTjh7QF15
---
Worse. The store sink is unfixable.

It's 05:05. Item 4 started ~04:56. 9 min. I need ~20 min. Let me continue a bit more, then write up.

Let me reconsider the problem once more. The best is score 2 with v_s8_dw_two. The only residual is the li a0/store swap. The sibling (func_801810E4) confirmed this is a sched-store-sink wall.

Let me try a few more genuinely different things:
1. What if the `s8 two` + do-while is combined with a different tail structure that changes sched priority? E.g., declare the tail stores as locals with init-at-decl.
2. What if I use a `for` loop for the v computation?

Actually, let me look at the mine disassembly of v_s8_dw_two to see the exact tail and think about sched priority. Let me dump it.

Actually, I know the tail: mine has li a0 at 29, sw 0x10 at 30. The target has sw at 29, li at 30.

Let me think about sched1 vs sched2. The li a0=2432 is a constant load (needed for the call). sched2 runs after reload. The store sw v0,16(s0) uses v0 (live). Both ready. sched picks by priority. 

Maybe the issue is the RTL order: the store's RTL is in the middle block, the li's RTL in the tail. sched1 (which works on EBBs) sees them in one EBB and reorders. If they were in separate EBBs (separated by a basic block boundary), sched1 wouldn't reorder across. A basic block boundary is created by a label/jump. The do-while around the store/tail didn't create a boundary at the right place.

What if I put the final call in a separate block via an `if`? E.g.:
```
    if (a0 != 0) { func_8002D4C8(0x980, 0); }
```
This adds a branch (a0 is the param, non-null but the compiler doesn't know). Adds a compare/branch — extra insns. Bad.

What if the tail is in an `else` of a false condition? Adds branch.

Hmm.

Let me try: a `goto` that creates a label right after the store, splitting the EBB:
```
    CAST_WIDTH(0x10) = v;
    goto after;
after:
    unk14 = ...;
```
The `goto after; after:` is a no-op jump, likely deleted. But if it survives, it creates a label that sched1 respects. Let me test.

Actually, the jump_optimize would delete `goto after; after:`. But maybe a forward goto over a statement survives? Let me try:
```
    CAST_WIDTH(0x10) = v;
    goto tail;
    tail:
    unk14 = ...;
```
Hmm, no-op.

What if I use a `do { } while (0)` with the store inside, and the tail after? Tested.

Let me try the goto-label idea and a `switch(0)`.

Actually, let me just accept the wall. I've done ~40 tries and the sibling confirms. Let me spend the remaining time writing up item 4 and the final log. The writeup will bring the clock to ~05:12-05:15.

Let me do 2 final tries (goto-label) and then write up.

Let me test v_goto_label:
```
        CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;
        goto tail;
    }
tail:
    unk14 = ...
```
Wait, the goto would be inside the block; the label outside. Let me structure:
```
    {
        s32 v;
        ...
        CAST_WIDTH(0x10) = v;
    }
tail:
    unk14 = ...;
```
No goto. Hmm.

Let me try:
```
        CAST_WIDTH(0x10) = v;
        goto after_store;
    }
after_store:
    ...
```
The goto jumps out of the block to a label right after. This creates a label. jump_optimize might delete the jump+label if trivial. Let me test.

Let me just do it.

Actually, I'll do the goto test and then finalize regardless.
