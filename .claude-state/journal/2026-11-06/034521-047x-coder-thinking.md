---
ts: 2026-11-06T10:45:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gqPPRl6FwcUEH3DukQl1
---
Hmm, now there's an extra nop at 29 and the store moved later. Also the branch offset differs (j fb0 vs fac) — that's due to the nop.

The do-while around S1 didn't split as hoped; instead it created a nop (the loop structure?). Not good.

Let me reconsider. The do-while around S1 emits a nop? Actually the do-while(0) around a store may generate a loop that isn't optimized away? The nop at 29 suggests the branch target alignment or a delay slot.

OK. Let me think again about the target's block structure. The barrier is `__asm__ __volatile__("" ::: "memory")`. In gcc, an asm volatile is a scheduling barrier and also splits basic blocks? Not necessarily — but sched1 uses the asm as a barrier and won't move insns across it. cse1's EBB: asm volatile with memory clobber might end an EBB.

So after the barrier, the load/store/RMW are in a *separate* EBB for cse1 but perhaps the same basic block for local-alloc? No — local-alloc works on basic blocks from the CFG; a barrier doesn't split a basic block.

Hmm, but t got v0 in the target, suggesting t was a local allocno in the same block as the address. So the barrier does NOT split the basic block for local-alloc; it only affects sched1 (no motion across) and cse1's EBB.

So I need a scheduling barrier without splitting the basic block. The do-while splits the EBB (and possibly blocks).

Hmm. What real-C construct acts as a scheduling barrier for sched1 but not a block split? A function call, a volatile access, an asm. Hmm.

Wait — maybe not: maybe sched1's *schedule* is what matters, and the target's schedule is just source order. Maybe the issue is that without the barrier, sched1 hoists the load; with the barrier, it doesn't. If instead we give sched1 a reason not to hoist the load (a dependence), we'd get the target order while keeping one block and t local → v0.

So: make the load depend on the preceding store. A real dependence: the load's address depends on the stored value. E.g.:

```
((Unkstruct*)a0)->unk5C = 0x8000;
t = ((Unkstruct*)a0)->unkC4;
```
What if we spell the load with an address computed from the stored value? No.

Hmm, what if the load is a read of a struct field whose address is `(s32)a0 + (unk5C - 0x8000) + 0xC4`? That's a launder/identity — not allowed and cse folds it.

Alternative: make the store before the load a store *through a pointer that may alias*: e.g., store unk5C via `s0` but load via a different pointer variable p that's a copy of a0. gcc's dependence: `(plus (reg p) 196)` vs `(plus (reg s0) 92)`. If p != s0 as pseudos, the addresses can't be compared → assumed dependent → the load stays after the store. But cse would merge p and s0 if p = a0 copy... unless p is used differently.

Wait, actually the load is already after the store in the source; the problem is it's hoisted ABOVE MANY stores (to position 19, before the unk2 store). So the alias analysis proves all these stores independent. If the load's base were a different pseudo, it couldn't be hoisted above any store.

But then the load would also not be hoisted above... it would stay at its source position, which is what we want. And t remains a local allocno in the same block (no block split) → v0. 

How to get a different base pseudo without a launder? Declare the local pointer p and assign p = a0 *at the point of the load*? E.g.:

```
Unkstruct_800B5CB8 *p;
...
p = (Unkstruct*)a0;   // right before the load?
t = p->unkC4;
```
But that's a copy assignment which cse will propagate (p = a0 → t = a0->unkC4).

Hmm, but if p is assigned once and used for several accesses, cse may still merge.

Wait — but actually, is it the *same* base reg? The C uses a0 directly everywhere now, so all stores and the load use the same pseudo → gcc proves the offsets differ. If I introduce a separate local pointer used only for the tail stores/loads, cse might still canonicalize.

Alternative real-C dependence: make the load a *different type* with a different alias set AND a non-comparable address. My v_cast used `*(s32*)((s32)a0 + 0xC4)` — the address `(plus (reg) 196)` is comparable with `(plus (reg) 92)` → independent. Same base.

So I need a different base reg. What if the load is through a pointer *stored in memory*? No.

Hmm, what about making the preceding store use a computed pointer? e.g. `*(s16*)((s32)a0 + 0x5C) = 0x8000;` vs the load `((Unkstruct*)a0)->unkC4`. Same base reg.

OK, different idea: use the do-while to split the EBB but check whether local-alloc still sees one block. In d_S2S3S4, the load was in its own block and t got v1. So the do-while DID split the basic block (t became global). Hmm, or the loop notes affected allocation.

Wait, maybe the issue in d_S2S3S4 is different: t got v1 because after the block split, the *address* pseudo is in block 2 and got v0 (local-alloc), and t (global, spanning blocks 1-2) got v1 from global-alloc. If I make the address pseudo *not* get v0 (e.g., by having t allocated first in global order), t would get v0.

Global-alloc assigns hard regs to global allocnos in priority order. t is global with 2 refs in a tiny live range → low priority. The address is local, allocated later by local-alloc, which takes free regs. If t were assigned v0 by global-alloc, then the address would get v1. But global-alloc gave t v1 — maybe because the register order in global-alloc starts from... Hmm, the target's t was local, so no issue.

What if we make t *not* live across the block boundary: wrap the load AND the RMW in one do-while, leaving the store in between? That's dw2 = 7 (t in v1, address in v0). Hmm, same issue: the address is between them, so t spans the store block.

What if the store S3 is *inside* the same do-while as the load (d_S2S3S4-e style, e_S2S3S4 = 7) — t and address in the same block → t v1 again? e_S2S3S4 wraps S2 and S3: score 7.

Hmm, so whenever the load and the address are in the same block, t gets v1?! That contradicts the target where they're in the same block and t gets v0.

Unless in the target they are NOT in the same block, and t got v0 as a *global* allocno because global-alloc assigned it v0 by priority. Let's check: if the barrier splits the basic block, then t is global (defined in B, used in C). global-alloc assigns it some reg. It got v0. The address is local in C → v1.

So in the target t IS global and global-alloc gave it v0. In my d_S2S3S4, t is global but global-alloc gave it v1. Why the difference? Because of the other code! In the target, the barrier also splits earlier, affecting the allocation order of other pseudos.

Hmm, this is getting deep. Let me try yet another thing: what if the *whole tail* (load, store, RMW) is wrapped in a do-while (d_ or e_ variants of a 3-statement block)? That doesn't split between them.

Alternatively: maybe the right shape is a `goto`-based block or an `if` that splits the block. Real C: an `if (1)` gets folded. A `switch`? folded. 

What about `while (0) {}`? A do-while(0) is the known trick.

Hmm, let me look at how similar items were cracked. Search moves.md for "barrier" MATCHes and their moves, especially "sched" ones. Also the walls.txt entry for sched1-load-delay-fill (G18 func_80180610).

Actually — maybe I should reconsider: maybe the natural lever-free body doesn't need the load in the same place. Let me reconsider the target: maybe a different C statement order makes sched1 produce the target naturally without a barrier. Since sched1 hoists the load to the top of the EBB, the EBB must start where the target's load is. The EBB starts after the last branch/call. The calls: `jal func_8012A828` at f08 ends... calls don't end EBBs in cse1? cse1's EBBs end at labels/jumps/notes.

Hmm, actually cse1's EBB ends at basic block boundaries, which include calls? No. In gcc, basic blocks end at jumps/labels; calls don't end blocks.

So the EBB here starts after the `if (v0 == 0)` branch's else label (the else block start). The load was hoisted to position 19, right after the else label. The target has it at 28.

What if the else block's beginning contains instructions that the load can't move above due to dependencies? The first instructions in the else block: `li v0,1; sh v0,2(s0)` (unk2 store), `li v0,1; sb v0,192(s0)`, `lui/addiu v0,D_801907D4; sw v0,188(s0)`, `li v0,0x8000; sh v0,92(s0)`.

If one of these stores *may alias* the load, the load can't be hoisted above it. The unkBC store stores a symbol address; the load reads unkC4. Same base.

What if we spell the unkBC store through a cast that makes gcc think it may alias? E.g. `*(s32 *)((s32)a0 + 0xBC) = (s32)&D_801907D4;` — still comparable.

What if we use a pointer variable for the base of the earlier stores that is *not* provably equal to a0? E.g., declare `s32 base = (s32)a0;` early? Then stores via base and the load via a0: `(plus (reg base) 92)` vs `(plus (reg a0) 196)` — different regs, no proof → dependent! But cse may equate base with a0? They're different pseudos; base = (s32)a0 is a copy that cse might propagate (make_regs_eqv). Hmm, if base is used in many stores, cse would canonicalize to one of them.

Ugh.

Let me step back and consider time. I've spent ~25 min on item 1. Budget 20-30 min. Let me check the clock.

Actually, let me reconsider the whole approach: maybe use `do{}while(0)` around the load AND make t global get v0 by adjusting global-alloc priority — e.g., give t more refs via a loop-weighted construct? No, keepalive is a lever.

Alternatively, the register swap v0/v1 might be fixed by a *declaration order* or by making the address variable explicit. What if we compute the address into a variable first?

```
s32 ad = (s32)&D_801907C4;
```
placed before... hmm.

Let me try: in d_S2S3S4 (score 2, order right, store position wrong), what if I add `s32 a = (s32)&D_801907C4;` as a separate statement before the load? Then the address is computed earlier (before the load) — but the target has it after the load. sched1 would order by source.

Hmm.

Wait, actually, let me re-examine d_S2S3S4's diff (score 2): the ONLY diff was the sw v1,88 position. Everything else matched, including registers (t v0, address v1). Let me re-read:

```
insert mine[31:31] target[31:32]: sw v1,88(s0)
delete mine[34:35] target[35:35]: sw v1,88(s0)
```
So mine: positions 28 lw v0,196; 29 lui v1; 30 addiu v1; 31 <missing sw>; 32? ...; 34 sw v1,88. And target: 31 sw.

Since only the store moved, the registers are right in d_S2S3S4! Wait, but d_S2S3S4 scored 2 while v_dw4 scored 7 with the v0/v1 swap. Let me recheck: d_S2S3S4 = do-while around S2 only = my earlier v_dw = score 2. Yes! The order was wrong (store sunk) but registers right.

So d_S2S3S4 has t in v0, address v1 — matching the target. Only the store placement differs: mine emits sw v1,88 at 34 instead of 31.

Now: can I get the store earlier? In d_S2S3S4, the block structure: block1 = load; block2 = store+RMW+rest. Within block2, sched1 put ori/sw before sw 88. The store's priority is low.

What if I split block2 so the store is in its own block? That's v_dw4 (7) which swapped the regs. Hmm.

What if I put the store in block1 with the load? That's e_S2S3S4 (7)? e_ wraps S2+S3 → the load and store in one block, RMW outside. Score 7 (regs swapped).

Hmm.

What if I reorder in block2: put the S3 store FIRST in the source of block2? In d_S2S3S4, the source order in block2 is S3 then S4. sched1 sank S3 anyway.

What if S3's store depends on something computed in block1 (the load)? E.g., store `(s32)&D_801907C4` — no.

Hmm, what if we make the store's value an expression involving t in an identity way? Not allowed.

OK here's another idea: move the unk58 store into the do-while with the load but ALSO move the RMW... no.

Let me try: do { t = unkC4; } while(0); then S3, S4 — what if S3 and S4 are swapped? That's d_S2S4S3 = 7.

Hmm.

What if we use two do-whiles but arrange so t stays in v0: do { t = unkC4; } while(0); do { unk58 = ...; } while(0); — v_dw4 gave t v1. Because t became global (used after two blocks).

What if we wrap the load + RMW in one do-while and the store in another, order load, store, RMW? dw2 = 7.

So the pattern: whenever the store is between the load and the RMW in different blocks, t is global and gets v1. When the store and RMW are in the same block as each other but after the load's block, t is global and gets v0 (d_S2S3S4). Interesting.

So global-alloc gave t v0 in d_S2S3S4 but v1 in v_dw4? Odd. The difference: in v_dw4 the store is in its own block between. Maybe global-alloc's allocation order/priority depends on the number of blocks.

Let me try a different split: keep block1 = load, block2 = store, block3 = RMW, but make t's live range not cross block2 — impossible since the RMW uses t after the store.

What if the RMW is in block2 with the store and the load is in block1 (d_S2S3S4) — that's our best.

So the remaining fix: get the store before the ori within block2. sched1 sinks the store. To prevent, we could make the store's address/value depend on the ori? No.

What if the RMW is written as two statements: `t = t | 0x2;` then `unkC4 = t;`? That changes the chain: the ori writes t (v0), then sw v0. sched1 might schedule the store earlier. Let me try:

```
t = unkC4;   (do-while)
unk58 = &D_801907C4;
t = t | 2;
unkC4 = t;
```
Hmm, that's the same data flow but with an extra copy; cse may merge.

Alternatively write the RMW store before the ori? no.

Let me try a few micro-variants in block2:
a) `t |= 0x2; unkC4 = t;`
b) `unkC4 = (t | 0x2);` same.
c) split: `unkC4 = t; unkC4 |= 2;` no (two loads).

Let me also try putting S3 in the do-while with S4 but not S2:
d_S3S4S2 = 14, no.

Hmm, what about a completely different tactic: change the *order of the earlier stores* so that the unk58 store is adjacent to the load in the source and sched1 keeps it? 

Actually, let me look at the target's schedule again:
```
lw v0,196       S2
lui v1          
addiu v1        S3 addr
sw v1,88        S3
ori v0,v0,2     S4
sw v0,196       S4
lw v0,32(s0)    next
li v1,16384
```
sched1 in the target did NOT sink the store. Why? Because with the barrier, block B is: S2, S3, S4, and the rest. sched1 scheduled the store right after its address. In my d_S2S3S4, block2 is: S3, S4, rest — and sched1 sank the store.

Difference: in the target's block B, the load S2 comes first and has a long latency; the scheduler issues it, then the address computation for S3 (independent), then the store (dependent on addiu), then ori (dependent on the load). Since the load has latency, the ori isn't ready until 2 cycles later; the store is ready 1 cycle after addiu. So the store goes before the ori. Natural!

In my block2 (no load in it), there's no load latency; the ori is ready immediately, and the scheduler chose the ori chain first. So the load's presence in the same block matters.

So: the block must contain the load AND the store AND the RMW — i.e., the barrier is *before* the load, and the block is NOT split after the load. That's the target.

But a do-while around S1 (v_dw5) split the block but produced a nop. Let me look at why: v_dw5 diff showed mine[29] nop vs target lui/addiu/sw. So the do-while around S1 added a nop before the load? Let me dump v_dw5's listing around there.

Actually mine[29] nop: mine had the load at 28? and a nop at 29. Hmm, the do-while around a single store might not be optimized away (loop with one iteration) and leaves a nop? It emitted a `j`/nop? The diff also showed mine[9] `j fb0` vs target `j fac` (just the target address shift from the extra nop).

So the do-while around S1 added 1 insn (nop). Not good.

Alternative: put the do-while around a *pair* of statements ending with S1, e.g., `do { unkBC = ...; unk5C = 0x8000; } while(0);` Then the EBB splits after, and the loop notes surround two stores. Might not add a nop? The nop might come from the loop structure (a backward branch). Hmm, `do{}while(0)` should be optimized to nothing by the loop optimizer... but it left a nop here. Odd.

Wait, maybe the nop is the load-delay slot: mine[28] lw v0,196; mine[29] nop — that would be a load delay nop inserted because the next instruction... no, sched1 doesn't insert nops; the assembler does for load delay when the next insn uses the loaded reg. Hmm, the target at 28 lw v0,196; 29 lui v1 — the lui doesn't use v0, so no nop needed. Mine had nop at 29 — meaning the instruction after the load used v0? Let me dump v_dw5.

Let me just dump the listing.
