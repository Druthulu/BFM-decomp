---
ts: 2026-10-21T23:37:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jlBHYf6RPnGllmQDFvjH
---
This tool reads gcc dumps. The brief mentions `tools/cc1_dumps_tu.sh + tools/alloc_table.py` (TU dumps). That's the precise approach: dump the TU with gcc 2.7.2 and read the allocation table to see priorities.

But that's a bigger detour. Let me first try simple empirical variants.

Understanding gcc 2.7 global.c priority: allocno_compare uses `floor(log2 refs) * refs / live * 1e4` per the tool docstring! Great — that's the formula.

So priority = floor(log2(refs)) * refs / live_length * 1e4.

Let's compute for candidate c1 (the lever-free version). I need refs and live lengths. Let me compute approximate.

Actually let's just use the alloc_table tool to get exact numbers. But that requires gcc dumps (cc1_dumps_tu.sh). Let's try it — it's the sanctioned path and gives precise data.

Let me look at cc1_dumps_tu.sh usage.
