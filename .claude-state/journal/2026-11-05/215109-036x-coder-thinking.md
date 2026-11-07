---
ts: 2026-11-06T04:51:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ADpWTPVoTqLq7ImUHY1a
---
All still 5. The residual seems robust. Let me look at the actual schedule to understand if ori/a3 can be moved by anything. Let me check the gcc source sched.c to see how priorities work... but first, let me consider that maybe I should try a different approach entirely: instead of do-while, use a `for` loop that gcc unrolls? No.

Alternative: maybe make the two stores use a single pointer variable so they're tied: `p = &D_800C7C60; D_800C7C64 = &D_800A2E20; *p = val;` We did (c1/c4).

What about making D_800C7C64 store use `at` (the address) computed early vs late... 

Hmm, let me look at the score 5 residual again: mine has ori at 5 (after lh), target ori at 3. mine a3 setup at 15-16, target at 6-7. Note: target's a3 setup at 6-7 and mine's at 15-16 — a difference of 9 insns. The other insns (lh at 3-4 in mine, and at 6...) — wait, actually the diff only shows 3 hunks, meaning the rest aligns. So mine: [lui v1, lui v0, lh v0, ori v1, sw ra, and, sll, lui at, addu at, lw a0, lui at, addu at, lh v1, lui a3, addiu a3, ...]. Target: [lui v1, ori v1, lui v0, lh v0, lui a3, addiu a3, sw ra, and, ...]. 

Wait, if only 3 hunks, then after the a3 setup mine continues with "lui v0,D_800A2E20..."? Let me see the full mine b10 asm beyond 174. Earlier dump showed up to 174 lui v0. And target at 174 lui v0 too! So after the a3 setup the sequences align. So the diff is just: ori moved one slot later in mine, and a3 setup moved 9 slots later. When a3 setup moves later, everything between shifts.

So mine order: ..., lh v1 (val), [a3 setup at 16c], then lui v0 D_800A2E20, addiu v0, lui at, sw v0, andi a0... Target: ..., lh v1 (val), lui v0 D_800A2E20 at 174 after a3 at 148? Wait target: a3 at 148-14c, sw ra 150, and 154, sll 158, lui at 15c, addu 160, lw a0 164, lui at 168, addu 16c, lh v1 170, lui v0 D_800A2E20 174, addiu 178, lui at 17c, sw v0 180, andi a0 184...

Hmm target's a3 (D_800C7C60 address) is set at 148, way before its use at 18c (delay slot of bltz). So sched1 placed it early. Mine placed it right before the D_800A2E20 setup at 16c.

The target's a3 setup is at 148, right after lh v0 (currentLocationId) at 144 and before sw ra at 150. In mine, sw ra at 148 is right after ori at 144. 

So target: lui a3/addiu a3 before sw ra. Mine: sw ra before (a3 later). This is a sched1 priority ordering.

What determines it? Maybe the `p` variable's pseudo has a higher priority in target because it's used in the same basic block (no do-while split). With the do-while, p's use is in the next block, so p's address setup gets low priority (can be delayed to end of block).

So to get target exactly, we need no block split at the store, i.e., the barrier replacement must not split blocks... but any C construct that blocks reordering splits blocks.

Unless... we can make the D_800A2E20 store not hoistable by a *data dependence* without a block split. Think: what real C can make an instruction depend on a load without changing the emitted insns? If the store's address `at` (lui/addiu D_800C7C64) were computed from `val`, we'd get extra insns. But maybe we can make the *value* depend on val via a register that's already computed... The store is `sw v0,0(at)` where v0 = &D_800A2E20. Target: v0 loaded at 174 after lh v1. Actually target's D_800A2E20 address (lui v0 + addiu) is at 174, AFTER the val load (170). So it's naturally after val in birth? Source order: `val` declared before the barrier, `D_800C7C64 = &D_800A2E20` after. Birth order: val's lh before the store's address. So target follows birth order. a1 hoists the address above the load because sched1 reorders by priority (address setup for a store has high priority?). Hmm.

Actually, why does a1 hoist it? Let me reconsider: maybe it's not sched1 but global/local alloc deciding to compute the address early. The insn order in the final object is determined by sched2 (reorg?) or sched1. 

Let me try a totally different angle: make the address of D_800C7C64 store use a pointer local initialized in a way that forces late birth: `s32 *pp = &D_800A2E20;` declared at the top would be even earlier. Declaring it after the loads (inside a block) maybe later.

Hmm, we tested b4 (q = &D_800A2E20 in a block before the store) = 17.

Let me look at what happens if we write the store as `*(s32 **)0x...` no, symbolic.

Alternative: what if we keep the do-while but ALSO ensure `p`'s use is in the entry block by putting the store *before* the do-while? Not target.

Wait — maybe we're overcomplicating. What if we restructure so that the two stores are at the *end* of the entry block in the right order, and the barrier is replaced by a *call* that is already there? There's `CdReadRequest(...)` call later. The stores happen before it. The call clobbers memory, so sched1 can't move the stores after it. But the loads are before the stores in source; sched1 could move loads down? sched1 moves insns within the block; the loads feed the branch, so they stay.

The issue is the store hoisting *up* above the loads. A memory barrier (the call) placed between loads and stores would stop it. But a call emits a jal. Unless... we use a call that's already in the target? No, target has no call before the stores.

Hmm, what if we move the loads' source order AFTER the stores? Semantically: compute raw/val after storing? The stores don't depend on raw/val except *p = val depends on val. So we could write:

```
D_800C7C64 = &D_800A2E20;
*p = val;   // val must be computed before
```
val depends on idx which depends on currentLocationId. We could store to D_800C7C64 *before* computing val? But `*p = val` needs val. Reorder:
```
s32 mask = ~0xF000;
s32 idx = currentLocationId & mask;
s32 *p = &D_800C7C60;
D_800C7C64 = &D_800A2E20;
s32 raw = D_800D34AC[idx];
s32 val = D_800D34AE[idx*2];
*p = val;
```
Then the D_800C7C64 store is before the loads in source, and sched1 would place it... target has it after the loads. Not helpful.

What if the D_800C7C64 store comes after val in source but sched1 hoists it because it's independent — to prevent, make it *depend* on val through the address: `D_800C7C64 = &D_800A2E20;` no.

OK here's a thought: what if we make `D_800C7C64` store use `p` somehow: `*p = val;` then `D_800C7C64 = &D_800A2E20;`. Since *p = val is a store, and D_800C7C64 store... no dependence.

Honestly, maybe the wall tag applies: this is a sched1 ordering residual. But before declaring a wall, let's try the "no C spelling" question. The residual is 5 (ORDER) with all kinds gone. A WALL requires ≥20 min and ≥30 tries. We're at ~15 tries. Let me keep trying.

Let me examine whether the `p` init could be moved early by making p's value used before the block split. What if the do-while only wraps `*p = val` and D_800C7C64 is stored... hmm b11 (only *p in do-while) = 17. b10 (only D_800C7C64 in do-while) = 5.

What if we wrap the D_800C7C64 store in do-while but place it *after* *p = val? b8 did that without do-while = 17. Try `*p = val; do { D_800C7C64 = ...; } while(0);` — the *p store in entry block, then the do-while. Then p init's use is in the entry block (early priority) and the D_800C7C64 store is blocked from hoisting. But source order differs from target: target has D_800C7C64 store at 180 and *p at 18c. If source is *p then D_800C7C64, target order reversed. Let's test anyway.

Also: what if we wrap the D_800C7C64 store in a do-while AND keep p's init in the entry block by *also* using p before the do-while (genuinely)? e.g., the *p = val store before the do-while. Let's test f1.

f2: `do { D_800C7C64 = &D_800A2E20; } while(0); *p = val;` (b10) but declare p as `s32 *p = &D_800C7C60;` and also reference p earlier... e.g., `s32 *p = &D_800C7C60; ... *p = val;` p's use is after the do-while, so still in a later block. Unless we make p's use in the entry block.

What if the D_800C7C64 store is wrapped and the *p = val is also in the same do-while (b1) — p use in do block.

Alternatively, what if we use a `while` loop with a condition that's always false but opaque? That emits code.

Hmm, let me test f1 and a few others:
f1: *p=val first, then do{D_800C7C64=...}while(0)
f2: p declared and its address used in a dummy way? no identity.
f3: put `s32 *p = &D_800C7C60;` BEFORE the do-while and make the do-while contain `*p = val;` too but p's init... same as b1.

Let me also consider: maybe the a3 early placement in target comes from `p` being used as the 4th arg to CdReadRequest (at 1b4: `addu a0,v1,a0` then presumably move a3->a2? Let me check the tail). In target, the call passes p as 4th arg. `CdReadRequest(&cdFileLocTable[id], arg0, 0, p)` — p is used at the call too, in a later block. So p is live across blocks in both. Hmm, but in target (no do-while) p's init is early.

Let me just try f1 and also try putting the do-while around the *p store only while D_800C7C64 stays in entry block but source-ordered after... no, b11=17.

Actually, wait. Let's reconsider b11 (only *p = val in do-while) score 17 = same as a1. And b10 (only D_800C7C64 in do-while) = 5. So the D_800C7C64 store is the one that must be blocked. And the block split's side effect is the a3 delay.

What if we could put the D_800C7C64 store in a do-while that is placed *after* the loads but *before* p's init? Then p's init is after the do-while, in the entry block? No — after a do-while, subsequent code is a new block too (the loop exit). Unless flow merges it... The loop exit block merges with the following code. p's init after the do-while would be in the exit block, and its use in the same block (if *p = val follows immediately). That could give p init early within its block!

Source:
```
s32 *p;
...
do { D_800C7C64 = &D_800A2E20; } while (0);
p = &D_800C7C60;
*p = val;
id = ...
```
Then in the exit block, p init is first, followed by the store. sched1 in that block: p init early. Target has a3 setup at 148 (early, before sw ra) — in a different block than where I'd put it, but the final insn order may still match if the blocks get laid out and sched1 places the a3 setup at the top of the exit block... The exit block starts after the do-while. The loads (and, lw, lh) are in the entry block. The exit block would contain: a3 setup, D_800A2E20 setup, stores, andi, bltz, etc. Target has a3 setup before sw ra which is in the entry block region... Actually target's `sw ra` (prologue save) is placed at 150. In my scheme, sw ra is in the entry block and a3 in the exit block — the a3 setup would come after the entry block's insns (after lh at 170). That gives a3 at ~174, not 148.

Hmm, but the current best (b10) already has a3 at 16c. Target 148. The difference is 2 insns (lui v0/addiu v0 D_800A2E20 at 174-178 in target are after a3; in mine a3 is after... wait mine: lh v1 at 168, lui a3 16c, addiu 170, lui v0 174. Target: lh v1 170, lui v0 174. So mine's a3 at 16c comes after lh v1 168; target's a3 at 148 comes before and/sll/lw/lh. So target's a3 is ~9 insns earlier.

If p init were in the entry block, sched1 would place it early (as in target). In b10 the do-while starts before p's store, but p's init is before the do-while in source — so p init IS in the entry block! Source: `s32 *p = &D_800C7C60;` is in the declaration list, before the barrier/do-while. So p init is in the entry block. But sched1 placed it at the end of the entry block (16c) because its use is in the next block and its priority is low.

In target (no split), p's use is in the same block, so higher priority → early placement.

So the fix: make p's init and use in the same block, without a split between them, while still blocking D_800C7C64's hoist. But the do-while creates the split. Unless the do-while is *after* the p use: `*p = val; do { D_800C7C64 = ... } while(0);` — then p init and use are in the entry block (before the do-while). That's f1. Target order has D_800C7C64 store before *p store though (180 vs 18c). But maybe sched1/flow reorders? Let's just test f1.

Also f2: put the D_800C7C64 store in a do-while placed between the loads and p's store, with p init moved after the do-while:
```
s32 *p;
...
do { D_800C7C64 = &D_800A2E20; } while(0);
p = &D_800C7C60;
*p = val;
```
f3: same but p init inside the exit block right before store (p = &D_800C7C60; *p = val;).

Let's test.
