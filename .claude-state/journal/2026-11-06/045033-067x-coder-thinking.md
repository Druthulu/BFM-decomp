---
ts: 2026-11-06T11:50:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YGoIpEUI0cMs3dLM0ysN
---
Now compare with target:

Target:
```
3894: lw t1,16(sp)      (w_)
3898: lw a2,0(v0)       (tag)
389c: addu s1,s1,t1     (x += w_)
38a0: sh s1,16(v0)
38a4: sh v1,18(v0)
38a8: sh a0,24(v0)
38ac: lw t1,24(sp)      (h_)
38b0: and a2,a2,a3
38b4: addu s2,s2,t1     (y += h_)
38b8: sh s2,26(v0)
38bc: sh s1,32(v0)
38c0: sh s2,34(v0)
```

Mine (p10):
```
3894: lw t1,16(sp)
3898: lw a2,0(v0)
389c: addu s1,s1,t1
38a0: lw t1,24(sp)     <-- h_ load hoisted here
38a4: and a2,a2,a3
38a8: addu s2,s2,t1
38ac: sh s1,16(v0)
38b0: sh v1,18(v0)
38b4: sh a0,24(v0)
38b8: sh s2,26(v0)
...
```

So mine scheduled `lw t1,24(sp)` (h_) and `addu s2` before the three x stores. Target schedules the x stores right after addu s1, and the h_ load after them.

This is exactly the "load-delay fill" / sched1 priority thing: the h_ load is independent, priority 1; the x stores priority 1; tie → LUID order. The x stores have LUID before the h_ load (source order: sh 16, sh 12, sh 18 come before y += h_). So why did the h_ load go first?

Because after addu s1 is scheduled, the ready list has: sh s1,16 (priority 1? data-dependent on last scheduled → class 1), lw t1,24 (independent, class 3), and a2,a3 (class 1?). rank_for_schedule: priority first (equal 1?), then class: class 1 (data dependent) beats class 3. So sh s1,16 should go first. Unless the stores' priority is 2 (they depend on v0's addiu which... ) hmm.

Wait, maybe the difference is the hazard/queue mechanism: "launching X before Y with 1 stalls" — sched1 also models the load delay slot: a load's result isn't ready until the next cycle; the insn in the delay slot can be filled by an independent insn. So after `lw t1,16(sp)` at 3894, the next cycle's slot can be filled by an independent insn (lw a2 or addu? no). This is the standard MIPS load-delay scheduling in sched1: `queue_insn` with the load's latency.

Target fills the delay slot of lw t1,16 with lw a2 (another load). Mine also does lw a2. Then addu s1 (dependent on lw t1). Then target puts sh s1,16 in the delay slot of... hmm.

The key difference: mine scheduled `lw t1,24` immediately after addu s1, target put the 3 stores there. The lw h_ is independent; the stores depend on addu s1 (just scheduled). Class 1 (data dependent on last scheduled) → sh s1,16 should be preferred. But the priority of lw t1,24 might be higher?

Hmm, in target, the same choice existed and went the other way. What differs? In target, the barrier (asm) was removed here (p10 removes the middle barrier only; barriers 1,3,4 kept? wait p10 = bar[2] removed; bar list [24,32,38,45] in p5 = the 4 barriers. bar[2] is line 38 = the barrier before tag2? Let me recount p5's barriers: p5 = p1_nolaunder, which has 4 barriers at lines 24 (after p[7]), 32? Hmm, in orig the barriers are at body lines 24, 34, 40, 47. In p5 (after removing launders), the line numbers shift: 24, 32, 38, 45. So bar[0]=24 (after p[7]=0x38), bar[1]=32 (before tag2), bar[2]=38 (before tag2=0xE1000200), bar[3]=45? Wait that's 4 barriers: 24, 32, 38, 45. Hmm, but orig had barriers at 24, 34, 40, 47 and p1 removed 2 launder lines (26,27), so 24, 32, 38, 45. Yes.

So p10 removed bar[2] = the barrier at line 38 = the one before `tag2 = 0xE1000200;` (the third barrier). And p11 removed bar[0] (after p[7]) and bar[2].

Wait, that means p10 still has the barrier before tag2 (bar[1]=32) and the barrier after p[7] (24) and bar[3]=45?? Hmm, bar[3] at line 45 — what barrier is that? Let me look at p5 content. orig barriers: line 24 (after p[7]=0x38), 34 (after vx/vy stores, before tag2 load), 40 (after the vx store at 0x18, before y += h_), 47 (after the tag store, before tag2 const). p1 removes launders at 26,27 → shifts by 2: 24, 32, 38, 45. So:
- 24: after p[7]=0x38
- 32: before tag2 load (after vx/vy stores)
- 38: before y += h_ (after sh 0x18 = vx)
- 45: after the tag store, before tag2 = 0xE1000200

p10 removed bar[2] = the one before y += h_ (line 38). That's the barrier between the x-stores and y += h_! Removing it caused the ORDER diff of exactly the three x stores vs the h_ load. Makes sense!

And p11 removed bar[0] and bar[2] (after p[7], and before y+=h_) → also 6.

So the residual is precisely the barrier that kept `y += h_` from being scheduled before the x stores. 

Now: can a real-C move replace that barrier? The barrier at that point: between `*(s16 *)(p + 0x18) = vx;` and `y += h_;`. In target, after it: lw t1,24(h_); and; addu s2; sh s2,26...

Real C: make the y-add depend on the x stores. E.g., write the stores so that the y computation uses a value produced by the x stores? Can't (semantics).

OR: change the *source order* so that the h_ load is born after the x stores (it already is: y += h_ comes after sh 0x18 in source). LUID: sh 0x18 (0x18 store) is before lw h_. Hmm, so why did the scheduler pick the load? The load has priority... both 1? The stores are data-dependent on addu s1 (class 1), the load is independent (class 3). Class 1 wins. Unless the load's LUID... 

Wait, in mine the order was: addu s1 (389c), lw t1,24 (38a0), and a2 (38a4), addu s2 (38a8), then the stores. The `and a2,a2,a3` and `addu s2` also jumped ahead of the stores. So the scheduler is picking the whole y-chain before the x stores. This suggests the x stores have LOWER priority than the y-chain insns. 

Priority: sh s1,16 depends on addu s1 (priority?) ... The stores' priority = 1 + (dep chain). Hmm, the y-chain: lw h_ (1) → addu s2 (2, load cost) → sh s2 (3?). And sh s1,16 = priority(addu s1)+... 

Both adds are priority 2. So sh s1,16 (dep on addu s1, priority 2+1-1=2?) Hmm.

The dump earlier showed priorities 5 for the stores in the no-barrier case. With barriers, the priorities reset per EBB.

Anyway: empirically the barrier matters. Can I split the EBB without a loop? 

Idea: make the y computation textually inside a nested block `{ ... }`? Doesn't affect RTL.

Idea: use a function call? no.

Idea: use `do{}while(0)` around y += h_ and its stores (the small group). That's a loop but small (only y and its stores); regalloc impact might be acceptable. Let me test: p12 = p5 with barriers 0,1,3 removed and the y group wrapped in do-while? Hmm, we want to remove barrier 2 (before y += h_); replace with do-while around the y group.

Actually let me be careful about which barriers to remove: we want a MATCH (all barriers gone). p9 (all barriers gone) = 78. So removing all is bad; the first barrier (after p[7]) and the one before the tag2 load are also load-bearing.

Hmm, but wait: p9 removed all 4 and got 124 insns (4 extra!) — the do-while... no, p9 is just p5 minus barriers. 124 insns means the codegen went wild.

So a full MATCH would need real C replacing all 4 barriers. That's hard.

PARTIAL:barrier is achievable at score 0 (p5). That's a valid result per the brief: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". p5 keeps the barriers (kind: barrier), drops the launders. So PARTIAL:barrier with win.c = p5.

Given the time (~55 min on item 1, way over the 20-30 min budget), I should take PARTIAL:barrier and move on. But let me consider: is it worth a couple more tries to reach a MATCH? The budget says stop at 30 min. I'm well past. Let me finalize item 1 as PARTIAL:barrier.

Wait — but hold on. Is PARTIAL acceptable as a row? Yes: result = PARTIAL:barrier, best = 0, wall = a tag (WALL/PARTIAL need a tag from walls.txt or new). For a PARTIAL, the wall field needs a tag too. The tag for "the barrier cannot be removed lever-free" — the mechanism: sched1 orders the y-chain before the x stores without the EBB split; that's `sched1-birth-order` or a new tag `sched1-load-order` (exists in walls.txt: "sched1-load-order sched1 sched1 orders an addiu/lw pair opposite to the target (G20)").

Hmm, for p10 the mechanism is: without the barrier, sched1 hoists the h_ load + y-add chain above the x stores (load-delay priority). That's closest to `sched1-load-order`.

But actually, for the PARTIAL row, evidence should explain what was achieved: launders dropped via s16 vx/vy width (forced copies); barriers still needed for sched1 EBB.

Now, is p5 really a valid PARTIAL? Check constraints: kinds gone = launder; kept = barrier. p5 has `s16 vx, vy;` — a real C move. No new levers. Pins mFF/tag2 remain (not row kinds). Good. Score 0 → PARTIAL:barrier.

Let me also double check p5's score is 0 and that it's stable (run dt.sh once more, and maybe the score is with the whole TU). Yes, sc.sh uses the same scorer.

Also verify p5 doesn't accidentally contain a launder: it has only barriers. Let me grep.

Then: win.c = p5. Append results row, moves.md line, notes.md.

Then move to item 2.

Actually wait — one more consideration: maybe the width move alone (s16 vx,vy) without barriers... p9 was 78. So barriers are essential.

Let me also try one quick idea for a MATCH: p5 but with the barrier at 38 replaced by a do-while around the y group, plus barriers 0,1,3 kept? No, that's still PARTIAL. For MATCH all barriers must go.

Given time, finalize PARTIAL.

Let me verify p5 content and score once more, then write files.
