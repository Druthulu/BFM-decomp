# jtbl leading-island split — design study (ox-alpha, P31 S58, 2026-08-24)

**Provenance:** produced by `stealth/ox-alpha` under `tools/api_agent.py` with a read-only surface
widened to `config,tools,Makefile` (`EXTRA_READABLE`). It read the target `.s`, the full sources of
`jtbl_carve` / `jr_isolate` / `ld_interleave` / `jtbl_rodata_pads` / `jtbl_family_bank`, the Makefile
excerpt, and cookbook §8 / §8a / §8a-pad / §8e / §154.

**Status: DESIGN, NOT VERIFIED.** ox cannot run `make`, so nothing here has been executed. Two of its
claims were independently checked against the source before this file was written, and both held:

* `jtbl_carve.py:66` — `open(cfg_path(ov))` is unguarded and `cfg_path` hardwires
  `config/splat.{ov}.yaml`; main's config is `config/splat.us.exe.yaml`, so main raises
  `FileNotFoundError`. This is the crash observed on `SaveLoadRoutine`, `func_8003388C`,
  `func_80035270` and `StreamLoadStateMachine`.
* `jr_isolate.py:83` — `line_re` matches only `- [0xADDR, c, SUB]` (code subsegs), so isolation
  cannot move a `.rodata` island. `jtbl_carve`'s own error text proposed a fix its tools cannot
  perform.

The remainder is the agent's verbatim deliverable.

---

// TOOLING PLAN — jtbl leading-island split (md_* modules) + main crash fix
// Ground truth read: asm/md_SC03_076/nonmatchings/md_SC03_076/func_801F218C.s,
// .run/bakeoff/toolwork/{jtbl_carve,jr_isolate,ld_interleave,jtbl_rodata_pads,
// jtbl_family_bank}.py, Makefile.excerpt, cookbook §8/§8a/§8a-pad/§8e/§154.
// config/*.yaml and the full Makefile are OUTSIDE my read surface; where that
// matters I name the file an engineer must read.

// ─────────────────────────────────────────────────────────────────────────────
// (a) LEADING-ISLAND: evaluate the error-text proposal (jtbl_carve.py:741-743)
// ─────────────────────────────────────────────────────────────────────────────
// VERDICT: HALF-RIGHT. "Isolate the jr function into its own code subseg" works
// unchanged; "so its .rodata is a separate OBJECT" is FALSE as stated, and
// ld_interleave cannot do the ordering it promises. Evidence from source:
//
// 1. jr_isolate.py rewrites ONLY `- [off, c, SUB]` lines (line_re :83 demands
//    `,\s*c,\s*`) and its contract (:16-17) is "never edits a `.rodata` carve".
//    On md_SC03_076 (config shape quoted in apply()'s own error: `- [0x0,
//    .rodata, md_SC03_076]` + `- [0x27C, c, md_SC03_076]`) it splits just the
//    code piece into [c, md_SC03_076] + [c, md_SC03_076_jr_<addr>] +
//    [c, md_SC03_077_after_<addr>]. The island piece still binds to the OLD
//    object name; the new jr object has NO .rodata input; the table bytes never
//    move. Isolation alone reproduces the §8a duplicate-at-wrong-address disease
//    in a new costume.
// 2. jtbl_carve.py cannot supply the missing half: parse_config() (:470-473)
//    defines the carvable region as the run of {data,.rodata} pieces AFTER the
//    last `c` piece and exits "no data-tail region" otherwise. A module's island
//    sits BEFORE its code — structurally uncarvable by this tool. (apply()
//    refuses in migrated_tables() before build_carve() is ever reached.)
// 3. ld_interleave.py --order cannot express the placement: that branch
//    (:101-115) hardcodes FILL/TEXT_START -> text -> empties -> ordered pieces
//    -> bss. Nothing can be emitted ahead of {PREFIX}_TEXT_START. A leading
//    island needs [.rodata pieces] BEFORE _TEXT_START; no existing mode does it.
//
// WHAT IS RIGHT (implementation):
//   Step 1 — jr_isolate.py md_SC03_076 --func func_801F218C, unchanged. Gives
//   the fn its own code object; that object's NAME is what the carve piece must
//   carry (the §8a dotted-subseg law).
//   Step 2 — NEW: split the LEADING `.rodata` piece around the fn's MIGRATED
//   table(s). Replace
//       - [0x0, .rodata, md_SC03_076]
//   with
//       - [0x0,   .rodata, md_SC03_076_pre]
//       - [0x268, .rodata, md_SC03_076_jr_801F218C]
//   (no post piece HERE: the table is the island's LAST occupant — its .s header
//   says file offset 0x268, 5 words end at 0x27C == the code piece start; a post
//   piece appears once a LATER table in the island is carved). Because the middle
//   piece's NAME equals the fn's code subseg, spimdisasm migrates the table into
//   the jr object's .s — the exact §8a mechanism aimed at a leading piece.
//   Span derivation reuses jtbl_range()'s oracles, but sourced from the FN'S OWN
//   .s (the dlabels are migrated there — read them the way migrated_tables()
//   already does at :709-718), bounded by the function's own `sltiu` (here
//   `sltiu $v0,$v1,0x5` = 5 entries = 0x14 bytes; jtbl_801EF6D0 %8==0 so no
//   trailing-pad trim and NO JTBL_PADS line — single-table carves get none, §8e).
//   Step 3 — extend ld_interleave.py with a leading mode (new flag, e.g.
//   `--leading <same comma list>`): emit the ordered .rodata piece lines FIRST,
//   then _TEXT_START/text/_TEXT_END, then bss — keeping every START/END/SIZE
//   symbol splat defines, with RODATA_START/END placed ahead of TEXT_START.
//   Tight packing preserved (. = ALIGN(.,4) between pieces; SUBALIGN(2) in the
//   splat script caps external alignment — §8e law 3).
//   Step 4 — config: the splat yaml gains the two/three piece lines above; wire
//   the interleave through the existing per-binary var mechanism (extend
//   `<ov>_JTBL_INTERLEAVE` or add `<ov>_JTBL_ISLAND := leading`). Mind the §8a
//   GOTCHA: no trailing #comment on the var line, $(strip) it. NOTE: the
//   Makefile's extract-stage wiring of JTBL_INTERLEAVE is NOT in
//   Makefile.excerpt — read the real Makefile + config/overlays.mk before
//   editing (also confirms whether md_* binaries already have an output-section
//   hook; ld_interleave takes `--section .<binary>`).
//   ORDERING CONSTRAINTS: (i) all input-section lines must be emitted in
//   ascending ADDRESS order — island pieces (0x0..0x27C) precede text (0x27C);
//   (ii) multiple matched fns follow the SAME contiguity law as overlays —
//   same-code-subseg carves must abut (gap 0, or gap 4 with a verifiably-zero
//   payload word, else NON-CONTIGUOUS → isolate that fn too); (iii)
//   jtbl_rodata_pads applies ONLY to the carve piece (pure $L/.word content) —
//   it must NEVER see pre/post, it refuses mixed include-rodata content (the
//   very 'unexpected rodata content .include "..."' error quoted in apply()).

// ─────────────────────────────────────────────────────────────────────────────
// (b) main: the crash
// ─────────────────────────────────────────────────────────────────────────────
// `jtbl_carve.py main --func <fn>` → apply() → migrated_tables() → func_jtbls()
// → func_subseg() → code_pieces() → overlay_vram_base() →
//   jtbl_carve.py:67-68  `txt = open(cfg_path(ov)).read()`
// with cfg_path() (:60-61) hardwired to `config/splat.{ov}.yaml`.
// CAUSE: every other failure on the entry path is a CLEAN sys.exit (missing .s,
// missing jtbl, no data-tail region); a Python TRACEBACK requires an unguarded
// exception, and the only unguarded I/O on that path is this open(). main is the
// root binary and predates the per-binary config naming (Makefile.excerpt :6-9:
// per-binary aliases are a Phase-9/10 addition), so `config/splat.main.yaml`
// does not exist → FileNotFoundError traceback. CONFIRM BY READING (outside my
// surface): the Makefile "Binaries" block — what is main's SPLAT_YAML path?
// SECOND-ORDER (bites immediately after the path fix): Makefile.excerpt :106-108
// says main's roots are REPO-LEVEL asm/ + src/ (siblings nest at asm/<bin>/),
// but every fs-touching helper hardcodes the nested root — all_data_labels :233,
// jtbl_words :244, _label_words :260, _sltiu_bounds :286, overlay_jtbl_addrs
// :162, func_jtbls :217 all build `asm/{ov}/...` ⇒ for ov="main" they resolve to
// nonexistent asm/main/... and turn real data into "not found" exits. FIX: an
// asm_root(ov) helper beside cfg_path(ov); both return repo-level paths when
// ov == "main". (Whether main is then CARVEABLE at all depends on its config's
// piece layout — parse_config will answer that honestly once paths work.)

// ─────────────────────────────────────────────────────────────────────────────
// (c) NEGATIVE CONTROL
// ─────────────────────────────────────────────────────────────────────────────
// Function: func_801F218C, binary md_SC03_076 (this task's target: 83 ins,
// jtbl_801EF6D0 @0x801EF6D0, sltiu bound 5, island span 0x268..0x27C).
// Two-stage control:
//   Stage 1 (split-only, fn STILL A STUB): after jr_isolate + island split +
//   re-extract, `make build BINARY=md_SC03_076` must be BYTE-IDENTICAL — size
//   43,760, SHA1 == payload. Proves the split itself byte-neutral.
//   Stage 2 (splice the matched C, rebuild): STILL 43,760 / SHA-equal. The
//   diseased baseline is the measured 43,768 (+8) with first diff at 0x144.
// Byte-level discriminators of success vs plausible-looking failure:
//   - objdump -h build/src/md_SC03_076/md_SC03_076_jr_801F218C.o: .rodata
//     sh_size == 0x14 (exactly 5 words, NO align pad — 0x...6D0 is 8-aligned);
//     md_SC03_076.o's .rodata shrinks by exactly 0x14. If BOTH objects still
//     carry table bytes, the migration did not happen (name mismatch).
//   - Final image: bytes from 0x144 onward IDENTICAL to payload (the +8
//     signature GONE, not moved); the five words 801F21C8/801F22C4/801F2238/
//     801F2278/801F22A4 sit at vram 0x801EF6D0.
//   - A build that links at 43,760 but with the first diff merely MOVED (pre/
//     post boundary off by a pad word, or table present twice) is FAILURE.
//     Arbiter = whole-binary SHA gate, NEVER rtu_match (§8a: masks relocs and
//     excludes jtbl rodata — false-MATCH class).

// ─────────────────────────────────────────────────────────────────────────────
// (d) WRONG rather than MISSING in the existing tools
// ─────────────────────────────────────────────────────────────────────────────
// 1. migrated_tables()'s premise (jtbl_carve.py:684-692: matching makes the C
//    "emit the table into the same object's .rodata, AT THE SAME ADDRESS, by
//    construction") is refuted by apply()'s own measured error text (+8 bytes,
//    first diff 0x144): pruning the .s drops the table out of the include chain
//    and cc1 re-emits it at the END of the object's .rodata. The REFUSAL is
//    correct; the no-op rationale is byte-measured wrong and must not survive
//    as documentation.
// 2. Hardcoded overlay VRAM window `0x80100000 <= w < 0x801D0000` in
//    _continuation_words (:306) and the over-span clamp (:434): md_SC03_076's
//    text lives at 0x801EF468+ — EVERY real entry (e.g. 0x801F21C8) falls
//    OUTSIDE the window, so "surplus word looks like a code address" is vacuous
//    and the continuation/clamp authorization gates misfire for exactly the
//    module class this work enables. Derive the window from the binary's text
//    bounds (config), not constants.
// 3. ld_interleave --order's docstring claims it "generalises the sandwich to N
//    pieces"; it generalises only TAIL islands (text-first is structural,
//    :101-115). Overstated contract — fix the doc or add the leading mode.
// 4. parse_config's "data region = after the last `c` piece" — the structural
//    gap that makes (a) necessary rather than optional.
// 5. Nested-root path helpers + cfg_path for ov=="main" ((b)) — wrong default
//    for the root binary, not merely absent.

// Residual unknowns + the files that answer them: config/splat.md_SC03_076.yaml
// (exact piece list/indent/trailing-bin — shape above taken from apply()'s
// error text + the .s's own /* 268 */ offset), config/splat.main.yaml existence
// and the Makefile "Binaries"/extract-interleave wiring. All outside src/,
// asm/, docs/, include/, .run/bakeoff/.
