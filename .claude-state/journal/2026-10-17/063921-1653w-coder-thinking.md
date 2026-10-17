---
ts: 2026-10-17T12:39:21.204Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
This is a contrived scenario where a label would need to survive across cse1, a loop, and jump before cse2, dying only after cse2 folds a branch — essentially requiring cse2 to know something cse1 didn't, after the loop runs. I'm now checking whether loop notes get removed between cse2 and scheduling, looking at flow.c's handling of loop depth and whether jump.c deletes certain NOTE_INSN types.

That note pattern matches loop rotation behavior. I'm now digging into how scheduling treats loop notes — specifically whether notes sitting mid-block (rather than at boundaries) create barriers, since a do-while(0) loop stripped of its jump/label by jump optimization would leave loop notes stranded inside a block. I'm also checking sched_analyze's handling of CALL_INSNs, since calls that set hard registers need special treatment to prevent other insns from moving across them.
