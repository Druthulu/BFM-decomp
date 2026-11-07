---
ts: 2026-11-06T16:31:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qU3o7ezx2hLvaO4qV483
---
I can use `--keep` to get the spliced TU? No, --keep keeps the object, not the source. But the scratch_src (spliced TU) is written at .run/score/<alias>__<fn>/p<pid>/<basename>. It's removed after unless --keep. With --keep, the dir stays. Then I can dump that TU with cc1_dumps_tu.sh.

Actually, the scratch dir is under RUN = .run/... let me check RUN. Also, I could construct the spliced TU myself in my item dir: take the src TU and replace the function body with my candidate. Then dump it. That's straightforward and keeps things in my dir.

But cc1_dumps_tu.sh writes to ${DUMP_ROOT:-.run/P32/t4e}/dumps_<tag> — I must set DUMP_ROOT to my item dir (absolute). And it compiles the TU with cpp. The TU is src/md_MAIN_041/md_MAIN_041.c — but it may include headers; the script handles -Isrc/shared. But the TU's own directory must be on the include path — it adds -I$(dirname $tc). If I copy the TU to my item dir, includes like "../shared/..." would break. Better: keep the TU at its real path? But then I can't modify it. I can create a spliced copy in a dir that mimics the layout: e.g., .run/P40/T11/W47x/dumpmd/md_MAIN_041.c — then ../shared doesn't resolve. Hmm, but the script passes -Isrc/shared; relative includes with "../shared/engine_prelude.h" would resolve relative to the including file's dir = .run/.../dumpmd/../shared → no.

Alternative: use DUMP_ROOT and pass the real TU path? Can't modify real TU (constraint: write only under shard dir; and it's a banked file).

Hmm, but cc1_dumps_tu.sh takes a .c file. I can copy the TU to my item dir AND create a sibling "shared" symlink? Symlinks... maybe. Or use the `-I` trick: the script adds -I$(dirname $tc); cpp resolves `#include "../shared/x.h"` relative to the current file's directory, not -I paths. Hmm.

Wait, does md_MAIN_041.c include "../shared/..."? Let me check its includes.

Actually simpler: the spliced TU from delever_search's --keep is placed in .run/score/<alias>__<fn>/p<pid>/md_MAIN_041.c with extra -I<src_dir> and -I<shadow>. That resolves `#include "../shared/..."`? The scratch_src is at .run/score/.../md_MAIN_041.c, and `#include "../shared/x"` → .run/score/.../../shared → no. Hmm, but the recipe's pipeline for the real TU presumably works with the real path. Let me check what the recipe pipeline is and whether the TU has relative includes.

Let me just check the head of the TU.
