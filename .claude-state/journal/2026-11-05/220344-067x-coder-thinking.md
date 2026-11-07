---
ts: 2026-11-06T05:03:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rN2hq8Qh6yI5nhmwpTGO
---
In t2, a1 (r73) has refs 10 (up from 7) → pri 6000, above base (r75, 3088). So the do-while added 3 refs to a1 (loop weighting: each of the 3 uses inside a do-while adds +1 ref? refs 7→10).

So the do-while on the stores (3 of them, each using a1 once) added +1 ref each → 10.

In v1 (no do-while), a1 refs=7, pri 2916 < base 3181 → base gets s0 (correct).

So I need the block-split/order effect WITHOUT the loop-weight refs on a1.

Options:
1. Use the do-while around the *if* (r1) instead of the store: r1 wraps the if, which contains `D_80078EA4 = 0xA00000` (no a1). But r1 also gave a1→s0. Let me check r1's alloc: maybe the if's body includes... no a1. Hmm, but the do-while might still add a ref to a1 if a1 is live across the loop? No, loop weighting applies to refs of pseudos used inside the loop. Let me dump r1's alloc to check.

Actually wait, r1 wrapped the ifs at lines 7,14,18 (0-based 6,13,17). The if bodies contain D_80078EA4 stores, no a1. So a1's refs should stay 7. Let me check.

Let me dump r1's alloc.
