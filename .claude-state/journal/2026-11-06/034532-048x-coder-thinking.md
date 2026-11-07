---
ts: 2026-11-06T10:45:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jF5jMC9T8xSJNHGitkQo
---
Interesting! v_dw5 (do-while around S1) gives:
```
f34 lw v0,196
f38 nop
f3c ori v0,v0,2
f40 sw v0,196
f44 lw v0,32
```
And where's the S3 store (sw v1,88)? It got sunk below again (after lw v0,32?). Let me see more. Also the nop at f38 is the load-delay slot because the next insn (ori) uses v0.

So the block after the do-while contains S2, S3, S4, but sched1 scheduled the load then ori immediately (no room), and the address computation for S3 was... let me see the rest.

Let me print the following lines.
