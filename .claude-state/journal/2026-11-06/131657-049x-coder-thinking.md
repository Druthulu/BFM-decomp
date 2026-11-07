---
ts: 2026-11-06T20:16:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i4kKsuas2r1TfFFEgjoZ
---
Baseline without launder: score 11, 177 insns both. The differences are register allocation (a0/a2 swapped for bidx) and scheduling (lw v1 in delay slot vs later).

Interesting: the bidx register is a0 in mine, a2 in target. In the pinned orig (score 0), bidx is a2 (target). So the launder affected the allocation of `bidx` too? Because pv's extended live range changed the pressure.

Now the challenge: lever-free real C to (1) get the lw into the delay slot, (2) get bidx into a2, (3) lui a0,0xff00 in the right place.

The notes say the launder gives pv a 2nd set at the end, making pv's live range global → this kills the sched1 birth boost on the pv load. Also the pins ang/pv are kept.

Real-C replacement for the launder that creates a real 2nd set of pv at the end that survives cse/flow:
- C0414 dead-reset: `pv = 0;` — flow deletes it if pv is dead. But is pv dead at the end? pv is a local, dead after its last use. A `pv = 0;` at the end would be deleted by delete_dead_from_cse (cse1). The note says exactly this.

- Make pv live to the end via a use that doesn't emit code: hard in C.

- What about reusing pv in the second addPrim half: `pv = ((Unk*)ot)->unk40;` then `((Unk*)ot)->unk40 = (pv & 0xFF000000) | ((u32)p & 0xFFFFFF);` This is a real read-modify-write with the same local pv. That gives pv a second set (the load of ot->unk40) and a use. The note says this "makes pv a 2-death GLOBAL allocno that loses $v1" — but pv is pinned to $3 now, so it can't lose $v1. Let me check: does the target's second half use v0 for the ot->unk40 load and s1 for p? Target: `lw v0,0x40(v1); and s1,s1,a3; and v0,v0,a0; or v0,v0,s1; sw v0,0x40(v1)`. So the ot->unk40 value is in v0, and p in s1. If I write it with pv, the compiler might put the loaded value in v1 (pv's pinned reg), which would NOT match target (v0).

Hmm. So reusing pv for the second half changes the register of that value → mismatch.

Alternative: give pv a second set that doesn't change code. The asm launder sets pv to an unknown value at the end (no instruction). Any C assignment emits an instruction (li/load) unless it's dead (then removed).

What about a second set that is a *copy of another live variable* which then gets coalesced away? E.g., `pv = p;` at the end — p is s1, pv is $3=v1. That emits `move v1,s1` (1 insn) → +1 insn, not matching (177 vs 178).

What if the second set is `pv = pv;`? cse1 removes self-copies? Actually gcc: `pv = pv` — the tree may keep it; cse's copy propagation would likely delete it. Worth a try.

What about a set of pv inside a `do{}while(0)` that cse can't fold? C0535: do-while splits cse1 EBB. `do { pv = pv; } while (0);` — cse1 processes each EBB; a self-set is redundant within the block and deleted.

Hmm.

What about making the second set *conditional on a value that flow can't prove*: e.g. `if (p == 0) pv = 0;` — adds a branch. No.

Wait, maybe the launder's real effect can be replicated differently: the goal is to kill the sched1 birthing boost on the `pv = *(u32*)p` load, i.e., make pv's pseudo have 2 sets so it isn't a "single-set" birthing-boost candidate. Actually sched1's birthing boost applies to insns whose dest is set once in the function (REG_N_SETS == 1). If pv has 2 sets, no boost.

So: any C construct that makes pv's *variable* have 2 sets in RTL, surviving cse1, without adding instructions.

Ideas:
- Use pv in a loop that's unrolled/removed? no.
- Assign pv in a branch that's dead but not provably: `if (arg0 & 0x80000000) pv = 0;` — changes code (branch).
- `pv = (arg0, pv);` comma — same as pv = pv.
- `pv = *(u32 *)p;` twice? Second load would be cse'd (redundant load from same address, no intervening store to *p... actually there IS a store to *p between them: `*(u32*)p = ...`. So a second `pv = *(u32*)p;` after the store would be a real load (+1 insn). No.

Hmm, but wait: what about writing the first half as a read-modify-write using pv *twice*: 
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (...);
```
Already 1 set.

What about making `pv`'s second set happen in the second half but on the SAME value that target keeps in v1? In target, after the first sw, `lhu v1,0(a2)` reuses v1 for the bidx. So v1 is reused. If pv had a second set at the end, pv's live range would span... no, the asm at the end sets pv, extending the *variable* but the register allocator might still reuse v1 in between since the pseudo is dead after its last use.

Hmm — the launder creates a second pseudo for pv (a new set = new pseudo), so pv's variable has 2 pseudos; the second pseudo is born at the asm (end of function) and dies... The effect on sched1: the *first* pseudo (the load) now has REG_N_SETS for the variable = 2? sched1's birthing boost uses REG_N_SETS? Let me check sched.c for the boost condition.

Let me look at the sched1 birthing boost code.
