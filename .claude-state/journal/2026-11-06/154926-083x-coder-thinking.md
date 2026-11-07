---
ts: 2026-11-06T22:49:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JzNpwpWsfb3c0aKZ20nT
---
The sched priorities are IDENTICAL between w0 and w6 for the insns (16: pri 1, 20: pri 2, etc.). The only difference is the ref_count of insn 72 (the bne): w0 2147483528, w6 2147483529 — one more ref (because s1ang is used in the bne? no, the bne uses the masked value; in w6 s1ang is the masked value).

The scheduling decisions differ due to the tie-breaking (hazards). In w0, insn 20 gets priority at T-8 ("insn 20 has a greater potential hazard") and insn 16 is launched before 45. In w6, at T-8, 45 is chosen, then 43, then 20 at T-14.

So the difference is a hazard tie-break. The insn 72's ref_count difference (one extra ref in w6) might change the hazard computation for the whole block. Hmm, that's the bne's ref_count.

Hmm, in w6, the bne (insn 72) uses s1ang (masked) and u5. In w0, it uses u6 and u5. The ref_count differs because... the bne's operands.

Actually, the key difference in the schedule: in w0, insn 20 (lh s1ang) is scheduled earlier (before the lw), so the arg0 pseudo dies at the lw (later). In w6, insn 20 is scheduled later (after the lw), so arg0 is still live at the lw.

Hmm, the scheduler's "potential hazard" tie-break uses `insn_ref_count`? This is hard to control via C.

OK. Given the difficulty, let me consider: the target's schedule is the w0 schedule (with the pin). In w0, the schedule is right; only the registers are wrong (d/s1ang swap). In w6, the registers are right but the schedule is wrong (and the arg0 copy is lost).

Is there a way to get the w0 schedule AND the d/s1ang fix? The d/s1ang fix requires s1ang global (mask-in-place), which changes the schedule. Hmm.

Wait — maybe not! Let me reconsider: the d/s1ang swap in w0 is because local-alloc gives s1ang (r75) $s0. If s1ang is local, it takes $s0. To give d $s0, s1ang must not take it. The mask-in-place globalises s1ang (changing the schedule).

What if instead we make s1ang's local pseudo NOT cross the call? Then local-alloc wouldn't need a callee-saved reg for it. But the load is before the call and used after.

Hmm, what if we make the load result die before the call by copying it to a global pseudo before the call? E.g.:
```
s1ang = *(s16 *)(...);
```
Hmm, the value must survive the call.

What if we load s1ang TWICE: once before the call (dead) and once after? No, extra instructions.

Hmm.

What if the s1ang load is HImode (s16 s1ang)? Then the pseudo is HImode; local-alloc might treat it differently. Let me try that — it's cheap. w10: `s16 s1ang;` with u6 = s1ang & 0xFFF.

Actually, the target's `lh $17,18($2)` loads a full word and `andi` uses it. With s16, gcc might do `lh` then the andi with an implicit extension. Let me test.

Also w11: `u16 s1ang`? No, the target sign-extends (lh).

Let me also try the sibling's exact structure (their win.c) adapted: they had `a = arg2; div = arg3;` and used `a = a & 0xFFF` inside a do-while with the cast. That's w8 (49). Hmm.

Wait, in the sibling's win.c, the div block is ALSO in a do-while (a separate one). w9 had that (38). Hmm.

The sibling's win.c has the div in a do-while AND the cast+mask in a do-while. That's exactly w9 (38). Their residual was the cast temp only. But ours has the u5/iVar4 shift.

The difference between our function and the sibling: our function has an extra `arg0+0x20` pointer load (the s1ang load is `*(s16*)(*(s32*)(arg0+0x20)+0x12)`), while the sibling's s1ang load is `*(s16*)(arg0 + 0x12)`? Let me check the sibling's source: `ang = ratan2(*(s16 *)(arg0 + 0xA) - ...)` and `a = arg2` — so their "a" is a parameter, not a memory load! Their s1ang equivalent (a) is arg2, not loaded from memory. So the structures differ significantly.

OK. Let me now think about the arg0 copy issue separately. The arg0 copy exists in w0 but not in w6. The difference is the schedule (sched1 tie-break). Could I force the w0 schedule in w6 by reordering the source statements? The scheduler's order is determined by the data dependencies and priorities. The priorities are identical; only the tie-breaks differ (due to ref_count/hazards).

Hmm, what if I change the source order so that the lh uses are before the lw naturally? E.g., compute `*(s16*)(arg0+0xE)` and `*(s16*)(arg0+6)` first, then the pointer load. But the target order has the lw before `subu $4,$3,$4`... The source order: s1ang = load(ptr); u5 = ratan2(*(s16*)(arg0+0xE)-..., ...). The scheduler hoists.

Actually, in the target (pin), the s1ang load (insn 20) is scheduled before the lw (insn 16)? The target asm: `lh $3,14($2); lh $4,D_80126CB8; lh $5,6($2); lw $2,32($2); subu...; lh $3,D_80126CB4; lh $17,18($2); jal`. So the lw is before the s1ang lh. Hmm! In the target, the lw (insn 16) is BEFORE the s1ang lh (insn 20). And the arg0 pseudo dies at the lw. But the `lh $3,14($2)` and `lh $5,6($2)` use arg0 before the lw.

So the target order: lh14, lh(D_80126CB8), lh6, lw, subu, lh(D_80126CB4), lh(s1ang), jal. The arg0 uses (lh14, lh6) are before the lw; then the lw overwrites $2.

In w0's asm: `lh $3,14($2); lh $4,D_80126CB8; lh $5,6($2); lw $2,32($2); subu $4,$3,$4; lh $3,D_80126CB4; lh $16,18($2); jal`. Same order as the target! Great.

In w6's asm: `lw $2,32($4); lh $6,14($4); lh $3,D_80126CB4; lh $5,6($4); lh $17,18($2); lh $2,D_80126CB8; subu...; jal`. The lw is FIRST. Different.

So in w6, sched1 ordered the lw first because of the tie-break difference. Hmm.

Since the sched priorities are the same, the difference is the "potential hazard" tie-break. The hazard computation depends on the insn's ref_count. Insn 72's ref_count differs (2147483528 vs 2147483529). Insn 72 is the bne (jump). Its ref_count affects... hmm, the scheduler's `insn_ref_count` is used for the hazard tie-break? Let me look at sched.c's `rank_for_schedule`.

Actually, the "potential hazard" is computed from the dependency links. The bne's ref_count difference (1 more) suggests one more dependency. Hmm.

This is a very deep scheduling tie-break. The W50x coder's notes said the keepalive was the scheduling anchor and the do-while replaced it. So the schedule is sensitive.

Given the complexity, let me consider: is a MATCH realistically achievable? The task says W50x left it PARTIAL:pin after 9 tries. My job is to try with "new moves". I've tried several. If I can't crack it, I record a WALL with ≥30 tries.

Let me continue with more variants, focusing on:
1. Getting the w0 schedule with the mask-in-place (maybe a different anchor).
2. Removing the a1 preference.

Let me try: mask-in-place but with the cast do-while SEPARATE from the mask (w6) and also add a do-while around the s1ang load to change the schedule (w5-like). Hmm, w5 (load do-while) didn't globalise.

Let me try the reverse: keep the u6 variable and make s1ang global by a do-while around the LOAD but with a body that forces a block. w5's do-while around the load made it 3 refs/13, still local. Hmm.

What about `do { s1ang = load; } while (s1ang);`? That adds a test/branch (extra instruction).

Hmm.

Let me try the `s16 s1ang` variant (w10) and a few width/order variants. Also try `u16`.

Actually, wait. Let me reconsider the problem from the perspective of what the ORIGINAL source likely was. The original compiler (with no pin) produced d=$s0 and s1ang=$s1. So there IS a real-C body. The decomp's body (pin+keepalive) is an approximation. The original probably had a slightly different structure that made d's priority high or s1ang's low.

Key: in the original, s1ang raw is a local pseudo crossing the call, and local-alloc gave it $s1 — meaning $s0 was NOT free. What occupied $s0? If d is global, local-alloc doesn't consider it. So $s0 must be occupied by another LOCAL pseudo at the time r75 is allocated. But then d would conflict with that local $s0...

UNLESS: local-alloc processes block 0's qtys in priority order and r75 is NOT the highest. If another local qty with higher priority took $s0 and its live range is BEFORE d's live range... d is live from insn 6. Hmm.

OR: the original had s1ang raw allocated $s1 because the local-alloc qty order put another qty in $s0 first, and that qty's live range didn't conflict with d because d's live range started later (at the cast, insn 57)? Wait — in the target, `move $16,$5` is at insn 6 (d = arg1 at entry). So d is live from insn 6.

Hmm, but maybe in the original, `d = arg1` was NOT a separate statement at entry; maybe d was defined by the cast only: `d = (s16)arg1;` at insn 57. Then d would be live from insn 57, and the local pseudo in $s0 before insn 57 wouldn't conflict. But the target has `move $16,$5` at entry! Unless that move is the cast's input...

Wait, let me re-read the target asm:
```
subu $sp,$sp,32
move $2,$4        # arg0 -> v0
sw $16,16($sp)
move $16,$5       # d = arg1
sw $31,24($sp)
sw $17,20($sp)
...
sll $16,$16,16    # cast
sra $16,$16,16
```
The `move $16,$5` at entry means d is live from entry. Hmm.

Unless the original source was `s32 d = arg1;` — same thing.

Hmm, so how did the original get $s1 for s1ang? Maybe in the original, local-alloc gave $s0 to a local pseudo in a DIFFERENT block (not block 0), and d's live range... no, d spans.

OR maybe the original's s1ang raw was NOT local! Maybe in the original, the s1ang load's result was global because the original source used it in a later block (like the mask-in-place). Then the original's allocation would be: d (10000) first → $s0, s1ang (2857) → $s1. And u6 (r77) prefers s1ang's reg → $s1.

That's exactly w6! But w6 has the schedule/arg0 issue. Maybe the original source had the mask-in-place-like structure AND a different statement order that gives the w0 schedule.

Hmm, w6's schedule difference comes from the bne's ref_count. Let me look at what the bne (insn 72) depends on in w6 vs w0. In w6, s1ang is reassigned and used in the bne; in w0, u6 is used. The ref_count difference (2147483528 vs 2147483529) is the `insn_ref_count` = the number of dependencies? 

Let me look at sched.c's rank_for_schedule to see if ref_count affects the order.
