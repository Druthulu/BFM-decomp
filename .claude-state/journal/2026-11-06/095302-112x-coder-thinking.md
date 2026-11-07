---
ts: 2026-11-06T16:53:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V7qp6pts5SwPeiwSNJ12
---
In no_fp: s0 ($16) = fp = buf+38 (0x26). Wait, `addu $16,$19,38` — fp = buf + 38 = 0x26 = prim+0x1A. But the source says fp = prim + 0x22 = buf+0x2E = 46. And `addu $21,$19,46` (s5) = buf+46 = the real fp!

So there are TWO pointers: s5 = buf+46 (fp) and s0 = buf+38 (fp-8?). The stores use $16 (buf+38) with offsets -22,-14,-6,2,-23,... These correspond to fp-0x1E = buf+0x10? Hmm: if $16 = buf+0x26, then -22 = 0x26-0x16 = 0x10. That doesn't match fp-0x1E = 0x2E-0x1E = 0x10. Yes! -22 (0xEA = -22) → 0x26-0x16 = 0x10. And fp-0x1E = 0x10. So $16 = fp - 8 = buf+0x26, used with offsets 8 less than fp's.

So the compiler split fp into fp-8 (s0) and fp (s5)? And s5 (buf+46) is used where? Let me see the loop end: probably `fp += 0x24` uses $21.

So without the pin, the compiler chose to keep a second pointer fp-8 in s0 and the main fp in s5. That's the extra register (s0) — but wait, s0 was free, so it's not the frame issue; the extra s7 came from 81 in s7.

The extra instruction `addu $16,$19,38` is the second pointer's materialization.

This is a mess. The pin was likely added exactly because lever-free codegen splits the address. Cracking it would require making the two address bases merge — e.g., by rewriting the loop stores in terms of a single base.

Observation: the loop body accesses fp-0x1E..fp+0 (offsets -0x1E..0) and also `cbase + 0x18 + ...`. The compiler created fp-8 = buf+0x26 as the base for the fp accesses (offsets -0x16..+8). Why? Maybe because the loop uses fp with offsets up to +0 (fp - 0x0 = fp) and the addressing range? The base fp-8 lets all offsets be within ±0x18.

Hmm, but the target keeps fp=buf+0x2E as the base with offsets -0x1E..+0.

The compiler's choice of base offset depends on the address expressions and combine. The source writes `*(s32 *)(fp - 0x1E)` etc. With fp = prim + 0x22 and prim = buf + 0xC, the folded address is buf + 0x10 for the first store. GCC's combine may choose to use fp-8 as a common base if it can share the address computation.

The pinned version prevents this by fixing fp in s0? No — the pin makes fp a register variable, which forces `fp = prim+0x22` to be a real value in $16, so the addresses are fp+offset directly.

Without a pin, gcc splits. To prevent splitting lever-free: make fp's value used in a way that forces materialization, e.g., pass fp to a function? no.

Or write the stores with explicit offsets from a single base that gcc can't fold: e.g., use `prim` as the base with offsets 0x22-0x1E=0x4, etc.? The source already uses fp.

Hmm, the split to fp-8 = buf+0x26 comes from combine folding `fp + K` addresses into a base. If we instead write the addresses as `*(s32 *)((s8 *)prim + 0x4)` (fp-0x1E = prim+0x4), gcc would use prim as the base (s4?) with offsets. That changes the register assignment but might match the target if the target also... no, the target uses s0 = fp = buf+0x2E.

OK. Given the time (10:04, 20 min in), and the complexity (3 interdependent pins), I'll likely record a WALL. But I need ≥30 scored tries and ≥20 min. I have ~10 tries. Let me do a batch of quick variants (20 more) that vary the loop base and the three pins individually, then record the WALL with best = lowest score of a lever-free body.

Important: WALL best = lowest score of a lever-free body (all kinds gone). Our lever-free best so far is nopin = 52. A PARTIAL keeps some pins: no_ot (8) and no_t0c (5) are PARTIAL candidates if we can't get them to 0... but PARTIAL requires win.c scores 0 while keeping only the listed kinds. no_t0c scores 5 → not 0, so not PARTIAL.

So for this item: WALL with best 52 (the full lever-free body), unless I crack.

Wait — maybe I can at least get the t0c pin removed (score 5 → fix the addiu/move) and the ot pin (8). But a PARTIAL requires score 0 with remaining pins. If I can crack 2 of 3 pins to score 0, that's PARTIAL:$16. Let's see if that's easier: no_t0c (fp and ot pinned) score 5; the only issue is the missing `addiu v0; move s3` pair. If I can produce that copy, the score is 0 → PARTIAL:$16 (fp pin kept). That would be a good result.

Similarly no_ot (score 8) — with fp and t0c pinned. Let me look at the no_ot diff.
