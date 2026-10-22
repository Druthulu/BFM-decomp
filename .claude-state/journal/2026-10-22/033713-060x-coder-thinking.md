---
ts: 2026-10-22T09:37:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hvyOdTlMVAUafgJY4ejm
---
So cse records `qty_const` for a reg whose class head is a constant — i.e. when a reg is set to a constant (symbol_ref), cse records qty_const[reg] = symbol_ref, and later `simplify_addr` (cse.c:2282) replaces the base REG with the constant.

Crucially, the `simplify_addr` replacement happens for an address whose base is a REG with a known constant. This is the "cse-const-addr" mechanism from walls.txt.

Now: how to prevent it? Options:
(a) The pointer pseudo must not be in the "quantity" as a constant — e.g. if the pseudo's class has multiple members or the set isn't recognized as a constant.
(b) The address's base must not be a plain REG (e.g. if the pointer is used as (plus (reg ptr) (reg idx)) but the base is not the first operand...). Note simplify_addr handles (plus (reg) (const_int)) and (plus (reg) (reg)) cases, and the plain REG case.

Hmm — importantly, simplify_addr replaces the base REG with the constant when the base has a constant equivalent. But what if the pointer's *mode* differs (qty_mode check)? The check `qty_mode[reg_qty[REGNO(base)]] == GET_MODE(base)` — the mode must match. If the pointer is used with a different mode (e.g. as a u8* vs the set mode), the substitution wouldn't happen! Hmm, the pointer is set as a pointer (32-bit) and used as (u8*)p — same mode.

(c) Make the address not have the pointer as its BASE: e.g. `off + (u32)(u8*)p` → the tree (plus (reg off) (symbol)) hmm — then the base is off (not a constant) and the symbol is the second operand (not a base) → simplify_addr wouldn't replace... but the resulting order is index-first → wrong order anyway.

(d) Prevent cse from recording qty_const: the recording happens when the reg's class head is a constant. If the pseudo is set to the symbol AND ALSO something else (e.g. set twice), the class might not be "is_const".

Hmm! What if the pointer pseudo is set to the symbol TWICE (e.g. `p = D_80195AF6;` in two places)? cse would find them equivalent. Hmm.

(e) What if the pointer is assigned in a way that produces a non-constant SET: e.g. `p = (D_80195AF6_t *)(s32)D_80195AF6;`? The cast of a symbol to an integer then to a pointer: in gcc 2.7 the tree would be (set p (cast (symbol_ref))) — hmm, the C front end folds (cast (addrconst)) to (addrconst) usually. For an integer cast: (cast (symbol_ref D_80195AF6) int) — the symbol_ref in an integer context is not allowed in gcc (symbol_ref is an address); the front end would produce (symbol_ref) with a different mode? Hmm, in old gcc, casting a pointer to an integer keeps it as (symbol_ref) with a "CONST" wrapper? Actually gcc 2.7 represents `&D_80195AF6` as (symbol_ref D_80195AF6) and casting to int gives... the front end would produce (cast (symbol_ref)) — illegal in strict gcc, but old gcc allowed (SYMBOL_REF) in any mode? Let me test empirically! The notes tried "(u16 *)(s32)&D_800B99DC" for the OTHER item (8018483C) and it was "folded".

OK. Time to experiment! Let me set up the batch tester and try a bunch of spellings for 80184828. Each try ~1s. Let me write a runner that takes a list of body files and prints scores, so I can generate many variants.

Let me write a Python generator that produces variants by textual substitution on the base file, then score them all.

Base body (v1.c) region:
```
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

Variants (each a full body):
A. base
B. `u8 *p = (u8 *)D_80195AF6;` + `*(s16 *)((u8 *)p + off + 4)`
C. `D_80195AF6_t *p = D_80195AF6;` + `*(s16 *)((u8 *)p + (off + 4))`
D. `*(s16 *)((u8 *)p + 4 + off)`
E. off as u32: `u32 off;` + `off = unk100 * 8;` + same load
F. off as `u32 off = unk100 * 8;` inline
G. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` where off = `unk100 << 3`
H. pointer temp: `u8 *pa = (u8 *)p + off; D_801270C8 = *(s16 *)(pa + 4);`
I. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with the newval through p: `s16 newval = p[unk100].f0;`
J. `s16 newval = p[unk100].f0;` + `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` (both through p)
K. `off` computed via a temp index: `s32 idx = unk100; off = idx * 8;`
L. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with p declared as `D_80195AF6_t *p;` at the top and assigned in the arm: `p = D_80195AF6;`
M. `*(s16 *)(void *)((u8 *)p + off + 4)`
N. `D_801270C8 = *(s16 *)((u8 *)p + off) ; ` with off = unk100*8+4 and the load `*(s16 *)((u8*)p + off)`
O. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` but with `p` used as `&D_80195AF6[0]`
P. swap the C operand order: `*(s16 *)((u8 *)off + (u32)(u8 *)p)` — hmm invalid semantics? (u8*)off + (u32)p is the same address. Actually `*(s16 *)((u8 *)off + (u32)(u8 *)p)` = off + p ✓ same address.
Q. `*(s16 *)((u8 *)p + off + 4)` with p as `volatile`? no (lever).
R. index as u32: `off = (u32)unk100 * 8;`

Let me also consider: maybe the fix is to make the *index* not scaled in the tree: e.g. compute `off` as `unk100 * 8` but with off being a *u32* and the address `(u8 *)p + off` → the tree (plus (reg p) (reg off)) — the simplification of the address by cse's simplify_addr only replaces the base when the base has a constant equivalent. So the base (p) IS replaced by the symbol → (plus (symbol) (reg off)) → reload swaps → index first.

Hmm! But hold on: what does simplify_addr do with (plus (symbol) (reg))? It doesn't change it. Then reload's commutative swap put the symbol second.

So the crux is: prevent cse from replacing the base REG with the constant, so that reload sees (plus (reg p) (reg idx)) and keeps the order.

How to prevent? The base must not have a constant equivalent in cse's quantity table. Ideas:
- Make p's set not a constant: e.g. `p = &D_80195AF6[0];` → same constant.
- Make p's *mode* differ at the use: e.g. declare p as `u8 *` but assign `D_80195AF6_t *`? Mode is still 32-bit pointer.
- Use a pointer of a different SIZE? no.
- Have p set to the symbol AND to something else later (so its class isn't "is_const")? Then the value isn't the symbol.

Hmm, what if p is set to the symbol in a way that creates TWO sets: e.g. `p = D_80195AF6;` and later `p = p;`? Identity laundering — not allowed.

What if the pointer is *copied* through another variable: `D_80195AF6_t *q = p;` and then use q? The class would have q and p equivalent to the constant → same folding.

Hmm, what about the *quantity* mechanism: `qty_const` is recorded when the reg's class head is a constant. If the reg has TWO different classes... no.

What if p is assigned the symbol in a *different basic block* or after a call? Doesn't matter.

What if p is a **function-scope static**? no.

Hmm, what about making the pointer's value come from the *symbol's address* computed as a difference? no.

Alternatively: attack from the reload side. The swap happened because reload chose the swapped alternative. What if the tree were (plus (symbol) (reg idx)) but the *symbol* can't be reloaded into a register (e.g. it's a LO_SUM address)? Hmm.

Alternatively, make the address such that the pointer is not the base: e.g. `*(s16 *)((u8 *)off + (u32)(u8 *)p)` → tree (plus (reg off) (symbol))? Hmm — wait, that's interesting! Here the symbol is the SECOND operand (not the base), so cse's simplify_addr doesn't replace anything (the base is off, a non-constant reg) — but the symbol is still a constant in the tree, and reload will need to materialize it into a reg → and the commutative swap might then put the symbol... in the second position (already there) → "addu v0,v0,a1"? Hmm, but wait: which is the "index" and which is the "base" in the MIPS output? For "addu rd, rs, rt", gcc prints the operands in tree order. So (plus off symbol) → "addu v0,v0,a1" (off in v0, symbol in a1) — index first. Still wrong.

Hmm, we want "addu v0,a1,v0" = (plus symbol idx) with the symbol FIRST. So the tree must be (plus (symbol) (reg idx)) AND reload must not swap.

Reload swaps when it thinks the insn compiles better that way — e.g. because the operand that needs a reload should be in the "base" position? Actually the MIPS constraint: for the `addu` pattern (set (reg) (plus (reg) (reg))), both are regs — the commutative pair is (reg, reg). Reload tries both and picks the better allocation. In ours, the symbol operand needed a "reload" (lui+addiu) into a1 and the index was already in v0.

Hmm, in the target, the pointer pseudo also needed a reload (lui+addiu into a1) and the index in v0 — the same situation! Yet the order differs.

So the difference is the tree order at reload entry: target (plus (reg p) (reg idx)) → reload allocates p → a1, keeps order → "addu v0,a1,v0". Ours (plus (symbol) (reg idx)) → the symbol is not a reg; reload must create a register for it; and the swap logic applies to (symbol, reg) pairs? Reload's commutative handling applies to the insn's operands — the insn is `(set (reg 113) (mem (plus (symbol) (reg 118))))` — the MEM's address. Reload decomposes MEM operands into address+offset.

Honestly, the practical difference: in the target the pointer was a REG at reload time.

SO: the question remains how to keep it a reg. The cse quantity mechanism replaces the base reg with its constant.

Hmm, what if the pointer is used in an address where the base is NOT the pointer reg? E.g. `*(s16 *)((u8 *)p + off + 4)` — the base of the MEM address is the whole PLUS. simplify_addr: `base = addr` where addr = (plus (reg p) (reg off))... wait, the constant 4 was folded into the displacement, so addr = (plus (reg p) (reg off)). simplify_addr's cases:
- GET_CODE(addr) == REG → no (it's a PLUS).
- addr == SYMBOL_REF → no.
- addr == CONST with PLUS → no.
- addr == LO_SUM → no.
So simplify_addr returns base = the whole (plus (reg p) (reg off)) — no substitution!

Hmm! But our .cse dump shows (plus (symbol_ref) (reg 118)) — so the substitution DID happen. Where? Maybe not simplify_addr but `fold_rtx`/`simplify_rtx` in cse: cse calls `simplify_rtx` on the MEM? Or `fold_rtx (dest, insn)` (cse.c line ~6985: `dest = fold_rtx (dest, insn);` for MEM destinations) — but our MEM is a source, not a dest.

Hmm, cse also processes the source of each insn: `src = fold_rtx (src, insn)`? Let me check: in cse's main loop, for each insn, it computes `src = fold_rtx (SET_SRC(...))`? Actually cse calls `simplify_rtx`? Let me look for where cse simplifies the source: in cse.c, `if (GET_CODE (x) == MEM) ...`?

The relevant: cse.c has in the main loop:
```c
      /* Simplify the source of the insn */
      ...
```
Let me search cse.c for "simplify_rtx" usage.

Hmm, time is ticking. Let me switch to empirical mode NOW, and use the gcc source only to interpret results.

Let me set up the variant generator + batch scorer, and run ~20 variants for item 80184828.

I'll write a python script that takes the base body and a list of (old, new) replacements, writes each variant to a file, and scores them.

Let me look at the exact base file text first (v1.c).
