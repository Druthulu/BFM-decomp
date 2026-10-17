---
ts: 2026-10-17T05:56:57.101Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm noticing some flagged READs are actually on registers already assigned as parameters, like in func_8017BF14 where arg0 is read via $4:c1. That suggests the pin might not indicate a missing parameter but rather a compiler quirk like register reuse, so I need to check each case individually rather than assume they're all genuine issues.

I'm cross-checking pin register index against declared parameter count across functions like 80136824, 8018C000, 8017F0AC, and 8014E048 to see where the pin position actually exceeds existing params, which would confirm a real missing parameter versus a false positive. I'm also flagging several WRITE rows as SCRATCH/out-of-scope since they look like classifier misfires rather than genuine missing-parameter cases.

Now I'm compiling a list of about 27 clear void-def functions (8001C9D0, 80029E30, 800CC024, and the rest) that I need to trace callers for, planning to run row.py on each with N=8 and read the output in chunks.
