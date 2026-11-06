---
ts: 2026-10-22T21:02:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZU0B5XyNU3pToDf8DKPu
---
v4's residual is different! v4: `insert at 73 target has addiu s0,s1,123 (ax)`; mine has ax at 74 (and ay at 75). So in v4, by is at 72 (matching target's 72!), and ax is at 74 instead of 73, ay at 75 instead of 79.

So v4 fixed the by/ax order (by first) but now ax is one late and ay still early. Progress? Score is still 4 but the diff is a different permutation.

v4 source:
```
bx = out.vy;
ay = out.vx;
by = bx - 0x5D;
bx = bx - 0x57;
ax = ay + 0x7B;
```
Interesting: moving ax after the bx re-set gives by first, then bx, then ax — but the target wants by, ax, bx. Hmm.

Let me see v4's actual order: by(72), then mine has bx at 73? and ax at 74, ay 75. Target: by(72), ax(73), bx(74), chain, ay(79).

So v4: by, bx, ax, ay. Target: by, ax, bx, chain, ay. Still 3 diffs.

What if the source order is: by, then ax, then bx (the original), but with something that makes sched1 keep it. The original (gen_o3) gives ax, by, bx (swapped). v4 gives by, bx, ax.

Try: `by = bx - 0x5D; bx = bx - 0x57; ax = ay + 0x7B;` (v4) vs `by; ax; bx` (gen_o3). What about `by; bx; ay-load; ax`? Or `by; ax` with ax's source *after* bx but the add's operands... 

What about: `bx = out.vy; by = bx - 0x5D; ax = out.vx + 0x7B; ay = out.vx; bx = bx - 0x57;` — ax computed from out.vx directly (a load) and ay loaded separately? That would add a load.

Hmm, v4 is a different residual. Let me try variations around v4:
z1: v4 + move the ay add later? The ay position (75 vs 79) is the chain issue.
z2: v4 with `ax = ay + 0x7B;` before `bx = bx - 0x57;` but after by (that's gen_o3).

What if I swap the *statements* `ax` and `bx` in gen_o3? i.e.:
```
bx = out.vy;
ay = out.vx;
by = bx - 0x5D;
bx = bx - 0x57;
ax = ay + 0x7B;
```
= v4. 

What about:
```
bx = out.vy;
ay = out.vx;
ax = ay + 0x7B;
by = bx - 0x5D;
bx = bx - 0x57;
```
= v6. Its diff was the same as gen_o3 (ax at 72?). Hmm, v6's diff shows the same residual as gen_o3 — so v6 also has ax first.

The chain/ay ordering: target has the chain before ay. In all variants, ay is before the chain.

What if the ay add's *use* is delayed: the target's ay add is right before the store sh s1,36. In mine, ay's add is at 75 and the stores at 80+. The chain is 4 insns (76-79). So ay is scheduled before the chain because... sched1 sees ay's result used by the store (after the chain) and the chain's result used by the call (after the stores). Both are "far".

Hmm, what if I make the ay add depend on the chain? e.g. compute prim.x0 = ay + 0x75 where ay is updated *after* op... no.

Alternatively, make the chain depend on nothing and schedule earlier by increasing its priority: the chain has 4 insns; the first (lui/lhu D_800B9A02) is at 1504-1508 (early!). The sll starts at 76. The chain's sll depends on the lhu (1508). In the target, the sll starts at 152c (right after bx) and the lhu at 1504. So the target's chain starts earlier.

What if I compute op's index earlier in the source (before the loads)? The source already has `op` computed in the block after bx. The lhu of D_800B9A02 is hoisted to 1504 in both.

I could try making the index computation a separate statement *before* `bx = bx - 0x57`:
```
op = &D_800A6518[...];
bx = bx - 0x57;
ay = ay + 0x75;
```
Then the chain's uid is before bx's, and sched1 might schedule it right after by/ax and before bx — but the target has bx before the chain. Hmm.

What about `op` assigned *between* ax and bx? no.

Time: 15:20, item 3 at 30 min. The brief says past 30 min stop and record a wall. I'm at the limit. Wall it at 4 (best = gen_o3 or v4; both 4). I'll record gen_o3 as the best (ORDER, 207 ins, matches except order).

Actually, for the results row "best" = 4. Wall tag: `sched1-birth-order` (new). Evidence: sched1 orders ax before by and ay before the D_800B9A02 index chain; the target keeps the source order; 4 ORDER words, 207 ins.

Let me write notes.md, the results row, and the moves line, then clean up the dumps.

Then the final report. Also I need to write the task log phase-ends/current/logs/T11.cG16b.md (the brief's LOG). And append per-item lines to moves.md (done for items 1,2; item 3 pending).

Note: I have not committed (no git allowed for this task: "no make, no git, no commit"). Right, the CONSTRAINTS say no git/commit. So no commit — the brief's DONE WHEN is results rows + win.c scoring 0 for MATCH/PARTIAL. Since all three are WALLs, no win.c needed.

Wait, the brief says "Per item append exactly one row to G16/results.tsv". All 3 items now have rows (8012B4B8, 8012C750, 801372B0). The list.tsv has 4 items; func_8012C2D0 already had a row (skip). So DONE WHEN is satisfied.

Let me finalize item 3's files.
