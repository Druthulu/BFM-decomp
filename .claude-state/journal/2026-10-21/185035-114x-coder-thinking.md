---
ts: 2026-10-22T00:50:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_QDRNeawGhuGrUjyN7Bfk
---
**q15 = MATCH!!! score 0!**

q15: `u16 i; u16 j;` with `i = arg0; j = arg1;` — the u16 widths!

Wait, let me check: v1("q15", D_U16, "    i = arg0;\n    j = arg1;\n") → i and j are u16!

So making i and j `u16` (instead of s32) gives a byte-identical match!!!

Hmm, interesting: with u16, the copies `i = arg0; j = arg1;` — the truncation to 16 bits creates the "opaque copy" effect ✓ (the HImode copy escapes cse! — exactly the moves.md trick: "s16 flag2/3/4 copies (HImode copy a0 = u keeps the move)").

Excellent! Let me verify: q21 (`i = (u16)arg0; j = (u16)arg1;` with s32 i/j) scored 2, and q22 (`i = arg0 & 0xFFFF`) scored 2. And q15 (u16 decls) = 0 ✓✓✓.

So the MOVE is: declare i and j as u16 → the assignment `i = arg0` is an HImode copy that escapes cse → the opaque copy survives ✓.

This is a REAL C move (a type width — explicitly in the C0505 catalog: "s16/u8 widths") ✓✓.

Let me write win.c for func_8003DF8C = q15 and verify.

And this suggests the same trick for the other $0-add items:
- func_800D0D7C: `r` and `h` → u16? Hmm, r's value is masked with 0xFF/0xFFFF and h is used in a subtraction... Let me try the same: `u16 r; u16 h;`? Hmm, r's semantics: `r = ((r - arg1) & 0xFF) | (now & 0xFF00)` — with u16, the arithmetic would be 16-bit ✗ (the target has 32-bit ops). Hmm, but let me TRY it: maybe the target's ops are 16-bit-compatible.

Hmm, careful: the target's `andi v0,a2,0xff` etc. are 32-bit. If r were u16, gcc would use 16-bit ops ✗.

Hmm. But the KEY insight: the copy `r = now` must be an HImode copy → so `now` and `r` must both be u16! Hmm, but then the rest of r's arithmetic would be 16-bit.

Hmm, hmm. Let me think: in the target, `r` is a 32-bit value (the `or a2,v0,v1` with 0xFF00 etc.). Hmm, so r can't be u16.

Hmm, but maybe the COPY can be made 16-bit while r stays 32-bit:
```c
u16 tmp;
tmp = now;      /* HImode copy → opaque */
r = tmp;        /* 16→32 zero extension → sll/sra or andi ✗ */
```
✗ extra insns.

Hmm. Hmm! But wait: for 8003DF8C, i and j are u16 and the target's uses are `i | (j << 8)` — with u16, `j << 8` in HImode... hmm, the target's code: `sll v0,a1,0x8` (32-bit shift) hmm. Let me look at the target's asm for the i/j uses. Since q15 matches byte-for-byte, gcc generated the same 32-bit shifts ✓ (gcc promotes the shift).

OK so for 800D0D7C, let me try:
- `u16 r` — hmm, r's arithmetic would be 16-bit. Let me try anyway (the score will tell).
- `u16 h` — h is used as `(u32)h & 0xFF` and `h - v1` (a 32-bit subtraction? with u16 h, `h - v1` → hmm, v1 is `r & 0xFFFF` (32-bit) → the subtraction would be 32-bit ✓ (the usual arithmetic conversions promote u16 to int) ✓. And `(u32)h & 0xFF` ✓.

So `u16 h` might work for the `h = arg0` copy! And for `r`: the copy `r = now` — hmm, r must be 32-bit for the target's ops.

Hmm, what if `now` is u16 and `r` is u32? Then `r = now` is a 16→32 zero-extension ✗ (extra insns).

Hmm. What if BOTH now and r are u16? Then:
- `now = D_80078EB0 | (D_80078EB1 << 8)` — in HImode: the shift `D_80078EB1 << 8` → the result truncated to 16 bits → `sll v0,v1,8` then the OR → in HImode, gcc 2.7 would need to truncate the shift result → hmm, the target has `sll v0,v0,0x8` then `or a3,v1,v0` (no truncation!) — with HImode, gcc would emit `sll` + `sll/sra` (truncate) ✗.

Hmm. So `now` must be 32-bit.

Hmm! But hold on: in the 8003DF8C case, the copy that mattered was `i = arg0` where i is u16 and arg0 is s32 → the copy is a truncation (32→16) → gcc emits `andi`?? Hmm! But the match is byte-identical to the target, so the target's copy must also be a truncation... hmm, or gcc's "copy" of a u16 from a 32-bit reg is just a plain move (the upper bits are don't-care for u16!).

YES! That's the key: for an HImode (u16) destination, gcc 2.7 does NOT need to clear the upper bits (they're don't-care) → the copy is a plain `move` ✓ and the HImode copy ESCAPES cse (because cse's copy propagation works on word-mode copies) ✓✓✓.

So the trick: make the copy's DESTINATION a u16 (or s16?) so the copy is HImode and escapes cse.

Hmm, for s16 the upper bits are "don't care" too in gcc 2.7? For a signed 16-bit, the sign bit matters but the upper bits are don't-care ✓. So `s16` also gives a plain move.

Hmm, but q16 (u16 with `i = arg0 & 0xFFFF`)? hmm, q16 was D_S32 with the dead copy → 34. Hmm.

So for 800D0D7C: the copies are `r = now` and `h = arg0`.
- `h`: if h were u16/s16 → the copy `h = arg0` is an HImode copy ✓ escapes cse ✓ → `move t0,a0` ✓!! And h's uses: `(u32)h & 0xFF` ✓ and `h - v1` → hmm, with h as s16, `h - v1` (v1 = (r & 0xFFFF) >> 8, a 32-bit int) → the s16 h is promoted to int (sign-extended) → `subu v0,t0,v1` — hmm, the sign extension of h would need an extra insn (sll/sra) ✗. Hmm! Unless gcc knows h's range... it doesn't.

Hmm. Hmm, but wait: in the target, `h` is in $t0 and used as `subu v0,t0,v1` — a 32-bit subtraction of t0 ✓ (no sign extension). So h is 32-bit in the target ✗.

Hmm! Hmm, but for 8003DF8C, i and j are u16 in the target?! Let me check the target's uses of i/j: `i | (j << 8)` → the target's `sll v0,a1,0x8; or v0,s3,v0` — hmm, `or` with the u16 values: if i/j were u16, `i | (j << 8)` in HImode → the result truncated to 16 bits → the target's `or v0,s3,v0` (32-bit) — hmm, with HImode gcc would emit `or` and the upper bits are don't-care ✓ (the result is used as a 32-bit arg though! `func_80040DE8(i | (j << 8), 1, 1, 1)` — the arg is 32-bit → the upper bits would be garbage ✗ semantically, but it matches the target byte-for-byte, so the ORIGINAL source had u16 i/j too!).

Interesting — so the original source had `u16 i, j;` and the project wrote `s32 i, j` + the $0 pin. My finding: `u16 i, j` reproduces the target ✓.

Hmm, and the semantics: `i | (j << 8)` with u16 → in C, the u16 operands are promoted to int for the `|` → so the result is 32-bit ✓ (the usual arithmetic conversions promote u16 → int). So `i | (j << 8)` is a 32-bit expression ✓ and the shift `j << 8` is an int shift ✓ 32-bit ✓. And the assignment `i = arg0` truncates arg0 to 16 bits ✓.

So the original source had `u16 i; u16 j;` — and the truncation to 16 bits is exactly the "opaque copy" ✓ (the upper bits of the copy are don't-care, so gcc emits a plain move, and the HImode copy escapes cse ✓).

So for 800D0D7C: the copies `r = now` and `h = arg0`. If `h` were u16:
- `h = arg0` → HImode copy ✓ (a plain move, escaping cse) ✓
- `h = arg0 + 1` → in HImode: `addiu t0,a0,1` ✓ (the target has `addiu t0,a0,1` ✓✓!)
- the uses: `(u32)h & 0xFF` → `andi v0,t0,0xff` ✓ (the target ✓)
- `h - ((r & 0xFFFF) >> 8)` → h is u16 → promoted to int (zero-extended!) → hmm: the promotion of a u16 to int is a zero-extension → gcc would need `andi t0,t0,0xffff` (an extra insn) ✗. Hmm! But wait: in the target, `subu v0,t0,v1` uses t0 directly.

Hmm, but for 8003DF8C the u16 values were used in `|`/`<<` — hmm, the promotion issue would apply there too. Hmm! `i | (j << 8)` — i is u16 → promoted to int (zero-extended) → gcc would need to clear the upper bits of i ✗. But the match was byte-identical!

Hmm, so gcc 2.7 did NOT zero-extend. Because gcc 2.7 knows that the u16 value's upper bits are don't-care?? No — for a promotion to int, the upper bits matter.

Hmm, unless gcc's "nonzero_bits"/combine analysis figured out that the upper bits are irrelevant. Hmm! OR: gcc 2.7 keeps the u16 value in a reg and, when promoting, uses the reg directly if the value's upper bits are known to be zero... Hmm, i = arg0 (a truncation) → the upper 16 bits of the reg are NOT known to be zero.

Hmm, but the match is byte-identical, so the target does `or v0,s3,v0` with s3 = the truncated i. So the original compiler also didn't zero-extend. Hmm, so the original had the same "don't care" behavior. OK, gcc 2.7 apparently optimizes the promotion away (maybe because the value's upper bits are unused in the OR with a shifted value? Hmm, `i | (j<<8)`: the upper bits of i DO matter for the result... hmm, unless the result is used as a 16-bit value).

Hmm, whatever — the match is byte-identical ✓. That's what matters.

So let me now apply the same trick to the other $0-add items:
- func_800D0D7C: try `u16 h`, `s16 h`, `u16 r`, `u16 now`, and combinations.
- func_80181E64: try `u16 t` (the copy `t = v`)! Hmm, t is used in `func_8004787C(t)` (a 32-bit arg) and `t += 0x600` and `*(s16 *)(arg1+0x100) = t`. With t as u16: `t += 0x600` in HImode → `addiu s8,s8,0x600` ✓ (the target ✓). And `func_8004787C(t)` → the promotion → hmm.

Let me just try a batch of u16/s16 variants for both items!

This is a big lever. Let me generate:
For 800D0D7C: the types of r/h/now in {s32, u32, u16, s16} → 4×4 = 16 combos (plus the dead array on/off → 32).
For 80181E64: the types of t/v in {s32, u32, u16, s16} → 16 combos.

Let me do it now!

Also for func_801415C0 (the allocation order): maybe a width change flips the local/global split! E.g. if c or d were u16/s16, they'd be HImode → hmm, they'd still cross calls. Hmm. But let me try widths too (the q08-q10 in the batch I generated will tell).

Let me first score the 801415C0 batch (q01-q30), then do the u16 sweeps for the two $0 items.

Let me score 801415C0's batch now.
