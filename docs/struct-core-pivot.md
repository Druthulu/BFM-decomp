# Struct-Heavy Shared Core — Findings & Pivot (Phase 16)

> **Status (2026-06-19):** the m2c + decomp-permuter brute-force approach **will not crack** the
> struct-heavy shared core. It yields a few percent, bounded by a fundamental wall (loose typing),
> not by a fixable bug. **Decision (Drew): pause this approach, document, and plan a new idea.**
> This file is the durable record + the seed of the next plan. The harness bug-fixes are real and kept.
>
> **Phase 17 / T1 update (2026-06-19):** the wall is now *quantified* by a full census of all 957 residual
> shared stubs — see **`docs/wall-taxonomy.md`**. Headlines: the loose-typing wall is **~99 functions (10%)**
> (not the whole tail); the **biggest addressable lever is rich m2c context (struct + jump-table +
> fn-pointer-table types), reaching ~67%** — i.e. Direction A/B's *value is as m2c `--context`, not Ghidra-C*,
> exactly as the deep-research revised. The named "DATA-symbol header" lever (§14c-c) addresses **0** functions
> and is dropped. `sig_unify` alone (no permuter) re-derives ~5%, matching this doc's ~3% finding.
>
> **Phase 17 / T4-T5 update (2026-06-19):** the rich-context thesis was **tested and is byte-neutral**.
> The actor struct was fully recovered (base `0x80078E00`, ~154 fields, 32 pointers; live-verified via
> PCSX-Redux, anchored to Phase-3 — see `docs/actor-struct.md`), m2c **adopts** it (`arg0->f_X`), but on a
> structural-miss sample it scored **0 better / 10 same / 2 worse** vs m2c-alone (identical bytes; the misses
> are 50–98% mismatched = m2c decompiler limits, not missing types). The fn-ptr-table context (T4) *unblocks
> compilation* for the 85 fnptr-call functions but they remain structural misses underneath. **Conclusion:
> Direction A/B (struct/type recovery) is a comprehension/decomp.me win, NOT a byte-match lever** — Phase 16's
> wall re-confirmed from the type angle. The last untested byte lever is the permuter on the genuine 146
> near-misses (T6).

## Objective (unchanged)
Match the ~964 remaining **shared** engine functions in `ov_SC01_077` (struct-heavy; each propagates
×134 overlays via `dedup_propagate`). Cracking them would lift the fleet from 54.5% toward ~90%.

## What we built and tried (the pipeline)
`m2c --valid-syntax` (+ `common.h` byte-faithful macros `M2C_FIELD`/`NULL`/`s64`) → `sig_unify`
(canonical signatures) → `match_one` (fast prefilter) → **decomp-permuter** (regalloc/schedule search) →
`harvest_verify` **whole-binary byte-gate** (the sole arbiter, G3) → `dedup_propagate` (fleet-wide).
Driver + supervisor + safe-exit (`tools/auto_*.{py,sh}`) built for an unattended 5-day run.

## Harness bugs found and fixed (REAL improvements — kept regardless of direction)
The byte-gate caught a string of false positives; each fix is committed and correct:
1. **Permuter `base.c` stripped callee externs** → compiled with implicit-`int` callees → matched in the
   wrong signature context. Fixed (`make_base_c` keeps the canonical externs).
2. **`run_permuter` counted `output-<score>` dirs as matches** — only `output-0-*` is a true byte-match;
   it was calling score-20/145 "best" results "MATCH" (this produced the illusory overnight "42%"). Fixed.
3. **`sig_unify` missed m2c's no-`extern` prototypes** (`M2C_UNK func_X(void *); /* extern */`), so callee
   types stayed m2c's guess and the whole-binary build hit `conflicting types`. Fixed (`PROTO_DECL_RE`).
4. **`winner_to_draft` string-replace failed** (permuter reformats typedefs one-per-line) → typedef
   redefinition. Fixed (line-filter strip).
These got the harness from "false 42%" to "honest ~1 in 8 on a controlled sample."

## The fundamental wall: the original code is LOOSELY TYPED
The original BFM engine was written in **K&R-style / loosely-typed C** (PsyQ-era). Evidence (byte-checked):
- The *same* function is called with an **integer at one site and a pointer at another**, and with an
  **argument at one site and no args at another** (e.g. `func_8012AAAC` is defined `void func(void)` but
  called as `func_8012AAAC(arg0)` from a matched caller — and the caller is byte-correct).
- A **global canonical-decls header** (the planned "lever 1") forces ONE signature per function and
  therefore **breaks the existing matches** (`passing arg makes integer from pointer without a cast`
  across many already-matched functions). Confirmed and reverted.
- For many functions the **body is byte-correct in isolation** (`match_one` MATCH) but there is **no C
  declaration** that simultaneously (a) matches the canonical definition and (b) supports the call site.
  These are not fixable by any harness change — they'd need per-call-site type surgery or hand inline-asm.

## Why this yields ~3%, not the crack
- The easy/consistently-typed functions were **already matched by Phase 15**. What remains is
  disproportionately the **loose-typed hard class**.
- **m2c** is a per-function decompiler with weak type inference; it *guesses* a prototype per call, and on
  loose-typed code those guesses are mutually inconsistent across the TU.
- The **permuter only fixes register allocation / scheduling** — it cannot fix a wrong callee type, a wrong
  symbol, or a structural mis-decompilation, which is what the residual actually needs.
- The **byte-gate correctly rejects** the subtly-wrong drafts (this is good — zero false matches — but it
  means the yield is genuinely low, not artificially low).
- Measured gate-verified rate on controlled samples: **~1–2 of 8–16**. A 5-day run would bank a modest
  fraction (single-digit to low-double-digit percent of the 964), ×134 propagation ⇒ a few fleet points.

## Decision
**Pause the m2c+permuter brute-force as the "crack."** Optionally still run it during the away window for
the cheap few percent (the byte-gate guarantees correctness) — but only after the harness is hardened, and
understood as a consolation, not the solution. **The real next step is a new approach + new research.**

---

## New directions to research (the next plan)

The root cause is **lost type information**. The compiled binary discarded the structs/signatures the
original C had; m2c can't recover them from one function at a time. The promising directions all attack
*that* — recover or model the real types — rather than brute-forcing past them.

### Direction A — Ghidra's decompiler + GLOBAL type propagation (most promising)
We used m2c (lightweight, per-function). But the overlays are **already imported into Ghidra** (Phase 13),
and Ghidra's decompiler does **whole-program type propagation** — define the actor/entity struct(s) once and
Ghidra propagates field/param types across *all* functions, producing **consistent** signatures (exactly what
the loose-typing wall needs). Most mature decomps (sotn-decomp) start from Ghidra's C, not m2c. **Plan:**
define the actor struct in Ghidra (from analysis + Direction B), let it propagate, export typed C, then
permuter+byte-gate. Test on the known-answer ladder.

### Direction B — Emulator-guided struct & type recovery (attacks the root cause)
PCSX-Redux (our runtime oracle, R11) can reveal the **true** struct layout and field semantics by watching the
running game (R10 multi-datapoint): which offsets are pointers vs scalars vs arrays, field widths, and the real
argument types at call sites. This recovers the type information the binary lost. Feed it into Ghidra
(Direction A). This is the backlog's "emulator time-capture," elevated from quality-nicety to **the enabling
step** — without real types, no decompiler (m2c or Ghidra) can produce consistent matchable C.

### Direction C — Model the original's K&R / no-prototype declaration style
The original almost certainly used K&R declarations (`func_X();`, no arg types), which is *why* loose calls
compiled. The textbook `()` escape failed for **default-promotion params** (`s8/s16/u8/u16/float`) — but that's
a minority. **Research:** how do other PSX/PsyQ-era matching decomps (sotn, mednafen-era titles) handle
K&R-style engine code at scale? There may be a known declaration pattern (or a maspsx/compiler-flag trick) that
lets loose calls match without a global canonical signature. Treat web sources as untrusted (X2).

### Direction D — LLM-in-the-loop WITH gate feedback (narrow, re-evaluated)
Earlier we (correctly) dismissed ML for *one-shot byte-exact generation*. A different, untried shape: an
agentic loop where the model proposes a draft, sees the **byte-gate diff**, and revises — gate-supervised,
not blind (§14d's poor ROI was measured on *blind* drafting). Possibly with the typed Ghidra C as the seed.
Low priority vs A/B, but a bounded experiment once types exist.

### Research to run (deep-research skill, X2)
1. **Ghidra-decompiler matching workflow** — struct definition + type propagation + export, as used by
   sotn-decomp / other PS1 decomps; tooling that bridges Ghidra C → compilable matching C.
2. **Loose-typed / K&R PSX engine matching** — community idioms for inconsistent call-site types.
3. **PS1/Square actor-struct recovery** — has any Square PS1 decomp recovered an entity struct, and how?

### Recommendation
1. **Pause** the brute-force as the crack (this file).
2. **Optionally**, harden the harness and run the modest brute-force during the away window for the free
   few percent (cheap compute, correctness gate-guaranteed) — a consolation, not the plan.
3. **Make Direction B → A the new plan**: emulator-recover the actor struct + field/arg types → define in
   Ghidra → global type propagation → Ghidra-C → permuter + byte-gate. Run the deep-research first to ground
   it in how the community does it. This attacks the root cause (lost types) instead of brute-forcing past it.
