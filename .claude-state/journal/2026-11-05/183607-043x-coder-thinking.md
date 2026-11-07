---
ts: 2026-11-06T01:36:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5nOcl58r6Z6s4lPZLEqa
---
emit_jump(label) — creates a jump insn to the label. So a `return;` should emit a jump. But expand_null_return_1 might not be called for the terminal return if the parser elides it. Let's check expand_null_return: it has the logic around last_insn. Lines 2481-2545.
