---
ts: 2026-10-22T05:17:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_gNpiJXH0x03HnHeWESLr
---
r2 is very close! 15 mismatches, 91 ins ✓. The differences:
1. The prologue order: mine has `sw s1,20(sp)` at ins 3 while the target has it at ins 1 (before the `lui s1`/`addiu s1`) — a scheduling difference in the prologue.
2. `sw a0,-20(s0)` placement (mine at 33, the target at 37) — a scheduling difference.
3. `lhu v1,-2(s0)` vs `lhu v1,0(s0)` — the q-0x4 address: the target uses offset -2, mine uses 0 with a different base?! Hmm: mine[64] `lhu v1,0(s0)` vs target[63] `lhu v1,-2(s0)`. Hmm, the target: `lhu v1,-2(s0)` = q-2 ✓ (the source: `*(u16 *)(q - 0x4)`?? hmm, -2 vs -4).

Hmm, the source has `*(u16 *)(q - 0x4)` → the target has `lhu v1,-2(s0)` — hmm, that's q-2! So the target's s0 is not q but q+2! Hmm!

Hmm, wait: the target's `lhu v0,-74(s0)` (q-0x4A) ✓ and `lhu v1,-2(s0)` — hmm, the source's `*(u16 *)(q - 0x4)`. Hmm, -2 ≠ -4.

Hmm, so the target's s0 = q + 2?? Then `lhu v0,-74(s0)` = q+2-74 = q-72 = q-0x48 ✗ (the source says q-0x4A). Hmm.

Hmm, let me recheck the target listing:
```
80178580: lhu v0,-78(s0)     <- q-0x4E ✓
80178584: lhu v1,-4(s0)      <- q-0x4 ✓
80178594: lhu v0,-74(s0)     <- q-0x4A ✓
80178598: lhu v1,-2(s0)      <- q-0x2 ✗ (the source says q-0x4A? no)
```
Hmm: the source:
```
*(s16 *)(w + 8)  = *(u16 *)(q - 0x4E) + *(u16 *)(q - 0x4);
*(s16 *)(w + 10) = *(u16 *)(q - 0x4A) + *(u16 *)q;
*(s16 *)(w + 0xC) = *(u16 *)(q - 0x46) + *(u16 *)q;
```
So the pairs are: (q-0x4E, q-0x4), (q-0x4A, q), (q-0x46, q).

The target:
- 80178580: lhu v0,-78(s0) = q-0x4E ✓; 80178584: lhu v1,-4(s0) = q-0x4 ✓
- 80178594: lhu v0,-74(s0) = q-0x4A ✓; 80178598: lhu v1,-2(s0) = q-0x2 ✗ (should be q!)

Hmm! q-0x2 ≠ q. Hmm, so the target's s0 ≠ q? Let me re-derive: s0 = s1 + 84 = p + 0x54 = q ✓. And `lhu v1,-2(s0)` = q - 2. But the source wants `*(u16 *)q`.

Hmm! Unless the source's `*(u16 *)q` is at a different offset... The src (orig.c) says `*(u16 *)(q - 0x4A) + *(u16 *)q;` hmm.

Hmm, but hold on: `lhu v1,-2(s0)` — hmm, maybe gcc used a base of q-2 for the `*(u16*)q` read? That'd be an address difference of 2 ✗ — a semantic difference!

Hmm, wait: maybe the target's `lhu v1,-2(s0)` corresponds to `*(u16 *)(q - 0x4)` and the `lhu v1,-4(s0)` to something else. Let me recheck the ordering in the target:
```
80178580: lhu v0,-78(s0)    ; q-0x4E
80178584: lhu v1,-4(s0)     ; q-0x4
80178588: nop
8017858c: addu v0,v0,v1
80178590: sh v0,8(a0)
80178594: lhu v0,-74(s0)    ; q-0x4A
80178598: lhu v1,-2(s0)     ; q-0x2  <- hmm
8017859c: lw a0,-52(s0)     ; q-0x34
801785a0: addu v0,v0,v1
801785a4: sh v0,10(a0)
801785a8: lhu v0,-70(s0)    ; q-0x46
801785ac: lhu v1,0(s0)      ; q
801785b0: lw a0,-52(s0)
801785b4: addu v0,v0,v1
801785b8: sh v0,12(a0)
```
So the second pair is (q-0x4A, q-0x2)?? and the third is (q-0x46, q).

Hmm, so the source's second pair should be (q-0x4A, q) but the target shows (q-0x4A, q-0x2). Hmm, so the target's `*(u16*)q` reads q-2?!

Hmm, that means the current src does NOT match the ROM?! But the project claims the tree reproduces the ROM byte-identically...

Hmm, unless the src's `q` is not what I think. Let me re-read the src:
```
*(s16 *)(*(s32 *)(q - 0x34) + 8) =
    *(u16 *)(q - 0x4E) + *(u16 *)(q - 0x4);
*(s16 *)(*(s32 *)(q - 0x34) + 10) =
    *(u16 *)(q - 0x4A) + *(u16 *)q;
*(s16 *)(*(s32 *)(q - 0x34) + 0xC) =
    *(u16 *)(q - 0x46) + *(u16 *)q;
```
Hmm, so pair 2 = (q-0x4A, q) and pair 3 = (q-0x46, q).

The target: pair 1 = (-0x4E, -0x4) ✓; pair 2 = (-0x4A, -0x2) ✗; pair 3 = (-0x46, 0) ✓.

Hmm! So the target's pair 2 second operand is q-2, not q. That's a 2-byte discrepancy — hmm, that means the ROM's code differs from the src's?! OR the target's s0 is q+2 and the other offsets are shifted: if s0 = q+2, then -78 → q-0x4C ✗ (the source says q-0x4E).

Hmm. So the offsets are inconsistent with a single base. Hmm, unless gcc used a different base for the `lhu v1,-2(s0)`: the address q (for `*(u16*)q`) could be computed as s0+2 → but the instruction shows -2.

Hmm, hmm: what if the target's s0 = q - 2 and the other offsets are relative to that? Then -78 = q-0x50 ✗.

I'm misreading something. Let me carefully re-read the target disassembly:

```
80178580:	9602ffb2 	lhu	v0,-78(s0)      0xffb2 = -78
80178584:	9603fffc 	lhu	v1,-4(s0)       0xfffc = -4
80178594:	9602ffb6 	lhu	v0,-74(s0)      0xffb6 = -74
80178598:	9603fffe 	lhu	v1,-2(s0)       0xfffe = -2
801785a8:	9602ffba 	lhu	v0,-70(s0)      0xffba = -70
801785ac:	96030000 	lhu	v1,0(s0)
```
Hmm: -78, -4, -74, -2, -70, 0.

The source's offsets: -0x4E (-78), -0x4 (-4), -0x4A (-74), 0, -0x46 (-70), 0.

So: -78 ✓, -4 ✓, -74 ✓, then -2 ✗ (should be 0), -70 ✓, 0 ✓.

Hmm! So the target's second pair's second operand is at -2 instead of 0. But the third pair's second operand is at 0 ✓.

Interesting: so the ROM reads q-2 where the src says q. Hmm! That's a 2-byte difference... unless the src's current body is not the ROM's source and the pin doesn't reproduce the ROM byte-for-byte?!

Hmm, but the score compares against the BUILD object (the current src compiled) — and the target listing I dumped is from build/ov_SC03_099/ov_SC03_099.elf (the current tree's build) ✓. So the target IS the current src's compiled output. So the ROM bytes = the current src's output (the project maintains byte-identical builds) ✓.

So the target's `lhu v1,-2(s0)` comes from the src's `*(u16 *)q`?! That would mean the src's q ≠ the base s0 by 2.

Hmm! `q = p + 0x54` and s0 = s1 + 84 = p + 0x54 ✓. Hmm, so s0 = q ✓.

Hmm, unless... hmm! The second pair: `*(u16 *)(q - 0x4A) + *(u16 *)q` — hmm, and the third: `*(u16 *)(q - 0x46) + *(u16 *)q`. The target's third pair: -70 (q-0x46 ✓) and 0 (q ✓). The second pair: -74 (q-0x4A ✓) and -2 (q-2 ✗).

Hmm, so the two `*(u16*)q` reads got different offsets (0 and -2) — that's IMPOSSIBLE for the same address... unless gcc used a different base register for one of them! E.g. `lhu v1,-2(s0)` might be `*(u16*)(s0-2)` where s0 = q ✓ — but the address should be q.

Hmm, unless the second pair's second operand is NOT `*(u16*)q` but something else. Hmm, what if the compiler CSE'd the two `*(u16*)q` reads (they're the same address!) — then the third pair would reuse the value from the second pair. The target has -2 at 80178598 and 0 at 801785ac → two different reads of q?!

Hmm, unless the target's s0 changes between them? No, s0 is fixed in the loop.

Hmm, wait: 80178598 `lhu v1,-2(s0)`: hmm, what if this is `*(u16 *)(q - 0x2)`? Hmm, hmm.

Hmm, hold on: maybe the src in the tree is NOT what I think — maybe the src's `q` is `p + 0x56`? No, `q = p + 0x54`.

Hmm, let me look at the ACTUAL current src file (src/shared/ov/func_8017849C.h) — the orig.c in the item dir is a copy, but maybe it's outdated? Let me check the real src.

Hmm, but the score's target = the build object ✓ and the build = the current src.

Hmm, hmm. But actually, wait: is the build up to date? The target comes from `oracle.baseline_path(obj)` → the build object (or the baseline snapshot). If the build is stale... hmm.

Let me look at the real src file and compare with orig.c. Maybe orig.c (the copy) differs from the current src!

That's important: if orig.c is stale, my candidates (built from orig.c) might be based on a wrong body!

Let me check.
