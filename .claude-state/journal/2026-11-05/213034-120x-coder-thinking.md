---
ts: 2026-11-06T04:30:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_91hZoPmFZUhWXRfVjYXB
---
The sched dump has hundreds of functions (the TU is huge). The section at 35406 "Function func_801810A4" — but the block numbers 4..290 suggest it's the right function? Our function's insns in the combine dump were 204-265, but those are insn UIDs which are per-function and reset; the sched dump uses the same UIDs. Block 0 "from 4 to 290" — hmm, our function's first insn might be 4 and last 290? In the combine dump for func_801810A4, the insns I saw were 204-265. The prologue insns would be 4-30. So block 0 "from 4 to 290" could be our function's block 0 (the prologue+switch). And the insn numbers 204-265 fit. But block 13 "from 243 to 256", block 14 "from 239 to 235", block 15 "from 262 to 265" — the `<0x11` arm might be block 13 (243-256)? Hmm, the insn 232 (p load) isn't in any block list — because block 13 starts at 243? 

Wait, the insn UIDs in the sched dump are the SAME as the combine dump? The combine dump showed insn 211, 214, 216, 217, 232, 235, 262, 265. The sched dump block 13 is "from 243 to 256" — those are different UIDs. So the sched dump's insn numbering is different from the combine dump! Because sched1 runs AFTER the jump_optimize that follows cse, which may renumber? No, insn UIDs are stable. Hmm, but sched1 runs after `jump_optimize` (line 2870/2923) which can delete/duplicate insns and assign new UIDs. The combine dump is after combine (before sched1), so UIDs there differ from the sched dump if jump_optimize ran between. Actually the order is: jump, cse, delete_dead, jump, loop, cse2, jump, ... combine, sched1. So combine is right before sched1, with no jump between. So UIDs should match. Unless the .combine dump I read (23845) was from a DIFFERENT function than the sched section.

I'm spending too much time on the dump. Let me refocus: the empirical fact is that in the RTL the p load is after the chain (insn 232 after 217), and sched1 moved it before. The sched dump's block 13 (243-256) etc. suggests our function's sched block numbering is offset.

Let me search the sched section 35406-36346 for the priorities of insns 232/235 and see the block. Actually, let me grep the section for "232" — none found. So the UIDs in the sched section don't include 232. That means the sched section's UIDs differ. The block 13 "from 243 to 256" might be the `<0x11` arm with different UIDs.

This is a rabbit hole. Let me instead focus on a practical fix.

Observation from the RTL: the p load (insn 232) is after the chain (217) and before the addiu (235). sched1 moved it before the chain. Its priority was 1 (no dependents in-block; the store 265 is in the next block). The chain's priority: 214→216→217→235. So the chain's insns have priority ≥ 2. With priorities 2+ vs 1, the scheduler should schedule the chain first. But it moved the p load first?! Unless the ready-list logic favors the load due to "potential hazard" (the scheduler tries to avoid stalls by launching loads early). Look at the trace: "launching X before Y with no stalls" — the scheduler uses hazard avoidance. A load has a delay; launching it early avoids a stall. So the p load (priority 1) was launched early to avoid a load-delay stall.

In the TARGET, the p load is NOT early. So in the target's RTL/schedule, the load's launch didn't happen early — maybe because the target's block had different insns or the load's latency was already covered.

Hmm, the scheduler's `launching 46 before 51 with no stalls` logic: it can reorder to avoid hazards. This is `schedule_insn`'s "if insn has a delay and the next insn would stall" logic.

Given the complexity, maybe the practical fix is to change the RTL order so the p load is in the SAME block as its use (the store), i.e., AFTER the label. If the p load is after the label 262, then it's in the next block and won't be hoisted into the arm's block. But the C source has the p load in the arm (before the merge store). Could we move the p load into the merge block? The merge block is shared by all arms; each arm sets p. If instead the merge block loads p itself (raw expression), then:
- For the n<8, n<0x16 arms: they set p and store to 0x1A, then the merge store needs p. If the merge loads p raw, those arms would load p twice (target has once). Hmm.

But wait — for the `<0x11` arm, the target's p load IS in the arm block (4944, before the label 494c). So the target's p load is also in the arm block. It just wasn't hoisted.

OK, let me try a different tack: maybe the target's p load wasn't hoisted because the *store* at the merge block was in the same block (not a separate label block) in the original RTL, giving the p load a priority 2 chain (lw→sh) that tied with the chain, and the scheduler kept the original order. In the target, the merge block at 494c is a branch target (from other arms), so it IS a separate block. Hmm.

Actually, maybe the cross-jump (jump2) created the label 494c AFTER sched1/sched2! jump2 runs after sched2 (post-reload). So at sched1 time, the merge block might NOT be a separate basic block — the arms might fall through into the merge without a label, and the jumps from other arms are added later by cross-jump. In that case, the p load's dependent (the sh) is in the SAME block at sched1 time, giving it priority 2 (lw→sh) vs the chain's priority 4. Still lower.

Hmm, but if the sh is in the same block, the scheduler would schedule the chain (priority 4) before the lw (priority 2). That matches the target! And in mine, if the sh is NOT in the same block (a label exists at sched1 time), the lw has priority 1 and the hazard logic launches it early.

So the difference could be whether the merge store is in the same basic block as the `<0x11` arm at sched1 time. If the compiler created a label there (because other arms jump to it), the block splits. In the target's original source, maybe the merge block was reached by fall-through from the `<0x11` arm and the other arms used `goto` to a label AFTER the store? Hmm.

Our C uses `goto call;` in the else arm (line 69) and the merge store is shared. The compiler creates a label at the merge for the goto. The other arms (n<8, n<0x16, ==0) fall through to the merge. So the merge has a label (from the goto) → block boundary.

If the original source had the merge store duplicated or structured differently... The target's assembly shows the merge block at 494c reached by jumps from 48b8, 48d0, 48f8, 491c. Those jumps are from the n<8, n<0x16, ==0 arms (which store to 0x1A then jump). So in the original, those arms had explicit gotos or the compiler's cross-jump merged their fall-through into a jump. Actually the `j 494c` at the end of those arms with the store in the delay slot is the natural fall-through: the arm ends, falls through to the merge... but the merge is after the `<0x11` and else arms. So the arms must JUMP over the later arms to the merge. That's a goto in C (or the if-else chain structure). Our C has the if-else chain with the merge after; the compiler generates jumps for the earlier arms. So the merge has a label from those jumps. Same in the original.

So at sched1 time, the merge is a separate block. Then the p load's priority is 1. And the hazard logic launches it early in mine but not in the target. The hazard logic depends on the load's *latency* and the following insns. Hmm.

I think I should stop analyzing and try more empirical variants, then record a WALL if no crack. Time is well past 30 min. But I need ≥30 tries for a WALL.

Actually, wait. Let me reconsider the whole approach: maybe the target can be reached by NOT using the raw-pointer trick in the `<0x11` arm, i.e., by making the 0x1A store through `p` where p was loaded BEFORE the store (so p is live across the store), then the merge store reuses p? No, the store kills cse but p is a register holding the model pointer; the store to `((Unk*)p)->unk1A` writes through p, so p itself (the pointer value) is still valid in the register! cse doesn't invalidate the *register* p; it invalidates the memory load `*(a0+0x20)`. If the C is:
```
p = ((Unk*)a0)->unk20;      // load model into p
((Unk*)p)->unk1A = 0xC00;   // store through p
v = multiply;
v = v + 0x600;
((Unk*)p)->unk18 = v;       // merge store using the SAME p (no reload!)
```
Then there's only ONE p load, and no reload. But the target has TWO model loads (4924 and 4944) in this arm! Because the target's source used a raw expression for the 0x1A store (not p), so cse killed the load and the p assignment reloaded. So the target's original source indeed used the raw expression for the 0x1A store. Our source does that too.

Hmm OK. Let me try yet another angle: the p reload is a `mem/s:SI` (struct) load. The first model load (for the 0x1A store) is `mem/s:SI` too (insn 232 is struct). Wait, insn 232 is the p load; the raw store's load is insn 200-ish. Both struct.

What if the p reload is made a NON-struct load (`mem:SI` vs `mem/s:SI`)? That changes cse/invalidation? The `mem/s` (in_struct) affects `invalidate_memory`: a nonscalar store removes entries with in_struct=1. Hmm! The store `sh v0,26(v1)` — its address is `(plus (reg v1) 26)`, a PLUS → nonscalar=1. It removes in_struct entries. The model load entry (in_struct) is removed. If the model load were NON-struct (in_struct=0), the store might NOT remove it (if the store's address doesn't vary). Wait, the store's address is PLUS → `cse_rtx_addr_varies_p(written)`? The written MEM address is `(plus (reg v1) 26)` → rtx_addr_varies_p true → nonscalar=1, and `(MEM_IN_STRUCT_P || PLUS) && mode != QImode` → doesn't set all. Then invalidate_memory removes entries where `nonscalar && p->in_struct` OR `cse_rtx_addr_varies_p(p->exp)`. The model load's address is `(plus (reg 72) 32)` → cse_rtx_addr_varies_p returns true (address varies) → removed regardless of in_struct. So it's removed anyway.

OK.

Let me try a completely different structure for the `<0x11` arm: use a local `Unkstruct_800B5CB8 *q;` variable for the model in this arm (block scope), separate from p, and store via q, then set p for the merge. That changes the pseudo allocation (q separate from p) and maybe the schedule. Target uses v1 for both p and q (same reg). If q is a separate pseudo, it might still get v1 (disjoint). Let me try.

Actually, simpler idea: the target's p load is at 4944 AFTER the addiu? No: 4944 lw v1; 4948 addiu; 494c sh. So p load BEFORE the addiu. In x1 the RTL is p (232) then addiu (235). sched moved p before the chain. If p's priority were higher than the chain's, it'd still be before. Hmm.

Let me try making the addiu depend on p: `v = v + 0x600;` — no.

What if the store value is computed as `v + 0x600` where v is the chain result, and the store's address is p — the store depends on both. If we reorder so the addiu comes BEFORE the p load in C (x1 did: chain, add, p), the RTL order is chain, add, p. Wait, x1's RTL: 211,214,216,217,232,235 — the p load (232) is BEFORE the addiu (235)! But x1's C order was chain, add, p. So the RTL order doesn't match the C order! Why?

Because the C `v = v + 0x600; p = ...;` — expand emits addiu then p load. But the RTL shows p (232) before addiu (235). Insn 232's UID is lower than 235, so it was created first, but placed after 217. Wait, 232 < 235, so p was created before the addiu. That means the C order at expand was chain, p, add — i.e., x1's source was NOT what I thought. Let me check x1's source: I did the swap awk: NR==60 (p) skipped, NR==61 (add) printed then p. So x1 = chain, add, p. But the dump says p created before add (232 < 235). Hmm, maybe the scratch TU I dumped was from a previous --keep run (p3) that didn't correspond to x1! The --keep scratch dir is reused per call; when I ran cc1_dumps_tu.sh, the scratch TU was from the LAST --keep call, which was... I ran --keep for w9 (p3), then x1? Let me check: after x1, I ran `dt.sh x1` (no --keep). The last --keep was w9. So the dump was of w9, not x1! w9 = chain, add, p? No: w9 was p after add? Let me recall: w9 was built as `NR==59{print; next} NR==60{next} NR==61{print; print p; next}` → line 59 = multiply (printed), line 60 = p (skipped), line 61 = add (printed) then p. So w9 = chain, add, p. Hmm, then the RTL should be chain, add, p. But the dump shows p (232) before add (235).

Wait, maybe I mislabeled: in the combine dump, insn 232 is `(set (reg/v:SI 76) (mem/s:SI (plus (reg/v:SI 72) 32)))` — the p load. And insn 235 is `(set (reg/v:SI 75) (plus (reg/v:SI 75) 1536))` — the addiu. The list order: 211,214,216,217,232,235. So p before add. But the C order was chain, add, p. Unless the scratch TU was from an earlier call (w6 or x1?). Let me re-dump x1 explicitly to be sure. Actually, this doesn't matter much.

Let me try to control the RTL order: the key is the p load before the chain in the RTL? No — in the dump, the p load is AFTER the chain (217) and before add (235). That's the ideal RTL order (chain, p, add)! And sched1 moved it before the chain. So the C order that gives this RTL is chain, p, add (w4). sched1 hoists it.

So the issue is purely sched1's hazard-avoidance. The scheduler launched the load early. Why doesn't it in the target? The target's load is at 4944, after the chain. 

Look at the sched trace: "launching 46 before 51 with no stalls" etc. The scheduler reorders to avoid stalls. The p load's launch: it has no in-block dependent (the store is in the next block), so its priority is 1. The scheduler's `schedule_insn` has logic: if the next insn is not ready and this insn is a load, it can "launch" it early. This is the "launch" mechanism for delaying.

Hmm, the target avoided this. The difference could be the number of insns or the block boundaries. If the merge store were in the SAME block, the p load's priority would be 2 and the scheduler would schedule it after the chain (priority 4) naturally. So: make the merge store part of the same basic block as the `<0x11` arm at sched1 time. How? If the merge block has no label at sched1 time — i.e., if no other arm jumps to it. But the earlier arms must jump over the later arms to reach the merge.

Unless the if-else chain is structured so that the `<0x11` arm is the LAST arm (fall-through to the merge), and the earlier arms jump. It already is: the `<0x11` is the second-to-last, then the `else` arm (which gotos call). The `else` arm is between the `<0x11` arm and the merge! So the `<0x11` arm falls through to... the `else` arm's code? No, it's an else-if chain: after the `<0x11` arm's body, control goes to the merge store (line 71), which is after the whole if-else chain. The `else` arm (line 63-70) ends with `goto call;`. So the merge store (line 71) is after the else arm's code. The `<0x11` arm must JUMP over the else arm to reach the merge store! Indeed, the target has `j 494c` at 4948 (delay addiu) from the `<0x11` arm, jumping over the else arm's code at 490c-4920? Wait, the target's `<0x11` arm is at 4924-4948, and the else arm at 490c-4920 is BEFORE it. Hmm, the order in the target: ==0 arm (48d8-48fc), <0x11 arm (4900-4948), else arm (490c-4920)? No...

Let me re-read the target order:
- 48c0: n<0x16 arm
- 48d8: ==0 arm (bnez at 48e0)
- 4900: slti (the <0x11 condition), bnez 4924
- 490c: else arm (the final else: 490c lw v0; li v1,3072; sh; 4918 lw; j 4950; sh)
- 4924: <0x11 arm (lw v1; nop; sh; lw v1,28; sll...; lw v1,32; addiu; sh 24)
- 494c: merge? No — 4948 addiu; 494c sh v0,24(v1) is the <0x11 arm's final store (the merge store).
- 4950: call.

So the target's block order: the `<0x11` arm is placed AFTER the else arm (the compiler reordered the arms). The `<0x11` arm falls through to 494c (the merge store), which is also the target of the jumps from the earlier arms (48b8, 48d0, 48f8, 491c). So 494c IS a branch target → block boundary. And the `<0x11` arm's p load at 4944 is before 494c.

OK so the merge store is a separate block in the target too. And yet the p load wasn't hoisted. So the hazard logic didn't fire in the target. Why? Maybe because the target's block has a different insn count/layout: the `<0x11` arm at 4924: lw v1,32(s1); nop; sh v0,26(v1); lw v1,28(s2); nop; sll; addu; sll; lw v1,32(s1); addiu. The block starts at 4924. The p load (4944) is the 9th insn. In mine, the block starts at 4924 too and the p load is hoisted to 4934.

Hmm, the difference: in the target, the p reload is at the END of the block (after the chain). In mine, sched1 moved it up. The hazard logic: "launching insn before X with no stalls". Let me look at the sched trace for this block in the target — but I don't have the target's RTL/dump. 

I think this is genuinely a sched1 hazard-scheduling difference that may be hard to control with plain C. Given the time, I'll record a WALL for item 4 with best 14, after reaching ≥30 tries.

Let me quickly generate a batch of ~12 more variants to reach 30 tries, then record WALL. Variants to try:
1. `v = *(s32*)(obj+0x1C); v = v*3*32;` (r3 was 22)
2. Different temp for the multiply.
3. `p` declared as pointer type `Unkstruct_800B5CB8 *p;`
4. `p` declared inside each arm (block scope) — but the merge uses p... skip.
5. Use `v = *(s32*)(obj+0x1C) * 96;` (r2=14)
6. Move the merge store into each arm? big change.
7. Add a dead reset of p after the store? 
8. Make the `<0x11` arm's multiply use `n`.
9. Use `q` local pointer in the `<0x11` arm.
10. Wrap the whole `<0x11` arm in do-while.
11. Wrap the 0x1A store in do-while.
12. Use `u16`/`s16` casts for the multiply.

Let me just run a batch and count. I'll build variants from w4.

Actually, hold on. Let me try ONE promising idea first: make the merge store's `p` load happen in the merge block by making the `<0x11` arm jump to a separate label with its own store? No.

Another promising idea: the hazard logic launches the load early because the load has a delay and the next insns are dependent? Actually the "launching" logic in sched.c is for `T` (issue time): it can move an insn earlier if it reduces stalls. Let me read the relevant part: search for "launching".
