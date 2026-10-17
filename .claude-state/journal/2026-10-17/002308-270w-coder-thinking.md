---
ts: 2026-10-17T06:23:08.449Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
One function at 8018C730 appears to be referenced only as a callback, with no direct calls. For 80180ED4, I'm checking the caller func_8017E100, which sets a0 to sequential values (1,2,3) before invoking it, suggesting an actual integer argument. I'm also tracing the many callers of 80182334 to see which pass a genuine arg0 versus plain calls.

Checking 80182998's callers across different translation units, I see the parameter is a void pointer copied from a register, and multiple callers pass pointer-typed arguments that need casting from s32. For 8017F258, the param is a u8 pointer copied locally, with callers like 80180AE8 passing void* args directly. I want to look at 8017E100 next and then proceed with a batch of caller edits.
