---
ts: 2026-11-06T16:37:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WeB044ycusmFlZEJsE5Z
---
Same as before: 72→a1, 73→a0. So in c1, self (73) = a0 and the copy 72 = a1. The then block uses 73→a0? But the assembly earlier (c1.s) had then using a1. Because regmove/coalescing reassigned? Hmm, c1.s: then uses $5, else uses $4. So the then uses 72 (a1) and else uses 73 (a0). In the cse dump, block1 (then) used 73 and block2 (else) used 73 too... let me recheck. Earlier cse dump showed insn 11 `(set 72 73)`, and then block1 insn 36 uses 73. Hmm, but that was before global-alloc. Global gave 72=a1, 73=a0; then regmove might swap.

Anyway, the target wants self in a1 for both arms. In the pinned version (o1), what are the pseudos? Let's dump o1's greg.
