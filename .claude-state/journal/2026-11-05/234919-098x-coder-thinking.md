---
ts: 2026-11-06T06:49:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ffdWK7aBHfvLMBufE7ym
---
m1 (no pins, no launders, do-while) = 72. Worse than the 54 of the plain lever-free body? Hmm, that's odd — with the do-while the score went UP from 54 to 72.

Hmm, wait: win.c (no pins, no launders) = 54; m1 (same + do-while) = 72. So the do-while hurts when the pins are gone.

Let me check: maybe with the pins removed, the constant `li`s get rematerialized differently.

OK. So:
- Full lever-free: best 45 (v_w3: var_a0 direct stores) or 54.
- Pins kept + launders → do-while: score 0 → PARTIAL:pin.

That's a solid PARTIAL for item 4.

Can I get a full MATCH? The blocker is the pins: they force k50/kF0/k100 into $18/$19/$20 and var_t7 into $3, which shapes the whole allocation.

Given time (item 4 at ~25 min), let me do 2-3 quick attempts at a full MATCH, then finalize with PARTIAL.

Idea: the constants k50/kF0/k100 in the target are callee-saved ($18,$19,$20) — they're live across the func_80017738 calls. In my lever-free body, are they in callee-saved regs? If they're rematerialized as `li` before each use, that's the structural difference.

Let me check the target: `li $20,-80; li $18,-240; li $19,-256` appear ONCE at the top, then `sh $20,40($sp)` etc. multiple times → yes, they're held in registers across the block.

In my body, if the constants are also held (162 insns ≈ target 163), they are.

The difference is which registers and the v0/v1 choices.

Let me try combining the do-while with the var_a0-direct-store variant (v_w3) — maybe.

Actually, let me look at what changes with the pins removed more concretely. I'll compare the alloc order: with pins, the constants are hard regs; without, they're pseudos competing.

Time. Let me do a final quick batch: v_w3 + do-while, and a couple of declaration/order permutations, then finalize.

Actually, let me think about which is more valuable: a MATCH (kinds gone) vs PARTIAL. A MATCH requires the pins gone. Given ~30 min spent and the clear mechanism (4 hard-reg reservations shaping a 163-insn function), the probability is low.

Let me do one last batch of 6 combos and then finalize.
