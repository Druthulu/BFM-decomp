---
ts: 2026-10-15T16:20:39.189Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad22d9836f4993c3d
model: claude-opus-5-5[1m]
effort: high
turnId: 737a3070-27c3-47ed-b12e-9e964bb03b0a
---
I'm noticing that even restamped rows (t2_rst_ov) still carry TNC stamps that don't match the live cause, which suggests the restamp process is mispairing entries — likely when a body has multiple RESIDUAL entries sharing a key, the restamp pairing logic and the residue_split pairing (which follows ledger order) can assign different entries to the same covered site.

Looking closer, I suspect my --forms P,X choice deliberately excluded I/M-form entries from restamping to avoid disturbing GADDR/GLOBAL long-tail sites, but that means I/M entries belonging to top-75 types weren't restamped even though they should've been for the done-when criteria. I don't see an easy way to restrict restamping by type rather than form, so I'm weighing whether restamping GADDR/GLOBAL for the long tail is actually the more honest fix here.

I'm also puzzled by the t2_res_ov rows carrying stale TNC labels that contradict the residual table — it seems the residue step may have merged in copies of old entries that kept their outdated cause, and restamping afterward via t2_rst_ov might not have overwritten those copied rows if it only appended a new latest row rather than correcting the merged ones.

This looks like a pairing bug: restamp likely pairs covered sites against only the latest row per body, while residue_split's annotation reads across all rows in ledger order, so the two processes disagree on which entry to treat as authoritative. Since c4 is already editing the relevant restruct.py file, I should flag this to c4 rather than take it on myself, but first I want to check the residue_split cause annotation logic in type_census.py to describe the bug precisely.
