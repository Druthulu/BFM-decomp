---
ts: 2026-11-06T12:11:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5TBxdu4mizMDaZz1stLb
---
All 141 includers score 0. w7 is a valid PARTIAL:launder.

Wait, I need to double check the results row semantics for PARTIAL: "result PARTIAL:<kinds still kept>". So PARTIAL:launder. And best = 0. wall = a tag from walls.txt or a new one. For PARTIAL, wall = a tag (WALL/PARTIAL need a tag). evidence = gcc pass + mechanism.

Let me record PARTIAL:launder, wall tag... The launder's role: it makes nx opaque so combine/flow doesn't fold `nx*0x10000>>0x10` into a 16-bit shift of the induction variable. Tag: `flow-known-value`? Or `launder-opaque-value`. walls.txt has `flow-known-value`: "flow/jump: a redundant test on a known value is folded away; target keeps it (G22)". That's close: the sign-extension is folded away because the value is known. I'll use `flow-known-value`.

Hmm, but the sll/sra is a truncation, not a test. Still, flow's known-value analysis. Let me use `flow-known-value` (existing tag) or a new `flow-known-range`. I'll use the existing `flow-known-value` since it's about a value known to be in range.

Actually, let me be precise: the launder makes `nx` opaque; without it, `nx` is known to be in [0,2], so `nx*0x10000>>0x10` is folded to a plain value. The pass doing this is combine or flow. Let me check which. The v07 diff showed the loop transformation (induction variable), which is loop.c or combine. Hmm.

The two missing instructions are the sll/sra at the condition and at the `(short)iVar4` comparison. The `(short)iVar4` comparisons are folded by combine/flow because iVar4's range is known.

Let me name a new tag `flow-known-range` — "flow/combine folds a 16-bit truncation of a value whose range it knows; only an opaque launder keeps the sll/sra".

Hmm, the brief says "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". So a new tag is fine. Let me use `flow-known-range`.

Evidence ≤140 chars: "keepalive cracked by do-while around the 2 stores; launder: flow knows nx in [0,2], folds nx*0x10000>>0x10 and (short)iVar4 -> no sll/sra; opaque launder needed".

Let me count: that's ~160 chars. Let me shorten: "keepalive -> do-while around the 2 stores (0); launder: nx known in [0,2] folds the 16-bit truncations (sll/sra) away; opaque launder needed" — ~135.

Let me install win.c = w7.c, append results, moves.md, notes.

Tries for item 3: w1-w8 (8), v01-v10 (10), u01-u06 (6) = 24. Plus the isolation tests (w2/w3 counted). Hmm, 24 < 30. For a PARTIAL, does the 30-try rule apply? "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". PARTIAL is also a wall (the row says wall = WALL/PARTIAL). Hmm, but PARTIAL means win.c scores 0 keeping only some levers — it's a successful partial crack. I think the 30-try rule is for declaring a WALL. For PARTIAL, we have a win.c scoring 0, so it's fine. But to be safe, let me add a few more tries... Actually the time is ~28 min (05:02→05:30), satisfying the 20 min. And I have 24 tries. Let me quickly run a few more (6) to reach 30 — cheap.

Actually, let me not waste time; PARTIAL has a scoring win.c, which is the deliverable. But the row's "tries" should be accurate. Let me just count what I did: w1,w2,w3,w4,w5,w6,w7,w8 = 8; v01-v10 = 10; u01-u06 = 6 → 24. Plus orig baseline. I'll record 24. Hmm, but if a PARTIAL counts as a wall, the ≥30 rule might apply. Let me add 6 quick variants to reach 30, to be safe. I can reuse the v/u generator with 6 more minor variants.

Actually, let me just do 6 more real attempts on the launder (cheap) — they might even crack it.

Let me try:
- iVar4 as uint
- nx as int with `iVar4 = (int)nx`
- condition `nx * 0x10000 >> 0x10 < 3` with nx unsigned
- `while (((nx << 16) >> 16) < 3)` (v05, done)
- use a for loop
- make nx a `short` and iVar4 an `int` with the condition `(short)iVar4`

Let me do 6 and score. Then record.
