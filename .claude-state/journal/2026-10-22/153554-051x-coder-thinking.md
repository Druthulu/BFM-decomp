---
ts: 2026-10-22T21:35:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yZuS6mrKDFd5tvHo5lP0
---
Item 2: func_8017F898 — a memory-clobber barrier at function entry. Mechanism per the comment: sched2's potential_hazard rule promotes `sw $ra` over the ALU candidates and sinks it; the clobber makes sw $ra only ready after the load.

Lever-free: need plain C that keeps `sw $ra` in the prologue. The barrier is at entry. What does it do? It creates a memory dependence so that sched2 doesn't sink sw ra.

Let me first score the lever-free body (drop the asm) and see the residual.

Let me extract the function (4276-4298) as orig.c and strip the asm line.

Note: `s32 s0 = arg0;` — the name s0 is a variable name (not a register). Hmm, "no `register` vars" — it's fine.

Let's go.
