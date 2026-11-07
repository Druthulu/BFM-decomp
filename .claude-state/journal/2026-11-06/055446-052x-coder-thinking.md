---
ts: 2026-11-06T12:54:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2lH7h1acI4VhCqnuYt29
---
`birthing_insn_p`: a SET to a REG that is live at block entry and has exactly one set in the function → birth. So the constant's pseudo: `lui v1` sets v1 (or a pseudo). If the pseudo is live at block entry (bb_live_regs) and has reg_n_sets == 1, it's a birth. The constant temp has one set → birth → boosted.

If the pseudo had TWO sets (e.g., assigned in both arms), reg_n_sets != 1 → not a birth → no boost. Interesting!

But the constant is a fresh pseudo with one set.

Alternatively, if the pseudo were NOT live at block entry... it IS live at entry only if used later? bb_live_regs = registers live at the *start* of the block. The constant pseudo is born in the block, so it's not live at entry → `bb_live_regs & bit` = 0 → returns 0 → NOT a birth → no boost!

Hmm, so the lui (setting the constant pseudo) shouldn't be boosted at all. Unless the pseudo is a *hard* register: after reload... but sched1 is before reload, so pseudos.

Hmm, so which insn gets boosted? Let's reconsider. The lui/ori set a pseudo. If the pseudo is not live at block entry → not birthing → no boost.

Then why does the lui/ori hoist above the sh? Because of priority: with all-1 priorities, order = ready list order. Hmm.

Wait, maybe the boost goes the other way: the sh's *predecessor*... no.

Let me look at this differently — empirically test whether the sh would move if the constant pair were absent. Not helpful.

Let me try a few more real-C variants quickly, then decide on a wall.

Variant idea: make the constant pseudo have 2 sets (so no birth boost and different allocation): e.g.
```
u32 m64;
if (j) m64 = 0x64808080; else m64 = 0x64808080;
```
That's silly. But we could write it as part of the loop: `m64 = 0x64808080;` in the decls area... no, j is the loop var; the block executes twice.

Hmm, what about: since the join block runs twice (loop), a variable assigned in the block has 2 dynamic sets but reg_n_sets counts static sets = 1.

Another idea: `eight` is s16 and used twice. Not relevant.

Let me try the "constant temp" variants properly (declare at the top of the block, assign at different points):
q1: `u32 m64;` decl; `m64 = 0x64808080;` right after the y store; store uses m64.
q2: assignment before the y store.
q3: assignment in both arms (so 2 static sets → no birth).

Let me also try:
q4: wrap `sh y` and `C64 store` in one do-while.

Let me write these.

Time: I'm at ~25 min on item 2. Budget 20-30 min per item; past 30 min → stop and record a wall, but a WALL needs ≥20 min and ≥30 scored tries. I have ~22 scored tries. I need ≥30. So let me run ~10 more.

Let me generate 10 variants in one batch.
