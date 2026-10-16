---
ts: 2026-10-16T00:06:03.499Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I'm puzzled why 106 rows exist in the recheck that weren't in struct_twins' original doc, since dup classes should be determined purely by definitions, not by run-to-run variance—unless something about the first check-structs run's data differed in a way I haven't accounted for yet.

I'm wondering if this is a formatting discrepancy rather than real nondeterminism, like an lhash carrying an ":opaque" suffix marking a tier-3 split that doesn't match a plain-named entry already in the doc, so I should grep for the plain version to confirm.
