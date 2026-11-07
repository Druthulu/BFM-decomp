---
ts: 2026-11-06T08:02:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NL04VFpLZBvng9EzjHdm
---
v64_w3c_u32 scores 5 (a block temp for the load) — same as the split. No 0.

Time: ~01:04. Item2 has taken 24 min with ~70 tries. I should wrap it as a WALL. But let me make one final attempt at the natural-C idea: maybe the original uses `twicep` in the `L.w38` and `L.w3C` assignments AND the keepalive exists because the compiler's allocation needs it — meaning it's genuinely a wall. The wall tag would be "lreg-qty-priority" or "global-copy-pref": "the loaded value keeps its copy preference for the dying base s5; lever-free the conflict that pushes it to a0 is missing". The wall tags include:
- `global-copy-pref` — "call-result copy keeps its hard-reg copy preference; the local result conflicts it, so the target's move is coalesced" (not quite)
- `lreg-qty-priority` — "local-alloc qty priority gives the hard reg to the other pseudo" (G22)
- `cse-copy-merge` — "cse merges a copy the target keeps in its own reg"
- `lreg-index-conflict`

Our mechanism: the target's w3c conflicts with s5 because twicep is live; lever-free twicep dies at the load, so w3c keeps the copy preference s5. That's essentially "global-copy-pref" or a new tag. Let me define a new tag: `lreg-copy-pref-dying-base` — "the load's dest keeps the dying base register's copy preference; target's base stays live across the dest's range". That's a good new wall tag.

But wait — the brief says WALL needs ≥20 min and ≥30 scored tries. I have both. Best lever-free = 5 (v5_split etc.). Hmm, but is v5_split "lever-free"? Yes (no asm). Best 5.

Actually, hold on. Let me reconsider whether the original might have the `L.w38` and `L.w3C` reads via a SINGLE pointer variable `u32 *p = twicep;` used twice, making the pointer live across the whole span. Let me test:
```
u32 *tp = (u32 *)twicep;
...
L.w38 = *tp;
...
w3c = *tp;
```
Then tp is live across w3c's range → conflicts with s5? But tp would be in a register (a1?) and the loads use `lw v0,0(tp)` — target uses s5 as the base. If tp is coalesced to s5 (it's twicep), the loads still use s5. And tp's liveness extends past the loads? tp is used at both loads; if no later use, it dies at the second load, same as twicep. No.

What if `tp` is used for the L.w3C store too: `L.w3C = *tp;` (a third load) — extra insn.

OK, let me also consider that maybe the original's keepalive is actually needed because the C source genuinely can't express it — that's why P36 added the lever. The whole point of this shard is to find real-C cracks where possible; WALL is an acceptable result.

Let me record item2 as WALL with best 5. But wait — the results format: WALL (best = lowest score of a lever-free body). v5_split is lever-free (no asm) and scores 5. So best 5, wall tag = a new tag. Evidence: "the load's dest keeps the dying base's copy preference ($s5); target's $a0 needs twicep live across the dest range; no lever-free spelling reproduces it".

Actually, let me reconsider the tag list: `lreg-qty-priority` is close but not exact. I'll use a new tag `lreg-copy-pref-dying-base`. The brief says "a new `<pass>-<what>`". Pass = lreg (local-alloc/global-alloc). Good.

Hmm, but let me double-check: is v5_split truly the best? v5, v7, v44, v46, v48, v53, v54, v55, v64 all 5. Yes.

Let me also make sure I've genuinely tried ≥30 scored tries: v1-v12 (12), v20-v29 (10), v30-v34 (5), v40-v49 (10, v47 compile error), v50-v55 (6), v60-v64 (9). Plus t1, tw_s32/s16/u8 (4). Total ~55. Good.

Time: 00:40:12 → 01:04 = 24 min. Good.

Wait, before declaring WALL, let me try one specific natural-C idea I haven't: the original may have used `L.w38 = *(u32 *)twicep;` and `w3c = *(u32 *)twicep;` but with `w3c` declared as `volatile`? No (lever).

Another: maybe the original's `w3c` is `u32 w3c = 0;` initialized at decl (dead init). C0505 mentions "init at decl". A dead init might change the qty. Let me quickly test `u32 w3c = 0;`. Also `u32 w3c = *(u32*)twicep;` (v50, 19). Let me test w3c=0 and w3c with a dead assignment.

Let me do a final small batch: w3c=0, w3c=(u32)twicep (wrong), w3c declared as u16, w3c as s16, and w3c with a redundant assignment.
