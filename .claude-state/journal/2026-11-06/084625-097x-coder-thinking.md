---
ts: 2026-11-06T15:46:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jamea8bmT0Entxf8PKLI
---
Target: `lui s0,0x0; addiu s0,s0,0` (the base &D_800AF630 in s0), then `jal; addiu a0,s0,24` twice. So the base is in s0, and each call computes +24.

Mine: let me look at the same region.
