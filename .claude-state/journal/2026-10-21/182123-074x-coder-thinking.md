---
ts: 2026-10-22T00:21:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_zEaZrfGFvUlmPrdbj1zC
---
Item 8 (func_80181CF4) = MATCH on the first try.

Let me write win.c for it and continue. Then items 3, 4, 6, 7, and 1, 2.

Let me create win.c for item 8 and record results so far.

For recording: results.tsv rows (tabs): `dir file func kinds result best tries wall evidence`.
- dir = the item dir name
- file = the src file (from list.tsv: `src/ov_SC03_097/ov_SC03_097_jr_8017D898.c`)
- func = func_80181CF4
- kinds = launder
- result = MATCH
- best = 0
- tries = number of candidates scored
- wall = -
- evidence = "gcc pass + mechanism ≤ 140 chars"

Let me determine the tries count for each item:
- func_8018AA98: scored orig(0), cand V1(11), base(11), v1(0) → let me count *candidates* (excluding the baseline orig?): base, cand(V1), v1 → hmm. Let me count distinct body candidates scored: base.c(11), cand.c(11), v1.c(0) → 3 tries (plus the baseline orig.c). I'll report tries=3.
- func_80181CF4: cand.c(0) → 1 try.

Evidence: "gcc pass: pv &= 0xFF000000 splits the mask into a real 2nd SET of pv's $3 reg (kills the sched1 birth boost); the load stays at its source slot; byte-identical 177/177."

≤140 chars. Let me write concise ones.

Now let me also append to moves.md (one line per item): `kind | func | MATCH: move / WALL tag — mechanism (G11)`.

And write notes.md in the item dir.

Let me batch: write win.c for item 8, notes for both items, append results rows, append moves lines.

For appending to results.tsv: use `sed -i '$a <line>'`. Careful: the line contains tabs — in sed, I can use \t in the replacement? GNU sed supports \t in the replacement ✓. And the text contains `|` (no problem) and `&`? Avoid & in the text or escape it.

Let me test the append mechanism with the first row.

Also moves.md append: `sed -i '$a ...' /home/musashi/bfm-decomp/.run/P40/T11/moves.md` — allowed? moves.md is in .run/P40/T11/ ✓ (the brief allows appends to it).

Let me do these now. First win.c for item 8 + a test append to results.tsv.
