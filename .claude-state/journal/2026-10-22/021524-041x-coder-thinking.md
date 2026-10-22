---
ts: 2026-10-22T08:15:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OqAWWzx1N7zIaAJ2EAa6
---
PERFECT! The trick: route the copy through an s16 temp:

```c
s16 t;
t = (s16)v0;   /* the truncation escapes cse */
v1 = t;        /* the copy survives */
```

And "the sign-extend of the s16 temp is folded back into the same instruction stream" — so gcc folded the sign extension away! Because... hmm, in that case the value must have had a known range, OR gcc's combine folded `s16 tmp; tmp = v0; v1 = tmp;` into `v1 = v0` with the sign extension folded because v0's value fits.

Hmm, wait: "the sign-extend of the s16 temp is folded back into the same instruction stream". So the result was `move v1,v0` — the sign extension didn't materialize. How? Because combine could determine that v0's value fits in 16 bits? Or because the sign-extension of the s16 temp was recognized as redundant?

Hmm! Here's the thing: gcc's expand for `tmp = (s16)v0` → `(set (reg tmp) (sign_extend:HI (reg v0)))`? And then `v1 = tmp` → `(set (reg v1) (sign_extend:SI (reg tmp)))`. combine: `(sign_extend:SI (sign_extend:HI v0))` → combine has a rule to simplify nested sign extensions: `(sign_extend:SI (sign_extend:HI x))` → hmm, combine's simplify_expr for SIGN_EXTEND:
```c
    case SIGN_EXTEND:
      ...
      /* If we are sign extending a sign extended value, ... */
```
Hmm, gcc's convert.c `sign_extend(SImode, sign_extend(HImode, x))` → gcc's convert has:
```c
rtx
sign_extend (machine_mode mode, rtx x)
{
  ...
  /* If X is a constant... */
  ...
}
```
Hmm.

But regardless — the G06 note says it WORKED: score 0. And the mechanism: "the HImode copy escapes cse's equivalence class, so v1 keeps its own register and the `move v1,v0` survives; the sign-extend of the s16 temp is folded back into the same instruction stream."

Hmm, "the sign-extend of the s16 temp is folded back" — I think what happens is:
- `tmp = (s16)v0` → the RTL: `(set (reg tmp) (sign_extend:HI (reg v0)))`? or `(set (reg tmp) (truncate:HI (reg v0)))`?
- `v1 = tmp` → `(set (reg v1) (sign_extend:SI (reg tmp)))`.
- combine: `(sign_extend:SI (sign_extend:HI v0))` → hmm.

Actually maybe gcc's expand for the assignment `tmp = (s16)v0` where tmp is s16 produces `(set (reg tmp) (truncate:HI (reg v0)))` — hmm, no: assigning an s32 to an s16 var in C truncates → the value stored is the low 16 bits → `(set (reg tmp) (truncate:HI (reg v0)))`? But then when tmp is READ as s16, the sign extension happens at the read: `(sign_extend:SI (reg tmp))`.

So `v1 = tmp` → `(set (reg v1) (sign_extend:SI (reg tmp)))` where tmp holds the truncated value. combine would emit the sign extension as sll/sra... unless combine can see that tmp's value is the sign extension of v0's low 16 bits and v1's use...

Hmm, but G06 says the sign extension was "folded back into the same instruction stream" — maybe meaning it merged with other insns.

Hmm, but crucially, G06's score was 0 — byte-identical. So the `move v1,v0` appeared with NO sign-extension insns. So the sign extension was fully eliminated.

How? If v0's value is known to fit in 16 bits with the sign bit 0 → combine folds. In G06's func_8017E204, the value probably came from a u16 field or was masked.

For OUR case, t = lh (sign-extended s16) → the value fits in s16 EXACTLY (it's a sign-extended 16-bit value). So `(s16)t` = t exactly, and `u = tmp` where tmp is s16 → the sign extension of tmp = the sign extension of t's low 16 = t (since t is already sign-extended). So the sign extension is REDUNDANT — but does gcc KNOW that?

combine's nonzero_bits: t's bits 16-31 are unknown (a MEM load). Hmm. BUT combine might handle the `lh` load specially! gcc 2.7's combine.c has:

```c
    /* If we have a sign extension of a value that is known to be sign
       extended already (e.g. the result of a sign extending load), ... */
```

Hmm, actually gcc's `nonzero_bits` for a MEM: gcc 2.7's combine has `known_zero`/`nonzero_bits` handling for `(mem (reg) const)` with a KNOWN CONSTANT ADDRESS! `D_801xxxx` globals! But our load is `132(s0)` — a variable address. ✗

Hmm. But maybe combine handles it differently: combine's `simplify_expr` for SIGN_EXTEND:
```c
    case SIGN_EXTEND:
      if (GET_MODE (x) == mode) return x;
      ...
      /* If we know that the value being extended is already extended... */
```
Hmm.

Let me just TEST it in my harness! I have the fast compile loop. Let me test:

```c
int w1(int t) { s16 tmp; unsigned u; tmp = (s16)t; u = tmp; return u - 1; }
```
and see the asm. But my harness's `t` is a parameter (hard reg) — that changes things (the hard-reg rule would keep the copy anyway). Let me use a memory load to mimic:

```c
int w2(int *p) { s16 tmp; int t; unsigned u; t = *(short*)p; tmp = (s16)t; u = tmp; return u - 1; }
```

Let me test that. If it gives `or v1,v0` + `addiu v0,v1,-1` → the trick works!

Let me also test the exact 80182ED4 shape.

Let me run.
