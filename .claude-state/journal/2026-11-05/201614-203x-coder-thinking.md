---
ts: 2026-11-06T03:16:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_62pGTlNnxAyMKBC4srJX
---
q9 uses `d - 0x200 > 0` which compiles to `addiu v0,-512; blez` — different insns. Score 3 because the instruction count matches but the test form differs. Not the target.

q10/q11 use `0x200 < d` or similar. Let me check q10/q11.
