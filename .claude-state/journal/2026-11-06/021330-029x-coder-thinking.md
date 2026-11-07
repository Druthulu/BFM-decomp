---
ts: 2026-11-06T09:13:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PCR5TqVKo94esR53OIAI
---
Removing all three keepalives gives a diff around the bVar1/&0x10 test and the fc area. The differences are register allocation: target uses v1 for the `(bVar1 & 0x10)` andi, and for the fc/limit values uses v1/a1, mine uses t0/v0/a1.

Let me get the full diff. dt.sh tail 20 cut it. Let me get more lines and see the whole score line.

Actually the key: keepalive 1 forces bVar1 live in $8. Keepalive 3 forces fc. Let me remove them one at a time to see which diff each causes.

Let me make candidates: rm1 (remove only first), rm2, rm3.
