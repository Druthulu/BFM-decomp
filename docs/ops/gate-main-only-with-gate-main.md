# gate-main-only-with-gate-main

**`main` is gated ONLY by `tools/gate_main.py`** — baseline assert → substitute the whole slate →
`make extract` → `make build` → compare SHA1, with a bisect when the batch fails. `parallel_gate` now
REFUSES `binary == 'main'` in code, so this cannot be re-learned by accident.

**Why:** main's `make extract` runs the EXE-only `psyq_integrate` + `ld_interleave` steps, which
REWRITE the linker script. `gate_stage` (and therefore `parallel_gate`, whose worker *is*
`gate_stage`) builds incrementally, so it re-runs that on an already-rewritten `.ld`. S58 recorded the
false-DIFF direction (105 competent main drafts thrown away). S71 hit the **false-PASS** direction,
which is worse: `parallel_gate` reported "11 banked" on main, the merge was committed, and R22 came
back 212/213 — the tree did not compile from clean, and once the declarations were reconciled it was
still not byte-identical. All 11 re-gated individually: **11 of 11 REJECTED**.

**How to apply:**
* Any main draft → `gate_main.py`. Run `--assert-baseline` first; it is cheap and it separates "my
  draft is wrong" from "the tree was already red".
* **Count banks from the SOURCE** (the `INCLUDE_ASM` stub is gone), never from the tool's slate.
  `gate_main` printed "BANKED 5 of 6" when 4 had applied — `len(good)` is *what we decided to keep*,
  not *what was substituted*. Fixed, but the principle is general: this was the 4th tool in one
  session reporting a derived number as a measured one.
* A draft that **contains its own `INCLUDE_ASM`** is a silent no-op — substituting it restores the
  stub, the build is trivially byte-identical, and it counts as a bank. `gate_main` refuses these now.
* **A tool that wraps another tool inherits its refusals.** Every constraint documented on
  `gate_stage` binds `parallel_gate`, `harvest_verify`, and anything else that shells it — encode it
  as a refusal in the WRAPPER, not a paragraph in the callee.

**CORRECTED S72 (2026-09-02) — that "11 PROVEN gate-rejects" line was WRONG; NONE of them is a body
reject.** The S71 re-gate ran through an ad-hoc script (`.run/S71_main_bisect.py`), not `gate_main.py`,
so the decl pre-check never ran — and **all 11 are switch functions**. main had carried exactly ONE
`.rodata` carve since Phase 7, so a drafted switch DOUBLE-EMITS its jump table, the image grows
(+28/+52/+76/+84 measured) and ~332 symbols shift. Extending the carve to the contiguous span
`0x80072A38-0x80072C70` banked `func_8001A114`, `func_8001AAD0`, `func_8001AF34` **byte-identical in
14 s**; the other 8 sit in uncarved spans B/C and need `src/800.c` split. Cookbook §426/§427.

**S75 CORRECTION (2026-09-02) — THAT VERDICT LINE HAD A CLASS THAT COULD NOT FIRE.**
`main_diff_locate.classify()` gained a `TABLE REJECT` case in S72 precisely because BODY/PLUMBING had
mislabelled a table failure. On main it was **unreachable by construction**: it summed bytes whose
object string contains `(.rodata)`, but main's `section_order` is `[.rodata, .text, .data, .bss]` — its
rodata sits BELOW `.text` and its jump tables live in **`.data`** objects
(`build/asm/data/63C4C.data.o(.data)`). It also demanded PURITY (`ro == outside`), so a few bytes of
perturbed code dropped the verdict through to PLUMBING anyway.

Cost: **`SaveLoadRoutine` (1,165 ins — the largest open function in the project, 9.2% of all remaining
work, carried as the §434 WALL) has a BYTE-IDENTICAL body.** Gated alone, twice, the tool said
"PLUMBING REJECT … route to fix_arity_callers -> cast_self_callers"; the chain was run twice and fixed
nothing, because the real split is **3,787 of 3,989 bytes (94.9%) in `.data` jump tables vs 202 (5.1%)
in `.text`**, and the built image is **4 bytes SHORTER than retail** (§446's first diagnostic).
It is a CARVE — and it sits in `src/800_b.c`, i.e. **span B, exactly where the S72 note above predicted
the remaining 8 would sit.** Fixed: table bytes counted in `(.data)` OR `(.rodata)`, and the test is
DOMINANCE (>=60%) not purity, naming which part is carve and which is declaration. NC: 5 of 6
pre-existing verdict shapes unchanged. Cookbook §447.

**THE LAW, and it generalizes past this tool: a verdict class that CANNOT FIRE is worse than one that
does not exist** — it converts "I don't know" into confident, specific, wrong advice that then
consumes sessions. When a verdict names a subsystem, check that subsystem owns the MAJORITY OF THE
BYTES before acting on it.

**ALSO S75: gate main with `--no-propagate`.** `gate_stage`'s tail runs
`dedup_propagate --auto-from <bin>`, which sweeps the WHOLE binary rather than the function just
banked; a binary with an unswept pile stalls the gate 30+ minutes (`ov_SC01_005` held 557). Drew's
decision 2026-09-02: leave the ~12,000-copy hygiene backlog (all already matched, orthogonal to
completion %) and gate `--no-propagate` by default. See [[dedup-backlog-leave-it]].

**A main gate now says WHERE, not just that.** `gate_main` preserves the red image + map under
`.run/gate_main_fail/` BEFORE the R40 baseline control rebuilds over them (that ordering bug is why
nobody could ever localize a main failure), then prints **BODY REJECT / PLUMBING REJECT / MIXED** via
`tools/main_diff_locate.py`. **Read that line before recording any main verdict.**

Related: [[standalone-match-is-not-bankable]] · [[verify-blast-radius-not-just-defect]] ·
[[silently-narrowed-tool-scope]] · [[check-against-a-known-true-case]] (cookbook §414)
