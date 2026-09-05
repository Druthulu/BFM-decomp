# T3 drafter brief — one function, byte-identical C (Phase 32, 2026-09-05)

You are byte-matching ONE PlayStation function (MIPS, gcc-2.7.2 -O2 unless the pack says -O0, PsyQ SDK) in the
Brave Fencer Musashi matching decompilation (repo: /home/musashi/bfm-decomp). Your C must compile to instructions
IDENTICAL to the target. Read `.run/P32/t3/SYS.md` (the laws) and your pack `.run/P32/t3/packs/<fn>.md` FIRST.

## Tools you have (use Bash; run from the repo root)
* Read the target assembly IN FULL: the `asm` path in your pack. The assembly is the ONLY ground truth.
* Read the destination TU (`tu` in your pack): if it already declares a symbol, copy that declaration EXACTLY
  (type, arity, struct name). If absent, type by access width (lb/lbu→s8/u8, lh/lhu→s16/u16, lw→s32).
* Cookbook: START at `docs/cookbook-index.md` (symptom-keyed), then read the § it names in
  `docs/matching-cookbook.md` (`grep -n "^#* *§NNN" docs/matching-cookbook.md`). Never read the whole cookbook.
* Leaf check (free, fast, per-instruction diff; masks jal/HI16/LO16 relocations):
      .venv/bin/python tools/match_one.py <fn> --c <your.c> --asm-subdir <dir of the asm path> --work .run/P32/t3/work/<fn>
  Add `--o0` only if the pack says the TU is -O0.
* Real-TU check (the one that predicts the gate — run it once you have a leaf MATCH, and before you submit):
      .venv/bin/python tools/rtu_match.py <fn> --split <sub> --source <binary> --c <your.c> --asm-subdir <dir of the asm path> --work .run/P32/t3/rtu/<fn>
  For `binary == main` add `--tu <tu path>`. `<sub>` is the pack's `sub` field.
  A standalone MATCH that fails here names a TU spelling to adopt (`conflicting types for X`: copy the TU's
  declaration of X exactly and cast at the use/call site) or a typedef the TU already defines (strip yours).

## Output contract (the coordinator gates and commits — you never touch src/)
* Scratch ONLY under `.run/P32/t3/work/<fn>/` (your `--work` dir) and `.run/P32/t3/rtu/<fn>/`. NEVER run `find`, `rm`, `mv`,
  or a glob over `.run/P32/t3/<arm>/` or any directory you did not create — that directory holds OTHER agents' deliverables
  (one tidy-up there moved eleven of them). Do not touch `src/.masked_diff_probe.*.c` — they are other agents' live probes.
* Write your BEST draft to `.run/P32/t3/<arm>/<fn>.c` (`<arm>` = haiku|sonnet|opus, given in your task), as a
  self-contained compile unit: the externs your body needs (spelled like the TU) + the function definition.
  NO `#include`, NO typedefs the TU already has, NO `__asm__` reproduction of the target (an assembly body is
  not a match and will be refused).
* If your target `.s` carries a `dlabel D_xxx` block in its `.rodata` section, your draft must DEFINE that data at
  file scope from the bytes (`const char D_xxx[] = "...";` / `const u32 D_xxx[] = { ... };`, cookbook §304) — an `extern`
  for it fails at LINK because the stub `.s` was its only owner (rtu_match is compile-only and cannot see it). Declare
  every shared global/function with the EXACT type the TU or its banked siblings already use — two drafts of one TU that
  spell one symbol differently both MATCH alone and fail together (§500-F).
* Write any evidence/prose you want to keep to `.run/P32/t3/reports/<fn>.md` (mkdir -p it). Your FINAL message is EXACTLY
  one JSON object on its own line and NOTHING else (the coordinator ingests 30+ of these; prose in the final message overflowed it once):
  {"fn": "...", "binary": "...", "arm": "...", "status": "MATCH|NEAR|FAIL", "closeness": <int or null>,
   "compiles": true|false, "draft_path": "...", "note": "<what closed it, or the residual's class + the levers you
   measured INERT — the cookbook § if you found one>"}
  `status` MATCH means rtu_match said MATCH in the real TU. NEAR = exact length, N mismatches (give N).

## The laws that matter most (from SYS.md; the pack repeats the ones with evidence)
1. SPELL EVERY SYMBOL FROM YOUR TARGET's own relocation lines. Never carry a seed's or a twin's per-binary symbols.
1c. match_one MASKS relocations — it verifies SHAPE, not symbol identity. After MATCH, walk the .s once more.
2. A twin/seed gives the SHAPE, never the symbols or the literals. A pack's `twin` is a starting body, not an answer.
3. If the pack or a journal note names a lever, grep the cookbook for it BEFORE drafting. A plateaued diff whose
   class is [permuter] (a register swap / a schedule reorder the search cannot reach from C) is DONE: submit NEAR
   with the class rather than spending ten more compiles on it.
4. An argument you invented changes scheduling (§263): check callee arity against the TU's decl before touching
   a fence.
5. Budget: stop when match_one says MATCH and rtu_match agrees, or when you have genuinely exhausted your levers —
   then submit honestly. Do not loop on a 1–2 instruction register-order residual.
