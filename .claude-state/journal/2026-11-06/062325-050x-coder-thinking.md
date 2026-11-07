---
ts: 2026-11-06T13:23:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kPGcrtcmCCQe4tQp43El
---
Dropping pins is much worse. So keep the pins.

Score 2 with a single addiu misplaced. We need to force the addiu a1 earlier. 

Think about sched1: it schedules each basic block. The addiu is sunk to the end because of low priority. In the target it's early. The barrier (memory clobber) made it a scheduling barrier — sched1 won't move insns across an asm? Actually sched1 treats asm as a barrier? The MIPS sched1 (sched.c) doesn't move insns across asm with memory clobber? Hmm.

Real-C alternatives to a memory clobber: a *store* to memory that the scheduler can't move across? Any store is a memory op; sched1 orders memory ops? On MIPS, sched1 might not reorder memory ops across each other (no alias info). So a dead store between `nn = ...` and the s0 chain could act as a barrier AND be deleted later... but "flow-dead-store" says flow deletes stores the target keeps. If our dead store is deleted by flow (which runs before sched1? pass order: flow analysis before sched1?), it won't act as a barrier at sched1.

Pass order: cse, loop, cse2, jump, flow? Let me check toplev around 2940-3040. sched1 runs after flow? The order in toplev: ... flow_analysis, combine, sched (schedule_insns), local_alloc, global_alloc, reload, sched2, jump(cross-jump), dbr. So sched1 is before local_alloc, and flow is before sched1. A dead store would be deleted by flow before sched1 → no barrier.

What real-C construct is a scheduling barrier at sched1 but emits no code?
- A `volatile` load/store: emits code (lw/sw).
- A function call: emits code.
- do{}while(0): C0535 says it splits cse1's EBB. Does it affect sched1? sched1 is per basic block; a do-while creates notes, and the basic block boundaries are determined by... LOOP_BEG notes are not basic block boundaries. So do-while does NOT split basic blocks for sched1! That's why v01 didn't help (it only splits cse1's EBB, which is a different thing).

Hmm. What about a `switch`? No.

So what splits a basic block? A conditional jump. Can we add a conditional jump that emits no code? A conditional whose branch is optimized away... e.g. `if (0)` is folded at tree level.

What about an `&&`/`||` fold? Hmm.

Wait — maybe there's another way: make the addiu a1 have a dependency that forces it early, e.g., compute the s0 chain value using `buf`? No.

Or make the call argument setup happen early by moving the call earlier? The call must come after d[2] = s0 (target order: jal func_80015978 then sh s0,28(sp)! Look at the target: 
```
3800: addu s0,s0,v0
3804: jal func_80015978
3808: sh s0,28(sp)      ← the store d[2]=s0 is in the DELAY SLOT of the call!
```
Interesting: in the target, `d[2] = s0` is placed AFTER the jal (in the delay slot). In mine:
```
37fc: addu s0,s0,v0
3800: addiu a1,sp,16
3804: jal
3808: sh s0,28(sp)
```
Mine also has sh in the delay slot. OK.

So the only difference is the addiu a1 position. sched1 placed it at 3800 (just before the jal) in mine. In the target it's at 37ec.

Hmm, what if we change where `nn` is assigned in the source? Target has addiu a1 at 37ec (early). If we move `nn = (s32)buf;` to before `aa = (s32)(q+1);`? The order would be addiu a1 then addiu a0 — target has a0 then a1. No.

What if the source computes `nn` earlier, e.g., before the rand calls? Then it'd be even earlier.

The real question: why does sched1 sink it? Its priority. In sched.c, insn priority is computed from the dependency graph; insns with no successors get low priority? The MIPS sched1 (from the scheduler) computes priority = length of the longest path to the end + ... Actually sched.c: `priority = insn_priority()` = sum over dependencies? An insn that nothing depends on and that depends on nothing gets priority 1 (lowest) and is scheduled last.

The asm memory clobber created a dependency chain: memory ops can't cross it, so the addiu (which is not a memory op...) hmm, addiu isn't memory. Why would the asm affect the addiu? Because sched1 treats asm insns as scheduling barriers (it doesn't move insns across them). In sched.c, `insn = ...; if (GET_CODE(insn) == INSN && GET_CODE(PATTERN(insn)) == ASM_OPERANDS) ...` there's `asm_noperands` handling: the scheduler treats an asm as a barrier if it has a memory clobber? Let me check sched.c for ASM handling.

Alternatively, maybe sched1 is not the pass that sank it; maybe it's the *reorg/dbr* or sched2. The barrier is gone, and the addiu moved from 37ec to 3800 (5 insns later). Both sched1 and sched2 could do this.

Let me test the hypothesis directly: use a real C construct that creates an ordering dependency between nn's assignment and the s0 chain. For instance, make the s0 chain depend on a value computed from nn — but that adds code.

OR: make `nn`'s assignment depend on the s0 chain? Then the addiu would be born after the chain → later. No.

Hmm, what about swapping the two: assign nn *after* the s0 chain (v09 = score 2)? That means even when written after, it lands at the same place (score 2). And when written before (nobar), also score 2. So sched1 ignores source order here and sinks it regardless.

What if we make nn's value come from a computation that sched1 can't sink: e.g. `nn = (s32)buf + (t & 0)`? fold removes.

`nn = (s32)(buf + 0)`? fold.

Hmm. What about declaring `nn` as `s32 nn = (s32)buf;` at declaration (init at decl)? Then the assignment is at the top of the block, not after the rand calls. Target has it after the rand calls. Hmm, but maybe the allocator/scheduler still places it at 37ec? Unlikely.

Wait, actually let me reconsider: maybe the barrier's effect is on *cse*: `__asm__ __volatile__("" ::: "memory")` prevents cse from... hmm no, the difference is purely ordering.

Let me look at the target's scheduling: the addiu a1,sp,16 at 37ec is right after addiu a0,s3,4 at 37e8. Both are "argument setup" for the call. They're adjacent in the target. In mine, addiu a0 is at 37e8 but a1 is at 3800.

What if the barrier's role was to stop sched1 from moving the s0 chain ABOVE the addiu? No, it's the addiu that moved down.

Alternatively, maybe in the target, the s0 chain is *dependent* on the addiu a1 through a register? No: s0 chain uses s0, v0, t.

Hmm, sched1 priority: `addiu a1,sp,16` is the birth of nn (hard reg $5). Since nn is pinned, the destination is a HARD reg. In sched.c's birthing_insn_p: `if (GET_CODE(dest) == REG && REGNO(dest) >= FIRST_PSEUDO_REGISTER && reg_n_sets[...]==1)`. For a hard reg, no boost. So it gets a low priority and sinks.

But wait: in the target, with the barrier present, sched1 couldn't sink it past the barrier. So the barrier is what pins it. Any construct that sched1 treats as a barrier... Let me check sched.c for how it handles asm and what it treats as a barrier.

Actually, more promising: C0535's do-while *does* split an EBB for cse1, but for sched1 the EBB is a *scheduling region*? Let me check sched.c: it builds regions via `find_basic_blocks` and the scheduler uses "extended basic blocks" (EBBs) for some things. In sched.c, `schedule_insns` builds control flow and computes `regions`? Hmm, in 2.7.2 sched.c there's "struct haifa_insn_data"; the scheduler works on basic blocks. There's also the concept of `sched_region`?

Let me grep sched.c for "asm" and "barrier".
