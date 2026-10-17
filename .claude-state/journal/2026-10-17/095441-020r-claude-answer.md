---
ts: 2026-10-17T15:54:41.717Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 8fbb9e95-2d97-4372-a4c3-ae46dee1a5d2
usage: {input: 10, cacheRead: 240814, cacheWrite: 3891, output: 1713}
---

The revised 3.40 plan is approved and installed. This is what it changes:

- **Milestone.** Only the lever part changes, to the rule you picked: every lever is either removed or has a row naming the compiler behaviour that blocked it (its "wall"), and a tool checks that. T13's final check now runs that version.
- **T19 (new): the wall check.** No such check exists yet. The lever tool doesn't look inside residue rows today, and none of the 1,436 rows names a wall. T19 adds a list of named walls, `config/lever_walls.tsv`, and the check that enforces it. Then it maps the walls T11 records onto that list.
- **T20 (new): walls for the rows no wave touches.** About 864 rows were never part of the wave:
  - 607 rows in head-class lever families that weren't cracked;
  - 255 pins T7 found to be scratch registers;
  - 2 asm rows.

  T20 tags each with its wall, testing every class-wide tag on one sample first. Without T20, your rule would need a hand-written list of exceptions.
- **T18 (new): the 4 cast-check failures T8 left.** It waits until T11 finishes, so the two never edit the same file at once.
- **T13's dependencies** now include T17, T18 and T20. T17 had been missing from them.

T11's lever wave isn't affected, since it's the next task under its current wording.

One correction to the numbers I gave you earlier: T10's "2,342 to 2,309" counted lever sites covered by residue rows, not rows. The table actually holds 1,436 rows.

One question is still open in the picker. The generation plan's done-criteria still say the strict lever check must reach a true zero. I recommend changing that to the same "removed or walled" rule, so the generation's gate matches this phase.
