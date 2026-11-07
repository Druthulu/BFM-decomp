---
ts: 2026-11-06T15:16:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lf755newU0tqFJ3eKtPu
---
SCORE 0! c_m1 = MATCH!

The winning move: `vol = vol | 0x3000;` right before the call (after the shift), with the arg kept in the target spelling `(vol | (0x3000 | sx)) & 0xFFFF` — the redundant 0x3000 lets fold produce the right birth order.

Let me verify c_m1 is lever-free: it has no launder asm. It keeps the $5 pin on av and the $4 pin on r4 (not row kinds; kinds=launder). And no new levers.

Let me double-check the win.c content: does it still contain any `__asm__` besides the pins and the extern alias? The pins: `register s32 av __asm__("$5")` and `register void *r4 __asm__("$4")` — these are pins, not the launder. Allowed to stay ("levers of other kinds the def already had may stay").

But careful: the MATCH definition per the brief is "the kinds in <dir>/kinds gone". kinds=launder. The launder is gone. 

Hmm, but the brief's CHANGE bullet says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." This reads as: lever-free means no launder (the row kind). The parenthetical enumerates what the kinds are. And CONSTRAINTS clarifies pins of other kinds may stay. So keeping the $5 pin is fine.

Also the `extern u16 aB9A02[1] __asm__("D_800B9A02")` style alias — not present here.

Now: does win.c need to be the *body* only? Yes, like the worked example.

Let me finalize: copy c_m1.c to win.c, verify score 0 once more from win.c, record the result.

Also check: no `do{}while(0)` used — right.

Let me also record the time: started 08:00, now ~08:25.

Then: append results.tsv row and moves.md line, write notes.md.

Then item 2.

Let me do the verification and file setup.

Results row format: `dir file func kinds result best tries wall evidence`.

dir = func_801806D8__ov_SC03_099_jr_8017BEBC (the item dir name). file = the src file. func. kinds=launder. result=MATCH. best=0. tries=count. wall=-. evidence=gcc pass + mechanism ≤140 chars.

Let me count tries for item 1: a1, c_dw, c_s16, c_dws16, c_split, c_u16 (6), c_u16dw, c_u167f, c_u16s16, c_hvol (10), c_u16late, c_u16late2 (12), c_d1 (13), c_e1..e4 (17), c_f1, c_f3, c_f4 (20), c_g1, c_g2 (22), c_h1(compile error), c_h2 (24), c_i1 (25), c_i2, c_i3(failed compile attempt - didn't score), c_i4 (28), c_j1, c_j2 (30), c_k1 (x2) (32), c_l1,l2,l3 (35), c_m1, c_m2 (37).

Let me say tries = 36 (scored candidates). I'll count exact scored ones: a1(1), dw(2), s16(3), dws16(4), split(5), u16(6), u16dw(7), u167f(8), u16s16(9), hvol(10), u16late(11), u16late2(12), d1(13), e1(14), e2(15), e3(16), e4(17), f1(18), f3(19), f4(20), g1(21), g2(22), h1(compile-error, not scored), h2(23), i1(24), i2(25), i4(26), j1(27), j2(28), k1(29 + 30 + 31? k1 scored 3 times: unused-id version 2, then id version 2, then... I ran sc.sh on k1 twice), l1(32), l2(33), l3(34), m1(35), m2(36). Say 36.

Evidence: "sched1: vol 2nd set `vol = vol | 0x3000;` + arg `(vol | (0x3000|sx))` — fold's assoc birth order puts li a0,2715 before ori; launder asm dropped (O04)".

Keep ≤140 chars.

Wall = `-` for MATCH.

Let me finalize win.c and verify.
