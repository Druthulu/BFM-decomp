---
ts: 2026-11-06T15:12:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SqfvRsnHuL8p8pbYbsMy
---
In a0: launching 472 (vol mult) at T-9, and no "launching 484" line? Let me see the full log region for a0.

Interesting: in b4, 484 (pan) launched first at T-10, then 472 at T-22. In a0, 472 launched first at T-9. So the final code order differs? But a0's final disassembly had pan first (from the diff: mine[200] addiu a0,a3,160, mult a0,a2). Hmm, the sched1 order and final order are decoupled due to sched2.

I'm going too deep. Let me look at the actual sched2 dump for both and compare the final insn order. Actually, the .sched2 dump contains the final RTL before reorg. Let me compare the region in a0 vs b4 vs the target(orig).

But honestly, the difference between b4 and target is ONLY the delay slot. b4's insn stream is otherwise identical. So sched2 order matches; reorg picks a different delay-slot insn. That's the whole issue.

So: can I make reorg prefer the sll? Options:
(a) Move the andi out of the bne's basic block.
(b) Make the andi not eligible (resource conflict).
(c) Make the sll appear before the andi in the backward scan? The backward scan stops at a label. The order from the bne backwards: subu a2 (pan result), sra v1, mfhi a2, sra v0, subu a1 (vol)... all feed the branch? The branch is `bne a2,v0`. needed = {a2, v0}. Scanning backwards: insns that set a2 or v0 conflict. `subu a2,v1,v0` sets a2 → conflict, skip. `sra v1,a2,3` references a2 but doesn't set; sets v1. `insn_references_resource_p(trial, &set, 1)` where set = resources set by the branch (none, just pc?) — hmm, set is what the branch sets. The check `!insn_sets_resource_p(trial, &needed, 1)` — needed = registers the branch uses (a2, v0). `sra v1,a2,3` doesn't set a2/v0 → eligible? Then it would be moved into the delay slot! But it's needed by the branch's operand (transitively), and reorg's scan also requires `insn_references_resource_p(trial, &set)` — set accumulates as it scans. Let me re-read: after each trial, `mark_set_resources (trial, &set, 0, 1); mark_referenced_resources (trial, &needed, 1);` — set accumulates the sets of insns skipped, needed accumulates references. So moving an insn into the delay slot must not set resources set by later insns and must not set resources needed by later insns. Since `sra v1,a2,3` sets v1 which is needed by `subu a2,v1,v0` (skipped later... no, earlier in the scan). Hmm, the scan is backwards: trial starts at the insn just before the branch = `subu a2,v1,v0`? No — the branch's operand computation. Let me map: before the bne at 588: insns ... subu a2,v1,v0 (580) then li v0,16 (584) then bne. The scan starts at li v0,16: sets v0; needed includes v0 (branch uses v0) → conflict (insn_sets_resource_p(trial,&needed)) → skip, accumulate set={v0}, needed={a2,v0}+refs of li = {} → still. Next trial = subu a2,v1,v0: sets a2 ∈ needed → conflict. accumulate. Next sra v1,a2,3: sets v1 ∉ needed; but does it reference resources in `set`? set={a2,v0}; it references a2 → `insn_references_resource_p(trial,&set,1)` is true → conflict → skip. Good. Next mfhi a2: sets a2 ∈ needed → conflict. Next sra v0,v0,0x1f: sets v0 ∈ needed → conflict. Next subu a1,a0,v1: sets a1 ∉ needed, references a0,v1 ∉ set? set now includes {a2,v0,v1,...}? After skipping sra v1 (sets v1), set={a2,v0,v1}. subu a1 references v1 ∈ set → conflict. Next sra a0,t1,0x6: sets a0; references t1. Is a0 ∈ set? No. t1 ∈ set? Hmm, set accumulates. mfhi t1 sets t1, so t1 was added to set. So references t1 ∈ set → conflict. Etc. So the whole chain conflicts and the scan stops at the block start (or a label). So in the target there's no eligible pre-branch insn → thread copy.

In b4, the andi sits at the top of this chain (before all of it), so after skipping the whole chain, the scan reaches the andi: sets a1. Is a1 ∈ set (accumulated)? set = all regs set by skipped insns = {v0,a2,v1,a0,t1,...}. a1 is set by `subu a1,a0,v1` → yes, a1 ∈ set! So `insn_sets_resource_p(trial,&set)` → conflict! Then the andi should NOT be eligible...

Hmm, but it WAS moved. Unless the andi is scheduled elsewhere. Let me look at the b4 final disassembly again: 
```
584 li v0,16
588 bne a2,v0,594
58c andi a1,a1,0xffff
590 li a2,15
594 sll a2,a2,0x8
```
Wait — is the andi really in the delay slot? The delay slot is 58c. And `li a2,15` at 590 is the fall-through. So the andi is at 58c — delay slot. And the sll at 594 is after. Hmm, so the andi was placed in the delay slot.

But per my analysis it should conflict (a1 ∈ set). Unless `insn_sets_resource_p` with `1` (include calls?) — the last arg is `1` = include_delayed? Let me look at the exact semantics. Actually maybe a1's set by subu is *dead* by then (REG_DEAD on a1? no, a1 is vol, live to the call).

Hmm, maybe the delay slot was filled by `fill_slots_from_thread` not the backward scan — the andi is in the fall-through thread? No, the andi at 58c precedes the branch in source.

Wait — maybe reorg's delay slot for the bne is filled from the THREAD (fall-through) with the andi because the andi was scheduled... no, the andi is before the branch in the final code, at 58c which is after the branch insn at 588 — that IS the delay slot position (branch at 588, delay slot at 58c). In the RTL before reorg, the insn order would be: ... andi(478), ..., bne, li a2,15, sll. After reorg: bne, andi, li 15, sll. So the andi was MOVED from before the branch into the slot (backward scan) OR it was already the fall-through?

Hmm, actually maybe the RTL order before reorg is: bne, andi, li 15, sll — i.e., the andi was scheduled AFTER the branch by sched2? That can't be: the branch is a jump_insn; insns can't move across a jump in sched1 but sched2 also doesn't cross jumps.

I think I'm overanalyzing. Let me try a practical alternative: make the second set of vol a *call argument copy* that's zero-cost? No.

PRACTICAL NEW IDEA: give vol a second set that is *the existing andi at the call* (c1) but ALSO make the launder position free... c1 gave 236/pan-first. So c1's second set didn't influence. Why? Let me dump c1 properly and check reg_n_sets and the sched. Actually, maybe in c1 the second set of vol is in the same insn as the final andi, and combine turned `(vol | X) & 0xFFFF` into a form where vol's first set got merged/forwarded by cse, i.e., cse replaced vol's use with the div expression? Hmm.

Let me check c1's sched dump for reg 196 sets.

I'll dump c1 correctly (the earlier attempt copied stale). Use the same command sequence with verification.
