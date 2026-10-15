---
ts: 2026-10-15T04:37:48.613Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
Checking the rc predicate: since uncovered, unbacked, and unledgered are all zero today, rc should evaluate to 0 right now, and the defline sites get excluded properly via residue_split so that doesn't interfere. I'm also noting the milestone needs no TNC appearing in the by-cause breakdown.

But the full milestone predicate also requires TNC absent and lying=0, and those fail today since TNC is at 291k and lying sits at 11 — so the milestone isn't actually met yet despite rc passing. I'm wary that TNC could be masked by re-stamping causes rather than genuinely fixed, since by-cause is just a ledger stamp that can go stale.

Looking at instrument 2 now — restruct with rung S and check-residue per segment shows uncovered at 0 today since everything's covered by Reading A, so this instrument's predicate doesn't fail on today's counts either, unless something in the TNC rows changes that. I want to grep through how restruct's check-residue actually works to confirm.
