---
ts: 2026-10-22T21:12:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MkRWlHjUmzh23vBC9tp4
---
Key: line 77: "barrier: swap inner arms if(!overshot){store;ret=1;}else ret=0 (no cross-jump)". So cross-jump is defeated by restructuring arms.

For my item: arms 1 and 3 have identical tails. The cross-jump merges the shared tail into one place. To defeat in plain C: change statement order in one arm so the RTL differs but the insns come out the same? Hmm, cross-jump operates on RTL comparing blocks.

Actually, let's look at what the target does vs mine. Let me dump both disassemblies. dt.sh only gives diff. Let me check for a dis script in T11 bin.
