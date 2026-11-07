---
ts: 2026-11-06T04:21:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4n1MObdMNhu0fOa5nCEz
---
In w4, the n<8 arm now has v0 for the value and a0 for p (target: v0 for value, v1 for p). So p = a0.

Target uses v1 for p in all arms. Mine uses a0. The difference: in target, the `n` variable in the n<8 arm is v1, and p is also v1 (disjoint arms). In mine, `n` is v1 and p is a0.

Hmm, so the target's p and n share v1 (disjoint). Mine's p gets a0 because... maybe a0 is preferred (it's the first caller-saved). Why would the target pick v1 over a0? Because a0 might be live at that point? At the store points, is a0 live? In target, a0 holds the model pointer `*(s32*)(a0+0x20)`? No, s1 holds a0 (moved at prologue). a0 is free. Hmm.

Global alloc's `find_reg` for a pseudo with priority: it scans the allocno order (by priority) and calls find_free_reg which scans registers by `reg_alloc_order` (probably $4,$5,...,$2,$3...). Wait, the MIPS register allocation order is defined in the machine description: typically a0-a3, t0-t7, v0-v1, ... or similar. If a0 is earlier in reg_alloc_order than v1, then p would get a0 if free. Target got v1 — so at the time p was allocated, a0 must have been taken (or p's conflict set included a0). 

In target, at the store points, what's in a0? In the n<8 arm: 48a8 sll v0,v1,1; addu v0,v0,v1; lw v1,32(s1); sll v0,v0,7; j; sh v0,26(v1). a0 is free. Yet p got v1.

Maybe p's allocation happened globally: p has multiple live ranges (one per arm), and global_alloc considers the *union* of conflicts? In global.c, each pseudo is allocated once; p is a single pseudo with defs in multiple arms; its conflicts are the union of all points where it's live. If a0 is live somewhere during any of p's live ranges, p can't take a0. In the `==0` arm, p's live range is after the sh and until the store; is a0 live there? a0 holds... in target's `==0` arm, a0 is not used. Hmm.

But in the `<0x11` arm, the multiply uses v0/v1; a0 free.

What about the `n<8` arm: `p` is live from the lw to the sh. `v` is v0. a0 free.

Why v1? Maybe because global_alloc's `allocno_compare` uses floor/priority and a0 was assigned to another pseudo that conflicts. Which pseudo could be a0? The `n` in the n<8 arm is v1 in target. In mine, n is v1 too. Hmm.

Maybe the target's p pseudo is actually a DIFFERENT pseudo per arm (if the source declared p inside each arm)? The body declares `s32 p;` at function scope. If the target's source declared `p` separately in each arm (block scope), each arm's p is a separate pseudo, and each could get different registers! But target uses v1 in all arms consistently. Hmm, still v1.

Wait, maybe the target's `p` is declared as a pointer type `Unkstruct_800B5CB8 *p;` vs mine `s32 p;`? The source has `s32 p;`. If p were a pointer, regalloc could differ? No, same reg class.

Let me look at this from a different angle: the target's v1 for p might come from the *order of pseudo allocation*: global_alloc allocates by priority; p's priority might be higher than the multiply temporaries, so p gets the first free reg in reg_alloc_order. If reg_alloc_order for MIPS is v0,v1,a0,a1,... then p would get v0 — but v0 is taken by v (the value). Then v1. That fits! If the order is v0, v1, a0..., then: v takes v0 (higher priority), p takes v1. Mine: v takes v0, p takes a0 — meaning v1 was taken by something else at that moment, or p's conflict includes v1.

What takes v1 in mine? In the n<8 arm, n is v1. p's live range in the n<8 arm is from the lw (48b0) to the sh (48bc) — does it overlap n's liveness? n is live at 48a8-48b4 (used by sll/addu). The lw a0 at 48b0 is between addu (48ac) and sll (48b4). So p's live range starts at 48b0, while n (v1) is still live until 48b4 (sll uses v1). Therefore p CONFLICTS with n (v1) in the n<8 arm! That's why p can't take v1 in mine.

In the TARGET, the n<8 arm: 48a8 sll v0,v1,1; 48ac addu v0,v0,v1; 48b0 lw v1,32(s1); 48b4 sll v0,v0,7. Here p (v1) is loaded at 48b0 AFTER the last use of n (v1) at 48ac! So no conflict: n dies at 48ac, then v1 is reused for p. That's why target can use v1.

So the key is the ORDER: in the target, the p load (lw v1) comes AFTER the addu that last uses n. In mine, the p load is between addu and sll? Mine: 48a8 sll v0,v1,1; 48ac addu v0,v0,v1; 48b0 lw a0,32(s1); 48b4 sll v0,v0,7. n (v1) is last used at 48ac; the lw is at 48b0, after. So no conflict either! Wait, then why a0?

Hmm, mine's lw at 48b0 is after the addu. n's last use is 48ac. So p's live range doesn't conflict with n. So that's not it.

But wait, the *source order* is: v = n*3; p = load; v = v*128; store. The scheduler moved the p load after addu but before sll. The RTL order at global_alloc time (before sched1? no — sched1 runs BEFORE global_alloc? Let me check pass order: sched1 (schedule_insns) at line 3028-3033, then global_alloc (line ~3050?). Actually the order: combine → sched1 → local_alloc → global_alloc → ... So sched1 runs BEFORE global_alloc! That means the instruction order sched1 produces affects local/global alloc conflicts. So the schedule matters for register allocation.

In the target, sched1 put the p load after the sll (48b4). In mine, after the addu (48b0). The difference: in target, n's last use (addu at 48ac) then lw v1 at 48b0 then sll v0 at 48b4. Same as mine except the lw dest is v1 vs a0 — that's post-alloc. The pre-alloc schedule (sched1) determines the conflicts.

In target's schedule: sll v0; addu v0; lw p; sll v0. In mine: sll v0; addu v0; lw p; sll v0. Identical positions! So the pre-alloc schedules are the same here. Then why v1 vs a0?

The conflict analysis uses live ranges from the pre-sched order? Actually local_alloc uses the post-sched1 order (sched1 runs before local_alloc). Both have the same order here. Hmm.

Wait, maybe the difference is in a DIFFERENT arm that makes p conflict with v1 in mine. Since p is one pseudo used in all arms, its conflicts are the union. If in any arm p's live range overlaps v1's use, p can't take v1.

Consider the `<0x11` arm: mine (w4) 4920 lw v1,32(s1) [p]; 4928 sh v0,26(v1); 492c lw v1,28(s2) [obj->1C]; 4930 lw a0,32(s1) [p reload]; 4934 sll v0,v1,1; 4938 addu v0,v0,v1; ... Here the p reload (a0) is at 4930, BEFORE the uses of v1 (4934, 4938). So p conflicts with v1! In target, the p reload is at 4944 AFTER the v1 uses (4934-4940), so no conflict → p can be v1.

So the reload position is the cause of the register difference. If I fix the reload position (after the sll chain), p can take v1 and everything matches.

So back to: force the p reload after the multiply chain. The fences did it. How in real C?

The p reload is forced by cse because the earlier `sh v0,26(v1)` (the 0x1A store) kills the model pointer load. The reload's position is then scheduled. Target: after the chain. Mine: before.

To make the scheduler put the reload after the chain, maybe add a dependency: make the p value depend on v. Or make the multiply's result feed into p's address (identity)? Not allowed.

Alternative: change the *order of source statements* so the reload is naturally born after the chain. Source: store, multiply, p load, add, store. The reload (p load) is after the multiply in source. sched1 moved it before the chain (above sll). The chain (sll,addu,sll) depends on obj->1C. The p load is independent.

Hmm, what if we express the multiply differently so its first instruction is scheduled before the p load? sched1's priority: the p load's use (addiu/sh) is near, so it gets high priority and is scheduled as early as possible. In target, the p load is later. The scheduler's priority is based on the "depends on" chain length. If the multiply chain had higher priority, it would go first.

Maybe the do-while around the p load changes the priority/birth. w5 didn't help (same schedule?).

Let me try wrapping the p load in do-while AND making the load's use later... Hmm.

What about moving the p load's *use* (the addiu/store) — no.

What if the `v = v + 0x600;` is folded into the store: `((Unk*)p)->unk18 = v + 0x600;`? Then the addiu is after the p load (needed for the store address? no, p is the base). The addiu depends on v; the store depends on both. Sched: multiply chain, p load, addiu, sh. Same.

What if we make the p load's address depend on v: `p = ((Unk*)((s32)((Unk*)a0)->unk20 + (v - v)))`? fold.

Hmm.

Let me look at what birth order does: sched1's priority includes `birth` (insn's position). The p load's birth is after the multiply insns. Sched1's list scheduling picks by priority = priority of the dependence chain. The multiply insns have longer chains? Let me look at the target's order: lw obj->1C (4930); sll (4938); addu (493c); sll (4940); lw p (4944); addiu (4948); sh (494c). So the multiply chain ran first, then p, then add. In mine: lw obj->1C (492c); lw p (4930); sll (4934); addu (4938); sll (493c); addiu (4940); sh (4944). So mine scheduled p early.

If p's load had a dependency on the multiply result, it'd be after. Can we make that real? The stored value is v (the multiply result); p is the base. No real dependency.

UNLESS: we reuse the variable! If `p` and `v` are the same variable? No.

What if the model pointer is obtained via `((Unk*)v_related)`? No.

OK here's an idea: use a **single temp for the multiply chain** such that the p load's destination register must be different... no, that's regalloc, not sched.

Alternative: make the p load happen via a *store-then-load* dependency that's real: the store `((Unk*)*(s32*)(a0+0x20))->unk1A = 0xC00;` writes through the model pointer. Then `p = ((Unk*)a0)->unk20;` reloads. cse forces the reload because the store may alias. The reload is real. The scheduler then places it. To make sched place it after the multiply, give the multiply chain a dependency on the store? No.

Hmm, what about reordering the source: put the multiply BEFORE the 0x1A store?
```
v = *(s32*)(obj+0x1C) * 3 * 32;
((Unk*)*(s32*)(a0+0x20))->unk1A = 0xC00;
p = ((Unk*)a0)->unk20;
v = v + 0x600;
```
Then the store kills cse after the multiply; the p load follows. Target order is store first, then multiply. So source order would differ from target. But maybe sched reorders. Let me test (r1).

Also: maybe the original source had the 0x1A store AFTER the multiply? Target shows store at 492c before the multiply chain at 4938. But sched1 could move the store later/earlier. Let me try.

r1: multiply first, then store, then p.
r2: store, multiply, then p but with the p load after the add.

Let me also try making the p load's value used in the multiply chain (impossible).

Let me test r1 and a variant where the `p` load is inside the same expression as the store:
```
((Unkstruct_800B5CB8 *)((Unkstruct_800B5CB8 *)a0)->unk20)->unk18 = v + 0x600;
```
This is a direct raw pointer (no p variable) — the load of model happens right before the store. Then p isn't used; the store address computation loads model after the addiu? The load of `((Unk*)a0)->unk20` would be scheduled maybe after the chain. Let me test r3: replace the p load + store with a single raw store expression. But the target has TWO model loads (one for the 0x1A store, one for the 0x18 store) — with a raw store, cse might forward the first model load into the second (no store between? there IS the 0x1A store between, which kills it). Actually the 0x1A store happens before, so the second raw load can't be forwarded → two loads. Good.

r3:
```
} else if (*(s32 *)(obj + 0x1C) < 0x11) {
    ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk1A = 0xC00;
    v = *(s32 *)(obj + 0x1C) * 3 * 32;
    v = v + 0x600;
    ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk18 = v;
}
```
Hmm, but the merge block `((Unk*)p)->unk18 = v;` is shared by all arms (it's after the if-else chain). The `else` arm (last) writes both and gotos call. The `<0x11` arm falls through to the shared `p` store. So I can't replace it with a raw store without restructuring (the shared block uses p).

But I could restructure the `<0x11` arm to goto a different path? That changes structure/insns. Risky.

Let me just try r1 (reorder multiply before store) and see.

Actually, wait. Let me reconsider: the p load at 4930 in mine is the reload. Its position relative to the multiply chain is what matters for the register. What if I make the multiply chain start earlier by moving the `v = *(s32*)(obj+0x1C) * 3 * 32;` BEFORE the 0x1A store in source? Then sched would schedule the multiply insns first (birth earlier), then the store, then p. Target order: store, multiply, p. Hmm, if the multiply is born first, sched might still emit the store first (store has low priority) — actually stores are typically scheduled late. So the store might stay before the multiply's results are ready? Let me test r1.

Let me also test r2: keep order but wrap the p load in do-while with the multiply inside the loop (w7 did multiply+p? w7 wrapped 57-58 in one do-while; got 14). Hmm w7 = do-while around multiply+p (57-58). It got 14. Did it change the reload position? Let me check w7's diff quickly. Maybe it did but something else.

Let me be efficient: test r1, and check w7's diff.
