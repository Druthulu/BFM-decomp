---
ts: 2026-11-06T08:56:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_54ZiytVW4Sa9JhCHkAKo
---
The shift is already present at index ~119: target[119] is `nop` while mine[119] is `move a3,v1`. So the 5 extra insns are earlier. Let me find the first difference by diffing the two listings.
