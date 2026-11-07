---
ts: 2026-11-06T09:35:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_W5IlFwWuNWh9SQIbT1LD
---
The lreg dumps are identical in this region. The asm keepalive was optimized away by then (it was an empty asm; in the .lreg dump it's gone? but insn numbering 127 vs 125 suggests two extra insns in o... maybe the asm insns are elsewhere).

The difference must be in the .greg (global-alloc) dump or in the final sched. The store `*(u16*)(s0+0x188) = 0` — let me find it. It's a set to mem with const_int 392. Search the lreg region for "const_int 392" — only insn 59's sign_extend (the load). The store must be elsewhere. Let me search the whole function region for a movhi to 392.

Hmm, the store `*(u16 *)(s0 + 0x188) = 0;` might have been combined: `sh zero,392(s0)`. In the RTL, `(set (mem:HI (plus (reg 74) (392))) (const_int 0))`. Let me grep for "mem:HI" near 392.

The window I printed (67365-67610) covers only part. Let me grep the full function for "const_int 392".
