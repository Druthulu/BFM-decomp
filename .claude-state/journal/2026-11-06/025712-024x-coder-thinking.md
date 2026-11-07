---
ts: 2026-11-06T09:57:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ing2BcNsXAKrk3LU69zK
---
I can write a scratch script that compiles a body and dumps both instruction streams fully. But there might be an easier tool: `.run/P40/T10/hdump.sh` (header pass dumps) and `tools/cc1_dumps_tu.sh`. Those are for cc1 dumps of the TU. For the candidate object, I could use --keep and objdump.

Simplest: write a scratch script `dump.py` under the shard dir that reuses delever_search internals to print both streams side by side fully. Let me check the rest of _score_file to know function names (scorer? mine/tgt).

Actually the --explain path prints full listing. There's a mode at line ~700 printing sites and the opcodes. That's probably `--explain`. Let me look at args.
