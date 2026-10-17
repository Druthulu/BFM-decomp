---
ts: 2026-10-17T08:48:25.733Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad48947f967e77fd9
model: claude-opus-5-5[1m]
effort: medium
turnId: 5652b206-5bd1-470d-af6a-d1e28be458c3
---
I'm realizing that matching by function name alone is risky since identical names can appear across multiple translation units or as aliases, pulling in unrelated bodies. Since I can't filter by (TU, function) pairs directly, and matching by TU path would just pull in everything from that unit, I'm weighing whether drawing in these extra non-target bodies is actually harmless given how they'd later get filtered.

Redrawn bodies would still get banked if byte-identical, which is the normal operation and gets confirmed by the R22 gate — the real issue is whether this creates stray ledger rows that shift instrument assignments in the residue, which seems tolerable but wasteful. I want to check if there's a `--plan` mode for delever to preview how many bodies get pulled in by name versus by exact target, and verify whether rejudged bodies actually get tested site-by-site including ones left by the original author. First step is building the target list, counting unique (file, func) pairs and flagging name collisions, then writing a scratch script under the run directory to test this.
