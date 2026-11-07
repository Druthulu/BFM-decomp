---
ts: 2026-11-06T12:26:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_klKpgknShloWJUViwGuv
---
The path taken depends on `mostly_true_jump` (prediction). For `beqz v0` after `lh v0`, prediction is... mostly_true_jump uses branch probability heuristics. If prediction <= 0, it tries fall-through first, then target.

The note said the empty asm made the fall-through head ineligible so it fell back to the taken thread. So without the asm, reorg fills from fall-through.

Options to flip: make the condition's probability say "mostly true"? If the branch is predicted taken (prediction > 0), it tries target first! Interesting: with prediction > 0 the target thread is tried first, and if the fall-through head is eligible but the target thread yields a usable insn, the target wins.

Hmm, but we don't want to change the branch direction in the final code. mostly_true_jump examines the condition: for `beqz` of a register load result, probably neutral. For the if condition written as `if (x != 0)`, the branch is beqz. mostly_true_jump for an EQ/NE against zero uses `mostly_true_jump` heuristics based on REG_BR_PROB? In 2.7.2, mostly_true_jump computes based on condition code and, for comparison with zero, uses `REG_BR_PROB_NOTE`? Let me read mostly_true_jump.

Alternatively: the condition `*(s16 *)(...) != 0` — what if I write it as a comparison that gets reversed, e.g. `if (0 != *(s16 *)...)`? Same.

Let me read mostly_true_jump in reorg.c.
