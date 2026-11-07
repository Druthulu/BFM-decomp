---
ts: 2026-11-06T20:48:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7L8i1mDA1Z8vTHftA8Sr
---
After combine, pseudo 87 is GONE (no references in the combine dump). So combine merged the copy into its uses (or the register was renumbered). Let me check the combine dump for insn 92.

Actually, combine renumbers? No. Let me look at the combine dump around insn 92 (insn numbering may have changed after combine deletes/merges).

Let me look at the .combine dump's early part of our function.
