---
ts: 2026-10-22T01:00:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yxOhmlCQONNzoLxwXNtq
---
All 12 order variants = 2. The `li a0,409` position doesn't change with the source order.

Hmm. The remaining difference is a scheduling detail. What else could move it? The `do-while` placement, or the cast.

Let me think about the target's shape:
```
1b40: lw v1,32(s0)     ; e = unk20  (case0)
1b44: j 1b6c           ; goto shared
1b48: li a1,2          ; delay: argmode = 2
...
```
Hmm, wait, in the target the `li a0,409` is at index 44 (before the `li a1,2`?). Let me look at the target's asm around there.

From my candidate (pg018) listing:
```
1b3c: li a0,409
1b40: lw v1,32(s0)
1b44: j 1b6c
1b48: li a1,2
```
So in mine: li a0,409 (callarg0), lw v1 (e), j shared, li a1,2 (argmode in the delay slot).

The target has `li a0,409` at index 44 and mine at 45 → so in the target the order is: [something], li a0,409, ... hmm, one instruction earlier. The diff says: insert mine[44:44] target[44:45] = "li a0,409" → so the target has it at 44 and mine doesn't (mine has it at 45).

So the target's sequence around 44: ..., li a0,409, lw v1,32(s0)? and mine: lw v1,32(s0), li a0,409, ...? Hmm, the diff shows a single "replace": mine[45] = li a0,409 vs target[46] = li a0,409 — hmm, the "delete mine[45:46] target[46:46]" means mine has li a0,409 at 45 and the target has it at 46. Combined with the insert (the target has an extra instruction at 44), the target has ONE MORE instruction before it? But both have 89 instructions...

The diff: "insert mine[44:44] target[44:45]: 44 -- | li a0,409" and "delete mine[45:46] target[46:46]: 45 li a0,409 | --". So: the target has [44]=li a0,409, [45]=?, [46]=li a0,409?? That doesn't make sense... unless the target has li a0,409 at 44 AND at 46 (two of them — in different branches!) while mine has one at 45.

Hmm! Right: the target has `li a0,409` twice (once in the case0 path, once in the case1 path) and mine has it... hmm.

OK, whatever the exact layout, the difference is a scheduling/placement detail of one instruction.

Given the time, let me consider: is this item worth more effort? It's at score 2 with a faithful body (pg017). The developer's rule: a WALL needs ≥20 min and ≥30 scored tries. I've done 16 + 13 + 75 + 12 + 24 = 140+ tries for D96C and ~50 min. So I could call it a WALL, but let me try a few more moves since it's so close:

- The do-while at the e site + the cast at the v1 site gives 2; the *cast* on v1 might be the problem. What about a different replacement at the v1 site (e.g. do-while only, or a "real 2nd set" of v1 = mode)?

Let me look at the posgen results more comprehensively: the best combos were (cast,dowcast) = 1 and (cast,dow) = 2. What about (dowcast, dow) etc.? Let me print the full list with the combo names.

Let me get the top 20 with names.
