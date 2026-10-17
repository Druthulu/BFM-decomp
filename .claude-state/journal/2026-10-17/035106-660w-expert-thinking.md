---
ts: 2026-10-17T09:51:06.552Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a28afe298c346ad4e
model: claude-opus-5-5[1m]
effort: medium
turnId: 78408b4b-baed-477f-9c59-797589f1b95e
---
The pin count shift from 1689 to 1711 seems to come from macro expansion adding pin lines at call sites, affecting roughly 48 ledger rows. I'm checking whether the lone remaining prelude definition under ENGINE_SHB needs its own residue row, or if --write-resid already handles that case.

Looking ahead, I still need to land twelve asm-body drafts, tackle func_80020F34, rewrite the TSV, and write the final summary. For func_80020F34, since the Makefile likely doesn't support standalone .s files, I'm checking whether it should stay as an inline asm body in C with a residue row marking it as hand-written evidence -- so I want to look at how that function is currently handled and what the Makefile actually supports.
