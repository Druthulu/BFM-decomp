---
ts: 2026-10-22T08:18:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ONfoSkpnnlIgYAgk9Erq
---
Very close! Score 2. The copy survived (both `or v1,v0` are there presumably), but the compare uses v1 instead of v0: mine `slti v0,v1,2049` vs target `slti v0,v0,2049`.

So in the target, the compare reads v0 (the loaded value) and the copy is in v1. In mine, the compare reads v1 (the copy) — meaning gcc swapped: v = the copy and c = the original? I.e. my `c = tmp` copy got allocated v1 but the compare `v >= 0x801` read... hmm.

Actually: mine has `slti v0,v1,2049` — the compare reads v1. So in mine, v1 holds the value being compared. That means gcc assigned the LOAD to v1 and the copy to v0? Let me see the full listing.

Hmm, the diff only shows those two lines. So mine: `move v0,v1`? Let me get the full asm of my version. Let me use the --keep option or just look at the diff more fully. Let me run dt.sh with a bigger tail to see more context... the diff only shows differences.

Let me think: mine has 38 ins (same as target). The differences: the compare's source reg. In the target: `lh v0,24(a0)` → v0 = the loaded value; `move v1,v0` → v1 = the copy; `slti v0,v0,2049` compares v0 (the loaded value) with 2049; `addiu v0,v1,-512` computes v = c - 0x200 into v0.

In mine: the compare reads v1 → so the loaded value is in v1 and the copy in v0? Then `move v0,v1` would be the copy... but then the diff would show it. The diff shows only the slti lines differing, so the `move` lines match textually: mine has `move v1,v0`?? Hmm, if mine had `move v0,v1` the diff would show it.

Hmm! Unless mine's copy is `move v1,v0` too (same text) but the LOAD is in v1: mine would have `lh v1,24(a0)` — that's a different text → the diff would show it. But the diff doesn't show it.

Hmm, so both have `lh v0,24(a0)` and `move v1,v0`, but mine's compare reads v1?! That means in mine, the compare `v >= 0x801` reads the COPY (c/tmp), not v. Because I wrote `if (v >= 0x801)` — hmm, but gcc may have substituted: since c = tmp = (s16)v, gcc knows c == v (the sign extension is a no-op) → it replaced the use of v with c (the copy's reg) → `slti v0,v1,2049`.

Right! The compare reads the copy because gcc propagated v → c.

In the target, the compare reads v0 (the original) and the copy is v1.

So I need to prevent gcc from substituting v with c in the compare. Hmm.

Options:
- Use a different expression for the compare that doesn't refer to v: e.g. compare against the tmp: `if (tmp >= 0x801)`? Hmm, tmp is s16 → the comparison `tmp >= 0x801` would be a signed 16-bit comparison → different semantics and different insn (`slti` with a sign-extended value). Hmm, actually `tmp` as s16: `tmp >= 0x801` → tmp is promoted to s32 (sign-extended) → `slti v0,v1,2049` — hmm, the same text but reading the copy.

Hmm. I want the compare to read the ORIGINAL v (v0) while the copy goes to v1.

Since gcc thinks c == v (via the s16 round trip), it prefers to use c (the later copy). Hmm.

How to break that? Make the compare read a value that is NOT provably equal to c. Hmm, but they ARE equal.

Alternative: make the copy NOT a copy of v but of a different-but-equal value... hmm.

Alternative: reorder — make the copy come AFTER the compare in the source:
```
v = *(s16 *)(p + 0xC);
if (v >= 0x801) {
    tmp = (s16)v;
    c = tmp;
    v = c - 0x200;
    *(s16 *)(p+0xC) = v;
}
```
But then the copy is inside the if-block, and the target's copy is BEFORE the compare. Also, in the target the copy exists on both paths (it's before the branch). Hmm — in the target, the `move v1,v0` is before the slti and the branch, so it executes always. If I move the copy inside the if-block, the target's structure changes (the move would only be in the if-arm) → the insn order/count would differ.

Hmm. But wait — would it? The target's `move v1,v0` is at 34b8, before the slti at 34bc. If our copy were inside the if-arm, the asm would be:
```
lh v0,24(a0)
slti v0,v0,2049
bnez v0,...
  <delay>
  move v1,v0
  addiu v0,v1,-512
  sh v0,24(a0)
```
vs the target:
```
lh v0,24(a0)
move v1,v0
slti v0,v0,2049
bnez v0,...
  addiu sp,sp,-16
  addiu v0,v1,-512
  sh v0,24(a0)
```
Different. ✗

So the copy must stay before the compare, and the compare must read v0 (the original), not the copy.

How? The compare `v >= 0x801` where v is the loaded value. gcc substituted the copy's value for v. To prevent: make the copy's value NOT provably equal to v at the compare point.

Hmm, but the copy IS equal to v.

Hmm, alternatively: make the copy's value equal to v but through a path gcc can't prove: e.g. the s16 round trip IS provable (that's why gcc folded the sign extension). Hmm, so the round trip being provable is what makes the copy "equal" — and the equality lets gcc substitute.

Hmm! But in 80182ED4 the same trick worked: there the compare was `if (t == 0)` where t is the ORIGINAL (not the copy) — and the copy was `u = tmp`. gcc substituted... hmm, in 80182ED4 the target's compare is `beqz v0` / `bnez v0` reading v0 (the original t), and the copy `or v1,v0` is in v1. And our c6 MATCHED! So there gcc did NOT substitute the copy into the compare.

Why the difference? In 80182ED4: `t = unk84; tmp = (s16)t; u = tmp; if (t == 0) {...} else { t = u - 1; }`. The compare reads t. gcc could have substituted u's value into the compare (since u == t) but didn't — maybe because the compare's operand t is used BEFORE the copy in program order? No: the copy is before the compare in our source.

Hmm, in c6: `tmp = (s16)t; u = tmp; if (t == 0)`. The compare reads t (the original). gcc might have substituted u for t in the compare → `beqz v1`. But the result MATCHED, so gcc kept v0 for the compare.

Hmm, so in 80182ED4 gcc did NOT substitute but in 8018302C it did. Difference: in 8018302C, the copy is `c = tmp` and the compare is `v >= 0x801` — v and c are DIFFERENT variables both derived from the same load. In 80182ED4, `t` and `u` are different variables too...

Hmm, what's different? In 80182ED4, `u` is used only in the else arm; in 8018302C, `c` is used only inside the if-arm.

Hmm, and the substitution direction: in 8018302C, gcc replaced the use of `v` (in the compare) with `c` (the copy). In 80182ED4, gcc kept `t` in the compare.

Hmm, maybe the difference is the ORDER: in 8018302C the copy `c = tmp` comes right before the compare, so cse/combine's "prefer the latest copy" applies. In 80182ED4 the same...

Hmm, whatever the reason, let me try to fix 8018302C:

Option A: Make the compare use a value that gcc won't substitute. E.g. keep `v` used in the compare but ALSO make the copy's source different.

Option B: Swap the roles: make the COPY be the value used in the compare and the ORIGINAL be used in the subtraction! I.e.:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (c >= 0x801) { v = c - 0x200; ... }
```
Then the compare reads c (the copy). But the target's compare reads the ORIGINAL (v0) and the copy is v1. Hmm, in the target the compare reads v0 = the original load and the copy is v1. If we swap, the compare would read v1 (the copy) → the diff would show `slti v0,v1,2049` vs the target's `slti v0,v0,2049` ✗.

Hmm, so we need the compare to read the ORIGINAL.

Option C: prevent the substitution by making the copy's value provably different... no.

Option D: use TWO separate temps so the copy's value isn't tracked? Hmm.

Option E: Hmm — what if the substitution happens because gcc sees `c` as the canonical name for the value (cse's canonicalization: the copy's dest becomes canonical). In 80182ED4 the same should apply... but there the compare read t.

Hmm, wait. Let me re-look at 80182ED4's c6 result — it MATCHED, so the compare read v0 (the original). Hmm, so in 80182ED4 gcc kept t.

What's different? In 80182ED4 the compare is `t == 0` (an equality with 0) and in 8018302C it's `v >= 0x801` (a comparison with a constant). Hmm, that shouldn't matter for substitution.

Hmm, another difference: in 80182ED4, `u` (the copy) is used in the ELSE arm (a different block); in 8018302C, `c` (the copy) is used in the THEN arm.

Hmm! Maybe the direction of the substitution is "use the value that's live at the point". In 8018302C, the compare happens after the copy, and c is live (used later in the if-arm) while v is also live (used in the compare and then reassigned). Hmm.

Alternatively, maybe the difference is that in 8018302C, `v` is REDEFINED inside the if-arm (`v = c - 0x200`), so v's value after the compare is dead → gcc prefers to use the copy c for the compare (since c is the surviving value). Whereas in 80182ED4, `t` is redefined in the else arm too...

Hmm. Hmm, in 80182ED4: `t = u - 1` in the else arm — so t is redefined there too. And the compare `t == 0` read t (v0). Hmm.

Hmm, but wait: in 80182ED4, the compare is at 80d4 (bnez) and the copy at 80d8 (the delay slot) — the copy is AFTER the compare in program order! So the compare necessarily reads the original v0. In our c6, the copy was hoisted before the branch, but the SCHEDULER placed the copy in the delay slot (after the branch) — so the compare reads the original.

In 8018302C, the target's copy is at 34b8 BEFORE the slti at 34bc. So the compare comes after the copy → gcc can substitute the copy into the compare (the copy's value is available). And it did.

So for 8018302C, I need the compare to read the original v0 even though the copy comes first.

Hmm! How? The target's `slti v0,v0,2049` reads v0 = the loaded value, and `move v1,v0` is before it. So in the target, gcc did NOT substitute the copy into the compare (the copy was `(plus v (reg 0))` — not a recognized equality! cse couldn't create the equivalence, so the compare kept reading v).

So in our version, the s16 temp creates the equality → gcc substitutes.

Hmm! So the s16 trick has a side effect here.

How to keep the copy alive WITHOUT creating the equality that lets gcc substitute?

Hmm. Ideas:
1. Use a `u16` temp instead of s16: `tmp = (u16)v; c = tmp;` → the zero-extension would materialize an `andi` ✗ (unless the value's high bits are known zero — for a sign-extended lh value they're not).

Hmm. But wait — what about the SIGN of the comparison? `v >= 0x801` where v is s32 (sign-extended). The u16 truncation would break the comparison semantics anyway.

2. Make the copy's value NOT provably equal: e.g. copy through a temp with a different type but the same value...

Hmm, what if we route the copy through the s16 temp but the compare uses a DIFFERENT variable that holds the same value? E.g.:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { ... }
```
gcc substitutes v→c in the compare because it knows c == v.

What if we prevent the equality by making `tmp` a volatile? no.

3. What if the compare reads a value that is loaded TWICE? Hmm, extra insn.

4. **What if we give the compare a DIFFERENT source that gcc can't equate — e.g. the compare uses the ORIGINAL load and the copy is of a re-loaded value?** ✗ extra insn.

5. **What if we use a different structure: make the copy the value that's compared, and the ORIGINAL the value used in the subtraction?** The target: compare reads v0 (original), subtraction reads v1 (copy). If we swap the roles in C (compare the copy, subtract from the original) then gcc's allocation might put the copy in v0 and the original in v1 → `slti v0,v0,2049` (if the copy is in v0) and `addiu v1,v0,-512`?? The target has `addiu v0,v1,-512` (the result in v0). Hmm, so the subtraction's result must be in v0 and the compare's operand in v0 too (they're the same reg v0!). Target: `slti v0,v0,2049` (compare v0) and `addiu v0,v1,-512` (result v0, source v1). So v0 is used for BOTH the compare operand and the result. That means the compare's operand and the subtraction's result share the register → they're the same variable (v). And the copy is in v1.

So: v (the loaded value) is in v0, the copy (c) is in v1, and the subtraction `v = c - 0x200` writes v0.

So the compare must read v0 = v. We need gcc to keep the compare on v, not c.

Hmm. Since gcc substituted c for v in the compare (because c == v and c is "later"), maybe I can make the SUBTRACTION read v and the compare read c? No — the target's subtraction reads the copy (v1) and the compare reads the original (v0).

Hmm, so we need: compare → original, subtraction → copy. And gcc wants to use the copy for both.

Hmm! What if we make the copy NOT equal to v in gcc's view but produce the same asm? E.g. copy through a temp of a DIFFERENT type where the conversion is a no-op but gcc doesn't create the equality... e.g. `tmp` is `s16`, and `c = tmp` → gcc knows c = sign_extend(tmp) = sign_extend((s16)v) = v. So it knows c == v.

What if `c` were declared s16 too? Then `c = tmp` is a same-mode copy → cse propagates (c and tmp merged) → then c == v still.

Hmm. What if the copy is `(s16)` but the compare uses a value that gcc treats as distinct...

**IDEA**: what if the compare's operand is `v` but `v` is a DIFFERENT variable from the one copied? I.e.:
```
v = *(s16 *)(p + 0xC);       /* v in v0 */
w = (s16)v;                 /* hmm */
c = w;
if (v >= 0x801) { v = c - 0x200; ... }
```
Same equality.

**IDEA**: Break the equality by making the compare read a value with a DIFFERENT proven range: e.g. compare `v` as an unsigned? The target's `slti v0,v0,2049` is a SIGNED comparison (slti) ✓ (v is s32, 0x801 = 2049). Hmm.

**IDEA**: Use the copy in the compare and the ORIGINAL in the subtraction but arrange the registers so the result matches:
Target: compare operand v0, subtraction source v1, result v0.
If the compare reads the copy (c) and the subtraction reads the original (v): then c must be in v0 and v in v1 → `slti v0,v0,2049` ✓ and `addiu v0,v1,-512`?? the result would be v0 = v1 - 512 where v1 = the original v ✓✓ !!!

WAIT! That works! Let me re-read the target:
```
34b0: lh v0,24(a0)      ; the loaded value in v0
34b8: move v1,v0        ; the copy: v1 = v0
34bc: slti v0,v0,2049   ; compare v0 (the ORIGINAL) with 2049
34c0: bnez v0,34d0
34c4: addiu sp,sp,-16
34c8: addiu v0,v1,-512  ; v = c - 0x200 → result in v0, source v1
34cc: sh v0,24(a0)
```
So the compare reads v0 = the original load, and the subtraction reads v1 = the copy.

If instead our C were:
```
v = *(s16 *)(p + 0xC);   /* v */
tmp = (s16)v;
c = tmp;                  /* the copy */
if (c >= 0x801) { v = v - 0x200; ... }   /* hmm, the subtraction would use v, not c */
```
Then: the compare reads c (the copy) → c in v0? and the subtraction `v = v - 0x200` reads v → v in v1 → `addiu v1,v1,-512`? no: the result goes to v → `addiu v1,v1,-512` (v in v1) → the target has `addiu v0,v1,-512`. ✗ (the result must be in v0).

Hmm. So the result reg v0 must hold the subtraction's result, and the compare's operand is also v0. So the compared value and the result share v0.

In the target: compare operand = the loaded value (v0), result = v (v0). So the compared value IS v (the same variable). ✓ So the compare must read v.

Therefore: compare reads v (v0), the subtraction reads the copy (v1). We need gcc to NOT substitute the copy into the compare.

Hmm. How about: make the copy's value provably different from v by a tiny amount... no, the asm must match.

Hmm, what if the copy is of a value that is equal to v but through a path where gcc's equality is not "exact"? E.g., if the copy went through an `unsigned short` temp: `tmp = (u16)v; c = tmp;` → c = zero_extend(tmp) and tmp = truncate(v) → c = v & 0xffff ≠ v in general → gcc would NOT substitute ✓! But then the copy would need the `andi` (the zero extension materializes) ✗... UNLESS gcc can prove v's high bits are zero — it can't (v is a sign-extended lh).

Hmm, but hold on: does the zero-extension really materialize? In the c4 experiment for 80182ED4 (u16 u), the andi DID materialize. ✗

Hmm. What if the temp is `u16` and the SOURCE is a value with a known-zero high part? v = sign-extended lh → no.

Hmm. What if we route the copy through an s16 temp but ALSO ensure the compare's operand can't be substituted because the copy is not "the same value" — hmm.

**IDEA**: What if the compare is on a DIFFERENT variable that holds the same loaded value? I.e., load once into v, copy into c, and compare... no, the compare must be on the value in v0 and the result also in v0.

Hmm, hmm. Let me reconsider: what if gcc's substitution is a *scheduling/regalloc* artifact rather than a value substitution? The diff shows `slti v0,v1,2049` — the compare reads v1 where v1 holds... hmm, in MY version, what's in v1? Let me look at my full asm. Let me compile my c1.c with --keep to see the object, or reason:

My version:
```
lh v0,24(a0)      ; v
move v1,v0        ; c = tmp (the copy) — wait, is the copy `move v1,v0`?
slti v0,v1,2049   ; compares the copy
```
Hmm, if the copy is `move v1,v0` then v1 = the copy = v's value, and the compare reads v1 ✓ (gcc substituted). The diff shows only the slti lines differ, so the `move v1,v0` line is the same in both. So in MY version: `lh v0` ; `move v1,v0` ; `slti v0,v1,2049` ; `bnez v0,...` ; `addiu v0,v1,-512` ; `sh v0,24(a0)`.

Interesting: so in mine, the compare reads v1 (the copy) and the subtraction also reads v1. And the target: compare reads v0, subtraction reads v1.

So it's JUST the compare's operand register that differs! Everything else matches (38 ins, same text except the slti operand).

So I need the compare to read v0 (the original) instead of v1 (the copy).

Idea: what if the compare uses `v` but gcc's substitution is because the copy c is "equivalent" to v... Let me try making the compare use a DIFFERENT variable that holds the same value but is not the copy's target. E.g.:

```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p + 0xC) = v; }
```
That's what I have. gcc substituted v→c in the compare.

What if we make the compare read a value that's NOT c: e.g. compare the ORIGINAL load expression again? `if (*(s16 *)(p + 0xC) >= 0x801)` → that would reload → an extra lh ✗.

Hmm. What if we prevent the substitution by making the copy's value DIFFERENT in gcc's view but the same in the asm? E.g. the copy through a `u16` temp where the high bits are known zero...

Hmm, hold on: what if we change the LOAD to `lhu`?! Then v's range is 0..65535 and:
- `tmp = (u16)v` → no-op (v is already 16-bit zero-extended) → the copy `c = tmp` → zero_extend:HI(v) → hmm, v's high bits are known zero (from lhu) → gcc folds → the copy becomes `or v1,v0` ✓ and NO andi!
- And the equality c == v would still hold → the compare would still be substituted ✗.

Hmm. But also the load would be `lhu` vs the target's `lh` ✗.

Hmm.

OK, so the issue is the substitution of v→c in the compare. How did the TARGET avoid it? Because in the target, `c = v + $0` created NO equality (cse couldn't equate c with v) → the compare kept reading v.

So I need a copy that (a) survives cse and (b) does NOT create an equality that lets gcc substitute the compare's operand.

Hmm! What if the copy is `c = v` where the equality is broken by an intervening... hmm.

**IDEA**: What if the copy's SOURCE is a different variable than the compare's operand, but they hold the same value? E.g.:

```
v = *(s16 *)(p + 0xC);     /* v: the load */
w = v;                     /* w: a plain copy?? */
```
no.

Hmm, what if:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;      /* tmp */
c = tmp;            /* the copy: c == v in gcc's view */
if (v >= 0x801) {...}
```
The equality c==v comes from tmp == v (the s16 round trip) and c == tmp.

What if we break it at the tmp→c step: `c = tmp` where c is s32 and tmp is s16 → gcc knows c = sign_extend(tmp) = sign_extend((s16)v) = v (it folded the sign extension). So c == v.

What if tmp is `unsigned short`? Then c = zero_extend((u16)v) = v & 0xffff ≠ v → no equality ✓. But the zero extension must materialize → `andi` ✗ — UNLESS gcc can prove v's high bits are zero.

Hmm, v = lh → high bits unknown ✗.

Hmm. What if the copy's source is a value whose high bits ARE known zero? The other loads in the function: `*(s16 *)(p + 0xC)` is s16. Hmm.

OK, alternative: **prevent the substitution by making the compare read a DIFFERENT (but equal) variable that gcc doesn't equate with c.** For example:

```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p+0xC) = v; }
```
gcc: v == tmp == c. It picks the copy (c) for the compare.

What if the compare reads a variable `q` that is assigned from v BEFORE the copy:
```
v = *(s16 *)(p + 0xC);
q = v;             /* hmm, another copy */
```
✗.

Hmm. What if the compare is done BEFORE the copy in program order? I.e. the copy is placed after the compare in the source but the SCHEDULER hoists it before the compare?

The target's order: `lh v0` ; `move v1,v0` ; `slti v0,v0,2049` ; `bnez`. So the copy comes before the compare in the final asm. But in the SOURCE (the target's decompiled C), the copy `c = v + z` comes before the compare `if (v >= 0x801)` ✓ (that's the given source).

But if in OUR source we write:
```
v = *(s16 *)(p + 0xC);
if (v >= 0x801) {
    tmp = (s16)v;
    c = tmp;
    v = c - 0x200;
    *(s16 *)(p + 0xC) = v;
}
```
then the copy is inside the if-arm → the asm would have the copy in the if-arm, and the compare would read v0 ✓ (no substitution possible since the copy comes later). But the copy would then be inside the branch → the target's copy is before the branch. The resulting asm:
```
lh v0,24(a0)
slti v0,v0,2049
bnez v0,...
  <delay>
  move v1,v0      <- in the if-arm
  addiu v0,v1,-512
  sh v0,24(a0)
```
vs the target:
```
lh v0,24(a0)
move v1,v0
slti v0,v0,2049
bnez v0,...
  addiu sp,sp,-16
  addiu v0,v1,-512
  sh v0,24(a0)
```
Different order and the delay slot differs. ✗

Hmm. But wait — what about the SECOND arm? The target has the same pattern for p+0xD.

Hmm. Hmm, so we need the copy before the compare but the compare must read the original.

**IDEA**: What if the compare's operand is a variable that is NOT the copy's source, and the copy's source is a different variable holding the same value, where the "same value" relation is not a simple equality? E.g.:

```
v = *(s16 *)(p + 0xC);      /* v */
tmp = (s16)v;               /* tmp: the truncation */
c = tmp;                    /* the copy */
if (v >= 0x801) { ... }
```
gcc knows c == v.

What if:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;      /* tmp */
c = tmp;           /* c */
if (c >= 0x801) { v = c - 0x200; ... }
```
Then the compare reads c. gcc would allocate: c is the copy → which reg? The copy is `c = tmp` → the copy's dest gets a reg; the source v gets another. Since the compare reads c and the subtraction reads c, and the result goes to v...

Hmm! In this version, the copy's dest (c) is used for BOTH the compare and the subtraction, and v is only the store target. Then gcc would allocate: c → v0 (used by the compare) and v → v1?? Then the copy `move v0,v1`?? Hmm, the copy's source is tmp (which is v's value).

Hmm, let's think: the copy is `c = tmp` where tmp's reg = v's reg (they're equal). The copy `or rd,rs` where rs = tmp's reg. tmp is dead after → tmp's reg = v's reg = v0? and c gets v1.

Then the compare `c >= 0x801` reads c = v1 → `slti v0,v1,2049` ✗ (the target reads v0).

Hmm, unless gcc allocates c → v0 and tmp → v1: then the copy would be `or v0,v1` — but the target's copy is `or v1,v0` (dest v1). ✗

Hmm. The target: the copy's dest = v1, the source = v0, and the compare reads v0 (the source's reg = the original v).

So the compare must read the ORIGINAL v (v0) and the copy's dest must be v1.

In my current version, gcc put the copy's dest in v1 ✓ but substituted the compare's operand to the copy ✗.

Hmm! So the register allocation is right; only the operand of the slti is wrong.

So: how do I stop gcc from substituting v with c in the compare?

Option: make the compare read something gcc can't equate to c. Hmm... What if the compare's operand is the ORIGINAL load expression, i.e. `v`, but `v` is modified between the copy and the compare? No.

What if we make the copy's source a DIFFERENT variable than the compare's operand, where the source is provably equal but through a conversion that gcc tracks as "equal but different"? Hmm, gcc's substitution happens because the values are the same RTL.

**IDEA**: What if the copy is `c = tmp` where tmp is `s16` and the compare's operand `v` is ALSO routed... hmm.

**IDEA**: What if we make the compare's operand be a value that is NOT the same as c: e.g. compare `v` but where `v` was re-loaded? ✗

**IDEA — reverse the copy direction!** What if the copy's SOURCE is `v` and the compare reads a DIFFERENT variable `w` that was set from v BEFORE... hmm, then w == v == c and gcc picks the latest = c.

Hmm. gcc's preference: it substitutes the "canonical" reg. cse's canonicalization picks the reg with more uses or the later-defined one.

**IDEA**: make the compare's operand have MORE uses than c? Hmm.

Hmm, actually — hold on! In 80182ED4 (c6, MATCHED), the compare `if (t == 0)` read t (the original) and the copy's dest u was v1. So gcc did NOT substitute there. Why?

In c6:
```
t = unk84;         /* t */
tmp = (s16)t;
u = tmp;           /* the copy */
if (t == 0) { ... t = 0x1E; } else { t = u - 1; }
```
Here u is used in the ELSE arm and t is used in the compare (and later reassigned). gcc did not substitute u for t in the compare.

In 8018302C c1:
```
v = *(s16*)(p+0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; *(s16*)(p+0xC) = v; }
```
Here gcc DID substitute c for v in the compare.

Difference: in c6, `t` has a use AFTER the branch (t = 0x1E in the if-arm, t = u-1 in the else) — hmm, both are redefinitions.

Hmm, in c6 the compare is `t == 0` — an EQUALITY test with 0. In 8018302C it's `v >= 0x801` — a relational test. gcc's combine might handle them differently: for `v >= 0x801` → `slti v0,v1,2049` — combine rewrites the comparison using the "true" operand. If combine sees that v and c are the same value, it picks one.

Hmm, in c6, `t == 0` → `beqz v0` — no operand choice needed (the branch reads the compared reg directly). Combine might still substitute.

Hmm, honestly, let me just try variants:

v1: put the copy AFTER the compare in the source but before the branch... impossible (the compare IS the branch condition).

v2: Write the compare as `if (v >= 0x801)` but make the copy's dest used in the compare too:
```
if (c >= 0x801) { v = c - 0x200; ... }
```
→ the compare reads c (v1?) ✗ probably.

v3: Use a separate variable for the compare that holds the value BEFORE the copy:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; ... }
```
(current)

v4: Make the copy's SOURCE a different variable than the compared one:
```
v = *(s16 *)(p + 0xC);
w = v;            /* hmm, plain copy → cse */
```

Hmm.

v5: **Make the compare read the value BEFORE the s16 round trip, and the copy be of the round-tripped value, and prevent gcc from seeing the equality by using an unsigned temp whose high bits are... ✗ (andi)

v6: **Break the equality with a `+ 0`-style no-op?** ✗

v7: What if the copy's temp is `s16` but the compare's variable `v` is declared `s16` too?! Then:
```
s16 v, tmp, c?  hmm
```
Hmm: `v` as s16 → the load `*(s16*)(p+0xC)` → v is s16 → `lh` ✓ (same insn!). Then `if (v >= 0x801)` → v is s16 → promoted to s32 (sign-extended) → the compare would need a sign extension ✗ (the value is already sign-extended in the reg from lh → so `slti v0,v0,2049` might work! Since the lh result is already sign-extended, the promotion is free ✓).

Hmm! Interesting. And `v = c - 0x200` with v as s16 → truncation → the store `*(s16*)(p+0xC) = v` → the value's low 16 bits ✓.

Hmm, but the target's `addiu v0,v1,-512` computes the full 32-bit difference and then `sh v0,24(a0)` stores the low 16 ✓ — with v as s16, `v = c - 0x200` → the result is truncated to 16 bits → `addiu v0,v1,-512` then the store takes the low 16 → the same insn ✓ (the truncation is free at the store).

Hmm, so making `v` an s16 might work. And then the equality: c == v? c = tmp = (s16)v = v exactly (as an s16 value). And the compare `v >= 0x801`: v (s16) promoted → sign-extended → equals v's 32-bit value. Hmm, gcc would still know c == v.

Hmm, but the compare's operand: gcc would substitute c (the copy) again. Hmm.

Hmm, unless the equality is broken by the truncation: if v is s16 and c is s32, then c = sign_extend(tmp) where tmp = (s16)v. gcc knows c == v (as 32-bit values, since v is sign-extended). Hmm.

OK, let me think about WHY gcc substituted. Maybe it's not a value substitution at all! Maybe it's a REGISTER ALLOCATION difference: maybe in mine, the LOAD is in v0 and the copy is in v1, and the compare reads v1 because... hmm, the compare `v >= 0x801` reads v. If v is in v0, the compare should read v0.

Unless in MY version, the LOAD is in v1! I.e. mine: `lh v1,24(a0)`? But then the diff would show the lh line differing. It didn't. Hmm, unless the diff only shows the changed lines and I mis-assumed.

The diff showed:
```
replace mine[5:6] target[5:6]
     5  slti v0,v1,2049 | slti v0,v0,2049
replace mine[13:14] target[13:14]
    13  slti v0,v1,2049 | slti v0,v0,2049
```
Only the slti lines. So mine[4] = `move v1,v0` (same as target) and mine[3] = `lh v0,24(a0)` (same). Hmm, so mine has `lh v0` then `move v1,v0` then `slti v0,v1,2049`.

Hmm, that means the compare reads v1 = the copy. So gcc DID substitute the value.

Hmm, wait. OR: mine's `move v1,v0` might be at a different index... The diff replaced mine[5:6] with target[5:6], so index 4 matched. OK.

So gcc substituted. Hmm.

Hmm, hold on: what if in mine, the roles are: v0 = the copy's SOURCE (tmp) and v1 = the copy's dest (c), and gcc decided the compare should read c because c is the "canonical" name.

Yes, that's the substitution.

**How to prevent**: make the compare read a value that is NOT provably equal to c.

IDEA: **Compare a value loaded a second time?** ✗

IDEA: **Change the comparison to use the copy explicitly but arrange the registers so the compare's reg is v0**:
```
if (c >= 0x801) { v = c - 0x200; ... }
```
Then the compare reads c. And c = the copy. Which reg does c get? The copy is `c = tmp`; tmp's reg = v's reg. gcc's local_alloc: tmp is short-lived (dies at the copy) → tmp and v might share a reg. c is live (used in the compare and the subtraction). v is live (redefined later, stored).

Hmm: the compare reads c → c must be in a reg; the subtraction `v = c - 0x200` reads c and writes v. The target wants: the compare operand = v0, the subtraction source = v1, the result = v0.

Hmm, in this variant: the compare operand = c and the subtraction source = c → the same reg! So the compare and the subtraction both read c. The target has the compare reading v0 and the subtraction reading v1 — DIFFERENT regs. ✗

So the target's structure REQUIRES: the compare reads the original (v) and the subtraction reads the copy (c). And gcc's substitution kills it.

Hmm! So the target's `c = v + $0` avoids the equality. And the s16 trick creates the equality.

**So I need a copy that survives WITHOUT creating an equality.**

Hmm, what if the copy's source is a value that equals v but through a path gcc tracks as "the same value" — hmm.

What about: `c = tmp` where tmp is s16 and `tmp = v` — gcc folds the sign extension → c == v.

What if tmp is s16 and `c = tmp` where c is ALSO s16?! Then c == tmp == v as 16-bit values. And the subtraction `v = c - 0x200` → c is promoted (sign-extended) → hmm, the promotion is free if gcc knows c's value...

Hmm, the equality is still there.

**IDEA**: Break the equality by making the copy's value a *different* variable that gcc doesn't merge, using a conversion gcc can't fold but which produces the same asm. The asm of the copy is `or v1,v0` (a plain move). A conversion that produces a plain move: sign_extend/zero_extend that folds to a copy. Both create an equality with the source.

Hmm, unless the conversion is "the value is the same but gcc's equality check fails" — e.g., if the copy is `c = (s16)v` and gcc folds it to a copy, the equality is exact.

Hmm. **What if the copy's source is a value that is EQUAL to v but not the same variable — e.g. a second load of the same field?** ✗ extra insn.

**RADICAL IDEA**: what if we don't need the copy to be a copy of v at all? What if we restructure so that the "copy" is `c = v` where c is used ONLY in the subtraction and the compare reads v — and gcc's substitution is prevented because c is NOT equal to v in gcc's view because the s16 round trip LOSES information!

Specifically: if v's value doesn't fit in s16, then tmp = (s16)v ≠ v. gcc knows that! So c ≠ v → no substitution ✓. But then the copy's asm would include the truncation ✗ (the andi/sll).

Hmm, unless the truncation is free... no.

Hmm.

**IDEA**: use the fact that the COMPARE's operand could be a variable that gcc keeps distinct because it's used in a context requiring the exact value.

Hmm.

**IDEA — the "store between load and copy" trick!** From moves.md line 99: "pin | func_80184F08 | WALL combine-copy-merge — cse prev-insn swap beaten by a store between load and copy (block 2); block 1 has no store to place, combine merges lw+copy; best 6 (G03)".

Interesting: a STORE between the load and the copy defeats combine's merging! Because combine merges `lw` + `copy` when they're adjacent (it can then load directly into the copy's destination). A store in between prevents that.

Hmm, in our case, the merge that happened is the substitution of c for v in the compare. Would a store between the copy and the compare prevent it? Hmm, the store `*(s16*)(p+0xC) = v` is inside the if-arm (after the compare). Hmm.

Hmm, what if we put a store between the copy and the compare? There isn't one in the target's structure.

Hmm.

**IDEA**: what if the copy is placed after the compare in the source but the SCHEDULER hoists it before the compare? Let's think:
```
v = *(s16 *)(p + 0xC);
if (v >= 0x801) {
    tmp = (s16)v;
    c = tmp;
    v = c - 0x200;
    *(s16 *)(p + 0xC) = v;
}
```
The copy is inside the if-arm → the compare reads v (no substitution possible since the copy is later) ✓. But the copy's position in the final asm: the target has it BEFORE the slti. Ours would be after the branch. ✗ (order differs)

Hmm, but wait — would it? Let me think about the delay slot: the target's `move v1,v0` is at 34b8, before the slti at 34bc. If our copy is in the if-arm, the asm would be:
```
lh v0,24(a0)
slti v0,v0,2049
bnez v0,34d0
  addiu sp,sp,-16   (delay slot)
  move v1,v0
  addiu v0,v1,-512
  sh v0,24(a0)
```
Hmm, the target:
```
lh v0,24(a0)
move v1,v0
slti v0,v0,2049
bnez v0,34d0
  addiu sp,sp,-16
  addiu v0,v1,-512
  sh v0,24(a0)
```
The difference: the position of `move v1,v0` (before vs after the slti/bnez). The masked diff would flag it (an insert/delete). ✗

Hmm. So close but no.

Hmm, what if the copy is before the compare in the source but the compare uses a variable that is NOT c...

Let me reconsider: WHY did gcc substitute? Because cse/combine know c == v. In 80182ED4, u == t too, but no substitution. Hmm, let me look more carefully at 80182ED4's c6: the compare `if (t == 0)` → `beqz v0` / `bnez v0`. The branch reads the compared reg directly. gcc's combine for `t == 0` → `(set (reg) (eq (reg t) (const 0)))` → the branch reads t's reg. If gcc substituted u for t, the branch would read u's reg (v1) → `beqz v1`. The MATCH says it read v0 ✓ (no substitution).

Hmm! So in 80182ED4, no substitution; in 8018302C, substitution. What's different?

In 80182ED4, the copy `u = tmp` and the compare `t == 0`: the compare's operand t is used in the compare AND the copy's source is tmp (not t). So gcc's equality t == u is only known through tmp.

In 8018302C, same structure: `c = tmp`, compare on v.

Hmm, the difference might be the number of uses: in 8018302C, `v` is used in the compare and reassigned in the if-arm; `c` is used in the subtraction. Hmm, in 80182ED4, `t` is used in the compare and reassigned in both arms; `u` is used in the else arm.

Hmm, maybe the difference is that in 8018302C the compare is `v >= 0x801` where the CONSTANT is involved → combine's "compare simplification" picks the operand. While `t == 0` → `beqz` → no operand choice.

So: what if I rewrite the compare to a form that doesn't allow substitution? E.g. `if (v >= 0x801)` → `if (!(v < 0x801))` → `slti` + branch... The target's asm is `slti v0,v0,2049` + `bnez` → i.e. `if (v >= 0x801) { ... }` compiled as "if (v < 0x801) skip" → `slti v0,v0,2049` (v < 2049) then `bnez` (if v < 2049, skip the block).

So the target's compare is `v < 0x801` inverted. Our source `if (v >= 0x801)` → gcc computes `slti v0,v?,2049` where the ? is the value being compared.

**IDEA**: write the compare as `if (v - 0x801 >= 0)`? Hmm, that changes the insn.

**IDEA**: write the compare using a different but equivalent expression that reads a variable gcc won't substitute: e.g. `if (v >= 0x801)` where v is... hmm.

**IDEA**: What if we make the compare's operand the ORIGINAL load expression but through a variable that is NOT equal to c — e.g. compare `v` BEFORE the copy is made, i.e. compute the comparison result first:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { ... }
```
Hmm.

What if:
```
v = *(s16 *)(p + 0xC);
w = v;              /* w: the copy's source? no */
```

Hmm, hmm. What if the copy's source is `v` but the copy's dest is compared? no.

**IDEA**: What if the compare reads the copy `c` and the SUBTRACTION reads the original `v`?? Then: the compare reads c (v?), the subtraction reads v. For the asm: `slti v0,v0,2049` (compare c in v0) and `addiu v0,v1,-512` (result v0, source v = v1)?? But the result must be v0 = the original's reg... and the original is v1. Hmm, the result `v = c - 0x200` would be written to v → if v is in v1, the result is in v1 → `addiu v1,v?,...` ✗.

Hmm, unless the result variable is different. Let's define:
```
v = *(s16 *)(p + 0xC);     /* the load */
tmp = (s16)v;
c = tmp;                   /* the copy */
if (c >= 0x801) {
    v = c - 0x200;         /* the result */
    *(s16 *)(p + 0xC) = v;
}
```
Here c is used for both the compare and the subtraction; v is the store target. gcc: c → some reg; v → another. The compare `slti vX,c_reg,2049`; the subtraction `addiu vY,c_reg,-512` (dest = v's reg).

Target: `slti v0,v0,2049` (dest v0, src v0) and `addiu v0,v1,-512` (dest v0, src v1). So the compare's dest and src are the SAME reg (v0), and the subtraction's dest is v0 and src is v1.

In my variant: the compare's src = c's reg; the subtraction's src = c's reg → the same reg → so `slti v0,vC,2049` and `addiu vD,vC,-512` where vD is v's reg. For the target we'd need vC = v0 and vD = v0 → but then the subtraction's dest = v0 = c's reg → `addiu v0,v0,-512` ✗ (the target has v1 as the source).

So the target NEEDS the compare's operand and the subtraction's source to be DIFFERENT regs: the compare's operand = the original (v), the subtraction's source = the copy (c). ✓ my current version has exactly that, but the compare's operand got substituted to the copy.

So I need to prevent the substitution. Hmm.

**KEY QUESTION**: why did gcc substitute in one case and not the other?

Let me test variants in my fast harness:
```c
int x1(short *p) { int v; int c; short tmp; v = *(short*)p; tmp = (short)v; c = tmp; if (v >= 0x801) { v = c - 0x200; *(short*)p = v; } return v; }
```
Let me compile and look. Then try variants:
- x2: `if (v >= 0x801)` with the compare written as `if (!(v < 0x801))`.
- x3: declare v as `short`.
- x4: use `unsigned` compare.
- x5: put the compare on a different variable.

Let me run the harness with several variants and inspect the asm. This is fast.

Actually, let me think about what "substitution" gcc did: it replaced the compare's operand with the copy. This is cse's canonicalization: cse made `c` canonical (or `v`?) and rewrote the uses. Hmm, in cse's make_regs_eqv, the direction depends on which reg has more references / lives longer.

v's uses: the compare (1) + the copy source (1) + the reassignment (kill). c's uses: the subtraction (1). So both have 1 use after the copy. cse's canonicalization: "if the dest outlives the source, the dest is canonical". c is born at the copy and dies at the subtraction; v is born at the load and dies at the reassignment (in the if-arm) — hmm, but v's live range extends to the store `*(s16*)p = v` in the if-arm.

Hmm, so v's range is longer → v should be canonical → the copy's use (the subtraction) should be rewritten to read v → giving `addiu v0,v0,-512` ✗. But the observed mine has `addiu v0,v1,-512` (the copy survives for the subtraction) and the COMPARE reads v1.

So gcc rewrote the COMPARE's operand (v → c) and kept the copy for the subtraction. That's cse rewriting v's use to c. So c was canonical.

Hmm! Because... cse's canonicalization: the reg with the LONGER live range becomes canonical? Or the one with more references?

In 80182ED4: t's uses: the compare (1), the copy source (1), the reassignments. u's uses: the subtraction (1). And gcc did NOT rewrite the compare to u. Hmm.

Difference: in 80182ED4, u is used in the ELSE arm (a different block), while t is used in the compare (in the entry block). cse's canonicalization is per-block! In the entry block, u's definition (the copy) is present but u is not USED in the entry block → so within the entry block, cse rewrites t's use (the compare) to u? Hmm, no: cse rewrites uses of the canonical reg.

Hmm, in 80182ED4's entry block: `t = load; tmp = (s16)t; u = tmp; if (t == 0)`. The uses of t: the compare. The use of u: none in this block (u is used in the else block). If cse made u canonical, it would rewrite the compare's t → u. It didn't. So in 80182ED4, t stayed canonical.

In 8018302C's block: `v = load; tmp = (s16)v; c = tmp; if (v >= 0x801) {...}` — the compare's use of v was rewritten to c.

Hmm! So in one case cse rewrote and in the other it didn't. The difference must be in the number of refs or the "canonicalization" rule.

Hmm, maybe the difference is the extra `tmp` in one? No, both have tmp.

Hmm, what differs: in 8018302C, `v` is used LATER (reassigned and stored) — hmm, both.

OK, let me just experiment in the harness. Fast.

Variants:
x1: `v` s32, `if (v >= 0x801)`.
x2: `v` s32, `if (v > 0x800)`.
x3: `v` s16, `if (v >= 0x801)`.
x4: `v` s32, compare written as `if (!(v < 0x801))`.
x5: `v` s32, `if (v >= 0x801)` with the copy `c = tmp` where tmp is s16 but v is read via a different var.

Let me write them.

Note: in the harness the function signature differs from the real one, but the essential structure is there.

Let me run.
