---
ts: 2026-11-06T05:45:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R1bxpZJXHkOKLhR2brhD
---
`invalidate_memory` removes a memory entry if:
- all, OR
- (nonscalar && p->in_struct), OR
- `cse_rtx_addr_varies_p(p->exp)`.

`p->exp` for the `*q` load is `(mem:HI (reg q))`. `cse_rtx_addr_varies_p` — let me check: it likely returns true if the address contains a register that is not a constant. Since q is a pseudo whose value is the address of D_800B9A02 (a constant via REG_EQUAL?), the address might not "vary".

Let me read cse_rtx_addr_varies_p.
