---
ts: 2026-10-17T11:59:45.959Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm trying to figure out which label survives past the first jump deletion pass but still has its references vanish by the time of a later pass like local-alloc, reload, or jump2 — since a label referenced only by a jump that becomes redundant later would need that jump to still exist at cse2/local-alloc but then get eliminated afterward.

I'm considering whether cross-jumping in jump2 after reload could be the mechanism, since that pass merges equivalent branch targets after register allocation. I'm also second-guessing whether the copy instruction and the loop-top label are actually positioned the way I assumed, since scheduling before the second pass could reorder things within the block.

Then I wonder if NOTE_INSN_LOOP_BEG/END notes separating the copy and the second temp could matter — checking whether cse2's end-of-basic-block logic actually stops at those loop notes or skips past them since it runs after loop optimization.

I'm also wondering whether a do{}while(0) wrapper actually changes anything structurally, since cse2 could still rewrite the loop-note references the same way. Stepping back, I want to think through the register allocation angle more concretely: which lower-priority allocnos actually conflict with k, since that determines what regs_someone_prefers accumulates for it.

I'm scanning for lower-priority, long-lived pseudos like a, b, c, i, n that conflict with k across the loop, checking their reference counts and priorities. One candidate, i, gets sign-extended into a2 when passed as an argument to a call, which would set a preference for a2 and could push k away from that register.

But since i crosses calls, prune_preferences strips call-clobbered registers like a2 from its preference set, so I need to verify whether that pruning actually removes i's a2 preference in the current code path.

Now I'm trying to find which non-call-crossing pseudo live during the loop actually holds the a2 preference, so regs_someone_prefers can pick it up from a lower-priority conflicting allocno. Candidates like pb, m24, mhi, t3v, q, and e seem worth checking—e in particular looks promising since it appears to have no calls crossing its live range.

Tracing through q's computation, it's just a pointer offset from ot with no hard-register src, so that candidate doesn't fit either. I'm wondering whether the real scenario needs optimize_reg_copy_1 to fail on validate_replace_rtx because m appears in a context requiring a hard register, or because m only shows up in REG_NOTES rather than the actual insn body.

Replacing a same-mode register with another in a subreg context like a movhi shouldn't normally make the insn unrecognizable, so that path seems like a dead end. What's more promising is that the scan for m's death only looks within the current block — if m is still live out of the preheader and only dies somewhere inside the loop, the copy propagation into k might never trigger properly within that block boundary.

If m is used after the loop but not inside it, m stays live through the whole loop, meaning v1's clobbering in the loop conflicts and blocks the optimization — unless the scan in optimize_reg_copy_1 halts early due to a LOOP_BEG/END note, jump, or label sitting between the copy and t3v. That raises the question of ordering: is the "k = m" copy actually placed in the preheader, or could it instead sit at the top of the loop body itself?

If the copy executes every iteration inside the loop, loop.c would recognize it as invariant (since k is set once and m doesn't change) and hoist it out to the preheader, which changes where it lands relative to t3v, pb, m24, and mhi in the instruction order. That raises the possibility that cse2 still rewrites things even after this hoisting happens.

Thinking more carefully, cse2's rewriting depends on whether k's last use extends beyond the cse block or its first use precedes the copy point — so if the hoisted t3v computation comes before the copy in the preheader RTL, m might die at the merge point unless it's used again afterward. At this point I'm starting to suspect the K3 approach itself is flawed, and I should go back to the simpler plain-copy route and figure out how many references k or j would need for cse to rewrite it properly.

I'm also wondering if k's live range could be extended by being function-scope and somehow live across a loop boundary, but that seems to break down since the earlier assignment would just be dead code eliminated by flow or cse. Another angle: maybe k is actually the function-scope variable used as the fourth argument to the K3 call, with the source originally having a separate k = b[0] assignment feeding into a conditional check.

I try flipping this: maybe the long-lived outer variable is K itself, carried through to the K3 call as a3, with a separate inner loop index copied from K. But checking the K3 region shows a direct load into a3 with no visible intermediate copy, which rules this out if K were mapped to v1 — the code would need to show a move instruction that isn't there. Scrapping that idea, I want to reconsider the problem by looking at register allocation priorities instead.

Now I'm tracing through what happens if m is allocated before k rather than after, since m carries copy preferences for a3 inherited from the merge with k, and find_reg's preference-matching logic might pick a3 for m directly if it isn't excluded by the "used" register set in that pass.

So the key question becomes whether a3 ends up in regs_someone_prefers[m], which would knock it out of m's AND_COMPL'd copy preferences — and that depends on whether expand_preferences runs before prune_preferences in global_alloc's actual call order, which it does.

Thinking about whether k's assignment could become a copy only after optimize_reg_copy_1 in local-alloc has already run, so it slips past that rewrite but still gets caught by global's conflict logic — nothing sits between local-alloc and global_alloc to produce that timing, and combine would just trigger optimize_reg_copy_1 anyway as before.

I'm also reconsidering optimize_reg_copy_1's dead-register check, since it relies on finding a REG_DEAD note on the source register matching mode, and if that note's placement or mode doesn't line up the rewrite simply won't fire.

If m dies later at t3, there's a conflict and no merge happens at all. Checking cse2, I'm wondering whether that subreg assignment even registers as a reg-reg equivalence, since cse only merges quantities when the source is a plain REG of matching mode, not a subreg — so it would record k's value as the subreg expression rather than unify with m's quantity. That makes me reconsider how a paradoxical subreg like this would even arise in the first place, probably from a case where k is SI and m is a narrower HImode register being widened.

C semantics demand a zero_extend here unless GCC treats the HI register as already promoted, but checking MIPS's config, PROMOTE_MODE doesn't promote local HI registers in this setup, so a u16 value should legitimately produce a zero_extend into SI, lowering to an andi instruction. But then I'm considering combine: if m is loaded via lhu from memory and then immediately zero-extended into k within the same block, combine could fuse these into a single lhu load directly producing k, since HI loads from memory already use lhu regardless.

So for an HImode register m, the generated load is `lhu v1,0(s5)`, and when m gets compared against i, the target code shows `bne v1,v0` with no andi at all — meaning the compiler already knows the loaded value is zero-extended without an explicit mask. This must come from MIPS's LOAD_EXTEND_OP setting for HImode to ZERO_EXTEND, which tells combine that a SImode view of an HI register loaded via lhu already has clean upper bits, avoiding any redundant masking.

Checking the dump confirms reg 193 is the zero-extended version of reg 194, which itself is the HImode memory load. I'm noting that u16 m variants score the same across these configs except for a j/k register swap, meaning u16 m produces identical, clean code with no extra andi. Now I want to verify this holds on the K3 base case too, by building that config with u16 m and a plain assignment, then inspecting the copy RTL in cse2/lreg to see whether m dies there as expected.
