---
ts: 2026-10-22T00:13:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Xp5YDLBchSGAGK65xoV5
---
Good. Now let me write a dump script that prints the target's instructions for a function, and also my candidate's. This will be very useful for the remaining items.

Let me write .run/P40/T11/G11/dump.py:

import sys
sys.path.insert(0, "/home/musashi/bfm-decomp/tools")
import masked_diff as md
obj, fn = sys.argv[1], sys.argv[2]
ins = md.insns_from_object(obj, fn)
for i, x in enumerate(ins):
    print(f"{i:4d} {x['mnem']}")

And run it via run.sh.

Note: the object must be the BASELINE (target), not the current build (which has the banked body — same bytes, since it matches). For item 1, build/src/.../ov_SC02_026_jr_8017C180.o contains the banked body = target bytes.

But careful: the build object contains the *whole TU* (all functions), and insns_from_object(obj, fn) filters by the function label. Good.

Let me write and run it for func_801832A8, printing the tail (from index ~180).

Let me also print the candidate's instructions for comparison (from the score scratch). Hmm, the score tool deletes the scratch. I can use `--keep` to keep the candidate object! Then dump it. That's the way to compare.

Let me do:
1. dump.py on the baseline object for func_801832A8 (tail).
2. Score base.c with --keep, then dump the candidate object.

Let me write dump.py now.
