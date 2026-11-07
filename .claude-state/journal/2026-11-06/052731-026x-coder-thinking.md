---
ts: 2026-11-06T12:27:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LbLVL8NAYh2qIAJwi6QU
---
Key: `if (condition == const_true_rtx || (! insn_sets_resource_p (trial, &opposite_needed, 1) && ! may_trap_p (pat)))` — so an insn that sets a resource needed at the opposite thread can't be moved. opposite_needed = live regs at the branch target. At the target (2238: move s1,v0), v0 is live (used by move s1,v0), and also s1 is live? s1 is used at 223c (sll v0,v0,0x10) — wait at the target after redirect... Let's see: target_label 2238 (0x1e4). mark_target_live_regs at that point: what's live-in at 2238? s1 (used at 223c? no, 2238 is move s1,v0 then 223c sll v0,v0,0x10 — v0 is live into 223c; s1 is written at 2238 so not live-in). Also s2, s3 live at 2238 (used later). And ra? Hmm.

So if the fall-through head sets a register that's live at the target label, it's rejected. The head is `move a0,s0` — a0 isn't live at 2238. If the head were an insn setting v0 or s2 or s3, it would be rejected!

Wait — but the loop counter increment `addiu v0,s1,1` sets v0 which IS live at target → that's why it can't be "moved" from the fall-through... but it's in the taken thread. Hmm, for the taken thread fill (thread_if_true=1, likely=1) the same check applies with opposite_needed = live at the fall-through (the call arm). v0 is live at the call arm? After the call, `move s0,v0` uses the call result, so v0 is set by the call; live-in at 2224 includes a0? a0 is set at 2224... The opposite thread here is the fall-through (2224). live at 2224: s0, s3, s1, s2, sp, ra... v0 is not live-in at 2224 (it's the branch condition value, dead after). So `addiu v0,s1,1` doesn't set a live-in resource at the fall-through → allowed → stolen.

So to make the fall-through head rejected we need its first insn to set something live at the branch target. What's live at the target 2238: s2, s3, sp, ra, v0 (live-in), and... the target is `move s1,v0` so s1 not live-in.

Our fall-through head is `move a0,s0`. If instead the arm's first emitted insn were something that sets s2 or s3 or v0... s3 is `panel` — the arm does `ot = xf(ot, panel, i)` where panel is s3 (read). If we wrote `panel = panel;`... no.

Hmm, alternatively: what if the call's arg setup for panel (s3) went through a copy that writes s3? No.

What about making `i` not in s1 but... The head writes a0 always.

OK, different idea: make the fall-through head ineligible because `insn_sets_resource_p(trial, &opposite_needed, 1)` — opposite_needed is computed by mark_target_live_regs(opposite_thread) where opposite_thread for the fall-through call is... wait in the else-branch call: `fill_slots_from_thread(insn, condition, fallthrough_insn, insn_at_target, 0, 0, own_fallthrough, own_target, ...)`. So thread = fallthrough, opposite_thread = insn_at_target = 2238. opposite_needed = live at 2238 = {v0, s2, s3, sp, ra?}. And trial = `move a0,s0` sets a0 → not in needed → eligible → winner. 

So indeed we need the arm's first insn to set v0/s2/s3.

Hmm! What if we make the call `ot = xf8017E1D4(ot, panel, (s32)i)` but the FIRST arg setup chosen by gcc is for the third arg? The order of arg setup: gcc emits `move a0,s0` (ot), then `move a1,s3` (panel), then... `(s32)i` → s1 is s16 so needs the sll/sra → hmm, but target has no sll/sra for the third arg! Target's arm: `move a0,s0; jal; move a1,s3`. Only 2 arg setup insns for a 3-arg function — because the third arg a2 already holds (s16)i from the loop's index computation at 2204 (`sra a2,v0,0x10`)! Indeed target computes `sra a2,v0,0x10` at the top of the loop — a2 holds (s32)i as a leftover. So the source passes `(s32)i` and gcc keeps a2 live? Interesting.

Anyway, the fall-through head is `move a0,s0`.

New idea: what if the C is structured so the call arm's head writes v0 — e.g., compute a temp used by the call inside the arm before the call, where the temp is allocated to v0? E.g. `s32 t = (s32)i; ot = xf(ot, panel, t);` — but that would emit the extension at the head (sll/sra) writing v0? In target, a2 already has it, so no insn. Hmm.

Honestly, maybe there's a much simpler path: change the C so reorg's prediction for this branch is > 0 (predict taken), because then the target thread is tried FIRST. With prediction>0, `fill_slots_from_thread(insn, condition, insn_at_target, fallthrough_insn, prediction==2, 1, own_target, own_fallthrough, ...)`: thread = target thread (taken). The stolen insn must not set a resource live at the fall-through (opposite) — `addiu v0,s1,1` sets v0; is v0 live-in at the fall-through head 2224? The fall-through is the call arm: after the jal, `move s0,v0`. So v0 is not live-in at 2224 (it's clobbered by the call... well the call sets v0? The call returns in v0, so mark_target_live_regs at 2224 should consider v0 dead-in (since jal defines it)). So it'd be allowed → the target thread fill wins → exactly the target shape!

So: make mostly_true_jump return > 0 for the beqz at 221c. Options:
(a) `rare_fallthrough - rare_dest` differences (rare_destination uses loop notes/exit labels).
(b) condition code: EQ → 0; NE → 1.

The branch is beqz = branch when the value is 0 = EQ. The condition returned by get_branch_condition is the condition to branch to the target label. We want the *source* to make the branch NE to the target, i.e., the target label should be taken when x != 0.

Currently: `if (x != 0) { call }` → beqz to skip. If we write `if (x == 0) { } else { call }` → gcc might emit `bnez x, arm` (branch when x != 0 → NE → prediction 1!) and the fall-through is the empty then + increment. That changes layout: target has the call in the fall-through and the beqz to the increment. If we invert, the call arm becomes the branch target and the increment is the fall-through — opposite of target. No.

Hmm. So the branch must be EQ-to-target (beqz to the increment) but with prediction>0. Prediction can be raised by rare_destination: if the target label (the increment path) is... rare_destination returns -1 for labels that are "exit" labels or in a different loop? Let me read rare_destination.
