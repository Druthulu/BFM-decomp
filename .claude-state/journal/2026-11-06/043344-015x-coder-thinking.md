---
ts: 2026-11-06T11:33:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RqZY1MKAuFTJ5Yiq4BDk
---
Baseline lever-free: 23, 72 ins vs 71. Let's look at the full diff to understand.

Actually from the tail above, differences:
- mine has an extra `move s1,a1` after beq? Actually target has `move s1,a1` where mine has nothing at insn 21. Wait: "replace mine[20:21] target[20:22]: 20 beq v1,v0 | beq; 21 -- | move s1,a1". Hmm.

Wait that's odd: target has move s1,a1 and mine doesn't? Let me see full diff. Let me dump the diff to a file and read it.

Let me use --explain maybe. Actually dt.sh with tail big enough. Let me run with tail 200 and pipe to file under item dir.
