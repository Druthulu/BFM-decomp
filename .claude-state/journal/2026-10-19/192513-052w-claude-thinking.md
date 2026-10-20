---
ts: 2026-10-20T01:25:13.195Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: 88ab4e68-eeae-4ee3-b16f-c731ccb14733
---
I'm noticing that the T1 snapshot's content hash matches the first 269,013 lines of the live ledger exactly, which means the p37 restructuring snapshot from Oct 14 can be verified and recovered just by taking a head of the live ledger up to that line count and checking it against the known sha256 prefix.

For the delever snapshot, same approach: its content hash should match the first 32,633 lines of the live delever ledger, so I'll test that. The pre-T4 snapshot has 302,004 lines but no recorded hash, so I can only check consistency, not cryptographically verify it — still worth confirming since rebuilding the snapshots is cheap and writing them into .run/keep won't cause issues since T13 refreshes that directory anyway. Let me go ahead and verify these hashes.
