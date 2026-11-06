---
ts: 2026-10-22T21:53:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AgCfdoTcOx2OuIdkWWHJ
---
Same issue. Time to WALL item 4 at 28-30 tries. Let me run 3 more quick ones to reach 30+ and be safe, then record.

Actually I have 28 scored tries. Let me run 3 more cheap variants (n1-n3) and then record the WALL.

n1: move the whole store block after the `D_80126962/6A` pair (m5 = 15, similar).
n2: `*(s16 *)&D_80126970 = -0x60;` first with `D_80126976` second (m2 = 15).
n3: interleave with the -0x80 group: 76, 7A, 70, 74.
n4: the -0x60 group after the -0x80 group with the values in variables.

Let me just do 3 and count 31.
