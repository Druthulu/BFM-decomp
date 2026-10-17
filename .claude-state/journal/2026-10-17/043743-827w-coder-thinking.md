---
ts: 2026-10-17T10:37:43.389Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm computing the threshold as 2*(1+n_non_fixed_regs), with the loop call flag set to 1 and insn_count at 74 from counting register-set instructions. Checking whether savings*lifetime*58 clears that threshold—lifetime of 2 would qualify for moving, but I'm wondering if lifetime could be 1 despite two uses, depending on the ordering of set/store instructions.

I'm tracing how luids get assigned per instruction in loop.c—whether notes share luid values with real insns or only real insns increment the counter, which affects minimum lifetime for two uses. I'm also considering whether `moved_once[regno]` doubling insn_count (from being moved out of an inner loop already) could push insn_count past 116 and block the move, and whether the inner loop containing a call changes this calculation.

I'm now checking the loop-call threshold—58 against 74 doesn't exceed it, so that's not the blocker either. I'm wondering if the constant 8 is actually stored in a variable that gets set more than once in the loop, since loop invariant motion requires n_times_set==1 (barring consecutive sets)—maybe a size variable gets reused for two unrelated computations within the same loop, which would explain why it isn't hoisted.

I'm also considering a "y" temp variable reused across both branches of the conditional plus a later store of 8—if y gets set three separate times across the arms, it would have n_times_set==3 and be disqualified from invariant motion, even though it's a natural artifact of branch-specific temp reuse.

Given that global allocnos could lose $v0, I want to check the v_yarm_* file variants (chain/copy/lit/tv/yv) since c48 already tried this exact "y set in arms" approach, but it's missing from the results table. I'll score these c48 files along with the related w_* and scratch-level files to see if any lever actually worked.

I've confirmed the hoisting rule (58·1·2=116 ≥ 74) explains why the 8 gets hoisted. Now I'll score every c48 candidate in one batch to get the full landscape before diving into individual cases.
