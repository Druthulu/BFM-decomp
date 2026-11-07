---
ts: 2026-11-06T10:08:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_neHcljDXqM6iFBNSC1iq
---
sched1 DOES model memory dependencies (memrefs_conflict_p). So a load can't move above a call (a call sets memrefs to "all memory" via `sched_analyze_insn`? let me check line 2183+ for CALL: it adds deps for hard regs, and for memory? Let me look at how a call is treated in terms of memrefs. Let me search for where calls clear memrefs or set them.

Actually, in sched.c, `sched_analyze_insn` for a CALL_INSN: the call itself has a `(clobber (mem:BLK ...))`? Let me check `sched_analyze_1/2` and the CALL handling around line 2183-2260.

Let me read that region fully.
