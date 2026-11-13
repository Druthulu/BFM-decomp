# TASK_PROGRESS — T8.c2 (handoff at context threshold)

## Done so far (committed)
- 2e545eedd2 T8.c2 batch A: decl<def (34 names, 7744 decl lines incl. func_80161208 `()` lines) take the def prototype; 172 short calls KR_AS; 10 kr_view rows; func_80161208 DECL-EMPTY-CONFLICT row dropped; tools/sig_evidence.py check_ret_views: a `#define SHARED_FN aF…` bind also defines its asm label (+ kit-corpus copy). Scratch 2178/2178 objects identical; type_census --check OK, --check-casts unbacked 0.
- d9d26dcda4 T8.c2 batch B: callers-set class. 563 defs widened (unread params) + 11 header defs where every caller sets the count (sites.min >= decl count): func_80016A5C func_8012D624 func_80138AB4 func_801391F0 func_80139788 func_801565C0 func_80156848 func_801632E0 func_801632F0 func_80163328 func_801633A8; their flipped decls (13431 rows) rewritten. 10 header-scale units whose callers pass fewer (sites.min < count) and widening would flip 600-3700 decls were NARROWED instead (minority decls -> def prototype, KR-OVER KR_AS): func_8001931C func_800D0CE0 func_8013240C func_80139220 func_801465C0 func_8014B33C func_80161104 func_80165910 guess_AddVelocityToPos guess_ObjRotTransSV. DECL-EMPTY-CONFLICT rows of func_80013450, func_801877C0 dropped (their `()` lines prototyped). 8 KR-OVER rows dropped (unwrapped). Scratch 3988/3988 identical; type_census both OK.

## In flight (uncommitted, built and verified, waiting only for type_census to finish)
- Batch C (ARG-OVER): pins -> params: func_80013478 (s16 *a0, s16 *a1), func_80131B14 x133 copies (u8 *a0v), func_8017F768, func_8017FF7C, func_80181864, func_8018247C, func_80182EB0, func_80185230; `u32 a3` local -> 4th param: func_8017D484 func_8017E4B4 func_8017EE08 func_8017EE64; GsTMDfast{G3GL,G3GNL,F4GL,F4GNL,G4GL,G4GNL} 8-arg PsyQ list (F3GL's spelling) + src/800.c:16177-16182 decls. Flipped decls rewritten (2130). 12 kr rows (2 replaced). 151 lying_exceptions rows (T8): UNINIT-LOCAL (func_80131B14 x133, func_8017DCC0 x3, func_8018015C, func_8017DC38, func_8017DD98, func_80188D1C, func_801816DC), STRUCT-RETURN W4_8018020C (6 names, ARG-OVER + 4 DECL-ARITY).
- Scratch 1542/1542 identical vs d9d26dcda4; sig_evidence --check: failed 0, unused 0, unledgered ARG-OVER 0, DECL-ARITY 2094 = nosites 845 + overboth 1249; kr-view all 0.
- NOT committed: type_census --check OK, but `--check-casts --residue` = uncovered P=8 (segment ov) and KR_AS unbacked 1
  (batch B was 0/0). Batch C stays in the working tree AND is saved as phase-ends/current/TASK_PROGRESS.patch
  (`git diff -- src include config`, 1496 files).
- Suspects: the pin -> param edits change a site's base kind (local -> param) or pin.py's deleted local lines shift later
  lines, so 8 raw P sites lose their RESIDUAL key (look in func_80013478 `a0[1]..a1[2]` in src/800.c, func_80181864,
  func_8018247C, func_80182EB0, func_80185230, func_8017F768, func_8017FF7C); the unbacked KR_AS is likely one of the 12
  new rows that type_census cannot back (alias/def_file), compare against the sig_evidence kr check (0 unbacked there).

## Hypotheses rejected with evidence
- Widening every callers-class def: flipped 31,409 agreeing `(void)` decls (shared headers; SHARED_FN headers bound to guess_* names) -> rule sites.min >= count to widen, else narrow decls.
- Uninit-local reads (switch without default) are not arguments: ledgered, not widened.

## Current hypothesis / next 5 steps
1. Find the 8 uncovered P sites and 1 unbacked KR_AS (type_census check-casts listing; .run/P37/census/residue_census.*
   has only counts), fix (re-key the residual entries or revert that one pin), rerun --check-casts --residue to 0/0, then commit (python3 .run/3.44/t8/c2/commit.py "<msg>" <list> config/kr_view_casts.tsv config/lying_exceptions.tsv).
2. R22: `make clean && make extract-all JOBS=16 && make check-all JOBS=16` (alone, background) -> 218/218.
3. `.venv/bin/python tools/sig_evidence.py -j 16 && .venv/bin/python tools/sig_evidence.py --check -j 16` (census is deleted by make clean).
4. main via `tools/gate_main.py --assert-baseline` on the committed tree.
5. Write phase-ends/current/logs/T8.c2.md final numbers (draft exists).

## Gotchas
- commit_task.sh auto-stages phase-ends/current/logs: T8.progress.md (modified by someone else) went into 2e545eedd2.
- sig_evidence mask_text sometimes hides calls (krfix "nocall"): wrap by sed at the error line.
- gcc error line for a conflicting def is the `{` line (head+1).
- Header with many TUs: compile errors appear once per TU path `src/<b>/../shared/...` - normpath.

## State to carry verbatim
- Scratch: .run/3.44/t8/c2/ (apply_decl.py, widen.py, krfix.py, conffix.py, iter.sh, pipe.sh, krrows.py, ledg.py, mkproto.py, unwrap.py, pin.py, units.py, ltok_edits.py).
