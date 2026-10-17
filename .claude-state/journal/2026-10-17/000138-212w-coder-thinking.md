---
ts: 2026-10-17T06:01:38.425Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'll restrict overlay name lookups to files within the def's overlay directory, leaving decl resolution within def binaries for a later pass. Now I'm starting Batch 1 edits by sketching a small script that rewrites a function call on a given line to use new arguments, matching both direct calls and wrapped/cast call expressions.

I also need a companion script that simplifies K&R-style forward declarations into plain parameter-less prototypes, applying it uniformly even if the def is already K&R for consistency. Decls for functions in other overlays don't need touching since they belong to separate code, but I should handle function-pointer cast calls like `((void (*)(void))func)()` by converting them into plain calls with the correct arguments. Time to actually write this helper.
