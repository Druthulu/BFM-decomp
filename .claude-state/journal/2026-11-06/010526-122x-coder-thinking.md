---
ts: 2026-11-06T08:05:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NOubU8AFeDA7ldnGYNb7
---
Mine: m computed late (andi v1,v1,0x1f after the stores), sll s1 into the branch delay slot. Target: m and ang computed early.

The target's order: load unk60 (96), load unkA (10), andi m, sll ang, addiu t-16, store unkA, lw unk50, addiu v+1, bnez, sh unk60.

Mine: load unkA (10), load unk60 (96), addiu t-16, store unkA, addiu v+1, andi m, store unk60, lw unk50, bnez, sll ang.

So mine sank the m/ang computation after the stores. The keepalive forced them early.

Real-C: force m and ang to be computed early by using them early. The source computes them early but sched1 sinks. What real C uses m/ang before the stores? If `ang` were stored to a local (e.g., `d[1]` computed early)? No.

What if the original wrote:
```
v = obj->unk60;
m = v & 0x1F;
ang = ((m << 8) & 0x7F00) >> 1;
t = obj->unkA;
obj->unkA = t - 0x10;
obj->unk60 = v + 1;
```
Same as source.

The keepalive is the lever; the natural C must have a genuine use of m and ang before the stores. Maybe the original's `if (obj->unk50 == 0)` uses ang/m? No.

Let me look at the target's `sll s1,a0,0x7` — s1 = ang. Then `move a0,s1` at the func_8004787C call. So ang is computed early and kept in s1. What if the source computed `d[1] = func_8004787C(ang) / 512;` where ang is used after; the compiler keeps ang in s1 from the entry block. Mine computes ang late (in the delay slot) but still keeps it in s1 until the call. The only difference is WHERE the sll happens.

To force the sll early, maybe the source uses `ang` in a context before the stores: e.g., `d[1] = ...` no.

What if the source's `ang` expression is more complex such that it can't be sunk? E.g., `ang = ((m << 8) & 0x7F00) >> 1;` — the compiler folds to m<<7. If we write it differently (e.g., keep the mask), the compiler still folds. 

What if the original used `s16 ang`? Then the shifts might differ. Let me try types.

Alternatively, the real-C move might be to reorder the source statements: put the `t = obj->unkA;` load AFTER the m/ang computation but BEFORE the stores (it already is). Hmm.

Let me try the C0505 catalog: "Set counts steer three passes: a second identical assignment demotes sched1's birthing boost". Maybe adding a second assignment of m or ang keeps them early. Or "a block with exactly THREE quantities is allocated in BIRTH order".

Let me try a batch:
1. `s32 m7 = m << 7;` and use it for the call and ang.
2. `ang = m << 7;`
3. reorder: put `t = obj->unkA;` before m/ang.
4. `s16` for m/ang.
5. use `u16` for v/t.
6. separate the stores into a do-while.
7. compute d[0]/d[1] differently.

Let me look at the source once more and generate.
