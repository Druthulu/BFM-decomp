---
ts: 2026-11-06T20:08:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ftqQ9E8euSQTVzqbnpR7
---
Condition: `threshold * savings * m->lifetime >= insn_count`. threshold = (loop_has_call ? 1 : 2) * (1 + n_non_fixed_regs). n_non_fixed_regs = number of non-fixed regs... `1 + n_non_fixed_regs` where n_non_fixed_regs counts registers allocated? Actually n_non_fixed_regs = number of registers that are not fixed (from `max_reg_num`?) Let me check. It's `n_non_fixed_regs = max_reg_num() - FIRST_PSEUDO_REGISTER`? Let me grep.

Actually the key: with the pin, v0 is a fixed hard register. `n_non_fixed_regs` might change? Probably not much.

Hmm, `savings` = number of times used * loop depth? For a constant used once, savings=1. `m->lifetime` = ? For a constant, lifetime maybe 1. insn_count = number of insns in the loop (~60). threshold*(1)*(1) >= 60 → threshold >= 60, so no hoist. Hmm, but mine hoisted! So maybe lifetime is large or savings large.

Wait, maybe the constant insn `li -1024` was not hoisted by loop.c but by cse's constant pool or by `combine`? The `li s4,-1024` appears at the preheader right before the loop (2124, after `move s3,zero`). That's the loop preheader. So loop.c or `loop_optimize`.

Hmm, hold on: maybe it wasn't hoisted at all; maybe the `-0x400` store was *converted* to use a callee-saved reg because local-alloc decided to keep the constant in a register across iterations? No, a constant load inside the loop would be `li v0,-1024` each iteration; the hoist is a real optimization.

Actually wait: maybe it's `cse` that hoisted it? cse doesn't hoist out of loops. `loop.c` does.

Let me look at the loop dump. I can run cc1 with -dl on a spliced TU. That's the reliable way. Let me create a spliced TU with vA's body and dump loop.

But first, is it worth it? We have a promising direction: keep -1024 inside the loop. The target does `li v0,-1024` with v0 free because... hmm.

Think: `threshold * savings * m->lifetime >= insn_count`. n_non_fixed_regs is computed at line 532: `threshold = (loop_has_call ? 1 : 2) * (1 + n_non_fixed_regs);`. Let me find n_non_fixed_regs.
