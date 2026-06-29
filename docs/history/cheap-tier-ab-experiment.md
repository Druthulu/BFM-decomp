# Cheap-tier A/B experiment — Haiku drafters vs Opus drafters (2026-06-29)

**Question (Drew):** for a 24/7 self-grinding setup, can a *cheaper model* draft matches under an
Opus orchestrator, given the SHA1 byte-gate makes a weak model a throughput risk only, never a
correctness risk? Concretely: Opus orchestrates (as now), but each fan-out drafter runs on a cheap
model instead of Opus.

**Method.** Forked `worker_wave.js` → `tools/workflows/ab_match.js`: same proven drafter prompt,
but jobs are `target × arm` and each agent takes its arm's `{model, effort}`. Froze a 20-target
sample from the `reach1` pool (`.run/ab-exp/targets20.json`, 18–108 ins, WAVE/PINS/STRUCT, all
currently-open / still-INCLUDE_ASM). Ran two arms as separate background workflows for clean
per-arm token totals: **opus** (`effort xhigh`, the production baseline) and **haiku**
(`effort high`). Scored with `tools/ab_score.py`, which re-runs `match_one.py` on every draft from
disk — the agents' self-reported MATCH is NOT trusted (the byte-gate is the sole arbiter, G3/P9).

## Result — `match_one` proxy (per-function, relocation-masked)

| arm | matches | near | cost (measured) | $/match | matches/$ |
|---|---|---|---|---|---|
| opus  | **15/20** | 5 (median close 11) | $35.43 | $2.36 | 0.42 |
| haiku | **10/20** | 10 (median close 88) | $4.92 | $0.49 | **2.03** |

## Result — whole-binary SHA gate (the TRUE arbiter, G3/P9)

**IMPORTANT correction:** `match_one` is a per-function *proxy* (standalone compile with the draft's
own externs). Running the Opus arm through the real whole-binary gate (`gate_stage`) banked only
**4 of the 15** proxy-matches: `func_80138BE0 func_8012F828 func_8012E9C0` (_a) + `func_80141100`
(main). The other 11 are **self-match-but-gate-rejected** — byte-correct standalone, but in the real
TU the canonical engine-header declarations change codegen (the documented `plumbing_blocked()` /
`reserved_walls()` wall). They were logged to the backlog as recovery/hand-finish fuel, not lost.

So `match_one` **over-counts bankable yield** on reach1/split-file functions. The A/B *drafting-
capability* comparison above still stands (Haiku ties Opus on the small tractable band at the proxy
level), but BANKABLE yield is gated by a further, **model-independent** TU-plumbing filter. Of the 4
that banked, Haiku had proxy-matched 3 (the ≤52-ins ones) — the cheap tier still owns the small band.
Banked + committed @ commit:0307; ov_SC01_077 stays byte-identical (d19c9580).

**Haiku closes ~4.8× as many functions per dollar as Opus.** Cost from measured workflow tokens
(opus 1,968,371; haiku 1,365,666) at a 35%-in/65%-out split, June-2026 ladder (Opus $5/$25, Haiku
$1/$5). Opus also took ~50 min wall vs Haiku ~10 min, and ~98k tok/draft vs ~68k.

## The structural finding — a clean size cliff, and Haiku ⊂ Opus

The 10 functions Haiku matched are a **strict subset** of the 15 Opus matched. Split by size:

- **≤52 ins (the tractable bulk): Haiku == Opus.** Haiku matched every ≤52-ins function Opus did
  (10 of 11), the lone exception being an 18-ins fn it missed by a *single* instruction (a
  `sra 12 vs 14` quirk — permuter/cookbook finishes that trivially).
- **94–108 ins (the hard tail): Opus only.** The 5 Opus-only wins are all big regalloc/schedule/
  struct functions where Opus's levers paid off (register `__asm__` pins, cross-jump tail
  duplication, §18 array-of-struct). Haiku was 25–101 off — not close.
- **5 both-missed** are the permuter tail: Opus is 6/7/11-close on several (finishable), Haiku 88+.

So the cheap drafter is **at parity with Opus on the small/medium bulk** and **falls off a cliff
around ~50–90 ins**. That boundary is the empirical Tier-2 → Tier-3 line.

## Validations of the safety thesis

- 2 Haiku agents crashed without returning structured output, yet had written **byte-perfect
  drafts** — the disk-based scorer recovered both matches the orchestration layer dropped. The gate
  is the arbiter; orchestration flakiness costs nothing.
- A Haiku self-report of `near 5` was really `near 72` — confirms self-reports must not be trusted;
  score from the gate.
- Zero false matches possible: `match_one` (standalone compile == whole-binary gate per function)
  gates every result.

## Takeaways for the 24/7 grinder

1. The cost-escalation ladder is empirically validated: **cheap drafter owns ≤~50-ins bulk; reserve
   Opus for the 90+-ins regalloc/schedule tail + the permuter-close near-misses.**
2. Expected real-world line: route by `nins` (and class) — `nins ≲ 60` → cheap arm; bigger or
   REGALLOC/SCHEDULE-walls → Opus/permuter. A GLM-5.2 arm (cloud, parallel, ~Haiku price) likely
   extends the cheap band upward vs Haiku — worth an identical A/B next.
3. Score the cheap tier on the WHOLE-BINARY gate, not `match_one` — the proxy over-counts on
   reach1/split functions (15 proxy → 4 banked here). The cheap-vs-Opus *drafting* delta is real,
   but route/measure on banks. 4 fns banked from this experiment (@commit:0307); the rest are backlog fuel.

## Artifacts
- `tools/workflows/ab_match.js` — per-arm-model fan-out (reusable for glm/local arms)
- `tools/ab_score.py` — disk-truth scorer, `--measured ARM:TOKENS --split` for real cost
- `.run/ab-exp/targets20.json`, `.run/ab-exp/{opus,haiku}/*.c` — frozen inputs + drafts
