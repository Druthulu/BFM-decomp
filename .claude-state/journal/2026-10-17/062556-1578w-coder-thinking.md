---
ts: 2026-10-17T12:25:56.951Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm tracing why r conflicts with v0: r is born in insn 50 right after a call result occupies v0, and since v is tied to v0 and still live when r is tested at insn 53, the two collide. This suggests the conflict would disappear if v were made global instead of local.

But locals get first pick of hard registers during local-alloc, so comparison temps claim v0 before globals are even assigned — yet the target code puts those compare temps in v1, with r itself in v0. That only makes sense if r isn't actually a pseudo being allocated at all, but rather the hard return-value register being set directly, likely through an if-conversion optimization in jump.c that rewrites a conditional return into a direct assignment to the return register.

So in the target, v0 must be live as a hard register before the reorg, meaning compare temps get bumped to v1 since local-alloc would otherwise greedily grab v0 for pseudos. That points to v0 being set via a real RTL assignment—either a hard-reg set from if-conversion's return-value handling, or something forcing it to stay occupied before the branches.

Tracing through: the call result copies into v0 (pseudo), v0 gets hard-set to 0 while that pseudo is still live, which blocks the combine_regs tie and forces the pseudo into v1. This looks like jump.c's if-conversion pattern for "x = b; if (cond) x = a" applied to a return register, likely around jump.c:699.
