---
ts: 2026-10-17T08:05:34.008Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab69a93f9cd77e107
model: claude-opus-5-5[1m]
effort: medium
turnId: 3b612e9d-1673-4d65-90d1-770672d83b37
---
T5 finished with zero uncovered items and a raw count of 116916, so something in T7's edits must have broken coverage by renaming or rewriting function bodies, causing the residue ledger's keys (likely based on body hash or line position) to no longer match — the 7 unbacked entries are probably CAST_* macros in those touched bodies whose ledger rows shifted. My fix is to rerun the residue check on the touched segments with the fuller set of forms (P, I, X, M) rather than the default.

But there are still 3 uncovered P entries, and check-residue reports zero uncovered, which suggests it may only be checking default forms like P and X. The census's check logic seems to differ from what I expect, so I want to understand how a macro gets marked "backed" — whether it's matched by a ledger row tied to a specific site. I'm going to read through the check_casts_verdict section, around lines 1995-2030, to see exactly how backing and site identification work, and to figure out a way to enumerate which sites are actually uncovered.

The gate was clean before T7, so T7's body rewrites introduced the 3 uncovered P sites and 7 unbacked macros by invalidating ledger keys. I'll check how sites are backed to identify and re-ledger the affected ones.
