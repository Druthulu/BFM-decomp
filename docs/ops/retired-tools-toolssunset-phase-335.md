## Retired tools (`tools/sunset/`, Phase 33.5)

*The rows below were moved out of the tool tables above when their tools were retired under the owner's criterion (superseded by a named
successor, or a one-off whose product exists); the census proved each had no live consumer. The verdicts are in `tools/sunset/README.md` and
`config/tool_dictionary.tsv`; the successor's own row stays above.*

| Area | Tool | What it did |
|---|---|---|
| | `tools/exemplar_miner.py` | **(Phase 20 / T2, cookbook §20)** Residual router: consume `.run/wall_taxonomy.json` (bucket/nins) + per-overlay reach (dedup_propagate's computation) → route every residual stub to a lever (WAVE / STRUCT / PINS / STUB) ranked by reach×size → `docs/exemplar_curriculum.md` + `.run/exemplar_routing.json` (wave-target list). "Scan all residuals, size the pools, pick the teachers." Caveat: its `mismatch` is the M2C-draft mismatch, not the hand-match floor. |
| | `tools/symcheck.py` | **(Phase 29 SESSION-18, cookbook §67a)** The pre-gate SYMBOL-SET guard: diffs the symbols a draft's object references (reloc records) against the target `.s`'s `%hi`/`%lo`/`jal` set. Catches the class **every masked oracle is structurally blind to** — `match_one`/`masked_diff` compare relocation-MASKED words (object-vs-`.s` mode is symbol-agnostic by construction) and `rtu_match` **compiles without linking**, so a draft that invents an extern no symbol table defines reads MATCH in both and can never bank (the SESSION-17 `func_801463A0` `_s`-alias trap). Negative-control-proven: on a draft with one renamed data extern, `match_one` reports the SAME 14 mismatched as the correct draft while `symcheck` exits 1 naming both the MISSING and the INVENTED symbol. `--c` (compiles via `match_one`, so the triple can never drift) or `--obj`. A cheap necessary condition, NOT a match oracle — still finish on the byte-gate (G3/P9). |
| | `tools/fix_header_decl.py` | **(Phase 29 SESSION-13, cookbook §63 + its UPDATE)** Rewrites a shared `engine_core.h` caller decl to a draft's byte-true sig. **Effectively retired**: its `[SAFE]` verdict inspects one caller and is structurally blind to the other ~137 overlays the shared decl reaches — 3/3 banked per-binary, then R22 **139/140**. Use `demacroize.py` (T1) instead. |
| | `tools/rtu_shadow.py` | **(P31 S61)** Shadow-mode `rtu_match` beside the wave gate to decide the gate INVERSION (§3 of the same analysis). `--wave X` (prospective, before X is gated, never while a gate is in flight) writes `.run/rtu_shadow/X.jsonl`; `--join X` after the gate commit prints the rtu-verdict × outcome matrix, P(bank | rtu MATCH), the false-negative rate, and current-vs-inverted build counts. Drafts map to binaries through the shard's targets file, never by bare name. |

*Rows shared with a live tool were left in place: `canon_draft_decls.py`; `t5_bank.sh, t5_targets.py`; `bounce_drafter_on_queue.sh`.*

### §P36 S102 — the delever engine's second generation: the tools added or repaired on 2026-09-10

Everything below is LIVE and carries a `config/tool_dictionary.tsv` row. Read this section before touching the engine.

**The generator registry** (`tools/delever.py`, `recipe_candidates(..., families=)`; each generator's own docstring
carries its mechanism, its `file:line` citations into `tools/reference/gcc-2.7.2/`, and the body it was harvested from):

| family | function | what it rewrites | harvested from |
|---|---|---|---|
| R15 | `sink_merges` | the statement after an if/else chain sunk into every arm, deleting the cross-block variable | agent a1, `func_80156044` |
| R16 | `constant_holders` | a local whose only assignment is one integer literal written at every use and deleted | agent a2, `func_80168828` |
| R17 | `constant_run_splits` | a run of same-literal assignments split by moving a differently-valued one into it | agent a2 |
| R18 | `bystander_moves` | one independent statement moved to each other position in its block, up to six away | agent a3, `func_801397B0` |
| R19 | `restore_arguments` | a call re-issued at the callee's REAL arity through a function-pointer cast, one candidate per in-scope value | agents a7/a8/a11/a12/a13/a25 |
| R20 | `narrow_chains` | every local in one def-use chain narrowed TOGETHER, and each pair of chains together | agent b3, `func_8016CBC0` |
| R21 | `second_consumer` | `v = E; slot = v;` → `v = slot = E;` (chain) or `slot = E; v = E;` (hoist), each site and ALL sites | agents b2/b6 |
| R22 | `merge_walked_pointers` | a second pointer `q = p + K` stepped in lockstep with `p` deleted; `q[n]` → `p[n+K]`, `*q` → `p[K]` (S103; leads the COUNT class after R19) | agent c2, `func_8013D8FC` — known-true: its start text's R22 candidate is the agent's closing body, score 0 |
| R23 | `split_reused_locals` | a local fully redefined several times at one brace depth of one open block (straight-line or between `if` groups; pointer declarators kept) split into one name per value (`u16 a, b;` → `u16 a, a2, a3, b, b2, b3;`), each and ALL (S103; leads the REG classes after R19) | agents c1 `func_80135168` / c8 `func_80135004` — known-true: its joint split scores exactly what each agent measured for the move alone (12, 26); on c16's `func_8013D178` its split of `p` alone scores 0 — a whole close with no agent |
| R24 | `word_read_bitfields` | the addPrim copy `X->addr = Y->addr;` read as a whole word `X->addr = *(u32 *)Y;` (a 24-bit field read + store leaves a phantom flow-time mask reference that decides `allocno_compare`), each site and ALL (S103; REG classes after R23) | agent c20 `func_8013DD68` — known-true: the in-loop site alone scores 10 from 17, the other two sites nothing, as the agent measured |
| R25 | `trim_arguments` | a call passing MORE arguments than the callee's real definition re-issued at the real arity (direct and through a cast to the real signature); refused when a dropped argument has a side effect (S103; beside R19 in every class — the inverse move) | agent c24 `func_8012956C` (a phantom fourth argument read off a live `$a3`). No single-move known-true number: on c24's texts the trim alone scores 11→12 and 4→7 — its close was joint. The census at S103: 203 residue classes / 448 bodies over-arity |
| R26 | `alias_repeated_addresses` | a symbol's address used twice or more, the later use(s) through a body-local `extern u8 SYM_b __asm__("SYM");` alias so cse (which compares symbol names by pointer) cannot merge them into one callee-saved pseudo (S103; class-E declaration, not an asm statement) | agent c45 `func_80183E3C` — known-true: its start text's "second" candidate scores 0 from 38 |

**Three of these are JOINT edits and that is the point.** R20's single-chain candidates score 43 and 51 where the joint
scores 0; R21's single sites are worse than its joint form; b7's four-way retype has every intermediate worse than the
start. A beam that only composes one-move steps walks AWAY from these answers, which is why thousands of compiles sat
flat on those bodies. When a generator's win is joint, generate the joint candidate — do not rely on the search.

**Call signatures — the largest class in the phase** (six agents found it independently before any tool existed):
- `tools/argcheck.py [--json F] [--argpin-only]` — every call declaration narrower than the callee's REAL definition,
  read from the definition wherever it lives. Reports the scope, which says which FIX is available: the CAST route is
  body-only at either scope, widening the declaration itself needs block scope. **Known blind spot in its docstring:** a
  function declared `(void)` AND defined `(void)` everywhere disagrees with nothing, so a declaration comparison cannot
  see it; only the residual can.
- `tools/decl_repair.py [-j N] [--apply]` — the free-correctness half: a declaration is repaired only where every call
  in that unit ALREADY passes the arguments. Compares `.text`/`.rodata`/`.data`, **never whole objects** (the object
  records its own source path, so a scratch-built candidate always differs — that mistake returned 0 free of 3,634 units
  and read like a finding). Every unit is negative-controlled by compiling it UNCHANGED first; a unit whose control
  fails is reported as a harness failure, not a result. `--apply` writes only what THIS run judged identical.
  Result on 2026-09-10: **3,439 units / 16,759 declarations repaired, fleet 218/218 unchanged.**
- `tools/readability_progress.py --snapshot "<label>" | --check` — the Gen3 series beside `docs/levers.md`, rendered to
  `docs/readability.md` from `docs/readability-progress.tsv`. Counts lying declarations (split `()` / `(void)`, and how
  many sit in a pinned body) and raw cast dereferences against struct member reads (the struct debt). Dated rows carry
  their commit; generated, never typed (R75).

**The oracle and the scorer:**
- `tools/delever_oracle.py --snapshot-baseline` — copies `build/**/*.o` into `.run/P36/delever/baseline/`, and
  `baseline_path()` makes every score read the snapshot when it holds the object. **This is what lets the R22 fleet gate
  and the agents run at the same time:** `make clean` deletes `build/`, which every score compares against, and without
  the snapshot a gate would make each live `--try` compare against a missing baseline and report nonsense in the agent's
  own voice. Refresh after each green `check-all`. Proven by moving an object aside: the score is unchanged.
- `delever_search.score_file` tags its scratch object per FUNCTION (`score_<alias>_<fn>`). It used to be a constant tag,
  keyed by the FILE — nine agents sharing one TU wrote and read one object, and two reported it independently.
- `delever.propagate` inherits the exemplar's lever allowance, DERIVED from the count of surviving `// !FAKE:` markers in
  its own banked text, and refuses a sibling whose remap would carry more.
- `delever.protos_outside_definition` — R14 refuses a function the TU declares anywhere but at its definition, because
  the bank is BODY-ONLY and a prototype rewrite cannot be banked. The engine also names an **OUT-OF-BODY** verdict when a
  score-0 candidate edited outside the definition.

**Reading the compiler, repaired after four agents asked for it:**
- `tools/alloc_table.py <tag> <fn> <dump_root>` — every pseudo with refs, live length, block, conflicts, copy
  preferences and `allocno_compare`'s priority, **with its coverage asserted against the `.greg` order line** (a named
  gap and a non-zero exit, never a confident subset). It used to print only callee-saved holders and returned an EMPTY
  table to two agents. Note the `.greg` dump carries the INPUTS to global allocation, not the final assignment, so a
  global allocno's hard register prints as `-`; that is the dump's shape, not a gap.
- `tools/cc1_dumps_tu.sh <wd> <tag>` — now passes `-I<the TU's own directory>` (it silently preprocessed to 44 lines and
  exited 0 on any TU with relative includes), adds `-dR`, and REFUSES a preprocess under 200 lines. It globs
  `$wd/*/t.c`, so `$wd/shared` must be symlinked to `src/shared` for TUs including `../shared/engine_prelude.h`.
- **Two cracks this session were arithmetic on that table, not searches:** one moved a priority 6524 past 6666, another
  shortened a live length from 44 to 43. A third predicted an allocation order from it before compiling and was right.

**The agent packs** (`tools/delever_pack.py --build`, ~2 min, no tree writes): each pack now also carries
`neighbours.txt` — the target's OWN header comment in full, the comment headers of the three matched functions either
side, and every `@class:`/`@stuck:`/`@crack:` note in the TU — and `best_body.c`, the text of the best candidate the
engine reached. Both came from agents: one closed on its first try after reading a sibling's header, and one lost hours
because the pack had reduced its own function's eight-point English header to two tagged lines. **A `@stuck:` note is a
CLAIM, not a fact — two were refuted on bytes on 2026-09-10.**

### §P36 S103 — 2026-09-10: two generators, the method file, and `verbatim_check` in the local chain

- **Generators R22 and R23** (rows in the §P36 S102 generator table above): R22 `merge_walked_pointers` (agent c2) and
  R23 `split_reused_locals` (agents c1/c8, one name per value — a pseudo that dies more than once is not a local-alloc
  candidate, `local-alloc.c:472`). R23 reads declarations from the WHOLE-BODY mask because `decl_run_end` masks one line
  at a time and ends the declaration run at a multi-line comment (it returned a run of 0 lines on `func_80135168`; R3's
  init-split shares that limitation). Known-true checks: R22's candidate from c2's start text IS its closing body (score 0);
  R23's joint split scores exactly what c1 and c8 measured for that move alone (12, 26).
- **`.run/P36/agents/METHOD_S103.md`** — the method every agent brief cites (after `PROMPT.md`, taking precedence): count
  first, the whole-function dump, the emitters of a missing instruction with the S103 additions (the walked-pointer merge,
  the `u16` width move for a surviving copy, the implicit handler argument), the allocation arithmetic, joint edits, the
  refusals. Grown at every landing.
- **The agent lane runs at most FIVE agents at once** (Drew, 2026-09-10). Fable 5.1 may be out of credits: an agent that
  dies with HTTP 429 on its first step is relaunched on Opus (R40 — the harness, not the function).
- **`tools/verbatim_check.py --strict` is now in `make tools-health`** (it ran only in CI: a DECOMPILE-NOW row converted by
  T4 batch tus10 kept CI red while every local chain was green). `--update` now keeps the manifest's row order and writes
  UTF-8 (it used to re-sort every row and escape every `§`/`—`, a 588-line diff for one removed row); its output was
  proven byte-identical to a hand-made one-row removal.
- **`tools/delever_pack.py` writes `related.txt`** — the LEVER-FREE bodies anywhere in the same overlay (its `.c` files and
  the shared headers they include) that share a `func_`/`D_` symbol with the target, ranked by how many, the top six in
  full. Three S103 agents found their answer in exactly such a body by hand (c2: the sibling walking the same list; c4:
  a sibling under a stale `@stuck:`; c10: `func_80135888` in a different file). Known-true: for `func_80135A4C` the top
  hit is `func_80135888`. ~2 s per pack.
- **`tools/cc1_dumps_tu.sh <TU.c | rtu work dir> <tag>`** — S103: also dumps `.cse2` (`-dt`) and `.jump2` (`-dJ`), accepts a
  `.c` FILE directly (an agent's spliced TU), and puts `-Isrc/shared` on the cpp line so `#include "../shared/…"` resolves from
  a copied TU (every scratch copy failed CPP-EMPTY and six agents wrote their own `dump.sh`). Smoke: a copy of
  `ov_SC04_011_jr_8013C98C.c` preprocesses to 7,168 lines, cpp.err empty, every dump written.
- **`tools/argcheck.py` reads K&R definitions** (`f(a, b) s16 a; u8 *b; {`): 505 functions are defined that way and 95 had no
  other readable definition, so R19, R25, `decl_repair` and the readability census were blind to them. The params string
  carries the DEFAULT-PROMOTED types (char/short → int), so a cast built from it matches the definition. Definitions read:
  15,626 → 15,721. Found by R25's known-true check (its first callee was absent).
- **`delever_search --try` is parallel-safe per call** (S103): its scratch directory and object tag carry the process id and
  are removed afterwards; `--keep` keeps them and prints the candidate object's path. Four simultaneous tries of one function
  score correctly (three agents had written private parallel scorers because same-function tries collided).
- **`tools/localalloc_sim.py <.lreg> <fn> <uid>`** (agent c26's simulator, promoted): local-alloc's per-block ranking
  (`qty_compare_1`) and the register each quantity gets, printed beside the dump's own assignment — validated 0 mismatches
  over 150 block simulations on four functions. Use it for a register permutation inside one block; `alloc_table.py` shows
  only global allocation and misled two agents.
- **`tools/delever_regen.py --families R22 R23 [-j 10] [--exclude FN …] [--label L]`** (read-only) then
  **`--bank .run/P36/regen/<L>.tsv`** (the one writer) — re-runs NEW generator families over the whole residue. The
  residue's NO-MATCH attempts predate every family harvested since, and nothing re-tried them; an engine re-sweep writes the
  tree and spends its budget on the old families first. Starting texts: the lever-free body and the engine's best text;
  scorer: `delever_search --try --body`; one worker per class (the scorer's scratch dir is per function). Run it after
  EVERY harvest that adds or widens a family, excluding the functions agents hold. First run (S103, R22+R23): see the log.
  **S104:** workers are forked PROCESSES after `sites_by_body()` and (with R19) `real_signatures()` are warm — on threads an
  all-families pass sat on the GIL for five minutes with zero compiles (R18 emits 1,000+ texts for one body; R19's table is
  ~29 s once). Each judged class is appended to **`.run/P36/regen/<L>.jsonl` as it lands** — the agent lane draws only
  classes the pass has judged and not closed. An ALL-families pass (`--families R2 … R26`, `-j 26`) costs ~1.8 s per `--try`
  and 100–370 candidates per head class; it closed an R12 class in its first minute, so re-running the old families on a
  moved tree is not redundant. **S104 (e22):** a third start text — a pack's lever-free `body.c` (an agent's near-miss); the sweep had only seen the free body, and the families finish some agent bodies in one pass. **Measured caveat (S104):** its first pass reported 14 MATCH of 27, and ALL 14 were classes whose agents had already closed them (the pass started from finished-but-unbanked bodies) or PARKED bodies — 0 new banks. Bank an agent-start TSV only after filtering rows to the live residue and out of the park list.
- **`delever_search.lever_free_body` refuses a strip that unbalances block comments (S104, R43)** — a lever line that OPENS a `/* …` comment continuing onto the next line was deleted whole, leaving the comment's tail as code; the start text never compiled and every sweep read the class as UNSCORED. Known-true: e24's pre-bank func_80180E24 now refuses; negative control over the whole residue: 709 ok, 16 other refusals, 7 comment refusals — each checked to be a real `/* …` lever line.
- **`tools/alloc_table.py` prints the INTEGER priority (S104)** — `global.c:594-603` stores it in a `register int` (truncated) and breaks ties by allocno number (`:607`); equal integers are flagged `TIE`. The float column hid e12/e14's closes (245.6 vs 245.2). Known-true: e14's `func_8017BEBC` lever-free dumps show the two `&g.sz` pseudos at 245 TIE.
- **`delever_pack.related_bodies` for main (S104):** main's units are `src/800*.c`, not `src/main/` — the search now falls back to the target TU's directory; every main pack's `related.txt` had been empty (e3: the answers were same-TU siblings sharing a global). Known-true: `func_80036FB0`'s pack now lists 7 bodies sharing `D_8006AEE8`/`D_80078F10`.
- **Marked ordinary-C fakes (S104, Drew's ruling (a)):** a `// !FAKE:` on a `do { … } while (0)` line or a `!FAKE:
  do-while|dead-init` marker is a KEPT fake (sotn-decomp's STYLE.md rule), not an orphan and not a lever —
  `lever_census` counts it apart ("marked ordinary-C fakes … NOT levers") and `--scrub` leaves it. Generator R7's do-while
  spelling now carries `// !FAKE: do-while — a LOOP-note scheduling barrier (sched.c:2058-2074; P36 R7)`.
- **Generators R28–R34 (`tools/delever.py`, S104 — each harvested from a T7 landing, each run against that agent's own start
  text before shipping):** **R28 `merge_pinned_twins`** (d12: locals the TREE pins to one register are one variable — reads
  the real TU; reproduces d12's 63 for the merges alone), **R29 `fold_store_temps`** (d15: a temp reused for several values
  each stored once → direct stores and `LV |= K`; reproduces d15's single-move 4), **R31 `shift_operand_casts`** (d13:
  `(s16)v >> N` at ONE shift; known-true 0), **R32 `compound_assignments`** (d5: `v = E; … L = L + v;` → `L += E;`, d8:
  `v = F + 1; … F = v;` → `(F)++;` — the use count is scoped to the variable's own declaration; both known-true 0), **R33
  `else_arm_assignments`** (d1: `x = A; if (C) x = B;` → an if/else with the non-simple value in the ELSE arm, the relational
  inverted or `!(C)`; known-true 0), **R34 `merge_disjoint_locals`** (d12/d14/d19: two same-type locals with disjoint textual
  spans merged — a single pair never closed those three alone (13 / 5 / 63): it is a MOVE for the engine's composition, not a
  one-shot closer). The new generators mask the WHOLE text (`sc.mask_text(text).split("\n")`): a per-line mask leaves a block
  comment's inner lines visible (R32's first known-true run counted a mention inside a comment). `delever_regen --families
  R28 …` feeds R28 the real TU like R27. **Then (S104, from d22/d24/d25):** **R23 accepts a `case K:` / `default:` label as a
  statement boundary** (it had refused d22's `t` after `case 2:`; known-true `split t into 2` → 0); **R35 `drop_param_copies`**
  (`T x = argN;` never reassigned → `argN` used; d24's start 36 → 23 — its close was joint); **R36 `merge_set_chains`** (`x = A;
  [≤2 unrelated lines] x += B;` → one assignment; d25's frame-only residual; known-true 0). **R31 widened** (d39: an all-shifts `(s16)` candidate — its two sites closed only together; known-true 0), **R35 widened** (d38: a CAST copy `T *p = (T *)a1;` becomes `((T *)a1)` at each use; known-true 0), `named_definitions` indexes `func_X_body(` asm-label definitions (two bank lists failed to resolve them); **R38 `shift_to_division`** (e7: `if (v < 0) v += 2^k-1; v = v >> k;` — gcc's own expansion — written `v = v / 2^k;` or merged into the preceding `v = (E) / 2^k;`; on e7's start text alone 6 → 6/7: e7's close was joint with a width move, so R38 is a composition move; 7 residue bodies carry the shape), **R39 `duplicate_join_statement`** (e12/e14: the simple statement after an if/else join copied into both arms to split an integer-truncated `allocno_compare` tie — cross-jump re-merges the copies; known-true 0 on e14's func_8017BEBC and func_8017CAD4; needs the `} else {` line shape — e12's func_8017E35C produced no candidate; widened S104: the first 1–3 simple statements after the join, blank lines skipped — e24's func_80180E24 store pair closes at ×2), **R40 `return_preincrement`** (e2/e16: `return i + 1;` → `return ++i;`, zero bytes, more refs; known-true 0 on both), **R41 `swap_if_else_arms`** (e16: `if (C) {A} else {B}` → `if (!C) {B} else {A}`, one site at a time — the arm order decides reorg's delay-slot steal; known-true 0), **R42 `move_statement_far`** (e19: one simple statement moved 2–6 simple statements down within its block — R9 only swaps neighbours; on e19's func_8018230C start text alone best 8: its close also inlined a temp and dropped an inner block, so R42 is a composition move), **R43 `sign_test_to_mask`** (e24/e26: `if (E < 0)` whose arms set/clear bit 31 → `if ((u32)(E) & 0x80000000)`, plus the variant with never-used pad arrays dropped; alone 9 / 4 on the two start texts — both closes also deleted temps: a composition move), **R37 `return_constants`** (d27: a result local `r = 0; if (A) r = (B); return r;` → `if (A && B) return 1; return 0;` or the nested form — jump1's store-flag on the hard `$v0`; known-true 0 both spellings). **(S105) R44 `counter_derived_pointer`** (e21/f2: a pointer initialised before a counted loop and stepped `p += K` inside it — its own biv, never eliminated while a bare `p[0]` is read (`loop.c:4196`, `:6022`) — re-derived as `p = (T *)(BASE) + i * K;` at the loop top for each up-counter `i` of that block (`(i - C)` when it starts at C; a second `&SYM[c + i * K]` spelling for an uncast symbol base); refuses a down-counter, a second assignment, `&p`; known-true: alone 0 on e21's func_80037EA0 start text (from 33) and f2's measured 18 on func_80038838's loop 2; composed with R22 it reaches f2's 0). **R22 extended + a blind spot fixed (S105):** two pointers derived from ONE base expression at two offsets (`a1 = (u8 *)arg0 + 0x1B` beside `a3 = … + 0x1A`) merge like `q = p + K` (f2's loop 1, alone 3); and R22/R44's `&p` refusal had matched the `&&` operator (`… != 0 && p[0]`) since S103 — every body testing its pointer with `&&` was silently never offered R22 (fixed to `(?<!&)&(?!&)`; the S105 regen re-runs R22). **(S105 f5) R45 `derived_pointer_store`** (`s0[K] = E;` with `s0 = &SYM` known to cse → `lui $at; sw E,K($at)` because cse pass 1 folds `(plus s0 K)` to the constant first, `find_best_addr` `cse.c:2622-2740`/`:2653`; the pointer the function already passes to a call, `&s0[K]`, is declared, born BEFORE the store, stored through and passed — per slot and ALL; known-true: alone 0 on f5's func_8018F944 (from 4), ALL 0 on func_8018FEA0 (from 16)) and **R46 `set_once_chain`** (1–3 consecutive `v OP= E;` lines followed by `DST = v;` → `DST = ((v OP1 E1) OP2 E2);` — a multi-set temp loses sched1's birthing boost `sched.c:2468-2546` and its chain is emitted at the block top; refused when `v` is read after the store before its next plain assignment; per chain and ALL; known-true: ALL 0 on func_8018FA34 (from 6), the singles 2 / 4 = the agent's numbers; the INVERSE of METHOD step 18's multi-set trick — the `.sched` priority column decides the direction). **R22, two more blind spots fixed (S105 f7):** the merge tried only the LITERAL base of `q = E + c1` (`prim`, which never steps) and stopped — it now tries every pointer local initialised from the same base at another offset and takes the first that steps in lockstep (`fp = prim + 0x2E` onto `pp = prim + 0xC`); and `*(u16 *)fp = v;` was read as an ASSIGNMENT to `fp` (the `)` before the name), refusing the merge — the assigns scan of R22/R44 excludes a `)` before the name. Known-true: R22 alone reproduces f7's close of func_8017FD14 (37 → 0). Every R22 refusal before S105 is suspect: the `s105_r22b` regen re-judged the residue. **The strip keeps a block-comment tail (S105):** a lever line whose trailing `/* …` comment closes on a LATER line is no longer deleted whole (`whole_line_of` refuses it; the statement alone goes, and `tail_marker_edits` removes the `// !FAKE:` rung B had appended INSIDE that open comment) — six residue classes had been UNSTRIPPABLE (`a stripped lever line opened or closed a block comment`); all six strip with 0 orphan markers now.
- **Generator R27 `named_ports` (`tools/delever.py`, S104; `delever_regen --families R27`)** — the SAME function already
  lever-free in another binary, ported. Donors: every definition of the name in `src/` (`named_definitions()`, one `git
  grep`, cached) with no `register`/`__asm__`/`!FAKE`, nearest line count first, ≤ 6 distinct texts. Symbol renaming by
  **`reloc_map`**: the two ORIGINAL objects' relocation sequences for the function (`objdump -dr`, the snapshot object; a
  shared header's first includer's) paired in order — a donor symbol mapping to two targets refuses the map; fallbacks pair
  the `extern` lists by position or the first occurrences, or rename nothing. **`_carry_decls`** copies the donor TU's
  file-scope `extern` for every renamed data symbol the target TU (minus the replaced body) never declares — d6's
  COMPILE-ERROR. Signature variants: the donor's, the donor's with the TARGET's return type (d2's `s32` vs the TU's later
  `extern void`), the target's whole header. Measured at birth: 511 of 1,010 residue classes (636 bodies) have a donor; a
  24-class probe closed 4 at the first candidate, all by `reloc`. Known limits: a same-name donor that is a DIFFERENT
  function scores high (the ranking is by line count only); a pair whose REL addends differ cannot match (MIPS REL: the
  addend is in the instruction, the object comparison sees the symbol name).

### §P37 S108 — 2026-09-12: the declaration layer run to its floor (Phase 37 T4)

- **`tools/restruct.py`** (rung D) — `defs_visible` indexes the shared headers each SIBLING TU includes (a binary's own shared bodies were
  "external") and, as a third level, a callee's fleet-unique signature when no member/main/resident TU defines it; `unit_call_counts` (the K&R
  arity read from the TU AND its included bodies; a definition head is `) {` or a K&R head); `--unalias`: a data-typed declaration of the real
  name (`extern s32 f;` / `extern char f[];`) becomes the prototype, a header-side arity error marks the INCLUDING TUs, escalation counts
  attempts; `--callee F --body FILE` gained **`--with REL=FILE`** (a caller-body edit inside the same judged unit, repeatable), **`--map-data`**
  (with `--all-defs`: the body's `D_` symbols renamed to each copy's own by order of first appearance; a count mismatch REFUSES), header-borne
  definitions excluded from `--all-defs` (a variant is another function); **`--redraw VERDICT[:cause-substring]`** (`DECL-NONE:visible`).
  `--unalias` runs under `--apply` (the S107 checkpoint's line lacked it). Selftest 54/54.
- **`tools/argcheck.py`** — every definition per name kept (`_ALL`), `resolve_definition(name, tu)`: one fleet-wide signature → it; else the
  declaring TU's own binary's; else main/resident; else `cross_binary=True`; rows carry `kr_marked` (the `// K&R:` marker read from the RAW
  line); `DEF` allows leading blanks (indented file-scope definitions); the K&R loop feeds `_ALL` regardless of `out`.
- **`tools/type_census.py` / `tools/readability_progress.py`** — lying declarations exclude `kr_marked` and `cross_binary` rows, which are
  published APART (`kr_sites`/`kr_callees`, `cross_binary`/`cross_callees`; two new TSV columns, read by name).
- **`tools/delever_oracle.py --snapshot-baseline`** — REFUSES an empty or shrunken `build/` before writing (it had stamped "HEAD, 0 objects").
- **`tools/restruct_cycle.sh`** — skips the fleet run when `git status src` is clean after a batch (the previous R22 stands).
- One-off drivers under `.run/P37/restruct/` (ignored; every command line is in the phase log): `sig_cycle.sh` (the parked signature bodies:
  oracle refresh → `--callee … --body` → R22 → log → commit; a `--tu` fallback when copies differ), `strip_banners.py` (the §8b banner comments).
- **Gotchas:** after `kill -INT` on a judge WAIT for its exit (`ps`) before `--restore`; `pgrep -f`/`pkill -f` never with a literal your own
  command line contains (`restruct_cycl[e]`).
