---
ts: 2026-11-06T09:56:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PGZKcs2CXR0wwcT0VHWQ
---
Score printed is the tail of the diff. dt.sh tails last N lines; the score line is at the beginning of output. Let me use tail larger or capture the score. Let me run with tail 200 and grep "score". Actually dt.sh output: `src/800.c:func_80023BF0: score N (...)`. The tail -N keeps the last N lines, so score line is lost. Use tail big enough, or just run and grep. Let me modify: run dt.sh with large tail then grep. Actually simpler: run dt.sh and pipe to grep score? dt.sh itself pipes to tail -N. I can call with tail 400 and grep.

Let me do that.
