### P35 T3–T5 (S94, 2026-09-08) — twin binaries, the macro bodies become per-function headers, the backlog shared
- **`tools/share_body.py` (T5, permanent — the successor of `dedup_propagate` + `dedup_extend`).** `--plan` (the buckets from the
  census: `extend` = registered classes whose members are not all sharing, `new` = unregistered same-address classes with private
  copies, largest reach first), `--apply --bucket extend|new [--batch N] [--limit N] [--only <h_exact>]`. Per class: the exemplar
  by majority normalized text (tie → pin-free → shortest; printed), its definition lines become the header (alias bodies get
  their binding), every private copy becomes the include at its position (bottom-up per TU), the registry group appended in
  shorthand by text (or the members added with `dedup_extend.add_members_surgical`). The gate per batch: every touched binary
  (a twin with its primary) snapshotted, `make check` by exit code, every object compared; a red binary is bisected class by
  class, the culprit's copies stay private and the class is ledgered in `config/dedup_exceptions.tsv` (TU-CONFLICT) with the
  compiler's line; "shared" only from the gate's success (R66). Evidence per batch under `.run/P35/share/`.
  **Run it on a COMMITTED tree, one batch per invocation** (`--batches`, default 1): the edit positions come from the run's census; the
  bisect restores TUs from an in-memory pre-edit snapshot (never `git checkout` — S94's version wiped the previous batch's uncommitted
  shares); a twin's instance resolves to its primary's TU and is edited ONCE. The failure cause is the first `file:line: message`
  diagnostic that is not a warning (gcc 2.7.2 errors carry no "error" token — S94's `Error 33` rows were the make line), and the
  ledger's reason code is derived from it: SYMBOL-NAME / GATE-REJECT / PARSE-ERROR / TU-CONFLICT (documented in the ledger's header).
  `--repair-registry` removes every listed member whose site is still a private definition (derived from the census, matched on
  (binary, vram) — h_exact is position-independent, a name-only match once removed 9,269); `--reexemplar <h_exact>` rewrites a
  registered class's header from the MAJORITY private text, re-gates its includers first (header rolled back on any red), then shares
  its private copies (`E_func_80168B70`: T4 had inherited the 7 late overlays' minority spelling). Records: `.run/P35/share/
  batch_<label>.json` (classes, results per binary, extended, rejected, causes), `repair_registry.json`, `reexemplar_<h8>.old.h`.
  **`tools/share_body_cycle.sh START END [R22_EVERY]`** runs bucket `new` unattended: per batch `--label new<k>`, exit code + the
  `gated N/N` line read, the phase-log entry appended, the bank committed (R42), the clean fleet run every N batches (R22, `218 passed,
  0 failed of 218` required); stops on the first red; refuses a dirty `src/`/`config/`. Size a call under the 10-minute foreground cap
  (a batch 40–100 s, a fleet run ≈ 90 s).
- **T6 (S96): the macro-era tools frozen or retired; the guard.** `tools/frozen.py` — the one refusal a FROZEN tool prints from its
  `main()` (never at import: libraries stay importable — cdecl imports gen_harvest_targets, 18 tools import family_remap). Dictionary
  status **FROZEN** (`tool_census` accepts it; the tool stays in `tools/`, its successor in the last column): family_sweep,
  gen_harvest_targets, p16_improve, recover_giant, restore_dropped_decls, normalize_self_decls, o0_subsplit, inject_capped_externs,
  aprop_autodraft, canon_sig_reconcile, conform_decls, blocker_probe, demacroize, family_remap (its command line; the library is live).
  Retired to `tools/sunset/`: dedup_propagate + dedup_extend (→ share_body.py, which absorbed add_members_surgical and the load_sig
  library surface verbatim), macro_draft, test_reconcile_ledger. **The macro-form guard** in `tool_census.py --check`: every LIVE
  `.py` under tools/ (FROZEN, retired and the six whitelisted detectors excluded) is parsed with `ast`; a non-docstring string constant
  carrying `DEFINE_func_` or `engine_core.h` is a gap — comments and docstrings are the record and may say anything. Its line reads
  `macro-form guard: 0 LIVE tools reference the retired form (N scanned, 14 frozen, 6 whitelisted detectors, M retired)`.
  `--guard-root DIR` runs only the guard against another tree's tools/ — the R39 negative control (a worktree of the pre-T4 commit
  `0e38b51a3` flags exactly 15 tools: the twelve whose dead macro branches T6 removed and the three retired; none frozen or whitelisted).
- **T7/T5b (S96): the S1 gate and the text tier.** `make tools-health` runs `share_census.py --selftest` and `--check --strict-macros
  --strict-text --quiet` before `report`; `dedup_integrate --check` has C2c (one source under `src/shared/` defining one function) and C2d
  (every member's site is an include of the group's source — from the census's cached per-instance forms). **The second oracle**
  (`--strict-text`) is keyed by (normalized text, address) over distinct TUs; it excludes the ledgered classes and the gate-1-deferred
  E/F classes (their same-address duplicates are PUBLISHED as `same_address_text_duplicates_deferred`) and treats what remains as the
  S1 text half. **The text tier (`tier: h_text`, T5b):** one normalized text at one address whose bytes differ per binary (the TU's
  declaration environment carries the per-overlay variance the original builds had) — a verbose-member group whose hash is the text
  hash and whose every member carries its own `h_exact`; C1 checks each member against its own hash; `share_body.py --apply --bucket
  text` shares them (header `func_<VRAM>__t<hash8>.h`, body from any site, declarations stay in each TU, the per-binary gate as ever).
  `progress.json` counts: `unique_function_bodies`, `duplicate_source_copies/_classes`, `text_tier_groups/_instances`,
  `deferred_same_address_texts/_copies`, and a dated `corrections` list (R75).

- **Twin binaries (T3).** Five overlay pairs are one payload (equal `config/check.*.sha`): SC01_005/006, SC03_118/119, SC02_000/003,
  SC04_018/019, SC03_014/015. The twin has NO source directory: `config/overlays.mk` declares `<twin>_TWIN_OF := <primary>` and
  `<twin>_SRC_DIR := src/<primary>`; the Makefile's twin block (after `-include $(C_DEPS)`) compiles the primary's files into the
  twin's OWN objects (`build/src/<twin>/<twin>_<suffix>.o`, static pattern rules, the same recipe, the -O0 objects kept) so a parallel
  `check-all` never races; the twin's yaml is the primary's carve with the alias substituted (`create_c_files: False` — splat must never
  recreate stub files), its `_JTBL_INTERLEAVE` and per-object `JTBL_PADS` lines likewise (the pads lines are keyed by OBJECT PATH —
  diff them by alias substitution, not by the block). Every tool asks `corpus.src_dir(alias)` / `corpus.twin_of(alias)` (the Makefile
  oracle) — never `src/<alias>/`. `audit-binaries` CHECK 3b asserts twin citizenship (primary onboarded and not a twin, same dir, no
  `src/<twin>/`, equal contracts, equal carves); `interleave_check` + `pads_audit` run on a re-carved twin (R60; `pads_audit` reads a
  twin's source through the oracle).
- **`tools/macro_to_header.py` (T4, one-off).** `--plan` (the census of macros: shared / single-site / dead, the naming), `--apply
  --binaries a,b,…` (each `DEFINE_func_X()` site → `#include "../shared/<space>/func_X[__h8].h"`, the TU's `engine_core.h` include →
  `engine_prelude.h`; headers written on first use, the LAST definition of a twice-defined macro, tokens asserted equal, no include
  guard), `--finalize` (the three legacy macro headers → plain headers — clearTbl40 in the `#define SHARED_FN` / include / `#undef`
  form —, the whale header moved under `ov/` with every `-O0` includer rewritten, alias-form bodies given their own
  `__asm__("func_X")` binding, the registry's `source:`/`func:` lines text-edited by group id, non-shared headers that included a
  macro header rewritten, `engine_core.h` deleted), `--verify` (0 sites, no macro header, the prelude present). The naming rule:
  `func_<VRAM>` + `__<h8>` iff (space, vram) hosts >1 h_exact class fleet-wide (86 of 2,215). The gate: the caller's per-binary
  `make check` + object A/B ledger (`.run/P35/convert/batch2.sh`, `ledger.txt`: 213 binaries, 4,121/4,121 objects byte-identical) and
  the clean fleet run. Measured S94: 246,347 sites in 3,818 TUs, 2,215 headers, 1,300 dead macros dropped, 224 s for the apply pass.

