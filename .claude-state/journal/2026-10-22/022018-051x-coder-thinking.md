---
ts: 2026-10-22T08:20:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Uf1qW80TkTAAiGSXLvnb
---
Both y3 and y4 give the compare reading the ORIGINAL (v1) and the copy in a1. So in isolation the shape is right — the problem is only in the real function.

y3 (the merged load): the compare reads v1 (the load) ✓ and the copy is `move a1,v1` — but it's in the delay slot (after the branch) ✗ order-wise.

y4 (same as before but with the compare after): the compare reads v1 ✓, the copy `move a1,v1` at index 34 — hmm, that's AFTER the bnez (in the if-arm) ✗ order.

Hmm! In y4 (identical to y1's first arm), the copy is in the if-arm (after the branch). But in the REAL function (c2.c), the copy is BEFORE the compare. So the real function's schedule differs (because of the frame/delay slot pressure: the bnez's delay slot in the real function holds `addiu sp,sp,-16`).

So in the real function, the delay slot is taken by the frame setup → the copy can't go there → it's scheduled before the compare. But then gcc's substitution (the compare reading the copy) happened.

Hmm, so the substitution is a separate issue.

OK, so two things to fix in the real function:
(a) the compare must read the original (v0), not the copy (v1);
(b) the copy must be before the compare.

In the real function, (b) holds but (a) fails. In the harness, (a) holds but (b) fails.

Hmm! Interesting. So maybe the fix is to make the compare read the original in the real function. What makes the real function substitute? Let me test the real function with the y3-style change (the compare using the load expression `*(s16 *)(p + 0xC) >= 0x801`).

Hmm, but in the real function, the load expression appears twice → cse merges → the compare reads the merged load's reg.

Hmm, but that doesn't change the equivalence to c.

Hmm. Let me think about (a) differently: what if the compare's operand is `v` and we prevent the substitution by making the copy's value NOT equal to v — using a **u16 temp** but where the zero-extension is free? For that, v's high bits must be known zero — v is a sign-extended lh ✗.

Hmm, what if we change the LOAD to `lhu` (unsigned read)? Then v's high bits ARE known zero → `tmp = (u16)v` is a no-op → `c = tmp` → the zero extension is free → the copy becomes `or v1,v0` ✓ and c ≠ v in gcc's view? Hmm: c = zero_extend(tmp) where tmp = (u16)v = v (since v's high bits are zero) → c == v numerically, but gcc's RTL: `(set c (zero_extend:HI (reg tmp:HI)))` — hmm, if v's high bits are known zero, combine folds the zero_extend → `(set c (reg tmp))` → a plain copy → cse propagates ✗.

Hmm.

OK, let me try yet another approach for (a): make the compare's operand a variable that is NOT the copy's source and NOT equal to it in gcc's view — i.e. keep the ORIGINAL load value in `v` and make the copy be of a DIFFERENT but numerically-equal value. The only such value is a re-load (extra insn) ✗.

Hmm, OR: make the copy's value differ from v in the SOURCE but produce the same asm: e.g. the copy is `c = v` where v is the loaded value, but the compare uses a variable `w` that was assigned the loaded value EARLIER (before the copy) — then w ≡ v ≡ c anyway.

Hmm.

Hmm, let me reconsider: is (a) really "the compare must read the original"? The target: `slti v0,v0,2049` — the compare's source is v0 and the load is `lh v0,24(a0)` → v0. So yes, the compare reads the load's reg.

But hold on! What if in the target, v0 is NOT the load's reg? What if the load went to v1 and the copy to v0? The target: `lh v0,24(a0)` → v0 is the load ✓. And `move v1,v0` → v1 = the copy. And `slti v0,v0,2049` → the compare reads v0 = the load ✓. So yes.

So: the compare must read the load's reg, and the copy must be in a different reg.

In our c2.c, the copy is in v1 and the compare reads v1 → the compare reads the COPY's reg, and the load's reg (v0) is unused after the copy. So the compare's operand was replaced by the copy's value.

**IDEA**: what if we make the compare read the load's reg by ensuring the copy's value is "older"? E.g., what if the copy is made BEFORE the compare in the source but the compare uses a variable that is NOT part of the equivalence class?

The equivalence class is formed by the copy `c = tmp` and `tmp = (s16)v`.

What if the copy's source is a temp that is NOT derived from v in gcc's view? E.g.:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
```
tmp IS derived from v.

Hmm, what if we reverse:
```
tmp = *(s16 *)(p + 0xC);   /* tmp: the load */
c = tmp;                  /* the copy (HImode→SImode) */
v = tmp;                  /* v: the value for the compare */
if (v >= 0x801) { v = c - 0x200; ... }
```
Hmm: `v = tmp` is another copy (SImode from QImode) → and `v` is used in the compare. The equivalence class {tmp, c, v} again ✗.

Hmm!! The problem is fundamental: gcc knows the copy's value equals the original.

**UNLESS the copy's value is NOT equal to the original in gcc's view** — which requires the copy to be lossy or the source to be different.

Hmm, what if the copy's source is a value with a KNOWN range that makes the s16 round trip lossy? E.g., if the source were a u32 value > 32767, then (s16) truncates → c ≠ v. But our source is a sign-extended s16 → the round trip is exact.

Hmm, BUT: does gcc KNOW it's exact? gcc folded the sign extension away (no sll/sra) — so it treated it as exact.

Hmm, what if the source is `v` as an `unsigned` interpretation? I.e. what if the load is `lh` (sign-extended) but we treat v as unsigned for the copy:
```
v = *(s16 *)(p + 0xC);     /* v: s32, sign-extended */
tmp = (u16)v;              /* the truncation to u16: lossy for negative values */
c = tmp;                   /* c = zero_extend(tmp) */
```
Then c ≠ v in gcc's view ✓ (no substitution!). But the copy would need the zero extension → `andi` ✗... UNLESS gcc folds it because... hmm, v's high bits are unknown.

Hmm, BUT: what if the copy's asm could be `or v1,v0` anyway? The zero_extend of v to 16 bits... no.

Hmm, hold on! What if the copy is `(u16)` and the value is then used in a way where the truncation is free? `v = c - 0x200` — c is u16 → promoted to s32 (zero-extended) → the subtraction `c - 0x200` → hmm, `addiu v0,v1,-512` requires c's full 32-bit value. If c = (u16)v (zero-extended), then c - 0x200 ≠ v - 0x200 for negative v → SEMANTICS CHANGE ✗ (the target computes v - 0x200 with the sign-extended value).

Hmm, so the copy must preserve the sign-extended value.

OK, so c == v necessarily. And gcc substitutes.

Hmm, so how do we prevent the substitution while keeping the copy?

**IDEA**: make the compare's operand be a value that is used LATER (so it's live at the compare and after) — in the target, `v` is reassigned inside the if-arm, so v's value at the compare is dead after. If we could make v's value live past the compare (e.g. used after the branch), then the substitution would be "safe" but gcc might still do it (the value is the same).

Hmm, in gcc, the substitution of the compare's operand v → c happens because c holds the same value. It doesn't matter whether v is live.

Hmm.

**IDEA**: use a DIFFERENT comparison that produces the same asm but reads a different value. E.g. compare `v` with 0x801 in a form that gcc computes from a different reg.

Hmm, what about `if (v - 0x801 >= 0)`? → `slti`? no, that'd be a different sequence.

Hmm, what about `if ((unsigned)v >= 0x801)`? → `sltiu` ✗.

Hmm.

**IDEA**: what if the copy's dest is used in the compare, but the copy is scheduled such that the compare's operand ends up being v0? In the target the compare reads v0. Hmm.

OK — alternative approach: **make the copy's reg be a1/a2 instead of v1**, so the compare can read v0 while the copy is elsewhere. But the target's copy is in v1 ✗ (the byte-identical requirement).

Hmm.

Hmm, hold on. Let me reconsider: in the real function, mine has `lh v0` ; `move v1,v0` ; `slti v0,v1,2049` ; `bnez` ; `addiu v0,v1,-512` ; `sh v0`.

The target: `lh v0` ; `move v1,v0` ; `slti v0,v0,2049` ; `bnez` ; `addiu v0,v1,-512` ; `sh v0`.

So the ONLY difference is the compare's operand: v1 vs v0.

What if the compare's operand reg were v0 because the copy went elsewhere? No — the copy is `move v1,v0` in both.

So: I need the compare to read v0 (the load's reg) while the copy occupies v1.

In gcc terms: the compare's operand must be the load's pseudo, not the copy's pseudo.

**IDEA**: what if the compare reads the load's pseudo directly and the copy is of a DIFFERENT pseudo? The copy `or v1,v0` copies the load's value...

Hmm, hmm. What if we introduce the copy from a temp that gcc keeps distinct:
```
v = *(s16 *)(p + 0xC);       /* the load → pseudo L */
tmp = (s16)v;                /* tmp: QI pseudo */
c = tmp;                     /* the copy */
if (v >= 0x801) { ... }
```
The chain: v ≡ tmp ≡ c.

**What if we make the compare read `tmp` instead of `v`?**
```
if (tmp >= 0x801) { v = c - 0x200; ... }
```
tmp is QI → the comparison promotes it to SI (sign-extend). If the promotion is free (gcc knows tmp holds a sign-extended value), the compare reads tmp's reg. And tmp's reg vs c's reg: the copy `c = tmp` — if tmp's reg is reused for c (tmp dies at the copy), then the compare would read c's reg ✗. Hmm, but the compare is AFTER the copy, so tmp is dead → its reg can be c's reg → the compare reads c's reg (v1) ✗.

Hmm! Unless the compare reads the LOAD's reg (v0) — which is what we want. So the compare should read `v`.

ARGH.

OK, let me try the practical approach: try MANY small variants on the real function and see if any gives score 0. Variants:
1. The compare reads the load expression `*(s16 *)(p + 0xC) >= 0x801` (y3-style).
2. The compare reads `v` but the copy is `c = tmp` with tmp as `u16`... ✗ (andi)
3. Make the subtraction `v = c - 0x200` → `v = c - 512` (same).
4. Use `if (v >= 0x801)` with v as `s32` and the copy's temp `s16`, but ALSO use `c` in the compare... no.
5. What if the compare is on `c` and the subtraction on `v`? (roles swapped) — analyzed: the compare and the subtraction would both read c → the same reg → but the target has them different ✗. Hmm, wait, let me redo this: if the compare reads c and the subtraction reads c, then the compare's operand reg = the subtraction's source reg. The target: the compare's operand = v0, the subtraction's source = v1 → DIFFERENT. So ✗.

Hmm, unless... the compare reads c (v0) and the subtraction reads v (v1): `v = v - 0x200`?? That changes the semantics (the target computes c - 0x200 where c == v, so numerically the same!). Hmm! Actually c == v numerically, so `v = v - 0x200` is numerically the same as `v = c - 0x200`. But the asm would be `addiu v1,v1,-512` (v in v1) vs the target's `addiu v0,v1,-512` ✗.

Hmm.

6. What if we make the copy's destination be used in the compare AND make the compare read the load: e.g. `if (v >= 0x801 && c == c)`? Extra insns ✗.

Hmm.

7. **What if we make the compare's operand be the load's reg by keeping the load's pseudo alive with an extra use that costs nothing?** Hmm.

8. **What if the copy is placed AFTER the compare in the source but the scheduler hoists it before?** The scheduler hoists independent insns. If the copy is inside the if-arm, the scheduler can't hoist it before the branch (it's in a different block) ✗.

Hmm, unless the copy is in the entry block AFTER the compare's load but the compare is also in the entry block... the compare IS the branch.

Hmm! What if the comparison is COMPUTED into a variable before the branch?
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
cond = v >= 0x801;      /* the compare → a boolean in a reg */
if (cond) { v = c - 0x200; ... }
```
Then the compare's operand is v (the load's reg) and the branch tests `cond`. The asm would be: `slti v0,v0,2049` (or `sltiu`) then `beqz/bnez cond`. Hmm, the target's asm is `slti v0,v0,2049` + `bnez v0` — the branch reads the SAME reg as the slti's dest! So `cond` must be the same reg as the slti's dest (v0). With `cond = v >= 0x801` → gcc computes `slti v0,v0,2049`? Hmm: `v >= 0x801` → gcc computes `v < 0x801` (inverted) → `slti v0,v?,2049` then the branch is `bnez` (skip the block if v < 2049).

With a boolean variable, gcc would compute `cond = (v >= 0x801)` as `sltiu cond,v,2048`?? Hmm, `v >= 0x801` → `(set cond (ge v 2049))` → gcc's mips: `sltiu cond, v, 2049` then `xori`? Hmm, gcc usually converts `x >= C` to `!(x < C)`. With a boolean assignment, gcc would materialize the boolean as 0/1 → `sltiu cond,v,2049; xori cond,cond,1`? That'd be extra insns ✗.

Hmm. But maybe gcc keeps the branch form: `if (cond)` → gcc's flow would use the boolean's reg directly with `beqz cond` → but the boolean must be 0/1 → the extra xori. Hmm, unless gcc's "jump threading" converts it back. Risky.

Hmm, but actually: gcc's front end for `if (v >= 0x801)` produces a branch directly with the comparison in the branch's insn. With `cond = (v >= 0x801); if (cond)`, the front end materializes the boolean. In gcc, `sltiu`+`xori` might be avoided: gcc's mips has a "sltiu + beqz" pattern... Hmm.

Let me just test it in the harness:
```c
int y5(short *p) { int v; int c; short tmp; int cond; v = *(short*)p; tmp = (short)v; c = tmp; cond = (v >= 0x801); if (cond) { v = c - 0x200; *(short*)p = v; } return v; }
```
Let me see what asm comes out.

Hmm, this is taking a lot of time. Let me consider the overall budget: I've used ~1h35m. I have 2 items left (8018302C and 8017E6EC). Let me time-box 8018302C to ~15 more minutes, then do 8017E6EC, then write up.

Let me try a batch of real-function variants in one sc.sh call:
V1: the compare as a boolean variable.
V2: the compare reading the load expression.
V3: `if (v >= 0x801)` with the copy `c = tmp` and an extra use of v after (e.g. `v = c - 0x200;` → keep).
V4: the copy via `tmp` where tmp is s16 and c is s32, but the compare uses `v` — with the arms SPLIT (c1/c2) — already tried (score 11).

Hmm. Let me think about V2 more: the compare reads `*(s16 *)(p + 0xC)` — gcc's cse would merge the two loads. Then the compare's operand = the merged load's pseudo. And c ≡ that pseudo. So the substitution could still happen. But maybe cse's merging of the loads happens differently (the load is a MEM; cse creates a reg for it).

Hmm, hmm.

**COMPLETELY DIFFERENT IDEA**: what if we make the copy's SOURCE a hard register?! Remember the hard-reg rule: a copy FROM a hard reg escapes cse.

In the real function, is there any hard register holding the loaded value at that point? No.

BUT!!! What about this: the copy `c = tmp` — what if `tmp` is a **function parameter**? no.

Hmm, what about the LOAD being into a hard register: gcc's `lh` into a pseudo → the pseudo is allocated later.

Hmm.

OK, let me try yet another idea: **what if the copy is not a copy of v but of the RESULT of the comparison?** no.

Let me look at this from the "what does the target's C look like" angle: the target's source (given) is `c = v + z;` with z pinned to $0. The lever-free equivalent must produce `or v1,v0`. The ONLY difference between the target and my c2.c is that the target's copy has a hard-reg addend (no equality) while mine has an equality.

**What if we make the copy's addend a hard register via a DIFFERENT mechanism than a pin?**

Hmm! What about `c = v + z` where `z` is a variable that gcc's RTL represents as `(reg 0)`? Only pins.

Hmm, what about the **`-` "zero" via a `volatile`?** no.

Hmm, what about **`c = v` where v is a `long long`?** ✗

What about `c = v` where the copy is done via a **`memcpy` of 4 bytes**? ✗ (a load/store).

Hmm, what about `c = v` where v is an **array element**? ✗

OK, what about this: the equality between v and c is what lets gcc substitute. What if we BREAK the equality by making the copy's value differ from v in a way that produces the same asm?

The asm `or v1,v0` means c = v (32-bit). So no.

Hmm, unless the copy is of a value that EQUALS v but is a different computation, e.g. `c = v + 0` where the 0 is... folded.

WAIT!!! What about `c = v` where the C is `c = v - 0`? Folded. `c = v ^ 0`? Folded. `c = v | 0`? Folded.

Hmm, what about `c = v` where v is a `volatile`-qualified... no.

Hmm, what about **`c = v` where the copy is written with a COMMA/conditional that gcc compiles to a copy**? e.g. `c = (v, v)` → folded to v.

What about `c = v` where the RHS is a `cast` that gcc implements as a no-op but keeps in the RTL? Like `(s32)(s32)v` → folded. `(u32)(s32)v` → hmm! A cast from s32 to u32: gcc's convert_to_mode(SImode, ...) with unsignedp → the RTL is the same mode → gcc folds it (no-op) → plain copy ✗.

Hmm.

What about a cast to a 64-bit type? `c = (s64)v` → a sign extension to 64 bits ✗ (different asm).

Hmm.

OK — time check. Let me consider whether 8018302C can be a WALL and move on to 8017E6EC (which has a different mechanism: the register swap). Actually, wait — 8017E6EC's residual was "the constant 0x10 is in v0 but should be in v1". That's a global-alloc/local-alloc ordering issue. Hmm.

Hmm, hold on! For 8018302C, let me reconsider the y3 experiment: the compare reading the load expression. In the real function, let me try that. And also try the boolean-variable version. Let me batch them.

Actually, here's ANOTHER idea for 8018302C that might work: **make the copy's temp `s16` and the compare read `v`, but ALSO give `v` an extra use after the compare that gcc can't remove** — e.g. use v in the store: `*(s16 *)(p + 0xC) = v;` — that's already there (v is reassigned first).

Hmm.

Hmm, what about: make the subtraction write to a DIFFERENT variable so that v stays live:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) {
    w = c - 0x200;
    *(s16 *)(p + 0xC) = w;
}
```
Now v is live after the compare (v is used in the compare only... hmm, v's value is dead after the compare; v is not reassigned). Hmm, so v's value dies at the compare → cse's reverse-copy rule fires → the compare's v → c ✗ (same).

Hmm, opposite: we want v's value to STAY LIVE after the compare so the reverse rule doesn't fire. E.g. use v after:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) {
    w = c - 0x200;
    *(s16 *)(p + 0xC) = w;
}
```
v is dead after the compare ✗.

What if v is used after the if-block?
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) {
    v = c - 0x200;
    *(s16 *)(p + 0xC) = v;
}
```
v is reassigned inside → v's value dead after the compare.

Hmm, what if we DON'T reassign v but keep it:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) {
    w = c - 0x200;
    *(s16 *)(p + 0xC) = w;
}
```
Then v's value is dead after the compare too (v isn't used later) → gcc would DCE v's assignment... and the compare would use c.

Hmm, what if v is used after the whole if:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { w = c - 0x200; *(s16*)(p+0xC) = w; }
use(v);   /* v's value live after */
```
Hmm, but v's value after the if is the ORIGINAL v (not modified) — that changes the semantics? The original code's `v` is modified inside the if. Hmm, in the original:
```
v = *(s16 *)(p + 0xC);
c = v + z;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p + 0xC) = v; }
```
v is modified inside. If I use a separate w, then v keeps its old value — but v isn't used after in the original either. So it's semantically equivalent to the original (v is dead after).

But the "use(v)" would add an insn ✗.

Hmm.

OK, let me try the empirical batch on the real function. 4 variants, one sc.sh call (~2 min):
R1: the compare reads the load expression `*(s16 *)(p + 0xC) >= 0x801`.
R2: the compare uses a boolean variable.
R3: `c` is s16 and the compare uses `v` (the compare reads v; c is used in the subtraction). — c3 was s16 c and score 10 (the copies vanished). Hmm, because with c as s16, `c = tmp` is a same-mode copy → cse merged it. ✗
R4: the copy's temp is `s16`, the copy's dest is `s32`, and the compare reads `v` — but the subtraction is `v = c - 0x200` where c is...

Hmm, let me think about R1's likely outcome: the compare reads the merged load's pseudo; c ≡ that pseudo → the substitution may still occur. But maybe the load's pseudo is "older" and cse keeps it canonical.

Let me just try R1 and R2.

Also R5: what if the copy is placed in the entry block and the compare uses `v`, but the copy's temp is `s16` AND the copy is `c = tmp` where tmp is loaded directly:
```
v = *(s16 *)(p + 0xC);
tmp = *(s16 *)(p + 0xC);   /* a second load of the same address */
c = tmp;
if (v >= 0x801) { v = c - 0x200; ... }
```
cse merges the two loads → one lh → then v and tmp are the same pseudo → c ≡ v ✗ same problem.

OK, R1/R2 it is. Plus:
R6: swap the roles so that the COMPARE uses the copy `c` and the SUBTRACTION uses the copy `c` too... no.

Let me also consider R7: **use `c` in the compare but write the compare so that gcc keeps the ORIGINAL for the subtraction**:
```
if (c >= 0x801) { v = c - 0x200; ... }
```
Here the compare reads c and the subtraction reads c → the same reg → the target has them different ✗. BUT hold on: what if the compare's operand is c (the copy, v1) and the target's compare operand is v0 (the load)? ✗.

OK R1, R2 and let me also try R8: make the copy's source a `u16` temp but with the value coming from a `lhu`-style load...

Hmm! Actually WAIT. Let me reconsider: the load is `*(s16 *)(p + 0xC)` — an s16 load → `lh` → sign-extended. What if I write the load as `*(u16 *)(p + 0xC)`? Then the load is `lhu` ✗ (the target has lh).

Hmm.

Let me just run R1, R2, and also R9: the compare `if (v >= 0x801)` where the copy is `c = tmp` and tmp is s16 — but with the SECOND arm using a different temp (c4 was that: score 11).

Let me look at c4's diff to understand score 11 — maybe it's informative.

Let me run R1, R2 and look at c4's diff in one go.
