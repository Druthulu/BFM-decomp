---
ts: 2026-10-22T22:02:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WS7cFIC3QQyKvSwzF6MU
---
I'm in the wrong dir — I used the item-4 dir path but with the func_80180610 name... wait, the output shows the do-while is at line 12, which is item 4's s2 (read + -0x60 pair in a do-while). OK this IS item 4 (func_80180610).

The u5 variant I mentioned was for item 5 (876C4), not item 4. Oops — u5 was `sp10[4] = D_801A9A88[a1*5]` (item 5), score 2.

For item 4 I need more ideas. Current best = 4 (s2: read + -0x60 pair in do-while).

Item 4's residual: the -0x60 group in the `lh` delay slot.

Let me think again with the do-while insight: the do-while DID change things (score 15 → 4). What if I combine the do-while with other moves?

Actually, since score 4 = 79 ins and the only difference is the -0x60 group's position (and the branch offset), maybe another do-while scope gets it.

Let me think about what the do-while does at the RTL level: it creates a NOTE_INSN_LOOP_BEG/END and a loop-shaped live range; sched1 treats the block differently (loop notes make sched1 do loop scheduling?).

Ideas for item 4:
t1: do-while around the read + all four stores + v1 pair (s1 = 15).
t2: do-while around each store separately (q5 = 4).
t3: do-while around the read only (q4 = 4).
t4: do-while around the -0x60 pair only (p1 = 4).
t5: do-while around the read + the -0x60 pair (s2 = 4).

All 4. Hmm, 4 seems to be the floor.

What's different between 4 and 0? Let me look at s2's actual diff vs the target in detail. dt.sh says: insert target[41:43] (lui at; sh v1) and delete mine[43:45]. So mine's v1 pair is 2 slots later than the target's.

And the earlier real diff showed the -0x60 group in the delay slot... but that was for q2/q4. Let me get s2's real instruction diff.

Wait, the dt.sh diff for the current win.c (s2) shows ONLY the v1 pair shift (2 insns). If that's the whole diff, then the -0x60 group IS in the right place now and only the v1 pair is off!

The dt diff for s2/current win.c:
```
insert mine[41:41] target[41:43]  → target[41]=lui at, [42]=sh v1
delete mine[43:45] target[45:45]  → mine[43]=lui at, [44]=sh v1
```
So mine has the v1 pair at 43-44 and target at 41-42. Everything else matches!

That's just 2 insns: the v1 store pair needs to move 2 slots earlier. What's at mine[41],[42] then? Let me dump.

This is very close. The v1 pair (D_80126962/6A = v1) placement.

Per the LAW 1c note, the pair order is reversed in source. The 2-slot shift suggests the v1 pair is scheduled after the -0x80 group in mine but before it in the target? No...

Let me get the actual disassembly.
