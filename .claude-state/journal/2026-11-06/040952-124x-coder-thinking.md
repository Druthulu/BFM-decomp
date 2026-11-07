---
ts: 2026-11-06T11:09:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EYr5Lo7Kb2SidujVGrB6
---
Both MATCH verified.

Now, can I apply the same move to the two small twins (items 1 and 2)? The big items' fix was: n as s16 (RC-12 replacement) + the do-while after the call (fence replacement) + the struct alias (memory barrier). The small items have a different issue (the store sink), which is a scheduling issue, not a reorg one. The do-while after the call doesn't apply there.

But wait — for the small items, maybe the `do{}while(0)` trick at a different place could fix the store sink. The store sink is sched1 ordering; the do-while creates block boundaries which I explored.

Hmm, one idea I haven't tried for the small items: put the do-while around the *whole* if-body/else tail to change the block structure... I tried many.

Actually, let me reconsider: maybe the small items' remaining diff (the store sink) can be fixed by a do-while AFTER the store (like the big items' fence trick, which worked via reorg). For the small items, the diff is sched1 (pre-reload) ordering, not reorg. Hmm.

But let me quickly try: in d_S2S3S4 (score 2), add a do-while after the unk58 store:
```
do { t = unkC4; } while(0);
unk58 = &D_801907C4;
do { } while(0);
unkC4 = t|2;
```
That's essentially v_dw6 (score 2, different diff). Hmm.

What about a do-while after the RMW? Let me try a couple of quick placements on item 1's d_S2S3S4. Cheap.

Actually, let me reconsider the small items with the knowledge that the empty do-while affects reorg (post-reload). The small items' diff (sw88 position) is in the sched1 output, before reload. So reorg can't fix it.

Hmm, but the store sink might also be affected by sched2 (post-reload). Let me test: does adding `do { } while (0);` after the store change anything? The do-while notes might split the block for sched2.

Let me try a few quick placements on item 1 (and item 2) — 5 minutes max. If one cracks, great.

Variants on d_S2S3S4 (item 1):
1. `do { t = unkC4; } while(0); unk58 = ...; do { } while(0); unkC4 = t|2;` (= v_dw6-ish)
2. `do { t = unkC4; } while(0); do { unk58 = ...; } while(0); unkC4 = t|2;`
3. `do { t = unkC4; } while(0); unk58 = ...; unkC4 = t|2; do { } while(0);`

Let me score these for item 1.

Actually v_dw6 = variant 2? v_dw6 was `do { t }` and `do { unkC4 = t|2 }` — the store unwrapped. Let me build the three.

Time check: it's ~05:15. I've been going ~2h20. Let me do this quickly and then write everything up.
