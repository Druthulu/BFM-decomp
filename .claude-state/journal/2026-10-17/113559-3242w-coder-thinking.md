---
ts: 2026-10-17T17:35:59.170Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm noticing source order barely matters since sched1 decides placement by priority, which explains why mlo appears early at instruction 74 while mhi comes later at 109 -- likely because mlo needs two instructions (lui+ori) for its value while mhi only needs one (lui).

I'm wondering if this is a stale-reference count issue: maybe mlo gets reused in a way where combine or cse folds a redundant mask operation like `(X & mlo) & mlo` after flow has already counted references, leaving the ref count artificially inflated. cse typically wouldn't simplify `(and (and X r) r)` since it doesn't fold repeated masking with a non-immediate constant, so this folding would have to happen later, at the combine stage after flow's analysis.

I'm also considering whether mhi's reference count can't be adjusted downward since its earliest use is already in HEAD1, and instead looking at how mlo is "born" — since loading it may require two instructions (lui then ori), meaning the pseudo is set twice before its first real use.

I'm checking q's address load (also a two-instruction lui/addiu sequence), and working through the arithmetic of priority values to see if tweaking mlo's reference count could push its priority above q's and mhi's, trying to find a combination where mlo comes first, then q, then mhi in scheduling order — but the numbers aren't quite lining up since raising mlo's refs pushes it ahead of q but also knocks mhi behind q incorrectly.

This three-way priority ordering is proving tricky and might need a structural change instead — like having q also referenced earlier (used in HEAD1 the way it's used in HEADN), which would bump its reference count and birth point, potentially altering how the address computation compiles for that line.

I'm setting up the quantity priority ordering so mhi comes first, then q, then mlo, with mlo's loading chain scheduled first to maximize its live range — aiming for a best score of 36.
