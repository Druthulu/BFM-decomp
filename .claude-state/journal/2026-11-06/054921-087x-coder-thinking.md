---
ts: 2026-11-06T12:49:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6asEyQdagKQydTlYq4ln
---
`Unkstruct_800B5CB8.unk10A` is s16.

So the store `unk10A = idx` (idx u16) → store HImode; the load `unk10A * 2` → s16 sign-extended.

Now: lever-free, to break cse's forwarding, make the store's value type differ from the load's: e.g. declare `idx` as `s16`? Then the store is s16→s16, still the same value.

Hmm, cse's forward: it records the stored value's equivalence with the load. Since both are HImode regs, the equivalence holds.

To break it: make the store truncate: e.g. store a *wider* value into the HImode field: `((Unkstruct*)param_1)->unk10A = (s32)idx;` — the store of a s32 into an s16 field emits `sh` of the low half; the RTL store value is `(subreg:HI (reg idx) 0)` — same as before. cse: the load is HImode → equal to the subreg → forward again.

What if the store value is a *different* pseudo: `s32 tmpv = idx; unk10A = tmpv;` — then the store's value is `(subreg:HI (reg tmpv))`; the load's result is HImode. cse would equate the load with the subreg of tmpv; then the multiply uses `(sign_extend:SI (subreg:HI (reg tmpv) 0))`. If tmpv is known to be a u16 (zero-extended), the sign_extend of a zero-extended value... The target needs `lh` (a real memory load), so we need cse to NOT forward.

How about making the value stored a *constant-folded* expression of idx that cse can't equate? E.g. `unk10A = idx + 0;` — folds.

Alternatively: make the load's address differ from the store's by an expression cse won't fold, e.g. using a different base register... 

What if the reload is done through a `u16 *` local that is initialized from the struct pointer *after* the store:
```
u16 *pp = &((Unkstruct *)param_1)->unk10A;   /* extra insn? */
```
gcc would fold `&x->f` to param_1+266 → the address is computed into a pseudo (addiu a0,s1,266 — extra insn, but maybe reused? The target has no addiu).

Hmm.

What about a completely different approach to break cse: an intervening *call*? No.

What about `func_8001C2C4(...)` — that call is later.

OK, at this point I've spent ~20 min on item 2 (05:30-05:50) with 44 best and 40+ tries. The remaining gap needs two levers (idx ref count + cse memory clobber) which the asm provided.

Hmm, but wait: maybe I should check whether the cse forward is actually happening because of the *do-while* blocks I added (they split cse EBBs — which can either help or hurt). In the ORIGINAL (with asm), the reload is kept because of the memory clobber.

Let me try one specific lever-free idea for the memory-clobber replacement: move the `D_801F32D0 = 0;` store to BETWEEN the unk10A store and the tmp2 load. In the target, `sh zero,0(at)` is at 1c64, before the store at 1c74. But maybe sched2 would move it back? Let me try: in the C, `D_801F32D0 = 0;` is before the block. Move it after the `unk10A = idx;` statement:

```
{
    u16 idx = D_801ED4B4[i70a];
    ((Unkstruct *)param_1)->unk10A = idx;
    D_801F32D0 = 0;
    tmp1 = D_801ED5F0[idx * 2];
    tmp2 = D_801ED5EC[...unk10A * 2];
}
```
A real store between them invalidates cse's memory table (a store to a scalar global might not invalidate a struct store→load? In cse.c, invalidate_memory: a store to a non-struct scalar invalidates only entries that could alias. In 2.7.2 cse, the memory table is invalidated by stores based on `struct_equiv`: a store to a scalar does NOT invalidate a "struct" entry? Hmm, actually it's the reverse: a store to a MEM_IN_STRUCT only invalidates struct entries; a store to a non-struct (like D_801F32D0) invalidates everything? Let me look at cse.c's invalidate_memory.

Actually, in cse.c 2.7.2:
```
static void
invalidate_memory (x, write)
{
  ...
  /* If X is a struct member, we don't need to invalidate anything else */
```
Let me grep.
