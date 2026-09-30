### §P37 S106 — 2026-09-12: the type census and the struct map (Phase 37 T1)

- **`tools/type_census.py [-j N] [--sites] [--check] [--selftest] [--out-dir .run/P37/census]`** — the structs phase's instrument.
  One walker per file (worker processes; `share_census.mask_text`/`scan_text` for the masking and the function spans; a per-file cache
  keyed by mtime/size/tool stamp under `.run/P37/census/cache/`, ~1 GB, ignored) returns: every struct/union/typedef **definition** with
  its o32 layout (`Resolver`: scalars, pointers, arrays, nested aggregates, unions, bit-fields, `packed`; a TU's own definitions first, then
  the canonical header, then the SDK sizes) and its layout hash — duplicate classes in three tiers (1 identical meaningful member names,
  2 opaque copy blocks, 3 layout twins with different meaningful names — NOT duplicates, reported), VARIANT camps (one name, several
  layouts — §64a), dead canonical names, canonical names redefined in `.c`; every **cast site** in six forms — P `*(T *)(…)`, I
  `*(T *)ident` / `*(T *)&D_x` / `*(T *)0x80…`, X `((T *)e)[i]`, M `M2C_FIELD(…)`, A `(T *)(base + k)` (address-of, no deref), C
  `((T *)e)->f` (typed cast-member, already a COMPONENT_REF — the rewrite's rung 1) — each with base class (param / local / global by
  value `PTR:` / global by address `AT:` / abs / nested / other), offset, accessed width and sign, load/store/rmw, stride; **coverage
  (R32)**: per form, sites recorded == an independent raw regex over the same masked text, else exit 1 (the readability regex's
  raw-text count is reported beside it for continuity: 411,850 vs 409,007 masked); the **declaration layer** (definitions K&R-read,
  4.28 M extern function declarations over 12,139 names, 3,870 spelled >1 way, 6,415 names with >1 body text, data externs typed >1
  way, asm-label aliases, builtins, attributes, `argcheck`'s lying set); **global blocks** (runs of ≥4 address-adjacent scalar `D_`
  symbols by declared width); **the struct map** — union-find over EVIDENCE edges only: a parameter's positional and named nodes; an
  argument into a callee parameter ONLY when the callee dereferences it (`typed_params`) AND, when both sides carry offsets, the
  callee's map is structured (≥2 offsets) and shares ≥1 offset of equal width with the caller's; single-source locals only (a local
  assigned from two sources is a reused temp and carries nothing); `&D_x` → `AT:D_x`; `x = f()` / `return v` through `R:<f>`; pointer-field
  reads through `FLD:<cluster>:<off>` to a fixpoint; a **width-conflict veto** on every merge (a bare global's declared type seeds its
  node); a function's identity is its body hash (`H:<shared header>` / `F:<nhash>` / `X:<space>:<name>`), never its name. Per type:
  members, sites, bodies, layout from the sites, width conflicts vs same-width sign mixes (a store's signedness leaves no byte), the
  evidence mix that built it, a `suspect` flag. Four **controls** (R39): the player block's agreed widths (+ the doc-disputed
  `D_80078F08/0C`: the code says 4, `actor-struct.md` says 2), MATRIX 32 vs MATRIX_L48 48, `Prim_8016E7C8` 1,192/1,192 in one layout (two
  spellings), the `D_800A651C` TU-CONFLICT row. Writes `type_census.json/.txt`, `struct_map.json` (full, ignored) + `struct_map_top.json`
  (300 types, tracked), `sites.jsonl` (`--sites`, 213 MB, ignored), **`parked.tsv`** (the 24 P36 parked classes with copies/sites/kinds,
  a `needs` class read from each pack's `mechanism.md`, the patch paths) and **`docs/struct-map.md`** (generated, R75). `--check` is
  T8's gate (0 duplicate classes, 0 definitions outside the canonical files, 0 raw casts, 0 lying declarations). Fleet run ≈ 3.5 min at
  `-j 16` (walk 49 s). Selftest 21/21 on a fixture with every form.
- **`tools/lever_census.py --check --strict` reads its own words** (S106): a DIRECT GTE coprocessor asm statement in a function body
  (kinds `gte` / `gte-unsigned` — Sony's idiom spelled inline instead of as `include/gte_inline.h`'s macro call; 6,717 today, incl.
  `func_8013D9B0`'s 268 unsigned respellings) is an asm statement outside the GTE header and FAILS `--strict`; the `--check` headline keeps
  the P36 definition (4,010) for the series' continuity. The three stale known-true controls were re-keyed (R85): `func_800226C0` 14 pins,
  `func_80178004.h` 8, the bare-name control moved to `func_801896EC` (2) — each counted independently with the gate-1 grep.
- **`tools/readability_progress.py --snapshot`** now REFUSES a stale type census (its `head` must be HEAD) and appends the census's
  columns (the four dereference forms, the typed cast-member intermediate, definitions/layouts/duplicate classes, the map); the TSV is
  read by column NAME (older rows carry blanks). **`tools/progress.py`** publishes `counts.types` and a "Types (Phase 37, …)" README
  sentence, with two dated `corrections` entries (the four-form count vs the one-form regex; `--strict`'s direct GTE statements).

