---
ts: 2026-11-06T11:51:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1hpuNMRXsEazRfjAA2sO
---
Target has `nop` after `lhu v0,0(v0)` — load delay slots not filled (the lhu's result is used immediately: srl v0,v0,1 → nop). Mine fills the delay slot with other work (no nop) because the barriers are gone.

Target:
```
lui v0; lhu v0,0(v0); nop; srl v0,v0,1; sh v0,20(t1); sh v0,12(t1);
```
Mine:
```
lui a0; lhu a0,0(a0); negu v0,a0; srl a0,a0,1; sh a0,20(t1); sh a0,12(t1);
```
Hmm mine's structure differs more: mine has negu before srl on the same reg.

This is the classic "load-delay slot must stay nop" wall: `sched1-load-delay-fill` (in walls.txt: "sched1 fills a load-delay slot with an independent store group the target leaves as nop").

But wait: in the target there IS a barrier after the first two shs, and the loads happen in a specific order. Let me look at the full target disassembly for this function to understand.

Let me dump the target.
