---
ts: 2026-11-06T22:41:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F0PN6H9DrvMqb9Os8i4J
---
`set_preference(reg, SET_SRC(setter))`: when a pseudo is set from a hard reg (e.g., `d = arg1` → `r74 = $a1`), the preference for $a1 is set on r74. Then `expand_preferences` propagates preferences between allocnos connected by copies? Let me look at expand_preferences (line 781).

But how does r78 (iVar4) get the a1 preference? Maybe through `expand_preferences`: r74 (d) prefers $a1; r74 and r78 are "copy-connected"? No, they're not copies.

Hmm, let me read expand_preferences.
