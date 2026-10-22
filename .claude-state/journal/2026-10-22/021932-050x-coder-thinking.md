---
ts: 2026-10-22T08:19:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hLj9s81lWrNa0ypXEo2y
---
In y1 (two arms), the FIRST arm's compare reads a1 (the copy) but the SECOND arm's compare reads v1 (the original)! Interesting asymmetry — the second arm has the copy AFTER the compare (scheduled later: `slti v0,v1,2049` then `bnez` then the delay slot `move a1,v1`).

So in the second arm, gcc scheduled the copy into the bnez delay slot (after the compare), and the compare reads the original ✓. But the target has the copy BEFORE the compare in BOTH arms:
```
34b8: move v1,v0
34bc: slti v0,v0,2049
...
34d8: move v1,v0
34dc: slti v0,v0,2049
```
Hmm! Wait, let me re-read the target:
```
34b0: lh v0,24(a0)
34b4: nop
34b8: move v1,v0        <- copy 1
34bc: slti v0,v0,2049   <- compare 1 (reads v0)
34c0: bnez v0,34d0
34c4: addiu sp,sp,-16   <- delay slot
34c8: addiu v0,v1,-512
34cc: sh v0,24(a0)
34d0: lh v0,26(a0)
34d4: nop
34d8: move v1,v0        <- copy 2
34dc: slti v0,v0,2049   <- compare 2 (reads v0)
34e0: bnez v0,34ec
34e4: addiu v0,v1,-512  <- delay slot
34e8: sh v0,26(a0)
```
So in the target, BOTH copies come before their compares, and the compares read v0 (the original).

In my y1: arm 1 has the copy before the compare (and the compare reads the copy: `slti v0,a1,2049`), arm 2 has the copy in the delay slot (after the compare).

So I need the copy BEFORE the compare in both arms AND the compare to read the original.

Hmm. So the target's structure: the copy is before the compare and the compare reads the original.

Since the copy's value == the original's value (in gcc's view), gcc can use either. In the target (with the $0 pin), gcc kept them distinct (no equality) → the compare read the original.

So I need the copy to be "distinct" from v in gcc's view — but the copy must still be a plain `or` (32-bit copy).

Hmm! What if the copy's temp is `s16` and the copy's dest `c` is `s32`, and the COMPARE reads `v`... that's the current shape and gcc substitutes.

Hmm, what if the compare reads the ORIGINAL LOAD EXPRESSION via a variable that gcc can't equate to c? What if we keep the loaded value in TWO variables?

```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; ... }
```
The equivalence chain v → tmp → c.

What if we break the chain by making the copy's source NOT v but a re-load? ✗ extra lh.

Hmm, what if the compare reads `tmp` (the s16 temp) instead of v?
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (tmp >= 0x801) { v = c - 0x200; ... }
```
Hmm: `tmp >= 0x801` — tmp is s16 → promoted to s32 (sign-extended) → `slti v0,v?,2049` where ? = tmp's reg. And c = tmp's value → the compare could read c's reg (the copy) — same problem? Hmm, but maybe not: the compare's operand would be tmp (QImode) → promoted → and gcc knows sign_extend(tmp) == v == c. Hmm.

Hmm, but the SIGN-EXTENSION of tmp: the compare `tmp >= 0x801` needs tmp's value sign-extended to 32 bits. If tmp's reg holds the sign-extended value (as gcc's convert does), the promotion is free ✓. Then the compare reads tmp's reg.

Hmm, and which reg is tmp's? tmp is dead after the copy → its reg could be reused for the copy (c)?? Then the compare would read the copy's reg → ✗ again? Hmm, but they'd be the same VALUE, so the compare reading c's reg is fine VALUE-wise — but the target's compare reads v0 (the original's reg) and the copy is v1.

Hmm! So the register assignment matters: the compare's operand reg must be v0 (the load's reg) and the copy's reg v1.

In y1's second arm: the compare read v1 (the load's reg) and the copy got a1 ✓ — the right shape! And in the first arm it was the opposite.

So the SCHEDULER decides where the copy goes. In the target, the copy is before the compare in both arms.

Hmm, so what makes the scheduler place the copy before the compare? In the target, the copy is a separate insn `or v1,v0` that must be executed before the compare? No — the compare doesn't depend on the copy.

Hmm, in the target the copy is BEFORE the compare in the instruction stream. That's the scheduler's choice (the copy is independent).

So I need: (1) the copy to survive, (2) the compare to read the original, (3) the copy scheduled before the compare.

In my c2.c (the real function), the copy IS before the compare ✓ (matching) but the compare reads the copy ✗.

Hmm, so in the real function the schedule already matches; only the operand choice is wrong.

Let me think about the operand choice: the compare `v >= 0x801` → gcc's combine produces `(set (reg) (ge (reg v) (const 2049)))` → hmm, actually `v >= 0x801` → gcc computes `v < 0x801` → `(set (reg) (lt (reg v) (const 2049)))` → the branch is `bnez` on that reg.

The compare's OPERAND is v. gcc substituted v → c. That's cse's canonicalization.

**How to prevent cse from canonicalizing c over v?**

cse's make_regs_eqv decides the canonical reg. The relevant code (gcc 2.7 cse.c) — I'm going to reconstruct it from the G02 note: "iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1".

So the rule involves LIVENESS: the reg that OUTLIVES the other becomes canonical.

In our case: c is born at the copy (after the load) and dies at the subtraction (inside the if-arm). v is born at the load and dies... v is reassigned in the if-arm (`v = c - 0x200`) and then stored. So v's range: [load, if-arm's reassignment]. That's LONGER than c's range ([copy, subtraction])!

Hmm, so v should be canonical (it outlives c) → the copy's use (the subtraction) would be rewritten to v → `addiu v0,v0,-512` ✗. But the observed result has the copy surviving for the subtraction (addiu v0,v1,-512) and the COMPARE rewritten to c. So c was canonical for the compare.

Hmm, confusing. Maybe the rule is about REFERENCES: cse's make_regs_eqv:
```c
  /* If the destination has more references than the source, keep the
     destination as canonical... */
```
Hmm.

OK, empirically: in 80182ED4 (which MATCHED), the compare was NOT substituted; in 8018302C it WAS. Let me find the structural difference:

80182ED4: `t = load; tmp = (s16)t; u = tmp; if (t == 0) {A} else { t = u - 1; }`
- The compare's operand: t (used after the copy ✓)
- The copy's dest u: used in the else arm.

8018302C: `v = load; tmp = (s16)v; c = tmp; if (v >= 0x801) { v = c - 0x200; store v; }`
- The compare's operand: v (used after the copy ✓)
- The copy's dest c: used in the then arm.

Structurally the same! The difference: the compare form (`== 0` vs `>= 0x801`) and the branch polarity (the else vs the then).

Hmm! In 80182ED4, the copy's use (u) is in the ELSE arm and the compare's branch is `if (t == 0)`. In 8018302C, the copy's use (c) is in the THEN arm.

Hmm, in 8018302C, the copy's dest c is used INSIDE the then-arm (the block guarded by the compare). So the compare's branch condition and the copy's use are in a parent/child block relation. cse's canonicalization might work differently across the CFG.

Hmm, alternatively: in 8018302C, `v` is REASSIGNED inside the then-arm (`v = c - 0x200`), so v's value at the compare is dead after the compare on the then-path, and c is live → the "reverse copy" rule fires: cse rewrites v's uses (the compare) to c, since v is dead after the compare but c is live!

In 80182ED4, `t` is reassigned in BOTH arms (t = 0x1E in the then, t = u-1 in the else) — hmm, so t is also dead after the compare. Hmm. ✗

Hmm, but in 80182ED4 the copy's dest u is used in the ELSE arm only, and the compare's then-arm is the big block with calls.

ARGH.

Let me try the EXPERIMENT: modify the real function so that the compare's operand is used after the compare in a way that keeps it live. Hmm.

Alternatively, let me try making the copy's dest used in a way that...

Hmm, let me try a completely different tack for 8018302C: **what if the copy's source is not `v` but the value is copied via the temp in the opposite direction**, i.e. what if the compare reads the copy's SOURCE (tmp) and the copy's dest is used in the subtraction, with the regs such that the compare's reg is v0?

Target: compare reads v0 (the load's reg), the subtraction reads v1 (the copy's reg).

What if:
```
v = *(s16 *)(p + 0xC);   /* v → v0 */
tmp = (s16)v;            /* tmp: the truncation */
c = tmp;                 /* the copy: c → v1 */
if (v >= 0x801) { v = c - 0x200; ... }
```
The problem is only that gcc rewrites the compare's operand v → c.

**IDEA**: what if we make the compare read a variable `w` that holds the value but is NOT in the equivalence chain? E.g.:

```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { ... }
```
The chain is v ≡ tmp ≡ c.

What if we do:
```
v = *(s16 *)(p + 0xC);
w = v;             /* plain copy: w ≡ v, but cse would merge w and v */
tmp = (s16)v;
c = tmp;
if (w >= 0x801) { v = c - 0x200; ... }
```
Now the chain: w ≡ v ≡ tmp ≡ c. Same.

Hmm.

**IDEA**: what if the compare's operand is the LOAD EXPRESSION, i.e. `*(s16 *)(p + 0xC) >= 0x801`, and the copy is of the loaded value? Then gcc would CSE the two loads into one (cse merges the loads) → the compare would read the load's reg ✓ and the copy... hmm, cse merging the loads means the compare reads the same reg as the copy's source ✓✓!

Hmm! Let me think: `if (*(s16 *)(p + 0xC) >= 0x801)` and `v = *(s16 *)(p + 0xC);` — cse would merge the two loads into one load (they're the same address, no intervening store) → one `lh` → and the compare reads that reg. And the copy `c = tmp` reads it too.

Hmm, but then the compare's operand = the load's reg = v0 ✓ and the copy's dest = v1 ✓!

Hmm, but would cse merge the loads? The address is `p + 0xC` where p is a pointer — cse can merge two loads with the same address if there's no store between ✓ (the same pseudo p).

Hmm, but the source would then have the load expression twice, which the C compiler (gcc's front end) would also merge? gcc's front end doesn't do that, but cse does.

Hmm, but there's a catch: the compare's operand would be the merged load's reg — which is the same reg as the copy's source. The target's compare reads v0 = the load's reg ✓.

Let me test this! In the harness:
```c
int y3(short *p) { int v; int c; short tmp; v = *(short*)p; tmp = (short)v; c = tmp; if (*(short*)p >= 0x801) { v = c - 0x200; *(short*)p = v; } return v; }
```
Hmm, but careful: the store `*(short*)p = v` is inside the if-arm; the compare's load is before it ✓.

Hmm, but there's a risk: gcc's front end might reorder/duplicate. Let me test.

Actually hold on. There's a subtlety: with the load expression in the compare, the "v" variable is only used for the copy. And cse merges the two loads → the compare reads the merged reg ✓.

But hmm, would gcc's combine then substitute the copy (c) into the compare? The compare's operand is the merged load reg; c = tmp = (s16)(that reg). The equality chain: loadreg ≡ tmp ≡ c. So cse could still rewrite the compare to c. Hmm. But maybe the fact that the load is a MEM (not a pseudo) breaks the chain: cse's equivalence is between pseudos; the load's reg is a pseudo too...

Hmm. Let me just test.

Another idea: use the ORIGINAL v but ALSO keep v alive after the compare by using it in the then-arm: `v = c - 0x200` — v IS used there. Hmm.

Let me just try several variants in the harness quickly (y3 = the merged-load compare; y4 = the compare on a re-load with a different expression form).

Let me run.
