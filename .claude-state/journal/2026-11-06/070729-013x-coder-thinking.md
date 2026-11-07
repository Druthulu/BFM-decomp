---
ts: 2026-11-06T14:07:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HbgCWBhd6uYBSWIkXL2g
---
Let me now get the target assembly for the function. The build/ dir has the object. Let me disassemble the function from build. First, find the built object.

Actually, delever_search --try --keep prints the candidate object path. But I want the target. Let me find how the build stores objects. Let me search build for ov_SC01_084.

Actually, an easier route: use cc1 dumps on the real TU with the current body (score 0) to see the assembly and register allocation; that IS the target (byte-identical). So I can study what the keepalives produce. Then remove them and try real C to reproduce.

Let me generate a dump for the SC01 TU. DUMP_ROOT under my shard dir (absolute), and delete after reading.

Let me do:
DUMP_ROOT=/home/musashi/bfm-decomp/.run/P40/T11/O02x/_dump bash tools/cc1_dumps_tu.sh src/ov_SC01_084/ov_SC01_084_jr_8013C98C.c sc01 >/dev/null

But wait, disk cap: cc1 dumps go under my item dir and are deleted as soon as read. Fine. But note hdump.sh is for header items; cc1_dumps_tu.sh for TU dumps. My item is a TU item (not header). So use cc1_dumps_tu.sh directly.

The dump will be huge (whole TU). Let me dump, then extract the .s portion for func_8013D53C. Let me check output size first.

Actually the dump dir for a 2179-line TU could be a few MB. That's fine (<200MB).

Let me run it.
