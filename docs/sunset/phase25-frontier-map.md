# Phase 25 — Frontier Map (rtu_match-measured, 2026-07-10c)

> The systematic map of ALL remaining endgame work, replacing the stale-object-tainted wave-2 leftover
> list. Built from `.run/family_manifest.json` (current matched status) + a `tools/rtu_match.py` measurement
> pass over every draftable exemplar (`.run/frontier_measured.json`). Fleet **73.97%**.
>
> **rtu_match caveat (same blind spot as the §41b object-probe):** rtu_match masked-diffs the fn's `.text`
> only — it is BLIND to rodata (switch jump tables) and to LINK errors. So an rtu-MATCH on a jump-table or
> last-referencer fn is a FALSE crackable-now; those are classified into the specialized tiers below via the
> whole-binary gate / the T7-M1 findings, not by rtu_match alone.

## The endgame = 3 buckets (multi-member families, by ov_SC01_077 membership)

| bucket | families | byte-MB | action |
|---|---:|---:|---|
| **draftable** | **42** | 3.0 | crack ONE exemplar → propagate ×134 (the core crack work) |
| **matched-free** | **235** | 5.9 | exemplar already matched → propagate siblings ×134 (mostly earlier-sweep-failure walls) |
| absent | 2481 | 2.1 | no ov077 member; small fns in other overlays — LAST |

## Bucket 1 — draftable 42, classified by rtu_match (`.text` closeness)

| sub-bucket | n | fleet-leverage (Σ inst×nins) | tier / tool |
|---|---:|---:|---|
| **reconcile-first (fan-out)** | 24 | 456,027 | CC1-FAIL raw → strip conflicting externs → rtu_match → crack. Wave-3: reconcile→~70% MATCH. |
| **DIFF-crack (fan-out)** | 7 | 123,153 | compiles, DIFF 52–349 → the §42c lever-set |
| **near (permuter/fan-out)** | 6 | 60,836 | DIFF ≤25 (incl. 0x801549f8=3, 0x80164e40=8) → cheap crack / permuter-ILS |
| **F-jumptable (rtu-blind)** | 4 | 94,604 | `_o0` giants (0x8013c414/8013bd74/8013c0f8) + 0x8012ace0 — rodata switch table; §8 jump-table workflow |
| **M-linkwall (rtu-blind)** | 1 | 8,040 | 0x8016d688 — last-referencer of a scratch data symbol; manual undefined-syms |

**Crack fan-out target = 37** (reconcile-first 24 + DIFF-crack 7 + near 6). Full ranked list: `.run/frontier_crack_targets.json`.
Top by leverage: 0x80133cd4 (399×134), 0x80166994 (369×134), **0x8014fbc0 (22×1996)**, 0x8014d820 (304×134),
0x801670e4 (279×134), 0x80135480 (258×134), 0x80163ec8 (234×134), 0x8016cbc0 (209×134), 0x80166690 (193×134),
0x80132144 (27×539), 0x8014fe60 (95×268) … down to the ≤100-ins med tail.

**Giants caveat:** the 200+-ins GIANTS (0x80133cd4, 0x80166994, 0x8014d820, 0x80135480, 0x80163ec8) are the
likely **Fable5 short-list** — the rtu_match+§42c fan-out cracks ≤~180-ins reliably (wave-3 evidence); the
giants may need Fable5's compiler-internals reasoning. The map does NOT pre-spend Fable5 — the fan-out attempts
them and the ones it can't close become the surgical Fable5 list.

## Bucket 2 — matched-free 235 (propagate, no cracking)

Exemplar already matched; siblings unmatched. These are the RESIDUAL of the T7-part-1 matched-free harvest
(which banked 16,512) — i.e. the families that FAILED that sweep: the //@EDIT class (file-scope edits not
carried per sibling), split-TU-type conflicts, macro-defined bodies. **Recovery = propagation enhancements**
(a `family_sweep --edit-remap` that carries the exemplar's `//@EDIT` edits per sibling, symbol-remapped;
the split-TU-type reconcile). Deterministic, ~0 agent tokens once the tooling lands. The 266 wave-3-part-2
sweep drops (func_80133AB0/80136824) live here.

## Chunked execution plan (smart chunks, biggest-leverage-first)

1. **Crack fan-out over the 37** — the core. rtu_match engine (reconcile-first + §42c levers), leverage-ranked
   waves. Each crack → `family_sweep --reconcile` ×134. GIANTS that resist → Fable5 short-list.
2. **Propagation enhancements → recover matched-free 235 + the wave-3 sweep drops** — cheap bulk (5.9 MB).
3. **F-jumptable 4 + M-linkwall 1** — specialized workflows (§8 / manual undefined-syms).
4. **Fable5 surgical pass** — only the giants/new-idioms the fan-out flags.
5. **absent 2481** — last, low ROI.

## Reproduce
`tools/family_manifest.py` → `.run/frontier_draftable.json` (42) → `.run/crack3/measure_frontier.py` →
`.run/frontier_measured.json` + `.run/frontier_crack_targets.json` (37).
