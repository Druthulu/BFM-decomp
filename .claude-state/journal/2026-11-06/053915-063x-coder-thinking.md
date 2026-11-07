---
ts: 2026-11-06T12:39:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JOnaeHhsKniBcSGECNoS
---
In c2: `li a0,7; j; sw v0,216(s1)` — the store went into the j's delay slot, and li a0,7 before the j. In target: `sw v0,216(s1); j; li v0,7`.

So the difference: which of {li, sw} goes in the j delay slot. The order in the RTL is li then sw (that's why the conflict). If the RTL order were sw then li, the li would be in the delay slot and ret could be v0 (no conflict).

So I need the RTL order: store v0 (call result) BEFORE the ret=7 def.

In the C: `unkD8 = call(...); ret = 7;`. The RTL order should already be store then li... but the dump showed li (insn 127) before sw (insn 124). Because the store insn 124 has a lower number but was placed after 127. Hmm, that means during expansion, the store insn 124 was emitted BEFORE 127 but the instruction *stream* order got changed by something before lreg (cse/combine/loop). 

Hmm, `(insn_list 120)` on 124 — insn 120 is the call. And 127 has `(insn_list:REG_DEP_ANTI 120)`. REG_DEP_ANTI is set by sched.c... but sched1 runs after local-alloc? Hmm no — actually in 2.7.2, `sched` (sched1) runs BEFORE local-alloc? Let me check toplev.c order.

Actually, in gcc 2.7.2 toplev.c rest_of_compilation:
```
  if (optimize) ... 
  /* Cross-jumping */
  jump_optimize
  ...
  if (optimize > 0) { ... }
  ...
  local_alloc ();
  ...
  global_alloc ();
  ...
  if (optimize > 0 && !flag_no_schedule) sched (insn) ...
```
Hmm, but the REG_DEP_ANTI notes in the lreg dump suggest sched already ran (sched1 before local-alloc?). Let me check toplev.c.
