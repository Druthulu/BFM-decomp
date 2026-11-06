---
ts: 2026-10-22T21:16:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_N808TrQMhEMNC6pfElWq
---
Lever-free: `m1 = mid` is kept in s1 (callee-saved) instead of rematerialised `addiu a0,sp,32`. And the stores of out.f0 to p2+2 are done... let me see the actual generated asm to understand. Let me generate the disassembly. Maybe use --keep and objdump. Let me check what tools exist: bin/dt.sh gives score+diff. Perhaps delever_search --try --keep prints candidate object path.

Let me look at the mine instructions fully. Use --keep and then objdump.
