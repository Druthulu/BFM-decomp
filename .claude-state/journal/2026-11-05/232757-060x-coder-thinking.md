---
ts: 2026-11-06T06:27:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HJ5TVRdJqrYBCbq3RsGg
---
Both dumps have the same RTL for insns 40-53 (these are from an earlier function in the TU). I need the RTL of func_801834A4 itself, which starts at line 7817 in both. Let me grep within the section after 7817 for insn 43, 45, 47.

Let me extract the RTL of the function from both dumps and compare the relevant insns.
