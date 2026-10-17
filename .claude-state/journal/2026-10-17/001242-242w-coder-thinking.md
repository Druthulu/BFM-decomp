---
ts: 2026-10-17T06:12:42.289Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
At 1.5 minutes per run, running --tu across all 123 files would take about three hours, so I'm looking for a faster path. I'm wondering whether --all-defs combined with --map-data could work for the 8 copies that share the same D_ symbol despite having different pin variants.

Running the 8 odd copies first via --tu would take roughly 12 minutes, but then --all-defs would still try to overwrite them with the 123-body once it sees "already defines," since that skip logic only applies when body_text is None — so they'd end up refused for mismatching bytes. I'm also considering whether restruct supports parallel runs at all, given the ledger and source-clean checks, and recalling how T6 handled a handful of identical-address copies easily since there were so few. The real issue is that the 123-group is only identical after normalizing D_, while the 8 others diverge in actual code — different pin assignments — so I can't just treat them the same way.

The 8 variants use a different register-pinned declaration than the 123's literal hex value, which likely produces genuinely different compiled bytes since the pin was functionally necessary. That puts the total cost around 131 runs at roughly 1.5 minutes each, nearly 3.3 hours — doable as a background task, but each run dirties the source again, triggering the "commit before next run" check, which conflicts with the one-commit-per-green-batch rule. I need to check whether restruct tracks an in-flight batch state that would let me continue applying the same label across runs without a fresh commit each time.
