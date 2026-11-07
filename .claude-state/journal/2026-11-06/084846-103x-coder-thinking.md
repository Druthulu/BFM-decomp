---
ts: 2026-11-06T15:48:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4tW5P2OP2OVOcaiQ02VW
---
WAIT. The a1 cse dump still shows the asm at insn 238! That means a1_tu.c is not a1 — it's the orig TU again (the `ls -td` picked the wrong dir, since the orig --keep run and the a1 --keep run... the a1 run was earlier, then orig ran after → p dir mtime newest = orig). Yes, my earlier command copied orig_tu.c correctly, but this one re-copied from the newest dir which is the orig run.

Let me redo: run --try a1.c --keep, then copy from the printed cand.o's directory.
