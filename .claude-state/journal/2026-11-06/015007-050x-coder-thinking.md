---
ts: 2026-11-06T08:50:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OEVAXYCyiSvjt5RYKgrZ
---
So in the lreg dump (after combine, cse2, flow, and register allocation prep), there IS a real insn 265: `(insn 265 132 134 (use (reg/v:SI 78)) -1 (nil))` with REG_DEAD (reg78) and an anti-dependency to 134.

Where did insn 265 come from? It's a USE insn. In GCC 2.7.2, `(use)` insns are emitted by... `flow`? No, it's not in the flow dump. It appears first in the combine dump.

OH WAIT. I bet insn 265 is from **combine itself**: when combine successfully substitutes and needs to keep the old value alive? No.

Hmm, but this is the *c1* (asm-removed) compile. The score is 1 with mine having `negu v1,s1`. If there's a `(use reg78)` insn blocking the merge, why is the negu still merged (neg reg77)? Because combine merged 132+134 into 134=(neg reg77) and then the use of reg78 at 265 became REG_DEAD... and the negu uses reg77 (s1). So the USE didn't block the merge — combine merged anyway and the use is just a dead use.

So where does this USE come from in c1? It must come from the source: `val = -val;` ... no. Hmm, `(use (reg78))` with REG_DEAD — a use of val that's dead. In the C source, is there a use of val that has no effect? Let me look at the full function source again... `val` is used: assigned in if/else, then stored twice, then reassigned. No bare use.

Unless the `(use)` is an artifact of combine's substitution: combine's `subst` creates a USE when the insn's value is... Actually, in GCC's combine, `try_combine` can create a USE insn when it splits i2/i3: "If I2DEST is used in I3 and also elsewhere..." Hmm.

Hold on — maybe the dumps I'm reading are actually from the ORIG (with asm) because cc1_dumps_tu.sh compiles the scratch .c file... which I verified has no asm at 5878. But wait: the `(use reg78)` at 265 with `-1 (nil)` — an asm with no outputs and one register input compiles to `(insn (asm_operands ...))` with `(use (reg78))` in its operands, not a bare `(use)`. Hmm, but in the dumps, `(insn 265 ... (use (reg78)))` could be the RTL that `expand_asm_operands` produces for a non-volatile asm with no outputs: GCC emits `(use ...)`? Let me check: for `__asm__("" : : "r"(val))` (non-volatile, no outputs), GCC's expand_asm_operands may emit just a USE of the input regs since the asm has no side effects... Actually with `__volatile__`, it emits an asm_operands insn. Our asm is `__asm__ __volatile__`. So it would be an asm_operands insn, not a bare use.

Hmm, but wait — the orig source line is `__asm__ __volatile__("" : : "r"(val));`. In the c1 candidate I deleted it.

So why a `(use)`? Let me check whether the scratch TU used by cc1_dumps_tu.sh is the p3 one I think. The cpp input path in the dump lines was `.run/P36/engine/score/ov_SC02_000__func_80187988/p3/ov_SC02_000_jr_8018173C.c` — that's the p3 scratch. And it has no asm at 5878. 

Hmm, let me directly check: does the c1 scratch still contain the keepalive anywhere? grep "keepalive" in it.
