---
ts: 2026-11-06T23:49:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n2XQAivzibWmpIpvaVnx
---
So cse makes them equivalent. Then when substituting, it picks the canonical reg (firstr). Hmm.

Then in the target, why did the copy survive? Because the asm insn between: q_old → asm → q_new. Then `p = q_new`. cse equates p and q_new, canonical may be p (longer-lived?) Actually the canonical choice: NEW=p (the copy dest), OLD=q_new. p lives longer (used in store and call) → p becomes canonical? Then the address computation `q_new = &sym` — wait, the address is set BEFORE the asm: `q_old = &D_800C7C60`, asm copies q_old→q_new. cse1 sees q_old = const address (a qty). Then the asm is a barrier. After the asm, q_new is a fresh qty? Actually asm outputs: cse might invalidate. Hmm, asm insns make cse clear the table (they're ASM_OPERANDS, `insn_invalidates`?). If cse clears the table at an asm, then after the asm, `p = q_new` — q_new has no known qty, so make_regs_eqv can't equate (it requires REGNO_QTY_VALID_P(old)); actually q_new would get a new qty from the asm output? 

Whatever the mechanism, the key: the asm breaks the chain so q and p stay separate, and the address is materialized into q_new (v0) then copied to p (a3).

Now: can we get this WITHOUT asm? A real C construct that makes the address computed into one pseudo then copied to another with the copy surviving.

Key insight: cse's canonicalization and combine. If q is a *different mode*? e.g. q is `u32` (integer) holding the address, then `p = (s32*)q`. Still SImode.

What if q is a `s16`? no, address truncation invalid.

What if q's value comes from a memory load? e.g. store &D_800C7C60 into a local array then load it: adds lw/sw (2 extra insns, but we need only 1 extra: the move). Actually the target has exactly one extra insn: `move a3,v0`.

Hmm what if we use a conditional expression to assign q:
```
q = (mode >= 0) ? &D_800C7C60 : &D_800C7C60;
```
No.

Alternative: use the fact that `p` is also assigned 0 in the else branch. In the target, `move a3,zero` at 120c (else branch: p = 0) is in the delay slot of `bltz s3`. So p is set in both arms. 

What if instead of `p = q`, we write the address into p via a *different* pseudo that cse can't equate because it's used across a call? Hmm.

Honestly, let me consider a different approach entirely: maybe there's a way to get the extra `move` from a different source, e.g. a real second assignment to p:
```
p = &D_800C7C60;
p = p;  // identity, no
```

Or maybe: the target's extra move could be produced by making the address computed in a temp used twice:
```
s32 *q = &D_800C7C60;
p = q;
*q = val;
```
That's exactly the launder-free version which folds.

What if we make q used elsewhere too, so it can't be merged? e.g.:
```
s32 *q = &D_800C7C60;
p = q;
*q = val;
```
same.

What if q is assigned from p? `p = &D_800C7C60; q = p; *q = val;` Then the address is computed into p... hmm.

Wait, maybe the trick is the ORDER of the store and the second address. In target:
```
lui v0; addiu v0   (q = &D_800C7C60)
move a3,v0         (p = q)
lui v0; addiu v0   (v0 = &D_800A2E20)
sw s2,0(a3)        (*p = val)
lui at; sw v0,0(at) (D_800C7C64 = ...)
```
Note v0 is reused for the second address. So q dies after the move.

Hmm. What if we restructure: compute both addresses first, then store:
```
s32 *q = &D_800C7C60;
s32 *r = &D_800A2E20;
p = q;
*p = val;
D_800C7C64 = r;
```
Would that create the move? The compiler would schedule.

Let me try a bunch of candidates empirically. It's faster. Let me write several candidate win files in the item dir and score them.

Candidates:
1. `p = q` where q declared as separate u32 var:
```
u32 q = (u32)&D_800C7C60;
p = (s32 *)q;
*p = val;
```
2. Use a 2nd real set of q before the copy:
```
s32 *q;
q = &D_800C7C60;
q = q + 0;  // identity, no
```
3. Dead-reset AFTER:
```
s32 *q = &D_800C7C60;
p = q;
*p = val;
q = 0;
```
4. Dead-reset before via C0414 style.
5. Assign q through a struct/union.
6. Make q a `void*` and p `s32*`.
7. Do `p = &D_800C7C60; *p = val;` and additionally assign q from p: `q = p;` then use q for... no.

Hmm, actually! What about making the *store* go through a second temp:
```
s32 *q = &D_800C7C60;
p = q;
*q = val;
```
vs
```
p = &D_800C7C60;
*q = val;  // q = p
```

Let me look at how the moves.md entries cracked "launder" where the launder was an out-only copy launder (the asm on a reg not from a mask). Looking at moves: `func_8018C2D8 | MATCH — reuse m for next ptr (m = s1+0xD0; dv = m)`. And func_80185944 WALL.

Hmm, let me look at cookbook C0414 to understand dead-reset.
