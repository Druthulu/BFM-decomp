---
ts: 2026-10-22T08:22:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Z1jJtZ33huUYVcCS9cja
---
c11 (u16 temp) gives the same diff — no andi! So the zero-extension WAS free (gcc knew the value's high bits, or it folded). But the compare still reads v1.

Interesting: with the u16 temp, gcc still substituted. So the "c ≠ v" hope failed — gcc must have known the value's high bits are zero?? Hmm, or it folded the u16 truncation of a sign-extended lh... hmm, that would be lossy. Hmm, but no andi appeared, so gcc must have proven the high bits are zero — which would be WRONG for a negative value! Hmm, unless gcc proved v's high bits are... hmm.

Hmm, wait: maybe gcc's `lh` gives a value whose high bits are the sign, and (u16)v truncates → the andi would be needed. But no andi appeared. So gcc must have used a different mechanism... Hmm, maybe gcc's expand for `(u16)v` where v is a pseudo → `(truncate:HI (reg v))` and then `c = tmp` → `(zero_extend:HI (reg tmp))` → combine: zero_extend:HI of a HI reg → free ✓ → so c = tmp = v & 0xffff. And the andi... the truncate of v to HI → the value in tmp's reg = v's low 16 bits. Since tmp is a QImode pseudo, gcc assumes the low 16 bits are the value — but the register physically holds the sign-extended value, so the low 16 bits are correct ✓ and no andi is needed! (gcc's QImode convention: the value is in the low bits; the truncation of a 32-bit reg to 16 bits is free for a pseudo since the pseudo's reg holds the value in the low bits — but that's only valid if the upper bits are don't-care... and they are, for a QImode pseudo.) ✓

So `tmp = (u16)v` is FREE (no insn) and `c = tmp` is a zero-extension which is ALSO free (a QImode pseudo's reg holds the value zero-extended? hmm, for a u16 → the reg holds it zero-extended ✓ since gcc's QImode convention for unsigned is zero-extension).

So `c = tmp` where tmp is u16 → c = zero_extend(tmp) = tmp's value (0..65535) — which differs from v for negative v! Hmm, so the semantics changed. But gcc doesn't care (it doesn't track the sign).

Anyway: the compare still reads v1 (the copy's reg). Because gcc still knows c ≡ v? Hmm, with the u16 temp, c = v & 0xffff ≠ v for negative v. But gcc's combine might have concluded the values are the same because it folded the truncation as a no-op (treating tmp's reg as holding v's low 16 bits, and c = tmp zero-extended = v's low 16 bits ≠ v). Hmm, but then the subtraction `v = c - 0x200` would use c's (truncated) value → the asm `addiu v0,v1,-512` uses the full 32-bit v1 which holds... hmm.

Anyway, the compare still reads v1.

OK. Let me try the opposite: make the copy's value provably DIFFERENT so the compare keeps v. Since gcc's model of the QImode value makes c == v (it thinks the truncation is free), maybe using an `s16` temp makes c = sign_extend(v's low 16) and gcc knows v's high bits are the sign → hmm.

Hmm, both give the substitution.

Let me try to think about it from a different angle: maybe the substitution is NOT cse but **combine's "prefer the copy's dest"**. In combine, when a copy `(set c v)` exists and c is used once, combine can replace c's use with v. That's the opposite direction (it would kill the copy). But we observe the compare's use of v replaced by c.

Hmm! Actually, maybe it IS the reverse: combine replaced the compare's `v` with `c` because... hmm, combine works on insns and rewrites operands to the "canonical" value.

Hmm, combine's `simplify_expr`/operand rewriting uses `reg_equiv_content`? no, that's cse.

OK: cse's reg_equiv_content[v] = ? cse processes `tmp = (s16)v` → hmm, that's not a reg copy (it's a conversion) → cse might still set reg_equiv_content[tmp] = v? cse's make_regs_eqv is called for `(set (reg) (reg))` patterns only. For a conversion, cse does nothing.

Then `c = tmp` → `(set (reg c) (reg tmp))` → make_regs_eqv(c, tmp) → reg_equiv_content[c] = tmp. Now, since tmp is dead after this insn (its only use is this copy) and c is live → cse's REVERSE rule: "if the source is dead and the dest is live, rewrite the source's uses to the dest" — tmp's uses = this copy → so the copy becomes `c = c`?? That would delete the copy. But the copy survived.

Hmm, alternatively cse's rule: "reg_equiv_content[c] = tmp" and then when cse sees the compare's use of v, it checks reg_equiv_content[v] — which is 0 (no equivalence) → no rewrite. Hmm.

So the rewrite of v → c in the compare didn't come from cse.

**It must be COMBINE.** combine's rule: when combine sees `(set c tmp)` and knows tmp ≡ v (via the truncation fold), combine can rewrite the compare's operand v → c if c is "cheaper" (fewer refs or a better reg). combine's `simplify_expr` for the compare's operand: it looks for a cheaper equivalent reg.

Hmm, in gcc's combine there's a step: "if the operand is a reg that is set by a copy, use the copy's dest if the dest has fewer references" — the classic "copy propagation in combine" that prefers the reg with fewer refs. c has 1 ref, v has 2 → combine picks c ✓!!

So: if v had FEWER refs than c, combine would pick v ✓.

So: **reduce v's refs or increase c's refs.**

v's refs: the copy's RHS (1) + the compare (1) = 2. Hmm, can we reduce? The copy's RHS is tmp, not v! So v's refs = 1 (the compare) + the truncation's RHS (1) = 2.

c's refs = 1 (the subtraction).

Hmm, so c (1 ref) beats v (2 refs) → combine picks c.

To make combine pick v, v must have ≤ 1 ref, or c must have ≥ 2 refs.

Hmm! What if the copy's RHS is NOT derived from v but from tmp, and v has only ONE ref (the compare)? Then v has 1 ref and c has 1 ref → a tie → combine's tie-break? Hmm.

v's refs: the truncation `tmp = (s16)v` uses v, and the compare uses v → 2 refs.

To get v down to 1 ref, the truncation's source must not be v. But then the copy's value wouldn't be v's ✗.

Hmm, alternatively increase c's refs to 2: use c twice in the subtraction!
```
v = c - 0x200;
```
→ 1 ref. What if:
```
v = (c - 0x200);
```
Hmm. What about `v = c - 0x200;` and also `*(s16*)(p+0xC) = v;` — c is used once.

Hmm, what if the subtraction is written as `v = c + (-0x200);` → still 1 ref.

What if we use c in the compare too? Then c has 2 refs and v has 2 → tie. And the compare would read c ✗ (we want it to read v).

Hmm, what if the compare reads v and c is used twice: e.g. `v = c - 0x200;` and `w = c;`? ✗ extra insn.

Hmm! What if c is used twice in the subtraction: `v = c - 0x200 + (0);` → folded.

Hmm.

What about making v's ref count 1 by making the truncation's source something else? What if the copy's source is the LOAD and the compare's operand is also the load but through a different variable... circular.

Hmm, hold on: what if the compare's operand is `tmp` (the s16 temp) instead of `v`? Then:
- v's refs: 1 (the truncation's RHS)
- tmp's refs: 1 (the copy's RHS) + 1 (the compare) = 2
- c's refs: 1
→ combine would pick c for the compare ✗ (c has 1 ref vs tmp's 2). Same problem.

Hmm! But wait — the compare's operand would be tmp (QImode) → the comparison promotes it → the sign extension → hmm.

Hmm, what if the compare's operand is the LOAD's pseudo (with 1 ref) and the copy's source is tmp (2 refs: the copy + ... hmm, tmp's refs: the copy's RHS = 1) and c's refs = 1?

So: compare → the load pseudo L (1 ref: the compare) + the truncation's RHS (1) = 2 refs. Hmm, the truncation `tmp = (s16)v` uses v.

ARGH: v is used by both the truncation and the compare → 2 refs.

Unless the truncation's source is a DIFFERENT pseudo than the compare's operand. Which requires two loads of the same address (merged by cse) ✗.

Hmm, hold on: what if the truncation's source is the load and the compare's operand is ALSO the load — same pseudo, 2 refs.

Hmm, so v has 2 refs and c has 1 → combine prefers c.

**What if we make c have 2 refs?** Use c in the subtraction and... hmm. What if the store uses c?
```
if (v >= 0x801) {
    v = c - 0x200;
    *(s16 *)(p + 0xC) = v;
}
```
c: 1 ref.

Hmm, what if the subtraction is `v = c - 0x200` and the store is `*(s16*)(p+0xC) = (s16)(c - 0x200)`? Then c has 2 refs but the asm would compute c-0x200 twice ✗ (unless CSE merges them → 1 ref again).

Hmm.

**What if we make v have 1 ref by removing the truncation's use of v — i.e. the copy's source IS v but through a form that isn't a "use"?** Hmm.

Hmm, what if the copy's source is `v` directly and the temp is used elsewhere... no.

OK, alternatively: **increase the load pseudo's refs?** No, we want fewer.

Hmm, hold on! What if the compare's operand is v (2 refs) and the copy's dest c has 2 refs too — by using c in the compare as well? Then the compare reads... hmm, we want the compare to read v.

Ugh.

Hmm, wait. Let me reconsider: maybe combine prefers the reg with fewer refs, so I want c to have MORE refs than v. c's refs: 1 (the subtraction). Can I make c have 2 refs without extra insns?

What if the subtraction is `v = c - 0x200;` and we ALSO reference c in a way that's free — e.g. in the second arm? Hmm, c is redefined in the second arm.

What if c is used in the compare: `if (v >= 0x801)` — no.

Hmm! What about: `v = c - 0x200;` → what if instead we write `v = c - 0x200;` where the 0x200 is `c`?? no.

Hmm, what if the SECOND arm's copy is `c = tmp` and the first arm's copy is `c1 = tmp`? Then c1 (1 ref) and c (1 ref). Hmm.

What if the SAME variable c is used in both arms: the first arm's `v = c - 0x200` and the second arm's `v = c - 0x200` → c has 2 refs total! And in the target, both copies use v1 (the same reg) ✓✓ — that matches the target's structure (v1 reused for both copies)!

Hmm, but c's refs are counted per-definition... gcc's ref count is per pseudo (across all definitions). c is defined twice (once per arm) and used twice → 2 refs. Hmm, but that's already the case in c2.c (c is defined twice and used twice) — hmm, gcc's ref counts are per pseudo (not per definition) in the RTL. So c already has 2 refs (2 uses).

Hmm! Then the ref counts are: v = 2 (the truncation + the compare) × 2 arms = 4?; c = 2 uses. Hmm, but gcc's combine works on a per-insn basis.

OK, this ref-count theory is shaky.

Let me try yet another empirical approach: try making the compare's operand `v` where v is a variable with MORE uses. E.g. what if `v` is used in the second arm too? Hmm.

Honestly, let me try a bunch of quick structural variants in one batch and look for a score 0:

V1: `if (v >= 0x801)` with the copy `c = tmp` where tmp is s16 AND `v` is used in the second arm's compare... no.

V2: Hmm! What about making the copy's destination `c` used in BOTH the compare and the subtraction? I.e. `if (c >= 0x801) { v = c - 0x200; ... }` → the compare reads c ✗ (c12 gave score 6).

V3: What if the compare reads v and the SUBTRACTION reads tmp (the s16 temp) rather than c? Then c would be unused ✗.

V4: What if the copy's dest is `c` and we write `v = c - 0x200` but ALSO `*(s16 *)(p + 0xC) = v;` — hmm.

Hmm, let me try: **what if the second arm's copy uses a DIFFERENT variable (c2) so that the first arm's c has 1 use and the second's c2 has 1 use?** That's c4 (score 11) — the reg allocation changed badly.

Hmm.

**Let me try the reverse of what I did in c12**: `if (c >= 0x801) { v = c - 0x200; }` gave score 6 (36 ins) — the copies vanished (because the compare uses c → cse propagates c into the compare and the copy dies... hmm).

Hmm.

OK, time to make a decision. I've spent ~2h15m. Let me:
1. Move to 8017E6EC (the last item) and try the s16/copy tricks there.
2. Come back to 8018302C if time permits.

Actually, wait. Let me try ONE more thing for 8018302C, based on the "combine prefers the reg with fewer refs" theory: **make the compare's operand have FEWER refs than the copy's dest**.

The compare's operand is v (2 refs). The copy's dest c (1 ref). If I make c have 2 refs and v have 2 → tie. Hmm.

Alternatively: what if the compare's operand is the LOAD pseudo (which has 1 ref besides the truncation)? Hmm, the truncation uses v.

**IDEA**: what if the truncation's source is NOT v but the load, and v is assigned from the load separately:
```
v = *(s16 *)(p + 0xC);      /* v: 1 ref (the compare) */
tmp = *(s16 *)(p + 0xC);    /* tmp: the load again → cse merges with v's load → 1 pseudo → v gets 2 refs ✗ */
```
✗ (cse merges).

**IDEA**: what if the copy's source is v and the compare's operand is v, but the truncation is applied to the COPY's dest rather than its source? I.e.:
```
v = *(s16 *)(p + 0xC);
c = (s16)v;      /* c is s16?? */
```
c as s16 → the copy `c = (s16)v` → a truncation (not a plain copy) → escapes cse ✓ → and the compare reads v ✓ (c is a different mode) → and the subtraction `v = c - 0x200` → c (s16) promoted → the sign extension... gcc would need to materialize it ✗? Hmm, but maybe not: c's reg holds the sign-extended low-16 value = v (since v is sign-extended-16) → the promotion is free if gcc knows c's value...

Hmm, that's c7 (s16 v) — no, c7 was `s16 v` + `s16 tmp` + `s32 c`. Let me construct: `s32 v; s16 c;` with `c = (s16)v;` and `v = c - 0x200;`.

Hmm: `v = c - 0x200` where c is s16 → the promotion → gcc's expand: `(sign_extend:SI (reg c))` → gcc's combine: is it free? c's reg holds the truncated value (the low 16 of v) → the sign extension is needed → `sll/sra` ✗.

Unless gcc tracks that c = (s16)v and v is sign-extended-16 → then sign_extend(c) == v ✓ → free. gcc might know this: the RTL would be `(set c (sign_extend:HI v))` and then `(sign_extend:SI c)` → combine: sign_extend:SI of sign_extend:HI(v) → combine's rule: `(sign_extend:SI (sign_extend:HI x))` → hmm, that's not a standard simplification (sign_extend:HI x is x's low 16 sign-extended to 32 = x if x fits in 16 bits).

Hmm, gcc's convert.c `sign_extend(SImode, x)` where x = `(sign_extend:HI v)`:
```c
rtx
sign_extend (machine_mode mode, rtx x)
{
  ...
  if (GET_MODE (x) == mode) return x;
  ...
  /* If X is a sign extended narrow value, don't extend it twice */
  if (GET_CODE (x) == SIGN_EXTEND && GET_MODE (x) == HImode) return x;   /* ??? */
```
Hmm! Actually YES — gcc's convert.c has:
```c
/* Return a mode MODE version of X ... */
rtx
convert_to_mode (machine_mode mode, rtx x)
{
  ...
    case SImode:
      ...
      if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
	{
	  rtx extended = extend_mode (mode, x, GET_MODE (x), 0, 1);
	  ...
	}
```
and `extend_mode` → for signed → `sign_extend(mode, x)` → and gcc's `sign_extend`:
```c
rtx
sign_extend (machine_mode mode, rtx x)
{
  int wordsize = GET_MODE_BITSIZE (mode);
  ...
  if (GET_MODE (x) == mode) return x;
  ...
  /* If X is a sign extension of a narrow value, the sign extension
     to the wider mode is the same.  */
  ...
}
```
I'm not sure. Let me just TEST it in the harness: `int z1(short *p) { int v; short c; v = *(short*)p; c = (short)v; if (v >= 0x801) { v = c - 0x200; *(short*)p = v; } return v; }`.

Hmm, but the return would materialize the sign extension ✗ (as in x3). Let me make the harness function void-ish to avoid that: return nothing... but then the compare's shape may differ. Let me use a global sink? Simpler: mimic the real function with a void return and a store.

Let me test:
```c
void z1(short *p) { int v; short c; v = *(short*)p; c = (short)v; if (v >= 0x801) { v = c - 0x200; *(short*)p = v; } }
```
and check the asm.

Let me run it. This is my last exploration for 8018302C; then I move to 8017E6EC.
