---
ts: 2026-11-06T15:39:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5UhDVQN8d8nYvWJkxlT8
---
The comment says: "the two NON-VOLATILE `asm("":"=r"(mb):"0"(mb))` re-ties that keep &D_800AF630 opaque in $s0 so `addiu $a0,$s0,0x18` is re-emitted at BOTH jals". And "a volatile re-tie costs 3 ins".

And the twin is ov_SC06_018:func_8018F060 at src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c:8383. Let me look at the twin — maybe the twin was cracked lever-free? It says "The twin's three hard-won levers are carried verbatim". Let me check the twin's body — maybe it has the same launders, or maybe it has a different lever. Let me look.
