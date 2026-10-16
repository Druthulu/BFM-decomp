---
ts: 2026-10-16T11:43:02.970Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a877a45df9e0229a1
model: claude-opus-5-5[1m]
effort: medium
turnId: e31cc4d9-ecf8-46bb-9be1-1631c84ed118
---
I'm checking the ranking data: only 8,702 of 14,499 current struct_map names show up in the band file, leaving about 5.8k unranked—likely canonical entries or new ones. I'm wondering why these new hash types emerged after the freeze, and whether they trace back to canonical-covered sites in the post-T2 census.

One possibility is that T4's respelling of sites into members left remnant raw sites on a base that lost their union-find link, spawning fresh hashes as drift from existing band types. The T3 E1 detection logic and the residue_cause fallback to the body's latest canonical draw should have caught this, but maybe it didn't fire because the base in question wasn't the one drawn by that row — meaning this isn't just a cleanup sweep but a real decision point on a batch of new types.

I'm weighing whether to extend the tool with a new decision mode for post-freeze drift types — folding E1 matches to drawn canonical types, falling back to residual-by-layout-class, or defining new types outright — but that's a heavier change than this phase's scope, since defining types is supposed to be T3's job. Given the scale involved, I should actually measure how many distinct new types there are among the 7,128 overlay sites, whether their lineage is clearly E1, and their size distribution, since large types spanning many bodies would clearly need formal definitions. Given the ambiguity, flagging this as a question with a recommendation seems like the right move rather than trying to force a decision inside this sweep.

I should check whether the census file is tracked in git and look at its state at the T3 commit, checking if that particular struct type was already present before T4.
