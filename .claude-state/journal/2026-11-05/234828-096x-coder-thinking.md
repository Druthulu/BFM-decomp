---
ts: 2026-11-06T06:48:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CLJrasKXemEwsTjhoStB
---
With the pins kept and the launders removed, the only difference is the ORDER: the target places the four `li` (and `move a0,zero`) BEFORE the `#APP` (i.e., before the store block), while mine places them after.

In the target, the launder asm (4 empty asms) acts as a scheduling barrier: the `li`s are emitted before the asm block, and sched1 can't move them past the asm.

Without the asm, sched1 sinks the `li`s down to just before their first use (the sh stores).

So the launders here are a scheduler barrier: they keep the `li` constants at the top of the block.

Plain C equivalent: what makes sched1 keep the `li`s early? sched1's birth boost / priority. Hmm.

The four `li`s in the target are at insn 53-57, before `move $2,$fp` etc.

In mine, they're at 64-67, after the sb stores and before the sh stores.

How to make them early in plain C? Options:
- Move the assignments earlier in the source (they ARE earlier: k40=-0x40 etc. are before the store block). sched1 sinks them because they're single-use constants.
- The known wall: "sched1-birth-boost" / "sched1-const-sink".

Since the `li`s are constants with a short life, sched1 gives them low priority and sinks them.

What if the constants are used across the calls (later in the function)? They are (sp10.w[4] = k40 later too).

Hmm, in the target, the li's are all born right after the third bgez block, before the `#APP`. In mine they're after the sb stores.

What could anchor them? A real C second set? No.

Options to try:
1. Reorder the source so the k assignments come *after* the var_a0 computation but before the stores — they already do.
2. Make the constants part of a compound expression evaluated early.

Hmm, what about making the k variables used in a statement before the store block? E.g., `sp10.w[4] = k40;` is the first use.

Honestly, the ordering here is a scheduler decision.

Time: item 4 at ~20 min, ~42 tries. Let me try a few quick variants on p_nolaunder (pins kept):
- reorder the k assignments vs the var_a0 block
- move the k assignments before the three computations
- interleave

Let me try ~6 variants. If one gives 0 → PARTIAL:pin. Otherwise record the WALL.

Actually — wait. Since with the pins kept the only issue is ORDER, and the wall tag would be "sched1-birth-order"... Let me try the documented C0535 move: do-while(0) to split the EBB and change scheduling. E.g., wrap the k assignments in `do { k40 = -0x40; ... } while (0);`? That splits the EBB (a block boundary) — sched1 then can't sink them past the block boundary? Actually a do-while(0) creates a NOTE_INSN_LOOP_BEG... no, it creates a block boundary. The move "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item".

Let me try: `do { k40 = -0x40; k50 = -0x50; kF0 = -0xF0; k100 = -0x100; } while (0); // !FAKE: do-while`.

Hmm, but do-while(0) with a body creates a jump structure that jump.c optimizes away, leaving block boundaries.

Let me try that on p_nolaunder.
