---
ts: 2026-11-06T13:09:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YkEumYFRJP4YAqNtmzJk
---
Now item 5: func_8018046C in src/ov_SC02_000/ov_SC02_000_jr_8017FCB0.c line 3078.

Also note moves.md line 105 has: `pin | func_8018046C | MATCH — split reused const var (0x325 loop, then 0x65 loop) into two vars...` — that's a different function? It says func_8018046C, so the same function! Interesting — a previous shard matched it by splitting a reused const var. That was about a pin. Let me read the function.
