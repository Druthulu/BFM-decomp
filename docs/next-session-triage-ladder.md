# NEXT SESSION — build the TRIAGE LADDER (spec, written S68 with full context)

> Written deliberately so a session with NONE of S68's context can build this. The companion tool,
> `tools/neighbor_ref.py` (retrieval), is already BUILT and committed — this is the other half.

## What it is

One deterministic, local, ZERO-TOKEN pass that sits **between `wave_args` and the drafting agent**
and answers *"does this target need an agent at all?"* before one is spent.

    draw -> cards -> packs -> wave_args -> [TRIAGE LADDER] -> draft -> gate -> bank
                                                 |
                                 banked / wall / already-matches / one-extern-away
                                       -> skip the agent, go straight to the gate

## It is ~70% already built

`tools/residual_rules_b.py` exists and works. Built by a Fable agent in S68 as a head-to-head
experiment against `tools/residual_rules.py` (mine). Scored on a HELD-OUT set of 113 drafts
(`.run/S68_rules_eval_set.json`), results in `.run/rules_b/eval_results.jsonl`:

| | mine | residual_rules_b |
|---|---|---|
| classified | 85/113 | **113/113** |
| errored | 28 | **0** |
| any rule fired | 18% | **88%** |
| certain/high | 1% | **63%** |
| pure residual-SHAPE rules only | ~1% | **1.8%** |

**Read that last row carefully — it is the most important number in the experiment.** Two
independent implementations converged at ~1-2% on pure cookbook-shape rules. The shape tier's
ceiling is the POPULATION, not the implementation: surgical single-mechanism residuals live at the
END of escalations, not in first-pass wave output. So the shape tier belongs in ESCALATION loops;
the ladder's value is everything ABOVE it.

Its tiers, with S68 held-out firing counts:
`ALREADY-BANKED 28` · `INTEG-STANDALONE-MATCH 22` · `NOCOMPILE-UNDECLARED-MEASURED 21` ·
`NOCOMPILE-UNDECLARED-FIXED 10` · `NOCOMPILE-UNDECLARED 9` · `NOCOMPILE 5` ·
`R372-COPY-CAPTURE 3` · `REDRAFT-SIZE-MISMATCH 2` · `RPOL-KLASS 1` · `W332-MASPSX-WALL 1`

## THE FREE BANKS IT ALREADY FOUND — do this first, it is the immediate payoff

**10 drafts are byte-MATCHES once a missing `extern` derived from the target's own `.s` is added.
I verified all 10 myself with `match_one`: 10 of 10 `match`, closeness 0.** Patched drafts are at
`.run/rules_b/<case>/autodecl.c`:

    ov_SC01_080:func_8017D72C   ov_SC04_010:func_8017D6CC   ov_SC07_010:func_80180E68
    md_SC07_004:func_801A3D60   ov_SC01_077:func_80185E68   ov_SC03_105:func_801829CC
    ov_SC03_105:func_80182BD8   ov_SC06_022:func_8017CDE4   ov_SC07_000:func_8017E1BC
    ov_SC07_002:func_80185FB0

Plus **22 more classified INTEG-STANDALONE-MATCH** (already match standalone, misfiled as failures)
— gate those too. Gate with `tools/gater_lane.py --extra BINARY:PATH`, and remember main routes
IN-TREE via harvest_verify (its worktree cannot link).

## What is left to build

1. **Wire it into the wave pipeline** between `wave_args` and the draft launch; emit a per-target
   verdict the card renderer consumes.
2. **Put it in front of every ESCALATION.** S68 escalated `main/func_8005D734` to Fable at closeness
   8 — it is a §332 toolchain wall and the escalation could never have succeeded. The wall tier
   refuses it in under a second. That was pure waste and it was a MISSING CHECK, not a judgement
   failure.
3. **HARDEN — and this is the part that matters most.** The failure modes are ASYMMETRIC: a false
   *"needs an agent"* costs one draft; a false ***"skip — already banked"* silently drops a bankable
   function, possibly forever.** That is the worst failure mode in this codebase and the same shape
   as `seed_ref` offering dead text as bankable earlier in S68.
   **Acceptance test (R39), not optional polish:** run the ladder over EVERY function that has ever
   banked and assert **ZERO** false skips. Also give it an R32 coverage assertion over its own
   denominator.
4. **Re-run it** — the S68 eval set is stale by construction (28 of its 113 were banked mid-session,
   which is exactly why my version errored on 28: `corpus.stubs()` no longer contained them and the
   resolver raised IndexError).

## Predictions, so this can be judged rather than believed

* ~30% of a fresh wave skips the drafting agent (the 28 stale is an artifact of this set's age; the
  durable tiers are the 22 standalone + 10 autodecl + walls).
* ZERO functions falsely skipped. If any are, the ladder is worse than useless.

## Related, same session

* `tools/neighbor_ref.py` — BUILT. Ranks matched functions as worked examples; validated on
  `main/func_80024054`, whose top 3 neighbours were all matched in S68 in the same TU.
* `tools/wall_sweep.py` — BUILT. `--emit-exclude` feeds `draw_waves --exclude`. 10 fns / 1,027 ins.
* `docs/accelerators.md` #15 — the differential-oracle harness (the day-one tool).
* `docs/generic-decomp-package.md` — what a NEW decomp inherits.
