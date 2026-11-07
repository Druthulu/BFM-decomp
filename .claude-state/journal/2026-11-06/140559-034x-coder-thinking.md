---
ts: 2026-11-06T21:05:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8VIAVbFRk45p2VZt7WWP
---
So:
- reg 95 (off): def insn 54, uses: insn 70 (address of lim) and insn 81 (plus e). n_refs = 3 (1 def + 2 uses).
- reg 79 (e): def insn 73, use insn 81. n_refs = 2.

Priority off > e, so off allocated first → a0 (mine). Target needs e first.

Now, how did the launder change this? The launder `__asm__("" : "=r"(e) : "0"(e))` produces an insn with e as input (use) and output (def), i.e., reg 79 gets +1 def and +1 use → n_refs = 4. Then priority e (4 refs) > off (3 refs) → e first → a0. Exactly.

So I need to give e a 2nd def+use, i.e., a real 2nd set. Options in real C that survive:

The launder essentially is: e = e (through a compiler-opaque operation). We need a genuine 2nd assignment of e.

Idea: assign e from an expression that isn't a simple symbol_ref: e.g., 
```
e = (s16 *)D_801E8F78;
```
then later, before the use, 
```
e = (s16 *)((u8 *)e);   // identity, optimized away
```
No.

What about a conditional 2nd set that's value-preserving:
```
if (t < lim) { ... } else { e = e; }
```
No, identity.

Real 2nd set from C0414: a dead reset is `e = 0;` — but here e must still be valid at insn 81. If we insert `e = 0;` AFTER insn 81 (after the condition), it's dead and removed.

Hmm. What if we restructure so e is assigned twice with both values used? For instance:

```
e = (s16 *)D_801E8F78;
...
// use e in the condition
...
```
The only use is in the condition. To add a 2nd set that's live, e must be used after it. There's no later use.

But wait — we can *create* a later use that doesn't change codegen: e.g., assign `p` or something using e after? Any use changes code.

Alternative: increase n_refs of e without a 2nd def: use e twice in a way cse can't merge. The two textual `*(s16*)((u8*)e+off+2)` were merged by cse. What if we make them NOT merge? Then e gets 2 uses, off gets 2 uses (already 2). Then n_refs: e=3, off=3 → tie → qty_compare tie-break by qty number. qty order... The tie-break `return *q1 - *q2` in qty_compare_1, and for qty_compare (non-1) let me check. Actually with 3 qtys or fewer, the switch handles. Hmm.

But making the two loads not merge would change the target asm (target has one load). So no.

What about making e's REG_EQUIV go away? A pseudo with REG_EQUIV might be treated specially. If e has REG_EQUIV, global-alloc can rematerialize. But local-alloc sees the pseudo. Actually REG_EQUIV is used by cse/global-alloc. Hmm.

Alternatively: reduce off's priority by extending its live range. If off's live_length is doubled, priority halves. off's live range: born insn 54, dies insn 81. Length ~27 insns. e: born 73, dies 81, length ~8. Priority = floor_log2(refs)*refs*size/live_length. 
off: floor_log2(3)=1, *3*4/27 = 12/27 = 0.44.
e: floor_log2(2)=1, *2*4/8 = 8/8 = 1.0.

Wait! e has HIGHER priority (1.0 > 0.44) because its live range is shorter! So e should be allocated first and get a0. But mine gives e a1. Contradiction!

Hmm, maybe my live_length numbers are off. Actually reg_live_length is computed differently (counts of insns where live, maybe with loop weighting). off is live from 54 to 81 = 27 insns. e from 73 to 81 = 8. So e priority higher. Yet mine assigns off a0.

Unless... local-alloc's qty_n_refs/live_length computed after combine; maybe off's live range got shortened or e's lengthened. Let me look at the .lreg dump for the actual assignment (hard regs). Let me check the .greg dump which shows global-alloc; but these are local.

Hmm, maybe I have the mapping backwards: maybe mine gives off=a1 and e=a0? Let me re-read the diff:

mine: 
32 sll a0,s0,0x2       ← off = a0
34 addu at,at,a0
36 lui a1,0x0          ← e = a1
37 addiu a1,a1,0

target:
32 sll a1,s0,0x2       ← off = a1
34 addu at,at,a1
36 lui a0,0x0          ← e = a0

So mine: off=a0, e=a1. Target: off=a1, e=a0.

So mine allocates off first (a0). Given my priority calc says e higher, something's off. Let me actually verify by checking reg_alloc_order for MIPS — maybe a0 is not first. In mips.h, REG_ALLOC_ORDER might be { 4,5,6,7, 8,...} or might start with 2 (v0), 3(v1)? Let me check. If reg_alloc_order = {0,1,2,...}? Let me grep mips.h.

Actually, the first free reg in alloc order is chosen. If the alloc order starts v0,v1,a0,a1,... then a0 before a1. But v0,v1 might be free or used.

Let me instead get the actual live_length/n_refs. GCC can dump with -dg? The .greg dump (-dg) is global-alloc. local-alloc doesn't have a dedicated dump of qty priorities. Hmm.

Wait — maybe the issue is not local-alloc but reload. Since e has REG_EQUIV, global-alloc might allocate e to a hard reg, but reload could rematerialize. Let me look at the .sched (post-reload) or .greg dump to see the actual hard regs.

Let me grep the .greg dump for the function region and the sll.

Actually, let me step back. Rather than deep-diving, let me empirically test moves that add a real 2nd set / use of e and see if any scores 0. Quick experiments are cheap.

Ideas to test:
A. Use e in the lim load via a separate variable that cse shares: `lim = ((s16 (*)[2])e)[idx][0];` — compiles? e is s16*, cast to s16(*)[2]. Let me test; may change code.
B. 2nd set: `e = (s16 *)D_801E8F78;` then `if (...) {...}` — no.
C. Split off: `lim = D_801E8F78[idx][0];` and use `e[idx*2+1]` for the condition instead of `(u8*)e+off+2`. That removes off from the condition (off used once, only lim address). Then off n_refs=2, e n_refs=2 (def+use). Hmm, and the code: condition address = e + idx*2*2 = e+off. Would cse recompute off? Actually if off is still used for the lim address (sym+off), and condition uses e[idx*2+1], the address is e + (idx*2+1)*2 = e+off+2. cse may compute e+off+2 from e and idx*2... could differ.

D. Make `off` live longer by defining it before `t = func_80029504()`? off needs idx which comes from the load after the call. Can't.

E. Define `off` from `idx` earlier: idx is defined at insn 48 (after the call func_80029504). off at 54. That's already immediately after.

F. Make off a s16 and compute in halfwords? `s16 off = idx * 2;` then use `e[off]` and `e[off+1]`? Then off is HI mode, shifts differ. Might change code.

G. Reorder: compute `lim` before `off` so off is born later (shorter live → higher priority → gets a0). That's the wrong direction; we want e to get a0. Wait, we want e first. Currently off first. To make e higher priority: e's live range shorter or refs higher. e's live range is already short. Hmm.

Hold on, let me reconsider whether priority is really the mechanism. Let me actually verify by looking at the .lreg dump's assigned regs. In -dl output, are pseudos renumbered? Let me check if "reg:SI 95" appears or "reg:SI 4" etc. The dump at line 384 shows reg:SI 95 — so local-alloc dump shows pseudo numbers still (renumbering applied at reload). Hmm, then the .lreg dump doesn't tell me the assignment.

Actually wait: GCC's -dl dumps after local-alloc where reg_renumber is set but the RTL still has pseudo regnos. The renumbering is applied in final. So I can't see assignment.

Let me instead look at the .sched dump (-ds) which is after reload (regs renumbered). Let me find the sll there.

Actually, easier: get the candidate .s asm (cand.s) — that's the final. But I already know from the diff.

Let me look at reload dump? The dump list didn't include -dR... yes it has cand.i.rtl maybe. Hmm.

Let me think about the priority differently. Perhaps off and e are not the competing qty; maybe the competition is between off and the *lim* pseudo, and e inherits.

Let me try: what if I make e's n_refs higher by a real 2nd set using C0414-style but live? Here's an idea: 

```
e = (s16 *)D_801E8F78;
lim = D_801E8F78[idx][0];
if (t < lim) {
    e = (s16 *)D_801E8F78;   // 2nd set, live: used below
    if (*(s16*)((u8*)e+off+2) == 0 || ...) idx = -1;
}
```
Here e is set twice, both live (first set's value used? No — the first set is only used... hmm the first set at line before lim isn't used before the 2nd set, so it's dead and removed). Unless we use it: e.g. `lim = e[idx*2]` uses the first e. Then second set inside if. But that changes lim's address to use e.

Alternatively:
```
e = (s16 *)D_801E8F78;
off = idx*4;
lim = D_801E8F78[idx][0];
...
if (t < lim) {
    e = (s16 *)D_801E8F78;  // 2nd set
    ...
}
```
First set dead → removed.

To keep both sets live, the first value must be used before the second. The only use is the condition. So:
```
e = (s16 *)D_801E8F78;
off = idx*4;
lim = ...
if (t < lim) {
    if (*(s16*)((u8*)e+off+2) == 0 || ...) idx=-1;
    e = (s16 *)D_801E8F78;  // dead after
}
```
2nd set dead → removed.

So a real 2nd set requires 2 uses, which changes code.

Hmm. What about increasing e's refs via the REG_EQUIV? 

Different angle: What if off is not a separate pseudo at all in the target? In target, `sll a1` is off, used twice. It IS separate.

Let me reconsider: maybe the fix isn't priority but the ORDER in which local-alloc processes qtys due to qty numbering, and the real difference is that the launder created a *second* def which split the pseudo into two qtys, changing things.

Actually the launder asm: `__asm__("" : "=r"(e) : "0"(e))`. This creates an insn: (set (reg e') (asm_operands... (reg e))). So e gets a new def (e') and e is used. The asm output e' is tied to e's reg. This effectively creates 2 pseudos? No, "=r"(e) means output goes into variable e, so e is both input and output, tied "0". So one pseudo with def+use, but it's a 2nd def.

This raises n_refs to 4 and makes e multi-set, which in local-alloc changes qty assignment.

Given the difficulty, maybe there's a simpler crack: the barrier/launder might be replaceable by other real-C that changes the scheduling such that a0/a1 swap naturally. Let me try a bunch of cheap variants and see if any hits 0:

1. `off` used for both, but reorder `e` assignment to before `off` (v2 tried, 4).
2. Use a different temp name/type.
3. Compute `off` via `idx << 2` (v3, 4).
4. Make `lim` an `s32` (already s32).
5. Use `e` declared as `void*` then cast.
6. Compute condition as `e[idx*2+1]`.
7. Compute condition as `*(s16*)((u8*)e + (off + 2))`.
8. Use a local `s16 v` for the load: `v = *(s16*)((u8*)e+off+2); if (v==0 || (func(v)&0xFF)==0)`.
9. Combine `off` into `e`: `e = (s16*)((u8*)D_801E8F78 + off)` then condition `*(s16*)((u8*)e+2)`, and lim still from sym+off. This makes e derived from off — e's birth after off, live shorter. Let's test! This might give e a0 (shorter live, born later) and off a1.

Actually idea 9 is promising: e = (s16*)((u8*)D_801E8F78 + off). Then e is e0+off. But target's e is the bare symbol address (lui+addiu), and target computes the condition address as e+off (addu a0,a1). If e is already e0+off, the condition address = e+2 (addiu). That changes code (target does addu). So no.

Let me test 6, 7, 8. Also test making the condition use `off` twice differently.

Actually, wait. Let me reconsider the target asm again:
```
80: sll a1,s0,2         off
84: lui at, sym
88: addu at,at,a1       at = sym+off   (lim address)
8c: lh v1,0(at)         lim
90: lui a0, sym
94: addiu a0,a0,0       e = sym
98: slt v0,v0,v1        t<lim
9c: beqz
a0: addu v0,a0,a1       v0 = e+off
a4: lh a0,2(v0)
```

Mine:
```
sll a0,s0,2         off=a0
lui at,sym
addu at,at,a0
lh v1,0(at)
lui a1,sym
addiu a1,a1,0       e=a1
slt
beqz
addu v0,a1,a0       (e+off)
lh a0,2(v0)
```

So only the reg assignment differs. The instruction sequence identical.

Now, priority: I computed e should have higher priority. But it doesn't get a0. Unless find_free_reg's first free reg isn't a0. Let me check REG_ALLOC_ORDER in mips.h. If alloc order is v0,v1,a0,a1,... and v0,v1 are live (v0 holds t? at insn 76 v0 is used then dead; v1 holds lim), then at the allocation, but local-alloc considers the whole block's liveness. v0 and v1 are live in this block (v0=t from call, v1=lim). So they're taken. Next a0. So a0 to first allocated.

If e has higher priority it should get a0. It doesn't → e's priority is lower. So my live_length estimate must be wrong. reg_live_length is computed with loop depth weighting and might count differently. Let me look at how reg_live_length is computed — maybe it's the number of instructions in the *range* or "length of live range" measured from first to last reference, and e's REG_EQUIV might not count as a ref at def? 

Actually reg_n_refs and reg_live_length are computed in flow.c. Let me check: reg_live_length = (last_use - first_use)? And n_refs counts. Hmm.

Let me look at local-alloc's own qty_n_refs: `qty_n_refs[qty] = reg_n_refs[regno]`. And reg_n_refs from flow counts references. For reg 79 (e): def insn 73 + use insn 81 = 2. For reg 95 (off): def 54 + use 70 + use 81 = 3.

reg_live_length: in flow.c, computed as total length of live ranges. For e: from 73 to 81. For off: 54 to 81. But there's also the "death" — reg 95 dies at 81 (REG_DEAD). reg 79 dies at 81.

Hmm so e live 8, off live 27. e pri = 1*2*4/8=1; off = 1*3*4/27=0.44. e > off. But empirically off gets a0.

Unless find_free_reg is called with just_try_suggested first (line 2197) and copy suggestions matter. Let me read lines 2190-2230.
