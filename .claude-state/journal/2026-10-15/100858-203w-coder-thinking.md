---
ts: 2026-10-15T16:08:58.580Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a39b699a467f2c7b2
model: claude-opus-5-5[1m]
effort: medium
turnId: 222ded7f-48dd-426b-b712-eaf41c6db60b
---
I'm trying to figure out why the 7 macro sites classify the nested base as a parameter - it seems the T2 rewrite turned the raw pointer dereference into a field access expression, which changed how the census identifies the base, now reading it as param a0 with offset 24.

This looks like a tool-level gap: when a body's nested base gets rewritten, the rung-S row doesn't preserve KEPT entries for surviving CAST_* macro sites under the new base spelling, and the residue path only handles raw P/I/X/M forms, not macros. Since fixing this requires editing tools or the ledger — both out of scope — I don't see a clean option, so I'll need to flag this back to the expert as blocked, after committing and logging everything else that's green, noting check-casts still returns rc 1.

Before giving up though, let me check if a redraw pass on those three bodies might force restruct to re-derive KEPT entries for the macro sites under the new spelling, since it has recorded KEPT for similar non-struct param entries elsewhere.

But even then, since the same tool ran in the same state, rerunning likely gives an identical result — this really is a base-normalisation mismatch between the two tools, a classic tools-fix rather than something worth chasing further. I'll move on to tallying the batch metrics: counts for batches, walls, bodies drawn, and site classifications across MEMBER, KEPT, and RESIDUA.

I need to break down residual causes from the t2_* ledger rows — let me write a script to do that.

The root cause: 7 CAST_SIGN/CAST_NONSTRUCT sites lost their KEPT backing because the T2 draw re-spelled nested base expressions as member accesses, and the new latest rows don't carry a matching KEPT entry—fixing this requires a tools or ledger change outside this brief's scope. I'll collect the metrics, commit, and flag this as an open question.
