---
ts: 2026-11-06T10:20:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B2MhRzJo9gjRSTU2OoyD
---
Item 2's lever-free body (29 ins) vs target (32). The target has `move a2,a0` (a param copy!) and the ret values. The missing 3: `move a2,a0`, `move v0,zero`, `li v0,1`.

Interesting: the target has `move a2,a0` — a copy of arg0 into a2 (because the source `s32 a2 = arg0;`). In mine, the copy was coalesced away (a2 reused a0). So even the param copy differs.

Hmm, the register pairs show a2->v1 x4, v1->a0 x2, a0->a2 x1 — a 3-way cycle. So a real-C crack would need to prevent the a2/a0 coalescing and keep ret live.

For the lever-free best, 23.

OK. Now let me accept the WALL results and do the formal ≥30 tries per item with variety. Let me write generators that produce many variants per item, score them, and record the counts.

Let me create a combined approach: for each item, generate ~20 additional variants (beyond the ones already scored) and score.

Actually, let me reconsider the total effort. The brief wants ≥30 tries per WALL item. I have:
- Item 1: ~14 scored.
- Item 2: 1 (w1).
- Item 3: 2 (w1, wk, wp = 3).
- Item 4: ~35.

So items 1-3 need ~15-30 more each.

Let me write per-item generators with ~25 variants each and score. Then count total per item.

Let me do item 2 and item 3 generators now.

For item 2 variants (lever-free, keeping the function structure but varying real C):
1. decl order permutations (5)
2. `s32 a2 = arg0;` vs `s32 a2; a2 = arg0;` (2)
3. if/else instead of goto (2)
4. ternary ret (2)
5. temp splits for dz/dzsq/dy (5)
6. pointer casts: `Unkstruct_80180AC4 *p = (void*)arg0;` (2)
7. field access spellings (3)
8. reorder the two adds (2)

That's ~20+. Plus the existing ones = 30+.

For item 3 variants:
- decl orders
- obj/chn/w/rv splits
- store order permutations
- cast spellings
- if/else structure

For item 1:
- already k0-k4, m1-m3, w1, w2, w3, wk, wp = 14. Add ~20.

Let me write the generators efficiently.

Actually, I realize each sc.sh invocation compiles each file — for ~25 files that's ~25 × 3s = 75s. Fine.

Let me write item 2's generator.
