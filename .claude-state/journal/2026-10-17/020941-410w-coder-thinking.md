---
ts: 2026-10-17T08:09:41.754Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aee27218559a6cb07
model: claude-opus-5-5[1m]
effort: medium
turnId: 924c6b58-d828-4a45-885e-7f9083635c03
---
The combined flag should handle both macro-carry row matching via normalized keys and offset, plus residue rows for uncovered P entries—so I should just run it as ledger-only and check the output.

I'm checking whether `--only` accepts function names in the help output, and it does. Since residue_sites matches via `matches_only(only, tu, fn)`, function names will give more precise matching than TU paths, so I'll use those.

Running `restruct --rung S --residue` scoped to the 4 functions, since it re-keys unbacked K sites via `macro_carry_rows` and adds RESIDUAL entries for the 3 uncovered P sites via `residue_rows` — touching only the ledger.
