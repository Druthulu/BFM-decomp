---
name: offline-tooling-first
description: Standing goal — push every COMPUTABLE step of the loop into deterministic, model-free tooling that runs at zero token cost on every future item; reserve the model and the search for what is genuinely not computable
metadata:
  type: feedback
---

When a recovery, diagnosis or integration step is computable, it belongs in a deterministic tool that runs with zero tokens on
every future draft — not in an agent prompt and not in a search.

**Why:** the measured economics kept pointing the same way on the source project. A fifty-agent wave once added a third of a
percent while deterministic recovery added nearly three points for about no tokens; the permuter's problem turned out to be
targeting, not a missing transform — most of its CPU was aimed at residuals a search provably cannot close, fixed for free by a
deterministic classifier. Every hour of agent drafting is spent once; every deterministic stage is spent once and paid forever.

**How to apply:** keep the two engines separate — deterministic recovery (declaration, arity and cast reconciliation, type
lifts, carve repairs: computable fixes, applied always, arbitrated by the byte gate) and search (the permuter, for register and
schedule permutations where the answer must be explored). Putting a computable fix into the search is a category error. When a
draft fails to bank, ask "is this residual computable?" before reaching for agents or the permuter; if yes, add a stage — and
check whether the logic already exists in another tool (one implementation, many callers). A stage that mutates shared state
undoes by snapshot-restore, never by an inverse transform, and is verified fleet-wide. Track the model-free fraction of the
work and make raising it the objective.
