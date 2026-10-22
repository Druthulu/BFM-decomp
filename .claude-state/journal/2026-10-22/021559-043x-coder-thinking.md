---
ts: 2026-10-22T08:15:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_5RBAVzxRpSHGb2UulxWV
---
EXCELLENT! w4 shows:
```
lh v0,0(a0)
nop
beqz v0,2c
move v1,v0     <- THE COPY SURVIVED!
addiu v1,v1,-1
```
The s16 temp trick WORKS — the copy `move v1,v0` survived, and NO sign extension insns!

w2 (without the branch) → the copy died (cse merged, since both in the same block and the copy's dest didn't conflict).

w4 has the branch: the copy `u = tmp` is in the entry block, and the use `u = u - 1` is in the then-block → different blocks → and the s16 temp escapes cse's equivalence class.

Hmm, actually in w4 the structure is: `tmp = (short)t; u = tmp;` then `if (t) u = u - 1;`. The copy `u = tmp` is in the entry block; the use in the then block. So the copy survived due to the block split (or the s16 escape).

Wait, in w2 the same two statements are in the same block as the use → the copy died. So the s16 trick alone didn't save it there — the block split did. Hmm, or the combination.

Hmm, but in our real function (c5), the copy `u = t` was in the entry block and the use in the else block, yet the copy died. The difference: in c5 the copy was a plain s32 copy (cse propagated it across blocks — reg_equiv_content is global), while in w4 the copy went through an s16 temp (cse's HImode equivalence class doesn't apply).

So: the s16 temp is what makes the copy escape cse.

Now let me apply this to 80182ED4:

```c
} else {
    s16 tmp;    /* hmm, needs to be declared at function scope in C89 */
    tmp = (s16)t;
    u = tmp;
    t = u - 1;
}
```
Hmm, but in the target the copy is `or v1,v0` and the addiu is `addiu v0,v1,-1`. In w4, we got `move v1,v0` + `addiu v1,v1,-1` (the addiu wrote into v1!). Hmm, because in w4 `u = u - 1` (u is both src and dst) → the same reg. In our case `t = u - 1` (different vars) → `addiu v0,v1,-1` ✓.

Now, about the sign extension: in w4, `u = tmp` where tmp is a short holding the sign-extended value → the sign extension was folded away. Why? Because `tmp = (short)t` where t came from `lh` — gcc knows the value fits in short exactly, so the round trip is a no-op. gcc's combine: `(sign_extend:SI (reg tmp))` where tmp was set by `(sign_extend:HI (reg t))` → hmm, combine folded it.

Actually, in w4 the tmp assignment `(short)t` → the RTL is `(set (reg tmp) (truncate:HI (reg t)))`? Hmm, but gcc's convert for a signed narrow destination: `(sign_extend:HI (reg t))` — the reg holds the sign-extended 16-bit value. Then `u = tmp` → `(set (reg u) (sign_extend:SI (reg tmp)))` → combine: sign_extend:SI of sign_extend:HI(t) → combine's rule: "if we are sign extending a value that is already sign extended, we can drop it" — hmm, combine would need to know tmp's mode is HI and that the extension from HI to SI is...

Actually! gcc's convert.c `sign_extend(mode, x)`:
```c
rtx
sign_extend (machine_mode mode, rtx x)
{
  int wordsize = GET_MODE_BITSIZE (mode);
  if (GET_MODE (x) == mode) return x;
  ...
  /* If X is a sign extended narrow value, don't extend it twice. */
  ...
  return gen_rtx_SIGN_EXTEND (mode, x);
}
```
Hmm, but the key: `sign_extend(SImode, x)` where x is `(sign_extend:HI (reg t))` → gcc's convert.c has:
```c
      /* If we are sign extending a value that is already sign extended
	 (i.e. a SIGN_EXTEND of a narrow value), we can just use it. */
```
I'm fairly confident gcc has this (it's the standard "sign_extend of sign_extend" simplification in convert.c:
```c
rtx
sign_extend (machine_mode mode, rtx x)
{
  ...
  if (GET_CODE (x) == SIGN_EXTEND && GET_MODE (x) == mode) ...
```
Hmm.

Whatever — empirically it works! The `lh` value's round trip through a short temp is a no-op.

Now let me apply it to the real function. The shape:

```c
void func_80182ED4(s32 arg0) {
    s32 t;
    s32 u;
    s16 tmp;
    ...
        } else {
            tmp = (s16)t;
            u = tmp;
            t = u - 1;
        }
```
Hmm, but wait: in w4, the copy `u = tmp` was in the entry block and the use in the then-block. In our case, the copy `u = tmp` and the use `t = u - 1` are BOTH in the else block. In w2 (same block), the copy died!

Hmm. So I need the copy in a different block from the use, OR the s16 escape alone suffices.

Hmm, in w2 the copy died. But maybe in w2 the reason is different: in w2 the sequence was `tmp = (short)t; u = tmp; return u - 1;` — all in one block. The copy `u = tmp` is a copy from a QImode pseudo (tmp) to an SImode pseudo (u) — that's `(set u (sign_extend:SI (reg tmp)))` — NOT a plain reg copy! So cse doesn't propagate it. Yet the copy disappeared → so it was combine/local_alloc that eliminated it (combine folded the sign_extend into the use → `addiu v0,v0,-1`).

In w4 (different blocks), the copy survived → because combine couldn't fold the sign extension into the use (the use is in a different block!). Combine works within a block → it couldn't propagate the sign_extend into the use in the other block → so the copy stayed as a separate insn → and the sign extension... hmm, but the sign extension still has to materialize somewhere! In w4's output there's no sll/sra. So the sign extension was folded into the copy `move v1,v0`??

Hmm: `u = tmp` where tmp is a short → the value is sign_extend(tmp). The copy `or v1,v0` — for that to be correct, v0 must already hold the sign-extended value. And v0 = t = the lh result = already sign-extended! So `or v1,v0` is correct ✓ and gcc knew the sign extension was redundant (because tmp = (short)t and t was sign-extended).

So gcc's combine figured out that tmp's value = t's value (the sign extension is a no-op) → the copy became `or v1,v0` → and since v0 already has the sign-extended value, no extra insns. And the copy stayed in a different block from the use → cse/combine couldn't merge it.

So the KEY for our case:
1. The copy must be in a different basic block from its use (so combine can't fold the conversion into the use).
2. The value must round-trip through the s16 temp without a net conversion (true for a sign-extended s16 value).

In our function, the else arm is a separate block from... hmm, the copy `u = tmp` and the use `t = u - 1` are in the SAME block (the else arm).

Hmm! But in w4 the copy was in the entry block. Let me restructure our function so the copy is in the entry block and the use in the else block:

```c
t = unk84;
tmp = (s16)t;    /* hmm, this is the copy... */
u = tmp;         /* the copy */
if (t == 0) { ...; t = 0x1E; }
else { t = u - 1; }
```
Hmm, but then u is live across the calls in the if-branch → callee-saved reg issue (as discussed). Hmm, but w4's structure had the copy in the entry block and the use in the then-block, with no calls.

Hmm, in our case the calls are in the OTHER branch (t==0). u is dead on that path. But u is live at the branch point... and the calls are inside the t==0 block where u is dead. So u doesn't need to be callee-saved. But local/global alloc: u is a global pseudo (live across the branch) → global_alloc. global_alloc gives globals callee-saved regs preferentially, but it does consider whether the pseudo is live across a call. Hmm, in gcc 2.7's global_alloc, the "live across calls" analysis: a pseudo is live across a call if it's live at the call. u is dead in the t==0 block → not live at the calls → OK.

Hmm, but global_alloc might still give u a callee-saved reg because globals are allocated from the "global register" set... Actually gcc's global_alloc allocates a pseudo to a hard reg considering "REG_ALLOC_ORDER" and whether it's live across calls ("across_call" flags). If a global pseudo is not live across calls, it can get a call-clobbered reg.

Hmm, risky. Let me just TEST it.

Actually, better: let me test the exact structure in the real function. Variants:

c6:
```c
        t = ((Unkstruct_80182ED4 *)arg0)->unk84;
        tmp = (s16)t;
        u = tmp;
        if (t == 0) { ...; t = 0x1E; }
        else { t = u - 1; }
```

c7: keep the copy inside the else arm but split the block with a goto:
```c
        } else {
            tmp = (s16)t;
            u = tmp;
            goto lab;
        }
        lab: t = u - 1;
```
Hmm, the label placement: the `if (t==0)` branch falls through to... let me structure:
```c
        if (t == 0) {
            ...
            t = 0x1E;
            goto lab2;      /* hmm */
        } else {
            tmp = (s16)t;
            u = tmp;
            goto lab;
        }
        lab:
        t = u - 1;
        lab2:
        unk84 = t;
```
Messy. Let me first try c6 (the hoisted copy) and c8 (the copy in the else arm but with the USE in a separate block via a goto).

Actually, hmm, wait. Let me reconsider: is the "different block" really needed? Let me test the exact else-arm shape in my harness:

```c
int w5(int *p) { short tmp; int t; int u; t = *(short *)p; if (t == 0) { t = 30; } else { tmp = (short)t; u = tmp; t = u - 1; } return t; }
```
This has the copy and the use in the same block (the else). Let me test it — maybe the s16 escape alone is enough (combine might not fold the conversion into the use because the copy's SOURCE is a QImode reg and combine can't fold `sign_extend:SI` into the use... hmm, it did in w2).

Let me test w5 and w6 (hoisted).

Let me run.
