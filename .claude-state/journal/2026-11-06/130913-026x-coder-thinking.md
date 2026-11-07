---
ts: 2026-11-06T20:09:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TyN9rrbBPba076K5R8TZ
---
`fix_register` is called for `__asm__("$2")` register variables → fixed_regs[$2]=1, n_non_fixed_regs--. So with the pin, threshold decreases by 1: threshold = 1 * (1 + n_non_fixed_regs). Without the pin, n_non_fixed_regs is one higher → threshold one higher → hoisting more likely!

So the pin's side effect: one fewer non-fixed reg lowers the threshold, preventing the hoist of the constant. That's a "global-hardreg-reserve"-adjacent mechanism: the pin changes the loop.c threshold.

Now, to reproduce lever-free: lower n_non_fixed_regs by one without a pin — impossible in C (that's a compiler-global). OR make the hoist not desirable by other means: raise insn_count or lower savings*lifetime. Since the condition is `threshold * savings * lifetime >= insn_count`, we need to make the product < insn_count (with threshold = 2*(1+29)?? Actually n_non_fixed_regs for mips = 32 - fixed. Fixed regs: $0,$31,$sp,$gp? Typically fixed_regs: 0, 28(gp?), 29(sp), 30(fp?), 31(ra). n_non_fixed maybe 26. threshold = (has_call?1:2)*(1+26)=27 or 54. insn_count = loop insns ~60. savings=1? lifetime=? If lifetime=1, 27 >= 60 false → no hoist. But we observed hoist without pin: threshold=2*(1+27)=56, 56*1*1=56 < 60... hmm not enough. Maybe lifetime=2 or insn_count smaller.

Wait — the loop is case 2's while loop. insn_count counts the loop insns (about 50?). Let me compute: the loop body from 2120 to 21a4 is ~35 insns. Then threshold*savings*lifetime >= 35 → with 56*1*1=56 ≥ 35 → hoist. With pin: 54 ≥ 35 → hoist too! Hmm, that contradicts.

Unless m->lifetime for a constant is small, like 1, and savings = 1... both hoist.

Hmm, so maybe the difference isn't loop.c. Let me look at the actual loop dump. That's decisive.

Let me splice vA's body into the TU and run cc1 -dl. I'll write a splice script (similar to hdump but for a function in a .c).

Plan: script splice.py <src.c> <body.c> <fn> <out.c>: replace the function definition in src with body text. Finding the function: from `^void func_80180254(s32 param_1) {` to the matching closing brace. Since we know the line range 3957..4067 from grep, easier: use the known body range. But a general approach: find the line starting with the signature and brace-count to the end.

Let me write it.

Actually, maybe simpler: I already have orig.c = exact function text, and the TU contains that exact text at 3957. So replace orig.c's text with the candidate body. Script: read TU, read orig (old body), read new body, assert old in TU, replace.

Let me write splice.py with args: tu, oldbody, newbody, out.

Then run cc1_dumps_tu.sh out.c tag with DUMP_ROOT under item dir, grep the .loop dump for our function and the constant.

Disk: dumps are a few MB; delete after.
