---
ts: 2026-10-22T21:11:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_03IR8vDZlBmC0cyHu8I4
---
Now the first item: func_8017D508, kind barrier, 52 lines. The barrier is `__asm__ __volatile__("")` in the third branch, between `s16 k = -0x50;` and the `unk30 = k;` store.

Goal: lever-free body that scores 0. The barrier is a cross-jump barrier: it stops the compiler from merging identical code across branches (cross-jumping) — the third arm and the fourth arm have identical bodies except the last store, so without the barrier, cross-jumping would merge the tails.

Note the moves.md for barrier-like things: the T10 example replaced a launder with `do {} while(0)` and 2nd sets. For a barrier, the standard crack: make the two arm tails genuinely different so cross-jumping cannot merge them, in plain C. Here arms 3 and 4 are:
- arm3: unk20=0x71, unk22=0x600, unk24=0, unk2E=0, then barrier, unk30=k
- arm4: unk20=0x2AA, unk22=0x600, unk24=0, unk2E=0, unk30=0

Hmm, arms 1 and 3 also share a tail (unk20=0x71...). Actually arm1: unk20=0x71, unk22=0x600, unk24=0, unk2E=0, unk30=-0x50. Arm3 is identical with k=-0x50. So arm1 and arm3 are literally the same body! So cross-jump would merge them; the barrier prevents... hmm actually the barrier prevents the *sched* hoisting? Comment says "§5a/§336 cross-jump barrier - LOAD-BEARING".

Let me first just score the orig with the barrier removed and see what happens. But I need to write a lever-free body in win.c.

Let me first copy orig.c from src and make nopin/leverfree version, and check score.

First, I need to understand the workflow: delever_search.py --try <TU> <fn> <file> --body. The file contains a bare definition of the function (body only? "bare definition"). From the worked example, win.c is the full function definition. Yes.

Let me set up item 1. Start time.

Plan for each item:
1. Copy the def from src to <dir>/orig.c.
2. Create win.c = same but with the barrier removed (lever-free).
3. Score with dt.sh.
4. Iterate on plain C moves.

Let me write orig.c for item 1. I'll extract lines 2930-2982 with sed.

Let me be efficient. Use sed to extract and write to file. That's a shell write to the item dir — allowed (write allowOnly "." — project dir). Fine.

Let me do it.
