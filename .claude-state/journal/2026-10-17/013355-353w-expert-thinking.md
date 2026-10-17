---
ts: 2026-10-17T07:33:55.044Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab508551f6c1ff968
model: claude-opus-5-5[1m]
effort: medium
turnId: bbcb7c47-120d-43fb-91c6-ce7ec681d3cb
---
I'm looking at function 80038308, where arg0 is pinned as a 4-byte read before being written, but the declared parameter is an unused `s16 a0`. This looks like the pin is reading the parameter as a32 without the sign extension the declaration implies, so I'm considering whether to change the function signature to take an a32 argument directly.

For the rest: 80038698, 801896EC, 80180390, 8017D040, and 8012A860 all look like SCRATCH cases since their variables get written before use, while 8017D81C's z parameter needs more context to determine if it's truly scratch. So my priority is testing the fix on 80038308 and then double-checking z's usage in 8017D81C.
