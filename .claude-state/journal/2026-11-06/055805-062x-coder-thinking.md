---
ts: 2026-11-06T12:58:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6fKQzyP67ycEYMvusk05
---
Key: `if (GET_CODE (i1) == CODE_LABEL) { --minimum; break; }` — a CODE_LABEL in the scan stops the comparison (with minimum decremented). So a label between the two tails DOES stop cross-jump (but reduces the minimum requirement).

In our case, cross-jump is called with minimum=2 (line 1941). If a label appears, minimum becomes 1. Hmm, then it breaks and the comparison stops — so if the matched range is ≥1 insn, the cross-jump still happens.

So adding a label reduces the merge length. Currently mine merges 2 insns (slti; beqz)? Let me see: mine's merge produced a shared beqz, i.e. the merged range is 1 insn (beqz) — the minimum is 2 with a label decrement... Hmm.

If I could place a label so that the merged range would be 0 (< 1), no merge. That means the arms would need to differ in their last insn (the beqz). But they're identical.

Alternatively, note that the `do{}while(0)` creates a CODE_LABEL (the loop end). If I put a do-while in the then-arm, a label appears before the beqz → minimum becomes 1, and if the matched insns are just the beqz (1 insn), the merge still happens (>= minimum 1)? Let me read the rest of find_cross_jump to see how minimum is used.

Let me read further (after the loop).
