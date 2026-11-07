---
ts: 2026-11-06T15:01:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hnf7dL0KAY8XkCPL1fQi
---
a2 (mask 0xFFFF) scores 2 — interesting, it stays 237 ins (combine must prove the mask? or the mask is folded into the or?). Actually `vol & 0xFFFF` then `vol | (0x3000|sx)` and `& 0xFFFF` — combine may fold the two masks into one (the outer `& 0xFFFF`), so zero cost. Score 2, not 0. Let's see the diff for a2.

a1 score 14 (COUNT — instruction count differs? "mine 237 ins, target 237" yet COUNT family... maybe the classify says COUNT due to different mnemonic multiset). Let's get the tail diff.

Let me run dt.sh with a larger tail on a2.
