---
ts: 2026-11-06T21:04:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eiBF2RGuk6ZeWSWSl1dM
---
Let me look at the RTL around lines 386-397 (relative to 2, i.e., absolute 387-398). This is the case 5 body.

Line 386: `(ashift:SI (subreg:SI (reg/v:HI 76) 0) ...` → reg 76 is idx (HI). Wait, line 239 ashift reg 84, line 386 ashift of reg 76. Hmm the function section includes many lines. Actually the .lreg dump has multiple copies? No, one section.

Hmm, this is the case-5 region? Let me look at absolute lines 380-420.
