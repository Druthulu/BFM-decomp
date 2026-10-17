---
ts: 2026-10-17T05:14:23.643Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
I see c1's note that rung D with --callee scopes to around 130 TUs and can't edit calls, plus an --unalias option to restore alias-defined functions to their real names. I want to verify whether rung D actually rewrites declarations in includer TUs for shared headers, so I'll try a dry run on func_80161208 without --apply first to check its behavior.

Rung D likely requires --apply, so I need to check whether calibration is at HEAD before restructuring. Before going further I should write up the approach, but first let me check the built object files for func_80161208, 8012BD14, and 8012CBF4 to confirm whether v0 reflects a tail-called callee's return value -- these look like simple call-then-return patterns, so I need to check the definitions of func_8016130C, func_80013350, and func_8012CC88 to confirm.
