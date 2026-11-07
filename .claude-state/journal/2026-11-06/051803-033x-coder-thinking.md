---
ts: 2026-11-06T12:18:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TMYivbIy41WckGElXXxE
---
Identical residual for all order variants: the allocator assigns vh→v0 (mine) instead of a0, and vv2→a0 instead of a1. It's a tie-break between two allocnos: vh and vv2 (both live long). In target, vh gets a0 and vv2 gets a1. In mine, vv2 gets a0 and vh gets v0.

The allocation priority: gcc global-alloc assigns by priority (refs/live). vh's live range: mine computes vh at 378 and uses at 382 → short. vv2's live range 375-384 → long. So vv2 gets a0 (higher priority), vh gets v0.

In target: vh is computed at 373 and used at 383 → long range, vv2 loaded at 376 used at 384 → long too. vh has one ref (set) ... both have 1 set 1 use.

What determines vh's earlier birth in target? The asm's operand order? No — the asm is at the end.

Hmm, the real cause: the asm makes all three live at the same point, and global-alloc's ordering by pseudo number / priority tie-break gives vh a0.

Real-C move to lengthen vh's live range so its priority beats vv2: compute vh earlier and use it later — i.e. compute vh at the top of the fill and use it at v1.vy (already the case in f5: `vh = rec >> 24;` first). But sched1 then sinks the srl to just before its use (378), shortening the range again. Right — sched1 reorders based on dependencies, and since there's slack, it sinks.

What could prevent sinking? A scheduling dependency. E.g. if vh's computation depended on something computed late... no, we want it early.

Alternatively make the srl's result needed early: use vh in an earlier statement. E.g. `v1.vy = vh;` placed earlier (right after computing vh). Then the store to 82 happens early, but target has it at 383 (late). Hmm, but the store order is determined by sched1 too.

Different idea: use vh in a statement whose position is fixed early. The `q[0x1D] = q[0x0D] + (rec >> 24)` at index 340-343 — target computes rec>>24 there separately. If I compute `vh = rec >> 24` before that and use it both there and at v1.vy, then vh's live range spans 340→383 — huge, giving it top priority → a0 likely. But v4 did exactly that and scored 100. Because the srl then appears only once (at ~340) and v1.vy reuses the register — target has two srl's (340 and 373). So the code shape differs (one fewer srl → count mismatch → 100).

Unless I keep the separate computation: e.g.
```
vh = rec >> 24;      // used at q[0x1D] and at v1.vy
```
gives one srl. Not matching.

So we need TWO srl's but the second one early. Hmm.

What if the value at 373 is not a shift of rec but something else? Target: `srl a0,s1,0x18` where s1 = rec. Then a0 used at 383 (sh a0,82(sp)).

OK, different approach: force the allocation by making vh and vv2 conflict more. Actually maybe use a different width for vh: `u8 vh = rec >> 24;`? Then an andi would appear. No.

What about making vh's value used in a way that requires a0? No, a0 isn't hard-assigned.

Alternative: the residual is 7 = one insert (1) + one replace (1) + delete 2 + replace 1 + replace 2 = 7. The reorder of stores: target 374 v0.vx, 378 v0.vz, 379 v1.vz, 381 v1.vx, 383 v1.vy, 384 v0.vy. Mine: 373 v0.vx, 376 v1.vx, 379 v0.vz, 380 v1.vz, 382 v1.vy, 384 v0.vy.

Hmm so mine stores v1.vx early (376) because vw is computed at 374. Target computes vw at 375 and stores at 381.

If the allocator gave vh=a0 (as target), then the srl a0 would be at 373 and things might line up.

How to raise vh's priority relative to vv2 in the allocator? Priorities come from refs/live length (floor_log2(regs_live_at_def) etc.). The asm gives all three an extra REF (asm operand counts as a use). So vh: 2 refs, vv2: 2 refs, vw: 2 refs. Without the asm, vh: 1 ref... but vv2 also 1 ref, vw 1 ref. So the refs don't distinguish; the tie-break is by allocno number (pseudo order) — and with the asm, the pseudos are born in a different order maybe.

Hmm. Global-alloc assigns in order of priority; ties broken by allocno number. Target: vh=a0, vv2=a1, vw=v0. Mine: vv2=a0, vh=v0.

If priorities are equal, allocno number decides: earlier allocno (lower pseudo number) gets the lower register? a0 is register 4, v0 is 2. Hmm, hard regs a0=4, a1=5, v0=2.

Global alloc: `find_reg` iterates over allocnos sorted by priority, and for each tries registers... The order of assignment to hard regs among equal-priority allocnos follows the allocno order (qsort by priority, stable?).

So to make vh get a0 instead of vv2, vh must have higher priority. Priority = floor_log2(REG_N_REFS) * something + live length. Refs: give vh an extra real use somewhere that doesn't change the shape — e.g. use vh in a statement that already computes the same value... 

Hmm! What about `v1.vz = sz` — no.

What about assigning vh twice? `vh = rec >> 24;` then later `vh = rec >> 24;`? That would create 2 srl's — target has 2 srl's total (340 and 373) but both are used. Hmm.

Idea: give vh an extra ref via a dead store that gcc keeps? A dead store to memory would change code.

Alternatively use `vh` in the loop's tail? No.

Another angle: maybe don't fight the allocator — instead restructure so that the ORDER of pseudo creation matches. In the asm version, the allocnos are: v0.vx's load temp, vv2, vw, vh. In mine (f5, vh first), vh's pseudo is created first, yet still got v0.

Hmm, but sched1's output order is what matters for "birth": global-alloc doesn't care about sched1 order (it runs before sched1? Actually order: cse, loop, global_alloc, then sched1... no: in gcc 2.7.2 the order is cse, loop, ... local_alloc, global_alloc, then sched1? Let me recall: flow, combine, sched1, local-alloc, global-alloc, reload, sched2. Hmm, sched1 runs BEFORE global-alloc. So sched1's reordering determines the live ranges that global-alloc sees. That's why "sched1-birth-order" walls appear in moves.md.

So sched1 sinks the vh srl to just before its use. With the asm, sched1 can't sink it past the asm (the asm uses vh). So the asm's position (after all the fill stores) pins vh's birth early?? No — the asm is at the END, so it prevents vh's srl from being sunk BELOW the asm, but vh is computed at 373 which is early anyway.

Hmm, wait. In the asm version, why is vh's srl at 373 (early, before the load at 376)? Because sched1 orders by priority/latency; the asm at the end forces vh live, so... hmm, sched1 works within an EBB with dependency-based scheduling; it puts instructions as early as their inputs allow, ordered by priority. The srl has a dependency on rec (available). Its priority might be high because of the long chain to the asm? 

The key structural difference: with the asm, the three values must all be live simultaneously at the asm point, so sched1 must schedule the three computations before the asm (they already are) and the register pressure is 3. Without the asm, each temp's life ends at its store.

What if I add a real use at the END that keeps vh, vv2, vw live — but a use that produces the same code? For instance, store v0.vy from vv2 last (already), and use vw in v1.vx last...

Actually here's a cleaner idea: reorder so the last store of each value happens at the end:
```
v0.vx = p->unk8;         // early load, stored at 373/374 (early in target)
vv2 = p->unkA;
vw = rec >> 16;
vh = rec >> 24;
v0.vz = sz;
v1.vz = sz;
v1.vx = vw & 0xFF;
v1.vy = vh;
v0.vy = vv2;
```
Here all four are computed before any store except v0.vx. Then all three temps are live simultaneously (from their computation to their store) — mimicking the asm's pressure. sched1 may still sink computations, but the stores' order forces: v1.vx (vw) at 381, v1.vy (vh) at 383, v0.vy (vv2) at 384 — matching target! And v0.vz/v1.vz at 378/379.

But sched1 could still sink `vw = rec>>16` to just before `v1.vx = ...`. That's what happened in f2 (score 22).

Hmm, in target vw's srl is at 375, which is before v0.vz (378) and before the vv2 load (376). So target's vw srl is NOT sunk to just before its use (381). Why? Because of the asm: the asm at the end uses vw, so sched1 keeps vw's computation... no, sched1 schedules by dependencies; sinking to the last possible slot before its use would still be after the asm? No, the asm uses vw, so vw must be computed before the asm; sched1's "as late as possible" is limited.

I think sched1 in gcc 2.7.2 does forward list scheduling: each cycle it picks the ready instruction with highest priority, so it tends to fill slots with the highest-priority ready insns. The asm at the end raises the priority of vw's srl (since asm has a "use" dependency)... 

OK. Rather than theorize, let me sweep. This is a WALL candidate but let me spend some tries. I have ~15 min in. Let me generate a batch of ~10 more variants around "all temps computed early, stores at the end" and a few with the v0.vx store early/late.

Actually, note that target has v0.vx's LOAD at 371 and its STORE at 374 — quite early. Mine has load 371, store 373 — one slot earlier. Fine.

Let me define variants that move the STORE of v0.vx later/earlier and group the temps.

Let me write gen3 with 10 variants:

g1: 
```
v0.vx = p->unk8;
vv2 = p->unkA;
vw = rec >> 16;
vh = rec >> 24;
v0.vz = sz;
v1.vz = sz;
v1.vx = vw & 0xFF;
v1.vy = vh;
v0.vy = vv2;
```
g2: same but v0.vy = vv2 before v0.vz:
```
v0.vx = ...; vv2 = ...; vw = ...; vh = ...;
v0.vy = vv2; v0.vz = sz; v1.vz = sz; v1.vx = vw & 0xFF; v1.vy = vh;
```
g3: temps early, then stores in target order with v0.vx store first... can't reorder v0.vx's store since it's a statement.

Hmm — actually I CAN: `v0.vx = p->unk8;` is the load+store combined. To store it at a chosen point I'd need a temp: `t = p->unk8; ... v0.vx = t;`. But target's v0.vx store is at 374, third instruction in the group; a temp would add a register.

g4: keep vw/vh as the only temps, vv2 inline:
```
v0.vx = p->unk8;
v0.vy = p->unkA;
v0.vz = sz;
vw = rec >> 16;
vh = rec >> 24;
v1.vx = vw & 0xFF;
v1.vy = vh;
v1.vz = sz;
```
g5: all four temps declared and computed first, v0.vx stored via temp too:
```
u8 t; t = p->unk8; vv2 = p->unkA; vw = rec>>16; vh = rec>>24;
v0.vx = t; v0.vy = vv2; v0.vz = sz; v1.vx = vw & 0xFF; v1.vy = vh; v1.vz = sz;
```
needs a new local `t` (u8) — declaration change inside the body is allowed (no signature change). But adding a declaration changes nothing else.

g6: order v0.vz, v1.vz first then vw/vh:
```
v0.vx = p->unk8;
v0.vz = sz;
v1.vz = sz;
vv2 = p->unkA;
vw = rec >> 16;
vh = rec >> 24;
v1.vx = vw & 0xFF;
v1.vy = vh;
v0.vy = vv2;
```
g7: swap vw and vh computations (vh first):
```
v0.vx = p->unk8;
vv2 = p->unkA;
vh = rec >> 24;
vw = rec >> 16;
v0.vz = sz;
v1.vz = sz;
v1.vx = vw & 0xFF;
v1.vy = vh;
v0.vy = vv2;
```
g8: assign v0.vy at the very end but compute vv2 early (same as g1) with v1.vz before v0.vz.

Also consider: maybe the do-while around the store isn't the only cluster A fix, and a different A fix could change B too (loop notes change refs). Hmm, v3's loop note covers q and attr and tpage — the fill group is outside the do-while (it's after). Fine.

Let me also try a variant where the fill group is wrapped in do-while AND the temps are used... (v5 was 21).

Let me just run g1-g8 and see if any hits 7→0. Probably not. If all 7, I'll try a couple more structural things, then record WALL.

Time: ~05:35. Started 05:10. Budget 30 min → until ~05:40. Then WALL requires ≥30 scored tries; I have ~16 so far (v0-v5=6, f1-f8=8, v3 dup... let me count: v0, v1,v2,v3,v4,v5 (6), f1..f8 (8) = 14 distinct, plus 2 re-scores. I need 30 for a WALL. So generate ≥16 more.

Let me do g1..g8 (8) then h1..h8.

Actually, let me be smart: automate a bigger sweep over statement permutations of the fill group with a generator, say 24 permutations of the 6 stores + computation placement. But each compile takes ~3-5s; 24 = 2 min. That's the efficient route to 30+ tries.

Plan: generator that takes an order of the 6 stores (permutations restricted) plus variants of which temps exist. Too big; sample ~20.

Let me do g1-g8 first quickly.
