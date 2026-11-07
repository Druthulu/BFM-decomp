---
ts: 2026-11-06T13:34:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AQV2MEGIPwm8E2astbwz
---
So after cse2: thread_jumps, flow_analysis, combine_instructions, then sched1.

`flow_analysis` includes dead code elimination? flow.c's `flow_analysis` computes life info; `delete_dead_from_cse` is separate. Hmm, but flow_analysis can delete insns? It computes; `combine_instructions` can delete insns (dead code elimination in combine: "if the result is unused, delete").

The no-op `a1 = a1` (312): combine would see it as a no-op and delete it, or the preceding 291 becomes dead? combine's `try_combine`/`subst` might merge 291 into 312's position.

Actually the most likely: combine_instructions processes the no-op `a1=a1` with REG_EQUAL fp+16; combine replaces it with `a1 = fp+16` and then the earlier 291 is dead (dead code elimination in combine deletes insns with unused results). Then the addiu lands at the later position. That's the nobar behavior.

In orig, the asm at 293 between them blocks combine: combine only combines adjacent insns (or within a "basic block" up to a few insns). The asm between 291 and 312 prevents combining them, so 291 survives early.

So: we need a real-C construct between `nn = (s32)buf;` and the s0 chain that stops combine from folding the no-op into the call site. A real instruction that combine won't look past. Any instruction there would do — but it must be zero-byte or part of the code.

Wait: what if we simply reorder the source so the no-op move at the call site doesn't exist? The no-op arises because the pinned variable's value is copied to the hard reg at the call site by cse's canon_reg. Hmm.

Alternatively: make the *chain* insns sit between the real addiu and the call — they do. Combine only combines within a few insns; the chain is 5 insns. Combine works on a sliding window of 3 insns typically. So how does it fold the no-op at 312 into 291, 20 insns earlier? It doesn't; the folding happens in cse2 (which has a global table).

OK, let me test the hypothesis differently: in nobar, which pass changed 291→310? Let me look at the flow dump (after flow_analysis) for insn 291. If 291 is gone in the flow dump, cse2 or thread_jumps did it.

Let me check nobar.i.flow for "(insn 291".
