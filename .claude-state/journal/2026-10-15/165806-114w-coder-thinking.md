---
ts: 2026-10-15T22:58:06.323Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I'm comparing Named8 and NamedB8, finding they share the same field layout but distinct meaningful signatures, so they split into separate camps rather than merging. Then I check Pair8's (hp, mp) signature against the naming pattern to see if "mp" counts as meaningful under the regex.

I'm working through Opaq8 and its unknown s16/s16/s32 fields, treating it as opaque with a new tier since no fields are named. I verify T_e1's and T_d2's layouts against the twin structures and canonical hash to confirm whether they match or diverge due to padding differences, then check the ledger_latest, has_addr, binary_of, and addr_of helper calls before confirming json is imported and running the selftest.
