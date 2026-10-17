---
ts: 2026-10-17T06:32:45.896Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: ec261558-e851-4858-881a-bafc3737e5d1
---
Since callers already pass param_1 by value, I'm reasoning that func_8015410C should take a single s32 parameter matching its shared header definition, so I'm planning to hand-edit the header body so it calls func_80151664 with that argument, treating this as an interim fix before cleaning up the declarations properly.

This K&R approach also applies to similar cascading functions like func_80169228 and func_80157D20, which each touch over a thousand files, so I'm expecting these to be slow background rung D runs. I'm also noting func_8017D098 follows the same pattern across three translation units, where its caller func_8017CEF4 passes the argument the same way.

I'm now checking whether func_80151664's other callers across different overlays are actually sharing the same header definition or are distinct per-overlay functions, since some use cast-call syntax that already passes the real argument.

Then for func_80169228 I confirm no cascade is needed since its caller already supplies the arg, and I work out the cascade for func_80157D20 into func_80149CB4 based on matching parameter types across callers. This settles batch 3 (80169228, 80151664 with its cascades, and 80157D20 with its cascade), and I move into batch 4 starting with 80182998, 80182334, and 8017F258.

Actually batch 4 looks smaller, so I decide to tackle it first while waiting on background work, and begin pre-examining the callers of 80181B14, 8017E210, and 8017F0AC.
