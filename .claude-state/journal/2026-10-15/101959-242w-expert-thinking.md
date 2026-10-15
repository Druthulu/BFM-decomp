---
ts: 2026-10-15T16:19:59.554Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad22d9836f4993c3d
model: claude-opus-5-5[1m]
effort: high
turnId: 737a3070-27c3-47ed-b12e-9e964bb03b0a
---
I'm checking the top map names still stamped TNC, with 800D3888 and 8012D3B4 dominating the count, and trying to figure out why 8012D3B4 remains mostly TNC when restamping was only expected for P and X forms — it looks like these sites might sit in shared segments where the restamp logic behaved differently than in main.

I'm now puzzling over why 800D3888's 4,273 entries stay TNC even though the canonical mapping should resolve cleanly, and I suspect the issue is that the restamp only ran against P,X forms while these particular sites are I/M type, or that the stamped cause comes from an entry whose type field doesn't match what I'm checking against.

Maybe the discrepancy traces back to c4 already touching the residue state mid-run, or to a mismatch in how restamp pairs covered sites against ledger-order TNC entries versus how residue_split does it. I think the fastest path is to pick one specific 800D3888 covered site, compute its live cause directly, and trace which row it actually matches.
