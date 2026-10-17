---
ts: 2026-10-17T10:19:27.199Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a28afe298c346ad4e
model: claude-opus-5-5[1m]
effort: medium
turnId: 19fadc38-27f9-43cf-8450-c53af22fd50b
---
I notice those rows had the "T7 refused" instrument, and stripping lost those texts since hand-written T7 instruments got replaced by ledger-derived text — which is more truthful anyway. Now I need to regenerate the TSV with strip and write so the 4 rows show the oracle differing.

Then I'll hand-fix func_80020F34, ENGINE_SHB, and func_8001BBBC, which has junk compile-error text — checking that ledger entry shows a compile error at t8_r2, derived from 'why'. Rather than guess at the verdict, I'll grep the ledger tail to see what's actually there.
