---
ts: 2026-11-06T11:33:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0AdtvNeGEPuUNcNdzskz
---
The diff shows my code allocates temps t3..t6 etc, while target uses a0..a3, t0,t1,t2,v0,v1. The target apparently keeps the values in argument registers because the pins forced them there ($2..$5 = v0..a3). With pins removed, the compiler allocates differently.

The target uses the calling-convention registers as scratch (since this function takes no args, a0-a3, t0-t9, v0/v1 are all free). The original pins forced r2-r5 into $2..$5 (v0..a3) and the barrier forced ordering.

So to replicate, I need to reproduce that allocation naturally. The values r2..r5 are loaded from D_80120200..0C then stored to D_80126950..5C. The target order (from diff): mine uses v0,v1,a0,a1... target uses a2,a3,t0,t1,t2,v0,v1,a0,a1 for the last 10 stores.

Let me get the full target asm to understand. I need a way to see the target disassembly. Maybe there's a tool. Let me check .run/P40/T11/ for tgt files or a dump tool.

The worked example had a `tgt` file. Let me look at how it was produced. Maybe delever_search --keep prints candidate object; and target object is in build/.

Let me search the project for a tool that dumps target asm. Actually tools/cc1_dumps_tu.sh + tools/alloc_table.py for TU dumps. For a header, hdump.sh is the header pass dumps.

Let me check .run/P40/T10/hdump.sh.
