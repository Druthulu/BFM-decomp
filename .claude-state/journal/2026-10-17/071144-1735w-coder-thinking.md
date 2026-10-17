---
ts: 2026-10-17T13:11:44.567Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a68ccc2589980bbb7
model: claude-opus-5-5[1m]
effort: medium
turnId: d2c7b2f5-b16a-49db-83ae-0a0f8f0ba379
---
I'm checking that other translation units still reference the original extern declaration safely, then planning w4b.py: inserting the typedef only in the definition TU, swapping the extern declarations there, and rewriting callers using the cast approach since it should preserve identical binary behavior.

Calling through a cast function pointer is already proven safe since the definition itself uses that exact pattern for func_8012B77C, and GCC folds it to a direct call — it's not some kind of pointer pinning trick, just the same style already present in the source. The hidden-pointer argument passed as a0 stays identical under the cast too, so this approach should be safe to apply.
