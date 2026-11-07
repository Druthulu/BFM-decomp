---
ts: 2026-11-07T00:52:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gXTSngqUHpHjsR3tuPAW
---
Score 0! MATCH.

Let me install win.c, verify no asm/register, and check the body. Note the `a = 0;` dead reset — is it a "launder"? The brief: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". `a = 0;` is a dead reset (C0414), not an identity statement. It's the exact move banked in the sibling (banked MATCH, 397/397).

Let me verify win.c and record.
