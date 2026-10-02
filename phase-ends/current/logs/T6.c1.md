# T6.c1 log (coder) — partial (harness context threshold)

## Tool fix (tools/restruct.py, UNCOMMITTED; selftest 109/109 OK; needs `make kit-corpus && make tools-health` then commit)
- `_sig_key(ret, params)` (module level, before signature_change): ret + param types, names dropped.
- signature_change: (a) callee with no walk def by C name -> alias defs found by asm label (`T aF…(…) __asm__("func_x")` + def head) -> `def_name[rel]`;
  (b) a def whose (ret, types) already equal the signature (K&R via kr_ansi_params) is NOT rewritten/judged = caller-only unit; still scopes;
  (c) shared-header def: def_bins += its includers' binaries; (d) a decl file whose rewrite is a no-op is skipped (not judged).
- decl_sites: skips asm-label decls (`… __asm__("x");`) — its rewrite dropped the label (bug: aF8014C4AC barrier lines; aF801848DC link DIFFERS; func_80181E0C DIFFERS were this).
- selftest lines: `--callee caller-only unit: _sig_key…`, `decl_sites skips an asm-label declaration`.
- earlier version passed kit-corpus + tools-health (exit 0); edits (b-d, asm skip) after it.

## Per group (driver .run/P39/t6c1/drive.sh; unit logs .run/P39/t6c1/t6c1_<callee>.log; checks *.check; calib per unit since calibration keys HEAD)
DRAWN (restruct IDENTICAL + make check rc=0 every touched binary, committed):
- aF801376E8 52 (ad4c0f60b1) · aF80146A6C 33 · aF8014C4AC 33 · aF80161208 15 · aF80185EEC 14 · aF8018CB18 12 · aF8018A860 8 · aF8018AFD0 8 · aF8018A224 2
- aF801843E0 4 (`--tu src/ov_SC03_124/ov_SC03_124_jr_80181B44.c`; --all-defs DIFFERS: ov_SC05_017 def has another signature)
- func_80181E98_impl 1 (--tu) · func_80173544 2 (--tu ov_MAIN_012 def, --with both func_801734BC__*.h = themselves; 141 objects IDENTICAL)
- func_8018283C 1 (def void->s32, --tu ov_SC07_007) · func_80143C74 7 (def void->s32, 119 files) · func_8012CC40 2 (def void->s32, 1275 files, 136 binaries rc=0) · func_801AAF34 2 (def void->s32)
- fix commit: 3 `!FAKE: barrier` asm decls of aF8014C4AC restored (respelled by the regex bug), ov_MAIN_012/SC02_037/SC03_107 rc=0.
NOT YET DRAWN:
- aF801848DC 15: DIFFERS linked (ov_SC04_018_jr_80188E1C func_8018C1E0) — caused by the asm-decl bug (header func_8018C1E0__5fb4815c.h asm decl respelled); re-run with fix.
- func_80181E0C 1: DIFFERS — same bug (asm decl at :4009 respelled); re-run `--tu src/ov_SC05_017/ov_SC05_017_jr_801808D4.c`.
- func_8012BD14 7 (narrow 6 + K&R 1), func_8012CBF4 3: `void F(s32 a0)` COMPILE-ERROR "void value not ignored" (ov_SC01_084_jr_8017CA80.c:3929; ov_SC03_105_jr_8017C8D0.c:3480); next: `s32 F(s32 a0)` --all-defs; zero-arg callers (`F()`) then expected too-few-args -> ledger ZERO-ARG-CALLERS.
- func_80014CF8 1 (shared/ov/func_80148648.h): DIFFERS build/src/ov_MAIN_012/ov_MAIN_012_jr_801458E0.o -> ledger `PROTO-DIFFERS ov_MAIN_012 func_80148648: u8 return`.
- aF8017E3F0 x2 groups (ov_SC06_018 `s32 *param_1` 3; ov_SC03_011 `s32 param_1` 1): not run; use --tu per def file.
- func_801851DC 1 (ov_SC03_002_jr_8018431C.c:3611) and func_8018A224 1 (ov_SC03_014_jr_801848E4.c:5811): the binary's own def is an in-TU alias
  (`aF8018CB18 __asm__("func_801851DC")` :3701; `aF8018A224 __asm__("func_8018A224")` :6148); argcheck resolves to another binary's def. Plan: unalias in-TU by hand
  (delete the asm prototype line, rename the def), decl -> def's own prototype, make check that binary.

## Gotchas
- workflow: commit_task.sh refuses `.run/P37/restruct/ledger.jsonl` as a path; `git add -f` it first and omit it from the paths.
- workflow: restruct --apply refuses after any commit (calibration keyed to HEAD): `delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 md_SC07_004 main -j 16` per unit.
- harness: a `while read` driver loses lines to children reading stdin; read from fd 3.
