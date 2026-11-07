---
ts: 2026-11-06T01:39:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KmfE9JnmGJlqfEPbzi6d
---
The .rtl dump is after the first jump pass (jump_optimize at 2827)? The dump -dr is "after jump"? Actually -dr = dump after RTL generation? No: -dr dumps after "jump" ... The file .rtl is from -dr which is "dump after reload"? Let me recall gcc -d flags: -dr = dump after RTL generation? No: -d r = "jump" ... gcc 2.7.2 -dr: r = jump_optimize? Actually the flags: d = dump; letters: r=rtl, s=cse, j=jump, l=loop, g=global alloc, f=flow, c=combine, S=cse2, L=lreg, R=greg, t=sched, J=jump2, d=dbr. So -dr = "dump after RTL generation" (rtl dump). And here the jump at 368 to label 374 exists at RTL generation, right after the store. Good — the return DOES emit a jump.

Now check the .jump dump (after first jump pass) for vA: does the jump survive? And .jump2.
