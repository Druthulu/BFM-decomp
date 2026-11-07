---
ts: 2026-11-06T08:36:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1HmQXBvdM48aCU5AgLa9
---
Interesting. In w1 (no keepalives): r72 (a0 param copy, pointer) got a3 with pri 3703. r77 (t3) got a2 with pri 4000. So t3's priority 4000 > a0 copy 3703, so t3 gets a2 and a0 gets a3.

In target (w2, off keepalive kept): let me look.
