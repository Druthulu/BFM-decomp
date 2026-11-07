---
ts: 2026-11-06T20:14:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UdeEHCthrFXPfcbXuTPV
---
Still hoisted. The addiu was probably folded by cse1 or the insn_count didn't change. Let me check the loop dump for vG: insn count. Also check the .cse dump: maybe cse1 folded `a = *p; a += 10` into a mem reference? cse doesn't fold addresses... but maybe cse1's `simplify_rtx` or the address optimization in cse? Actually cse1 does `fold_rtx` which can fold `plus` of a register and a constant into a memory address? cse's fold_rtx does simplify address arithmetic: `lw v1,0(s1); addiu v0,v1,10` → fold_rtx may combine into `(plus (reg) (const 10))` only if the addiu is used as an address... cse doesn't create mem refs.

Hmm, but maybe cse1's `record_jump_equiv`... no.

Let me check the loop dump of vG.
