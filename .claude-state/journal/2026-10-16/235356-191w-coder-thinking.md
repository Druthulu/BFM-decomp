---
ts: 2026-10-17T05:53:56.112Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
The groups have different bodies, so they're not identical copies, which complicates using --all-defs since it requires every recipe to match exactly—applying it to the 123 group would also affect the other 8 non-matching defs, risking a whole-unit refusal. The alternative is handling definitions individually with --tu per def instead.

I need to time how long a single rung D invocation takes before committing to 131 of them, starting with a singleton test case. I also need to figure out how the shared caller header, which spans 136 TUs across many binaries, gets handled when using --tu scoping—since its reach exceeds any single binary's def_bins, it'll be left untouched by the tool and I'll likely need to manually set it to a K&R-style declaration myself.

Actually, I should just test by hand-editing the caller header plus one definition first and building that single binary to see if it even works, before committing to the full approach.
