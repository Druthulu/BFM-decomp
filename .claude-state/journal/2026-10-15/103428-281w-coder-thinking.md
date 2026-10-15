---
ts: 2026-10-15T16:34:28.931Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a86ec957c38e69a06
model: claude-opus-5-5[1m]
effort: medium
turnId: d2ceb926-9b47-40f5-bac5-5608e57c3046
---
I want to probe the 800D3888 ov P sites stamped TNC but showing live non-TNC: I'll write a check that runs restamp_rows on the same bodies to see if it actually changes them, restricting the candidates to the flagged bodies and the P/X column pair.

Tracing through the logic, residue_split and restamp_rows pull from the same pooled queues keyed by form, so given identical inputs they should pick identical entries — meaning the pairing should be equivalent unless something about the live site's underlying data differs from what's in the pool.

So I'm now suspecting the real discrepancy is temporal: restamp ran before the census was regenerated in step 4 of c3, and that regeneration can change a site's canonical "type" field, which feeds directly into residue_cause. If the census snapshot changed after restamp but before the later diagnostic check, that would explain why some bodies labeled t3_S1/TNC appear untouched — their live cause computed now differs from what it was when restamp actually ran.

I want to verify this by rerunning restamp_rows directly against the current (post-regeneration) census for the ov P,X sites to see if they'd move now — if so, that confirms the fix is reordering steps so census regeneration happens before restamp, not some pairing bug in the residue_cause logic itself.
