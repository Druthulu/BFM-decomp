---
ts: 2026-11-06T11:34:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RvftxeSlYehbMtZEiYyY
---
The baseline is build/'s object. So target asm = disassembly of the function in build/<obj>. I can get it via objdump on the baseline path. Let me find the baseline path resolution.

Simpler: write a script under my shard dir that:
1. Runs --try --keep to get cand.o, disassembles fn.
2. Finds the baseline obj and disassembles fn.

But how to get baseline path? Let me look at oracle.baseline_path.
