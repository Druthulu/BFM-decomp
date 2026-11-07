---
ts: 2026-11-06T14:12:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lZRoFHjTSBVYr0NXQ7Jc
---
Important: "When a reg is incremented, spilling it is worse, so we want to make that less likely" — reg_n_refs += loop_depth extra for an auto-increment! And REG_INC notes.

So `i++` as an increment gets an EXTRA ref (the increment counts twice: once as a use/set and once as an increment). That's why i has 14 and dst 11 — but wait, dst++ also increments. Hmm.

Actually this block (2300) is in a different context (probably `flow_analysis` handling of post-increment). Let me look at where this is. It's likely in `mark_used_regs` when it sees a REG_INC note? Hmm.

Anyway. Let me get the real numbers for c1. Set up the scratch TU and dump.

Actually, maybe an even simpler approach: let me look at what pseudo refs/live lengths c1 produces. Set up:

mkdir -p .run/P40/T11/O02x/_tu/ov_SC01_084 .run/P40/T11/O02x/_tu/shared
cp src/shared/engine_prelude.h .run/P40/T11/O02x/_tu/shared/
cp src/ov_SC01_084/ov_SC01_084_jr_8013C98C.c .run/P40/T11/O02x/_tu/ov_SC01_084/t.c

Then remove the two asm lines from t.c (use sed to delete lines containing `__asm__("" :: "r"`). But careful: the TU has the function at line 1308+. I'll edit t.c with a python script or sed.

Then DUMP_ROOT=... bash tools/cc1_dumps_tu.sh /abs/_tu/ov_SC01_084/t.c c1.

Let me do it. Use a scratch script under .run.

Actually, can I just cp and sed? sed -i is allowed? It's a file edit. Better to use Python for clarity. Let me write a small script.

Wait, but the TU's `#include "common.h"` — with -Iinclude that resolves. Good. And `-Isrc` etc.

Let me set up.
