---
ts: 2026-10-15T16:16:59.096Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a86ec957c38e69a06
model: claude-opus-5-5[1m]
effort: medium
turnId: d2ceb926-9b47-40f5-bac5-5608e57c3046
---
I'm planning the implementation: adding new normalization helpers after s_base_norm, extending the macro row matcher with a nested-pointer fallback, creating a macro_carry_rows function to call from residue(), and adding a corresponding selftest case alongside the existing md test.

For purity, I want macro_carry_rows to accept a sites list and optional texts rather than reading files directly, since the selftest fixtures live under the repo's .run directory. I need to check whether file_view's census sites already carry the text needed, or whether I'll need to read it from disk separately.
