---
ts: 2026-10-22T00:05:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_no3x59cFlNOt2d0lyPNB
---
The `Scorer` class takes ALL recs (recs_for returns all includers' recipes) → `scorer.score(text)` — and the Scorer's docstring said "the bank verdict: IDENTICAL on every recipe of the file (a twin's object; every includer of a header)" (line 260). So the Scorer scores against EVERY recipe ✓✓.

So `--explain TU FN` uses the Scorer over all recipes — but it scores the tree's own lever-free body (lever_free_body), not my candidate. Hmm.

But: the Scorer is a class I could use... if I could run my own script ✗.

Hmm! Wait: maybe there's a tools/ script that exposes the Scorer with a candidate file... `--try` uses only recs[0]. Hmm.

Alternatively: `tools/delever.py --apply-body TU FN FILE` — it judges the body on every recipe and then WRITES it to the tree ✗ (not allowed).

Hmm, is there a "--dry-run" for --apply-body? The help says "--apply-body TU FN FILE" with --dirty-ok/--allow-residue options. It writes.

Hmm. What about `tools/delever.py --recipes --only func_801580B4`? "rung R: the cookbook's byte-neutral shape recipes tried mechanically on every RESIDUE body" — it would try candidates and judge them (read-only? it might write to the ledger). Hmm, it says "byte-gated per translation unit" and --apply writes. --recipes alone (without --apply) probably just tries and reports ✓ read-only-ish (it writes a trace under .run/P36 — outside my shard ✗).

Hmm. The constraint "write only under .run/P40/T11/G08/ plus appends to moves.md" is about MY edits; the tool's own scratch under .run/P36 is the tool's business... but running --recipes would be a heavy campaign (57 candidates × 136 includers!) ✗ way too slow.

Practical decision: for MATCH items, I'll verify at rec[0] (the tool's --try path, one includer) and additionally at a second includer via a small mimic TU if feasible...

Hmm, hold on! Actually, maybe I can check a second includer cheaply with the --body trick: the TU can be the header, and the tool picks recs[0]. But what if I pass a DIFFERENT header that contains the same function? No.

What about this: the --try TU can be an includer .c and the candidate a full TU. I said I can't build the full TU. BUT: what if the candidate full TU is just the includer's .c file with the header include line REMOVED and my body appended? The includer's .c is 1400 lines — but I don't need to reproduce it if... hmm, I DO (the candidate is the whole file).

Hmm, unless the recipe's pipeline compiles my candidate INSTEAD of the original src — so the candidate must be a complete TU.

OK: alternative — the ROM bytes are what they are; the risk is that some includer's macro environment changes the compilation of this function. Let me spot-check that risk cheaply: compare the baseline object bytes of the function across two includers using the tool itself: score my candidate against includer A (rec[0] = 0 ✓). To get includer B, I could use a TU = an includer .c with a candidate that is a full TU...

Hmm, hmm. What about the simplest possible check: the tool's --try on the header uses rec[0]'s baseline; if the ROM function bytes differed between includers, the tree's own body would score 0 at rec[0] but the bank (all recipes) would fail — and the tree's headers were BANKED byte-identically on every includer (that's the "bank verdict: IDENTICAL on every recipe" rule) ✓✓. So the pinned body is byte-identical at every includer. And the macro environment does NOT change the function's bytes (proven by the bank).

But that doesn't prove MY candidate compiles identically at every includer. However, since the function body is plain C (no macros, no conditionals, no context-dependent types), gcc's output for it depends only on the function itself ✓. The only context-dependence would be if an includer defined a macro that the body text uses (e.g. `reserved`, `buf1`) — let me check: the body uses identifiers like `reserved`, `buf1`, `buf2`, `param_1`, `s0`, `r`, `ret` — a macro named e.g. `ret` could exist! Hmm, `ret` is a plausible macro name somewhere? Unlikely but possible. Let me grep the includers for `#define ret` / `#define r` / `#define s0`.

That's a cheap sanity check ✓. Let me do that for the MATCH items.

Let me now move to items 8 and 9 (the remaining). Time is ~2h. Let me speed up.

Item 8: func_8017849C — pins $16 (q), $3 (tbl), $2 (c6c) — three pins! The kinds file says "pin". So a MATCH would need all three gone; a PARTIAL would keep some.

Item 9: func_8018655C__5fb02634 — pins $19 (i) and $18 (t).

Let me read item 8 and 9's kinds and try the "call-site cast" trick where applicable. For item 8: the pins are on `q` ($16), `tbl` ($3), `c6c` ($2). These are not call results — hmm, `tbl = D_8011DB08;` (a global) and `c6c = *(u8 *)(q + 0x6C);` (a load). So these pins force specific registers for locals — harder.

For item 9: pins on `i` ($19) and `t` ($18) — loop counter and a call result.

Let me do item 8 and 9 probes + nopin versions.

Let me write the nopin candidates for items 8 and 9 andscore them.
