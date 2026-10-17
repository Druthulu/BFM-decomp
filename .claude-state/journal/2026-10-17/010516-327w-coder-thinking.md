---
ts: 2026-10-17T07:05:16.359Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: 4cd9ff51-cad4-4178-8a67-d6699e5d25ed
---
I need to pass param_1 correctly. My earlier survey of calls truncated at 25 lines, so I should double-check other function names for missed plain calls — a compile check would catch "too few arguments" errors when the prototype is in scope, meaning passing runs imply no missed calls there. But calls still out of scope under the old K&R declaration would silently accept garbage arguments, so those need to stay as-is for now.

I'll fix the call at 8638 to pass param_1 explicitly, check SC07_002, commit, and rerun the rung D check, then see how the cascading signature runs went — it looks like the sequence stopped early after that fix due to an exit error, so I need to check whether other decls like 80157D20 and func_8018094C were affected, and look at the git log to confirm.
