---
ts: 2026-10-22T12:54:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_P4ykMqz4VwxTSNrCScxv
---
EXCELLENT! Now I see the RTL after expand:

```
(insn 9) (set (reg/v:SI 73) (symbol_ref:SI ("D_80120194")))
(insn 12) (set (reg/v:SI 72) (plus:SI (reg/v:SI 73) (const_int 25996)))
...
(insn 26) (set (reg/v:SI 73) (symbol_ref:SI ("D_801202A0")))
```

So the front end (expand) already put the local variable `it` into a PSEUDO register 73 (reg/v:SI) — GCC 2.7 DOES keep locals in pseudos (the "local variable in a pseudo" optimization exists in 2.7: `expand_start_function` creates pseudos for locals? Apparently yes: `reg/v:SI 73`).

So `it` is pseudo 73 with TWO sets (insn 9 and insn 26)! And the base value is set once (insn 9) but the pseudo has 2 sets → cse's `n_sets == 1` condition fails → NO REG_EQUAL note → the constant is NOT substituted at the use!

Wait, but our compile DID fold it. Hmm, the fold must happen later (in reload or combine). Let me check the later dumps: .cse, .cse2, .jump, .lreg, .sched, .combine.

Note: pseudo 73 is used for BOTH the base and D_801202A0 (the same variable `it`, 2 sets). So the pseudo has 2 sets → cse won't add a REG_EQUAL note.

But the fold still happened in the final code (the address was folded with the addend). So the fold happened in a later pass (reload? combine?).

Let me look at the .combine dump and the final .s to see. Actually, more useful: let me see when the pseudo 73 (the base) becomes the constant address. Let's grep the dumps for "25996" and for the symbol_ref with the plus.

Let me look at .lreg (local-alloc) and .sched.

Actually the key: in the final output, `lui a0, hi(D_80120194); addiu a0,a0,25996`. So the plus (reg 73, 25996) became a memory-style address operand. That happens when the pseudo 73's value is known to be the symbol_ref and the address is folded: i.e., reload's "rematerialization" or cse's `find_best_addr`/`cse_addr`.

Since cse has the "quantity" mechanism: pseudo 73 has 2 sets → cse creates TWO quantities for it (reg_qty). Hmm, actually in cse, a pseudo with multiple sets gets split into quantities: `make_regs_eqv` splits a pseudo's uses. So the first set's uses (insn 12) belong to quantity A, and the second set's uses to quantity B. Quantity A has 1 set → qty_const[quantity A] = symbol_ref → equiv_constant(73) at insn 12 → the constant is substituted → (plus symbol_ref 25996) → folded into an address.

So cse DOES substitute it (because cse splits the pseudo into quantities per set). Then the address (plus symbol_ref const) is a MEM-like address → the mips backend emits lui/addiu with the addend.

Hmm! So to prevent this, the base's quantity must have 2+ sets, i.e. the base value must be set twice (in a way cse can't merge).

Hmm, that's the "real 2nd set" trick: e.g. `it = (s32)D_80120194;` appearing TWICE (two sets of the same value) → the quantity for the first set... hmm, cse would see two sets of the same constant → it would make them equivalent (cse merges them: the second set is redundant and cse deletes it). Hmm.

But my earlier test with the dead store `it = 0; it = (s32)D_80120194;` didn't help. Because cse deleted the dead store or because the quantity split still left the first set alone.

Hmm, what about the "real 2nd set" used in G14: `v = (s16)v;` — a conversion that produces a different mode → the pseudo gets a SUBREG/HImode value → the equivalence class is broken.

For our case: the base value is a 32-bit address. A conversion that keeps the value but changes the RTL: e.g. `it = (s32)(u32)(long long)D_80120194;`? Hmm.

What about `it = (s32)D_80120194;` then `it = (s32)(u16)...` no (truncation).

**What about a 64-bit intermediate?** `it = (s32)(long long)(int)D_80120194;` — the conversion of a constant to long long is folded by the front end (the value fits) → the RTL would be (set 73 (symbol_ref)) again? Hmm, but wait: expand_expr for a conversion to a wider mode emits a sign-extension (sll/sra or a word pair). For a CONSTANT, the front end's fold would... `(long long)0x80120194` = 0xFFFFFFFF80120194 (as a signed 64-bit) → then (s32) of that = 0x80120194. GCC's fold would compute the constant 0xFFFFFFFF80120194 in TImode → the RTL would be a TImode constant → the assignment to an s32 variable → a truncation → (set 73 (truncate (const 0xFFFFFFFF80120194))) → hmm, the truncate of a constant folds back to the constant. Probably folds.

OK. Let me look at the problem from the "2 sets" angle and TEST what actually works. Let me look at what the .cse dump shows for the base, and then try to find a spelling where cse can't split the quantity.

Let me look at the cse dump (nl.i.cse) around the function.
