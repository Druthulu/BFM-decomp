---
ts: 2026-10-22T09:27:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_aW2wndNOIKUXMMYiUocS
---
The standalone case folded the constant into the addressing mode (lh $2,A+4($2)) — different from the real code because there the pointer was also used elsewhere / the load was through a pointer variable in a bigger function.

The standalone experiment isn't representative. I need the real context.

Better approach: iterate on the real body. Each try is ~1s. Let me write a batch scorer and try many spellings of the address expression.

Let me set up a script to generate variants and score them.

Key hypothesis to test: the pointer must be a REG at combine time. Ways to make it a reg lever-free:
(a) Use `p` in two places so that... no.
(b) Make the pointer value come from an expression that's not constant-folded at expand: e.g. `p = &D_80195AF6[0];` same.
(c) Hmm! What about using the *existing* `at` materialization: In the target, the pointer is materialized in a1 at the arm start and reused at the end. In ours, the pointer (symbol_ref) is materialized by reload at the add. Same instruction count.

What if the source had TWO pointer uses such that gcc keeps a pseudo? E.g.:

```c
D_80195AF6_t *p = D_80195AF6;
s16 newval = p[unk100].f0;   /* uses p */
...
D_801270C8 = *(s16 *)((u8 *)p + off + 4);  /* uses p */
```
In our current source, the newval load is written as `D_80195AF6[unk100].f0` (not through p). If we write it through p, then p has 2 uses → gcc keeps p as a pseudo reg (since it's used twice, and reload can reuse the register). Then at the add, the tree would be (plus (reg p) (reg idx)) → pointer first! And the newval load's address would be (plus (reg p) (reg idx)) too → "addu at,at,v0"? Hmm, but then the target's `lui at; addu at,at,v0` shows the symbol materialized separately (at), not a1. If p were in a1, the newval load would use a1 as base: "addu at,at,v0" — no wait.

Hmm, in the target: `lui a1; addiu a1,a1,0` (pointer in a1) at the arm start, and separately `lui at; addu at,at,v0; lh v0,0(at)` (the newval address). So the target materialized the pointer TWICE (a1 and at). That means the two uses are separate expressions (not a shared pseudo) — one is p (used at the end) and the other is the direct array expression.

So the target's structure matches ours: p is a separate variable used once at the end. Yet in the target, the add's pointer operand is a REG (a1) rather than a symbol_ref.

Why? Because in the target, the pointer pseudo was materialized into a1 by reload at the arm start (as the `lui a1; addiu a1` we see), and at the add, reload had already assigned the pseudo to a1, so the tree used (reg a1)?? Hmm — but the RTL at combine time in ours was (plus (symbol_ref) (reg 118)); the symbol_ref came from expand folding p's constant into the address expression.

Hmm! Maybe the difference is: in the TARGET's original source, the final address expression was NOT `(u8*)p + off + 4` but something where the pointer appears as a separate operand, e.g.:

```c
D_801270C8 = *(s16 *)(p + off/2 + 2);
```
Hmm, if p is `D_80195AF6_t *` (element type) then p + off/2... no.

Wait, actually: what if the original was:
```c
D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
identical to ours. Hmm.

But the difference might be in the TYPE of p! In the target's original source, maybe `p` was declared as `u8 *p = (u8 *)D_80195AF6;` hmm same.

Let me think about what makes expand emit (plus (reg p) (reg idx)) vs (plus (symbol_ref) (reg idx)). Expand emits the constant directly when the pseudo's value is a constant AND the pseudo is not address-taken etc. Expand's `expand_expr` on `p + off`: it looks up p's reg in the "constant" table (expand does constant folding via `cse`? no — expand uses `get_mode`...). Actually expand replaces a pseudo reg with its constant value only if the reg is `reg_constant`... In gcc 2.7 expand, there's `expand_expr` handling REG: it checks `REG_CONSTANT`? Hmm, expand has:

```c
    case REG:
      ...
      /* If the variable is a constant, ... */
```
Yes: expand's REG case has code that looks up the constant value of the pseudo (via `reg_constant_rtx` / `cse`?) — in gcc 2.7 `expand_expr` REG case:

```c
      /* If this is a hard register, ... */
      if (GET_CODE (x) == REG && ... )
```
Hmm, in gcc 2.7 there's the "expand_expr: REG" case which does:
```c
	  /* If we have a variable that is not a register, ... */
```
I believe expand does substitute constants for pseudos (via `cse`? no, via `reg_equiv`? no) — actually it's `expand_expr`'s REG case that checks `CONSTANT_P`? There's `reg_constant` handling in expand: gcc 2.7's expand.c has:

```c
    case REG:
      ...
      /* Handle the case of a pseudo-register with a constant value... */
```
Hmm.

Whatever: empirically, in our compile the pointer became a symbol_ref in the plus at expand time, and combine swapped it. In the target's compile, the pointer stayed a reg. What could make expand keep the pseudo?

If the pseudo has MORE THAN ONE use, expand keeps it (it needs the reg). If p were used twice (e.g. also in the newval load), then p's pseudo would be a real register and the tree at the add would be (plus (reg p) (reg idx)) → pointer first! But then the newval load would ALSO use (reg p) → "addu a1,at,v0"? no, the newval load's address would be (plus (reg p) (reg idx)) → the compiler would compute the address into a reg: "addu at,a1,v0" instead of "lui at; addu at,at,v0" → different instruction count (lui+addiu vs just addiu) → score would change from 1 to ~2-3 (extra lui). Hmm, but actually gcc might reload the symbol into `at` anyway.

Wait, but the target DOES have `lui at; addiu at,at,0; addu at,at,v0` — i.e. the newval address materialized the symbol into `at` — that means the newval expression used a symbol_ref (folded at expand) and the reload created `at` for it. And the final add used a1 with the pointer as a reg.

So in the target: one use folded to symbol_ref (newval), the other kept a reg (the final add). What distinguishes them? The final add's pointer use is inside a larger expression `(u8*)p + off + 4` — hmm.

OH WAIT. I bet I know! In the target, the final address might be computed as `(u8 *)p + off + 4` where `off` is a *variable* and `p` is a variable — and the whole thing is a MEM address: (mem (plus p (plus off 4))). Expand would emit (plus (reg p) (plus (reg off) 4))? and then the constant 4 folds into the mem displacement: (mem (plus (reg p) (reg off))). Then combine sees (plus (reg p) (reg off)) — p's reg_equiv is the symbol → combine substitutes? Combine does NOT substitute reg_equiv into trees (that's cse's job? no — combine's `reg_equiv` handling: combine does use `reg_equiv` for constants? There's `reg_equiv_content`/`reg_equiv` used by combine to replace a reg with its constant value — yes, combine has code:

```c
  /* If we have a constant, ... */
  if (GET_CODE (x) == REG && ...)
```
Hmm.

Our rtl dump shows the symbol_ref already in the plus at expand time (before combine), so expand did the substitution. So in the target's compile, expand did NOT substitute for the final add but DID for the newval load. Both use the same constant address!

Difference: the newval load's address = symbol + idx (a plain address), the final = symbol + idx*8 + 4.

Hmm, so expand's substitution depends on the expression shape. What if the final address in the original source was NOT `(u8*)p + off + 4` but something like:

```c
D_801270C8 = *(s16 *)(p + off + 4);   /* p as u8* */
```
Hmm.

Honestly: the fastest path is to try spellings in the real body. Let me set up a fast batch loop with many variants:

Variant family for the final load, keeping everything else:
1. `*(s16 *)((u8 *)p + off + 4)` (current) → 1
2. `*(s16 *)((u8 *)p + off + 4)` with off = `((Unkstruct_800B5CB8 *)a0)->unk100 * 8` inline
3. `*(s16 *)((u8 *)p + (off + 4))`
4. `*(s16 *)((u8 *)p + 4 + off)`
5. `*(s16 *)((u8 *)p + off) ` with off = unk100*8+4 (folded into off)
6. Using `p` twice: newval through p: `p[unk100].f0` and final through p
7. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` where p is `u8 *` type
8. off as u32
9. Compute address in a temp: `u8 *pa = (u8 *)p + off; D_801270C8 = *(s16 *)(pa + 4);`
10. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with the load written as `*(s16 *)(void *)((u8 *)p + off + 4)`.

Also: maybe the whole arm could be restructured so that p is used twice.

Let me check the target asm count of lui/addiu pairs for D_80195AF6: at 2c0c (lui a1), 2c10 (addiu a1), 2c14 (lui at), 2c1c (LO16 at) — so `at` = symbol + v0 with NO addiu at! Interesting: `lui at; addu at,at,v0` — the LO16 relocation is on the lh at 2c1c. So `at` = (symbol + v0) where symbol's low part is 0 → lui at,%hi(sym); addu at,at,v0 — the low 16 bits are added via the displacement? Since D_80195AF6's low is 0, the LO16 is 0 and the relocation is attached to the lh instruction. OK.

So in the target the two materializations are: a1 = symbol (lui+addiu) and at = symbol (lui, no addiu since lo=0... but the reloc is there; gcc emitted lui at + addu at,at,v0 with the lo part folded as 0? The LO16 reloc on the lh means the lh's displacement is the low part of the symbol).

Fine.

Now let me check OUR asm for the same region to see what we produce. Let me dump our candidate object's asm for func_80184828.

Let me write my own objfn-like script under the shard: takes itemdir + body → objdump of cand.o → function asm.

Actually simpler: I can compare asm text directly. Let me do it.
