---
ts: 2026-11-06T11:10:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qa1b1E8gtpF4WSvZowgX
---
Now the notes.md per item and the moves.md appends.

moves.md line format: `kind | func | MATCH: move / WALL tag — mechanism (G28x)`.

Let me append four lines:
```
barrier,pin | func_8018966C | MATCH — param-direct a0; do-while around the unkC4 load + empty do-while after the unk58 store (sched1 keeps sw 88 before the RMW) (G28x)
barrier,pin | func_80189F7C | MATCH — as func_8018966C + v1 = 0x4000 moved after the RMW (lreg gives v1 $3) (G28x)
barrier,pin | func_80187EA0 | MATCH — n as s16 (cross-jump copy survives) + empty do-while after the loop call (reorg fills beqz from target) + D_801151D0 1-field struct alias (G28x)
barrier,pin | func_8018B238 | MATCH — same as func_80187EA0: n s16, empty do-while after the loop call, D_801151D0 struct alias (G28x)
```

Let me append them.

Then notes.md for each item, then the log file phase-ends/current/logs/T11.cG28x.md.

Wait — the LOG path: `phase-ends/current/logs/T11.cG28x.md`. The brief says write it. But the general instruction says never read phase-ends/*/logs/. Writing is fine.

Also, per the constraint "write only under .run/P40/T11/G28x/ plus appends to .run/P40/T11/moves.md" — but the LOG instruction says write phase-ends/current/logs/T11.cG28x.md. The LOG line in the brief is explicit, so I'll write it.

Let me do the moves.md appends first (one command).
