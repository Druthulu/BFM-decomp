---
ts: 2026-11-06T16:50:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2WQ53rzF7s5Vf4dopCEO
---
At RTL generation (before cse), there are separate pseudos per site: insn 153 (reg 86) for the first, insn 231 (reg 103) for the group B site. Then cse merged them into one (86) since both are the same constant and 86 is a variable pseudo that stays live.

Actually cse merged 103 into 86 (or vice versa) because they're equivalent constants. In the target, cse did NOT merge them. Why? Because with the asm, cse couldn't. Without it, cse merges because 86 is live across the calls and holds the constant.

Hmm wait, is that really cse? reg/v 86 is set at 153 and used later at group B. cse's "reg/v" merging: when cse sees `(set (reg 103) (symbol_ref))` and reg 86 already has the same constant, it can substitute 86 for 103 (if 86 is not clobbered). 86 is a pseudo (reg/v), not a hard reg, so it survives calls. That's the merge.

To prevent: make the constants *not identical* or make the variable pseudo not live across calls.

The original's C: what if each site used a *different* local variable (fresh scope), e.g. the block-scoped `{ s32 m = ...; }`? We have that for the laundered ones, but cse still merges across blocks because the pseudos are equivalent constants.

What if the expression isn't a pure constant but a *load* of a global pointer? E.g. if the original source had `(void *)D_8018E2DC` where D_8018E2DC is declared as a pointer variable (`u8 *D_8018E2DC;`), then the value would be `lw a1,0(a1)` — but target shows lui/addiu (address), so no.

Hmm, what if the original source used an *array indexing* form: `&D_8018E2DC[0]` vs `D_8018E2DC` — identity.

Let me think about cse's rules: it merges two identical constants if the first register is still valid. The reg/v 86 is a variable pseudo. The merge gives one register holding the address across calls, which global-alloc puts in a callee-saved reg. Target avoided it.

What if the variables m were declared with different *types* per site such that the RTL modes differ? E.g. `u8 *m` vs `s32 m` — the symbol_ref is SImode in both.

What if the target's source passed the address via a `void *` *parameter* or a function call? no.

Alternative: prevent cse from keeping the pseudo across calls by making the address "clobbered" — e.g., the value is stored to a volatile? no.

Hmm, let me reconsider. Maybe the original source didn't use symbol constants at all, but an array of pointers:
```
func_8017D8A4(D_801BFCC4 + 0x84, D_8018E2DC, ...)
```
Target shows lui/addiu — definitely the address.

What if the original used a **local array**: `u8 *srcs[] = {D_8018E2DC, ...};` then the loads would be from the stack. No.

OK, think about cse's merge condition more concretely. In cse.c, the merging of registers with known constant values happens in `cse_insn` via `qty_const` and `exp_equiv_p`. When the destination is a *variable* pseudo (reg/v), cse sets qty_const[reg] and marks it. Later, an insn `(set (reg 103) (symbol_ref))` with REG_EQUAL... cse's fold_rtx replaces the source with the equivalent register 86 if cheaper. The cost comparison: a register (cost 0? or REG_COST) vs a symbol constant (cost 2). fold_rtx prefers the register when the constant is "expensive" (COSTS_N_INSNS(2) > 0). So it substitutes.

In the target, the same substitution should happen... unless in the target's RTL the two constants are in *different modes* or the first register was killed.

Hmm, hold on: maybe the target's original had the first 3 calls (group A) laundered-free but the *order* of the source differs, so that the constants never have a long enough live range... but target is identical order.

Wait, maybe I should reconsider: perhaps the original source is exactly what we have WITHOUT the launders, but the compiler that produced the target used a different *declaration* of D_8018E2DC: e.g. `extern u8 D_8018E2DC;` (a scalar byte) rather than `extern u8 D_8018E2DC[]`. If it's a scalar u8, then `(s32)D_8018E2DC` is a *byte load* (lbu), not an address! But target emits lui/addiu — the address. So `(s32)D_8018E2DC` must be the address → array.

Unless the source wrote `(s32)&D_8018E2DC` — same.

Hmm, let me look at what the target does for the *5th argument* `1`: `sw s3,16(sp)` where s3 = 1 loaded once at 715c. So the constant 1 is kept in a register across calls (s3) in the target. So cse DOES keep constants in registers across calls in the target for the small constant 1. So cse merging per se isn't disabled.

The difference: for the symbol addresses, target does NOT keep them; for the int 1, it does. Why? Because the symbol address is used at most twice (once in group A, once in group B), while 1 is used 12 times. Hmm, cse doesn't count uses.

Actually, cse's constant preference: CONST_COSTS(SYMBOL_REF)=2. In fold_rtx, when replacing a constant with an equivalent register, it checks `if (COSTS_N_INSNS(1) <= cost)`. A register's cost is 0 in the same... hmm.

Wait, maybe the difference is that in the target the two uses of D_8018E2DC are in different *extended basic blocks* and cse's table is invalidated at the call (calls invalidate the table for memory but not for constants). Hmm.

Let me look at the actual cse dump for the ORIG (with asm) — it scores 0, so its RTL is the target's. Let me dump orig and look at how the symbol pseudos are arranged. That tells us what we need to reproduce.
