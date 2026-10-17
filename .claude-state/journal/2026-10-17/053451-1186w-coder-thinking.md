---
ts: 2026-10-17T11:34:51.237Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm tracing the register assignment requirements: k needs to end up in a3, m in v1 without being coalesced with k, and j in a2, based on how the target code reuses v1 after the copy.

With a plain copy, m likely dies at the copy point (naturally or via optimize_reg_copy_1), triggering global's expand_preferences to share preferences between m and k. If k gets an a3 preference from being used as a call argument, m could inherit that preference too and wrongly coalesce into a3 — so I need to check how expand_preferences in global.c actually handles this sharing to understand why m still ends up in v1 instead.
