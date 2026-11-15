# 3.45 T15 — rung T, the typing engine (tools/restruct.py)

One pointer SOURCE gets its struct type at its declaration; its casts become member accesses. Every unit is judged on
the objects (delever_oracle); nothing is written unless IDENTICAL / IDENTICAL-LINKED. Code: restruct.py section
"THE TYPING ENGINE" (`t_plan`, `T_KIND_HOOKS`, `t_second`, `type_sources`, `type_check`, `type_selftest`).

## CLI
- `PY tools/restruct.py --type-source KEY[,KEY…] | --type-batch FILE [--type T] [--write] [--label L]`: dry run prints
  kind, type, declaration, edits, verdict / pending; judged, nothing written. `--write`: git-clean guard on the unit's
  files, writes IDENTICAL units, appends one rung-T ledger row per key (`.run/P37/restruct/ledger.jsonl`).
- `PY tools/restruct.py --type-check [--only REGION…] [--sources-dir DIR]`: see below. Exit 0.
- `--type T`: the type for a raw-only base (no struct cast on it, no single typed T14 flow).

## Keys (T14's source key, docs/ops/p345-t14-source-census.md "Source key")
- `tu:fn:base` — param / param-copy / local / ret-of / field / global copy (a local assigned from a global).
- `tu:fn:<holder text>` — T14's nested / member base (kind field): `H` or `H + k`, H the member expression.
- `name@binary` (the global's value: a pointer) / `&name@binary` (the object's address: the object is the struct).
  T14's directory keys (`shared/ov`, `src/resident`) take the one address the name has across the binaries of the
  files naming it; 2+ addresses -> pending (key one binary).
- A name used in a function but declared nowhere in it (`tu:fn:D_x`) -> its `name@<the TU's binary>` key.

## Kinds (t_kind: T14's local-kind refinement over the base's assignments)
- param: the definition head + every declaration (signature_change `--body`, plan_only) — one judged unit.
- param-copy / local / global copy: the local's declaration only (C0383: never a local copy added).
- global (`t_hook_global`): EVERY declaration of the one object. Scope: the files naming it whose binaries resolve
  the name to the key's address (TU -> binaries: walk `tu_aliases` = the build's source sets; header -> its includers'
  binaries; name -> address: `mipsel-linux-gnu-nm` on build/us/SLUS_007.26.elf or build/<b>/<b>.elf, else
  config/symbols.<b>.txt + symbols.us.txt; C0586). A file also built into a binary where the name is another object
  -> pending (G41: never by name alone across binaries). Declarations `extern T D_x;` (`&` key) / `extern T *D_x;`,
  file and block scope. Pending: array declaration, an initializer, a multi-declarator statement, a file-scope use.
- ret-of (`t_hook_ret`, a local assigned from a call): the callee's return type `T *` (its one definition's head
  rewritten, signature_change `--body` plan_only: definition + every declaration of its binaries), the local's
  declaration, its casts. Pending: 0 / 2+ definitions, a K&R head, a kept-cast macro / M2C_FIELD on the right
  (a field read). Every other use of the call (`f(…)` in the unit's files) through t_noncast; a discarded call keeps.
- field (`t_hook_field`): the holder `((S *)X)->m` / `x->m` (x declared `S *`) / `x.m` (x declared S); member m of
  canonical S, pointer-sized (width 4, a pointer or s/u scalar), retyped `T *m` in S's definition (`t_member_retype`).
  T defined after S in the same header -> pending. A local assigned from the member: its declaration typed too; a
  holder text key: the sites on `H` / `H + k` respelled `H->f`. Every other use of S.m in the files naming S through
  t_noncast (`t_member_uses`; a chain / call object is not read: the judge covers its bytes). A header edit reaching
  more than 40 objects (`T_HDR_RECS_CAP`, all files' objects) is UNJUDGED in a dry run and judged by
  tools/scratch_cmp.py vs HEAD at --write (C0589/C0590).

## Type decision
The struct-view casts on the base in the LIVE text (sources.tsv's type column predates T7's folds): C sites, raw sites
with a struct pointee, plain `(T *)b` casts — ONE struct type (2+ -> pending `2+ cast types`). None: `--type`, else one
typed T14 flow (`flows.tsv`), else pending `no type`. Then canonical (`canon_types`) and visible in every edited TU.

## Respell rules
- C `((T *)b)->f` -> `b->f`; global `((T *)&D_x)->f` -> `D_x.f`, `((T *)D_x)->f` -> `D_x->f`.
- Raw P / I / X(constant) / M through rung S's `s_edits` on T's field map -> `b->unkNN`; a missing member is inserted
  by splitting T's `pad`/`unk` byte array (size unchanged, audit_definition clean).
- A member of another width / sign, a variable index, a negative offset: the site stays (pending width-view / index /
  negative, non-blocking).

## Non-cast rules (t_noncast; any non-cast pending blocks the source: no edit)
Keep: a cast, an lvalue, `== / != 0|NULL`, a truth test, a `void *` / `T *` slot or variable, M2C_FIELD arg 0, a
discarded call. Edit: `b + k` / `b - k` -> `(u8 *)b ± k` (a global: only when its old type is byte-scaled; else
pending `ptr-arith`). Pending: arith, compare, deref, addr-of, kept-macro (CAST_* `(p)+(k)` would scale), arg-int,
arg (untyped / unplaced), assign <type>, return, value (a `&` object's value use), file-scope use, other.

## Verdict and the second attempt (`t_second`)
Attempt 1: the whole unit. On DIFFERS:
1. `greedy_kept` over the respelled sites (leave-one-out, cumulative revert, minimise); each trial rebuilds the unit
   (`P["_compose"](sub)`) with the kept sites spelled as rung-S kept-cast macros (`t_kept_text`: `respell_edit` with
   `S_KEPT_MACRO[site_class(kept=True)]`, the base as `(u8 *)b` — on a typed b `(p) + (k)` would scale). IDENTICAL ->
   written with the kept set; the row's `kept_sites` are KEPT(<class>) site rows.
2. No set: `run_recipes` on the source TU's kept view (every site kept, raw casts); an IDENTICAL recipe is adopted.
3. Still DIFFERS: no edit, verdict WALL-PENDING; `wall` = the judge's first differing object recompiled on the
   candidate, its first differing .text word vs the baseline (objdump) as symbol+offset, classify_residual's class
   (REG / COUNT / ORDER / MIXED / OTHER; COMPILE-ERROR, NON-TEXT, UNSCORED).

## Ledger row (rung T, unit `type:<key>`; the latest row per key is the verdict)
ts, label, rung, tu (or the key), unit, fn, source, kind, type, casts_removed, kept, pending[], verdict (IDENTICAL /
IDENTICAL-LINKED / PENDING / NO-EDIT / WALL-PENDING / DIFFERS / UNJUDGED / COMPILE-ERROR …), objects, files[], err,
forms {form: n removed}, attempt (1 / 2), kept_sites [site rows + text], recipe, wall {object, function, offset, cls}.

## --type-check
The latest rung-T row per key joined with T14's `sources.tsv` (`--sources-dir`, default .run/3.45/t14; built there
by `struct_twins.py --sources` when absent). Per region (`struct_twins.region_of`, `--only` names / globs): sources,
typed, casts removed (total and by form), kept, pending, wall, untried by T14 verdict; the pending reasons' heads; per
binary: sources / typed / pending / wall / untried; one line per ledgered source (kind, type, verdict, casts by form,
kept, wall, pending).

## Edit procedure per batch
1. R22 green at HEAD, then `PY tools/delever_oracle.py --snapshot-baseline` (C0622, C0538); control: a known-neutral
   key's dry run says IDENTICAL.
2. Dry run the batch (`--type-batch FILE`); read PENDING reasons and walls; drop or `--type` keys as judged.
3. `git status --short src include` empty, then `--write`; keys apply in order on the tree the previous left (the guard
   allows files this run wrote, `t_dirty`). A header unit > 40 objects is judged by scratch_cmp vs HEAD: run in background.
4. Gates, in order, each its own call (BEFORE numbers: `struct_twins.py --sources --check` and `--gate -j 16` before step 3):
   1. R22 alone: `make clean && make extract-all JOBS=16 && make check-all JOBS=16` -> 218/218.
   2. `sig_evidence.py -j 16`, then `--check -j 16` rc 0 (a DECL-PARAM row a retype made unused: remove it from
      config/lying_exceptions.tsv). `struct_twins --sources` needs `build/sig_evidence/census.jsonl`: run sig_evidence first.
   3. `type_census.py -j 16 --check --check-structs --check-casts --residue --sites` OK (`tools/run.sh --bg`).
   4. `struct_twins.py --write` alone (C0539).
   5. include/ changed: `ghidra_types.py --write`, then `--check`.
   6. `lever_census.py --check --strict --residue config/lever_residue.tsv -j 16 --quiet` rc 0.
   7. Rule T2: `restruct.py --rung S --residue --forms P,I,X,M --only <bin> --label <l>`, `--residue --restamp …`,
      `--check-residue --forms P,I,X,M --only <bin>` -> uncovered 0.
   8. `struct_twins.py --sources --check` AFTER; `--gate -j 16` (a stale ratchet FAILs), `--gate --write-ratchet -j 16`.
   9. Commit the batch: src, include, config/consolidation_ratchet.tsv, config/ghidra/types/, docs/struct-twins.md
      (docs/struct-map.md: restore to HEAD, only a stamp churns).
   10. `restruct.py --type-check --only <bin|region> [--sources-dir DIR]` printed (`--only` matches a region or a binary).

## Pilot (T15.c3, md_SC02_009, 51 keys = sources.tsv's 50 + `guess_g_BoxHitNormalX@md_SC02_009`)
- typed 17 (IDENTICAL; the field unit func_801E5338:a1 through scratch_cmp, 4284 objects), pending 34, wall 0, no real
  DIFFERS (second attempt not exercised). Casts removed 46, all C; kept 0 written.
- Pending reasons (first per key): non-cast arg-int 17, no type 8, field holder untyped 4, 2+ cast types 1,
  non-cast assign ? 1, kept-macro CAST_WIDTH 1, non-cast other 1, width-view P 1.
- `--sources --check`: cast sites 482681 -> 482635 (C 309741 -> 309695; P/I/X/M unchanged), sources 103626 -> 103610.
- Gate: casts_C 295509 -> 295463 (ratchet lowered); every other metric unchanged.

## Selftest (`--selftest`, the stub oracle, fixture .run/P37/restruct/selftest/t/)
(a) param typed in its definition and declarations; (b) two cast types -> pending; (c) raw site -> member inserted
into pad; global `&D_x@bin` over two TUs of its binary, the other binary's same-named object left; ret-of; field (the
member retyped in the header); (d1) a planted DIFF on one site -> kept as `CAST_ALIAS(s32, (u8 *)a0, 0x8)`, written,
KEPT row; (d2) every candidate DIFFERS -> WALL-PENDING naming object, function+offset, class; nothing written
(assembled objects through `T_OBJ_STUB`).
