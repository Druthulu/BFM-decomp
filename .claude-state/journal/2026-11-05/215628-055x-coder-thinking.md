---
ts: 2026-11-06T04:56:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tPxjBbx3WGzjM6v9Nemy
---
Interesting: in cse2, insn 64 is `(set (reg:SI 4 a0) ...)` before the call — let me see its source. And insn 57 loads `(mem:SI (symbol_ref D_80127524))` into reg 84 (for the sh base), while insn 64 sets a0 for the call — what's the source? Let me look at lines around insn 57-66.
