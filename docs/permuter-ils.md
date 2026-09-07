# The permuter in BFM-decomp, the relocation-masked scorer, the ILS warm restart, and the upstream PR

> **Status (P33 E5, 2026-09-07).** The recipe this project ran decomp-permuter with, written for two readers: a
> BFM maintainer (what `tools/permuter/` does and why) and the upstream project (the PR that carries the scorer and a
> USAGE note on restarts, `tools/permuter/upstream/0001-reloc-masked-scorer.patch`, plus the issue text for the
> symbol-wildcard defect). The permuter itself is the pinned submodule `tools/decomp-permuter` (commit `b44b0622`,
> 2024-12-30); the PR was written against upstream `main` at `41bd0bfc` (2026-09-05, 39 commits later) and lives on the
> branch `reloc-masked-scorer` of the fork `Druthulu/decomp-permuter`.

## 1. Why the stock scorer could not reach zero here

decomp-permuter scores a candidate by diffing symbolised `objdump` rows against the target's and charging penalties
(register 5, reordering 60, insertion/deletion 100, …). On MIPS it recognises "this field is a relocation, ignore the
name" only when the field contains a `.` (`src/scorer.py`, `field_matches_any_symbol`: `return "." in field`), true of
`.text+0x34`-style references, false of every symbol this project's splitter names (`func_80012345`, `D_80054C10`).
Every relocation slot that differed by *name* was therefore a register penalty the search could never reduce, and the
score floated on a floor: `func_80176D94` sat at base ≈225 / best ≈210 / never 0 while a byte-exact answer existed
(Phase 24 T2). A random walk with no gradient to zero diverges.

## 2. The relocation-masked scorer (what the PR carries)

Compare the two objects' instruction **words**, masking exactly the fields the linker fills in, read from the
**target's** relocation records, never guessed from a `lui` pattern, and require the relocation operands to agree there:

| Target's relocation | Mask | Plus |
|---|---|---|
| `R_MIPS_26` (a `j`/`jal` to a symbol) | keep the 6-bit opcode, mask the 26-bit target | same symbol+addend |
| `HI16`/`LO16`/`PC16`/`LITERAL`/`GPREL16`/`GOT16`/`CALL16` | keep opcode + rs + rt, mask the low 16 bits | same symbol+addend |
| `R_MIPS_26` against `.text` (a `j` to a label inside the function) | as above | the target compared **relative to the function start**, two candidates that jump to different labels differ |
| none | the full 32-bit word | registers, constants and branch offsets all count |

`score = mismatching positions + |length difference|`, one unit per instruction; **0 exactly when the candidate links
to the same bytes**. The in-tree form is [`tools/masked_diff.py`](../tools/masked_diff.py) (shared with `match_one` and
`rtu_match`, so the closeness an agent reads is the closeness the permuter optimises) rebound over the pinned permuter
by [`tools/masked_scorer.py`](../tools/masked_scorer.py) + [`tools/permuter/run_masked.py`](../tools/permuter/run_masked.py)
without editing the submodule. Four of its rules were bought with byte evidence and are in the PR too:

- **`-drz`, not `-dr`.** objdump's default nop-elision under-counted GTE-heavy functions (`func_80132784` read as 384
  instructions instead of 400); `-z` keeps the runs.
- **The 26-bit field is masked only when the assembler left it to the linker.** A short-circuit on the *opcode* once
  dropped every `j .L…` to a local label from the comparison, and which label a `j` takes is the difference between
  `break` and `return` (`ov_SC03_118:func_801825EC`, one word). The internal-`j` target is compared relative to the
  function start (P31 T1).
- **Keep the opcode even at a masked slot.** A mask of 0 at a `j`/`jal` position swallowed whatever the other side held
  (a `j` vs a `bne` scored 0 one way and 1 the other, P31 S65).
- **`R_MIPS_PC16` is masked like `HI16`** (Phase 26-A): the object holds an unresolved placeholder in the branch
  displacement, so a full-word compare could never succeed; masking it cured 151 of 155 false non-zeros across 60,740
  stubs and introduced none.

**Upstream PR (PR-1).** `tools/permuter/upstream/0001-reloc-masked-scorer.patch` holds the two commits on the branch
`reloc-masked-scorer` (regenerable: clone upstream, `git am` the patch; it applies onto `41bd0bfc`). The first adds `src/reloc_scorer.py` (`RelocMaskedScorer`, a `Scorer` subclass
so `Permuter`/`Candidate` are untouched), `--score-mode {mnemonic,reloc-masked}` and a `score_mode` settings key
(default `mnemonic` = unchanged behaviour), a USAGE/README/example-settings note, a refusal with `-J` (remote evaluators
use the default scorer), and `test/test_reloc_scorer.py`, ten tests on an embedded `objdump -drz` listing of a small
gcc 2.7.2 object (link-time fields masked; symbol, register, opcode, branch and length differences each counted;
internal jump targets compared; the scorer end to end through `objdump_command`), needing no cross toolchain. The
second is a USAGE note on restarting from the best candidate (the generic half of §4). Verified at the commit: `black --check` clean on the touched files; `mypy` at upstream's own baseline (5 pre-existing
errors, none added); the suite's only failure is upstream's `test_perm`, which needs `mips-linux-gnu-gcc`; and the
real permuter run end to end with the mode on compiled objects: base == target → base score 0 → `--stop-on-zero`;
and **the floor, reproduced in miniature**, a 5-instruction function with two `xor` operands swapped in the base:
reloc-masked base score 4 (the debug diff names the four operand differences) and **score 0 at iteration 256**, under
40 s with `-j4`; the default scorer read the same base as **3,585** and sat at 3,420 twenty iterations later
(`.run/P33/permuter-e2e/`, `settings.toml` `objdump_command = "mipsel-linux-gnu-objdump -drz -m mips:4300"`).

**Submitted (2026-09-07):** the PR is https://github.com/simonlindholm/decomp-permuter/pull/213 (from the fork's
`reloc-masked-scorer` branch) and the symbol-regex issue below is https://github.com/simonlindholm/decomp-permuter/issues/214.

## 3. The issue for upstream (filed as #214): a configurable symbol regex

Title: *MIPS scorer: `field_matches_any_symbol` recognises a relocation only when the field contains "."*

> On MIPS, `Scorer.score`'s `field_matches_any_symbol` returns `"." in field` (`src/scorer.py`, the two branches
> for mips and arm32). Splitters such as splat name symbols `func_80012345` / `D_80054C10`, no dot, so a relocation
> slot whose symbol differs between target and candidate is charged as a register difference (`PENALTY_REGALLOC`) that
> no permutation can remove. The score then floats on a floor above zero even when a byte-exact candidate exists; we
> measured base ≈225 / best ≈210 / never 0 on a 225-instruction function that later matched.
>
> Proposal: a `symbol_regex` setting (and `--symbol-regex`), defaulting to the current behaviour (`\.`), that projects
> can set to their symbol shape (e.g. `^(func|D|jtbl)_[0-9A-Fa-f]{8}`), used wherever `field_matches_any_symbol`
> decides "this field is a symbol". Independent of, and complementary to, the relocation-masked scoring mode in PR-1 -
> that mode sidesteps the question by reading relocation records instead of symbol text, but the default scorer
> deserves the fix too.

## 4. The ILS warm restart (a usage recipe, ours to keep)

A cold permuter run on a pinned seed plateaus at the base score over ~10k iterations. **Warm-restarting `base.c` from
the best byte-waypoint each cycle**, with a fresh seed, descends where cold stalls: `func_80148094` 72 → 36 over ~8
restarts, the big drops coming from fresh restarts, not from continuing a plateaued run (Phase 24 T7 §G). The wrapper
is [`tools/permuter_ils.py`](../tools/permuter_ils.py) over [`tools/p16_permute.py`](../tools/p16_permute.py):

```bash
python3 tools/permuter_ils.py func_80148094 --draft .run/t7b/close/func_80148094.c \
    --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077 --klass REGALLOC --cycles 10 --secs 180 --j 12
```

Its guards, each bought with a session (P31 S79/S80, cookbook §493–§495): (1) **register pins are hidden** before the
permuter parses the seed, `register … __asm__("$16")` is carried in a base64 pragma so `cc1` still binds the register
while pycparser sees plain C, and a waypoint's `source.c` (which the permuter decodes back) is **re-hidden** before the
next cycle, or every cycle after the first is a parser refusal that reads as "unchanged" (`func_80020DA4`: 1 real cycle
+ 7 silent no-ops); (2) a **refused cycle aborts the run** with the reason, not-judged is not a verdict (R61); (3) the
seed's header comment is stripped before `cpp -P` (a `*/`-less comment made the permuter no-op silently on every
commented giant draft); (4) `stdout` is flushed, eight parallel runs once showed empty logs for twenty minutes (R55);
(5) **a score-0 winner is a candidate, not a bank**: intermediate waypoints can be semantically divergent (the permuter
rewrites stores for byte proximity), so the winner goes through `rtu_match` and the whole-binary gate.

The measured limits, so the tool is used where it pays: the permuter's problem on this project was **targeting, not a
missing transform** (decision log 2026-07-21), pointed at the right seed with the right scorer it closed
register-allocation and scheduling residuals; it never closed a structural residual (a wrong loop shape, a missing
idiom), which is the reader's job (`residual_class`, cookbook §66d: alternate a random search with a byte-verified idiom
and let the residual class decide whose turn it is). And a masked "1" is not a closeness until its diff is read (R63).

## 5. Related

- Cookbook §3 (the harness), §42/§45 (the F-band cracks where pins beat the permuter), §66d–§66d-5 (the permuter⇄reader
  loop), §137 (REGALLOC-PERM as a two-compile arithmetic problem), §493–§495 (the S80 repairs).
- `docs/hindsight-study.md` §7, mine the permuter's failures, not just its wins (the offline-automatic endgame).
- `docs/how-to-ai-decomp/07-compiler-source.md`, when the residual is the compiler's, read the pass instead.
