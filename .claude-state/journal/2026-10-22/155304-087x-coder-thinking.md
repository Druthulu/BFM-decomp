---
ts: 2026-10-22T21:53:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0IcLEGu3JUc7dOdZj9SP
---
Still 15. Time: 16:10, item 4 at 22 min, 22 tries.

Let me reconsider. The target's block: after `lh v1,524(s0)`, the nop. For sched1 to leave a nop, no independent insn may be ready.

The stores `D_80126976 = -0x60` etc. are independent. The barrier blocks them. In plain C, the only way to block a store from moving up is a memory dependence or a barrier.

Memory dependence idea: what if the -0x60 stores write through a pointer that *could* alias the lh's address (s0+524)? The lh reads `((Unkstruct*)a0)->unk20C` — a memory read via a pointer. If the store's address were also via a pointer of unknown provenance, sched1's alias analysis (true_dependence) would see a potential conflict and order them.

So: write the stores through a pointer variable whose value is the global address:
```
s16 *p = &D_80126976;   // p = symbol → folds to constant
```
gcc would fold p to the symbol constant, giving the same `lui at; sh`. But at sched1 time, if p is a pseudo register holding the address (not folded), the store would be `(mem (reg p))` — and the asm would be `sh v0,0(p_reg)` with p in a register (e.g. $at or a saved reg) — different asm.

Unless the pseudo is rematerialized as the constant at reload → `lui at; sh v0,0(at)`. That's possible! gcc rematerializes constants. Risky but worth a try: 

```
s16 *p = (s16 *)&D_80126976;
...
*p = -0x60;
```
Hmm, but the address differs for each store (70, 74, 76, 7A).

Alternatively use one base pointer with offsets: `s16 *p = &D_80126970; p[3] = -0x60; p[0] = -0x60; p[5] = -0x80; p[2] = -0x80;` — then the stores are `(mem (plus (reg p) (const)))` and the asm would be `sh v0,6(p)` etc. If p is rematerialized to the symbol, we'd get `lui at; addiu at,at,lo; sh v0,6(at)` — that's 3 insns vs the target's 2 (lui at; sh v0,0(at)). Hmm, the target uses separate symbols (D_80126976 etc. with their own lui/sh), which is the `lui at,%hi(sym); sh v0,%lo(sym)(at)` form (2 insns).

So a base+offset spelling gives different asm. Unless each store uses its own symbol (current form).

OK. Given the difficulty, and that the -0x60 group is only 5 insns off... 

Alternative: make the *lh* not be the first insn, e.g. by moving the table read earlier so the load-delay slot is filled by something harmless? The target's nop is required.

Hmm, what if the table read's `lh` load delay is filled by a nop because the *store group* is not ready due to `at`... no, pre-alloc.

Let me try one more class: what if the -0x60 stores are written as `D_80126976 = -0x60; D_80126970 = -0x60;` where D_80126970 is declared as s16 (not u16 cast)? The source uses `*(s16 *)&D_80126970` because D_80126970 is u16. Writing `D_80126970 = -0x60;` would fold to 0xFFA0 and cost a second li (per the comment). But maybe it changes the schedule in a useful way. Cheap to test.

Also: what if the two -0x60 stores are ordered 70 then 76? (target emits 76 then 70? The comment says source order 62 then 6A to emit 6A then 62 for the v1 pair.)

Let me test:
m1: D_80126970 = -0x60 (u16 assign, no cast) for both.
m2: `*(s16 *)&D_80126970 = -0x60;` first, then D_80126976.
m3: `D_80126976 = -0x60; D_80126970 = -0x60;` both as u16.

Time-box: 3 more minutes, then WALL (I have 22+ tries; need 30 for a WALL — I'll run more variants).

Actually, let me reconsider the problem completely: maybe the answer is to make the *table read* not be a load at the top — e.g. reorder so that the `lh` comes later. No.

Hmm, here's another thought: the barrier is `__asm__("")` placed after the table read. In the target the nop is the load-delay slot of `lh v1,524(s0)`. 

What if I make the table read's result feed the index AND make the stores depend on the index chain? For instance, if the -0x60 stores' addresses were computed from the index... no.

OK, one more idea: what if I introduce a second, earlier use of v1 that is a *memory store*: e.g. `D_80126962 = v1;` moved before the -0x60 group? j8 tried (15).

Let me try m1-m3 and then WALL if no luck. Actually, let me also try: put the -0x60 group *before* the table read statement in source (so it's above the lh) — then it can't be hoisted into the delay slot (it's already above)... no, the target has it after.

Time: 16:12. Let me run the last batch (m1-m6) and then decide.
