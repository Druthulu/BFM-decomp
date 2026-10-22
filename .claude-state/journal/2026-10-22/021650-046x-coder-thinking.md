---
ts: 2026-10-22T08:16:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_wchVAkglpzh1RBqXhsuO
---
Target for 8018302C:
```
lw a0,32(a0)
nop
lh v0,24(a0)        ; v = *(s16*)(p+0xC)
nop
move v1,v0          ; c = v + z   <-- the copy
slti v0,v0,2049     ; if (v >= 0x801)
bnez v0,34d0
addiu sp,sp,-16     ; delay slot of the bnez (frame setup!)
34d0: lh v0,26(a0)   ; v = *(s16*)(p+0xD)
      nop
      move v1,v0      ; c = v + z
      slti v0,v0,2049
      bnez v0,34ec
      addiu v0,v1,-512  ; v = c - 0x200   (delay slot)
      sh v0,26(a0)
```

So the `move v1,v0` is BEFORE the slti compare, and the copy's use is in the if-body.

Now: `c = v + z` with z=$0 → `or v1,v0,$zero`? The bytes 0x00401821 = `or v1,v0,$zero` ✓ (same as before).

Now the lever-free version: `c = v` → plain copy → cse propagates (the note says score 10).

With the s16 trick: `tmp = (s16)v; c = tmp;` — hmm, but here the copy `c = v` is in the entry block and its use `v = c - 0x200` is inside the if-block → DIFFERENT BLOCKS. So why did the plain copy die?

Hmm, the note says: "`c = v;` — score 10, 36 ins: combine folds the copy and cse propagates it, the two `move`s disappear and the load moves to $3."

Hmm, so it died. Maybe because cse's reg_equiv_content is global (not per-block) and the copy is in the entry block while the use is in the if-block: cse propagates the equivalence globally.

Hmm, but in the 80182ED4 case (c6), the copy `u = tmp` was ALSO in the entry block with the use in the else block, and it survived — because the s16 temp broke the equivalence.

Right. So the s16 trick is what matters. Let me apply it here:

```c
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p+0xC) = v; }
```

Hmm, but wait: `c = v + z` in the target. Lever-free we need `c = v`. With the s16 route: `tmp = (s16)v; c = tmp;`.

Hmm, but there's a subtlety: the target's `move v1,v0` comes right after the `lh`, and the compare `slti v0,v0,2049` uses v0 (the loaded value). So in our version, `c` (v1) is the copy and `v` (v0) is the loaded value ✓.

But the ORDER: the target has `move v1,v0` BEFORE `slti`. Our version: `tmp = (s16)v; c = tmp;` → the copy `or v1,v0` would be before the compare ✓ (assuming scheduling keeps it).

Hmm, but the tmp assignment: `tmp = (s16)v` → is that a separate insn? tmp is a short holding v's value; v is already the sign-extended s16 → `tmp = (s16)v` is a no-op → gcc should eliminate it (no insn) and `c = tmp` becomes `c = v`... but then it's a plain copy → cse propagates?!

Hmm! In the 80182ED4 case it worked. Why? Because `tmp` is a QImode pseudo and `c = tmp` is `(set c (sign_extend:SI (reg tmp)))` — not a plain copy → cse doesn't propagate ✓. And the sign extension was folded away by combine (since tmp's value = v's value, known sign-extended) → the copy became `or v1,v0` ✓.

So in 80182ED4, the key was: `u = tmp` where tmp is s16 → the RTL is a sign_extend → escapes cse → and combine folds the sign extension into a plain copy (because the value is already sign-extended).

So here: `tmp = (s16)v; c = tmp;` → same structure ✓.

Let me write c1.c for 8018302C:

```c
void func_8018302C(void *a0) {
    extern u8 D_801D4306;
    extern u8 D_801D4304;
    extern u8 D_801D4305;
    s32 v;
    s32 c;
    s16 tmp;
    u8 *dp;
    s16 *p;
    s32 frame_pad[3];

    (void)&frame_pad;
    p = *(s16 **)((s32)a0 + 0x20);
    v = *(s16 *)(p + 0xC);
    tmp = (s16)v;
    c = tmp;
    if (v >= 0x801) {
        v = c - 0x200;
        *(s16 *)(p + 0xC) = v;
    }
    v = *(s16 *)(p + 0xD);
    tmp = (s16)v;
    c = tmp;
    if (v >= 0x801) {
        v = c - 0x200;
        *(s16 *)(p + 0xD) = v;
    }
    dp = &D_801D4306;
    if (*dp >= 0xC1) {
        *dp -= 4;
        D_801D4304 -= 6;
        D_801D4305 -= 6;
    }
}
```

Wait — there's a problem: `tmp` is reused for both arms, and `c` too. The second `tmp = (s16)v; c = tmp;` — the second copy overwrites c. In the target, both copies use v1 (the same reg) ✓.

Hmm, but the reuse might cause cse to merge the two copies (they're different values though: v differs). Hmm, `tmp` is the same variable → the second assignment to tmp is a redefinition. cse might link them... Since the values differ (different loads), no.

Hmm, but careful: with `tmp` reused, the second `c = tmp` is a copy from the same pseudo tmp (redefined) → fine.

Hmm, but actually there's a risk: cse might treat `c = tmp` (the first) and `c = tmp` (the second) — c is redefined in between, so no.

Let me also consider: should I use separate temps (tmp1, tmp2) to be safe? The G02/G06 notes suggest splitting reused vars can help. Let me first try the simple version.

Also: `v = *(s16 *)(p + 0xC)` — v is s32 and the load is `lh` ✓.

Let me also double check the delay slot: the target has `addiu sp,sp,-16` in the bnez delay slot (the frame setup). Our version should produce the same.

Let me write and score.

Also note: the current win.c has `s32 z;` unassigned (the lever-free version). I'll write a fresh candidate.

Let me do it.
