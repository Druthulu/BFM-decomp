---
ts: 2026-11-06T10:45:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZUkd0W8YI5o5VaM42ABZ
---
v_dw5's schedule: lw, nop, ori, sw, lw(32), lui, addiu, sw 88. The store got pushed after the next load. This is sched1 reordering.

Hmm, so the do-while around S1 did NOT reproduce the target's schedule. The target's schedule has the load first, then the address, then the store, then the ori. The scheduler chose: load, ori, sw, then address, sw — because it didn't have the "load latency" logic? Wait, mine put ori right after the load with a nop (load delay). The target put lui/addiu between the load and the ori, filling the load-delay slot usefully.

Hmm, sched1 in the target produced: load; lui; addiu; sw; ori; sw. That's a good schedule: the lui/addiu fills the load delay.

Why did sched1 in mine (v_dw5) prefer ori immediately? Because sched1 doesn't model load delay (the nop is inserted later by the assembler). Hmm.

Wait, but the target's schedule IS from sched1 with the barrier. So the difference must be the block structure/priorities.

Ugh, this is subtle. Time check: I've spent a lot on item 1. Let me check the time.

Actually, maybe I should reconsider: is the barrier really the cause of the target's schedule? Yes, since orig has it and orig=0.

Let me think about the target's block B with the barrier: sched1 sees block B = [load S2, addr S3, store S3, ori S4, store S4, load unk20, li, sb, sw, sh, load unk20, ...]. sched1's list scheduling picks ready insns by priority. It produced: load S2, lui, addiu, sw 88, ori, sw 196, load unk20, li, sb, sw, sh...

In v_dw5, the block after the do-while should be the same content... but the schedule differs (load, ori, sw, load unk20, lui, addiu, sw 88). So the block content/structure differs. Maybe the do-while created an extra block boundary or the loop notes changed the priority computation.

Honestly, the do-while may be the wrong tool here. Let me look at the walls list and think about whether this item might be a WALL. But 3 of 4 items are the same family? Items: func_8018966C and func_80189F7C are nearly identical (same 63-ins shape). func_80187EA0 is 144 ins (same as 8018B238 shape?). Actually func_80187EA0 and func_8018B238 both 144 ins — likely the same HUD function in different overlays! Let me check: 80187EA0 in ov_SC03_124 and 8018B238 in ov_SC03_001 — both "build the SC03 HUD display list". They're probably near-identical. So I have 2 families × 2.

Let me look at func_80187EA0's orig to confirm.

But first, let me reconsider the strategy for the small pair. Maybe I should try harder with a smarter idea: the target's schedule arises from the barrier. What real-C construct acts as a scheduling barrier at exactly that point without a block split?

Hmm: a `volatile` store/load. If I make the unk5C store volatile, it becomes a scheduling barrier? A volatile store can't be moved relative to other volatile accesses, but sched1 treats volatile insns specially (they're never moved). Actually in gcc, volatile MEMs are not scheduled (sched1 won't move them, and they act as barriers). Let me test: `*(volatile u16 *)&s0->unk5C = 0x8000;` Hmm, but a volatile store to unk5C — the target's sh is the same. sched1 would treat it as a barrier? In sched1, volatile insns get a very high priority and are not moved? Let me check gcc 2.7.2 sched.c: there's `insn_is_volatile`? Hmm.

Actually in sched.c, `volatile_insn_p` exists? Let me grep the reference source.

Alternatively, the classic: an asm is the barrier. But we must remove it.

Wait, maybe I'm overcomplicating. Let me reconsider the possibility that a different statement *order* in the C gives the target schedule without any barrier. E.g., if the source order were:
```
unk5C = 0x8000;
unk58 = &D_801907C4;
t = unkC4;
unkC4 = t|2;
```
then sched1 might hoist the load above the store (independent) giving: load, lui/addiu, sw, ori, sw? But earlier p_S3S2S4 (no do-while) scored 11 (load hoisted to 19). Hmm.

What if the load is placed in the source *after* all the following stores? Then sched1 hoists it to the top anyway.

The hoisting is the problem: the load always goes to the top of the EBB. So we need the EBB to start at the load's position. The EBB boundary must be created by something between unk5C and the load.

What creates an EBB boundary in cse1? A label, a jump, a call? Actually `cse_insn` EBB ends at CODE_LABEL, JUMP_INSN, CALL_INSN, and notes? Let me check gcc 2.7.2 cse.c: in `cse_main`, EBB is tracked: 
```
if (GET_CODE(insn) == NOTE) ... 
if (GET_CODE(insn) == CODE_LABEL || GET_CODE(insn) == JUMP_INSN || (GET_CODE(insn) == CALL_INSN && ...))
  prev_insn = 0; (new EBB)
```
Actually there's a function `insn_...`. Let me grep.

But the *scheduler* (sched1) works on basic blocks, not EBBs. Hmm, but sched1 splits blocks at `NOTE_INSN_LOOP_BEG`? 

Let me look at sched.c's block boundary logic and what the barrier does. The asm volatile probably ends a basic block via `can_throw`? No. Hmm, in gcc 2.7.2, an asm volatile is just an insn; sched.c has `may_trap_p` and for volatile insns it sets `insn->volatile`? Let me grep sched.c for "volatile".

Let me do that — it's fast and grounded.
