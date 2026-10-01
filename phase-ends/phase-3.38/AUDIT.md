# Audit — 2026-09-29, phase 37.5 (previous 37)
## Verdicts
- (none) | leave | No `## Audit` / `### Carry audit` section exists in either PhaseEnd: `phase-ends/PhaseEnd_Phase37.5.md` is a 189-byte migration stub and `phase-ends/PhaseEnd_Phase37.md` is a PA2-format close; the deterministic half never ran because `tools/pa_ledger.py` is absent from this install (pa_version 3.11; only `tools/_credit.py` is present) and `.run/credit/` is empty, so there are no rows, no blended prices and no median-requests figure to judge from — insufficient in the tables; the next audit needs a ledger that covers a full PA3 phase (38).
## Tool candidates
- (none — no recurring reads measured; one occurrence of anything would be a `leave`)
## Rule candidates
- Rule candidate: a PhaseEnd closed without a `### Carry audit — phase <N>` section is audited as "no tables" and the auditor returns `blocked`, not a hand-measured substitute | from: this run (phase 37.5 / 37)
- harness: `pa_ledger.py audit --phase` is named by the auditor brief but not shipped in the 3.11 install here; the first PA3 phase (38) should run with the ledger present or the generation-start audit is a no-op | from: this run
