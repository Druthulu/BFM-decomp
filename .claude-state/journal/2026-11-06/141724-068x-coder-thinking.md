---
ts: 2026-11-06T21:17:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IFrSOO1byztFRNv7bnEr
---
Still 4. Let me check if v.c's combine merged the copy. Probably.

Time: 14:30, 32 min. I've hit the 30-min wall. But let me do one final decisive experiment: keep the launder but remove the barrier differently — maybe a real-C move replaces the barrier in l_only. If I can replace the barrier with real C while keeping the launder... no, MATCH requires the launder gone too.

Let me reconsider: with win.c (neither lever) the ONLY diff is a0/a1. The launder fixes it. The barrier is only needed because the launder breaks the order. So the question is purely: real C that raises e's refs by 2 without disturbing order.

Let me look at the actual allocno order for the LAUNDER version to confirm e jumps up. I can dump the launder candidate (l_only? no, l_only = launder kept, barrier dropped). Let me dump the orig (both levers) or l_only and check the "regs to allocate" order. If e moves up, confirms. But I know it fixes REG.

The key insight: e needs more refs. Real C that adds a use+def with no code...

IDEA: What if we make `e` the result of a *function call*? No.

IDEA: Use `e` in a loop that's executed once but the compiler keeps as a loop? No, unrolled.

IDEA: The target's launder asm is `__asm__("" : "=r"(e) : "0"(e))`. The real-C equivalent that changes refs and survives: a **volatile store/load pair**? No, adds code.

IDEA: What if `e` is assigned from a `memcpy`-like? No.

Let me reconsider the problem from the "moves.md" perspective: many launders were cracked with "real 2nd set `pv = pv & 0xFF000000`". These are real arithmetic. For a constant pointer, there's no such arithmetic... UNLESS the code actually does pointer arithmetic. 

What if we express e as `e = (s16 *)((u32)D_801E8F78 & 0xFFFFFFFF);` — the AND might survive as a real 2nd set (reg_n_sets=2)? We tried k (u32 cast) = 4. Let me try the AND explicitly and check if it survives. If combine folds `& 0xFFFFFFFF`, no. But maybe with a variable mask it survives: `e = (s16*)((u32)D_801E8F78 & mask);` where mask=0xFFFFFFFF — constant, folded.

Hmm.

IDEA: Change the *number of refs* by using `e` in a comparison that's needed. E.g., `if (t < lim && e != 0)` — but e is never 0 (symbol), so flow might fold. And it adds a test.

OK. Let me accept the WALL for item 1. I have ≥20 min and ~25 scored tries. The requirement for a WALL is ≥20 min and ≥30 scored tries. I'm at ~25 tries. Let me do a few more quick ones to reach 30, then record WALL with best=4.

Actually, let me reconsider: maybe I should count "scored tries" as candidate bodies scored. Let me count: orig(0), win(4), w1(4), w2(CE), w3(CE), v1(4), v2(4), v3(4), v4(4), a(23), b(25), c(4), d(4), e(4), f(4), g(4), h(4), i(4), j(4), k(4), l(4), m(4), n(4), o(4), p(21), q(13), s(12), u(4), v(4), l_only(4), b_only(4). That's ~31 scored (excluding CEs). Good, ≥30.

But before declaring WALL, let me try ONE more clever idea: the `do{}while(0)` trick with the launder-equivalent: use an *empty if* or a `for` to create a 2nd set? 

Actually — here's a promising one I haven't tried: assign e inside a conditional that the compiler cannot fold because it depends on a runtime value, but where both paths yield the same value... that's identity.

What about: `e = (s16 *)D_801E8F78; if (t < lim) { ... }` → move the e assignment such that it's used in the lim load? no.

Let me try: use `e` in the lim load via the SYMBOL but with `e` also used to guard: no.

Alternatively, maybe I can change off's priority to be LOWER by making it a `long` (same) or by extending its live range legitimately. off is used at the lim address and the condition. What if I ALSO use off in the lim address of a DIFFERENT array? no.

Hmm, what if I make `off`'s live range longer by defining it as `off = idx * 4;` and then using `off` in the `if (idx >= 0)` branch as the index for `D_801E8F98`: `p = D_801E8F98[off >> 2];` — off>>2 = idx. This uses off (extends live range) but changes code (extra shift) unless cse simplifies off>>2 back to idx. Actually `off >> 2` where off=idx*4 → idx, combine might simplify to idx (no code), but the USE of off would be at insn in the other block → extends off's live range → lowers priority! Let me test: replace `p = D_801E8F98[idx];` with `p = D_801E8F98[off >> 2];`. If combine folds off>>2 to idx, no extra code, but off's live range extends into the next block. That could lower off's priority below e's!

Similarly `result = D_801EF140` etc. Let me test this. Also apply to the `if (idx >= 0)` condition? idx is used.

Let me test:
w: `p = D_801E8F98[off >> 2];`
x: `if ((off >> 2) >= 0)` — changes branch? `idx >= 0` → `off>>2 >= 0`. Since off = idx*4, off>>2 = idx (arithmetic). Might fold. But it's in the same block.

Let me test w and x.
