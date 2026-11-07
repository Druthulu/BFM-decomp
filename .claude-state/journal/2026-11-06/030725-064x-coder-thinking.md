---
ts: 2026-11-06T10:07:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zz6II9GDCYtjgwFe8ffe
---
At 2183: for a CALL_INSN, instructions using hard registers that may be clobbered depend on the call. But memory? Let me look further for memory handling in sched_analyze_insn. Let me grep for "mem" in sched.c around the call handling.

Actually, the key: in gcc 2.7.2 sched1, memory references are tracked via `true_dependence`/`anti_dependence` only within `sched_analyze_insn` for MEM insns, and a CALL_INSN... let me check if a call adds a memory clobber dependency. Line 2044: CALL_INSN_FUNCTION_USAGE. Line 2125: call/jump dependency chain.

Let me look at the whole sched_analyze_insn for how memory is handled, specifically `sched_analyze_1`/`sched_analyze_2` for MEM.

This is a rabbit hole. Let me take a pragmatic approach: test v2 (load after call) already scored 32 — worse. So the load-before-call is right.

Let me think about the local-alloc problem from the "copy preference" angle. Actually, maybe I can make s1ang NOT be a separate local qty by making it a *global* qty — by using it in a later block. Let me try: use s1ang in the division computation, e.g., `q = iVar4 / d;` → `q = (iVar4 + (s1ang & 0x3FF) * 0) / d;`? That changes code.

Alternatively: declare `s1ang` as a variable that is used in the `if (iVar4 > 0x800)` blocks. But that adds code.

Hmm.

Let me reconsider the problem from the "keepalive" comment: "scheduling barrier: anchor u5 before the (s16)d cast". So the keepalive is needed for scheduling (u5's addiu/andi before the sll/sra). And the pin is needed for the register.

So the C-level solution must (a) put u5 before d's sign extension, and (b) flip the register.

For (a), maybe a statement-order change suffices: e.g., compute u6 before d=(s16)d? In the source, `u5 = ...; d = (s16)d; u6 = s1ang & 0xFFF;`. The target order: u5 compute (addiu+andi), then sll (d), then andi (u6). So the target order is u5, d, u6 — same as source. Without the keepalive, sched1 reorders. Hmm.

Wait, actually the keepalive on u5 forces u5 to be "used" right there, anchoring it. Maybe moving `u6 = s1ang & 0xFFF;` BEFORE `d = (s16)d;` would anchor differently? Let me test: reorder u6 before d. That's a real C move (statement order).

Let me also test: `d = (s16)d;` moved after u6. And test `d = (s16)d;` at the very end? No, must be before the divs.

Let me try several statement-order variants and score.

Actually, let me reconsider the whole thing. The score 21 with mine 75 = target 75. So the instruction COUNT matches; only registers/order differ. If I fix the register flip, maybe the scheduling follows.

Given the difficulty, let me check if maybe there's a "clean" way: what if `d` is declared as `s16` and the sign extension is done at the div? v3 scored 25 (worse).

What if the divisor variable is a `u16`? Or `s32 d = (s16)arg1` at decl?

Hmm, let me look at the target's register allocation from the perspective of: the target has d in s0 and s1ang/u6 in s1. What if in the original, the variable order/decls caused local-alloc to give s0 to a *different* qty that then died, making s0 free for s1ang... no, if it died, s0 is free.

Actually, WAIT. I think I've been wrong: local-alloc assigns s0 to s1ang, but what if there's ANOTHER local qty crossing the call that I'm missing — the *argument* a1's pseudo? `arg1` arrives in a1 (hard). If `d = arg1` is the only use of arg1, then arg1's pseudo dies at insn 6. No.

Hmm, but what about `arg0`? It's used in the loads at insns 15-20 (before the call). Dies before the call.

OK, let me try the empirical statement-order variants quickly. Let me create:
- w1: u6 computed before d=(s16)d
- w2: `d = (s16)d;` right after `d = arg1;` (at the top)
- w3: s1ang assigned after u6 (i.e., load, then u5, then d, then u6 — current) vs u6 before d
- w4: `d = (s16)arg1;` as a single statement at the top (sign-extend at prologue)

Let me test.
