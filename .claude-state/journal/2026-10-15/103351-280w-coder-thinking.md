---
ts: 2026-10-15T16:33:51.341Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a86ec957c38e69a06
model: claude-opus-5-5[1m]
effort: medium
turnId: d2ceb926-9b47-40f5-bac5-5608e57c3046
---
I'm comparing residue_split, which pairs across all forms (P,I,X,M) in census order, against restamp_rows, which only pairs over the forms sites (P,X) since the pool keys include form and don't share across them—checking whether residue_match is invoked with the same site ordering in both cases.

The real divergence might be in how `check_casts_inputs()` computes latest versus `ledger_latest(load_ledger())`—maybe it filters differently. I should also check whether restamp's `--only ov_*` default matches residue_candidates, and whether a cause mismatch (like TNC) arises because tc's latest and rs's latest disagree on some sites.

Rather than keep reasoning abstractly, the best move is to actually run diag_left to inspect current state, then simulate restamp_rows in pure/dry-run mode (which is read-only) to see if it would alter those specific sites.
