---
ts: 2026-11-06T12:47:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7fgaFWRlmD0BWG9l4y1y
---
Load delay is in mips.c/mips.md as an attribute? Line 121 says "can't describe load/fcmp/xfer delay slots here". So load delay handled elsewhere: in sched.c? Let's grep for "mips" specific... Actually GCC 2.7.2 handles load delay via `TARGET_SCHED_...`? Hmm. In 2.7.2, sched.c has `#ifdef MD_SCHED_...`. Let me look at how the "nop" after a load gets inserted: the assembler inserts it? No — the compiler emits `nop` in the delay slot (there are nops in the output). In 2.7.2 mips, the load-delay nop is inserted by `mips.c` in the `ASM_OUTPUT`? Actually there's `dbr_schedule` (reorg.c) which handles branch delays only.

Let me grep mips.c for "nop" insertion after loads.
