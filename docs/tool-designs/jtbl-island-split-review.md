# Review: jtbl leading-island split design (adversarial validation, 2026-08-24)

**Reviewed:** `docs/tool-designs/jtbl-island-split.md` (ox-alpha, read-only agent).
**Method:** static verification only against the working tree — every tool source, the real
configs, the real Makefile, the installed splat 0.41.0 / spimdisasm 1.41.0 sources, the actual
generated `build/md_SC03_076/md_SC03_076.ld`, and the actual asm/src for md_SC03_076. No build was
run (gate/sweep processes were live: `pgrep -f 'sweep_parallel|gate_stage|gate_main'` non-empty).
The two pre-confirmed claims (`jtbl_carve.py:66`, `jr_isolate.py:83`) were not re-litigated.

**Bottom line: GO-WITH-CHANGES — the carve idea is right and the byte layout works, but two of
the design's four steps are wrong (step 1 names a tool that provably cannot process the file;
step 2's `_pre` rename cannot build), and two are unnecessary (steps 3–4: splat's native linker
script already places `.rodata` ahead of `.text`). The correct implementation is *smaller* than
the design: one inserted config line + `jr_isolate_all.py --only`.**

---

## 1. Claim-by-claim verdicts

| # | Design claim | Verdict | Evidence |
|---|---|---|---|
| 1 | (a)1 `jr_isolate.py` contract "never edits a `.rodata` carve" (:16-17) | **CONFIRMED** | `tools/jr_isolate.py:16-17` |
| 2 | (a)1 isolation alone → "the island piece still binds to the OLD object name … the table bytes never move … reproduces the §8a duplicate-at-wrong-address disease" | **WRONG mechanism, right conclusion** | The island piece is a *dotted* `.rodata` paired by name to `md_SC03_076.c` (splat `segtypes/common/code.py:249-279` sibling pairing). Moving the fn to a jr c-file breaks migration (migration only targets the sibling file — `rodata.py:29-48` bails when `self.sibling is not None`), and the committed `md_SC03_076.c` has no `INCLUDE_RODATA` for the table — the bytes **vanish** from `md_SC03_076.o`; a matched-C table in `jr.o(.rodata)` has no ld entry and hits `/DISCARD/ { *(*); }`. Failure mode is *shrink/discard*, not duplicate. Either way isolation alone fails — the conclusion stands. |
| 3 | (a)2 `parse_config()` (:470-473) "defines the carvable region as the run of {data,.rodata} pieces AFTER the last `c` piece and exits 'no data-tail region' otherwise … structurally uncarvable" | **WRONG (and the truth is worse)** | "After the last c piece" is only the *comment* (`jtbl_carve.py:470`); the code takes **ALL** data/.rodata pieces (`:471`). The real config (which the design never saw) is `[0x0,.rodata]/[0x27C,c]/[0x35AC,data,tail]/[0xAAF0]` (`config/splat.md_SC03_076.yaml:96-99`) — so `parse_config` does **not** exit: it scopes the "region" 0x0..0xAAF0 *across the c line*, and `apply()`'s rewrite (`:749`, `lines[:lo]+region_lines+lines[hi:]`) would **delete `- [0x27C, c, md_SC03_076]`** — config corruption, written to disk (`:750`) *before* `set_overlays_var` dies on the missing overlays.mk anchor (`:766-768`; md vars live in `config/modules.mk:932+`). Reachable by any md fn whose table is NOT migrated (e.g. a jtbl in the 0x35AC tail): `migrated_tables` returns `[]` for it and `apply` proceeds. |
| 4 | (a)2 "apply() refuses in migrated_tables() before build_carve() is ever reached" | **CONFIRMED** (for migrated-table fns) | `jtbl_carve.py:727-746` |
| 5 | (a)3 `--order` branch (:101-115) hardcodes FILL/TEXT_START→text→empties→ordered→bss; nothing ahead of TEXT_START | **CONFIRMED** | `tools/ld_interleave.py:101-115` |
| 6 | Step 1: "`jr_isolate.py md_SC03_076 --func func_801F218C`, unchanged" | **WRONG — names a tool that cannot run on this file** | `jr_isolate.py:22-27` STATUS: scaffold "BLOCKED on split_src_region.py" (untouched since Phase 26, `git log`). Statically confirmed: `split_src_region.py` `trim` exits "cannot resolve address of item" (`:109-111`) on any top-level non-addressed item; `md_SC03_076.c:25-28` has exactly such a block (`extern void (*D_801F3468[])(void);` → `item_name` captures `void` → addr None). The production tool is **`jr_isolate_all.py --only func_801F218C`** (uses `overlay_src_split`; it is what `jtbl_family_bank.py:183` invokes). Its region model differs (cut *before* the jr fn; **no `_after` piece** — the jr object runs to the next boundary), and its name matches the design's: `md_SC03_076_jr_801F218C` (`jr_isolate_all.py:194-195`, `%08X`). |
| 7 | Step 2: replace `[0x0,.rodata,md_SC03_076]` with `[0x0,.rodata,md_SC03_076_pre]` + `[0x268,.rodata,md_SC03_076_jr_801F218C]` | **HALF-WRONG — the `_pre` rename cannot build** | The carve line (offset 0x268, name = jr c-subseg) is correct — splat pairs dotted `.rodata` to the same-named c subseg regardless of position (`code.py:249-279`; `readonly_before` exists precisely for rodata-first layouts, and md's leading island already migrates daily). But a dotted `.rodata` named `md_SC03_076_pre` has **no sibling c subseg** → splat resolves it to an "Implied C file" `src/md_SC03_076/md_SC03_076_pre.c` (`data.py:23-30`) that nothing creates → the ld references a never-built object. Worse, the rename **unbinds the island 0x0..0x268 from `md_SC03_076.c`**, breaking migration for the other five stub-owned jtbls (`jtbl_801EF5AC/5E4/61C/654/67C/6A4`) and orphaning the two committed `INCLUDE_RODATA` blobs (`md_SC03_076.c:131,133`) and compiled consts (`D_801EF6C0/6C8`, `:447,:502`). **Fix: keep the existing `- [0x0, .rodata, md_SC03_076]` line untouched and only INSERT the carve line** — its extent shrinks automatically (end = next piece's offset). The "split" is one inserted line. |
| 8 | Step 2 ground facts: carve at file 0x268; 5 words end at 0x27C == code start; `sltiu 0x5`; 0x801EF6D0 %8==0; single-table ⇒ no `JTBL_PADS`; no post piece (table is the island's last occupant) | **CONFIRMED** | `asm/md_SC03_076/nonmatchings/md_SC03_076/func_801F218C.s` (`/* 268 801EF6D0 */`, five `.word .L801F21C8/22C4/2238/2278/22A4`, `sltiu $v0,$v1,0x5`); `config/splat.md_SC03_076.yaml:97` (`[0x27C, c, …]`); `jtbl_carve.py:37` (single-table → no var) |
| 9 | Step 2: "read the migrated dlabels the way migrated_tables() does at :709-718" | **CONFIRMED** | `jtbl_carve.py:709-716` |
| 10 | Step 3: ld_interleave needs a `--leading` mode; "A leading island needs [.rodata pieces] BEFORE _TEXT_START; no existing mode does it" | **TRUE of ld_interleave, but the step is UNNECESSARY** | ld_interleave **never runs for md binaries** (no `<ov>_JTBL_INTERLEAVE` var; Makefile:648-649 gate) and never needs to: splat's native script is section-major with `.rodata` FIRST per `section_order` (verified in the actual `build/md_SC03_076/md_SC03_076.ld`: `RODATA_START` precedes `TEXT_START`), and within the `.rodata` group entries follow yaml/subsegment order (`linker_entry.py:238-270` buckets by section preserving order). Post-split the group is `md_SC03_076.o(.rodata)` then `md_SC03_076_jr_801F218C.o(.rodata)` back-to-back — exactly address order, tight (no intra-group ALIGN; `SUBALIGN(2)` caps input alignment). Auto-generated `.rodata` entries for carve-less c files (`auto_link_sections` default, `options.py:521-522`) insert *after* the declared ones (`code.py:84-140`) and are empty — byte-neutral. |
| 11 | Step 4: wire via `<ov>_JTBL_INTERLEAVE` / new `<ov>_JTBL_ISLAND`; "read the real Makefile + config/overlays.mk" | **PARTLY WRONG / unnecessary** | No interleave var is needed at all (see #10). And md per-binary vars live in **`config/modules.mk`** (`:932-…`), not overlays.mk — every mk-writing path in jtbl_carve hardcodes overlays.mk (`:114, :759, :782, :829-831`), so any future extension (e.g. a multi-table md span needing `JTBL_PADS`) must generalize the mk target first. The §8a trailing-comment/`$(strip)` gotcha is real (Makefile:122-125). |
| 12 | Ordering constraint (ii): same-subseg carves must abut (gap 0 / verified-zero gap 4) | **CONFIRMED as existing law** | `jtbl_carve.py:528-558` — but see §4 "pre-object contiguity" for the corollary the design missed. |
| 13 | Ordering constraint (iii): jtbl_rodata_pads must never see pre/post; refuses `.include` content | **CONFIRMED** | `tools/jtbl_rodata_pads.py:74-78`; pads armed per-object via target var (Makefile:689) |
| 14 | (b) crash chain `apply→migrated_tables→func_jtbls→func_subseg→code_pieces→overlay_vram_base→open(cfg_path)`; `config/splat.main.yaml` absent; per-binary naming a Phase-9/10 addition | **CONFIRMED** | Chain verified (`jtbl_carve.py:727→703-706→216→144-146→127→66`); `main_SPLAT_YAML := config/splat.us.exe.yaml` (Makefile:74); `config/splat.main.yaml` does not exist; Phase-9 binaries block (Makefile:39-47). The open is at `:66` (the design's verbatim text says :67-68; its own header says :66 — trivial drift). |
| 15 | (b) main roots are repo-level; the six fs helpers hardcode `asm/{ov}` (:162,:217,:233,:244,:260,:286) | **CONFIRMED** | `main_ASM_DIR := asm` (Makefile:85); `asm/main/` does not exist, main's tree is `asm/nonmatchings` at repo root; all six line numbers exact. |
| 16 | (b) "Whether main is then CARVEABLE … parse_config will answer that honestly once paths work" | **WRONG — the fix list is incomplete** | Main's region-line math happens to be safe (`splat.us.exe.yaml:206-209`: the data/rodata pieces are contiguous before the EOF line, no c lines between). But the **base/offset model breaks**: `overlay_vram_base` greps the first `vram:` = 0x80010000 (`:65`), while main's pieces are FILE offsets with `start: 0x800` — the correct flat base is 0x8000F800 (`main_VRAM_BASE`, Makefile:81). Every vram↔offset conversion is off by 0x800; `payload_word` **silently reads bytes 0x800 early** (zero-pad checks, gap checks, `spec_from_starts` all corrupted, no error raised). An `asm_root()`/`cfg_path()` fix alone ships a silently wrong tool for main. |
| 17 | (c) stub-state 43,760 bytes | **CONFIRMED** | `extracted/retail/SC03.CD.dir/FILE_076.dir/2.1` is 43,760 B (= EOF marker 0xAAF0), sha1 `9a165e…` == `config/check.md_SC03_076.sha` == yaml sha1. |
| 18 | (c) diseased baseline "43,768 (+8), first diff 0x144" for this experiment | **UNVERIFIABLE / misattributed** | Those numbers were byte-measured on **func_801F0F28** (`jtbl_carve.py:733`), not func_801F218C. Immaterial to the control's validity (pass = SHA-equality), but the design presents another function's disease signature as this experiment's baseline. (0x144 is the island offset of `jtbl_801EF5AC` — the first text-pointer word — consistent with a +8 text shift.) |
| 19 | (c) discriminators: jr object `.rodata sh_size == 0x14`; md object shrinks by 0x14; the five words at 0x801EF6D0; SHA gate the arbiter, never rtu_match | **CONFIRMED (one nit)** | Shrink 0x27C→0x268 ✓; the five words ✓ (from the .s); SHA-as-arbiter is project law. Nit: sh_size 0x14 holds because the table sits at *section offset 0* (`.align 3` is a no-op there), not because its final vram is 8-aligned — same number, misplaced reason. |
| 20 | (d)1 `migrated_tables()`'s "same address, by construction" premise (:684-692) refuted by apply()'s own error; stale doc must not survive | **CONFIRMED — real defect** | Docstring `:690-691` + `:699` ("a no-op here, NOT a refusal") vs the byte-measured refusal `apply():736-739`. |
| 21 | (d)2 hardcoded 0x80100000–0x801D0000 window (:306, :434) vacuous for md text | **CONFIRMED — and it is worse than stated** | Lines exact. md text starts 0x801EF6E4 (vram 0x801EF468 + 0x27C); every entry (0x801F21C8…) is outside the window. Consequences: `_continuation_words` can never absorb (under-carve risk, conservative), and the over-span clamp's *refusal* guard can never fire — for md the clamp would **silently drop real entries** (the dangerous direction). Also missed by the design: the window excludes **main's** text too (0x80010000..0x800629DC < 0x80100000). Derive from the binary's TEXT_LO/TEXT_HI (already in the Makefile per binary). |
| 22 | (d)3 `--order` docstring "overstated contract" | **PARTLY WRONG (minor)** | The same help text states "text -> [these] -> bss" explicitly (`ld_interleave.py:36`); only the clause "Generalises the … sandwich to N pieces" (`:40`) could mislead if read alone. A doc nit at most. |
| 23 | (d)4 parse_config's "after the last c piece" as the structural gap | **CONFIRMED as a gap, mischaracterized** | See #3: the comment is not implemented; the behavior is corrupt-on-rewrite, not refuse. Hardening it (implement the comment: anchor the region strictly after the last `c` piece, refuse anything else) is a **prerequisite**, not a nice-to-have. |
| 24 | (d)5 nested-root helpers + cfg_path wrong for main | **CONFIRMED** | Dup of #14/#15. |
| 25 | Config shape inferred as `[0x0,.rodata]+[0x27C,c]` (residual unknown, flagged) | **INCOMPLETE — honestly flagged, but it mattered** | The real config also has `[0x35AC, data, tail]` + EOF `[0xAAF0]`; that extra piece is what flips claim #3 from "refuses" to "corrupts". |
| 26 | Typo: "`md_SC03_077_after_<addr>`" | WRONG (trivial) | Should be `md_SC03_076_after_…`; and with `jr_isolate_all` no `_after` piece exists at all. |

**Tally: 14 CONFIRMED, 8 WRONG/PARTLY-WRONG, 1 UNVERIFIABLE, 1 honestly-flagged-incomplete** (plus 1 trivial typo).

---

## 2. Verdict on the mechanism: GO-WITH-CHANGES

The core idea — give the matched jr function its own code subseg and bind its table span to a
same-named dotted `.rodata` piece — is sound, and the byte layout works. But **as written the
design does not build**: step 1's tool dies on the source file, step 2's `_pre` object has no
producer, and steps 3–4 solve a problem splat does not have. The working implementation is:

1. `tools/jr_isolate_all.py md_SC03_076 --only func_801F218C` (production isolate; handles the
   md .c structure via `overlay_src_split`; writes the region files itself; no mid-flow extract).
2. Insert **one line** into `config/splat.md_SC03_076.yaml`:
   `- [0x268, .rodata, md_SC03_076_jr_801F218C]` between the existing `[0x0, .rodata, md_SC03_076]`
   (which stays untouched — its extent shrinks automatically) and the c pieces.
3. `make extract BINARY=md_SC03_076` → `make build` (stage 1, stub state, must be SHA-green),
   then splice the matched C into the jr file → `make build` (stage 2, must be SHA-green).
   No ld_interleave, no make variable: splat's native section-major script (rodata group first,
   entries in yaml order, `SUBALIGN(2)`) already produces the exact address-ordered layout.

Why this is byte-plausible (verified statically): the generated `.ld` places
`md_SC03_076.o(.rodata)` then `md_SC03_076_jr_801F218C.o(.rodata)` back-to-back at 0x801EF468;
md.o's rodata = includes + consts + the five remaining stub tables = 0x268 bytes; jr.o's rodata =
the migrated table (stub state) or the compiled switch table (matched state) = 0x14 bytes; text
follows at 0x801EF6E4. Same-name sibling pairing for the carve is the proven §8a mechanism, and
the leading position is already exercised daily by the module's own 0x0 piece.

## 3. The negative control (design §c)

**Discriminating, with caveats.** The pass condition — whole-binary SHA1 equality with the
43,760-byte payload at both stages — is the project's own arbiter and cannot pass for a wrong
reason: any migration failure, duplicate, boundary drift, or discard changes bytes. The
plausible-failure list (table twice, boundary off, diff moved) all fail SHA. Caveats:

- The "diseased baseline 43,768/+8/first diff 0x144" was measured on **func_801F0F28**, not the
  control function (claim #18). Do not treat reproducing that exact signature as meaningful.
- Stage 2 conflates two hypotheses: a red stage 2 could mean the mechanism is broken **or** the
  C match is wrong. Run stage 2 only with a candidate that already byte-matched elsewhere in the
  family, or accept the ambiguity.
- With `jr_isolate_all` there is no `_after` object; the jr object spans 0x2D24..0x35AC (the jr fn
  plus every trailing function). The objdump discriminator still holds — the census below shows
  the trailing functions contribute zero rodata — but that census is part of the control's
  validity and must be re-run per target.

## 4. What the design missed (would break an implementation or the rollout)

1. **The `_pre` object has no producer** (claim #7) — the single biggest defect; the design's
   own config sketch cannot link.
2. **jtbl_carve corrupts md configs instead of refusing** when a table is not migrated (claim #3).
   Harden `parse_config` (implement its own "after the last c piece" comment, refuse otherwise)
   *before* any md work — and before pointing jtbl_carve at main.
3. **Migration re-homing precheck.** Isolation moves every function ≥ the cut into a different
   c file; any moved function that owns a *leading-island* table, or matched C that emits const
   rodata, breaks the island reconstruction. Safe for this target — verified census: all six
   island jtbl owners (`func_801EFBB4/801F0210/801F0734/801F0A9C/801F0F28/801F218C`) are at or
   before the cut, and no const/`INCLUDE_RODATA` exists after `md_SC03_076.c:634` — but this is a
   per-target precondition, not a given. It belongs in the tool as a loud refusal.
4. **Pre-object contiguity wall.** `md_SC03_076.o` supplies ONE contiguous rodata run, so only
   tables adjacent to the island END (or chains growing backwards from it) are carvable cheaply.
   Example: carving `jtbl_801EF6A4` (@0x23C — func_801F0F28, the very function the §154-A refusal
   was measured on) leaves md.o needing 0x0..0x23C *and* 0x258..0x268 (the consts) — impossible
   for one object; the const-owning matched functions must be isolated too. The design's "a post
   piece appears once a LATER table in the island is carved" glosses over this: the post piece
   would have to be a *second* md_SC03_076 rodata entry, which GNU ld cannot split. The rollout
   therefore unblocks fewer module jr functions than "every jr member of every family" —
   plan for cascading isolations or accept end-adjacent-only.
5. **Pipeline integration.** Family waves reach carving through `jtbl_family_bank.py` →
   `jtbl_carve.py` (`:222`), which refuses §154-A binaries. Unless the island split is reachable
   from that path (and the refusal text updated), module jr functions stay wave-unbankable even
   after the mechanism exists.
6. **mk-file targeting.** All of jtbl_carve's overlays.mk writers (`set_overlays_var:759`,
   `set_pads_vars:782`, `revert:829`, `current_pads_specs:114`) and `jr_isolate_all`'s
   `repoint_overlays_mk` hardcode `config/overlays.mk`; md vars live in `config/modules.mk`.
   Dormant today (no md carve vars needed), a landmine for multi-table md spans later.
7. **Main's base/offset model** (claim #16): the path fix alone leaves `payload_word` silently
   reading 0x800 early on main. Add a per-binary (vram_base, file_base) pair, not just paths.

## 5. What could not be verified without a build

- Stage-1 byte-neutrality end-to-end (splat's actual re-extract output for the split config, and
  spimdisasm 1.41.0 writing the migrated table into the jr-subseg stub .s). Inferred from the
  §8a overlay precedent (134× proven) plus the module's own daily leading-piece migration; the
  linker-side ordering was verified against the real generated .ld and splat source, not a run.
- `overlay_src_split.partition()` on md-class .c files (static read says the model fits; the
  design's chosen `split_src_region.py` path was statically *dis*proven, which is stronger).
- The exact disease signature (+8 / 0x144) for func_801F218C specifically (measured value exists
  only for func_801F0F28).
- Whether any md_* binary actually has a tail-region jtbl (the trigger for hazard §4.2) — the
  hazard is structural regardless.

---

## Addendum — S59 (2026-08-24): the precondition is done, and what it measured

`parse_config` is fixed and the S58 blanket `md_*`/main refusal in `cfg_path` is lifted.
Proof: `tools/test_jtbl_parse_config.py` (read-only; run it before touching any of this).

**Three corrections to what S58 recorded.**

1. **The corruption class is exactly the 42 `md_*` configs, and `main` was never in it.** Measured
   over all 213 splat configs: 171 (every `ov_*`, `main`, resident) already satisfied the
   documented contract because their layout is `[all c pieces …, data tail]`; the 42 `md_*`
   modules do not, because the §154-A leading island puts `- [0x0, .rodata, md_XXX]` *before* the
   `c` piece. Under the historical derivation all 42 lose a `c` line to `apply()`'s splice — that
   is now demonstrated per-config, not inferred from a failure signature.

2. **main's defects were the path and the base, not the parse.** `cfg_path('main')` now resolves
   `config/splat.us.exe.yaml`, and `overlay_vram_base('main')` returns 0x8000F800 via the single
   existing derivation in `family_remap.vram_of` (R33) instead of the yaml's first `vram:`
   0x80010000 — with the naive value every vram→offset conversion was 0x800 short and
   `payload_word` silently read the wrong word.

3. **A third main defect the studies missed: the asm tree.** main is the one binary splat writes
   to the tree root — `asm/nonmatchings/800/func_8001A114.s`, `asm/data/*.data.s` — while every
   other alias gets `asm/<alias>/…`. `jtbl_carve` hardcoded `asm/<ov>/…` in nine places, so every
   main lookup missed a directory that does not exist and reported it as *"already spliced AND no
   stale copy"* — a true-sounding message about the wrong tree. Now routed through `asm_dir(ov)`.

**The refusal that replaced the class refusal** is operation-level (R43): a table whose file offset
is below the data region is in the leading island, which a tail carve cannot reach, so
`build_carve` refuses and names this lane. On the canonical target it prints the line to insert:

```
jtbl_carve: func_801F218C's jtbl_801EF6D0 at file 0x268 is BELOW md_SC03_076's data region
(starts 0x35ac) — it lives in the §154-A leading .rodata island … insert one
`- [0x268, .rodata, md_SC03_076_jr_801F218C]` piece in the island region and isolate with
jr_isolate_all.py --only
```

That 0x268 is derived from the payload and the config, independently of this document — a second
oracle agreeing with §2's prescription (R34).

**Where the two examples now stop, which is the next lane's starting line.**

| target | outcome |
|---|---|
| `md_SC03_076` / `func_801F218C` | refused with the island message above; config byte-unchanged |
| `main` / `func_8001A114` | reaches the real analysis and refuses correctly: subseg `800` would host non-contiguous `.rodata` carves (0x63238, the existing LZSS table, and 0x6327c) — isolate first, exactly as an overlay would |

So main's jtbl population is now blocked on `jr_isolate_all.py`, not on `jtbl_carve`; and the md
island split is blocked on the one inserted line plus isolation, as §2 prescribed. Neither is
blocked on config corruption any more.
