---
ts: 2026-11-06T17:43:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ixCv2e6W2u0rytUtQcAN
---
Time 17.5 min. Still 7 for hi-first forms.

The lo-first named form gives 5 (wrong shift order). Hmm.

Wait — maybe the shift order doesn't actually matter for the *bank* if the score is a masked diff... no, it's an instruction mismatch.

Let me look at p2/q1's asm order more carefully: mine srl then sra. Target sra then srl. What if sched1's order depends on the UIDs and we can flip it by making the srl depend on something? E.g., compute lo first but give it a later UID via a block split (do-while) between the two? The C0535 do-while splits cse1's EBB and can change sched1's order.

Try: 
```
s32 lo;
lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)(((sh16 >> 16) + lo) >> 1);
```
with a do-while around the lo assignment, or around the whole thing, to reorder.

Hmm, but the srl must come *after* the sra in the target; the source has lo (srl) first. A block split won't reorder them.

What if I compute lo first but write the hi shift *before* it in the RTL by using a comma/assignment expression... s1-s4 all gave 7.

OK. Time: 17.5. Let me reach 20 min with a couple more batches, then record the WALL with best 5 (p2/q1/r2). Note: the best lever-free body is 5 (p2). I should put the best body in win.c.

Actually, wait: is p2 lever-free? Yes (no pins). Best = 5.

Let me try a few more variants in the lo-first family to fix the order:
t1: `lo = ...; hi = sh16 >> 16;` (lo first, hi named second) → r2 (5).
t2: add a do-while between:
```
s32 lo;
lo = (s32)((u32)sh16 >> 31);
do { } while (0);
p[0x79] = (u16)(((sh16 >> 16) + lo) >> 1);
```
t3: wrap the lo assignment in do-while.

Let me test t2/t3.
