---
ts: 2026-11-06T21:11:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_I59Imv1GCV6VouSeFipZ
---
Interesting: d/e/f (barrier-less, do-while) show only the REG diff (a0/a1), no ORDER diff. But win.c (barrier-less, no do-while) also showed only REG diff! Wait, earlier win.c diff showed only REG (a1->a0 x3, a0->a1 x2), no ORDER. But l_only (launder kept, barrier dropped) showed ORDER diff.

Hmm, so without the barrier AND without the launder, the ORDER diff doesn't appear? That's odd. Let me re-check: win.c = no barrier, no launder → REG only (score 4). l_only = no barrier, launder kept → ORDER (score 4). b_only = barrier kept, no launder → REG (score 4).

So:
- barrier+launder: 0
- barrier only (no launder): REG swap
- launder only (no barrier): ORDER
- neither: REG swap

Interesting: with neither, the REG swap but no ORDER. With launder only, ORDER. So the launder, when present, causes the ORDER diff (it hoists e?), and the barrier fixes that. Without the launder, the ORDER is fine but the REG is wrong.

So: I need a real-C move that raises e's refs (to fix REG) but does NOT disturb the scheduling order. The launder disturbs order because its asm placement after lim acts as a scheduling barrier that... wait no, without barrier the launder causes ORDER. Hmm, the launder is an asm that also acts as a barrier-ish. Confusing.

Let me reconsider: win.c (neither) = REG only. So if I can fix the REG swap with a real-C move that doesn't add scheduling constraints, I'm done — no barrier needed!

The launder fixes REG but introduces ORDER (when barrier absent). So I need a different way to raise e's refs.

Wait, actually with win.c (neither), the REG swap is the ONLY diff. So the barrier was only needed because the launder created the ORDER issue. If I can fix REG without the launder, done.

So: raise e's n_refs without an asm. A real 2nd set of e that's live. Let me think again.

The launder: `e = (s16*)D_801E8F78; __asm__("" : "=r"(e) : "0"(e));` — this makes e have def, use, def, use = 4 refs. And the asm insn itself is a scheduling barrier that changes order.

A real-C 2nd set: `e = (s16*)D_801E8F78;` then another `e = ...` that's live. As discussed, hard because e used once.

BUT: what if we make the 2nd set part of a branch that's always taken but the compiler doesn't know? E.g.:
```
e = (s16 *)D_801E8F78;
if (t < lim) {
    ... uses e ...
}
```
What if:
```
e = (s16 *)D_801E8F78;
if (idx >= 0) { ... } // no
```

Alternative: use a conditional expression: `e = (idx >= 0) ? (s16*)D_801E8F78 : (s16*)D_801E8F78;` — both arms same, folded.

Hmm. What about a loop that runs once? `for (i=0;i<1;i++) e = ...;` — loop.c might unroll/remove.

What about a `do { e = ...; } while (0)` — we tried; didn't change REG.

What about making e assigned from a union/struct member so it's not REG_EQUIV, and used twice? Hmm.

Let me think about the actual refs needed. e needs n_refs ≥ 3 (to beat off's 3, or tie-break). With n_refs=3: floor_log2(3)=1, pri = 3/live. off = 3/27. If e live ~8, e = 3/8 > off. But current e n_refs=2 → 2/8 = 0.25 > 0.111. Already higher! Yet off wins. So my priority model is definitely wrong — the tie-break or something else.

Let me just try to get the global-alloc dump with allocno priorities. GCC might support `-dg` verbose? Let me check if there's a debug print in global.c controlled by something. Search for "if (1)" or "fprintf (stderr" in global.c.
