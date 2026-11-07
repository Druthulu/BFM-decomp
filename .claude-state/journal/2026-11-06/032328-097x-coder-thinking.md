---
ts: 2026-11-06T10:23:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NpDMRkGlqbHppSgdskZm
---
Item 3 total tries: orig + w1 + wk + wp + p0-p18 (19) + q1-q12 (12) = 35. ≥30 ✓.

Now item 1: currently orig, w1, w2, w3, wk, wp, k0-k4 (5), m1-m3 (3) = 13. Need 17+ more.

Let me generate ~20 variants for item 1 (lever-free, plus some keepalive-only).

Variants for item 1 (lever-free):
- s1: reuse d for both differences (already).
- s2: `s32 d = x - a0;` inline.
- s3: ternary rv.
- s4: if/else chain without goto.
- s5: `y = y + 0x5A0` → `y += 0x5A0`.
- s6: `x = x + 0x5A0` → `x += 0x5A0`.
- s7: `d * 2` → `d << 1`.
- s8: `d < 16` → `16 > d`.
- s9: decl order.
- s10: `rv = -1` → `rv = ~0`.
- s11: `rv = 31` → `rv = 0x1F`.
- s12: split x/y init.
- s13: `if (y < a0)` → `if (a0 > y)`.
- s14: combine the two 16 tests.
- s15: `goto done` vs return.
- s16: rv as s16.
- s17: rv as u16.
- s18: different d handling.
- s19: `D_801EEAEC[0]` into a pointer.
- s20: `if (a0 >= x || x >= y)`.

All lever-free. Let me generate and score. These will all be ≥15 presumably, but let me check if any reaches lower.

Let me write gen1c.py.
