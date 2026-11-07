---
ts: 2026-11-06T12:43:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vek5XX6JGyd9VRlbRDQm
---
Wait, my new4 inserts `do { ott = ott; } while (0);` BEFORE the ott assignment, but c4a had it after. Let me re-check: c4a = `m24=...; ott = ...; do { ott = ott; } while (0); mFF = ...;`. My new4 puts do-while before ott. That's wrong — it must be c4a's shape (after ott, before mFF). Let me fix.

Actually c4a: 
```
m24 = 0xFFFFFF;
ott = (u32 *)(idx * 4 + (s32)ot);
do { ott = ott; } while (0);
mFF = 0xFF000000;
```
Yes. Fix gen2.
