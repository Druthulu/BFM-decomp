---
ts: 2026-11-06T20:23:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ceC4D6SDlhyE8ofabwSx
---
Dump works now. Let me compare the .dbr and .sched2 dumps for func_801852B0 between nolau and orig.

Let me extract the function sections and diff. The dbr dump shows reorg's decisions with "delayed branch" notes.

Let me find the section in each and print the relevant part (search for "0xfff8" or the call).
