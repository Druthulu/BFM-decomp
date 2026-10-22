---
ts: 2026-10-22T00:00:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AbkNmSE6ORlEQ4aXAMmA
---
Now I see mine's structure:
- s0 = base (incremented at the end: addiu s0,s0,84)
- s1 = p (base+0x58 initially!? and incremented by 84 each iteration)

Hmm: mine[36] `addiu s1,s0,58` → s1 = base + 0x58 = base + 30 + 84 = the SECOND iteration's p! And `lhu v1,-6(s1)` = p[0xb] with p = s1-6?? Hmm: `lhu v1,-6(s1)` loads at s1-6 = base+0x58-6 = base+0x52. And the target has `lhu v1,22(s1)` with s1 = base+0x1E → base+0x1E+0x16 = base+0x34.

Hmm, these don't match. Hmm! base+0x52 vs base+0x34. Hmm, that's a different offset!

Wait — that's the "p[0xb]" access: p[0xb] = *(short*)(p + 0x16) = p + 22 = base+0x1E+0x16 = base+0x34 ✓ (target).
Mine: s1-6 where s1 = base+0x58 → base+0x52. ✗ Different!

Hmm, that means mine's `p` is NOT base+0x1E. Let me re-read: mine[35] `addiu s3,s0,30` → s3 = base+0x1E = p ✓. mine[36] `addiu s1,s0,58` → s1 = base+0x58.

And mine[37] `lhu v1,-6(s1)` → loads at base+0x52. Hmm. But p[0xb] should be at base+0x34.

Hmm, that's wrong! Unless... hmm. Hold on, maybe I misread the target: target[29] `lhu v1,22(s1)` with s1 = base+0x1E → base + 0x1E + 22 = base + 0x34 ✓.

And mine: `lhu v1,-6(s1)` with s1 = base+0x58 → base+0x52.

These are different addresses! That would be a semantic difference... unless mine's s1 is not base+0x58 in the first iteration. Hmm, mine[36] is at address 134c which is the first loop iteration's entry (the loop head is at 1350 per the branch at 13f8 `bnez v0,1350`).

Hmm, so the loop head is 1350 and mine[36] (134c) is before the loop. Hmm, so s1 = base+0x58 is computed BEFORE the loop, and the loop head at 1350 does `lhu v1,-6(s1)`.

Hmm, wait: mine[37] is at 1350 which is the loop head. So the loop body starts with `lhu v1,-6(s1)` = load at s1-6.

And s1 = base+0x58 = base+88. p should be base+30 (s3). So s1-6 = base+82. And p[0xb] = base+52.

Hmm, 82 ≠ 52. So mine computes a DIFFERENT address?! That can't be right — the source is the same.

Hmm, unless the loop was rotated: the loop head is at 1350 and the FIRST iteration's body was partially executed before (at 134c-134c?). Hmm: mine[35] `addiu s3,s0,30` (p=base+0x1E) at 1348, mine[36] `addiu s1,s0,58` at 134c.

Hmm, `addiu s1,s0,58`: 58 = 0x3A. And p[0xb] = p+22 = base+30+22 = base+52 = 0x34. And s1-6 = base+52 ✓✓ (58-6 = 52 = 0x34 ✓).

So s1 = base+0x3A and the load is at s1-6 = base+0x34 ✓ = p[0xb] ✓.

So mine's s1 = base+0x3A = p + 0x1C?? Hmm, p = base+0x1E = base+30. s1 = base+58. Hmm, 58-30 = 28. Hmm, that's p + 0x1C.

Hmm! Interesting. So mine has ANOTHER pointer variable: s1 = base + 0x3A, used as `lhu v1,-6(s1)` (p[0xb]) and `lhu v0,8(s1)` (p[0x12] = s1+8 = base+66 = base+0x42; p[0x12] = p+36 = base+66 ✓) and `lhu v1,0(s1)` (p[0xe] = p+28 = base+58 = s1 ✓).

So gcc strength-reduced: it created a new induction variable s1 = p + 0x1C (hmm, = base+0x3A) and rewrote the accesses relative to it, with p (s3) still used for the store `sh v0,0(s3)`.

So gcc 2.7.2's loop.c DID strength reduction on `p` (creating a new IV). Hmm! But in the target (the original compiler), no strength reduction happened.

Interesting. So to avoid it, the loop shape must be different — e.g., using `goto` instead of `do-while` (as moves.md suggests: "for -> goto loop (no LOOP notes)"), because loop.c's induction variable analysis needs LOOP notes.

Hmm! But wait — the CURRENT source (with the pin) scores 0 (it's the pinned version). Let me verify: does the pinned orig score 0? The src has the pin. Let me score orig.c for this item. If orig scores 0, then the pinned version's code has no strength reduction (because p is pinned to $17, so gcc can't strength-reduce it? hmm, or because...).

AH, that's it! The pin on `p` ($17) prevents gcc's loop.c from strength-reducing p (a pseudo with a hard reg preference can't be replaced by a new IV). So removing the pin lets gcc strength-reduce → different code.

So the fix: prevent the strength reduction while removing the pin. How? The strength reduction happens because `p` is an induction variable (p += 0x2a each iteration, and the loop body uses p[0xb], p[0x12], p[0xe], *p).

Hmm, the target's version increments p by 84 (0x54) — wait! `p += 0x2a` is 42, but the target's `addiu s1,s1,84` is +84! Hmm, 0x2a = 42 ≠ 84.

Hmm! `p += 0x2a` — p is `short *`, so p += 0x2a means 0x2a * 2 bytes = 84 bytes ✓. OK good.

And `base += 0x54` = 84 ✓.

So in the target, both p and base are incremented by 84 in the loop. Since p = base + 0x1E, both are parallel IVs. gcc 2.7's loop.c found `p` as an IV and strength-reduced the memory accesses relative to a new IV.

Hmm, in the target, the accesses are `lhu v1,22(s1)`, `lhu v0,36(s1)`, `lhu v1,28(s1)`, `sh v0,0(s1)` — all relative to s1 = p. So the target did NOT strength reduce.

How to prevent gcc 2.7.2 from strength-reducing? 

Idea: make the loop not a "loop" for loop.c → use `goto` (moves.md: "for -> goto loop (no LOOP notes)"). But the loop's structure with `do {...} while (i < 2)` — the source's `do{}while()` has a LOOP note.

Hmm, but if the target came from a source with a `do-while`, the original compiler (SCEI) didn't strength-reduce. For gcc 2.7.2, we need a spelling that avoids the strength reduction.

Option A: `goto` loop (no LOOP notes → loop.c doesn't run the IV analysis).
Option B: make `p` not an IV candidate: e.g., compute p differently.

Hmm, but hold on: with `goto`, the loop structure changes → the branch structure might differ from the target. The target's loop:
```
13ec: bnez v0,1348    (loop back to 1348)
13f0: addiu s0,s0,84  (delay slot)
```
and the loop head 1348 = `lhu v1,22(s1)`.

With a goto-based loop we'd have a similar structure but the `while (i<2)` test placement might differ.

Hmm, also: in the target, the loop body has multiple exits (goto L530, goto F0, etc.) — the exits jump to L530 (the increment block at 13d8). With a `do-while`, the exits go to the increment. Same with goto.

Let me try: rewrite the do-while as a goto loop:
```c
    base = (s32)&D_800B9A78;
    i = 0;
    sh = 0x30000;
    p = (short *)(base + 0x1E);
Lloop:
    {
        v = (u16)p[0xb];
        ...
    }
L530:
    p += 0x2a;
    sh += 0x10000;
    i += 1;
    base += 0x54;
    if (i < 2) goto Lloop;
```
Hmm, but the `goto F0/DC/L504/L530` labels are inside the loop body; a goto-based loop needs the labels structured so the exits jump to L530.

Careful with C: `goto` into/out of blocks. Let me write:

```c
void func_8012944C(void) {
    s32 base;
    short *p;
    s32 i;
    s32 sh;
    s32 *g = (s32 *)&D_8005128C;
    int v;
    s32 arg;
    if (*g == 0x34420200) {
        *g = 0;
    }
    D_80114EE0 = 1;
    base = (s32)&D_800B9A78;
    i = 0;
    sh = 0x30000;
    p = (short *)(base + 0x1E);
loop:
    v = (u16)p[0xb];
    if (v == 0x7ffe) goto F0;
    if (v < 0x7fff) {
        if (v == 0x7ffd) goto DC;
        goto L504;
    }
    if (v != 0x7fff) goto L504;
    goto L530;
DC:
    if (i != 0) goto L530;
    func_801299C8(1, 1, base);
    goto L530;
F0:
    arg = (i << 0x11) >> 0x10;
    func_801299C8(1, arg, base);
    goto L530;
L504:
    func_801298F4((void *)base);
    arg = sh >> 0x10;
    *p = p[0x12] + p[0xe];
    func_801299C8(1, arg, base);
L530:
    p += 0x2a;
    sh += 0x10000;
    i += 1;
    base += 0x54;
    if (i < 2) goto loop;
}
```

This is the same code but with a goto loop. Let me test it.

Also, maybe the issue isn't loop.c but something else. Let's test.

Note: the current source's `do { ... } while (i < 2)` — the exits `goto L530` jump to the increment block, then the while test. With goto, `goto L530` → increment → `if (i<2) goto loop`. The control flow should be the same.

Let me write this as c2.c and score.

Also worth trying: keep the do-while but make `p` a `short *` that is recomputed each iteration (e.g. `p = (short *)(base + 0x1E)` inside the loop) — that would change the code (an extra addiu per iteration) ✗.

Let me try the goto version.
