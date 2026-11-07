---
ts: 2026-11-06T22:24:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FGWyrso4DOOZHuJDHNyH
---
No improvement (best 135). Note: the y*.c glob also matched y_s16.c/y_u16.c etc. from earlier? Those are y_int.c, y_long.c, y_s16.c, y_u16.c, y_u32.c, y_u8.c (from the dst-pinned tmp test). The awk shows y01..y12; the y_* files might also be scored. Anyway.

The twins are walls. Let me stop and finalize.

Actually, I realize I should double-check that the y_s16.c etc. (dst pinned, tmp s16) scored 25 — those are not lever-free (dst pin kept), so they don't affect the wall's best.

Final state:
- Item 1 (func_80183534): MATCH, score 0, win.c = s1.c, 87 tries.
- Item 2 (func_801919A0): WALL, best 24 (invalid; valid best 135), 57+ tries (now more: u1-u3, v1-v3, z1, x1-x3, y01-y12, y_* = ~25 more; total ~82). Let me update the tries count to reflect the actual attempts? The row says 57. I've done more since. Let me update to the actual count: 57 + 3(u) + 3(v) + 1(z1) + 3(x) + 12(y) + 6(y_*) = 85. Hmm, the y_* (dst-pinned) were 6. Let me count precisely:
  - initial: 35 t + 21 u + w0 = 57
  - u1,u2,u3 (dst-block do-while) = 3 → 60
  - v1,v2,v3 (sh/sums) = 3 → 63
  - z1 (call seq) = 1 → 64
  - x1,x2,x3 (tmp blocks) = 3 → 67
  - y01-y12 (permutations) = 12 → 79
  - y_* (6, dst-pinned tmp types) = 6 → 85
  So ~85 tries.
- Item 3 (func_80191C50): WALL, 58 tries.
- Item 4 (func_8019059C): WALL, 58 + z1 = 59 tries.

Let me update the tries for item 2 to 85 (and item 4 to 59). Actually, the "tries" should count scored tries. Fine.

Now write the log file: phase-ends/current/logs/T11.cRM3.md with the timeline per item, start/end, minutes, tries, moves that cracked, walls with evidence.

The log path: phase-ends/current/logs/T11.cRM3.md. Let me write it.

Content (terse markdown):
```
# T11.cRM3 — singleton crack shard RM3 (scratch-only)

4 items, all kinds=pin (PARTIAL:pin banked, best 0 with pins kept). Work under .run/P40/T11/RM3/.

## Item func_80183534 (ov_SC06_029) — MATCH, score 0, 197 ins
start 14:37, end 14:51 (14 min) + resumed 15:10-15:22 (12 min) = ~26 min; 87 scored tries.
orig.c regenerated FRESH from src:6719-6817 (identical to prev_win.c).
Lever-free baseline: both pins -> plain decls + w2 s16 = 13 (only a v1<->a0 swap on the tail).
Moves tried (a1-a8, b1-b5, c1-c8, f1-f11): packet-word temp/alias, hi/lo split, tag temp, oidx width/casts, mask spellings, decl order, store reorder, early load — all 13-26.
Crack: do{}while(0) EBB splits (C0535) — around the otp block AND around the first 3 sxy stores. That splits the tail for local-alloc so the oidx qty gets $3 (target) and the packet-chain qty $4; the mask-const pair then schedules at the target's slot. win.c = s1.c, score 0, 197 ins, no asm/register.
Mechanism: lever-free the oidx qty (refs7/live34 pri4117) loses $3 to the packet-chain qty (refs6/live10 pri12000); the EBB split allocates them separately and the target pairing falls out.

## Item func_801919A0 (ov_SC06_032) — WALL lreg-qty-priority, best 24 (invalid), valid 135
start 14:51, end ~15:00 + 15:18-15:2x; ~85 scored tries.
orig.c FRESH from src:2960-3269 (identical to prev_win.c; orig 0).
Lever-free w0 = 135, 709 ins: dst -> a2 (target v1), 52-hunk bank shift, one missing li (tmp=6 merged).
Tried: 35 type/order variants, 21 dst x tmp type combos, pointer-typed dst, dst-block/call-sequence/tmp-block do-while splits, sh/sums permutations. Best 24 = u06 (dst s16, tmp u16) but invalid (lw->lh, tmp>>16=0); best valid 135.
Mechanism: dst is a long-lived block pointer; local-alloc gives $3 to the short temps, dst -> a2. 16-bit dst wins $3 only by narrowing the load.

## Item func_80191C50 (ov_SC06_018) — WALL lreg-qty-priority, best 24 (invalid), valid 135
Twin of func_801919A0 (same body, last call differs). orig.c FRESH from src:2843-3152 (identical to prev_win.c; orig 0). 58 tries, same result.

## Item func_8019059C (ov_SC06_018) — WALL lreg-qty-priority, best 31 (invalid), valid 137
start 15:05, end 15:09 + 15:23-15:25; ~59 tries.
orig.c FRESH from src:2787-3097 (identical to prev_win.c; orig 0).
Lever-free w0 = 137, 672 ins: tmp -> a3 (target v0) + missing li; dst-pinned tmp-free = 38.
Tried: 49 dst x tmp type combos, pointer dst, w0, x1, 6 tmp-type x1, tmp-block do-while. Best 31 = v33 (dst s16, tmp s16) invalid; valid 137.

## Friction
None. (No denials.)

## Files
RM3/results.tsv: 4 rows. RM3/*/win.c set. moves.md: 4 lines + 1 correction line for func_80183534.
```

Wait, I need to append the corrected moves.md line for func_80183534 (MATCH). Let me do that.

Also update the tries counts in results.tsv for items 2 and 4.

Let me do these final writes:
1. moves.md correction line for func_80183534.
2. results.tsv: update tries for item 2 (85) and item 4 (59). Keep best 24/31.
3. Write the log.
4. Clean up the item-1 dumps dir (27MB) and any large scratch.
5. Report.

Let me also check the shard size.

For the results.tsv tries update, use a python script (one action).

Let me do the moves line first.
