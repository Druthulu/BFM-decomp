---
ts: 2026-11-06T21:47:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WYl8Yjap3Bdr9RX3KfBL
---
Interesting: cse runs twice. The RM1 trick relies on the sign-extend surviving cse1/cse2 and combine folding it after. Where does combine run? In 2.7.2, `combine_instructions` is called... let me grep.
