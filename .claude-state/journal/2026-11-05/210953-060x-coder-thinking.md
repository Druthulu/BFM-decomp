---
ts: 2026-11-06T04:09:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Mo4fyF4G4i86IEuAgFLY
---
This is very deep. Note `#ifdef LOAD_EXTEND_OP`: MIPS defines LOAD_EXTEND_OP? For MIPS, LOAD_EXTEND_OP(MODE) is likely defined as SIGN_EXTEND for QI/HI. This means cse may replace a sign-extended load with a subreg of a wider load, but not relevant.

The key insight I need: the load entry's validity check uses `exp_equiv_p(p->exp, p->exp, 1, 0)` with validate=1, which checks all registers in the expression are up-to-date (reg_in_table == reg_tick). The expression is the MEM (address s0+46). s0 must be valid. It is. The VALUE (the register that holds the loaded value) is in the equivalence class: the table element for the MEM has `first_same_value` linking to the REG that holds it. The forwarding picks the REG if valid.

Now, when does the load's REG become invalid? When the REG is set. The load's destination REG is set by the load itself (recorded after). Between the two loads, the REG isn't set. So valid.

BUT: what if we make the destination of the FIRST load a register that is ALSO the destination of an intervening instruction — i.e., the compiler reuses the same pseudo for something else. In C, that means assigning another value to the same variable. c4 did that and it still forwarded, because the lookup of the second load happens at the insn where the same pseudo is the destination. Hmm, but the *first* load's entry maps MEM→pseudo x. The second load is `(set (reg x) (mem))`. At this insn, cse processes the src (mem): lookup finds MEM→x entry, validates x (not yet set by this insn? The set is being processed now). If x's tick hasn't been bumped yet, it's valid → replaces the src with x → `(set (reg x) (reg x))` → deleted. So yes.

To bump x's tick before the second load, we need an instruction that sets x between. In C, `x = <non-mem value>` where the value is a register/constant. That's c5's `x = t` (a copy from t). That bumped x. But c5 changed the first load to lhu+sll+sra because x was s32 and used in a copy context? Weird. Actually the reason: `x = t` where t is s32 made x's value need to be SImode; the first load `x = *(s16*)` is HImode→SImode sign extension. In the original `diff -= *(s16*)`, the load is directly consumed by subu, so `lh` works. When x is a separate variable assigned from the load, GCC should still use lh (sign-extending load). But c5 emitted lhu+sll+sra... because `x = t` where t is s32 made cse/combine try to zero-extend? Hmm, odd.

Wait, in c5 the first load became `lhu v1,46(s0); sll v1,v1,0x10; sra v0,v1,0x10`. That's sign extension from a u16 load. This suggests the load was treated as u16. Why? Because `x = t` made x's later value t; combine may have merged? Strange.

Let me try c5 variant where the reassignment is a *constant*: `x = 8;` but then x used? If x is used later in the stores as `x` (instead of t), and x = 8? That changes semantics.

Hmm, what if we reassign x to a value that's a copy of a *s32 constant* and then x is used in a place that doesn't affect output... but dead code.

What about reassigning x to `t` but declaring x as `s16`? Then `x = t` truncates; and the first load `x = *(s16*)` stays lh. Then the second load into x2. Let's test:
```
s16 x;
s32 diff = 8;
x = *(s16*)((s32)s0 + 0x2E);
diff -= x;
t = diff << 9;
x = (s16)t;      // reassign x, live? need use
```
x used later? We could use x at the end: `unk1A = x;` — but x = (s16)t truncates t, changing the value (t is diff<<9, could exceed s16). Wrong.

Use x for something harmless: `if (x) ...` adds branch. Hmm.

Alternatively, reassign x to a value and then *don't use* it, but prevent DCE by making x address-taken? no.

What if x is used in a context where the compiler must keep the assignment but it produces no extra insn? E.g., x is used as the value of a store that already exists? Not possible.

Let me look at the pass order: does DCE run before cse1? If dead assignments are removed before cse1, then a dead reassignment won't help. If after, it might. Let me check toplev.c rest_of_compilation order.
