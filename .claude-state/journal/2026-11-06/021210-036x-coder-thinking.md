---
ts: 2026-11-06T09:12:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QQ6cSMQJCChd6OZa0cHM
---
Item 3: pin $10 (ob) + keepalive on mlo (6 refs). This one may be crackable: pin $10 (ob) — ob is a pointer used across the function; keepalive gives mlo extra refs so it wins a register. These are the "global-hardreg-reserve"/"greg-pri-refs" style. Removing pin: ob is a u8* that holds D_800AA60C across the function. Might naturally get s2/something. The keepalive on mlo with 6 refs is a ref-weight lever.

Hmm, these are more plausible MATCH candidates via real-C moves (pointer reuse etc.).

Item 4: ov_SC02_027 func_80180A54 at 4160.
Item 5: ov_SC02_035 func_80183E68 at 7514.

Let me read those.
