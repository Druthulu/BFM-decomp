---
ts: 2026-10-17T12:00:37.975Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
Actually the ordering already matches target in sched1, so the hoist is happening at sched2, post-register-allocation. The real difference is register choice: my version puts the load into v1 (which is free to move), while the target uses v0, which is still busy from earlier stores and so gets blocked by anti-dependencies, keeping it in place.

That register choice traces back to local-alloc priority: the pseudo for t competes with the pseudo for the &D_801907C4 address, and whichever one has a shorter live range and fewer references wins v0 first. In the target, t gets v0; in mine, t gets v1 — so I need to adjust the live ranges or reference counts (possibly by reordering the source statements) so that t's priority flips and it claims v0 instead.

Working through the priority math though, the ratio still doesn't quite favor t over 81 by enough margin. Maybe the real fix is reordering sched1 so the load happens later, shortening t's effective live range relative to 81's.

Let me check b2's diff directly to see which register actually mismatches there.
