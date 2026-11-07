---
ts: 2026-11-06T14:57:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lybseJAt1nJN0sZPJEaL
---
Still 4/5. I've now done 30 scored tries (27 + 3). Time ~09:50, ~55 min on this item — well over the 30 min budget.

Let me record the WALL for func_8017EB30:
- result: WALL
- best: 4
- tries: 30
- wall: the fold is in the post-reload jump pass (jump2). Tag: `flow-known-value` is the existing tag (from walls.txt) — "a redundant test on a known value is folded away; target keeps it". That's exactly this. But the pass is jump2 (post-reload), not flow. The walls.txt tag `flow-known-value` says "flow/jump". Let me use `flow-known-value` (existing tag) since it matches. Or a new `jump2-known-value`. The brief says "a tag from walls.txt or a new `<pass>-<what>`". Let me use `jump2-known-value` for precision, noting the existing `flow-known-value` class.

Actually, the moves.md entry for func_801850B4 uses `flow-known-value`. Let me use the same tag for consistency, since it's the same class. Hmm, but the mechanism here is jump2 (post-reload), not flow. Let me use `flow-known-value` and note "jump2". Actually, let me create `jump2-known-value` to be precise about the pass. The brief allows a new `<pass>-<what>`.

Let me verify the pass is jump2: the fold appears in the .jump2 dump (post-reload jump_optimize). Yes.

Evidence (≤140 chars): "post-reload jump2 folds `bne t,3` to `j L73` (t==5 on the fall-through of `bne t,5`); the launder asm is the only barrier; real C cannot keep it (30 tries, best 4)".

Let me count: ~150. Trim: "jump2 folds `bne t,3` to `j` (t==5 on the bne t,5 fall-through); the launder asm is the only barrier; real C can't keep it (30 tries, best 4)" ~135.

Let me write the results row, notes, and moves.md line.

First, let me set win.c = c1 (best lever-free body, score 4).

Let me also clean up the dumps (_d7, _dc1_7, _tu, and the txt files).

Let me write the row.
