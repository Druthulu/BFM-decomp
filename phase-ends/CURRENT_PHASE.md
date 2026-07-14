# CURRENT PHASE — Phase 26: The Family-Endgame (finish the decomp)

> **Status:** ACTIVE · plan approved by Drew (gate 1) 2026-07-11 · Generation Gen2 (18th phase of the arc)
> **Opening brief:** `docs/family-endgame-megaplan.md` (Phase-25 handoff). **Fable5 window closes ~2026-07-13.**
> **Recovery note:** a fresh session resumes from the ▶ CURRENT TASK below (P3 — autonomous between gates). Read the plan context here + the megaplan; per-task log at the bottom is the crash-recovery trail.

## The plan in one paragraph

The Phase-25 h_seq reframe: the "unique tail" is really per-location families — crack ONE exemplar, template ×~120 siblings through the whole-binary byte-gate. Planning-session verification (2026-07-11) reproduced the survey from the sigs: **663 tail families; substantial (nins≥80) = 186 families / 1.85M ins** (megaplan's "986" was a miscount). Design-stage discovery (byte-verified on specifics, V0 re-verifies — R14): **the tail is ~90% a reloc-tracker blind spot** — `norm_stream`/`reloc_targets` drop the pending `lui`-hi on any R-type write, but gcc-2.7.2's indexed-global idiom (`lui; addu $idx; lw lo($at)`) preserves it, so every `D_x[i]` access made its function "fleet-unique" and broke remap. Substantial-tail classes: PURE-same-addr 62 fams/1.55M ins · PURE-cross-addr 103/0.10M · IMM 8/0.10M. **Free win: 63 families / 0.31M ins have a MATCHED exemplar** and siblings that failed earlier sweeps only from the tracker bug → zero-crack banks once the ~40-LOC fix lands (= the validation corpus). Also found: `remap()` sequential substitution corrupts chained renames → must become single-pass simultaneous. Immediate substitution shrinks to an escalation tier (diff-driven, 3 tiers; probe only ambiguous values). **Owner decisions:** carried Fable5 queue (5 giants) deferred to END of phase (low priority); milestone = structural completion.

## Task checklist (effort per R7 · one commit per completed task, Drew pushes — R6)

- [x] **Task 0 — Bootstrap** `[xHigh]` — this file + harness task list (R28). *(completes with this commit)*
- [x] **Task 1 — Remap core: extended reloc tracker + single-pass substitution** `[xHigh]` — `family_remap.py`: hi propagates through add/addu index adds; `symbol_map`/`remap` gained backward-compatible `to_addr=None` (cross-address) + `imm_map` hook; single-pass simultaneous substitution + self-rename. norm_stream/h_norm UNTOUCHED. Discovery → cookbook §40b (R30) + decision-log (R31). **V0 PASS** (`.run/v0_reloc.py`): 22/22 regression (`func_80141100` NEW==OLD), 15/15 fix (`func_801407F4` vs splat .s, recovers `D_80187B88/90/B0`), cross-addr symbol_map clean. **V1 PASS** (`.run/v1_regression.py`): 160 real h_norm pairs, 96 SAME, **0 lost**, differences are strict indexed-reloc improvements. *(committed)*
- [x] **Task 2 — `tools/family_hseq.py` + committed manifest** `[xHigh]` — full-frontier survey; shared word-diff classifier added to `family_remap.py` (`stream_words`/`reloc_indices`/`reg_fields`/`classify_member` — PURE/IMM/STRUCT, register-drift aware). → `.run/family_hseq.json` + `docs/family-hseq.md`. **VERIFIED:** fleet 74.8/58.2/30.3 (= PhaseEnd_25 & progress.py to the decimal); tail cross-check **663 families / 186 substantial / 1.847M ins** (exact); classification vs Plan-agent table **PURE-same 62, IMM 8 exact, PURE-cross 114≈103**; 890×134/562×134 PURE per-location + 952×113 #addr21 IMM confirmed; full frontier = 581 substantial families / 3.22M templatable ins, **345 matched-sibling PURE/IMM families / 1.14M ins = the V2/V3 zero-crack corpus**. *(committed)*
- [x] **Task 3 — Imm engine (T2a Tier 1) + cross-address delta (T2b)** `[xHigh]` — `family_remap.imm_value`/`imm_map_tier1`/`remap_hseq`: diff-driven Tier-1 value-replace (asm-side ambiguity guard defers ambiguous values; C-literal swap preserving sign/hex-case) + T2b self-rename via the Task-1 `to_addr`. **Tier 2 (probe) DEFERRED** — build-if-needed per Task-5 measurement (byte-gate arbitrates; only ~8 low-weight IMM families). **VERIFIED** (`.run/v3_imm.py`, match_one reloc-masked): **0 DIFF** on every compilable pair — 3 IMM + 2 cross-address MATCH; 4 remap-fails were correctly-deferred asm-ambiguous values; 45 compile-fail(isolation) → whole-TU gate in Task 5. *(committed)*
- [x] **Task 4 — `family_sweep --hseq` mode** `[xHigh]` — additive `hseq_sweep()` (h_norm path byte-untouched): consumes `family_hseq.json`, templates matched-exemplar members via `remap_hseq` (cross-address + imm), stages `.run/sweep/<ov>/func_<TO_ADDR>.c` grouped by (overlay,split), gates via `harvest_verify` (unique per-group verified-out — fixes a latent multi-split overwrite). Member pre-filter = `remap_hseq` refusal (STRUCT/unresolved). **Static pin guard** (`__asm__("$N"` → skip family; §42e — the ×1-only pinned cracks that cc1-crash sibling TUs). `--band`/`--min-members`/`--stage-only`/`--only`. **VERIFIED:** substantial → 29 families, 1507 clean members staged / 267 groups, 1643 correctly skipped as pinned (16/29 families pinned incl. the decision-log-named `func_8016DF5C`/`8013D9B0`/`80133AB0`); h_norm path intact; drafts byte-correct by construction (V3), type-using → whole-TU gate (Task 5). *(committed)*
- [x] **Task 5 — Zero-crack validation harvest (substantial band) — GO/NO-GO = GO** `[xHigh]` — ran the real byte-gate on the 29 substantial matched-exemplar families. **Tooling fix discovered + applied (Task-5's "measure then fix"):** `remap_hseq.gather_externs` carries file-scope externs for body-referenced symbols (`extract_unit` only grabbed adjacent ones) — the decl class that depressed the first run. **Result: 532 members banked** (byte-gated); per-family: **3 tracker-miss PURE families (`0x8015d5e8`/`0x8015f118`/`0x801407f4`) bank 100% ×133 = 399 byte-perfect** (the free win), 1 cross-addr family 50%; **9 zero-bank families are type-using (`Work8016`/`Prim`/…) → §41 reconcile follow-on (Task 8)**, 16 families pinned → Task 7. **VERDICT: the h_seq machinery is 100% correct on clean families — GO.** decision-log 2026-07-11 (R31). **R22 clean-fleet 136/136 GREEN**; metrics 30.3→**30.9% distinct** (+375 fns) / 58.2→**58.5% instr**. *(committed)*
- [x] **Task 6 — Step-A triage of the 119 draftable substantial exemplars** `[Ultracode]` — Workflow (`.run/wf_triage_full.js`, 119 agents / 0 err / 5.3M tok): per-family m2c draft (+§8 jtbl) → `match_one` closeness → class + §31/§45 lever + seed (`.run/phase26-seeds/`). **119 triaged → cheap 29 (325k ins, 23 closeness-0 isolation-MATCH) / permuter 29 (341k) / fable5 61 (1.71M).** Curriculum → `docs/phase26-triage.md`. **⚠ Banking caveat (verified): the 23 closeness-0 seeds gate 0/23 into ov077** — genuine function matches but carry standalone types + Ghidra sigs conflicting with the TU (§41 def-side wall: `redefinition of struct Obj` / `conflicting types`); banking needs the Task-8 `--reconcile`/`canon_sig_reconcile` pass. *(committed)*
- [ ] **Task 7 — Family-core crack waves (the Fable5 window)** `[launch at Max — R27; agents model:fable, parallel-isolated, distill-between]` — biggest byte-weight first (890/562/536/493…); §45-templated prompts (read `.greg`/`.lreg` first; Lever-A merged-accumulator audit; 1-death in-out-asm; /s; gdb-on-cc1, `tools/reference/gcc-2.7.2/`); PIN-FREE (×134); `harvest_verify` arbitrates; distill each crack → cookbook §46+ (R30); cheap-Opus applies banked idioms between waves; cheap/permuter lists run in parallel `[UC]`. ~375k tok/crack guide; documented wall + levers = valid outcome (P9).
- [ ] **Task 8 — Mechanical harvest waves** `[Ultracode; continues post-window]` — cracked exemplars → template ×members → gate → bank; h_norm draftable/matched-free retries with the new tracker (5.9 MB bucket); F-jumptable 4 (§8); M-linkwall 1; link-undef second pass. Batched commits; **R22 clean-fleet before each commit batch** (never while agents need `asm/`).
- [ ] **Task 9 — Mid-band + residue measurement** `[xHigh]` — <80-ins families (0.68M ins) through the engine; measure h_seq-miss → GO/NO-GO fuzzy pass (build only if ROI; else Phase 27).
- [ ] **Task 10 — Carried Fable5 queue (END of phase — Drew's call)** `[Fable5 if window remains, else permuter/Opus + banked levers]` — 801670E4 (diff-23), 80178004 (close-7), 801412A8 (close-29), 8016CBC0 (153/209), 8014D820 (LCS-226); specs `.run/giants/*.opus.md` + `.run/t7b/close/`. Crack ×134 or wall-document; post-window walls → Phase 27, accepted.
- [ ] **Task 11 — Step-D residue map** `[xHigh]` — true singletons (~0.27M ins) + 5 behemoths → Phase-27 input doc. NO execution.
- [ ] **Task 12 — PhaseEnd** `[Max — Tier 1; R27 prompt]` — P7 walk, milestone demo, gate 2, `PhaseEnd_Phase26.md`, worklog → `logs/Phase26.md` (R19), in-file recap (R25), decision-log current (R31).

## ⛳ SESSION-8 CLOSE (2026-07-14) — READ THIS FIRST

### ⚠ DREW'S DIRECTIVE (2026-07-14, binding): the TOOLING-INTEGRITY AUDIT comes BEFORE any further matching work
> *"I feel like we should do T14 now, before the rest of the work. but not in this phase."*

# 📄 THE AUDIT PHASE'S INPUT DOCUMENT IS **`docs/tooling-audit.md`** — READ IT FIRST, IT IS THE PLAN
> **40 MEASURED findings** (6 auditor agents + 6 adversarial skeptics, 1.2M tokens) with file:line evidence and
> candidate/parsed/skip counts per scanner — plus the METHOD, the priority order, the 7 bugs already fixed
> (do not redo), and the 63 tools not yet audited with the filter for which of them matter.
> **Almost nothing in it is fixed. It is diagnosis.** Everything below is a summary OF that document.

**The FIRST decision of the fresh session is a Tier-1 phase-boundary call for Drew** (do not decide it alone):
the audit is not part of Phase 26, and it must precede the remaining matching work — so either
**(a)** close Phase 26 with a PhaseEnd now (it has achieved a great deal, but its stated milestone — structural
completion — is NOT met, so this is an early close by owner decision), and open the audit as **Phase 27**; or
**(b)** run the audit as an INSERTED phase (the Phase-3.5 precedent: a half-phase spike) and return to Phase 26
afterwards. Present both; let Drew pick. Then plan the audit phase in **plan mode, Max** (Tier-1).

### WHY (the case for doing it first — this is the session's most important finding)
**Seven silent-skip tool bugs in one session**, and they were not typos — they are a *structural* blind spot:
> a scanner extracts N items from a corpus, the true count is M > N, and **nobody ever compared N to M**.
The whole-binary byte-gate is a perfect CORRECTNESS oracle (it never once accepted a wrong match) but it is
**blind by construction to work never attempted** — it has been green since Phase 5, when 0% was decompiled,
because `INCLUDE_ASM` pastes the ORIGINAL asm. A green byte-gate is compatible with ANY decomp %.
One hole (`SIG_IN_BODY_RE`, 10% of the callee oracle) made **nine byte-exact functions look like an intrinsic
compiler wall**. That is the cost of not auditing: not wrong answers — *invisible work*, and walls that aren't.

**AUDIT SCOPE SO FAR: 19 of 82 tools (23%), chosen by risk. NOT comprehensive.** The unaudited set includes the
most dangerous ones:
- **`dedup_integrate.py`** — the FAIL-CLOSED byte-honesty validator. A silent skip there prints
  *"1813 validated, 0 failed"* — **a false green from a gate.** Audit this FIRST.
- **`jtbl_family_bank.py`** — three bugs found in it BY HAND this session; never formally audited.
- **`family_hseq.py` / `wave_targets.py` / `exemplar_miner.py`** — target SELECTION. A hole here makes work
  **invisible to planning** — the worst kind, because you never know to look.
- **`masked_diff.py` / `match_one.py`** — the closeness oracle every agent trusts.
- (`harvest_verify.py` is the byte-gate but DERIVES from the build, so a parse hole makes it *conservative,
  not wrong* — the good kind of tool. See R33 below.)

**Do NOT "audit all 82"** — many are dead LLM-tier scripts. The filter is: **does it PARSE something, and does it
GATE or SELECT work?** (~15 tools.) And per R33, for each one ask the better question first: *why is this tool
re-deriving something the build already guarantees?*

### 🔑 THE COOKBOOK LESSON THAT SUPERSEDES THE ONE WE STARTED WITH (R33 candidate)
> **A metric DERIVED FROM A PROVEN INVARIANT beats a metric that RE-PARSES THE WORLD.**
`progress.py` has two metrics answering the same question. `weighted_metrics()` derives from the invariant —
*"not wrapped in INCLUDE_ASM ⇒ byte-exact, because the build is byte-identical"* — and **inherits the byte-gate's
correctness for free**. `classify()` re-derives the same fact by parsing C, and inherited a bug instead (it read
a K&R definition as a forward declaration). Same question, two tools; **the one that refused to re-derive was the
one that was right.**

### 🔴 AND AN HONEST SELF-CORRECTION (P9/R14 — do not repeat it)
I told Drew our headline numbers had been under-reporting by ~190k instructions. **That was WRONG.**
`weighted_metrics()` never calls `classify()`, so it was structurally immune; **the published 65.6% / 44.9% were
CORRECT ALL ALONG** — only the secondary REAL/fn-count report was wrong. I had verified the DEFECT against the
bytes (R14) and still got the conclusion wrong because **I did not verify its BLAST RADIUS**. What caught it was a
**null result** (+376 instructions, not +190,000) against a strong prediction — trivially easy to wave off as noise.
*"This tool is broken" and "this number is wrong" are different claims needing different evidence.*

### RULE CANDIDATES FOR PHASEEND (P10 — Drew ratifies)
- **R32 — Coverage assertion.** A tool that scans the corpus must assert its own coverage (found vs. an
  over-approximating candidate set) and **fail loud on unparsed input**. A silent skip is a DEFECT, not a no-op.
  *(Drew: "agreed", 2026-07-14.)*
- **R33 — Derive, don't re-derive.** Where a proven invariant answers a question, derive the answer from it rather
  than re-parsing the source. Before adding a coverage assertion to a scanner, first ask whether the scanner
  should exist at all.

---

## ▶ SESSION-8 RESULTS (2026-07-13/14)

### 📊 SESSION-8 SCOREBOARD
**Fleet: instr-weighted 63.0 → 66.5% · distinct-code 39.1 → 46.8% · fn-count 82.61%** (all DEFENSIBLE — see the
self-correction below). **FINAL R22: `make clean` + extract-all + check-all → 136/136 BYTE-IDENTICAL, 0 coverage defects.**
**136/136 byte-identical after every single bank** (R22). dedup 1813/0. 0 NON_MATCHING (G4). ~25 commits.

**13 CORES CRACKED**, incl. the four heaviest functions in the game. The 12-agent Ultracode wave: **11/12 MATCH**
first pass, every one adversarially verified by a skeptic (re-run `match_one` + the §8a jump-table check).

| Core | size × reach | how it fell | banked |
|---|---|---|---|
| `func_8017BEBC` | 952 × 113 | **Fable5** + §47 live-length slider | ×1 |
| `func_80178D40` | 890 × 134 | **cheap-Opus** reading loop.c/jump.c/cse.c (§46) | **×134** |
| `func_8015AE2C` | 562 × 134 | §8d decl-scope fix unblocked the sweep | **×134** |
| `func_8017A4AC` | 536 × 134 | §49 **LUID dial** (sched.c) | blocked — see below |
| `func_8015A3C8` | 493 × 134 | §48-A1 sink-the-init | **×132** |
| `func_8015444C` · `func_8016AB6C` · `func_8013FFD8` · `func_801380E0` | | wave | **×134 / ×134 / ×129 / ×134** |
| `func_8013F350` · `func_80131340` · `func_8015B950` · `func_8015C32C` · `func_80159C84` | | wave (MATCH) | **blocked on plumbing** |
| `func_80135EB0` | 289 × 134 | 21→**6**, WALLED with a named mechanism (§50-F) | honest defer |

### 🧰 THE TOOLKIT CROSSED A LINE — three ZERO-BYTE DIALS now cover the three passes that make every residual
Each emits nothing; each steers a tie; each has a **diagnostic signature a cheap agent can recognise on sight**.
That is why 9/12 fell first-pass without Fable5. *Fable5 DISCOVERS a class; everyone else APPLIES it.*
| signature | pass | dial |
|---|---|---|
| registers rotated | `global.c` allocno priority | **§47** live-length slider · **§48-A** pricing dials |
| two insns swapped, **SAME registers** | `sched.c` `rank_for_schedule` LUID tiebreak | **§49** LUID dial |
| structure right, instruction COUNT wrong | loop peel / cross-jump | **§46** · **§48-D** |
New this session: **§46** (4 loop-structure levers) · **§47** (the slider) · **§48** (+A4 sink-the-consumer-call) ·
**§49** (the LUID dial) · **§50** (refinements that **BOUND** §47/§48 — read §50-B before using A1/A4: the
"cross_jump refunds the bytes" claim is FALSE for a 1-insn tail reached by two jumps, `jump.c:1993` minimum=2).

### THE HEADLINE — the three heaviest cores in the game are cracked, and the wave scaled
| Core | size × reach | how | state |
|---|---|---|---|
| `func_80178D40` | 890 × 134 (477 KB) | **cheap-Opus** reading loop.c/jump.c/cse.c → §46 | **BANKED ×134** |
| `func_8017BEBC` | 952 × 113 (430 KB) | **Fable5** + the §47 live-length slider | **BANKED ×1** (×113 sweep = IMM-class, Task 8) |
| `func_8015AE2C` | 562 × 134 (301 KB) | §8d decl-scope fix unblocked the sweep | **BANKED ×134** |
| **12-core Ultracode wave** | 2.29 MB | §31/§46/§47 in the prompt + adversarial verify | **9/12 MATCH**, 3 near (close=2/2/21) |

**Metrics: instr-weighted 63.0 → 64.7% · distinct-code 39.1 → 42.8% · fn-count 82.43%.** R22 136/136 after
every bank. dedup 1813/0. 0 NON_MATCHING. ~15 commits.

### THE LESSON OF THE SESSION — every wall was OUR TOOLING, and the R17 triage rule called it every time
**Six silent-skip bugs found and fixed**, THREE of them the same brace-placement class:
1. `scope_data_externs` (NEW, §8d) — carried DATA externs were emitted at FILE scope, establishing a global
   the sibling TU never had → `conflicting types`. **Demote to block scope when the TU has no file-scope decl
   above.** Byte-neutral, never worse than raw. Unblocked the ×133 jr sweeps.
2. `extract_unit` — `not ln.rstrip().endswith(";")` missed m2c's `...);   /* extern */` form → a DECLARATION
   was read as a DEFINITION and the brace-scan swallowed the NEXT function's body. **15 of 35** substantial
   exemplars were phantom "matches"; 3 more templated garbage.
3. `scope_data_externs._body_open_brace` — matched only an own-line `{` → silently no-op'd on every ANSI draft.
4. **`gen_harvest_targets.SIG_IN_BODY_RE`** — required `)\s*{`, but an own-line brace has a `\` before it, so
   **186 of 1801 (10%) of engine_core.h's shared signatures were MISSING from the canonical-callee oracle**
   that `cast_call_sites`/`sig_unify` resolve against. This is why the wave's byte-exact cores would not bank:
   the draft kept its guessed sig, hit `conflicting types`, and the "recovery" pass reported nothing to fix.
   **Fixing it turned `func_8015A3C8` from 28-conflicts-unbankable into BANKED BYTE-IDENTICAL with zero hand
   edits.** (`commit:0561`)
5. `jtbl_family_bank.revert()` didn't restore the splat config → an isolation's residue rode into a commit as
   a DUPLICATE code-subseg line (harmless to splat, so R22 stayed green) → the NEXT isolation walked the
   object twice → "segments out of order". Now reverts the config + `jr_isolate_all` FAILS LOUD on a
   non-ascending/duplicate subseg list.
6. `jr_isolate_all` emitted an EMPTY region 0 when the object's first item IS the first cut (cutting a
   non-leader out of an already-isolated region) → duplicate config line.
> **Standing rule (cookbook §40): a tool that silently no-ops on input it cannot parse is indistinguishable
> from a tool that had nothing to do. Prefer fail-loud on unparsed input, and regression-gate any change to a
> "proven" text scanner by snapshotting its output over the whole corpus before/after.**

### NEW TOOLING + KNOWLEDGE (all committed)
- `tools/scope_data_externs.py` (§8d) · `tools/bank_exemplar.py` (bank a cracked exemplar ×1 through the same
  stage ladder) · `jtbl_family_bank --raw` (template from the RAW crack — REQUIRED when the exemplar banked at
  the `reconciled` stage, since a reconciled body is TU-specific; byte-proven: D40 banked reconciled → sweep
  0/4 until `--raw`, then 132/132).
- **Cookbook §46** (four LOOP-STRUCTURE levers: the PEEL rule — a `break` must never land on the loop's own
  fall-through label; the surviving-copy EBB rule; the merged store; the non-replaceable giv).
  **§47** (the LIVE-LENGTH SLIDER: measure `pri = int(floor_log2(n)·n/L·10000)` in the `.lreg`/`.greg` dumps;
  a zero-byte `asm("")` between two existing volatile asms shifts L by +1 and splits an allocno tie — and the
  split direction is FORCED toward the target). **§48** (the allocno-PRICING dials: sink-the-init-into-the-arms;
  the local-alloc `$s0` occupant; per-case temps as a tie gate. The EBB rule generalized. The C type selects
  the addressing mode. The cross-jump RATCHET.)

### ▶ NEXT — IN ORDER (Drew's directive: the AUDIT comes first)

**0. [FIRST — Drew's call] The Tier-1 phase-boundary decision** (see the top of this file), then the
   **TOOLING-INTEGRITY AUDIT** in plan mode, Max.
   **▶ Plan it FROM `docs/tooling-audit.md`** — 40 measured findings, the method, the priority order, the
   already-fixed list, and the not-yet-audited list are all in there. Do not re-derive them.
   Order: **`dedup_integrate.py` FIRST** (a fail-closed validator that can print a FALSE GREEN) →
   `jtbl_family_bank` → the SELECTION tools (`family_hseq`/`wave_targets`/`exemplar_miner` — a hole there
   makes work invisible to *planning*) → `masked_diff`/`match_one` → the 40 findings by severity.
   **Apply R33 to each BEFORE R32:** *why is this tool re-deriving something the build already guarantees?*
   The best outcome is a **deleted scanner**, not a fixed regex.
   **Then re-test the walls diagnosed on top of the broken oracle** (the real prize): the def-side loose-typing
   wall (§20/§41), the 159 arity/narrow-param conflicts, the 3,098 type-heavy tail, the 9 zero-bank type-using
   families. Some of that "intrinsic wall" may have been lookup misses all along.

**1. [THEN — the cheapest matching work on the board] The CONSOLIDATED INTEGRATION FIX PASS.**
   **Nine byte-exact cracks; six cannot bank — for PLUMBING, not matching (~1.2 MB sitting behind it).**
   Four distinct fixes, all identified, one already built:
   - **`tools/reconcile_tu.py` — WRITTEN + VALIDATED, NOT YET WIRED IN.** Replaces `reconcile_decls`' oracle.
     That tool asks *"what does the FLEET call this symbol"*; the only question that matters is **"what can THIS
     TU SEE"** — 34.4% of fleet symbols carry ≥2 mutually incompatible spellings, so one fleet-wide answer is
     **provably wrong for some TU by construction** (and it returns ACTIVELY WRONG decls for 3,717 symbols).
     `reconcile_tu` reconstructs the TU's visible file-scope environment from BOTH §8c sources (col-0 decls AND
     `engine_core.h` macro-injected externs — 544 visible syms from 1801 macros) and parses the **fn-ptr forms
     `reconcile_decls` is structurally blind to**. Validated on `func_8017A4AC`: resolves `D_801DA75C` (fn-ptr),
     `D_80126B58` (struct), `D_801DA734` (ptr). **Wire into `bank_exemplar.py` + `jtbl_family_bank.py` as a
     stage, byte-gate it.** Unblocks `func_8017A4AC` (287 KB), `func_8013F350`, `func_80131340`.
   - **Strip scalar typedefs** from the draft before splicing (`match_one` does this via
     `masked_diff.SCALAR_TYPEDEF_RE`; the BANK path does not) → `redefinition of 's16'`. Unblocks `func_8015C32C`.
   - **`canon_sig_reconcile` is not K&R-aware** — raises `no definition found in draft`, so the def-side (§41)
     conflict never gets a recovery attempt. Unblocks `func_8015B950`.
   - **`func_80159C84`**: carve STILL non-contiguous after isolation (0xb09a4 / 0xb09c4) — a real edge case where
     a region ends up hosting two carves with an unmatched jtbl between them.
   ⚠ **`func_8013F350` is NOT a plumbing bug — it is a real class.** Its `D_8011511C` must be **struct**-typed to
   force `la`+offset (§48-C1): the type IS the code. The TU declares it `u16` at file scope, and **no cast fixes
   it** (the cast folds back to `lui/%lo`). It needs an EBB-separated pointer re-crack (§48-B) or a fleet decl
   migration.

**2. Re-run the 780 h_seq rejections against the REPAIRED callee oracle** (`commit:0561`) — large mechanical
   recovery expected for ~0 agent tokens.
**3. The next crack wave** — 32 unmatched heavy-jr ov077 cores remain (`.run/wave_targets.json`, ranked, with
   per-core asm subdirs). Plus **32 PINNED families (1.09 MB)** needing pin-free re-cracks — the toolkit is
   pin-free by construction now. Recipe = the 12-core wave: §31/§46/§47/§48/§49 in the prompt + an adversarial
   verifier + the mandatory §8a jump-table check.
**4. `func_8017BEBC`'s ×113 sweep** (IMM-class, scattered addrs → the immediate engine, not the PURE path).
**5. `func_80135EB0`** — the one documented wall (§50-F): needs a lever that injects a **reload-deleted no-op reg
   copy** inside `[lhu 4($a2) … sh %lo(D_801152AC)]`. That is the entire remaining delta.

---

## ▶ SESSION-8 (earlier) — the ×133 sweep blocker

**THE ×133 SWEEP BLOCKER IS FIXED. `func_8015AE2C` (562 ins) BANKED ×134 — 133/133 siblings, 0 failures.**
**R22 clean-fleet 136/136 GREEN** (from `make clean`, 534 changed src files). dedup-check 1813 validated / 0 failed.
**Metrics: instr-weighted 63.0 → 63.6% · distinct-code 39.1 → 40.5% (+256 unique fns / +79,957 ins) · fn-count 82.31%.**
One core × 133 siblings = **+0.6% instr-weighted for ~0 agent tokens.** Tree clean, all work committed.

### The fix — §8d, `tools/scope_data_externs.py` (the session-7 diagnosis was HALF RIGHT — R14)
Session 7 blamed `reconcile_decls`' fleet-majority oracle and planned to teach it a TU-visible one. Reproducing
one sibling by hand (rather than trusting the handoff) gave a sharper picture and a **smaller, safer fix**:
- **The isolated region builds `[ OK ] ` WITHOUT the body** → §8b isolation was never implicated. The templated
  body is the sole cause.
- `family_remap.gather_externs` prepends carried decls at **FILE scope**. `D_801812A4` is a fn-ptr dispatch table
  the sibling declares **four incompatible ways at BLOCK scope inside its own later functions**. The carried
  file-scope decl **establishes a global the TU never had** → every later block-scope `extern` must now agree
  with it → `conflicting types`. Byte-proven asymmetry:
  `BLOCK(int) → BLOCK(struct*) → FILE(void*)` **builds**; `FILE(void*) → BLOCK(int)` **errors**.
- It was the **ONLY** hard error in the build. All 27 carried *function* externs were fine raw —
  `cast_call_sites` was not needed at all (session 7 thought it was doing the heavy lifting).
- **FIX: demote, don't reconcile.** Emit a carried `D_` extern at **block scope inside the function body** when
  the TU has no file-scope decl of it above the insertion point. Byte-neutral (an `extern` emits no code; type +
  access opcodes unchanged), **never worse than raw** ⇒ needs no oracle, no type comparator, no fn-ptr parser.
  It also *restores fidelity* — the original declares these symbols at block scope in exactly this way.
  Wired as the `scoped` stage: **raw → scoped → recovered → reconciled** (and `scoped` is the base for the
  later recovery stages). Cookbook **§8d** + decision-log + SETUP row (R30/R31/R21).
- **`reconcile_decls` is the wrong instrument for this class, twice:** its oracle answers "what does the FLEET
  call this symbol" when the question is "what can THIS TU see"; and its `DATA_DECL_LINE_RE` **cannot parse**
  `extern void (*D_x[])(void *);`, so it silently skipped the very symbols that were failing. (This is the
  "reconcile fn-ptr-extern gap" logged 2026-07-12 — filed as a small separate lever, it *was* the blocker.)
- **The R17 triage rule (committed `commit:0550`) paid off immediately:** `conflicting types` = the compiler
  REFUSED TO COMPILE = a C front-end diagnostic = **our Python**. Reading `cse.c`/`global.c` would have taught
  nothing. ("Wrong BYTES" → read gcc; "won't COMPILE" → read our tooling.)
- **Diagnostics gotcha:** gcc-2.7.2 does **not** prefix errors with `error:` — grepping a build log for `error`
  finds only make's `Error 33`. Grep the diagnostic text (`conflicting types` / `undeclared` / `parse error`).

### NEXT (priority order — byte-weight first; top-20 jr cores = 4.12M of the 5.53M templatable bytes)
1. **`func_80178D40` (890 × 134 = 477K bytes — THE heaviest core).** Crack in hand at
   `.run/phase26-cracks/func_80178D40.c`, **close=39, ALL 39 inside ONE case body (0x5C)**; every other case is
   byte-exact. The 4 residuals are named in the file header (cross-jump merge of `D_801DAB2C = 3`; `$v0→$v1`
   copy; loop2 keeping old q in `$v1`; gcc **peeling loop3's first iteration** where the original doesn't —
   `loop.c`). All §31-map classes ⇒ **cheap-Opus + permuter, NO Fable5**. Exemplar = ov_SC01_077, PURE
   per-location ⇒ straight `jtbl_family_bank` sweep once closed.
2. **`func_8017BEBC` (952 × 113 = 430K bytes) — close=2. THE genuine R17/Fable5 target (R27: PROMPT DREW).**
   Two `addiu`s TRANSPOSED in the loop preheader; registers already correct. Allocation order and preheader
   emission order are **coupled** (both follow creation/LUID order) but the target needs them to DIFFER:
   allocation (sz0, sz2, sz1) with emission (sz0, sz1, sz2). Permuter cannot reach it (not statement-permutable;
   ran 25 min, no close). Agent localized it to `global.c`'s allocno-priority **TIE** and named the move: a §45-B
   **gdb-on-cc1 read of `allocno_live_length`** (the original's length quantization plausibly split the tie),
   then hunt a byte-neutral L-shifter that survives cse. Full spec: `.run/phase26-cracks/func_8017BEBC.md`.
   ⚠ **Exemplar is `ov_SC01_000` (NOT ov077), class IMM, addr_tag scattered** → its sweep runs from ov_SC01_000
   through the immediate engine, not the plain PURE template path.
3. **The rest of the 191 substantial jr cores** (5.53M templatable bytes). Next by weight: `func_8017A4AC`
   (536×134), `func_8015A3C8` (493×134), `func_8013F350` (490×134), `func_801380E0` (438×134) — all ov077 PURE
   per-location. Recipe = the session-7 five-step (unchanged) + the new `scoped` stage.
4. **Re-check for cracked-but-unswept jr cores** whose ×N sweeps never ran because of this blocker — use
   `family_remap.extract_unit` as the definition oracle, **not** a hand-rolled regex (mine false-matched
   `extern` lines — R14).

### Banking a heavy jr core — the FULL recipe (unchanged from session 7, + the `scoped` stage)
1. `jr_isolate_all --only <core>` (also cuts every already-banked jr in the same object — one `.rodata` carve
   per region). 2. `jtbl_carve --func <core>` (trims trailing `.align` pad — §8a-pad). 3. If an `engine_core.h`
   thunk calls the core with **zero args**, the def must be **K&R** and the thunk's extern must drop `(void)` →
   `()`. 4. Gate stages: **raw → scoped (§8d) → recovered (`cast_call_sites`+`reconcile_decls`) → reconciled**.
   5. Whole-binary gate → `jtbl_family_bank` ×N → R22 → commit. **Commit each family before sweeping the next**
   (the per-sibling revert restores from HEAD).

---

## ▶ SESSION-7 CHECKPOINT (2026-07-13, cont.) — superseded by SESSION-8 above

**Heavy-jr crack waves RUN (Drew approved top-3 + distill). 1 core BANKED, 2 cracks in hand. R22 136/136 GREEN,
tree clean, all work committed.** The §8b wall stayed broken throughout.

### The three Fable5 cracks (all PIN-FREE, all independently re-verified against the bytes — R14)
| Core | Size × reach | Result | State |
|---|---|---|---|
| `func_8015AE2C` | 562 × **134** | **MATCH 562/562** | **Exemplar BANKED** (`commit:0547`, `d19c9580`, R22 green). ×133 sweep **BLOCKED** — see below |
| `func_80178D40` | 890 × **134** | **close=39/890** — 851 exact; **all 39 in ONE case body (0x5C)** | crack at `.run/phase26-cracks/func_80178D40.c`; 4 named residuals in a 44-ins block, agent calls it permuter-tractable |
| `func_8017BEBC` | 952 × **113** | **close=2/952** — two `addiu` TRANSPOSED, same registers (pure emission order) | crack at `.run/phase26-cracks/func_8017BEBC.c`; **permuter ran 25 min, did NOT close it** |

### ⛔ THE ONE BLOCKER — the `func_8015AE2C` ×133 sweep (precisely diagnosed, NOT yet fixed)
The remapped sibling body's **DATA externs conflict with the sibling's §8b carried decl layer**
(`conflicting types for D_801812A4`; the layer's decl is the "previous declaration"). `reconcile_decls`
resolves against a **fleet-majority canonical oracle**, not against the TU's *actually-visible* decl, so it
picks a type that still conflicts. **Fix direction:** reconcile the body's externs against the TU's carried
layer (which is authoritative — it reproduces the original TU's decl environment), or drop body externs the
layer already provides and cast at use. `cast_call_sites` already fixes the *function*-callee half (27
callees); only the ~4 DATA symbols remain. Everything else in the sweep works (isolate → carve → remap →
gate). **Bank flow now has 3 stages: raw → recovered (per-sibling cast+reconcile) → reconciled.**

### Banking a heavy jr core — the FULL recipe (all byte-proven this session)
1. `jr_isolate_all --only <core>` — now **also cuts every already-banked jr in the same object** (a region may
   host at most ONE `.rodata` carve; an object's `.rodata` is a single contiguous section).
2. `jtbl_carve --func <core>` — now **trims trailing `.align` pad words** (§8a-pad).
3. If an `engine_core.h` thunk calls the core with **zero args**, the def must be **K&R/unprototyped** and the
   thunk's extern must drop `(void)` → `()` (byte-neutral fleet-wide; R22-verified for func_8015AE2C).
4. Recovery: `cast_call_sites` (callees) + `reconcile_decls` (data) against the **isolated region TU**.
5. Whole-binary gate → `jtbl_family_bank` ×N → R22 → commit.

### Six tool bugs found + fixed this session (each silently corrupts and each is committed)
`canon_sig_reconcile` void→s32 not byte-neutral (§41d) · `extract_unit` swallowing the §8b decl layer ·
`jtbl_family_bank` cross-address naming · `jtbl_carve.func_subseg` reading the stale asm tree ·
`jtbl_carve/revert` deleting the committed `overlays.mk` carve var · `jr_isolate_all` `--only` erasing the
banked set + carve-ownership read from a `.s` splat never emits for matched fns + **one region hosting two
carves** · `p16_permute` `hide_asm` eating GTE `#define`s (permuter silently no-op'd `0s` on ALL renderer
drafts) + hardcoded to one overlay.

### NEXT (in priority order) — with the R17 routing call (Drew asked, 2026-07-13)
> **Do NOT read the gcc-2.7.2 source for the sweep blocker.** R17 (read the compiler internals) is for
> **codegen** residuals — regalloc / scheduling / cross-jump / CSE — i.e. things no C change reaches. The
> sweep blocker is a **C FRONT-END diagnostic** (`conflicting types`: two incompatible file-scope decls of one
> identifier in one TU). gcc is correctly rejecting plain C89; the bug is in OUR Python (`reconcile_decls`
> picks a fleet-majority type instead of the type the TU can actually SEE). Reading `cse.c`/`loop.c`/`global.c`
> would tell you nothing. **Triage rule: "the compiler produced the wrong BYTES" → R17. "the compiler refused
> to COMPILE" → our tooling.**

1. **Unblock the ×133 sweep** (above) → banks 562×133 ≈ 75K templatable ins. Highest ROI, well-diagnosed.
   **Python fix, NOT a gcc read.**
2. **`func_8017BEBC` close=2** (×113) — **THIS is where the gcc-source read belongs.** The permuter failed
   (25 min, no close). The agent localized it to `global.c`'s allocno-priority TIE and named the exact move: a
   §45-B **gdb-on-cc1 read of `allocno_live_length`** (the original's length quantization plausibly split the
   tie). Two instructions from a 107K-ins bank — the best R17 target in the queue.
3. **`func_80178D40` close=39** (×134) — all 39 in case 0x5C; agent named 4 concrete residuals (incl. gcc
   peeling a loop iteration the original doesn't → likely `loop.c`). Cheap-Opus/permuter first, R17 if it walls.
4. Then the rest of the 191 heavy jr cores. **R27: prompt Drew before any further Fable5.**

---

## ▶ SESSION-6 CHECKPOINT (2026-07-13) — superseded by SESSION-7 above

**THE §8b SCOPING WALL IS BROKEN. Heavy-jr harvest is UNBLOCKED. Effort: Max.**
Full 54-jr isolate-all on ov_SC01_077 → `d19c9580` **byte-identical**; **R22 clean-fleet 136/136**.
All tools committed. Baseline clean (no config/src changes).

**What session 6 delivered (committed):**
1. **Declaration-environment reconstruction** (`overlay_src_split.py` + `jr_isolate_all.py`) — the fix. Session-5's
   "gcc block-scope-extern TU-persistence" diagnosis was **WRONG (R14)**: `DEFINE_func_*` macros expand at FILE
   scope, so their leading externs are genuine file-scope decls that merely live in `engine_core.h` — invisible to
   any col-0 text scan. **Four** decl sources must be carried forward, and the byte-gate found three of them:
   (1) col-0 decls · (2) macro leading externs (1,377 macros / 3,929 lines / 1,462 syms) → `D_80126B3E undeclared`
   · (3) **a definition is itself a declaration** for everything below it → `func_8012B2CC undeclared`
   · (4) file-local typedefs used by a carried proto → `parse error before '*'` (`Vec3s`).
   **Rejected the approved "global symbol→type map + shadow set" design** — it would hoist loose-typing block-scope
   shadows to file scope and *create* the conflict the shadow-set then dodges. Faithful forward-carry is
   conflict-free by construction (see cookbook §8c + decision-log 2026-07-13).
2. **LAZY per-core isolation wired** (`jtbl_family_bank`): `jtbl_carve` NON-CONTIGUOUS fail-loud →
   `jr_isolate_all --only <core>` → re-extract → re-carve. Proven on **`func_80178D40` (890×134, the heaviest
   core)**: carve blocked → isolated (byte-neutral `d19c9580`) → carve lands in its own subseg.
3. **Two latent bugs fixed** (both would have corrupted the heavy sweeps): `jtbl_carve.func_subseg` derived the
   owning subseg from the **asm tree**, which `make extract` never prunes → after an isolation it returned the
   STALE owner and silently re-created the collision (now derived from the config); and the sweep's `revert()`
   **deleted** the shared `overlays.mk` carve var unconditionally → would have destroyed a *committed* carve (all
   134 overlays have one) on any failed sibling (now restored to its committed value). `jtbl_family_bank` also now
   refuses to start on a dirty `config/`+`src/` — **commit each family before sweeping the next.**

**DE-RISK COMPLETE (Drew's call, session 6): `func_80182268` cracked + banked ×3 (the whole family) through the
LAZY path — the composition is proven end-to-end.** Cracked first try (31-ins jr: shared-tail fallthrough where
jtbl cases 3+7 enter case 4's tail, + the `(s8)(*(u16*)(p+0x70) >> 8)` sign-extend idiom). Its carve collided
with the committed `func_801734BC` carve → lazy isolation fired → carve into its own subseg → whole-binary gate
`d19c9580`. Siblings `ov_SC02_000`/`ov_SC02_003` (**cross-address**, @0x8017FCB0) banked via `jtbl_family_bank`.
**The de-risk paid for itself — it exposed 3 more bugs that would each have silently capped the heavy sweeps:**
1. **`canon_sig_reconcile`'s `void`→`s32` return promotion is NOT byte-neutral** (cookbook **§41d**, R14): for a
   void body with no `return` it costs ONE instruction. It turned a perfect 31-ins MATCH into 32 → the extra word
   made the isolated object's `.text` 4 B long → **every data symbol shifted +4** (~271k differing bytes).
   `match_one` said MATCH; only the whole-binary gate caught it. **Fix (generalizes §19): every recovery pass is a
   FALLBACK — `jtbl_family_bank` now gates RAW first, reconciled only on failure.**
2. **`extract_unit` swallowed the §8b carried decl layer** (it walks backward absorbing extern/comment lines, and
   the layer sits above a region's first item) → the template dragged ~140 unrelated externs into every sibling →
   gate-fail. Fixed with an explicit end-marker + a stop in `extract_unit` (also guards the Phase-17 canon layer).
3. **`jtbl_family_bank` used the EXEMPLAR's name for the sibling's carve/isolate/stub** → cross-address families
   never resolved. Now derived from `to_addr`. (The first two banked jr families were same-address, so it hid.)

**Backlogged:** `func_801549F8` (31-ins jr, **reach ×134** — the other cheap ×134 target) is a genuine **§31
loop-IV / strength-reduction** residual: the target does NOT strength-reduce (recomputes `script+(i<<2)` each
iteration), but plain `arr[i]` with constant per-branch increments makes gcc build a pointer GIV. A variable-stride
`step` defeats biv recognition and gives the correct address shape (**17/31**, seed at
`.run/backlog_drafts/func_801549F8.seed.c`) but gcc then keeps `step` in a register instead of folding K into each
branch's `addiu`. Needs the C shape that keeps CONSTANT per-branch increments yet fails the giv worth-while test
(`loop.md` L1). Permuter/Fable5 class — do NOT hand-grind it.

**NEXT (R27 BOUNDARY — prompt Drew before launching):** Task 7 = the **heavy-jr core crack waves**. The 191 jr
family cores / 5.53M templatable ins are now bankable. Per core: Fable5 crack (**whole-binary gate — NOT plain
rtu_match**, jr false-match risk §8a) → lazy isolate → `jtbl_carve` → `jtbl_family_bank` ×134 → parallel R22 →
commit. Targets by byte-weight: `func_80178D40` (890×134 = 477K ins, isolation already proven), `func_8017BEBC`
(952×113), `func_8015AE2C` (562×134), `func_8017A4AC` (536), `func_8015A3C8` (493). Fable5 window now **7/19**.
Optional cheap de-risk first: the 45 small jr families (~129K ins, no Fable5) to exercise the full lazy bank
end-to-end (isolate→carve→remap→reconcile→**gate**) on a cheap target — its composition is proven in parts but the
end-to-end bank with a cracked body gates at the first real core. Ghidra MCP NOT needed (matching uses cached asm).

---

## ▶ SESSION-5 CHECKPOINT (2026-07-13) — superseded by SESSION-6 above

**Stage-2 isolation build — parser DONE + single-cut PROVEN; full isolate-all hit the gcc-2.7.2 scoping wall. Effort: Max. Drew's decision (2026-07-13, Fable5 window extended to 7/19 so no time pressure): BUILD declaration-completion + apply isolation LAZILY per-core (not upfront-×134 — avoids the ~7,200-file cost; same tool, isolate only cores that crack). Tools committed this session.**

Built this session (baseline reverted + intact — ov_SC01_077 rebuilds `d19c9580`; only the 2 new tools are untracked, NOT yet committed):
1. **`tools/overlay_src_split.py`** — overlay-`.c`-aware partition (header = includes + Phase-17 canonical-sig layer; per-address items = preamble + body; robust def/decl/K&R/`DEFINE_func`/`SETTER`/`RETCONST` classification). **VALIDATED fleet-wide: 404/404 overlay `.c`, 341,902 items — round-trip exact / 0 unresolved / 0 non-monotonic.** This is solid, reusable, commit-worthy.
2. **`tools/jr_isolate_all.py`** — multi-cut resegment (config split at every jr boundary, source repartition + INCLUDE_ASM path repoint, banked-jr carve repoint via config + `overlays.mk --order`, -O0-object skip, ambient file-scope decl carry). **SINGLE-cut isolation BYTE-IDENTICAL** (func_8013FFD8 in `main` → clean `make build` = `d19c9580`, R22). Full 54-jr isolation on the dense `_after` object hit the wall.

**THE WALL (byte-verified, decision-log 2026-07-13):** mechanical TU-splitting breaks gcc-2.7.2's **block-scope-extern TU-persistence** — `func_801734BC` uses `D_80126B3E`, declared `extern s16` ONLY inside `DEFINE_func` macros in `engine_core.h`; the original `_after.c` compiles because an earlier macro's block-scope `extern` persists to file scope for the whole TU. Splitting separates the core from that macro → `undeclared`. (7 distinct C-scoping edge cases surfaced + fixed incrementally; this last one is the deep one — col-0 ambient-carry can't reach macro-injected decls.)

**THE FIX TO BUILD (Drew-approved, fresh session):** **declaration-completion** — build a global symbol→type map from `engine_core.h` macro `extern`s (the `DEFINE_func`/`SETTER`/`RETCONST` bodies) + all overlay col-0 decls; then for each isolated region emit a file-scope `extern <type> <sym>;` for every `D_`/`func_` symbol the region USES, EXCLUDING the type-shadowed set (symbols with inconsistent decls across the codebase, e.g. `D_80115118` = `unsigned short` vs struct `S115118` — kept block-scope in bodies). This makes every region self-contained regardless of where the original declared the symbol (col-0, block-scope body, or macro). Est. ~40–60 LOC on the proven `overlay_src_split.py`; the whole-binary byte-gate (G3/P9/R22) arbitrates. Wire it into `jr_isolate_all._render_region` REPLACING the col-0-only ambient carry (which can't reach macro-injected decls).

**NEXT (fresh session):** (1) build declaration-completion (above); (2) re-prove full isolate-all byte-identical on ov_SC01_077; (3) switch isolation to LAZY per-core — integrate a single-core isolate into the bank flow (`jtbl_family_bank`), isolating a heavy jr core only when banking it (fewer files than upfront-×134); (4) then the heavy-jr-core crack waves — Fable5 (window now to 7/19) → §8 carve + template ×134 → R22. Committed tools this session: `tools/overlay_src_split.py`, `tools/jr_isolate_all.py`. Ghidra MCP NOT needed (matching uses cached asm). **R27 boundary: prompt Drew to re-confirm effort/Fable5 before the crack waves.**

---

## ▶ SESSION-4 CHECKPOINT (2026-07-12 later) — superseded by SESSION-5 above

**Stage 1 in progress — multi-jtbl `--order` BUILT + proven cross-subseg at fleet scale.** Effort: Max (this session, Tier-1 tooling build).

### What session 4 delivered so far (committed + R22 136/136)
1. **`ld_interleave.py --order`** — address-ordered N-piece multi-jtbl sandwich (text → [data|.rodata carves, address-ordered] → bss). Legacy `--front/--tail` path byte-untouched (main + the 133 single-carve siblings unaffected). Empty code-object sections parked byte-neutrally with .text.
2. **`jtbl_carve.py` rewritten additive/regenerate-from-config** — parses the current tail data-region + existing `.rodata` carves, adds the new fn's jtbl (splitting its containing data piece), re-emits the address-ordered pieces + the `--order` interleave arg. Same-subseg collision → fails loud (→ isolation). Idempotent.
3. **`jtbl_family_bank.py` fix** — `bank()` now `make extract`s BEFORE the carve (so the sibling asm matches the reverted committed config; the old error-string retry was fragile). Revert-on-carve-fail.
4. **Family-1 banked: `func_801734BC` (34-ins PURE jr, in ov_SC01_077_after) ×134** — matched in ov077 (shared-tail switch: `case N: t=-N; break; default: goto after;`), banked 133/133 siblings, **R22 136/136 clean-fleet byte-identical**. This is a CROSS-subseg multi-jtbl (func_8012ACE0 in `_a` + func_801734BC in `_after`) — the checkpoint's primary Stage-1 goal, proven fleet-wide.

### The same-subseg cases — TWO flavors (both surfaced this session; the de-risk paid off)
Two matched jr-fns in ONE code object emit their jtbls CONTIGUOUS (gcc source order). So:
- **(a) CONTIGUOUS jtbls (adjacent in the island) → MERGE.** `jtbl_carve` now merges adjacent same-subseg carves into one spanning `.rodata` piece (+ a **bound-fix**: a new jtbl's end is bounded by the next raw dlabel OR the next existing carve start — an already-carved adjacent jtbl is gone from the data asm, so raw dlabels alone over-extend it → false "non-contiguous"). **BUILT + config-proven** (func_80171B4C `jtbl_801D8C48` merges with func_801734BC `jtbl_801D8C68` → one `_after` carve `[0xb0af0..]`). **Byte-proof PENDING** a matched adjacent pair — func_80171B4C is struct-heavy (m2c gives `arg0->unkXX` + ratan2 + 8-case switch), a real match, not a quick de-risk. NO-OP for family-1/cross-subseg (single carve per subseg) — committed configs unaffected (verified by reasoning: R22 rebuilds static configs; jtbl_carve only runs on new carves).
- **(b) NON-CONTIGUOUS jtbls (unmatched jtbl between) → ISOLATE** one fn into its own code subseg (whale `_o0b` precedent). `tools/jr_isolate.py` written (config split + `func_subseg`-derived carve, no rename bookkeeping; isolating F preserves carves BELOW F, so bank ascending). **BLOCKED — the real finding:** `split_src_region` can't partition the overlay `.c` — it has 922 non-address top-level items (the Phase-17 global canonical-sig extern layer + per-function callee-extern blocks + `DEFINE_func_X()` dedup macros + `// @class` annotations). Making it overlay-`.c`-aware (header = includes+global-extern-layer; attach leading externs to the following fn-block) is the **Stage-2 build item**.

### ⚠ Stage-2 unblock decision (Drew's call): isolation is a HARD Stage-2 prerequisite
Because func_801734BC is now committed in `_after` of every sibling, banking any heavy core (also `_after`, non-adjacent) hits case (b) → needs isolation. Options: **(i)** fix `split_src_region` for the overlay `.c` + finish jr_isolate (robust, needed regardless — Stage-2 has many `_after` cores → same-subseg even without func_801734BC); **(ii)** a one-time "isolate-ALL-jr-per-sibling" resegment (scalable: ~134 resegments then fast fills, vs per-fn ×134 splits) — likely the right Stage-2 architecture. Also open: byte-proof the MERGE with a matched adjacent pair.

### NEXT: **pivot to Stage 2** (this is an R27 effort/model boundary — prompt Drew to re-approve + toggle). Stage 2 = the heavy 191 jr cores (Fable5 crack-core → template ×134), which first requires the isolation build-out (option i/ii above). Cross-subseg multi-jtbl (the primary Stage-1 goal) is DONE + committed + R22 136/136.

---

## ▶ SESSION-3 CHECKPOINT (2026-07-12 late) — superseded by SESSION-4 above

**Committed baseline = `commit:0534`, R22 136/136 (now ~50s, parallel).** Session-3 commits: `commit:0531` (tiny-band), `commit:0532` (§8 PoC), `commit:0533` (§8 ×134 automation), `commit:0534` (R22 parallelization). Phase-26 total: **distinct-code 30.3→39.1%, instr-weighted 58.2→63.0%.**

### What session 3 delivered (all committed, R22 136/136)
1. **Tiny-band harvest** — 17,975 member-matches; distinct 35.2→39.1%.
2. **§8 jtbl-rodata tooling (the strategic unlock)** — overlay switch (jr) functions can now bank as C for the first time. `tools/jtbl_carve.py` (per-overlay jtbl-rodata carve) + `ld_interleave.py --section` + `<bin>_JTBL_INTERLEAVE` Makefile hook; cookbook **§8a** + SETUP. Reconcile-per-sibling + `extract_unit` now carries single-line typedefs. `tools/jtbl_family_bank.py` = the sibling sweep driver. **func_8012ACE0 banked ×133/133, 0 fail.**
3. **R22 parallelized** — `make clean && make extract-all && make check-all` = ~50s (was ~9m), 136/136 byte-identical. `JOBS ?= 16`.

### ⚠ THE STRATEGIC REFRAME (decision-log 2026-07-12, Drew's steer) — READ BEFORE PICKING THE NEXT TARGET
§8 did NOT just unblock a small mop-up — it unblocked the **single heaviest byte-weight chunk of the game**. Measured (`.run/family_hseq.json`): **9 of the 10 heaviest unmatched family cores are switch (jr) functions** (`func_80178D40` 890×134 = 477K ins, `func_8017BEBC` 952×113, `func_8015AE2C` 562×134, `func_8017A4AC` 536, `func_8015A3C8` 493 …); **jr substantial = 191 fams / 5.53M templatable ins**; the 45 small jr families I first eyed = only 129K ins (a light-tail trap Drew caught). **The endgame plan = heaviest-byte-weight-first via crack-core → template ×134; §8 is its key enabler.**

### ▶ THE CORRECTED NEXT PLAY (fresh session) — small-jr-first as a DE-RISK PREAMBLE, then the heavy 191 (Drew's sequencing, 2026-07-12; agreed)
**Stage 1 — the 45 small jr families (mid/tiny, 129K ins) FIRST, as a pipeline-hardening preamble (NOT for byte-weight — it's ~+1% instr; the point is de-risk).** The decisive technical reason: `jtbl_carve` today only does the **single-jtbl-per-overlay** carve — but func_8012ACE0 is now matched in all 133 siblings, so the *next* jr family makes those overlays **multi-jtbl** → **BUILD the `ld_interleave --order` (address-ordered) multi-jtbl carve HERE**, on cheap targets, before a Fable5 giant depends on it. Also validates variety (IMM vs PURE, per-overlay jtbl positions, stubborn exemplars) where a bug costs a 30-ins fn, not a 890-ins core; and needs NO Fable5 (progress now, no session-limit burn). Pipeline: match each small exemplar (m2c + reconcile; func_8012ACE0 had a ready §41b draft — check which of the other 44 m2c cleanly) → `jtbl_family_bank.py` ×~120 → parallel R22. **Do NOT let "45 done, feels productive" become grinding more light tail — pivot to Stage 2 once the pipeline is hardened + multi-jtbl proven.**
**Stage 2 — the heavy 191 jr family cores (5.53M ins — THE byte-weight objective).** `func_80178D40` (890×134 = 477K ins), `func_8017BEBC` (952×113), `func_8015AE2C` (562×134)… **Needs Task 7 (Fable5) UN-PAUSED** (§8 makes it worth it now — a jtbl core crack banks fleet-wide, not unbankable fuel). Per core: Fable5 crack (whole-binary-gate-verified, NOT plain rtu_match — jr false-match risk, §8a) → `jtbl_carve` (now multi-jtbl-capable from Stage 1) + `jtbl_family_bank.py` ×134 → parallel R22. Cheap-Opus applies banked §31/§45 idioms between Fable5 cracks. Non-jr substantial families (7.3M ins) — heavy too; mechanical ones via `family_sweep`, hard cores via Fable5.

### Effort/model (fresh session): plan-mode Max for the Phase-Start re-plan; then **prompt Drew to re-approve + `/effort` for Fable5** (Agent model:fable, parallel-isolated, whole-binary gate) on the heavy cores; Ultracode for the mechanical ×134 template waves; Max for synthesis. Ghidra MCP NOT needed (matching uses cached asm).

---

## SESSION-2 CHECKPOINT (2026-07-12) — superseded by SESSION-3 above

**Phase 26 status:** Tasks 0–6 DONE + committed (the h_seq engine + triage). Task 7 (Fable5) + Task 8 (mechanical harvest) IN PROGRESS. **Committed baseline = `commit:0528`, R22 136/136 confirmed.** Commits this phase: `commit:0518`→`commit:0528`.

### What's banked (all committed + R22-verified through commit:0528)
- **729 reconcile-class member-matches**: 463 (`commit:0527`) + 266 (`commit:0528`), from **6 no-jtbl reconcile-clean triage cracks** templated ×~133 via `--reconcile-raw`. Metrics ≈ **31%+ distinct-code / 59%+ instr-weighted** (was 30.3/58.2 at phase start).
- **MID-BAND HARVEST DONE + committed + R22 136/136:** plain `--hseq --band mid` banked **6,853 member-matches = 320 distinct functions** (3,098 type-heavy tail / 1,743 pinned / 873 no-ov077-body — all expected). **Metrics: distinct-code 31.1→35.2%, instr-weighted 58.9→60.9%.**
- **TINY-BAND HARVEST DONE + R22 136/136 (session 3, 2026-07-12):** plain `--hseq --band tiny` banked **17,975 member-matches / 5,617 gate-rejected** (h_seq-collision false-templates, correctly refused by the whole-binary gate — the collision-prone <16-ins band) across **266 overlay `.c` files** (180 tiny families; skips 1,184 no-matched-unit / 148 unresolved-imm-Tier2 / 117 STRUCT / 39 pinned). R22 clean-fleet **136/136**. **Metrics: distinct-code 35.2→39.1%, instr-weighted 60.9→62.9%.** Phase-26 total so far: distinct 30.3→**39.1%**, instr 58.2→**62.9%**. **NEXT: the two harvest gaps** — §8 jtbl-rodata tooling (Drew-approved) + the reconcile fn-ptr-extern fix — then re-measure/milestone.

### The h_seq family engine (all committed, the durable tooling)
- `tools/family_hseq.py` — the survey → `.run/family_hseq.json` (regen after every bank) + `docs/family-hseq.md`. Bands: substantial(≥80)/mid(16–79)/tiny(<16).
- `tools/family_remap.py` — extended reloc tracker (addu-hi §40b), `classify_member` (PURE/IMM/STRUCT), `imm_map_tier1` (T2a), `remap_hseq` (plain template), **`remap_hseq_body`** (remap a RAW crack body — for reconcile-raw), `gather_externs`.
- `tools/family_sweep.py --hseq` — templates matched-exemplar families; `--reconcile-raw RAWDIR` = §41c per-sibling reconcile (remap the RAW crack per sibling + `canon_sig_reconcile` vs that sibling's TU); static pin guard (`__asm__("$N"` → skip). `--band`/`--only`/`--stage-only`/`--min-members`.
- Cracked-seed dirs: `.run/crack_raw/` (raw seeds, func_<ADDR>.c) + `.run/phase26-seeds/` (triage m2c seeds) + `.run/phase26-cracks/` (Fable5 crack bodies).

### The TWO harvest gaps (the levers for the remaining crack families) — see decision-log 2026-07-12
1. **§8 jtbl-rodata (Drew APPROVED building it, 2026-07-12).** Overlay jtbls live in the monolithic `data tail` (`asm/ov_*/data/tail.data.s`, e.g. `dlabel jtbl_801D8E24` ~line 92735 in ov077). Replacing a jr-function with C emits a duplicate jtbl → broken layout. FIX = carve each jtbl out of the data tail into a dotted `.rodata` subseg co-located with its function's code object (ov077 config `section_order:[.rodata,.text,.data,.bss]`; `ld_interleave.py` already wired, Makefile:397). **Per-overlay ×134** (each sibling's data tail). STAGE: prove on ONE jtbl fn in ov077 → automate ×134. Blocks all jr cracks incl. the top Fable5 cores (890/562/536…) and the 2 Fable5 crack bodies (`.run/phase26-cracks/func_80159C84.c`+`func_8015444C.c` — code-matched, jtbl-rodata unconfirmed; they bank once §8 exists).
2. **reconcile fn-ptr-extern gap.** `canon_sig_reconcile._reconcile_data` skips any extern containing `(` (fn-ptr syntax), AND `visible_above`/`tu_ambient` don't parse `void (*D_x[])(…)` → fn-ptr dispatch tables (D_801891B8) conflict → blocks ~15 of the 21 no-jtbl triage cracks. FIX = parse fn-ptr-array externs in all 3 fns (additive, but touches proven paths → regression-test the h_norm sweep). Smaller lever than mid/tiny.

### Fable5 findings (decision-log 2026-07-12) — Drew: NO more Fable5 agents until re-approval
- **rtu_match ≠ whole-binary gate for jr-functions:** rtu_match neutralizes INCLUDE_ASM (excludes the §8 jtbl rodata) + masks relocs → it MATCHES while the whole-binary gate FAILS. Batch-1 (`func_80159C84`/`8015444C`/`80176218`) = 0 whole-binary-confirmed cracks (2 jtbl false-MATCH, 1 limit-cut). **Fable5 crack prompts must require the whole-binary gate (or a jtbl-aware check), not plain rtu_match.** New idioms found (distill to cookbook when banked): postincrement pending-queue `(*(s32*)(p+K))++ >= N` (func_80159C84); split-temps inverse-§45-A for cross-jumped tails (func_8015444C).
- Usage/session limits repeatedly interrupt Fable5 (weekly + session limits, ~3:40am/5am resets).

### Triage (Task 6, committed) — `docs/phase26-triage.md` + `.run/phase26_triage.json`
119 draftable substantial families: cheap 29 (23 closeness-0 isolation-cracks) / permuter 29 / fable5 61. Whole-binary reality: 6 cheap no-jtbl-reconcile-clean bank; ~15 no-jtbl need the fn-ptr fix; 2 jtbl + the fable5 cores need §8. `.run/_rr_todo.txt` = the 19 not-yet-banked cracks.

### NEXT STEPS (priority order, all MECHANICAL — no Fable5)
1. ~~mid-harvest → R22 → commit~~ **DONE** (`commit:0530`). 2. ~~tiny band `--hseq --band tiny`~~ **DONE** (session 3, 17,975 banks, R22 136/136, distinct→39.1%). 3. **§8 jtbl tooling** (Drew-approved; ov077 PoC → automate) — the mechanical bands are now exhausted, so this + #4 are the remaining harvest levers. 4. **reconcile fn-ptr fix** → re-harvest the ~15 no-jtbl cracks (`.run/_rr19.sh` pattern). 5. **Task-5 type-families** (9 zero-bank substantial) via reconcile. 6. re-measure metrics; when gaps closed → milestone check.

### Effort/model: Max set (this session). Fresh session: re-apply `/effort max` for §8 design (Tier-1 tooling) or `/effort xhigh` for mechanical harvest runs. Ghidra MCP NOT needed (matching uses cached asm; run `/mcp` only if RE work resumes — R29).

## Milestone (gate 2 — structural completion, per Drew)

1. h_seq engine committed, V0–V3 validated with a measured template success rate.
2. Every substantial (nins≥80) family banked ×members OR classified with evidence.
3. Fable5-necessary cores attempted before window close; every crack distilled (R30/R31).
4. Carried 5-target queue resolved (cracked or wall-documented).
5. 136/136 byte-identical from clean fleet rebuild (R22); 0 NON_MATCHING (G4).
6. All three metrics reported + Step-D residue map.

Projections (targets, NOT gates): Task 5 ≈ +5.7% distinct-code; campaign → distinct 30.3%→~55–70%, instr-weighted 58.2%→~75–88%.

## Effort/model toggle map (R26/R27 — prompt + WAIT at every boundary)

On approval → `/model opus` + `/effort xHigh` (Tasks 0–4; ALL Fable5 via `Agent(model:fable)`). Task 5/6/8 waves → `/effort ultracode`. Task 7 launches + between-wave synthesis → `/effort max`. Task 12 → Max. Non-obvious debugging → Max.

## Blockers

*(none)*

## Log

- **2026-07-13 (session 8, the ×133 sweep blocker FIXED — `func_8015AE2C` banked ×134; Max):** Reproduced ONE
  sibling by hand instead of trusting the session-7 handoff (R14) and the picture sharpened: **the isolated region
  builds `[ OK ]` WITHOUT the body** (so §8b isolation was never implicated), and `conflicting types for
  D_801812A4` was the **only** hard error in the whole build — all 27 carried *function* externs were fine raw, so
  `cast_call_sites` was doing nothing. Root cause: `family_remap.gather_externs` prepends carried decls at **FILE
  scope**; `D_801812A4` is a fn-ptr dispatch table the sibling declares **four incompatible ways at BLOCK scope
  inside its own later functions**, so the carried file-scope decl **establishes a global the TU never had** and
  every later block-scope `extern` must now agree with it. Byte-proven asymmetry: `BLOCK(int) → BLOCK(struct*) →
  FILE(void*)` builds; `FILE(void*) → BLOCK(int)` errors. **Rejected the session-7 plan** (teach `reconcile_decls`
  a TU-visible oracle — a big, risky change to a proven path) for a smaller one: **don't disturb the TU's decl
  environment at all.** New `tools/scope_data_externs.py` demotes a carried `D_` extern to **block scope inside
  the function body** when the TU has no file-scope decl of it above the insertion point — byte-neutral (an
  `extern` emits no code), *never worse than raw*, so it needs no oracle, no type comparator, and no fn-ptr parser
  (`reconcile_decls`' regex **cannot parse** `extern void (*D_x[])(void *);` and was silently skipping exactly the
  failing symbols — the third silent-skip bug of the phase). Wired as the `scoped` stage (raw → **scoped** →
  recovered → reconciled). First sibling byte-identical first try; **full sweep 133/133 BANKED, 0 failures**;
  **R22 clean-fleet 136/136** (534 changed src files); dedup 1813/0; **instr-weighted 63.0→63.6%, distinct-code
  39.1→40.5% (+256 unique fns / +79,957 ins)** — one core, ~0 agent tokens. The **R17 triage rule** (committed
  `commit:0550` at Drew's ask) paid off on its first test: `conflicting types` = the compiler *refused to compile* =
  a C front-end diagnostic = **our Python**; a gcc-source read would have taught nothing. Knowledge captured
  DURING the session (R30/R31): cookbook **§8d**, decision-log, SETUP tool row. **NEXT: `func_80178D40`**
  (890×134, close=39, all in case 0x5C — cheap-Opus/permuter, no Fable5), then the R27 prompt for Fable5 on
  **`func_8017BEBC`** (952×113, close=2 — the allocno-tie R17 target).
- **2026-07-13 (session 6, the §8b scoping wall BROKEN — heavy-jr harvest unblocked; Max):** Built the
  **declaration-environment reconstruction** on the proven `overlay_src_split.py` parser. **R14 correction:**
  session-5's "gcc-2.7.2 block-scope-extern TU-persistence" root cause was *wrong* — there is no gcc quirk;
  `DEFINE_func_*` macros expand at FILE scope, so their leading externs are genuine file-scope decls that simply
  live in `engine_core.h` and are invisible to a col-0 `.c` scan (census: 1,377 macros / 3,929 extern lines / 1,462
  symbols). **Rejected the approved "global symbol→type map + shadow set" design** (X1/P5d — same goal, better
  mechanism): the engine is loosely typed (`func_80173544` is *defined* `s32 f(void*)` yet declared
  `extern void f(void);` inside `func_801734BC`'s body), so "declare every used symbol" hoists that block-scope
  shadow to file scope and CREATES the conflict a shadow-set heuristic then has to dodge. Instead: **reconstruct the
  original TU's file-scope decl environment and carry it strictly forward** — conflict-free by construction (every
  carried decl already coexisted with every definition in the one original TU; decl compatibility is
  order-symmetric; shadows stay in bodies). The byte-gate then found **two more** lost decl sources I had not
  predicted: **a definition is itself a declaration** for everything below it in its TU (`func_8012B2CC undeclared`)
  and **file-local typedefs** used by a carried prototype (`parse error before '*'`, `Vec3s`). **Full 54-jr
  isolate-all on ov_SC01_077 → `d19c9580` BYTE-IDENTICAL; R22 clean-fleet 136/136** (the exact configuration
  session 5 could not build). Parser selftest still 404/404. Then wired **LAZY per-core isolation** into
  `jtbl_family_bank` (Drew's call — upfront-×134 would add ~7,200 region files): `jtbl_carve` NON-CONTIGUOUS
  fail-loud → `jr_isolate_all --only <core>` → re-extract → re-carve; **proven on `func_80178D40` (890×134, the
  heaviest core)** — carve blocked → isolated (byte-neutral) → carve lands in its own subseg. **Two latent bugs
  found + fixed** (both would have corrupted the heavy sweeps): `func_subseg` read the owning subseg from the
  *asm tree*, which `make extract` never prunes, so after an isolation it returned the STALE owner and silently
  re-created the collision (→ derive from the config); and the sweep's `revert()` **deleted** the shared
  `overlays.mk` carve var unconditionally, which would have destroyed a *committed* carve (all 134 overlays have
  one) on any failed sibling (→ restore to its committed value). Added a dirty-tree preflight to
  `jtbl_family_bank` (an uncommitted prior family would be silently reverted). Knowledge captured DURING the
  session (R30/R31): cookbook **§8b RESOLVED + new §8c** ("splitting a TU means rebuilding its declaration
  environment, not moving text") + decision-log. Committed. **NEXT: Task 7 heavy-jr crack waves — R27 boundary,
  prompt Drew for effort/Fable5 before launching.**
- **2026-07-13 (session 5, Stage-2 isolation build — parser DONE, single-cut PROVEN, full isolate-all hit the gcc-2.7.2 scoping wall; Max):** Drew re-approved Stage 2 + set `/effort max`; steer = scalable isolate-ALL-jr-per-sibling upfront resegment, then Fable5 on the heavy cores. Built + fleet-validated **`tools/overlay_src_split.py`** (overlay-`.c`-aware partition; **404/404 overlay `.c`, 341,902 items, round-trip exact / 0 unresolved / 0 non-monotonic** — fixed 5 parser edge cases: definition-vs-declaration by brace/`;` scan, K&R defs, comment/`#`-directive peeling, `def_name` from the signature not preamble, `SETTER`/`RETCONST` macro anchors, trailing-footer preservation). Built **`tools/jr_isolate_all.py`** (multi-cut resegment: config split at jr boundaries, source repartition + INCLUDE_ASM path repoint, banked-jr carve repoint, -O0 skip, ambient file-scope decl carry). **SINGLE-cut isolation BYTE-IDENTICAL** (func_8013FFD8 in `main`, clean `make build` `d19c9580`, R22) — Task 2 proven. **Full 54-jr isolation FAILED on the dense `_after` object** after fixing 7 C-scoping edge cases in sequence, on the deep one (byte-verified): **gcc-2.7.2 block-scope-extern TU-persistence** — `func_801734BC` uses `D_80126B3E` declared `extern s16` only inside `engine_core.h` `DEFINE_func` macros; splitting the TU separates the core from the earlier macro expansion that declares it → `undeclared`. Root: mechanical TU-splitting rebuilds the decl ENVIRONMENT (semantics), not just text — col-0 ambient-carry can't reach macro-injected decls. **Candidate fix (not built): declaration-completion** from a global `engine_core.h`+overlay symbol→type map (decision-log 2026-07-13, R31). **Baseline reverted + intact; 2 tools untracked, NOT committed** — surfaced the fork to Drew (P5a) before sinking more time. NEXT: Drew's steer (build declaration-completion vs pivot Stage-2), then commit the tools.
- **2026-07-12 (session 4, multi-jtbl `--order` + family-1 — the Stage-1 de-risk build; Max):** Recon proved the Stage-1 core risk is precise: `jtbl_family_bank.revert()` restores each sibling to committed = has func_8012ACE0's carve, so banking ANY 2nd jr family makes the overlay multi-jtbl. Built `ld_interleave.py --order` (address-ordered N-piece sandwich; legacy `--front/--tail` byte-untouched → main + 133 single-carve siblings unaffected) + rewrote `jtbl_carve.py` additive/regenerate-from-config (parses tail data-region + existing carves, splits the containing data piece for the new jtbl, re-emits `--order`; same-subseg → fails loud). Fixed `jtbl_family_bank.bank()` to `make extract` BEFORE the carve (asm must match the reverted config; the old error-string retry was fragile — 3 early siblings carve-failed). **Family-1 `func_801734BC` (34-ins PURE jr, ov_SC01_077_after) matched in ov077 (shared-tail switch idiom `case N: t=-N; break; default: goto after;`) + banked 133/133 siblings — CROSS-subseg multi-jtbl (func_8012ACE0 `_a` + func_801734BC `_after`), the primary Stage-1 goal. R22 clean-fleet 136/136 byte-identical (~52s).** Wrote `tools/jr_isolate.py` (same-subseg non-contiguous case — split a fn into its own subseg via `split_src_region`, `jtbl_carve` re-derives the carve subseg; ascending-order discipline avoids carve-renames) — not yet integrated/committed. §8a finding: the still-INCLUDE_ASM carve build fails (migrated rodata not emitted through INCLUDE_ASM) — OFF the banking critical path (bank swaps C before building). Committed (Drew pushes — R6). NEXT: prove isolation on a higher fn → integrate → pivot to Stage 2.
- **2026-07-12 (session 3, R22 parallelization — Drew asked "why so slow, profile+optimize"):** Profiled the clean-fleet R22 (`make clean` + extract-all + check-all). **Phase split: extract-all ~6m11s (the BIGGER phase, 136 serial `splat split` runs) + check-all ~2m58s (136 serial builds; most overlays ~1.3s, ov077 slow — maspsx on its 15K-line `.c`) = ~9 min.** Both phases were serial on a 32-core box (the old Makefile comment called cross-binary `-j` "racy"). **Verified the only shared write is the 4 generated `include/*.inc` macros at extract time (identical content); everything else is per-binary-disjoint and `include/` is read-only during a build → parallel is safe.** Added `JOBS ?= 16` + **`make extract-all`** (seed `main` serial for the macros, then parallel-extract the rest) + **parallel `make check-all`** (`xargs -P$(JOBS)`), correctness-gated. **Result: `make clean && make extract-all && make check-all` = ~50s, 136/136 byte-identical — a ~10.5× speedup (9m→~50s).** Committed the Makefile change (own commit). This compounds across the endgame (R22 runs every commit).
- **2026-07-12 (session 3, §8 ×134 AUTOMATION — func_8012ACE0 banked fleet-wide):** Built the jr-function ×134 harvest pipeline and proved it end-to-end. `tools/jtbl_carve.py` = per-overlay §8 carve generator (finding: the same fn is at the same vram across siblings but its jtbl is at a DIFFERENT address in each — ov_SC01_000 jtbl_801A331C / ov_SC02_000 jtbl_801E587C — so the carve is recomputed per sibling; rewrites the config data-tail subsegs + sets `<ov>_JTBL_INTERLEAVE`). `tools/jtbl_family_bank.py` = the sibling sweep driver (per sibling: revert→carve→extract→remap_hseq+reconcile→whole-binary gate; idempotent, revert-on-fail). **Propagation-cap fix:** `family_remap.extract_unit` now carries single-line `typedef`s (jr-function bodies define local `typedef struct{} Foo_<addr>;` that must template with the body, else the sibling sees `Foo undeclared` — additive, byte-gate-protected). **func_8012ACE0 family: 133/133 siblings BANKED, 0 failures; R22 clean-fleet 136/136 byte-identical.** Metrics: distinct-code 39.1% (50,698 unique fns), instr 63.0%. **Opportunity map (`has_mid_jr` families):** 237 total (5,805 members / 5.68M ins) — 46 small mid/tiny (771 members, mechanical, same pipeline) + 191 substantial = the Fable5 cores (Task 7, paused). Committed. **NEXT: (a) R22 profiling/parallelization (Drew asked — check-all builds 136 binaries serially on a 32-core box); (b) the other 45 small jr families.**
- **2026-07-12 (session 3, §8 jtbl-rodata tooling — PoC PROVEN):** Built the overlay jtbl-rodata mechanism (cookbook §8a, the durable writeup). Findings: overlay jtbls form a contiguous `.rodata` island at the TAIL (between `.data` globals and a tiny remnant), not the EXE's central island. Mechanism (byte-identical, 2-step): (Step 1) carve a matched jr-function's jtbl out of `[data,tail]` into a dotted `[.rodata, <code-subseg>]` subseg (spimdisasm migrates it into the fn's `.s`) + `[data, tail2]`; parameterized **`tools/ld_interleave.py --section .<binary>`** (derives the symbol prefix; default `.main` = EXE byte-identical, backward-compat proven) places text→data(pre)→rodata→data(post)→bss — **build byte-identical with the fn still INCLUDE_ASM**. (Step 2) swap in the C body → **byte-identical** — the C-emitted jtbl lands exact. Wired into `make extract` via `<bin>_JTBL_INTERLEAVE` in `config/overlays.mk` + a `$(strip)`-guarded `ifneq` branch (gotcha caught: a trailing `#comment` on the `:=` left whitespace → the branch misfired on resident). **PoC target: `func_8012ACE0`** (25-ins single-jtbl jr-function, ov_SC01_077) — reconciled via `canon_sig_reconcile` (raw draft had `conflicting types`), banked **byte-identical `d19c9580`**, ov077 clean-rebuilds. Key P9 finding: **`func_80159C84`/`func_8015444C` (the 2 carried Fable5 bodies) are rtu_match FALSE-MATCHes** — their C jtbls are incomplete (52B vs 56B), so they never bank; rtu_match excludes the §8 rodata (confirms the checkpoint's "2 jtbl false-MATCH"). The maspsx "hang" scare was a truncated-experimental-file artifact — the real pipeline builds in ~1s. **NEXT: full R22 (in flight) → commit the PoC + tooling; then the ×134 automation** (generate the per-overlay carve + template the reconciled body per sibling).
- **2026-07-12 (session 3, TINY-BAND mechanical harvest — Task 8 continuation):** Regenerated the h_seq manifest from the mid-band-banked src (fleet 77.2% fn / 60.9% instr / 35.2% distinct — matches `commit:0530`), then ran `family_sweep.py --hseq --band tiny`. Dry-run sized it: 180 tiny matched-exemplar families / 23,592 staged member-drafts across 267 (overlay,split) groups (skips 1,184 no-matched-unit / 148 unresolved-imm / 117 STRUCT / 39 pinned). Gated run: **17,975 member-matches BANKED / 5,617 gate-rejected** (h_seq-collision false-templates — the whole-binary byte-gate G3/P9 refused every one; ~76% bank rate; per-group ~17/21 main + ~110–129/150 `_after`). 266 overlay `.c` files touched. **R22 clean-fleet (`make clean` + extract-all-136 + check-all) → 136/136, 0 failed.** dedup-check 1813 validated / 0 failed (registry untouched — hseq banks are per-overlay src, not ×134 registry). **Metrics: distinct-code 35.2→39.1% (50,571/84,996 unique fns), instr-weighted 60.9→62.9%.** The mechanical size-bands (substantial/mid/tiny) are now harvested; the remaining levers are the two harvest gaps (§8 jtbl-rodata, reconcile fn-ptr-extern). Committed (Drew pushes — R6).
- **2026-07-12 (session 2b, Fable5 batch-1 whole-binary reality):** **P9 correction:** the 2 Fable5 "cracks" (`func_80159C84`/`func_8015444C`) rtu_match-MATCH but FAIL the whole-binary gate — both are jr-functions and rtu_match doesn't verify the §8 jtbl rodata (decision-log). Two harvest gaps found: **§8 jtbl-rodata** (blocks all jr cracks incl. the Fable5 cores) + **reconcile data-extern** (D_801891B8-class, blocks ~15/21 no-jtbl triage cracks). Real whole-binary result: **6 no-jtbl reconcile-clean cracks bank = 729 members** (463 committed + **266 this commit**, func_8015CD20/8015C128 ×133). `func_80176218` (no-jtbl) still cracking = the clean non-jtbl Fable5 test. R22 deferred until it releases asm/.
- **2026-07-12 (session 2, resume after usage-limit interruption):** R22 confirmed the committed 463 reconcile-class banks **136/136**. Fable5 batch-1 results: **`func_80159C84` MATCHED** (337-ins 2-jtbl giant, pin-free; new cookbook idiom = gcc-2.7.2 postincrement pending-queue `(*(s32*)(p+0x238))++ >= K`); `func_8015444C` (reached 29-mismatch) + `func_80176218` (early) were cut off by the weekly limit → **re-launched** (444C resumes from its 29-mismatch partial). The interrupted reconcile-raw-19 harvest (260/1565, partial src) was **reverted (R22 discipline)** and **re-running clean** folding in func_80159C84. All background; process on completion → R22 → commit. **Fable5 batch-1 = the last batch until Drew re-approves (Drew, 2026-07-12).**
- **2026-07-11 (session 1, Task-8 validation slice — Drew-approved pre-window de-risk):** Ran reconcile→gate→template on the triage cracks. **Reconcile→bank WORKS:** raw 0/23 (§41 wall) → via `canon_sig_reconcile` v3.2 **4/15 banked into ov077** (`func_801506A4`/`8016A73C`/`80167540`/`80155800`, byte-identical). **Templating a reconciled body ×133 FAILS 0/4** — reconciled bodies are ov077-TU-specific (casts + collision-renames), need per-sibling re-reconcile (§41c). → **Task-8 prerequisite: port the h_norm `--reconcile` M2 path into `hseq_sweep`.** Kept the 4 ov077 banks. decision-log 2026-07-11 (R31). Paused before building the wiring per Drew.
- **2026-07-11 (session 1, Task 6 — DONE + paused):** Ultracode triage Workflow (119 agents, 0 err, 5.3M tok): m2c draft (+§8 jtbl) → `match_one` closeness → class + lever + seed. **cheap 29 (23 closeness-0) / permuter 29 / fable5 61.** Curriculum → `docs/phase26-triage.md`. Attempted to bank the 23 cracked "wins" into ov077 (Drew: "bank the wins but pause before task8") → **0/23 gate** — the isolation-MATCHes carry standalone types/Ghidra-sigs that hit the §41 def-side wall in the real TU (`redefinition of struct Obj` / `conflicting types`); banking needs the Task-8 `--reconcile` pass. Seeds preserved in `.run/phase26-seeds/` + `.run/ov077_bank/`. **PAUSED before Task 8 per Drew.** src pristine, ov077 green.
- **2026-07-11 (session 1, Task 5 — GO/NO-GO = GO):** Ran the real byte-gate on the substantial matched-exemplar band. Discovered + fixed the decl class (`remap_hseq.gather_externs` carries file-scope externs). **532 members banked**, R22 136/136 green, distinct 30.3→30.9% / instr 58.2→58.5%. Per-family: 3 tracker-miss PURE families bank 100% ×133 (399 byte-perfect free win); 9 type-using families → §41 reconcile (Task 8); 16 pinned → Task 7. Machinery byte-proven 100% correct on clean families → GO to scale. decision-log 2026-07-11 (R31). Committed.
- **2026-07-11 (session 1, Task 4):** Added `family_sweep --hseq` (additive `hseq_sweep()`, h_norm path byte-untouched): manifest-driven templating via `remap_hseq`, unique per-group verified-out, static `__asm__("$N"` pin guard (skips the ×1-only pinned cracks → Task 7). Dry-run (`--stage-only`): substantial band stages 1507 clean / 267 groups, 1643 correctly skipped as pinned (16/29 families pinned, incl. the decision-log-named ones). Drafts byte-correct by construction; whole-TU gate = Task 5. Committed.
- **2026-07-11 (session 1, Task 3):** Built the T2a imm engine (`imm_value`/`imm_map_tier1`/`remap_hseq`) — diff-driven Tier-1 literal swap with an asm-side ambiguity guard — + wired T2b cross-address self-rename. Tier-2 probe deferred (build-if-needed; byte-gate arbitrates). V3 (`.run/v3_imm.py`): 0 DIFF on all compilable pairs (5 MATCH), ambiguity guard + cross-address self-rename confirmed; comprehensive whole-TU gate validation is Task 5. Committed.
- **2026-07-11 (session 1, Task 2):** Built `tools/family_hseq.py` (full-frontier h_seq survey) + the shared word-diff classifier in `family_remap.py` (PURE/IMM/STRUCT, register-drift aware). Reproduces the fleet metrics + the 663/186/1.85M tail cross-check exactly; classification matches the Plan-agent table; 581 substantial target families / 3.22M templatable ins, 345 matched-sibling families / 1.14M ins = the zero-crack corpus. `docs/family-hseq.md` committed. Committed.
- **2026-07-11 (session 1, Task 1):** Extended `reloc_targets` for the add/addu indexed-global idiom (the "reach-1 tail" was largely this tracker blind spot, not unique code — decision-log + cookbook §40b). `symbol_map`/`remap` gained backward-compatible `to_addr` (cross-address T2b) + `imm_map` hook; sequential→single-pass substitution (fixes the latent chained-rename bug). norm_stream/h_norm untouched. V0 (22/22 regression, 15/15 fix vs splat .s) + V1 (160 pairs, 0 regressions) both green. Committed.
- **2026-07-11 (session 1, planning):** Phase Start (Tier 1, Fable5+Max+plan-mode). Megaplan analyzed; survey reproduced from sigs+src (R14) — fleet metrics match PhaseEnd_25 exactly; 186-not-986 substantial-family correction; #2 family is cross-address; 93 matched-sibling families found (0.51M ins). Tooling recon (Explore) + design pressure-test (Plan agent) → **the reloc-tracker blind-spot discovery** (addu-preserves-hi; 890×121 family is PURE reloc; 63-fam zero-crack corpus; sequential-substitution latent bug). Drew's gate-1 decisions: carried queue → end of phase; structural milestone. Plan approved; task list built (R28). Task 0 complete with this commit.
