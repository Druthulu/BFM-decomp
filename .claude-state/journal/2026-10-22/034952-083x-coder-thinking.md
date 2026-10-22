---
ts: 2026-10-22T09:49:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_6VRLOARq7K3EAn4JhuXQ
---
All still 1. Interesting: even v27/v28 (temp pointer) give 1 — so the tree ends up the same shape.

Hmm, v31 (p as u32) — the value is still a constant → folded.

Let me try a fundamentally different idea: make the pointer's value NOT a compile-time constant by deriving it from something the compiler can't fold, but which is still correct... e.g., the pointer could be computed as `&D_80195AF6[0]` — constant.

Hmm. What if the *index* is the constant and the pointer... no.

Let me reconsider: maybe the substitution at expand is NOT of the pointer but of the ADDRESS: expand's `expand_expr` for a MEM address builds the address; for `(u8 *)p + off + 4` it produces (plus (plus (reg p) (reg off)) 4) — and then... the .rtl dump shows (plus (symbol) (reg 118)) — so p was replaced by the symbol.

Where? Since the .rtl dump is post-expand and shows the symbol, expand did it. In gcc 2.7's expand.c, function `expand_expr` case REG:

I'm now going to accept it and think about how the ORIGINAL source might have differed. Since the target's asm has TWO materializations of the symbol (a1 for the pointer, at for the newval address) and the pointer is in a reg at the add...

Hmm, WAIT. What if in the original source, the pointer p was used in BOTH the newval load and the final load, and the newval load's address was (plus (reg p) (reg idx)) — with p in a1 — and the "lui at; addu at,at,v0" in the target is actually the *newval* expression using a DIFFERENT constant (not the symbol)!

Let me re-read the target's relocations:
```
2c0c: R_MIPS_HI16 D_80195AF6   (lui a1)
2c10: R_MIPS_LO16 D_80195AF6   (addiu a1)
2c14: R_MIPS_HI16 D_80195AF6   (lui at)
2c1c: R_MIPS_LO16 D_80195AF6   (lh v0,0(at))
```
Both a1 and at are D_80195AF6. So the symbol is materialized twice ✓ (as in ours).

In ours, we have the same two materializations: a1 (for the pointer at the final add) and at (for the newval address). And ours has the same count (111) and the same asm except the add's operand order.

So the ONLY difference is the operand order of the final add. And the trees at combine time are presumably identical in shape: (plus (symbol) (reg idx)) in both.

So combine swapped in OURS but not in the TARGET. The difference must be in combine's decision (which depends on the surrounding insns / allocation).

Hmm! Since the trees are the same, but the outcomes differ, the difference is in the *context*. What context? Possibly:
- The pseudo register numbers (different register allocation → different alternatives).
- The number of insns in the basic block.
- Whether combine's try_combine for that insn SUCCEEDED (accepted) in ours and FAILED in the target.

If combine's combination FAILED in the target, the swap would be undone (combine restores the insn). So in the target, combine attempted the same simplification but rejected the result!

What was combine trying? Possibly: combine the `sll v0,v0,3` (mult 8) with the address: the address (plus (symbol) (mult idx 8)) — combine can build a "compound operation" address: (plus (symbol) (mult idx 8)) and then try to fold the shift into the address, deleting the shift insn. In our case the shift insn is NOT deleted (the asm still has sll + addu) — hmm, so the combination failed there too but the swap persisted?!

Unless the swap we see comes from a DIFFERENT combine attempt that succeeded: e.g. combine tried to combine the `addu` with the `lh` (the load) — i.e. the address computation into the load — and accepted a version with the swapped operands.

Hmm, hmm. Since combine's swap is applied by simplify_rtx to the insn's source, and combine works on a copy (undobuf) that is restored if the combination fails... The swap would be undone on failure.

So in ours, a combine attempt SUCCEEDED with the swapped address. What did it accomplish? Perhaps it combined the shift+add into a different form but ended up with the same instruction count.

In the target, the corresponding attempt failed (perhaps because the register allocation differed).

This suggests: the difference could be flipped by changing the register pressure slightly elsewhere in the function — e.g. by changing the declaration order or the statement order in a way that changes the allocation but keeps the asm identical. That's a big search space.

ALTERNATIVELY: maybe the target's original source differed in a way that changes combine's behavior — e.g. the original had `off` as a different type or the index expression differently.

Since we're at score 1 (one instruction), maybe I should look at this from the "what does the ORIGINAL source look like" angle. The original game source (Silent Hill / Clock Tower?) — the decomp project's src is a reconstruction. The original code for this function might have been:

```c
void func_80184828(s32 arg0) {
    ...
    } else {
        s16 newval = D_80195AF6[arg0->unk100].f0;
        if (newval >= ...) {
            ...
            D_801270C8 = *(s16 *)(D_80195AF6 + arg0->unk100 * 8 + 4);
```
Hmm.

Let me try the variant where the final load uses the SYMBOL directly instead of p:
`D_801270C8 = *(s16 *)((u8 *)D_80195AF6 + off + 4);`
That's a variant I haven't tried! The tree would be (plus (symbol) (reg off)) — hmm, same shape as now (since p was substituted). But maybe the *shape* of the tree differs subtly (e.g. no separate set insn for p → different insn numbering → combine's decisions differ!). The pseudo numbering affects combine? Combine doesn't care about pseudo numbers much, but the surrounding insn structure does.

Also: the removal of the `p = D_80195AF6` set insn changes the block structure (one fewer insn) → combine's insn indices shift → different try_combine pairings! That's a plausible lever.

Let me try:
v37_symbol_direct: replace the load with `D_801270C8 = *(s16 *)((u8 *)D_80195AF6 + off + 4);` and remove the p declaration (p unused → compile error "unused" is fine, but the declaration of an unused variable is OK in C). Actually, keeping `D_80195AF6_t *p = D_80195AF6;` unused would still emit the set insn (or gcc removes it as dead). Let me remove the p declaration entirely.

v38: keep p but use it only in the newval load: `s16 newval = p[...].f0;` and the final load uses the symbol directly:
`D_801270C8 = *(s16 *)((u8 *)D_80195AF6 + off + 4);`
Then p is used once (in the newval) → the newval address = (plus (reg p) (reg idx))... hmm, that changes the newval's materialization.

Let me try a batch:
v37: no p at all; the final load uses the symbol directly.
v38: p used for the newval, the symbol for the final.
v39: p declared but the final load uses the symbol; p unused → remove p.
v40: the final load uses `D_80195AF6` with the index scaled: `D_801270C8 = *(s16 *)((u8 *)D_80195AF6 + off + 4);` with off = `((Unkstruct_800B5CB8 *)a0)->unk100 * 8`.

Let me also try moving the `off` assignment to a different place (statement order): e.g. compute off before the if.

And: move the pointer declaration to the top of the function and use it there.

Let me generate and run.
