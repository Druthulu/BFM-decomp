---
ts: 2026-11-06T04:03:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TXGsdYVqjJnfKCzih18n
---
Still 58 ins — single load. cse forwarded (or the two loads were merged because x reused). Hmm.

Let me think about cse's load forwarding validation. Maybe cse keeps the load's value in a *new* pseudo assigned per load, not in x's pseudo. Actually at RTL, `x = load; diff -= x;` becomes:
(set (reg x) (mem ...))
(set (reg diff) (minus (reg diff) (reg x)))
...
(set (reg x) (mem ...))   ; second load
cse sees the second SET's src MEM; looks up MEM → found with value (reg x). It checks whether (reg x) is still valid: reg_in_table[x] == reg_tick[x]. When cse processes the second insn, has it already bumped reg_tick[x]? Let's read cse_insn: the src lookup uses `src_elt = lookup (src, hash, ...)`, then validates with `exp_equiv_p (src, src_elt->exp, 1, 0)`? The validate flag checks reg_in_table vs reg_tick for regs in the expression. The MEM's address has s0, valid. The entry's value (reg x) — the check in `lookup`'s chain: `if (mode == p->mode && (x == p->exp || exp_equiv_p (...)))` and then the "if (! validate || reg_in_table...)"? Hmm.

Then after src replacement, cse_insn records the dest: for the SET dest (reg x), it does `invalidate` on x's old value and records the new value. Actually cse_insn processes the insn's sets in order, and it first calls `invalidate` for the destination? Let me look at the actual flow around line 6400-7000. This is getting deep. Let me instead test empirically with a variant that definitely changes the value between: e.g., `x = 1;` used later? 

Alternative idea: make the second load use a different *mode* that still emits lh. No.

Alternative: use a different address expression that is not rtx_equal but emits the same insn. E.g., `*(s16 *)((s32)s0 + 0x2E)` vs `*(s16 *)(((s32)s0 + 0x30) - 2)`. cse folds constants: `(s0 + 0x30) - 2` → `s0 + 0x2E` after simplification? fold_rtx/simplify_plus_minus would fold. Hmm.

What about using a `u8*` base: `*(s16*)((u8*)((s32)s0) + 0x2E)` — same.

What about making the address through a *different register* that cse can't equate: e.g., `s32 base = (s32)s0;` and then a function-like expression. cse's copy propagation replaces base with s0 only if base is a "copy" in the table; canon_reg replaces registers with their constant/equivalent? Actually cse's canon_reg does replace a register with another if reg_qty equal and a cheaper reg exists? It uses `qty_const` etc. A plain copy `base = s0` is recorded and canon_reg may substitute s0 into uses. Yes.

What if base is computed as `(s32)s0 | 0`? folds.

Hmm.

Let me look at the actual mechanism in the target: maybe the second lh isn't a cse failure but a *scheduling* artifact: the first lh is at 77cc, and the second at 77d8. Both load 46(s0). If cse had forwarded, the second would be `sll v0,v0,6` on the first value. The target has a second lh. So cse did not forward.

What in the ORIGINAL source could stop it? Let me reconsider: maybe the two accesses are through *different pointer variables* that are both derived from s0 but with a store in between that the compiler must respect. E.g., the original might have written the `+=` as a read-modify-write where the load of 0xE occurs before the second load of 0x2E... but no store between.

OH WAIT. Maybe the original source order is:
```
t = (8 - *(s16*)(s0+0x2E)) << 9;
*(u16*)(s0+0xE) = *(u16*)(s0+0xE) + (*(s16*)(s0+0x2E) << 6);
```
And the FIRST load (for diff) is the one at 77cc. The second load (0x2E) at 77d8. cse would still forward the second. Unless the *store* to 0xE is between them in the RTL! Let's see: if the source is `*(u16*)(s0+0xE) = *(u16*)(s0+0xE) + ...`, the RTL is: load 0xE, load 0x2E, shift, add, store 0xE. The store is last. Not between.

But what if the original did TWO separate stores:
```
*(u16*)(s0+0xE) = something;   // store
...
x2 = *(s16*)(s0+0x2E);
```
No.

Hmm, what if the first `lh` at 77cc is not from the 0x2E load in the diff expression but from something else? It's `lh v0,46(s0)` → 0x2E. And the `subu a0,a0,v0` uses it. So yes.

Let me consider: maybe the original used `u16` for the diff load and `s16` for the x2 load, with the diff load being `lhu`? But target first is lh (signed). Unless the first is `lh` from a signed field.

What if the first load is via `((Unkstruct*)s0)->unk2E` (u16 → lhu)? No, target lh.

Could the target's first lh be from `*(s16*)(s0+0x2E)` and the second from `*(s16*)(s0+0x2E)` but with the *first* being a `volatile`? no.

Let me look at the source file history/notes for this function: maybe there are derivation notes above it. Let me grep around line 6778 upward for notes about the barrier.
