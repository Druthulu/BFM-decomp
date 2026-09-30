### P33 E6 (S88, 2026-09-07) — `docs/matching-drafter-pipeline.md`, the drafter write-up
- Distilled from `docs/gen2-mips-matching-model.md` (every measurement, 2026-06-29 → 07-08) and
  `docs/community-matching-model-plan.md` (the parked community release) with the drafting loops of cookbook §12 / §500:
  §1 why a specialist is safe under the byte gate, §2 the toolchain-agnostic pipeline (all 12 tools verified present),
  §3 the measured arc as one table (stock floor ~0; v1 39/41 trivial / 0/34 non-trivial; corpus-v2 85% on 6–15 ins;
  the 0/222 that was two harness bugs; 7/15 on open stubs; 0/15 on shared code → corpus-v3 with the 1,623 macro bodies →
  57.5% held-out, ~352 production banks, fleet +502 fns at $0; `bulk_harvest` 65% at 0.4 s/fn gate; GLM5.2 10/18 bodies
  but 3/18 banks — the def-side wall; v4 discarded; the 4.8× Haiku A/B), §4 the portable lessons, §5 hardware, §6 a
  five-step recipe, §7 what is published (the scripts, this doc) and what is NOT (the ROM-derived pair dataset
  `datasets/match_pairs/` and the adapter weights `models/` — both gitignored, confirmed with `git check-ignore`; their
  release is a Gen3 licensing decision). The 2026-07-08 decision-log entry ("the local-7B tier is capacity-bound and off
  the endgame critical path") is the cited strategic conclusion. In `doc_links`' default set; this row.


