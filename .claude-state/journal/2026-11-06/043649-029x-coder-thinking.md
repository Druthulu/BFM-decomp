---
ts: 2026-11-06T11:36:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1i5IoNhpjZdbvD8DHWTc
---
Now compare. In mine:
- 3844 sh s1,8(v0) [vx stored before the p[3]=8 store]
- 3848 lw t1,16(sp); 384c move a0,s1; 3850 addu s1,s1,t1; 3854 sh s2,10; 3858 sh s2,18; 385c lw t1,24; 3860 li v1,8; 3864 addu s2,s2,t1; 3868 sb v1,3(v0); 386c lw a2,0(v0) [tag2 load]; 3870 li v1,56; 3874 sb; then c stores; 38a8 sh s1,16; 38ac sh a0,24; ...

So in mine, x += w_ and y += h_ happen BEFORE the p[3]/p[7] stores and before the tag2 load; also vx/vy stores happen before them. In target, those stores (p[3]=8, p[7]=0x38, c stores, vx/vy stores) all happen BEFORE x+=w_/y+=h_ and tag2 load. That's the barrier at line 2455 (after p[7]=0x38, before vy=y? no, barrier between p[7]=0x38 and vy=y; then launder x, launder y).

Hmm, actually the target ordering: stores p[3], p[7], c1.., vx,vy, then lw t1(w_), lw a2 (tag), addu x, stores, addu y, stores. So the scheduler hoisted the byte stores before the w_ load. In mine, the w_ load and addu came earlier — because sched1 in mine placed the adds first (birth order). The barriers in orig stopped this.

So I need real C to make the adds happen later. Options: make the p[3]=8 etc. depend on something? Or restructure: compute x += w_ later via a temp declared at use... The scheduler order is driven by dependencies. In target, `lw t1,16(sp)` (w_) is after the sh vx. But there's no dependency between them; it's a scheduling priority thing. The barrier in source prevented sched1 from moving the load/addu above the stores.

What real C changes could shift this? Possibilities:
1. Make `x += w_` a separate statement order (it already is after the stores). sched1 normalizes.
2. Use a temp: `s32 x2 = x + w_;` declared later. The birth of x2 depends on load of w_... same.
3. Introduce a dependency: compute the stores using values that make x+w_ later? E.g. reorder source so the add is textually after tag2 load: it already is (tag2 load at 2466, x += w_ at 2467).

Sched1 orders by priorities: insns with more dependents get scheduled earlier. In mine, `addu s1,s1,t1` got scheduled early (before p[3] store) because ... hmm, the p[3] store has no dependents; adds have dependent stores.

Alternatively force the stores earlier by making the byte stores depend on something already computed... They already depend on p.

Hmm. In target, order is essentially source order for these statements. The barrier forced sched1 to split into EBBs? Actually `__asm__ __volatile__("")` is a scheduling barrier at RTL level; sched1 doesn't move insns across it. So target = two separate EBBs: [stores...] and [adds...]. Lever-free we need C that produces that split.

Idea: use a function call? No, can't add calls.

Idea: make the second group dependent on the first via a value: e.g. `x += w_ + p[3]*0`? No — fake.

Real C move: the `tag2 = *(u32 *)p;` load and the adds could be moved into a nested block with a declaration? sched1 doesn't care.

Hmm, what about the `p += 8` pattern? Actually let's think about what the barrier achieves: it also stops the *first* block (before barrier) from mixing with the second. The first block: p+=8, p[3]=8, vx=x, p[7]=0x38. Then barrier. Then vy=y; launders; c stores; vx/vy stores; barrier; tag2=*p; x+=w_; ... So target first EBB includes p+=8, p[3]=8, p[7]=0x38, vx=x, vy=y, c stores, vx/vy stores. Second EBB: tag2 load, x+=w_, stores, y+=h_, stores, pmask, tag store, tag2=const, ot store.

Wait target 3894 lw t1,16(sp) [w_]; 3898 lw a2,0(v0) [tag2]; 389c addu s1,s1,t1 [x+=w_] — these are after the barrier at source 2465 (before tag2 = *p). So second EBB begins at tag2 load. Then x+=w_, stores, y+=h_ (2467-2475), pmask, tag store, barrier(2478), tag2=0xE1000200, ot store.

Third EBB: tag2 const; ot store. In target 38d8 lui a2,0xe100 comes right after sw a2,0(v0) at 38d4 — that's the barrier point. Actually 38d8 lui a2 (tag2=0xE1000200) after the sw. Then 38dc... store. Fine.

So without barriers, sched1 in the second EBB moved things around (mine has adds before stores). Hmm, but within the second EBB mine also differs: target has tag2 load (3898) before x+=w_ and after vx/vy stores; mine has x+=w_ before stores and tag2 load after p[3] store.

So two sub-problems:
A. First EBB ordering: mine starts the second block's computations early (x+=w_, y+=h_, vx/vy stores) before p[3]=8 store. Since no barrier, sched1 merged everything.

Wait mine: 3844 sh s1,8 [vx], 3848 lw t1,16 [w_], 384c move a0,s1, 3850 addu s1 (x+=w_), 3854 sh s2,10 [vy], 3858 sh s2,18 [vy at 0x12], 385c lw t1,24 [h_], 3860 li 8, 3864 addu s2 (y+=h_), 3868 sb v1,3 [p[3]=8]...

So sched1 in mine put all the "computation" first. Because in one big EBB, sched1 schedules by dependency depth; the adds feed more insns, so they come first.

To fix with real C, maybe restructure the stores so that the first group is textually and dependency-wise earlier... but sched1 ignores source order except for equal priority.

Alternative: introduce a data dependency between the early stores and the late adds. E.g. make `x += w_` use a value loaded from the packet after it's stored? That changes semantics unless crafted to be a no-op... but identity launder doesn't count as a crack. Hmm.

But maybe there is a natural C restructuring: target first group's `p[3]=8` and `p[7]=0x38` etc. Could use a struct assignment? The whole block writes bytes at offsets 3..0x1E of p+8. Target stores each byte separately though.

Hmm, what about the vx/vy: target `move a0,s1` (vx) at 3850 happens before c stores, and `move v1,s2` at 3858. Mine also moves vx (move a0,s1 at 384c) but the store sh s1,8 happens before move a0? mine 3844 sh s1,8 (vx from s1 directly!) then 384c move a0,s1 (for the later 0x18 use). So mine keeps vx=s1 for the first store and copies a0 for later. Target stores vx from a0 and also uses a0 later.

This is a codegen choice: vx variable has two uses (0x8 and 0x18); with x changing in between, vx must be a copy. Target copies once (a0=s1) then uses a0 twice. Mine uses s1 for the first store and a0 copy for later — but wait, s1 gets modified by addu; mine stores sh s1,8 before modification, so it can use s1 directly for that use. Target also could have, but sched1 placed the add before the store in mine... circular.

OK. Let's think about the real source shape that gives target. What if vx and vy are loaded/stored differently: e.g. `*(s16*)(p+8) = vx` written after `x += w_`? no.

Maybe the source originally (before levers) had a different structure: perhaps the function was written with a temp struct or with p as a struct pointer. The barrier at 2455 is between p[7]=0x38 and vy=y. Hmm, wait the original body order:
```
p += 8;
p[3] = 8;
vx = x;
p[7] = 0x38;
BARRIER
vy = y;
LAUNDER x
LAUNDER y
p[4..6], p[0xC..E], p[0x14..16], p[0x1C..1E]
*(s16*)(p+8)=vx; *(s16*)(p+0xA)=vy;
BARRIER
tag2 = *(u32*)p;
x += w_;
*(s16*)(p+0x10)=x; ...
```
Target matches this order. So with a barrier sched1 doesn't reorder across it. Without, it does.

Could we replace the barrier with a real C construct that creates an ordering edge: e.g., make `vy = y` depend on the earlier stores? Like `vy = y;` where y is... no.

What about declaring variables inside blocks so their lifetime starts later? In gcc 2.7.2, variable scoping doesn't affect scheduling much, but declaration order affects register allocation order, not schedule.

Alternatively use the fact that sched1 won't move an insn across a store to the same memory? It respects alias analysis: stores to p+3 etc. are distinct addresses? They're all through the same base pointer p with different offsets; gcc's alias analysis may not prove they don't alias w_ stack slot? Hmm.

Key: In target, the byte stores come before the `lw t1,16(sp)` (w_ load). w_ is on the stack, p points to heap. No alias.

Could we create a dependency by making the later computations read a value that the earlier stores produced, e.g. reusing `p[3]`? Not in real C without changing semantics... Actually! Real C move: `p[3] = 8;` then later `tag2 = *(u32 *)p;` — the load of *p aliases p[3] and p[0..3]. In target, tag2 load (3898) is after all byte stores, which is consistent: a load from *p must wait for the byte stores to the same object (p[3])! Actually the compiler's alias analysis: p[3] store (offset 3) and *(u32*)p load (offset 0-3) definitely alias (overlap). So the load must stay after p[3]=8 store. In mine, the load is at 386c, after sb v1,3 at 3868 — correct.

But that doesn't constrain the adds.

Hmm, what about the c stores at p+4..6, 0xC.. etc. vs the u32 load at 0: no overlap.

Let me think of another real-C move that makes sched1 put the adds later: increase the priority of the early stores. sched1 priority is based on the length of the longest path from the insn (or to the end?). In gcc, sched1 priority = "the number of insns in the longest path ending at the insn" — actually `priority` in sched.c is computed by `priority()` walking successors: a measure of how many insns depend on it (critical path length). Insns with longer dependency chains get scheduled earlier. The adds x+=w_ feed multiple stores → higher priority than p[3]=8 store (which feeds only the load at 0?). Wait sb p[3] is a store, no dependents. The adds feed stores too.

In target with the barrier, the first EBB is small so the adds are in the second EBB.

So the fundamental issue is EBB splitting. Real C constructs that split EBBs at RTL level... a function call splits (but no extra call allowed), a conditional branch splits. A `do{}while(0)`? C0535 says do{}while(0) splits cse1 EBB! Interesting: "cookbook C0535 (do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item)". But the constraint says `do{}while(0)` only with `// !FAKE: do-while`. So allowed with a marker comment! And it's a real C construct (a block), though the brief allows it with the comment. Let me read C0535.

Let me grep the cookbook.
