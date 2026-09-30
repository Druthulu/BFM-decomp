### Tools added 2026-09-02 (S71) — R21 record

| tool | what it does | when you need it |
|---|---|---|
| `tools/journal_notes.py` | mines the agent journals for a `(binary, fn)`'s PAST ATTEMPTS and appends them to its pack; also reads `.run/journal_notes_local.jsonl` for hand-recorded evidence | **automatic** — `claude_wave_packs.py` calls it at the end of pack generation. Run `--wave <dir>` to back-fill a wave built another way (idempotent), `--fn F --binary B` to read what we hold on one function |
| `tools/launch_check.py` | refuses to launch an agent at an **already-banked** target; `--payload p.json` filters a `{wave,targets}` payload in place | before every launch. `wave_args` asserts open-ness at DRAW time, and payloads sit on disk while gates run — S71 launched one stale card and burned a full agent run |
| `tools/gate_triage.py` | routes a `parallel_gate` result set to the repair lane each verdict names (CARVE / UNDEF / CONFLICT / ARITY / PARSE / NO-DIAG / DIFF), asserting the staged-draft denominator | after any gate that banked less than it staged — tells you which lane the failures belong to instead of guessing |
| `tools/restage_matching.py` | rebuilds a gate plan from `recover_integration --probe-only` verdicts, keeping only drafts that compile-and-MATCH in their REAL TU | when a binary banks 0 and you suspect one bad draft is failing its siblings' shared build. **Caveat measured S71:** that probe compiles but never LINKS or CARVES, so its MATCH is not a bank prediction |
| `tools/weave_sweep.py` | the §406/§408 derived-selector sweep: scores each open stub's stored drafts, classifies the `sw $ra` disagreement from the residual, applies the clobber only to WEAVE-SUNK, `--lever-all` is the ablation control | as the template for "price a class by its RESIDUAL, not its SHAPE" — the sweep itself is a measured null (§408) |

