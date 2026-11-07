---
ts: 2026-11-06T10:29:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OTWZ4clIBYY1uvqZcpwC
---
Now the picture:
- b13_off_pins_on (13 fences removed, pin kept, loop barriers kept) = 15 — matches the comment "0 -> 15". So the 13 fences are needed for 0.
- b13_off_pins_off = 88 (lever-free except loop barriers).
- loop_off_pins_on = 30.
- loop_off_pins_off = 99.

So the 13 fences are load-bearing (15 without them, with pin). No PARTIAL.

The lever-free best is nopin = 102 (but nopin also removed the loop barriers). Actually the fully lever-free body (all 15 barriers + pin off) = 102.

Hmm, but "lever-free" means none of the row kinds remain: barrier,pin. The loop barriers are also `__asm__` → barriers. So lever-free = 102.

WALL with best 102.

Now, can I improve the lever-free body with real-C moves? The 13 fences do live-length arithmetic. Let me try the pkt-earlier move and other live-length moves.

Actually, since b13_off_pins_off = 88 (keeping the 2 loop barriers), the loop barriers' removal costs 14 more. So both matter.

Given the difficulty, let me do a batch of ~30 real-C variants and record WALL. I have limited time (item 4 started ~03:27, now ~03:38 → 11 min). Let me generate variants and score.

Real-C moves to try:
1. Move `pkt = D_800A5E60;` earlier (before tp/tpage).
2. Move it to the top.
3. Move `tp/tpage` after the fences (i.e., into the if branches? no).
4. Move `mat = ...` later.
5. Move `otab = ...` later.
6. Reorder declarations.
7. Change types (s16/u16) of b9, idx, x, y.
8. Move `flags = ...` later.
9. Compute tpage differently.
10. Move `pkt += 0x10` etc.

Let me look at the full function structure once more to place moves. I have the top. The loops are long.

Let me generate ~20 variants:
m1: pkt = D_800A5E60; moved before `tp = ...`.
m2: pkt moved to after `otab = ...` (before the if).
m3: pkt moved to the very top (after declarations).
m4: `b9 = D_800B9A02;` moved after flags.
m5: `otab = ...` moved after the if (but it's used in the if branches? otab is used in both loops; the if sets x/y/idx. otab is used after. So moving otab after the if is possible? The if branches use otab? No, the first if only sets v/x/y/idx. So otab could move after. But it uses b9.)
m6: `flags = ...` moved after mat/prims.
m7: `mat` moved later (mat is used only in the first if branch).
m8: combine m1+m6.
m9: idx as u16.
m10: b9 as u16.
m11: x,y as s16? risky.
m12: move `prims = ...` later.

Let me generate and score. Note the function is big; each compile takes ~1-2s.

Let me write the generator.
