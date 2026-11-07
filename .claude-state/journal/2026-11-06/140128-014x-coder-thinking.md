---
ts: 2026-11-06T21:01:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_87j07CvDDo7bagoYCg9d
---
With `--keep`, I can get the scratch source path (it prints the object path). Actually the scratch src is in `.run/score/<alias>__<fn>/p<pid>/`. The object is `cand.o` next to the source. Then I can run cc1_dumps_tu.sh on the scratch source file (it accepts a .c file). But the scratch src sits in a scratch_dir whose `../shared` doesn't exist; the cpp line adds -I for the extra. cc1_dumps_tu.sh adds -Isrc/shared and -Isrc so `#include "../shared/..."` from src/md_MAIN_034/md_MAIN_034.c... but the scratch copy is at .run/score/... so "../shared" fails. Hmm. The tool comment says a copied TU's own directory isn't one. But cc1_dumps_tu.sh with a .c file uses `-I"$(dirname $tc)"` and `-Isrc/shared` and `-Isrc`. `../shared` from .run/score/x/ resolves to .run/score/shared — missing. So I'd need the scratch copy placed elsewhere.

Alternative: manually splice my body into a copy of the TU under my item dir, and run cc1_dumps_tu.sh on that file. Since the copy's dirname would be my item dir, `#include "../shared/..."` resolves relative to the *file's* dir? No — `#include "../shared/x.h"` resolves relative to the including file's directory, which is my item dir. So `../shared` = .run/P40/T11/W49x/shared — missing. Unless the TU uses `#include "shared/..."` with -Isrc. Let me check the TU's includes.

Actually, simpler: create a scratch dir that mirrors the src layout: .run/P40/T11/W49x/dump/md_MAIN_034/ ... with ../shared -> .run/P40/T11/W49x/dump/shared. I could symlink shared there. But writes must be under my shard dir — fine.

Hmm, this is getting heavy. Maybe first try more C experiments; dumps only if needed. The residual is a register swap; the alloc table would tell me priorities.

Let me do experiments. But let me think about which lever is likely: The known MATCH at moves.md line 6: "pin | func_80184F18 | MATCH — u16 t (HImode copy escapes cse equiv) + u = arg2 + 0xD40 late". Hmm.

Also there's the classic: to force a value into v0 without a pin, use a function call result? No.

Think about what gives a pseudo higher priority: more refs, longer live. To make the sub pseudo get v0 over the sll pseudo and the load... Wait — maybe the competitor that grabs v0 is not the load but the *sll result*. Let's see mine: `lhu v0,88(s0)` — v0 is the load. But the load might have been allocated v0 as the FIRST allocation (highest priority?). Let's compute priorities more carefully.

Actually, hold on. There might be a "copy sugg" that allocates v0 to something first. The sugg pass (qty_phys_num_copy_sugg) runs before the priority pass and assigns suggested registers to qtys with copy suggestions. A copy suggestion arises from move insns: `move s0,a0`? that's in the prologue block. Within block 1: `sh v1,88(s0)` is a store, no. `addiu`... Hmm, `move a0,s0` before a call.

Actually maybe the load's pseudo and the sub's pseudo are tied by combine_regs (non-copy sugg), giving them the same qty, which then gets... no, they'd share.

I need the actual data. Let me generate the dump. I'll set up a mirrored tree.

Actually wait — maybe simpler: delever_search --keep prints the scratch source dir. Then cc1_dumps_tu.sh on that file with CPP include issues. The script runs cpp with `-Iinclude -I"$(dirname $tc)" -Isrc/shared -undef ... -Isrc`. For the scratch src in .run/score/..., the TU's includes like `#include "shared/ov/..."`? Let me look at the TU's head.
