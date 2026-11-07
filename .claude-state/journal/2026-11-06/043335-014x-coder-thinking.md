---
ts: 2026-11-06T11:33:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_grGHgtMJzvEz95gRLVbF
---
The score is printed as the first line. tail -2 shows diff tail. The script: `| tail -${3:-2}`. Hmm so tail shows the LAST lines, which is the diff, not the score. I should use grep or --explain. Let me use sc.sh which greps the score line.

Actually sc.sh prints score per file. Let's use it.
