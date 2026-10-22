---
ts: 2026-10-22T09:45:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ploPaXqXjYVAqQ8tO2Fx
---
Now write the variants spec for item 80184828. Base = v1.c.

Key text anchors in v1.c:
- `            D_80195AF6_t *p = D_80195AF6;`
- `            s16 newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;`
- `                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;`
- `                D_801270C8 = *(s16 *)((u8 *)p + off + 4);`
- `    s32 off;`

Variants:
1. p2: newval through p → `s16 newval = p[((Unkstruct_800B5CB8 *)a0)->unk100].f0;`
2. p3: `u8 *p = (u8 *)D_80195AF6;` + load `(p + off + 4)`
3. p4: load `((u8 *)p + (off + 4))`
4. p5: load `((u8 *)p + 4 + off)`
5. p6: `u32 off;` (decl) + `off = ... * 8;`
6. p7: `off = ... << 3;`
7. p8: temp pointer: replace the load line with two lines:
   `                u8 *pa = (u8 *)p + off;\n                D_801270C8 = *(s16 *)(pa + 4);`
8. p9: p assigned (not initialized): decl `D_80195AF6_t *p;` at top + in arm `p = D_80195AF6;`
9. p10: index inline in the load, no off variable:
   `                D_801270C8 = *(s16 *)((u8 *)p + ((Unkstruct_800B5CB8 *)a0)->unk100 * 8 + 4);` and remove the off assignment
10. p11: load via `*(s16 *)((u8 *)p + off + 4)` with `off` moved to decl-init? e.g. `s32 off = ...` hmm off is assigned conditionally.
11. p12: pointer arithmetic with the struct type: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` → `D_801270C8 = *(s16 *)(p + off/8 + 0);`? semantics: p is D_80195AF6_t* (8 bytes) → p + off/8 gives the element; but we want byte offset off+4 → not expressible. Skip.
12. p13: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with p declared as `void *p`? then (u8*)p cast — the set would be (set (reg p) (symbol)) with mode Pmode... void* is a pointer, same.
13. p14: the pointer assigned from a *cast of an int*: `D_80195AF6_t *p = (D_80195AF6_t *)(s32)D_80195AF6;` — hmm, D_80195AF6 is an array symbol; casting to s32 then to a pointer. gcc 2.7 may reject "pointer from integer" without a cast — we have the cast. This might produce a different tree (the symbol in integer mode) → maybe the address keeps the reg!
14. p15: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with the load written as `*((s16 *)((u8 *)p + off + 4))`.
15. p16: newval through p AND the final through p (same as p2).
16. p17: off as `s32` but the load as `*(s16 *)((u8 *)p + (off + 4))` (already p4).
17. p18: declare p at function top and assign in the arm (p9).
18. p19: use a *local array* trick? skip.
19. p20: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with `off` declared as `u32` and assigned `off = (u32)((Unkstruct_800B5CB8 *)a0)->unk100 * 8;`

Let me also try:
20. p21: swap the operand order in C: `D_801270C8 = *(s16 *)((u8 *)off + (u32)(u8 *)p);` — hmm, (u8 *)off is an int-to-pointer cast; the sum (u8*)off + (u32)p → the tree (plus (reg off) (reg p)) — with p as a reg → but then the base is off... the tree order would be (plus off p) → index first → wrong. But worth testing: maybe cse/reload reorders.

Hmm, what about making the pointer the SECOND operand in C but with the symbol substituted by cse: (plus (reg off) (symbol))? Then simplify_rtx's rule: XEXP(x,0) = reg (not constant), XEXP(x,1) = symbol → the second condition: GET_RTX_CLASS(GET_CODE(XEXP(x,0))) == 'o' (reg is class 'r'? no: REG is class 'r') hmm. The rule swaps only if the FIRST operand is a constant or a complex expression. With (reg, symbol) neither triggers → no swap → the tree stays (plus off symbol) → the asm would be "addu v0,v0,a1" (index first) — wrong.

So we need (plus (something-not-constant) idx) with the pointer first. The pointer must be a REG.

So the crux is really: keep p as a reg.

Let me now test the "p used twice" hypothesis (p2) — if the newval goes through p, the count might change but the final add might become pointer-first, confirming the mechanism. Then I can think about how to keep 2 uses without changing the asm.

Hmm, here's an idea for a second use that produces the SAME asm: use p for the newval load AND keep the symbol for the newval?? no.

Alternative idea: make the pointer's value not a constant *at expand* by initializing it from a *conditional expression* that gcc folds late? Hmm.

Alternative: use p in the final address and ALSO in a *store* of the same value: e.g. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` and somewhere `*(s16 *)((u8 *)p + off + 4) = ...`? no, that changes semantics.

Hmm, what about the *index*: what if the scaled index is not a shift but a MULT in the tree? Then simplify_rtx's swap: XEXP(x,0) = symbol (constant) → swap anyway. The swap depends only on the first operand being a constant. So the only way is a REG first operand.

Hmm, unless the first operand is a *complex expression* (class 'o') — then the swap also happens. So the first operand must be a simple REG (class 'r') or a LABEL_REF etc.

So: the address tree must be (plus (reg) (reg)) at combine time.

Now, how did expand produce (plus (symbol_ref) (reg 118))? Because p's value is a constant and expand substituted it. In gcc 2.7's expand.c, the substitution of a constant pseudo into its use happens in `expand_expr` case REG:

I'm now fairly sure expand.c has this code:

```c
    case REG:
      /* ... */
      if (GET_CODE (x) == REG && REGNO (x) >= FIRST_PSEUDO_REGISTER)
	{
	  /* ... */
	}
```

Let me think about the actual gcc 2.7.2 expand.c REG case... I recall:

```c
    case REG:
      /* If this is a hard register, ...  */
      ...
      /* Handle the case of a variable that is a constant: this is
	 the case for a variable that is initialized with a constant
	 and never changed.  */
```
Hmm, in gcc 2.7 there's `expand_expr`'s:

```c
    case REG:
#ifdef HAVE_cc0
      if (GET_CODE (x) == REG && GET_MODE (x) == CCmode) ...
#endif
      /* ... */
      return x;
```

Honestly, I recall that gcc's *front end* (c-type.c) does the substitution for local variables: in `expand_expr` (c-type.c) for a VAR_DECL, it looks up the "declared" tree. No constant folding there.

Alternatively the substitution is done by expand's `expand_assign` → it creates a pseudo and a set; then in `expand_function`, at the end, there's a pass "remove_dead_vars"? Hmm.

WAIT. Maybe it's not expand at all: maybe the .rtl dump is printed AFTER cse! Let me check toplev.c: where is rtl_dump_file printed? Let me grep "rtl_dump_file" usage.

From the earlier grep, rtl_dump_file appears at 909 (flush) and 2045 (open). The print must be elsewhere: maybe in cse.c or in function.c: `dump_rtl (rtl_dump_file, insns)`. Let me grep the whole reference for "rtl_dump_file".
