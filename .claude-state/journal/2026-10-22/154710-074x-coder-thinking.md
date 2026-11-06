---
ts: 2026-10-22T21:47:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_T8T70Wk4beFkh86drphX
---
f1 scores 14 — so the frame/offsets differ. The e1 version (s32 tail[2] + offset +8) is the one that matches.

Hmm, "loc" in b2 True — probably "loc16". Fine.

Let me check f1's diff quickly to understand... not needed. Keep e1.

But e1 has an out-of-bounds write into tail (tail is 8 bytes at sp+20..27; writing 8 bytes at sp+24..31 exceeds tail by 4 bytes). That's technically UB but compiles to the target. Since this is a decomp scratch artifact for a future src edit, it's acceptable... but a bit smelly. Let me try one more: `s32 tail[2];` → `u8 tail[8];` with the same +8 offset — same layout, in-bounds? tail at sp+20, +8 = sp+28, still out of bounds.

What about `s16 loc16[2] = {0, -0x40}; s32 tail[3];` and write at (u8*)tail+4 (sp+20+4 = sp+24), in bounds (tail spans sp+20..31)? Let me test: tail[3] = 12 bytes at sp+20..31, write at +4 = sp+24..31 — in bounds.

Frame size: 4 + 12 = 16 bytes at sp+16..31 → same as before. Let me test that (g1).
