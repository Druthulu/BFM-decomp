---
ts: 2026-10-22T08:32:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_rzBlLW1fheq8mwpm6Op9
---
Let me now check the timeline / start date, and set up. First let me record start time.

Let me also examine the target assembly to understand what's needed. Let me find where the target's asm is (build/ dir?).

Actually, let's start by running dt.sh on the existing win.c to confirm score 4.

Let me do all three items' baseline scoring at once using sc.sh.

First, setup: create orig.c files (copy from src), and check whether the src def differs from what's in notes (it matches).

Let me write orig.c for item 1 and run sc.sh.

Actually, the plan: I need to find lever-free C bodies that compile to the exact same asm as the pinned version.

Key insight from notes for item 1 (func_801815AC, pin $3 for `q`): The target has `q` in $3/v1, and the constant 0x9000 also in $3/v1. The lever-free body puts q in $4/a0. The issue is local-alloc gives $3 to the block-local constant 0x9000 and global-alloc then may not reuse $3 for global q.

Ideas:
- Make `q` a local to each block? But q is used after the join. Alternative: restructure so that the store happens inside each switch arm instead of after the join. I.e., duplicate the tail:
```
case 2:
    if (...) return 0;
    q = ...;
    ((Unkstruct_801815AC_3 *)q)->unk2 = 3;
    ((Unkstruct_801815AC_3 *)q)->unk34 = 0;
    break;
```
But that changes instruction ordering: target does the stores after the join with val in a reg. Hmm, target: `li v1,0x9000` for constant and `q` in v1. Then stores after join.

Actually wait. Let me get the target asm to understand exactly. Let's find where the asm target is stored. Maybe there's an asm file in the project for the target function.

Let me check the build/ dir and see how scoring works. Let me look at delever_search.py --explain for the item to see the residual (the diff).

Let me run: /usr/bin/python3 tools/delever_search.py --explain src/ov_SC05_018/ov_SC05_018_jr_8017D604.c func_801815AC

That reads one body's residual. It may tell what differs.

Let's do that.
