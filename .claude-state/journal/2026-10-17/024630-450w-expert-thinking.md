---
ts: 2026-10-17T08:46:30.101Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
These prologues look like standard gcc output, which means these 13 routines need actual C bodies reconstructed via matching tools since no match was found before. This is the heaviest remaining work — each one likely requires m2c plus permuter passes, and I need to resolve each as either a matched C body or confirmed hand-written assembly.

I'm also thinking through coordination: running coders in parallel risks collisions since they'd share the same build tree and build/ directory, and concurrent make clean calls would create chaos. A worktree approach seems too risky since it would lack the gitignored extracted/ assets. Safer to run coders sequentially, starting with a re-judge pass to apply and refresh existing matches before diving into the harder routines.

Then I'm roughly sketching the sequence: first the re-judge pass across hundreds of bodies, then SHB macro consolidation, then the gte-clobber-steer respell tests, then the asm-body routine matching work (possibly split across two coders), followed by TSV rewrite and verification. I'm weighing whether to merge some of these steps to keep changes small, but conclude c4's scratch-compile matching work might be parallelizable with c1 if it doesn't conflict with delever's build baseline snapshot.
