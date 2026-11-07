---
ts: 2026-11-06T10:23:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dT9U8yRz2hZ1YVZtjuSn
---
This is too verbose. Let me take a step back.

Time: 03:23. Item 2 at 10 min. I need 10 more min for the WALL criterion. Let me use the time on a more promising approach rather than deep dumps.

Alternative approach: maybe the store can be kept in place by making it a different kind of store that sched can't sink — e.g., storing through a pointer variable:
```
s32 *ip = (s32 *)((u8 *)a0 + 0x1C);
*ip = m;
```
Tried e11 → 2.

What if I compute the address early: `s32 *ip = (s32 *)((u8*)a0 + 0x1C);` before the if, then `*ip = m;`. The address computation is hoisted, but the store still sinks.

What if the store uses a value that depends on the address setup? E.g., if m were computed from `&v`... no.

Hmm, let me look at the actual sched priority. Maybe I can raise the store's priority by making unk1C read right after (before the address setup). The code after the store is `CAST_WIDTH(...0x18) = v.vz << 9; func_800D20C0(...)`. If I insert `m = ((Unkstruct*)a0)->unk1C;` right after the store (e13) → still 2 (dead read removed).

What if the store's value is used by the next statement: `CAST_WIDTH(...0x18) = (v.vz << 9) + (((Unkstruct*)a0)->unk1C - m);`? That adds code.

I think this is a real scheduling wall. The target needs the memory barrier.

Let me consider the wall tag: the mechanism is sched1/sched2 sinking a dead store below the address setup. Is there a wall tag for it? Looking at walls.txt: no exact. I'll create `sched-store-sink`.

Actually wait — let me reconsider. The original comment says "without it both sched1 and sched2 sink this store below the three &v/&v2 address insns (byte-attributed with -fno-schedule-insns*)". So the project already knows this is a barrier-requiring case. This is a genuine WALL.

But hold on — the task is to find a lever-free body that scores 0. If the barrier is genuinely required, then this function can't be lever-free. That's exactly what a WALL is.

However, I should double check: is the store position the ONLY diff in d15? Yes, score 2 = 1 store moved. So d15 is extremely close.

Let me try ONE more idea: use C0535's do-while trick differently — wrap the store and the PRECEDING if in a do-while so the EBB split puts the store at the end of an EBB, then the address setup in the next EBB. e15 did that (store in do-while) and got 4 (store fixed but other insns moved). Maybe combine e15 with a fix for the other 2 moved insns.

e15's diff: `lh v0,52(sp); li a2,1` moved. In e15 they're at 121-122 (mine) vs 124-126 (target). So the do-while caused these to be hoisted. What if I also wrap them? 

Actually, maybe wrap a larger region: do-while around [store .. call]. f2 did that → 2 (store still moved?). Hmm, f2 scored 2.

Let me look at f2's diff to see if the store moved or not.

Actually, let me try a different split: do-while(0) around the `unk1C = m` store AND the following 0x18 store, with the call outside — f1 gave 12 (worse).

Hmm.

Let me try: put the do-while around the store and the address setup region by wrapping `func_800D20C0`? f2 = 2.

I'm going in circles. Let me check f2's diff quickly; if the store is fixed there and something else moved, a combination might work.

Time: 03:24. Let me spend until 03:33 (20 min) then record.
