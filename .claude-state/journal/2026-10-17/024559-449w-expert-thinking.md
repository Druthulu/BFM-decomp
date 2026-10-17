---
ts: 2026-10-17T08:45:59.868Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I'm planning to have coder c1 go through each of the 9 functions and test respelling every `_m` usage against the canonical gte_inline.h macro, checking per-site whether they match and recording evidence where they differ, while also making sure the 3 unjudged cases get properly judged. I also need to figure out how to surface the oracle verdict in the instrumentation.

After rewriting the TSV, rows without a delever ledger entry default to "not judged," so I need the residue writer to preserve judgments made by other instruments instead of overwriting them -- since the writer keeps existing rows verbatim when the (file,func,kind) key already exists, I'm thinking through a process where I regenerate fresh ledger-derived instrument data, then override any "not judged" rows that actually have T8 evidence (gte, macros, asm-body) with that evidence instead. I'm also considering whether I can just reuse delever's ledger mechanism for gte directly via its apply-body command.

For asm-body specifically, I should inspect a few examples in 800.c to understand whether these are C bodies matched elsewhere or genuinely hand-written assembly units.
