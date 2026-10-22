---
ts: 2026-10-22T10:56:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2EZDACmrGalB8peMXRB4
---
Hmm, ze0 = 1 — the same as before! So the front end STILL folds the constant (the assignment `p = D_80195AF6;` is folded into the use just the same). Hmm — so gcc's front end (c-type.c) does NOT substitute only for initializers; it substitutes for any assignment of a constant to a variable? Hmm, no: the front end can't substitute an assignment's RHS into later uses (that's a data-flow optimization, cse's job).

So the folding happens at the RTL level (expand/cse), not the front end. Hmm! But then how did the target keep the pointer in a reg?

Hmm, wait. Let me re-examine: with ze0 (the assignment form), the score is 1 — the same residual. So the tree still has the symbol in the plus.

Hmm, but hold on: with the assignment form, the RTL would be `(set (reg p) (symbol_ref))` + the use `(reg p)`. Then cse's "qty_const" mechanism substitutes the constant into the use (that's the cse.c:2282 code I read: `base = qty_const[reg_qty[REGNO(base)]]` in set_nonvarying_address_components — used by refers_to_mem_p, and also the fold_rtx path). So cse substitutes ✗.

And the .rtl dump (pre-cse) would show (plus (reg p) (reg idx)) → then cse substitutes → (plus (symbol) (reg idx)) → then combine swaps ✗.

Hmm! So for the target to keep (plus (reg p) (reg idx)), cse must NOT substitute. Per §195-I, a second set of the pseudo kills the fold!

Hmm — so for 80184828, the pointer p would need a second set. The def has p set once. Hmm.

Hmm, BUT: what about the *newval* load's address, which also uses the symbol? Hmm.

OK so, hmm, let me reconsider: maybe the fold in cse happens only when the reg's quantity has a constant. The quantity is per-reg-group. Hmm.

Let me test the hypothesis directly on 80184828: add a second set of p (an identity — just for the experiment, not as a crack) and see if the add's operand order flips to pointer-first. If yes, the mechanism is confirmed and the expert can look for a legitimate second set.

Let me try: `p = D_80195AF6; ... p = p;` (an identity, for diagnosis only).

Hmm, but hold on: is there a legitimate second set in the def? Let me re-read the 80184828 def's else arm:

```c
        } else {
            D_80195AF6_t *p = D_80195AF6;
            s16 newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;

            if (newval >= CAST_SIGN(s16, (u8 *)a0, 0xE)) {
                s1 = 1;
                ((S0E_80184828 *)((u8 *)a0 + 0xE))->h = newval;
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
                D_801E43B4 += 1;
            }
        }
```
One set of p. Hmm.

But WAIT: what about the FIRST arm (the `D_801E4BBC == 1` arm)? It has no p.

Hmm, and the p in the target: the target's pointer is in $a1 (a caller-saved reg) — so in the target, p's pseudo was NOT live across calls and was NOT folded.

Hmm, so the target's p pseudo exists at the RTL level and cse did not fold it. Hmm, why?

IDEA: maybe because in the target, the pointer's value was NOT a constant at the RTL level: e.g. the original source may have had `p` assigned from a *table* or the address of a *struct member*... but the asm shows lui/addiu of D_80195AF6.

Hmm, hmm. What if the original source had:

```c
D_80195AF6_t *p = D_80195AF6;   /* but D_80195AF6 is declared as an ARRAY of structs and p is used as p[idx].f0 */
```
Hmm.

Hmm, what if the original had the pointer as a **function parameter** of an inlined helper? no.

What if the original had the pointer in a **union/struct**? no.

Hmm, what if the original source's `p` was declared at the FUNCTION scope (not the block) and assigned in the arm? Then the pseudo is born at the function's start → live across the calls → callee-saved ✗ (the target has $a1).

Hmm! So the target's p is born in the else arm ✓ (like our def) and is NOT folded by cse.

So: why doesn't cse fold the target's p? Hmm, maybe because the SET of p is in a different basic block than its USE, and cse's quantity tracking... hmm, no, cse handles that.

Hmm, or maybe because in the target, p's value was set by an insn that cse didn't recognize as a constant set: e.g. `(set (reg p) (plus (symbol_ref) (const_int 0)))` — hmm, that folds to the symbol.

Hmm, what about `(set (reg p) (symbol_ref))` where the symbol_ref has a *non-default* mode (e.g. in a different mode than the reg)? Hmm.

OK, let me run the diagnostic: add an identity second set of p in 80184828 and see if the operand order flips. If it does, the mechanism is "the second set kills the fold" and I'll note it. Let me also test the same for 8018483C (`p = p;` after `p = &D_800B99DC;`) — the copy might then survive → "lui v0; addiu v0; move s0,v0"!

That's worth testing as a DIAGNOSTIC (not a crack — an identity statement is a launder per the brief).

Let me run both diagnostics.
