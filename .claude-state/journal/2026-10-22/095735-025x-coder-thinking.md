---
ts: 2026-10-22T15:57:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WT9quVS1G0I5fWV7VHRt
---
The scratch shared/ov has only func_8012B4B8.h? That means the other headers are resolved from src/shared via the -Isrc/shared include path (relative include `../shared/ov/func_80128158.h` from a file in p6 resolves to p6/../shared = .run/P36/engine/score/ov_MAIN_012__func_8012B4B8/shared/ov — which only has func_8012B4B8.h, so for the others cpp falls back to -Isrc/shared → src/shared/ov/...). OK.

So the TU includes my header at line 911. But the dump showed the launder... at line ~15460. Hmm, maybe there are TWO copies of func_8012B4B8 in the .i: one from the header and one... no.

Wait, maybe the cse2 dump I read is of the *old* body because the dump was made from a *stale .i*? The script re-runs cpp. Hmm.

Let me grep the .i for the body text. `grep -c 'Mat32 \*)m = D_800AE620'` returned 0! So the .i does NOT contain my struct copy. And `grep -c '__asm__'` = 74 (many other functions' pins). So the .i's func_8012B4B8 is the launder version. Why?

Because cpp resolved `#include "../shared/ov/func_8012B4B8.h"` — the TU is in p6, so `p6/../shared/ov/` = `.run/P36/engine/score/ov_MAIN_012__func_8012B4B8/shared/ov/func_8012B4B8.h` — that's the one with my body (we grepped it and found the struct copy). Hmm, but the .i doesn't have it.

Unless... there's an `inc` dir. Wait, the earlier `ls $s` showed: cand.o, inc, ov_MAIN_012.c, shared. And find showed p6/shared/ov/func_8012B4B8.h. But maybe cpp resolved to `p6/inc/../shared/ov/...`? No.

Hmm, but maybe the .i was generated from a different TU: cc1_dumps_tu.sh does `mipsel-linux-gnu-cpp ... "$tc" > $d/$tag.i`. $tc = $s/ov_MAIN_012.c. Fine.

Wait — maybe the `-Isrc` and `-I$(dirname $tc)` order: `-Iinclude -I"$(dirname "$tc")" -Isrc/shared ... -Isrc`. For `#include "../shared/ov/func_8012B4B8.h"`, the quoted include first searches the *directory of the including file*: $s/../shared/ov/... = .run/P36/engine/score/ov_MAIN_012__func_8012B4B8/shared/ov/func_8012B4B8.h. That exists with my body. So the .i should have my body.

Unless the include guard or the file content... let me directly grep the .i for a distinctive line from the header (e.g. 'extern Mat32 D_800AE620').

Hmm, grep -c 'Mat32 \*)m = D_800AE620' → 0. Let me grep 'Mat32' and 'D_800AE620' in the .i.

Actually — maybe the shell `$d` in my dump command was relative and the cc1 script ran `cd /home/musashi/bfm-decomp`, fine.

Wait, maybe the issue: the header at p6/shared/ov/func_8012B4B8.h has the struct copy at line 17, but the .i includes the header *twice* with different content? No.

Let me just grep the .i.
