---
ts: 2026-10-22T00:26:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Ss0ZhJsZot3l95woYCWm
---
The target's listing (rows 20-40):
```
20? ...
26 lw v0,108(s1)
27 nop?
28 lhu v0,6(v0)
29 lui v1,0x0
30 addiu v1,v1,0
31 sh v0,0(v1)
32 lw v0,108(s1)
33 nop
34 lhu v0,10(v0)
35 nop
36 addiu v0,v0,-64
37 lui at,0x0
38 sh v0,0(at)
39 lw v0,108(s1)
40 lui a1,0x0
41 lhu a1,0(a1)
42 lhu v0,14(v0)
```
The nops at 33 and 35: after "lw v0,108(s1)" (32) there's a nop, and after "lhu v0,10(v0)" (34) a nop. These nops are in the delay slots of... hmm, there's no branch there. So they're standalone nops — which in this compiler come from the "reorg" pass leaving a hole (e.g. a barrier where an instruction could have gone but the barrier prevented it).

These nops are exactly the "asm barrier" artifacts: the asm insns (with memory clobbers) are in the RTL and occupy slots; the assembler... hmm, but an asm with an empty template emits no instruction. Hmm, but gcc's reorg might leave a nop where the asm was scheduled (the asm is a "insn" for the scheduler but emits nothing → the final code has a hole → a nop? Actually a hole in the instruction stream is filled with a nop by the assembler ✓).

So the target's nops correspond to the 2 asm statements (v6 and p10 launders) — hmm, but the nops are at 27, 33, 35 (3 nops) and there are 2 asms. Hmm.

Anyway: the target's nops are the asm's footprints. Without the asms, we can't have those nops → the count differs → item 4 can't MATCH without the asms?!

Hmm, but wait: the nops could also be produced by other means (a hole in the instruction stream). E.g. if the scheduler leaves a gap. Hmm, in the target, the nop at 33 is right after "lw v0,108(s1)" and before "lhu v0,10(v0)" — a gap between two loads. And 27 (before "lhu v0,6(v0)")? Let me see rows 20-28.

Actually, the row numbering: the log starts at row 20 (I dumped from index 20). Let me get rows 20-28 to see.

Given the nops' positions, they look like the asm footprints. Since the row kind is "launder" and the nops are needed for the count... the nops are a byproduct of the asm. Without the asm, we can't reproduce them (a plain C body has no holes). Hmm! Unless the holes come from something else (e.g. the original game's code had nops there — the target is the ORIGINAL game's code, which had nops for its own reasons!).

Ah, right: the target is the original game binary. Its nops are the original compiler's. Our gcc 2.7.2 reproduces them only because the asm barriers create the same holes. Without the asm, we can't create holes... unless some other construct creates a hole (e.g. a `do {} while(0)`? no).

Hmm! But note: the target's nop at 33 is between "lw v0,108(s1)" and "lhu v0,10(v0)" — a hole where the original had... hmm, in the original game code, maybe there was a nop for a delay slot.

So item 4 = WALL (the target's nops are the asms' footprints; a lever-free body has no holes → the instruction count can't match).

Hmm, wait. Let me double check by computing: the target has 111 insns; base.c (launders removed) has 110 → only 1 fewer. So removing the 2 asms removed 2 nops? and something else added 1? Hmm.

Let me just check: is the residual in base.c mostly the nops? The base diff showed the store/load order differences, not nops. Hmm.

Let me try a different approach for item 4: since the nops and the ordering both come from the asms, and the row kind is "launder", maybe the answer is a WALL.

Hmm, but hold on. Let me reconsider: are the nops really from the asms? Let me look at the base.c diff again:
```
26  lw	a1,108(s1)                      | lw	v0,108(s1)
28  lhu	v1,6(a1)                       | lhu	v0,6(v0)
29  lw	a1,108(s1)                      | lui	v1,0x0
30  --                                 | addiu	v1,v1,0
31  lhu	v0,10(a1)                      | sh	v0,0(v1)
32  lui	at,0x0                         | lw	v0,108(s1)
33  sh	v1,0(at)                        | --
34  --                                 | nop
```
The target has "nop" at 34 (in the diff's right column) — so the target's nops appear in the diff.

Since the diff is a sequence alignment, the nops' positions are entangled with the ordering.

OK, decision: item 4 = WALL (tag: sched1-barrier-nops? or "asm-nop-footprint"). Hmm, I need a wall tag from walls.txt or a new `<pass>-<what>`. walls.txt has: cse-const-addr, sched1-argcopy-hoist, sched1-birth-boost, callee-saved-order, flow-unused-result, sp-stack-switch, no-c-spelling, hand-asm, hand-placed-asm.

For item 4, the closest existing tag: "sched1-birth-boost"? Hmm, the mechanism is: the launder is a *memory barrier* whose nops and ordering cannot be reproduced without an asm. Maybe "hand-asm" (the target's instruction stream contains holes that only an asm can produce). Hmm, "hand-asm: hand-written body or prelude" — not quite.

New tag: `sched1-mem-barrier` — the launder's "memory" clobber is a memory barrier: the loads after it cannot be reordered above the store, and its footprint leaves nops that no C construct reproduces.

Let me use the tag `sched1-mem-barrier` (a new `<pass>-<what>` tag, allowed: "a new `<pass>-<what>`").

Hmm, but before declaring the WALL, let me try ONE more thing for item 4: what if the *store* is moved in the source so that the natural order matches? E.g. put the `o = CAST_ALIAS(...)` + `D_8019004A = ...` block AFTER... it is after. Hmm.

What if the v6 load's dest gets a 2nd set via a compound assignment, e.g.:
```
v6 = ((Unkstruct_80185380_2 *)o)->unk6;
v6 &= 0xFFFF;   /* no-op for u16 */
*p10 = v6;
```
Probably folded.

Hmm, what about giving the v6 load a 2nd set by using v6 twice? E.g. `*p10 = v6;` and... no.

I'll declare item 4 a WALL with best=28 (v1) — hmm, "best = lowest score of a lever-free body": v1 IS lever-free (both launders removed) → best = 28. And base = 39. So best = 28, tries = 2 (base, v1).

Hmm, wait: is v1 really lever-free? Yes: the launders are removed and I added no new levers (just a fresh temp) ✓.

Let me also try one more quick variant for item 4: combine v1 with a fresh temp for the unkA value and for v6:
V2: v1 + `s32 t = ((Unkstruct_80185380_2 *)o2)->unkA;` hmm, the store D_8019004A = ... - 0x40 is a global store; its value's temp.

Hmm, the "unkA" load: `lhu v0,10(v0)` — the load of unkA. Its dest is a temp (single-set) → boosted → should be placed late. In mine it's early. Hmm, why? Because its consumer is the "addiu v0,v0,-64" and the store "sh v0,0(at)" — the value is used by the store (D_8019004A = ...). Hmm.

Let me try V2: give the unkA load a fresh temp and use it:
```
            t2 = ((Unkstruct_80185380_2 *)o2)->unkA;
            D_8019004A = t2 - 0x40;
```
That's the same as before (a temp either way).

Hmm. What about the ORDER: in the target, the sequence is [o1][v6][p10][store][o2][unkA][-64][store]. The o2 and unkA loads are after the store. In mine (base): [o1][v6][o2][unkA][p10][store].

What if we make the o2 load *depend* on the store? E.g. hmm.

What if the second block is moved in the source to AFTER the first block's... it already is.

Honestly: the fundamental issue is that gcc's scheduler hoists the o2/unkA loads above the store because they're independent and the store is a MEM with a lower priority. The target has them after due to the barrier.

Hmm, what if the store's PRIORITY were higher? The store's pri comes from the v6 load chain (pri 2 → 3). The o2 load is pri 2, the unkA load pri 3. Hmm, the store (3) vs the unkA load (3) → the LUID tie-break → the unkA load (later source) is placed later ✓ target. But mine places it earlier → so in mine the store's pri > 3, e.g. 4?

The store's chain: v6's load (pri 2) → the store = 3; p10's materialization (pri 1) → 2. Hmm.

Hmm, but wait: in mine, the p10 materialization is boosted (single-set) → max_priority → the store's pri = max(max_priority+1, ...) → the store's pri becomes very high → the store is placed LATE ✓ (mine). And in the target, the p10 materialization is NOT boosted (the launder gives p10 a 2nd set!) → pri 1 → the store's pri = 3 → the store is placed before the unkA load (pri 3, higher LUID) ✓ target.

So the p10 launder's effect = killing the boost of p10's materialization (so the store's priority isn't inflated).

So: to reproduce, p10's pseudo must have 2 sets (so the materialization isn't boosted). p10 = &D_80190048; then *p10 = v6. p10's pseudo has 1 set.

How to give p10's pseudo a 2nd set in plain C? Hmm! What if the store is written as `*p10 = v6;` and ALSO p10 is used again later? E.g. `*(u16 *)((u8 *)p10 + 0x10) = g5e;` — YES! Look at the source line 3184: `*(u16 *)((u8 *)p10 + 0x10) = g5e;` — p10 is used again! But that's a use, not a set.

Hmm, so p10's pseudo has 1 set, 2-3 uses.

To give it a 2nd set: hmm, what if p10 is assigned twice: `p10 = &D_80190048;` and later `p10 = &D_80190048;`? gcc would CSE the second (the same value) → 1 set.

What if the second assignment is to a different value that's the same at runtime? no.

Hmm, what about making the pointer a *fresh* variable? E.g.:
```
u16 *p10 = &D_80190048;
```
vs
```
u16 *p10;
p10 = &D_80190048;
```
same.

Hmm, what if the address is computed differently: `p10 = (u16 *)&D_80190048 + 0;`? A "no-op" addition → gcc folds it.

Hmm. What if the *use* of p10 is a compound assignment: `*p10 = v6;` → hmm, what about `*p10 += 0;`? That would be a read-modify-write → an extra load. No.

Hmm, what if we use p10 in a way that creates a 2nd set of the p10 pseudo: e.g. `p10 = p10;`? Folded/dead.

OK, so for item 4 we need a 2nd SET of p10's pseudo that survives. Hmm.

Alternatively: kill the boost differently — the boost applies to a "SET(REG, ...)" insn with REG_N_SETS(dest)==1. What if the materialization of &D_80190048 is not a SET but part of a bigger insn? E.g. if the store were written as `D_80190048 = v6;` (a direct global store instead of through p10)! Then there's no p10 pseudo at all — the address is materialized as part of the store ("lui at; sw v0,0(at)").

Hmm! But the target has "lui v1,0x0; addiu v1,v1,0; sh v0,0(v1)" — the address in a register (v1), not "at". And the later use `*(u16 *)((u8 *)p10 + 0x10) = g5e;` → the target has "lui at,0x0; sh v1,0(at)" (43-44) — hmm, different registers.

So the target keeps p10 in a register (v1) for the first store and materializes the address again (in `at`) for the second store. Interesting: so p10's register (v1) is used for the first store, and the second store re-materializes the address.

If I write the first store as a direct global store `D_80190048 = v6;`, the code would be "lui at; sw v0,0(at)" — different from the target's "lui v1; addiu v1; sh v0,0(v1)". So no.

Hmm, so the target's p10 is a register-held address. And that p10 pseudo has 1 set in the source but the launder gives it 2.

OK: item 4 = WALL. best = 28 (v1), tag: sched1-birth-boost (the p10/v6 materializations' boost must be killed; only an asm re-tie can give those pseudos a surviving 2nd SET).

Hmm, actually the tag "sched1-birth-boost" exists in walls.txt ✓ — perfect fit: "birthing-insn priority boost against a local-alloc constant". I'll use it with the mechanism described.

Now, time is pressing. Let me quickly assess the remaining items: 6 (func_80180054), 7 (func_8017E780), 1 (func_801832A8), 2 (func_8018389C).

Item 7: func_8017E780 in ov_SC03_092, launder at 4739: `__asm__ __volatile__("" : "=r"(t) : "0"(t));`. Let me look at it.

Item 6: func_80180054 in ov_SC03_030, launders at 5435-5466 (xa, xb, p) — several, with whitespace templates (" " , "  " etc. — those are non-empty templates → they're "instruction"-ish levers? The templates are just spaces → no instruction, but a non-empty template makes it a "keepalive"/barrier?).

Let me look at both quickly.
