---
ts: 2026-10-22T05:47:13.985Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a933331c6d154adc4
model: claude-opus-5-5[1m]
effort: medium
turnId: d25270b4-e42b-432f-9435-484b642c2966
---
I'm checking G07's results — it has 5 MATCH rows but 2 are actually NEEDS-DECL, so I need to exclude those from bank_rows rather than banking all MATCH rows indiscriminately. I also need to verify G14's func_80191020 entry against the results count, since G14 shows 6 MATCH plus 4 WALL totaling 10 against an expected 11.

Re-banking G14 should be idempotent since bank_swap just rewrites with the same content and WALL rows get rewritten identically, so I'm not too worried about rebanking already-banked rows, but I'll be safer and only bank G14b items in a later pass. I also want to check whether BANKING is still in place from before — B2 said T11 is paused and should never be removed — and figure out how pa_ext.py interacts with the ext lane to respect that hold.
