---
ts: 2026-10-21T23:32:23.663Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac5e83e17a550252a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2bc1963a-50f7-4587-ab9d-0d1677f52c5b
---
I'm checking whether C0505 already banks the both-arms tie and the s16 width variation, treating the 16-bit result approach as essentially covered under that same entry. The derived pointer case looks related but seems to use a different mechanism, reusing a later local instead.

Continuing the comparison, I'm seeing that call-into-&&-test resembles line 32's pattern, and the keepalive returns near lines 40-46 look like they match the "real s32 return replaces keepalive" case. I'm noting that short loop counters and the two unconfirmed T10 items (in-place RMW and %2^k) still need separate tracking.

So I'm planning three new ledger entries: one bundling the T9/T10 additions to C0505 (RMW, %2^k, derived pointer, loop counter drop, && call variant), one for the residue ledger refresh combining T2:34 and T7:22 under C0528, and I'm starting to sketch a third entry about map-type handling.

I'm now folding in the hash-name instability finding (T2:36/T4:25) and the capped census summary JSONs (T3:37, with the specific limits for dup classes, top_types, layout, and conflicts), then merging the band-twins-become-SHARED observation (T5:29) into that same third entry as "a rung-S sweep reshapes the map-type set." I'm also running through the rule-out list — tool bugs, ops facts, and items already banked under C0505/C0510-C0528 — before deciding to double-check C0505 lines 28-49 to confirm the exact matches.
