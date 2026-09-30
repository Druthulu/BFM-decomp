### §P37 S107 — 2026-09-12: the rewrite engine's full form, the layout library and the linked oracle (Phase 37 T3)

- **`tools/struct_layout.py`** — the o32 layout engine factored out of `type_census.py` (which re-exports the names): `SCALARS`, `SDK_SIZES`,
  `parse_struct_body` (MASKED text in — never raw), `Resolver` (`layout` / `resolve_name` / `layout_of_fields`), `layout_hash`, `field_offsets`,
  **`field_map`** (offset → name/width/sign/type of the top-level scalar/pointer fields), `leaf_at`, **the writer** `render_struct(name, entries,
  size)` / `entries_from_layout(map_layout)` (the final style: `/* 0xNN */` leading comments, `unk<HEX>` = accessed-unknown, `u8 pad<HEX>[n]` =
  never touched, `// size = 0x..`; an overlap or a misaligned scalar is a `ValueError`, a misaligned/overlapping map entry is skipped and
  counted), **the invariant** `audit_definition(def, resolver, text)` (`unk/pad<HEX>` at offset HEX, a LEADING offset comment equals the computed
  offset of its first declarator, the trailer equals sizeof — trailing legacy comments are not judged), `mask_comments`; `--selftest` (9). The
  legacy header today: `restruct --audit-types` → **26 violations, all legacy `pad<SIZE>` names** (T5's rename list).
- **`tools/delever_oracle.py` — the LINKED MODE.** `link_vars(alias)` (the Makefile's own `LD/OBJCOPY/LD_SCRIPT/UNDEF_SYMS/UNDEF_FUNCS/EXE/CHECK_SHA`
  via a `make -f Makefile -f -` query; main's `-T build/psyq/*_externals.ld` list from the Makefile's `_SYMS` lines, existing files only),
  `snapshot_links()` (called by `--snapshot-baseline`: every binary's `.ld` + `undefined_*_auto.txt` + the externals into the snapshot's
  `_link/<alias>/`, `_link/psyq/`, `links.json`), **`judge_linked(recipe, cand_bytes, tag)`** (the snapshot `.ld` with the one object pointed at
  the candidate and every other `build/…o` at its snapshot copy; `ld -T … -T undef_syms -T undef_funcs [-T externals] --no-check-sections`,
  `objcopy -O binary`, the ≤3-byte trim, SHA1 vs `config/check.<alias>.sha`; ~10 ms; verdicts IDENTICAL / DIFFERS / LINK-ERROR /
  NO-LINK-INPUTS), `reloc_only_diff(cand, base_path)` (the `.text` words equal under the relocation mask, only relocation operands differ —
  the cheap pre-check), `--linked-control` (md_SC07_004 `func_801A4258`: `p[1]/p[2]` → whole-object DIFFERS · reloc-only True · linked
  IDENTICAL; `p[2]/p[3]` → linked DIFFERS). **`--snapshot-baseline` now GUARDS itself:** an object whose bytes change in the snapshot must
  reproduce from an untouched compile of its TU, else the previous copy is restored and the refresh REFUSED naming the object — `build/` is a
  build product, the snapshot an oracle input (R56/R112; the T2 relocation control's `make build BINARY=md_SC07_004` had left a linked-identical,
  differently spelled object in `build/`, and a refresh carried it in). `compile_obj`'s error filter drops cpp's `NNN | …` context lines and
  `note:` lines and sorts gcc 2.7.2's `At top level:` prefix behind the message (R103).
- **`tools/restruct.py` (T3 form — the docstring is the reference):** `--plan/--apply --rung S|D|L --batch N --label L [--headers] [--only …]
  [--redraw VERDICT…] [--no-sa] [--recipes] [-j N]`; `--apply --rung D --callee F --signature "ret F(params)"` (a definition-side change as one
  multi-file unit); `--restore`; `--status`; `--check-ledger`; `--audit-types`; `--write-types --top N | --type … [--space ov] [--pointees]` →
  `.run/P37/restruct/types_preview/<space>.h`; `--try TU FN [--base] [--recipes]` (T2's local-type form + the R recipes on the kept casts);
  `--try-file TU [FN…]` (the engine's rung S → S2 → S+A with the REAL oracle and local types, NOTHING written); `--selftest [--real]` (48 stub
  checks; `--real` adds the calibration, the tree's own text IDENTICAL, a nop DIFFERS, the linked control and the reinterpret-macro proof → 53).
  Ledger `.run/P37/restruct/ledger.jsonl` (rows keyed rung/tu/unit/nhash; verdicts MEMBERS / S2 / S+A / KEPT-ALL / R:<recipe> / NO-SITE /
  TYPE-NOT-CANONICAL / TYPE-NOT-VISIBLE / REFUSED; DECL-CANON / DECL-PROMOTED / DECL-KEPT(cause) / FOLDED / FOLD-REFUSED / COMBINATION-FAILED),
  `inflight.json` (the only restore), `batch_<label>.json`, `apply_<label>.log`, `argcheck_cache.json` (the argcheck rows on the src stamp, 2.4 min
  to rebuild, ignored). **Gotchas:** `--apply` REFUSES on a dirty `src/`, a stale calibration or a snapshot without link inputs; the fleet walk
  (a process pool) runs before any worker thread exists — a fork from a threaded process deadlocked the first batch at 0 % CPU; a K&R-marked
  unit (every declaration `()` + `// K&R:`) is settled and never redrawn; header batches are serial (their includers compile in parallel).
- **`tools/restruct_cycle.sh START END [BATCH] [D|S|L] [ONLY]`** (`LABEL_PREFIX= TASK= REDRAW= CENSUS=0 HEADERS=1`): the detached batch cycle —
  clean tree → snapshot refresh (guarded) + calibration when stale → `--apply` read by exit code and `final X/X identical` → the clean fleet
  run → `type_census --sites` + `readability_progress --snapshot` → the log entry + the 🛑 headline → one commit. `setsid nohup … &` (R115).
- **`include/common.h`** — the reinterpret macros `LOBU/LOH/HIH/LOHU/HIHU/LOW/LOWU` (sotn's shape; proven equal to the bare casts on cc1's
  assembly by `restruct.macro_probe`, part of `--selftest --real`); the `M2C_FIELD` note corrected (it claimed "identical codegen to
  `p->field`" — false since the T2 probe: the `/s` flag). R22 after: `check-all: 218 passed, 0 failed of 218` (`.run/P37/baseline/r22_t3c.log`).
- **`tools/delever.py`** — `marker_edits(…, phase="P36")`: the attribution tail's phase is a parameter (`(P37 S+A <label>)`).
- **`tools/type_census.py`** — `walk_all(jobs)` factored out of `run_census` (the cached fleet walk the engine's rung D shares).

- **`tools/timeline.py` (lower panel, S107 on Drew's word):** the lever series is drawn as EVERY recorded increment on an ordinal axis —
  the Phase-36 log's own census lines for T1 / the T4 strip batches / the T5 GTE batches (`lever_rows()` parses `phase-ends/logs/Phase36.md`;
  the TSV began at T6) + every `docs/lever-progress.tsv` row — with a dashed marker and label where the KIND of step changes (`KIND_RULES`);
  the raw casts are two instruments (`cast_rows()`: the one-form regex count, then the four-form census as its own 100 %), never joined.
  Preview: `.venv/bin/python -c "import cairosvg; cairosvg.svg2png(url='docs/story-timeline.svg', write_to='<png>', output_width=1100)"`
  (`cairosvg` installed in the venv 2026-09-12 for this; not a build input).

