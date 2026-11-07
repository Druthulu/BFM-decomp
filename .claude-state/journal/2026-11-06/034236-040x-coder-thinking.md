---
ts: 2026-11-06T10:42:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zqio3DPXjphOdCSw6oFG
---
Now I see the full picture. v_dw:
```
f34 lw v0,196
f38 lui v1
f3c addiu v1
f40 ori v0,2
f44 sw v0,196
f48 lw v0,32(s0)      <- the unk20 load for the 0x4000 stores!
f4c sw v1,88
f50 li v1,16384
```
Target:
```
f34 lw v0,196
f38 lui v1
f3c addiu v1
f40 sw v1,88
f44 ori v0,2
f48 sw v0,196
f4c lw v0,32(s0)
f50 li v1,16384
```
So mine sank the sw v1,88 below the lw v0,32(s0) too. Interesting: sched1 grouped the ori/sw of unkC4 with... and put the sw 88 after the unk20 load.

Hmm, why does sched1 prefer that? The store sw 88 depends on the addiu; the ori depends on the load. Priority: the load lw v0,196 is a load with latency; ori/sw. Actually sched1 might be avoiding placing the store in a load-delay slot? No, MIPS has no load delay in the R3000 model with -mips1? It does (load delay slot) but gcc's mips.md... Actually the `nop` after loads in the target suggests load-delay slots are respected.

Look: in the target there are `nop`s after `lw v0,32(s0)` at f4c/f50 etc. Mine has no nop after lw v0,32(s0) because sched1 filled it with sw v1,88! That's a delay-slot fill issue. Hmm no, this is sched1 (pre-reload), so no delay slots yet. The nops in the target come from the assembler/reorg (load delay). Actually `-mgas` means the assembler handles the delay slots? maspsx expands. The `nop`s in the target appear after loads: `lw v0,32(s0); nop; a4430018` — that's a load delay nop inserted by the assembler. In mine at f48: `lw v0,32(s0); sw v1,88` — the store fills the load delay slot, which is valid on R3000 (load delay: the instruction after the load cannot use the loaded reg; a store is fine). So the assembler doesn't insert a nop.

So the difference is sched1's ordering choice. In the target (with the barrier), the block boundary after the load forced the order.

The key: I need the sw 88 to be emitted right after the addiu, before the ori. That means the ori/sw chain must not be ready earlier. 

What if we make the unkC4 RMW depend on the unk58 store's value? Semantically no.

What if we put the unk58 store in the do-while with the load but keep the *address* computation out? Hmm, the address is computed by the store itself.

Alternatively: what if we compute the unk58 address BEFORE the load in the C? e.g.
```
s32 a = (s32)&D_801907C4;
t = unkC4;
unk58 = a;
unkC4 = t|2;
```
Then the lui/addiu might be scheduled before the load... but the target has the load first.

Hmm, target: load (f34), lui/addiu (f38-f3c), sw (f40), ori (f44), sw (f48).

So the schedule is: load, then address, then store, then RMW. That's exactly source order. The mine schedule moved the store after the RMW and the next load.

Let me consider the sched1 priority: the store to 88 has no dependents (a store is a sink). sched1's priority = max over dependents; stores have priority 1 + ... low. The ori has the load as a predecessor; the load was issued at f34 with latency 2, so the ori is ready later. Hmm.

What if we make the store depend on the ori's result? Not semantic.

What if we reorder the C so the store comes after the RMW in source? Then sched1 might schedule it before (hoisting stores? sched1 can hoist stores too if no alias). If source is:
```
t = unkC4;
unkC4 = t|2;
unk58 = &D_801907C4;
```
then sched1 might hoist the store up to right after the address computation... which is where we want. But would it hoist above the ori? Stores are not usually hoisted (they have memory dependencies). sched1 does move stores up if safe. Hmm, the target order has the store BEFORE the RMW in the final code, so if source has it after and sched1 hoists it, that's possible.

Let me try: v_swap: move the unk58 store after the unkC4 RMW in the C, with the do-while around the load.

Actually, maybe simpler: no do-while at all, but reorder statements. Let's brute force a few statement orders and score. Each score is ~3-5s. Let me write a generator producing all permutations of the relevant statements? That's a lot but cheap.

The tail statements:
S1: unk5C = 0x8000;
S2: t = unkC4;
S3: unk58 = &D_801907C4;
S4: unkC4 = t | 2;

Target schedule: S1, S2, S3, S4. Source with barrier: S1,[bar],S2,S3,S4.

Let me enumerate source orders with the do-while and without. 24 permutations × 2 = 48 scores; ~4 min. That's within budget. But maybe smarter: think about which order yields the target.

Actually, maybe there's a much better approach: the *natural* lever-free body might use `|=` instead of the temp:
```
unkC4 |= 0x2;
```
This creates a read-modify-write as one insn pair. Then sched1 might schedule it differently. The target's ori/sw is exactly `|=`. Let me test `unkC4 |= 0x2;` (removing t entirely) with no do-while.

Let me try that: v_or.
