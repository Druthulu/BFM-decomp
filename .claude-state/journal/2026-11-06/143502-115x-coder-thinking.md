---
ts: 2026-11-06T21:35:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1V10vhbrYTQ1lpvnymT4
---
w7 (pin kept, keepalive removed, do-while on cast) = score 0! And w9 = 0. So w7 is a PARTIAL:pin (score 0, keeping only the pin; keepalive gone). 

But we want a MATCH: both gone. w7 keeps the pin. Can I remove the pin too and use the do-while moves to get d→s0?

w4 (both gone + both do-whiles) = 38. w5 (both gone + div do-while) = 21. So the do-whiles didn't crack the pin. Hmm.

Wait, w7 = w1 + cast do-while = 0. w1 has the pin. So the cast do-while fixes the sll order. Good.

For the MATCH, I need d→s0 without the pin. The func_8012BB3C approach said the div do-while cracks the $16 pin. But w5 didn't. Maybe I need a different do-while placement or the function structure differs.

Let me analyze the allocation. In w3 (both gone), d→s1, s1ang→s0. To swap, I need to change priorities. Let me look at the greg/lreg dumps for w3 to understand.

But first, note: the PARTIAL:pin result (w7) is already a valid outcome. The brief allows PARTIAL:<kinds still kept> with score 0. So if MATCH is too hard, PARTIAL:pin is acceptable. But let me try for MATCH.

Let me think about how to force d→s0 with real C. Options:
1. Add refs to d (loop-weight via do-while) — tried, didn't work (w5).
2. Change the declaration order (d before/after other vars).
3. Change d's type (s16 vs s32).
4. Use a different variable for the cast.
5. Make d live longer (add a use).

Let me look at the w3 .lreg/.greg dumps to see why s1ang gets s0 over d. Build a minimal TU for the header? The header is included by includers; a minimal TU needs the structs. Alternatively, use the --keep scratch? Or dump via an includer.

Actually, let me use the includer TU src/ov_MAIN_012/ov_MAIN_012.c (the first includer) and splice the body, then dump. But the includer is a real TU; splicing the header body means replacing the #include with the body. That's what hdump.sh does: `hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>`. 

Let me use hdump.sh with an includer. The brief: "hdump.sh needs an absolute <outdir> under your shard dir". Let me run it.

Actually, first let me try simpler real-C variants for the MATCH:
- w10: w3 + cast do-while + div do-while but with the div do-while structured differently (maybe the div block needs a loop to add refs).
- w11: swap the declarations `s32 u5; s32 u6;` order or move d's declaration.
- w12: use `s16 d` (but d is a parameter arg1; we'd need a local).

Hmm, d = arg1. The pin is on the local `d` assigned from arg1. In C: `d = arg1;` where d is a local s32. If we instead use arg1 directly in the divisions (no local d), the allocation differs. But the target has `move s0,a1` (copy arg1 to s0) and `sll/sra` on s0 — so there IS a local copy d.

What if we name the local differently or reorder declarations? The allocation depends on ref counts and declaration order (global-alloc priority).

Let me look at the w3 dumps. Let me use hdump.sh on the first includer with w3.

Actually, let me first try a few quick variants:
- w10: w3 + cast do-while + div do-while (like w4 but maybe w4 was 38 because the cast do-while on the wrong base? w4 = w3 + both. 38.)
- w11: w3 + cast do-while only (w6=38).
- w12: w3 with the div do-while placed around the *whole* if/else (not each arm).
- w13: w3 with `do { if (iVar4>=0) {...} else {...} } while(0);`

Hmm, w5 (div do-while on each arm) = 21 = same as w3. So it didn't change allocation.

Let me try changing d's ref count more aggressively: add a do-while around the cast AND around the divisions, but also make d used in the comparison? No.

Actually, the target's d=s0. In the C, d is used in: cast, div (x2). s1ang is used in: andi u6, compare, and the iVar4 computation (u5-u6 uses u6, not s1ang). So s1ang has 2 uses (andi, compare) plus the load. d has ~4 uses. Yet d gets s1 and s1ang gets s0. That's odd — maybe the priority is about *live length* or the order of allocation.

Let me dump w3 and inspect the greg/lreg allocation. Use hdump.sh on the first includer.

Let me find the includer for k=0: src/ov_MAIN_012/ov_MAIN_012.c. The header basename: func_8012B8E4.h. Body: w3.c. outdir: absolute under my shard.

hdump.sh signature: `hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>`. It replaces `#include "../shared/ov/func_8012B8E4.h"` in the TU with the body. Let me run it.

But careful: hdump.sh runs cc1_dumps_tu.sh and alloc_table.py, writing dumps to <outdir>. I must delete the dump dir after reading. And outdir must be absolute under my shard.

Let me run it for w3.
