---
ts: 2026-10-17T08:47:10.797Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I'm seeing 584 rows across 443 bodies, with match_one isolated enough that the asm-body coder can run in parallel with c1's re-judging work in scratch, landing edits only after c1 commits. I'll launch c1 and c4 in parallel, with c4 reporting matched C drafts for later landing — though I need to double-check the rung E entries like c48p/c49p/c46p before finalizing.

Those 528 rows are propagated bodies via head-classes. For re-judging per site, using `--only` with function names risks matching unrelated bodies with the same name across TUs; nhash prefixes would be more precise for head classes, though the coder needs to verify this works correctly on a small sample before scaling up to all 443 bodies (~8s per TU should be manageable). After the re-judge pass, I also need to run gte_consolidate with --rejudge per the earlier note, then write up the approach explanation and brief for coder c1 — targeting residue rows marked "left by the author" or "not judged" where kind isn't asm-macro, gte-lever, or asm-body.

I'm listing out the concrete steps: write target rows to a tracked file, prove the delever flag actually draws exactly the intended bodies and judges each site individually before fanning out widely, run in small batches with gates and GTE re-consolidation after each, avoid editing the residue config since the expert owns it, and report back removed/remaining rows plus any bodies that couldn't be judged. Also need to remember the restore constraint — never use git checkout, only the proper delever restore mechanism.

For coder c4's scope on the asm-body routines, I'm thinking through how they should decide per-routine whether the code is compiler-generated (standard gcc 2.7.2 frame conventions, delay-slot filling) versus hand-written (noreorder blocks, nonstandard register use, GTE conventions) — and for the compiler-shaped ones, write equivalent C.

Then I'm iterating with match_one until matching, using m2c as a seed and permuter if needed, time-boxed per function, without touching src/ since another coder is running delever there — just delivering drafts and evidence for later landing. I note func_80184440.h is shared across multiple includers, and that main's asm-body functions in 800.c should also be supported by match_one via the asm subdirectory option.

c2 (macros) should run after c1, and c3 (gte) should run sequentially after c1 too, since it touches files tied to func_8013AD38 overlays that c1's delever might also draw from. I'll skip reading C0505 for now since coders can grep it themselves, and I should write the approach note before launching c1 and c4, checking that coder logs land at the expected phase-ends path.

I'm tackling this in four parts: re-testing the 584 untested lever rows one site at a time, consolidating SHB macros under ENGINE_SHB while expanding the nine one-off code macros at their use sites, canonicalizing the 9 gte-clobber-steer functions to gte_inline.h, and running the 13 asm-body routines (including func_8001E378) through a C match in scratch space in parallel with the re-judging—then regenerating the TSV last.
