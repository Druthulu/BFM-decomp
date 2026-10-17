---
ts: 2026-10-17T16:45:46.753Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm correcting the end time to 10:45. Comparing this case to func_801497A8, I realize the register roles are reversed — here the target rematerializes while mine holds the address, so it's a different mechanism — and I'll spend about 10 more minutes investigating the launder in 8002B0B4.

Looking at case 13, the smallest residual is 79 for cp. I'm tracing how `cp` gets reused after the call to func_8002B08C, where cse keeps reusing cp's pseudo-register for D_80075CC0 across the call, making it callee-saved while the target rematerializes — and I'm trying to find a natural way to break that by having cp reassigned to the call's result afterward, which would invalidate the pseudo match and force rematerialization post-call.

I'm also checking a similar pattern for `m` in case 13, where m is tied to D_80075FC0 before a call to func_80016714, wondering if reassigning m to sym+16 afterward would similarly break cse's reuse of the old pointer value.
