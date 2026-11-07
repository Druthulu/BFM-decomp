---
ts: 2026-11-06T01:35:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XJhi4z2TB19LIbHZbeZO
---
MIPS defines HAVE_return? If so, a plain `return;` emits a `return` insn (jr ra + delay), not a jump to the epilogue. But the function's epilogue is shared: all the earlier `return;` compile to `j 180c` not `jr ra`. So HAVE_return must be false for this target (or the epilogue needed). Indeed target returns all `j 180c`.

So expand_null_return_1 calls expand_goto_internal(NULL, end_label, last_insn). Now expand_goto_internal has an optimization: if the goto is to the label that is next... Let me look. Also note `last_insn` parameter: it's used for the "jump to next" elision when the label is immediately after. Let me read expand_goto_internal.
