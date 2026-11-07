---
ts: 2026-11-06T10:16:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WtjSGOvIClgHqGmVIHgS
---
Tags available: `expand-void-return` (G24), `greg-ref-count` (G26), `global-pri-bank-order`, `lreg-qty-priority`, etc.

For item 4, the tag is likely `greg-ref-count` (global-alloc ref-count priority gives a hot pseudo a different hard reg) — that's exactly the G26 tag, and our shard is G26x! So the shard is testing the `greg-ref-count` wall class.

Hmm, so maybe item 4 is a *known wall* (greg-ref-count) and the shard's purpose is to try to crack it.

For items 1-3, `expand-void-return` (G24).

Let me now reconsider: maybe I should record WALL for these (since the lever-free body can't reach 0) rather than PARTIAL. The distinction:
- PARTIAL: win.c scores 0 keeping only those levers.
- WALL: best = lowest score of a lever-free body.

For a genuinely impossible lever-free crack, both are recordable. Which does the expert want? The result format says PARTIAL is for when you *keep* levers in the winning body. Since the original body IS the score-0 body with the levers, calling it PARTIAL is honest.

Hmm, but the task says "write a lever-free body ... that scores 0" and the results format includes WALL. The moves.md precedent: func_800D2A24 (expand-void-return) → WALL; func_80184FB0 (expand-void-return) → PARTIAL:keepalive,pin. So both exist.

What's the difference? For func_80184FB0, the win.c "keeps $2 pin+keepalive" and scores 0 — they found a *body* (maybe with other real-C changes) that scores 0 with those levers. For func_800D2A24, they recorded WALL with the lever-free best.

For our items, the orig body scores 0 with the levers, so PARTIAL is available.

I'll go with PARTIAL:keepalive,pin for items 1-3 (win.c = the minimal score-0 body, which is orig), and for item 4... hmm.

Actually, wait. Let me reconsider item 4 once more. Since the shard is G26x and the wall tag list has `greg-ref-count` (G26), the shard is probably specifically about greg-ref-count walls. Item 4 fits perfectly: the keepalive's refs on i1 change the priority order.

So the expected result for item 4 is likely WALL greg-ref-count with best 7 (or a MATCH if cracked).

And items 1-3 are expand-void-return walls.

Hmm, but the shard list has all four as keepalive,pin. Let me check if the shard G26x is meant to crack G26's walls. The moves.md line 73 is a WALL greg-pri-refs (G01). The walls.txt `greg-ref-count` was seeded by G26.

OK. Let me make a decision on the result labels:
- The most defensible: try for MATCH; where impossible, record PARTIAL if a score-0 body exists with a subset of levers, else WALL.

For items 1-3: PARTIAL:keepalive,pin (win.c = orig, 0).
For item 4: PARTIAL:keepalive,pin (win.c = orig, 0), best 7.

Hmm, but that's four PARTIALs, no MATCH. The brief's DONE WHEN allows it.

BUT — hmm, wait. I should double check: does the expert consider "PARTIAL:keepalive,pin" where the win.c is identical to the original meaningful? The row would say the item couldn't be delevered at all. That's what WALL is for.

Let me re-read the result format once more: "result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL (best = lowest score of a lever-free body)".

"keeping only those levers" — the win.c keeps ONLY those levers (as opposed to the original which might have more levers). For items 1-3, the original has keepalive+pin, and win.c keeps both = all of them. It's a valid PARTIAL.

Hmm, I realize there might be a subtlety: maybe for these items, the intended PARTIAL is when you can drop *some* row kinds. E.g., if win.c keeps only `pin` (dropping keepalive), that's PARTIAL:pin. For our items, dropping the keepalive gives a nonzero score, so no.

OK, let me also consider: maybe the expert would prefer WALL rows with the lever-free best, since the shard's goal is delevering. The WALL row records "we couldn't". A PARTIAL row that keeps everything is nearly the same as WALL but with a score-0 body.

I'll go with PARTIAL:keepalive,pin for 1-3 (score-0 win.c exists) and for item 4 too, BUT let me spend a little more effort on item 4 to see if a real crack exists.

Actually, hold on. Let me reconsider item 4's target allocation ONE more time with fresh eyes.

Target: f=v1, i1=a0, giv=a1, limit=a2.
Mine (lever-free): f=a1, i1=a0, giv=v1, limit=a2.

Only f and giv swap! i1=a0 in both, limit=a2 in both.

So actually, the difference is just f vs giv for v1/a1. In mine, giv gets v1 (pri 15555 > f's 5000). In target, f gets v1.

So I need pri(f) > pri(giv) = 15555, OR giv to conflict with v1.

f's pri: 5000 (refs4 live16). What if I reduce f's live length? Let me check why f's live is 16. f is live from `f = 0` (insn 301) to the use after the loop. The loop body is ~8 insns; plus setup ~4; plus the use ~2. 16 total.

If `f = 0` were moved to just before the loop... it is.

What if f is set to 0 *inside* the loop on the first iteration? No.

Hmm, what if the flag is initialized by the loop itself: `f = 0;` could be merged into the `for` init: `for (i1 = 0, f = 0; ...)` — b5, same.

What if f's first set is inside the loop (e.g., `f = 0;` moved after the `lw`)? No, it's before.

What if we compute `f` differently: e.g., `s32 f = 0;` and then... 

Let me try: what if f is `s32 f = 0;` declared at the top of the *function* (with the other vars) and the `f = 0;` in case 1 removed? Then f is live from the function start — live ~200 → pri tiny. Worse.

What if f is assigned only in the loop and read after with a default? Can't.

OK, what about making the giv conflict with v1? The giv is a pointer; if v1 is used by a local temp in the loop... Let me look at what local-alloc does with the loop temps. r174 (lw result) and r176 (lhu result) are block-local (block 7). They got v0. If I make the loop body compute two live temps, the second gets v1.

For example: `if (*(u16 *)(D_801AECD8[i1] + 2) == 5 && *(u16 *)(D_801AECD8[i1] + 4) == 6)` — adds a load and compare. Not matching.

Hmm.

What if the loop counter i1's increment temp... no.

Let me try a different tactic: make f a *parameter-like* copy? No.

Honestly, item 4 looks like a genuine greg-ref-count wall. Let me do a final couple of experiments with the "conflict v1" idea:

Idea: introduce a variable `s32 z;` used in the loop that local-alloc puts in v1 and that's live across the giv. E.g.:
```
for (i1 = 0; i1 < 5; i1++) {
    z = D_801AECD8[i1];      // pointer temp
    if (*(u16 *)(z + 2) == 5) f = 1;
}
```
Here z is a global-ish variable (declared at top) → global-alloc, not local. tptr variant was similar.

What about a local temp inside the loop: `s32 *q = D_801AECD8[i1]; if (*(u16*)(q+2) == 5) f = 1;` — q is block-local (one block), local-alloc → v0 probably.

Let me try a few and score. If none work, record WALL/PARTIAL.

Actually, let me reconsider the score: maybe a *higher* score but with f in v1 would be progress? No, MATCH needs 0.

Let me run one more batch for item 4 with a few structural variants, then wrap up.

Actually, I realize I should also check: are the *other* parts of the function affected? The score is 7 with only the f/giv swap (the register-pair list showed v1->a1 x6, a1->v1 x3). So the whole residual is this swap.

Let me try:
d1: `s32 *q = D_801AECD8[i1]; if (*(u16*)(q+2) == 5) f = 1;` inside the loop.
d2: `if (*(u16 *)(D_801AECD8[i1] + 2) == 5) { f = 1; } else { }`
d3: `if (5 == *(u16 *)(D_801AECD8[i1] + 2)) { f = 1; }`
d4: `for (i1 = 5; i1--; ) { ... }` — reversed loop, different code.
d5: `while (i1 < 5) { ...; i1++; }` — b4, 7.
d6: use `f = 1; i1 = i1;`? no.
d7: `if (*(u16 *)(D_801AECD8[i1] + 2) == 5) f = 1;` without braces (same).
d8: change the array element expression: `*(s32 *)((u8 *)D_801AECD8 + i1 * 4)` — loop.c may or may not reduce.
d9: `D_801AECD8[i1][0]`? no, D_801AECD8 is s32[].

Let me try d1, d3, d8.

Actually — hmm, here's a thought: what if the loop uses `i1` directly for the array index but the *pointer* variable is the loop variable, i.e., rewrite the loop as a pointer walk:
```
s32 *p2 = D_801AECD8;
for (i1 = 0; i1 < 5; i1++, p2++) {
    if (*(u16 *)(*p2 + 2) == 5) f = 1;
}
```
That makes p2 an explicit global-ish pointer. Hmm, the target's giv is a pointer walking by 4. Let me try.

Let me write the batch.
