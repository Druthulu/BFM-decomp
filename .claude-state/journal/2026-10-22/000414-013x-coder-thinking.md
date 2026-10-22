---
ts: 2026-10-22T06:04:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EolkSueZ0bBHouqNbJHS
---
Now I need the target disassembly of func_80191020. Let me find the baseline object and objdump it. The tool uses md.insns_from_object. Let me write a scratch script under .run/P40/T11/G14/func_.../ to dump the target asm.

Let me look at tools/masked_diff.py for the baseline path logic.

Simpler: find the built object for src/ov_SC06_018/ov_SC06_018_jr_8019059C.c in build/ and objdump it.
