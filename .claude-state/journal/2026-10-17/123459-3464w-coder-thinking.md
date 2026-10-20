---
ts: 2026-10-17T18:34:59.405Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm noticing store 72 is a leaf instruction ready early, while the other stores (82, 92, 103, 115) stay blocked—likely because the later loads at 125/135 carry a true dependency back on those stores, delaying their scheduling.

Checking the address forms: load 125 uses a plain (plus reg sym) form and disambiguates cleanly against store 72, but load 135's address collapses to a bare register, which find_symbolic_term can't resolve to a symbol—so it probably falls back to assuming a conflict rather than proving independence.

Still tracing memrefs_conflict_p logic...

When base addresses can't be matched directly, the fallback extracts symbolic terms from each side and compares those for equality. I'm now cross-referencing this against the actual sched.c trace, where reg119 is derived from reg118+reg116 and reg116 resolves to a known symbol via reg_known_value, trying to figure out whether reg119 compared against (plus r88 sym) would hit the symbolic-term fallback path.

This leads me to the real puzzle: the dependency trace shows store72 having no later dependents at T-2, implying load135 doesn't actually depend on it, even though the alias logic should flag a conflict given both are marked varying. I wonder if canon_rtx's reg_known_value substitution, or something about how pending dependency lists are limited, is causing this dependency to be dropped — so I'm trying an empirical approach instead, comparing against a case that scored correctly where the store used (plus r88 (const sym+4)).

Checking symmetry between the store's symbolic address and load125's address (r88 vs r111, no CONST_INT match), it seems find_symbolic_term pulls out the embedded symbol from inside the CONST, and since the two symbols differ, rtx_equal returns false — yet a conflict is still flagged empirically, meaning find_symbolic_term must return 0 for CONST terms, forcing a conservative conflict assumption. So to avoid the conflict, I'd need the load's address to not resolve to a symbolic term at all, perhaps by having its scaled index live inside a different const placement.

But then I'm second-guessing this: if the load address were just a bare register holding a symbol+index sum computed earlier, find_symbolic_term would return 0 and should trigger a conflict too — yet load135, which is exactly that bare-register form, apparently doesn't conflict with store72. That breaks my model, unless the dependency between store72 and load135 is coming from somewhere else entirely.

I'm now wondering if the scheduling order itself tells the story: store72 only becomes ready after load135 is scheduled, meaning there isn't actually a true dependence being tracked between them at all, so memrefs_conflict_p must be concluding no conflict despite the shared register. Maybe gcc 2.7.2's true_dependence logic handles this case differently than I assumed.

Rather than keep theorizing, I should just check the sched dump's LOG_LINKS for insn 135 directly to see what dependencies were actually recorded.
