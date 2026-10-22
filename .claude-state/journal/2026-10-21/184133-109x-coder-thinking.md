---
ts: 2026-10-22T00:41:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_lIyJKUgaBcJ32tAzCWS9
---
Now let me write a comprehensive variant generator for the two "opaque copy" items (80181E64, 800D0D7C) — 20+ variants each.

For func_80181E64, the body is fixed except for the copy spelling and the types. Let me parametrize:

copy spellings (the assignment of t):
 S1: "t = v;"
 S2: "t = v + 0;"
 S3: "t = v - 0;"
 S4: "t = v | 0;"
 S5: "t = v & -1;"
 S6: "t = v ^ 0;"
 S7: "t = v * 1;"
 S8: "t = v / 1;"
 S9: "t = v << 0;"
 S10: "t = v >> 0;"
 S11: "t = ~(~v);"
 S12: "t = (s32)(u32)v;"
 S13: "t = (s16)(u16)v;"   [the value is < 0x1000 so the truncation is exact]
 S14: "t = (u16)v;"
 S15: "t = v; t = t;"  [identity]
 S16: "t = v;" with v declared as u16 and t as u16
 S17: "t = v;" with v declared as u16, t as s32
 S18: "t = v;" with v declared as s16, t as s32
 S19: the block in a do-while(0)
 S20: the copy inside a do-while(0), the value outside
 S21: the store using v (v live past the copy)
 S22: no v at all: "t = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;"
 S23: the value computed via a temp w: "w = ...; t = w;"
 S24: the mask split: "v = *(u16 *)(arg1 + 0x100) + 0x100; t = v & 0xFFF;"
 S25: "t = v;" with the store `*(s16 *)(arg1 + 0x100) = (s16)t;`

Hmm, also: the value's use in the loop is `func_8004787C(t)` and `t += 0x600` → t must be 32-bit for those. But for the SCORE, what matters is matching the target's instructions. t as u16 would change `t += 0x600` ✗ — but let me try anyway (maybe the score improves).

Let me write the generator with a template function.

For 800D0D7C, the copies are `r = now` and `h = arg0`:
 R1: "r = now; h = arg0;"
 R2: "r = now + 0; h = arg0 + 0;"
 R3: "r = now - 0; h = arg0 - 0;"
 R4: "r = now | 0; h = arg0 | 0;"
 R5: "r = now & -1; h = arg0 & -1;"
 R6: "r = now ^ 0; h = arg0 ^ 0;"
 R7: "r = now * 1; h = arg0 * 1;"
 R8: "r = now / 1; h = arg1 / 1;" hmm, careful with the semantics.
 R9: "r = now; h = arg0;" with the order swapped: "h = arg0; r = now;"
 R10: with `now` computed by `+` instead of `|`
 R11: without the `dead[2]` array
 R12: with `dead[2]` and an extra unused local
 R13: h as u32/s16
 R14: the copies in a do-while(0)
 R15: the store `*(s16*)` vs `*((s16*)...)`
 R16: `r = now` with `now` as s32 instead of u32
 R17: the conditions spelled differently (>= vs <)
 R18: `return (s16)r;` vs `return r;` hmm, the target has the sra (the sign extension) ✓ keep.
 R19: the else branch's `h = arg0 + 1` vs `h = arg0; h = h + 1;`
 R20: `r = ((r - arg1) & 0xFF) | (now & 0xFF00)` vs `r = ((r - arg1) & 0xFF) + (now & 0xFF00)` (the or vs add) — the target has `or a2,v0,v1` ✓ keep the or.

Let me write these generators now. Time to be efficient: I'll write one script per item that emits the variants, then score them.

Let me write the 80181E64 + 800D0D7C generators in one file.
