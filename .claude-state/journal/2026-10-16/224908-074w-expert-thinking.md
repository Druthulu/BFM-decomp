---
ts: 2026-10-17T04:49:08.185Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9545e292ce6b8e9d
model: claude-opus-5-5[1m]
effort: medium
turnId: 82ef5817-c01e-4858-a424-9c300921422d
---
That residue-unused flag of 1 seems preexisting, likely from T5's change to md_MAIN_003 rather than something I introduced — but since config/lever_residue.tsv is in my files, I could just clean up that unused row trivially.

The calibration.json got overwritten with dirty uncommitted content lost; I'll note that as a finding since it's regenerable via --calibrate. The "one ANSI prototype" done-when condition still leaves K&R declarations across 188 overlay files, which is a real gap needing a follow-up pass across all binaries, mechanized rather than hand-edited.

For sequencing, I'm thinking c2 should cover the 8016BF50 remainder plus the three lying callees' decl unifications, while c3 handles the return-type lies and same-address copies.
