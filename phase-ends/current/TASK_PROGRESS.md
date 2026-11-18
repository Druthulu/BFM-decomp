# TASK_PROGRESS — T17.c25 (read-only judge, 3rd pass over c23's 466 residual Unkstruct_800B5CB8 sources) — handoff 1

## Done so far (all files under .run/3.45/t17/c25/, gitignored; nothing in src/include/config/tools touched)
- asmidx.py -> asmidx.pkl: every retail binary (config/splat.*.yaml, 218 bins): jal targets, data words in 0x80010000-0x80200000,
  lui/%lo pairs (addiu/ori/loads/stores; indexed `lui;addu;lw` = kind `lwx`). ~1.5 min.
- lib.py: refs/crefs (co-resident only), fn_of (starts = jal targets + C defs), word/dis, prov2 (straight-line back-walk, structured),
  cores(): two ov_ never; md_SC only with its paired host (pairs.tsv, >=2 refs: md_SC03_053/054/076/077->ov_SC03_001, md_SC03_056->SC03_002,
  md_SC07_003/004->SC07_002, md_SC02_009->SC02_005, md_SC03_135->SC03_124, md_SC04_027->SC04_018/019, md_SC05_026->SC05_017);
  unpaired md_SC = same-disc assumption flagged MDHOST?.
- cidx.py (snapshot C defs per bin), assigns.py (C assignments of a var), gl.py (global accesses), fwd.py (forward closure of an object:
  stores to +off, guess_InitActorModel, state/script tables), tblhelp.py, polyf.py (fields read via casts), pass2x.py (c23 pass2 copy ->
  labfinal.pkl, p2state.pkl; reproduces c23: 784 decided pre-emit).
- judge.py -> dossier.tsv `source reason labels label-cites unknown searched kinds segs` (all 466 rows, ~30 s).
  Rules: asm callers (jal / data word / addr) recursive through entry regs; f5C/f60/f64 header-table ranges (c17 tables.tsv);
  script tables run by func_80178CBC/func_80178B18 (cmd word called with a0: src/shared/ov/func_80178D40__7a0f8b4c.h:98);
  jalr dispatch on a table formed in the same function; ret-of analysis of callees (epilogue branches); ALLOC map (+func_8001D074 sprite,
  func_801291C0 fx); holder rows: holder label + closure stores at +off over every ancestor (fx+0x20 = S; actor +0x64/+0xD4 = A);
  locals: C assignments -> field/call/global/param origins, per-assignment segments; globals: init word (scratchpad / static / pool) + stores.
- emit.py -> split3.tsv, keys_<Parent>.txt (lines= for var-reuse segments with casts in range), residual3.tsv, dead.tsv, counts.json.
  Checks: size, model u8 +0x24..27, per-segment offsets; conflict rule: a label only from c23 R4-typed-arg-out (consumer's declared type)
  loses to the single asm-reaching label (flag consumer-typed).
- Current counts (last emit): split rows 233 / sources 222: A 113, S 62, M 20, X(fx) 38. Residual 248: not-pool 87 (74 scratchpad
  0x1F800010 globals + static objects), no-caller 43, dead 36, render+0x20 23, holder+0xCC 12, ret-of 12, var-reuse-segment 7, arith 6,
  holder-other 5, local 4, param-copy 5, pointer-global 5, holder+0xD0 1, polymorphic 1 (ov_SC06_018 func_80191320:e), other-overlay-only 1.
  Dead functions 36 (dead.tsv), e.g. func_80178970 in 22+ overlays (no jal/word/addr in any co-resident bin).

## In flight
- Nothing mid-edit. Outputs exist but are NOT yet reviewed by hand; poly.md not written; spot check not done; log written as handoff log.

## Hypotheses rejected (evidence)
- Nearest-lower referenced address as a table base: wrong for SC02_005 80196288 (pad-vibration data, func_80183074 @801830C8); now the
  function-pointer run is used first, the nearest reference only when it is a confirmed script/dispatch.
- Param var = P0 always: wrong when the param is reassigned (ov_SC03_011 func_8017E884 a0 = func_80132EF4(a0,0x26) at :3922 -> fx);
  reassigned params now go through local segments.
- prov2 across the jal whose delay slot holds the reader: was "clobbered"; fixed (skip jal at pc-4); `addu v0,zero,zero` = const 0.

## Current hypothesis
- c23 polymorphic fx+actor 16: asm shows only the f64 path (entry 65 dispatchers); the A label is the consumer's typed param
  (e.g. func_80182B90 in SC02_026) -> decided X with flag; the consumer is the rule-4 site. Fields read are all fx header fields
  (+0x2,+0x6,+0xE,+0x14,+0x1C) common to the fx def and the actor def (struct_types.h:428 / :640-662).

## Next 5 steps
1. Write c25/poly.md: per c23-polymorphic source (20; list via `python3 polyf.py`): asm reaching paths (dossier col 4), fields read,
   common header check vs struct_types.h (snapshot) actor :428-572, fx :640-662, sprite :~575-620, model :~100-178; recipe.
2. Hand spot check 15 decided rows across rules (header f60/f64, script table, holder closure, segments, globals, consumer-typed):
   read snapshot C + `python3 -c "from lib import *; ins(...)"`; record file:line in the log.
3. Review residual no-caller 43 / render 23 / holder+0xCC 12 evidence in residual3.tsv for any rule bug (grep `searched:`).
4. Finalise the log phase-ends/current/logs/T17.c25.md (counts from counts.json, method, gotchas) and commit only it.
5. Return done with decided per parent, residual per reason, dead functions (dead.tsv).

## Gotchas
- generalizable: md modules call overlay library functions at fixed addresses; only an md module that an overlay's data references
  (tables) is co-resident with that overlay; count same-disc jal callers only for those.
- generalizable: the overlay header f64/f60 tables also hold md module handler addresses (SC07_002 f64 80190D40 entries 45-48 ->
  md_SC07_004); c17 tables.tsv missed them (same-vram md modules); use address ranges of the tables.
- prov2 is straight-line; branch merges can mislead (decisions require every reaching path to agree).
- run order: `python3 asmidx.py` (only if asm/index changes), `python3 pairs.py`, `python3 judge.py`, `python3 emit.py`. pass2x.py
  already produced labfinal.pkl/p2state.pkl (3 min, background).

## State to carry verbatim
- cwd for scripts: /home/musashi/bfm-decomp/.run/3.45/t17/c25 (scripts import each other; run there).
- Snapshot for C/lines: .run/3.45/t17/c23/snap (4c191bc99c); all `lines=` refer to it.
- Parents: A=Unkstruct_801202A0 S=Unkstruct_800B5BD8 M=Unkstruct_8001C9D0 X=Unkstruct_8011DB30 SM=Unkstruct_8011D030.
