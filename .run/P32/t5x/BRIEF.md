# T4b — the FINAL 15: one Fable agent per function (Phase 32, 2026-09-05, session 491895ad)

You are byte-matching ONE PlayStation function (MIPS, gcc-2.7.2 -O2 unless your prompt says -O0, PsyQ SDK) in the Brave
Fencer Musashi matching decompilation (repo: /home/musashi/bfm-decomp — run every command from there). Your C must compile
to instructions IDENTICAL to the target. This function is one of the LAST 15 open functions of a 363,214-function fleet
that is otherwise byte-identical; every one of them has a prior exact-length draft and a written residual mechanism. Your
job is to find the C idiom that removes that residual — by reading the COMPILER, not by re-sweeping levers already
measured inert. Read, in order: this file · `.run/P32/t3/SYS.md` (the laws) · your pack `.run/P32/t5x/packs/<fn>.md` ·
the prior report(s) your prompt names · the cookbook sections your prompt names (`grep -n "^#* *§NNN" docs/matching-cookbook.md`;
start from `docs/cookbook-index.md` for symptoms; NEVER read the whole cookbook).

## Instruments (all from the repo root; the asm path / sub / TU are in your pack and prompt)
* Leaf diff (fast; masks relocations): `.venv/bin/python tools/match_one.py <fn> --c <draft> --asm-subdir <asmdir> --work .run/P32/t5x/work/<fn>`
  (add `--o0` only if your prompt says the TU is -O0).
* Real-TU check — the gate predictor, run before you submit: `.venv/bin/python tools/rtu_match.py <fn> --split <sub> --source <binary> --c <draft> --asm-subdir <asmdir> --work .run/P32/t5x/rtu/<fn>`;
  for `binary == main` add `--tu <tu>`. A `CC1 FAIL` names a TU spelling to adopt (copy the TU's declaration EXACTLY and
  cast at the use) or a typedef the TU already has (strip yours). Two drafts of one TU that spell a symbol differently both
  pass alone and fail together — spell every shared symbol exactly as the TU or its banked neighbours do (§500-F).
* RTL dumps of the pinned compiler: `tools/cc1_dumps.sh` (read its header for usage) gives `-dr/-dl/-dg/-dS/-dc` etc. so you can
  READ what cse/loop/local-alloc/global-alloc/sched did to your draft instead of guessing. `docs/gcc-2.7.2-map/` (cse_expr.md,
  loop.md, regalloc.md, sched.md) is the project's map of those passes; the compiler SOURCE is at `tools/reference/gcc-2.7.2/`
  (grep it: `grep -n 'find_best_addr\|qty_compare\|move_movables' tools/reference/gcc-2.7.2/*.c`).
* Permuter (only for a pure scheduling/regalloc residual, and only with a WELL-DEFINED seed): `.venv/bin/python tools/permuter_ils.py <fn> --draft <seed> --asm-subdir <asmdir> --klass REGALLOC --cycles 4 --secs 120 --j 2`
  (`--j 2` MAX — fourteen agents share this box). A permuter waypoint's masked score is NOT a closeness (R63): diff it against
  the seed, drop any semantically divergent mutation (a narrowed load, a store replacing an add), re-measure the sound remainder.
* Register pins `register T x __asm__("$16")`, zero-byte launders `__asm__("" : "=r"(x) : "0"(x))`, empty volatile fences, block-scope
  extern spellings, and the "birth point" of a variable (§47: qty_compare = floor_log2(n_refs)·n_refs·size/(death−birth)) are all
  legitimate, byte-proven levers in this project (§17, §30, §47, §162, §194, §364, §500). An `__asm__` body that REPRODUCES the
  target's instructions is NOT a match and will be refused (R62).

## Laws that matter most here
1. Spell every symbol and literal from YOUR target's `.s` relocation lines; a twin/seed gives shape only.
2. The prior report's INERT list is measured — do not repeat it; find the lever it did NOT try, or the mechanism it mis-read.
3. A `CC1 FAIL` in the real TU is a spelling problem, never a verdict. If your prompt names a sandbox TU copy under
   `.run/P32/t4/tu/`, use it with `--tu` for your rtu checks (the coordinator has already landed the byte-neutral TU edit).
4. If your `.s` carries a `dlabel D_xxx` block in `.rodata`, DEFINE it at file scope from the bytes (§304); an `extern` fails at LINK.
5. Read the target's frame/prologue first: the frame size and callee-saved set are fixed by the source's live ranges (§172).

## Output contract (the coordinator gates and commits — you never touch src/ or config/)
* Scratch ONLY under `.run/P32/t5x/work/<fn>/` and `.run/P32/t5x/rtu/<fn>/`. NEVER run `find`, `rm`, `mv` or a glob over
  `.run/P32/t5x/fable/` or ANY directory you did not create — they hold other agents' deliverables. Never touch
  `src/.masked_diff_probe.*.c` (other agents' live probes). Never edit anything under `src/` or `config/`.
* Write your BEST draft to `.run/P32/t5x/fable/<fn>.c` as a self-contained compile unit (externs spelled like the TU + the
  definition; NO `#include`, NO typedefs the TU already has). Keep the ledger's prior draft untouched.
* Write your evidence (what moved, what stayed inert, the mechanism as READ from the RTL dumps / the source, with file:line
  citations) to `.run/P32/t5x/reports/<fn>.md`.
* Budget: stop after ~2 hours of work or when the lever space named by the mechanism is exhausted. Report the measured
  closeness HONESTLY: MATCH only if rtu_match says MATCH in the real TU; NEAR with N otherwise.
* Your FINAL message is EXACTLY one JSON object on its own line and NOTHING else:
  {"fn": "...", "binary": "...", "arm": "fable", "status": "MATCH|NEAR|FAIL", "closeness": <int or null>, "compiles": true|false,
   "draft_path": "...", "note": "<what closed it, or the residual's mechanism (file:line) + the levers you measured inert>"}
