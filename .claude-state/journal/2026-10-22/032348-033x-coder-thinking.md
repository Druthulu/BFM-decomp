---
ts: 2026-10-22T09:23:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8FeWwO0QlSvmUSZsqOR5
---
The address tree in the cse dump: `(plus:SI (reg:SI 118) (symbol_ref D_80195AF6))` — index first, symbol second!

The target's tree must be `(plus:SI (symbol_ref D_80195AF6) (reg 118))` → pointer first.

So in our C source the tree came out index-first. The C source is:
```c
off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
Hmm — but the tree shows the symbol_ref (not a reg) as the second operand: (plus (ashift ...) (symbol_ref D_80195AF6)). So the p value was a constant symbol_ref! p = D_80195AF6 (a constant address). And the pointer got folded as symbol_ref.

So the source expression `(u8 *)p + off` where p is a variable holding the constant address → after cse/const-prop, p's reg_equiv = symbol_ref, so the tree is (plus off (symbol_ref)) or (plus (symbol_ref) off) depending on the C expression order!

We wrote `(u8 *)p + off` → that should be (plus (symbol_ref) off)... but we got (plus off (symbol_ref)). So something reordered it. Where? In the RTL dump (before combine) let me check the tree of insn 190.

Note the .rtl dump is after expand (before combine). Let me look at the same insn in rtl pass.

Actually, in expand, `p + off` where p is a pointer pseudo: the tree is (plus (reg p) (reg off)). Then combine substitutes p's reg_equiv (symbol_ref) — combine's `reg_equiv` substitution replaces (reg p) with (symbol_ref) — keeping position → (plus (symbol_ref) off)? That would give pointer first! But we see (plus 118 (symbol_ref)).

Hmm, wait: maybe the operand order in the RTL is already (plus off p)? Let me check the rtl dump for insn 190.

Note also the target: `addu v0,a1,v0` — the pointer is in a1, a register, not a symbol_ref. In our case the pointer is symbol_ref (folded into the add as lui/addiu). Actually the target also has `lui a1; addiu a1,a1,0` (materialized into a1), while ours has... our asm: we saw "lui a1,0x0; addiu a1,a1,0" in the target. In ours? The diff showed only 1 insn differing, so ours also has lui a1/addiu a1. So the pointer is in a1 in both; but the RTL tree shows symbol_ref, and the *reload* allocates a1 for it. Fine.

So the question: what determines (plus X Y) order? In our tree: (plus (ashift ...) (symbol_ref)). In the target: (plus (symbol_ref) (ashift ...)).

If the order came from the C source `(u8*)p + off`, expand would give (plus p off) → pointer first. So the reorder happened in combine or cse. Let me check the rtl pass tree for that insn.

Let me search rtl dump for the insn with symbol_ref D_80195AF6 and plus.
