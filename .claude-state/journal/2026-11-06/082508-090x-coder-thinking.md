---
ts: 2026-11-06T15:25:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_adF36zyrByEA94Qiykx9
---
All 4. Time 08:24:51. Item 2 from ~08:10 = ~15 min.

Hmm. I need ≥20 min. Let me continue for 5 more minutes with a genuinely different angle.

New angle: the problem is cse's fold of a `ne` compare where both operands are known. What if the *test* is not a `ne` but something cse doesn't fold — e.g., a comparison of *unsigned* values: `if ((u32)t != 3)` — the RTL would be `(ne (reg) (const))` after conversion, same.

What if the test compares `t` to 3 using a subtraction with an overflow check? No.

What if the test is `if (t > 3)`? t=5 → true; t=3 → false. cse knows t==5 → folds.

What if the test is on a *pointer*: `if ((s32)(t + (s32)&D_8011514A - (s32)&D_8011514A) != 3)`? folds.

What if the test is `if (t != *(s16 *)&some_zero)`? memory.

What about making t a `volatile`? banned.

What about making t an `s16` *static*? no.

Hmm, what if we use the fact that cse's jump equivalence is invalidated by a *call* that clobbers... t is a pseudo in a callee-saved register; a call doesn't clobber it, but does cse invalidate register equivalences at calls? cse's `invalidate_memory` at calls clears memory and call-clobbered registers' equivalences. t is in a callee-saved register, so its equivalence survives.

BUT — what if t were allocated to a *caller-saved* register (v0/v1/a0/a1)? Then a call between the branch and the test would clobber it and invalidate the equivalence! And the target's t is in s0 (callee-saved)... hmm, no.

Wait, but the equivalence is on the *pseudo* before allocation. cse works on pseudos, not hard regs. cse's call handling: `invalidate_memory` and invalidates pseudos that are call-clobbered? In cse, pseudos aren't assigned hard regs yet; cse treats a call as clobbering all memory and... let me check: cse.c's `invalidate_memory` and the CALL_INSN handling: it invalidates the equivalence table entries for registers that are call-clobbered (based on `call_used_regs`)? For pseudos (regno >= FIRST_PSEUDO_REGISTER), cse doesn't know their allocation. Hmm, in 2.7.2 cse, a call invalidates all memory and registers that are not... Let me check the source.

Actually, this could be a real lever: insert a call between the t==5 branch and the t!=3 test. But a call costs instructions (jal) and changes the object. Not matching.

Unless there's already a call we can reorder? No.

OK, another angle: what if the t==5 test is *not* a branch but a computed value, so no jump equivalence is recorded? E.g.:
```
s32 is5 = (t == 5);
if (is5) { if (t != 3) ... }
```
cse would fold is5 to a constant? It knows t's value only after the branch. Hmm, `is5 = (t == 5)` computes a boolean from t; then `if (is5)` branches. cse might record is5 == 1 on the fall-through, not t == 5! Then `t != 3` would NOT fold!

Wait, but gcc's front end / jump optimizer might see `is5` as `(t==5)` and propagate. Hmm. In 2.7.2, the tree→RTL generates the comparison into a register and a branch on it. cse's record_jump_equiv works on the branch's condition; if the branch is `bne is5, 0`, cse records is5 == 0 or != 0, not t == 5. Then the later `t != 3` isn't foldable!

But would the compiler emit the same code? The target has `bne s0,v0,740` — a direct compare of t vs 5. With `is5 = (t==5)`, the compiler would emit `slti`/`xori` + `beq is5,0` — extra instructions and a different shape. Unless combine/jump optimizes it back to `bne t,5`.

Actually, gcc's `jump_optimize` has a pass that converts `(set (reg) (comparison)); (set (pc) (if_then_else (ne reg 0) ...))` into a direct conditional jump (`do_jump`? or `if_then_else`). Hmm, in 2.7.2, `jump_optimize` does "if_then_else" optimization: if the condition is a comparison result used once, it converts to a direct jump. That would restore the direct compare and re-record the equivalence.

Let me test it — it's cheap:
v1: `{ s32 is5 = (t == 5); if (is5) { if (t != 3) ... } }` — but is5 must be 1 for t==5.

Hmm, but this adds a variable and a comparison. If the compiler optimizes it back, score 4.

Let me test. Also:
v2: use `if ((t == 5) != 0)`.
v3: `if (!(t != 5))`.

Also a different idea: make the t!=3 test's result be a computed value used in a goto:
```
if ((t != 3) ? 1 : 0) goto sel_094;   // folds
```

Let me test v1-v3.

Also, I realize I should consider: maybe the target's exact branch `bne s0,v1,71c` can be produced by a *different* source semantic that the compiler can't fold — e.g., `if (t != 3)` where t is compared against a value that comes from the *switch* index. Hmm.

Let me test v1-v3 quickly.
