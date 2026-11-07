---
ts: 2026-11-06T09:58:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M76wsLE8S4uX7YM32Ioz
---
Those are different addresses (different overlays have their own functions at 0x8017E8D8 in different banks). Not the same function.

Let me check ov_SC03_096_jr_8017BEBC.c:3646-3680 — that's the "same" overlay family? The comment says ov_SC02_035. Hmm, "ov_SC03_096_jr_8017BEBC" might be a sibling TU with the same function content? Let's look. Actually the comment in our file said "conformed VERBATIM to the TU's existing ones (ov_SC02_035_jr_8017BEBC.c:5139 and :5117)". So there's a TU ov_SC02_035_jr_8017BEBC.c with the same function at a different address? Let me check if it defines func_8017E8D8 with the same body but maybe a different return type. Actually the addresses differ per overlay; the function might be at a different address in that TU.

Let me look at ov_SC02_035_jr_8017BEBC.c around those lines.
