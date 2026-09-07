# Canonical-decl reconcile tool — design input (Phase 24 T7 → follow-on; Drew chose "invest", 2026-07-03)

> **Purpose:** the fleet-wide **×134 giant unlock**. Captured live in the session that hit the wall
> (R30) as the spec a fresh plan-mode session builds from. This is design INPUT, not a locked design
> — the plan-mode session picks the approach (§Design options) and gets Drew's approval before building.

---
## ✅ RESOLVED — Phase 24 T7b (2026-07-03). Built as `tools/reconcile_decls.py` (Option 1). Cookbook §33.
- **R14 REFRAME of the premise:** the "×134 giant unlock" framing was a **misdiagnosis**. `func_80129CF8` banks ×134 **FREE** via the *existing* `dedup_propagate --recover` once its ×1 draft is reconciled (byte-verified: 134 overlays byte-identical, clean fleet 136/136, fleet→65.52%). Its symbols were already fleet-consistent; the lone `D_801151D4` `ptr` conflict is in `resident.c` (not an overlay member). So the tool is **NOT** a propagation unlock — it **automates the manual ×1 decl-reconcile** a freshly-matched giant needs (for the 6 sibling giants + the wave tail).
- **Approach:** Option 1 (per-draft cast-injection), as recommended. Option 2 (shared `engine_decls.h`) stays deferred.
- **Open questions answered:** (1) picker heuristic = `engine_core.h`-macro type AUTHORITATIVE, else plurality across all overlays+resident (deterministic tie-break); it reuses `gen_harvest_targets.collect_data_decls`. (2) cast templates = the §conflict-taxonomy table, encoded as a single-pass per-symbol `re.sub`. (3) no genuine "no byte-neutral reconcile" class appeared for func_80129CF8 (all 5 conflicts reconciled byte-identical); the byte-gate logs+skips any that can't (fail-closed). (4) the per-member `--recover` callee/data extension (plan T4) was **NOT needed** — T1 byte-proved zero per-member conflicts (the fleet is decl-consistent).
- **Validated:** oracle 8/8 picks; full loose `func_80129CF8` → `reconcile_decls` → `make build BINARY=ov_SC01_077` = `d19c9580` (BYTE-IDENTICAL); idempotent on canonical input. Real end-to-end proof on an *un-reconciled sibling giant* is the remaining step (Fable5 match → reconcile → ×134).
---

## The problem (byte-proven this session)
A "giant" (e.g. `func_80129CF8`, 191 ins, Fable5-cracked — cookbook §32) MATCHES standalone and banks
**×1** in `ov_SC01_077` fine, but **won't propagate ×134**: its shared callees/data are **loose-typed
across the fleet** — the same symbol is declared with incompatible types by different `engine_core.h`
macros + overlay siblings. When `dedup_propagate` instantiates the giant's macro (which carries its own
externs) in overlay X, those externs collide with X's other decls → `conflicting types` → the byte-gate
fails → the overlay is excluded → reach<2 → dropped. `--recover` only reconciles the *propagated fn's
caller* extern, NOT the *callee/data* externs inside the macro body, so it can't fix this.

The flagship `func_80132784` propagated ×134 only because its symbols happened to be fleet-compatible.
Giants that touch loose-typed symbols (most) are ×1 without this tool → a fraction of the assumed ROI.

## Conflict taxonomy (all seen on func_80129CF8; the tool must handle each byte-neutrally)
| class | example (func_80129CF8) | canonical | byte-neutral reconcile (PROVEN by hand this session) |
|---|---|---|---|
| **data: array elem width** | `D_80126948` = `u8[]` (4 siblings) vs my `s32[]` | `u8[]` | decl canonical `u8[]`, cast at use: `cam = (s32*)D_80126948;` |
| **data: struct vs array** | `D_80126DB8` = `struct BigCopy` (engine_core macro) vs my `s32[]` | `struct BigCopy` | decl canonical, `p1 = (s32*)&D_80126DB8;` (BigCopy = `{s32 words[41]}`, engine_types.h) |
| **data: scalar vs ptr** | `D_801151D4` = `s32` (10×) vs my `s32*` | `s32` | decl `s32`, store `D_801151D4 = (s32)cam;` |
| **data: signedness** | `D_801150D6` = `s8` (macro) vs `u8` (needed for `lbu`) | pick per-opcode | decl `s8`, access `*(u8*)&D_801150D6` to force `lbu` (the target opcode decides) |
| **callee: return type** | `func_80012F74` = `s32` (macro) vs my `s16` (target sll/sra) | `s32` | decl `s32(...)`, cast the RETURN: `x = (s16)func_80012F74(...)` reproduces the sll/sra |
| **callee: arity / param width** | (fix_arity_callers class) | — | no-proto `extern <ret> f();` where promotion-safe (existing `fix_arity_callers`) |

**KEY INSIGHT:** the canonical decl goes in the giant's extern block (matching the fleet's majority /
the engine_core macro), and the giant's ACCESS SITE carries the cast. The cast is compile-time only →
the load/store/jal opcode is unchanged → **byte-neutral, arbitrated by the whole-binary byte-gate**.
A wrong reconcile just fails the gate (fail-closed, G3/P9) — so the tool can trial-and-error safely.

## What "canonical" means when the fleet disagrees
The tool must PICK one type per symbol. Candidates for the picker (plan-mode decides):
- The type used by the most `engine_core.h` DEFINE_ macros (they're the shared/propagated bodies — the
  fleet-consistent set), tie-broken by overall frequency.
- Never change the shared macros' type (that would re-break their matches); always conform the NEWCOMER
  giant to the established canonical + cast. (If a macro itself is wrong, that's a separate migration.)
- Signedness/width where an OPCODE depends on it (lbu vs lb, lh vs lw): the *target asm* decides, applied
  via an access cast under whatever the canonical storage type is.

## Design options (for plan mode)
1. **Cast-injection into the draft/macro (lighter):** extend the reconcile pipeline (a sibling of
   `sig_unify`/`cast_call_sites`/`fix_arity_callers`) to, per giant draft: resolve each callee/data
   symbol to its fleet-canonical decl, rewrite the giant's extern to canonical, inject the byte-neutral
   access cast at each use, re-gate. Integrates before `dedup_propagate`. **Recommended starting point**
   — it's the mechanization of exactly what I did by hand, and stays per-giant (no fleet-wide churn).
2. **Shared canonical-decls header (heavier, more permanent):** one `src/shared/engine_decls.h` with ONE
   canonical decl per shared symbol, included fleet-wide; migrate overlays/macros off their local decls;
   giants + everything else cast against it. Bigger blast radius (touches all overlays), but kills the
   loose-typing friction permanently, not just for giants. Phase-17 built a `gen_engine_decls.py` that
   FAILED as a *global* header (broke existing loose matches) — revisit WHY (the fix is per-site casts,
   which option 1 provides); this option only works married to universal access-casting.

Likely answer: **build option 1 first** (unblocks giants now, low risk), keep option 2 as the eventual
consolidation once casting is universal.

## Existing tools to extend / reuse (don't rebuild)
- `tools/sig_unify.py` — canonicalizes a draft's callee externs + its own def sig (callee-side).
- `tools/cast_call_sites.py` — §17a-1 per-site fn-ptr cast (the §20 cap tool).
- `tools/fix_arity_callers.py` — no-proto caller-extern arity (`--any-proto --binary`).
- `tools/canon_resident_calls.py` — resident-callee link-miss name rewrite.
- `tools/gen_harvest_targets.py` — resolves callee/data symbols to banked-canonical decls (scans the .s
  for D_ refs). **The canonical-type oracle probably lives here or is a sibling.** Note: it defaults to
  `asm/<bin>/nonmatchings/<bin>` — pass `--asm-dir …/<bin>_a` for the region-a giants.
- `tools/dedup_propagate.py --recover` — where the reconciled giant then propagates ×134.
- `tools/gate_stage.py` — the pipeline that chains canon → cast → sig_unify → harvest_verify → propagate.

## Live test case (committed)
`func_80129CF8` banked ×1 in `src/ov_SC01_077/ov_SC01_077_a.c` (byte-identical, the reconciled draft is
`.run/t7/func_80129CF8.c`). Its ×134 propagation currently fails (`dedup_propagate --addr 0x80129CF8
--recover` → all overlays excluded → dropped). **Done = that command propagates ×134, clean fleet 136/136.**
The 6 sibling giants (`.run/t7/GIANTS_SURVEY.md`) are the scale-up target once the tool works.

## Open questions for plan mode
- The canonical-type picker's exact heuristic + where it reads from (gen_harvest_targets? a fleet scan?).
- Per-conflict-class cast templates (the table above) — encode as a small rule set; the byte-gate validates.
- Does any conflict class have NO byte-neutral reconcile (a genuine Phase-16 "no consistent type" wall)?
  If so, that giant/symbol is honestly ×1-only — detect + log, don't force. (A narrow Fable5 probe is the
  only escalation, but the TOOL is Opus work — Fable5 is for stalled giant *matches*, not this plumbing.)
- Test on func_80129CF8 → then the 6 giants → then fold into the wave pipeline for all future giants.
