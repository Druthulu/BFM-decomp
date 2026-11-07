---
ts: 2026-11-06T10:52:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_strZ5xYOpaWYsZtcGiVK
---
The schedule: lw, lui, addiu, ori, sw196, lw32, sw88, li16384.

Interesting: the scheduler put the ori/sw196 right after the addiu (no load-delay nop needed since lui/addiu fill it), and the sw88 after the next load (filling its delay slot? no, lw v0,32 then sw v1,88 — the store doesn't use v0, so it's a valid delay fill).

sched1's ordering is a list scheduler. The store sw88 got a low priority.

How about making the sw88's address `v1` be used by the following `li v1,16384`? In the target, after sw88 comes `lw v0,32` then `li v1,16384`. The register v1 is reused for 16384. In mine, v1 is used for the address and then li v1,16384 later.

Hmm, what if the address variable `a` is declared as `u16`/`s16` to force a HImode? No, the address is 32-bit.

What if the address constant is spelled as `(s32)&D_801907C4` vs `(s32)(&D_801907C4)` — same.

Let me think about sched1's priority formula: `priority = insn's DEPTH (length of the longest path to the end)`. Stores have a small depth; the load lw v0,32 has a dependent store (sh) so it has a higher depth. The ori/sw196 chain: ori → sw; sw is a sink. The sw88 is a sink too. So the ori has depth 1 + sw's? Hmm.

sched1 uses `max_insn_priority` or similar. Let me look at how it computes priority: in sched.c, `priority (insn)` = 1 + max priority of successors (through dependences). So a store's priority is low (1 + ...). The ori depends on the load; the load depends on nothing.

The scheduler picks the ready insn with the highest priority. At the point after addiu, ready insns: ori (depends on the load, ready), sw88 (depends on addiu, ready). Priorities: ori = 1 + priority(sw196) = 1+1 = 2? sw88 = 1. So ori first. That matches.

In the target (with the barrier), the block is the same but the schedule differs: sw88 before ori. Why? The target's ori is at 32 and sw88 at 31. With the barrier, the insn ordering/dependences might differ? The barrier is a memory clobber: it makes ALL memory references depend on it. But it's before the block's start... hmm, the barrier is inside the same basic block, before the load. It would make the load and the stores depend on the asm insn (a memory dependence). That doesn't change relative priorities among the load/store/address.

Hmm, but the asm's presence shifts the *birth indices* in the block, which affects local-alloc (not sched1).

Wait, maybe the difference is the SCHEDULING: with the barrier as an insn with a memory clobber, sched1 treats it as a "memory" insn and the stores after it have a dependence on it. But their relative order among themselves is unchanged.

Hmm, unless sched1's `priority` is computed per insn including the dependence on the asm... The asm has priority high? The asm depends on nothing and everything after depends on it → the asm's priority = 1 + max(successors) = huge. So the asm is scheduled first. Then the rest.

That still doesn't change the ori vs sw88 order.

Let me actually compare the target's schedule with what sched1 would produce. Maybe the target's order (sw88 before ori) arises because in the target the ori is *after* the sw88 in the RTL? I.e., maybe the original C had the store before the RMW and the load early... The RTL source order is C order: t=load; unk58=store; unkC4=ori/store. The target's schedule: load, addr, sw88, ori, sw196 = source order. So sched1 did NOT reorder in the target. Why? Maybe because sched1's scheduling window is limited: it processes insns in order and only schedules within a window of ready insns; if there's no reason to reorder, it keeps order.

The reorder in mine put ori before sw88. Hmm, that's a "better" schedule (fills the load delay). But in the target it didn't happen.

Ahh, maybe the barrier *ends the scheduling region*: sched1 splits blocks into "scheduling regions" at notes or at insns that can't be scheduled (asm volatile with memory clobber?). Let me check sched.c for "region" and asm handling.
