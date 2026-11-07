---
ts: 2026-11-06T08:00:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AA795nxbHe9UwRetwBCP
---
v24 has the load at 61 (not hoisted) and swapped s5/s6 (twicep/oncep). So removing the early w3c read changed the parameter allocation order (s5/s6 swap) and added 2 insns. Not it.

Given the difficulty, let me consider whether the natural C could be the temp trick from the engine. The engine's best was score 1 (one insn off). Let me look at what a score-1 diff looks like on the *current* body by finding a candidate that scores 1. Let me search the trace for score-1 rows on the current body? The trace is old.

Alternative: run the engine's search on the current body? delever_search --run is a long campaign (but per body 128s). Actually the engine's `--run --only` could be run for this one function, budget 400 compiles, ~128s. That's a long command (2-3 min) but feasible. However, it writes to the tree? No, --try doesn't write; --run scores candidates without writing the tree (it says "WITHOUT writing the tree"). The engine --run may write trace/outcomes under .run/P36 (outside my shard!). The constraint says write only under my shard plus moves.md. So running --run would write to .run/P36/engine — not allowed. Hmm.

I could replicate the search in my own scratch script under my shard (using the same modules, writing nothing outside). That's a lot of work.

Let me instead try to understand the score-1 mechanism: the engine changed a width of a temp for `L.v48[0]`. The v48 array is `s16 v48[4]`; `L.v48[0] = *(u16 *)vsrc;`. The target's first GTE load `lwc2 $0,0(s1)` where s1 = sp+96 = L.mat? Wait, L.v48 is at offset? Let me compute the struct offsets: o1[4] s16 = 8 bytes (0..7), o2 8 (8..15), o3 8 (16..23), q28..q32 6*2=12 (24..35), w34..w40 16 (36..51), b44 1 (52), z45[3] (53..55), v48 8 (56..63), v50 (64..71), v58 (72..79), mat 32 (80..111). But the target uses sp+16 for L.o1! So the struct L starts at sp+16. Then o1 at sp+16, o2 at 24, o3 at 32, q28 at 40, ..., w34 at 52, w38 at 56, w3C at 60, w40 at 64, b44 at 68, z45 at 69, v48 at 72, v50 at 80, v58 at 88, mat at 96. Yes! That matches the target: L.w34=52, L.w38=56, L.w3C=60, L.w40=64, L.v48=72, L.v50=80, L.v58=88, L.mat=96.

So `L.v48[0] = *(u16*)vsrc` stores to sp+72. The temp for v48[0]... 

The engine's move "R8 temp tmp0 @443" introduced `tmp0 = *(u16*)vsrc; L.v48[0] = tmp0;`. This changes the register allocation slightly. Combined with a width change, score 1. The width change might affect a SUBREG/temp that changes the w3c allocation indirectly (qty ordering). 

This is too indirect to guess. Let me try more systematically: combine the temp move with the pointer-split (v5) and other moves. The best so far: v5/v7 = 5. Let me try combining v5 with a temp for v48[0], or with the do-while block.

Actually, let me try the `do{}while(0)` move around the w3c load and stores (C0535). It splits cse1's EBB, which could change the liveness/allocation. Let me test a few do-while placements on the base and on v5.

Let me also try: make `w3c` volatile? No (lever).

Let me try a broader combination generator: take v5 (score 5) and add real-C variations that might fix the pointer's order/register:
- v5 + do-while around the load+stores.
- v5 + pointer assigned via a different expression.
- v5 + move the L.w3C store after the pointer assignment (order).
- v5 + temp for v48[0].
- v5 + reorder L.v58[2].

And on base:
- do-while around the w3c load.
- do-while around the pointer assignment.
- etc.

Let me generate ~15 combos.
