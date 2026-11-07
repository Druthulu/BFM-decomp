---
ts: 2026-11-06T10:03:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wfeuJ0gNxGpNeaTNeVa0
---
The .greg dump is the RTL after global-alloc. The allocno table I got is from parsing `Register N used ...` lines in the .lreg (which are actually global-alloc's? confusing).

The alloc_table output gave "conflicts v0,a0,sp" and "prefers" — it parses the .greg dump's ";; Register dispositions" and other lines? Let me read the rest of alloc_table.py to know where "conflicts" and "prefers" come from.
