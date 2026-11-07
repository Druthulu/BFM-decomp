---
ts: 2026-11-06T13:03:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yx2DdlRNwG1npJhkbrJ1
---
Still 2. Time check: it's probably ~06:20 now. Item 3 started at 05:52 → 28 min. Tries: 15 + 20 + p1,p2 + r1-r4 + s1-s3 + t1-t4 = 15+20+2+4+3+4 = 48 tries. Time ≥ 20 min. So a WALL is legitimate for item 3.

But p2 is a PARTIAL:launder candidate at score 2 — not 0, so it's not a PARTIAL (PARTIAL requires score 0). Hmm: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So PARTIAL requires score 0 too. p2 is 2 → not PARTIAL.

So item 3 = WALL with best 2 (p2: launder kept volatile, keepalives gone, score 2). But wait — for a WALL, "best = lowest score of a lever-free body". p2 keeps the launder (a lever) → not lever-free! Hmm. The WALL's best should be the lowest score of a lever-free body: c1 = 18 (all asm gone).

So item 3: WALL, best 18 (lever-free), tries ~48.

Hmm, but hold on: is p2 legitimate as a PARTIAL? No (score 2, not 0).

Hmm, but wait — maybe I should keep trying on p2 to reach 0. The remaining diff is 1 insn order (li v0,36 vs addiu a0,a0,4). Let me think once more...

Actually — maybe the fix is the `dp` variable's type or the `dp = dp + 1` being `dp = dp + 1` where dp is `s32 *` → +4. In the target: `addiu a0,a0,4`.

sched1's decision: at the point after `lw v1,0(a0)`, the ready list has `li v0,36` and `addiu a0,a0,4` (and `subu` waits for the li). The scheduler picks by priority: the li's priority = chain length to the end... 

What if we make the addiu depend on the li? No.

What if the C computes `df` BEFORE `c36 = 0x24;`? Can't.

What if `dp` is incremented via the ba expression only (drop `dp = dp + 1`)? Then dp would be dead after... but dp is used in `ba = (u16 *)(tmp + (u8 *)dp);` — if I write `ba = (u16 *)(tmp + (u8 *)dp + 4);` and remove `dp = dp + 1;`, the addiu disappears (folding into the addu) → different code.

Hmm. What if `dp = dp + 1;` is moved to the very end (after the copy loop)? dp is dead after ba, so it might be deleted... it's a local.

OK, let me accept item 3 as a WALL (best 18 lever-free) — but actually, hmm, p2 at 2 with the launder kept is a *very* interesting data point for the notes/moves: "keeping the launder (volatile) + dropping the keepalives gets 159/159 ins, score 2 (one sched1 order)". That's useful for the expert.

Wait, but before finalizing: is `__asm__ __volatile__` on the launder an acceptable "kept launder"? The original was non-volatile; making it volatile changes it. In win.c for a PARTIAL I'd note it. Since it's not 0, it doesn't matter for the row.

Hmm, but hold on — maybe I should try to close the last 2 points on p2 with a different angle: the `li v0,36` vs `addiu a0,a0,4` order.

What if `c36` is declared as a different type (u32) so the li is emitted differently? Or if `df` is computed as `c36 - dcount` where c36 is a *constant expression*: `df = 0x24 - dcount;` (s2) — still 2.

What if the store `dp = D_80127548;` uses a different form: `dp = &D_80127548[0];`? Hmm.

What if `dcount` is loaded via a different type: `dcount = dp[0];` (same lw).

What if we add a `do{}while(0)` around `dp = dp + 1;` only? Let me try one more (u1) plus `dp++` (u2) and `dp = dp + 1` with dp as u8*? no.

Actually, maybe the sched1 order depends on the *hazard* of the addiu vs li. The addiu writes a0 (dp) which is used by... nothing until `addu a1,v1,a0` (ba). The li writes v0.

What if the `ba` computation's addu uses dp BEFORE the increment (i.e., `ba = (u16 *)(tmp + (u8 *)(dp + 1))` and drop the dp update)? Then the addiu folds into the addu — the target has a separate addiu a0,a0,4, so no.

Let me try u1/u2 quickly, then finalize item 3 as WALL and verify item 4's 141 includers.

Actually, item 4 needs the 141-includer verification which takes ~15 min in the background. Let me kick that off NOW in the background, then continue with item 3's last tries.

First, set item 4's win.c = q1 and start the verification loop.

The verification: for k in 0..140: tryinc.py k ... | grep score. Let me write a small script that prints a compact summary (max score, count of nonzero). 141 runs × ~5 s ≈ 12 min. Run in the background.

Note: tryinc.py rotates the includer list per run; I pass k = 0..140.

Let me write the script.
