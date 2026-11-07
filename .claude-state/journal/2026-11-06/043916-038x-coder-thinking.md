---
ts: 2026-11-06T11:39:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vgRTz6b2Remeiukxu52l
---
result_ready_cost for a MIPS load is likely 2 (load delay). So loads have cost 2, and insns depending on a load get priority boost. That explains hoisting.

In target with barriers, why doesn't the addu hoist above the stores? Because in target EBB2 the add's dependency is on `lw t1,16(sp)` which IS in the same EBB, so it would still boost. Hmm, but it appears the addu is scheduled right after the two loads... 

Actually target EBB2 order: lw t1(w_), lw a2(tag), addu s1, sh 16, sh 18, sh 24, lw t1(h_), and, addu s2, sh 26, sh 32, sh 34, lw ot, and pmask, and, or, sw...

Hmm interesting: the first two insns are loads (priority 1), then addu (priority 2). If the addu had priority 2 from the start... it can't be ready until the lw is scheduled (data dependency). So ready list initially: lw t1 and lw a2 (both priority 1). Pick lw t1 (source order tie-break). Now addu becomes ready with priority 2. But the scheduler picks... hmm, the ready list is resorted; the addu should be picked before lw a2 if priority 2 > 1. Unless the addu's priority is 1 because the load cost is 1 for stack loads? Or because `result_ready_cost` of lw is 1 in this config?

Hmm, but in mine, the adds moved before the byte stores. Let me reconsider: in mine, EBB is bigger. The ready list initially contains: after p += 8 (addiu), the byte stores, the moves, the loads. The lw t1,16(sp) — is it ready at block start? It reads the stack slot written in the prologue (sw a2,16(sp)), so it has an anti-dependence on that store? It's in the same block (the prologue stores are at the top of block 0 and schedule_block skips "insns at the beginning from scheduling" for b==0: the code at 3186 keeps parameter-copy insns from being scheduled: `INSN_REF_COUNT (head) = 1` keeps them from moving? Actually it advances HEAD past "SET of a hard reg" insns.

Hmm wait, the prologue's `sw a2,16(sp)` etc. — those are at the top of block 0. The head-advancing code skips insns at the beginning that are SETs of hard registers from... it advances head past them. So they're not scheduled.

OK so in mine, initial ready: stores + loads + moves. Priority of `addu s1,s1,t1` = priority(lw)+cost-1 = 1+2-1=2. But the lw must be scheduled first. Initial ready includes lw t1 (priority 1). It picked... in mine the order was: sh s1,8(v0) [vx store], lw t1,16 [w_], move a0,s1, addu s1, sh s2,10, sh s2,18, lw t1,24, li v1,8, addu s2, sb v1,3, lw a2,0 ...

So it picked the vx store first (source order? vx store is later in source than p[3]=8, so no).

Hmm, why is `sh s1,8` before `sb v1,3`? Both priority 1. Source order: p[3]=8 is earlier. Unless the vx store has some priority 2? `sh s1,8` depends on move s1,a0? no, s1 is x, defined in prologue.

Wait, maybe scheduling considers the last_scheduled_insn class: class 1 = data dependent on last scheduled insn. After scheduling lw t1 (load), addu is class 1 (data dep) but the stores are class 3. Hmm but that's only when priorities tie.

I'm going down a rabbit hole. Let me instead try empirical moves. Ideas:

(1) v2: v0 with `vx`/`vy` declared and assigned but the first block's stores reordered to match the target's needs? Since sched1's tie-break is LUID (source order) and priority, maybe making the adds have LOWER priority is the key: the adds get priority 2 because their operand comes from a stack load (cost 2). What if w_ and h_ are copied to local variables early (before the block)? `s32 w = w_, h = h_;` at the top — then the loads from stack happen early (in the prologue block) and the adds depend on pseudos (moves) with cost 1 → priority 1, so no hoisting! That's a real C move: copy params to locals.

But wait — the target has the loads `lw t1,16(sp)` and `lw t1,24(sp)` inside, so the parameters are NOT copied to callee-saved regs early. If I introduce locals w,h, the compiler may keep them in regs or reload from stack. Actually, w_/h_ are used once each; introducing a local `w = w_` at the top would create a copy... the target's shape shows the load happens late (at use), which is exactly what not having a local does.

Hmm, but maybe I can make the loads have cost 1 by... no.

(2) Alternatively, reorder source so the loads come AFTER in a way that... they already do.

Let's reconsider the actual mismatch. It's a COUNT class: 30. Which insns differ? The reordering means same insns, different order. Score counts masked mismatches.

Maybe there's a cheaper approach: the target's order equals source order (with barrier). If we can make sched1 not reorder, we win. sched1 reorders because of the load-delay cost boost. The barrier's role: split the block so the loads aren't in the same block as the stores.

So we need an EBB split at the barrier points, without changing regalloc. do-while is the tool but it changes regalloc via loop notes. 

Hmm, does the do-while really add loop notes? In gcc 2.7.2, LOOP notes are created by loop.c (NOTE_INSN_LOOP_BEG) and loop.c's `record_loop_exits`... Actually LOOP_BEG notes are created by the cfg/loop analysis in loop.c. The do-while(0) generates `do {...} while (0)` → a LABEL at the end, a conditional branch to the label. jump_optimize would see the branch with constant 0 condition and delete it, then the label becomes unused and deleted. This happens in jump.c (before loop.c? jump_optimize runs after cse1? Pass order: cse1, jump_optimize (jump), loop, cse2...). Hmm.

But C0535 says the do-while splits cse1's EBB — cse1 runs before jump_optimize. And sched1 runs after... let me check the pass order. In 2.7.2 toplev.c: 
- cse (cse1)
- jump_optimize
- loop_optimize? Actually order: `if (optimize) { ... cse ... jump_optimize ... loop_optimize ... cse (cse2) ... }` and sched runs in `rest_of_compilation` at "sched" after combine and before local_alloc? Let me check toplev.c.

If jump_optimize removes the do-while branch before sched1, then the EBB split wouldn't survive for sched1... but C0535 says it affects sched1 ("splits cse1's EBB so sched1 keeps their birth order"). Hmm, maybe the label/branch survives into sched1? No...

Wait, maybe the do-while block affects *cse1* which then changes what insns exist (e.g. merging copies), and sched1's birth order (LUID) of the surviving insns is what changed. In C0535's case the two copies were in a specific order.

For us, the do-while did change the schedule (score 47 vs 30) but also regalloc. Hmm.

Let me check the pass order quickly.
