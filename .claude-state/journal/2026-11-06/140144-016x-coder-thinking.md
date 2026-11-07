---
ts: 2026-11-06T21:01:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_b2An8eHpROZYLo0rlC5k
---
Function at lines 901-932 (body), ends at 932 with `}`. Note: orig.c matches src? The FRESH instruction says diff orig.c against the def in the current src file. orig.c has `void func_800CC4E8(void *a0) {` with no `register` on t? Let me diff. The src has `register s32 t __asm__("$2")`. orig.c also has it. Looks identical. Good.

Let me set up a dump. Create a scratch TU copy under my item dir with the function body replaced by my candidate, then run cc1_dumps_tu.sh.

I'll write a small python script under .run/P40/T11/W49x/ to do the splice (allowed, scratch under shard). Actually per rules, scripts not inline python. Fine, I'll write a small script.

Actually simpler: since the function is at a known location and the file is small (1089 lines), I can use python to read the TU, replace the function text between `void func_800CC4E8(void *a0) {` and the matching closing brace, and write the scratch TU. Let me write the script once and reuse for all items (but must be under my shard).

Let me write .run/P40/T11/W49x/splice.py: takes TU path, fn name, body file, out file. It finds the line starting with the signature (return type + name + "("), and finds the end by brace counting, then replaces with body.

Then run cc1_dumps_tu.sh on the out file with DUMP_ROOT in the item dir.

Let me do it.
