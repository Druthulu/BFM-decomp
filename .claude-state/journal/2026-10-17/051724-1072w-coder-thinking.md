---
ts: 2026-10-17T11:17:24.725Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
That s16 copy case doesn't work either since it's just sign-extension at the copy site. But I'm making real progress here - the lever-free comparison between andi and move is a solid difference I should record as a win candidate. Now I need to find a copy case that cse doesn't treat as equivalent and that optimize_reg_copy_1 doesn't fold away.

I'm wondering if cse's fold_rtx actually has special handling for AND with a zero-extended value equivalent - if m's expression class includes a zero_extend form, cse might recognize that the mask matches and simplify the AND away entirely, which would explain why I can't find a surviving andi instruction in this path.

I'm also considering whether k's mode mismatch could prevent cse from treating it as equivalent, since insert_regs skips equivalences when the register's mode doesn't match, but k seems to stay SImode throughout. Looking at make_regs_eqv, it scans the class of the source value for a register matching k's mode, which could be another angle for why the equivalence forms the way it does.

Now I'm tracing optimize_reg_copy_1's conditions more carefully — it only fires when flag_expensive_optimizations is set and the source register isn't marked dead, then checks whether the source and destination register numbers differ before scanning forward from the instruction to find where coalescing could apply.

I'm realizing the scan would break if it hits another set of the source or destination, or a loop boundary note, before reaching the point where the source dies. Since the hoisted assignment sits right before the loop-start note and there are no other labels, jumps, or loop notes in the preheader, nothing seems to stop the optimization from applying here, which doesn't match what I'd expect if it were being blocked.

So I'm testing whether the actual mechanism is coalescing through register preferences instead: since m dies right at the copy, it doesn't conflict with k, so m's preferences would absorb k's hard-register preference. Allocation order then matters—whichever of m or k gets processed first picks the preferred register, and the other follows since there's no conflict, which would explain the coalescing happening without needing a separate K3-style preference rule, perhaps simply because allocation priority order already favors it.

Looking at the conflict lists for r197/r198, a1 isn't listed as conflicting, which suggests a1 is already claimed by an earlier-allocated global (the giv), pushing j and k to fill a2 and a3 based on which gets processed first—bringing me back to needing j's priority to exceed k's, with their live lengths (j=75, k=74) being close enough that ordering or hoisting could tip it either way.

I'm now considering whether optimize_reg_copy_1 could shift k's ref count by adjusting for a copy where t3v reads m instead of k, but that doesn't help j. I'm shifting focus to whether j could get a hard-register preference toward a2 directly, like through a copy with a third call variant, though that doesn't seem to change anything yet.

Testing why j still gets swapped when preferring a2 — since k gets allocated first and grabs a2 before j can claim it, the preference only wins if the preferred register isn't already taken. So I'm going back to the k-prefers-a3 scenario, trying to figure out how m could avoid coalescing — maybe m needs to conflict with k, or have its own preference toward a different hard register so it doesn't just inherit.

Copy preferences get shared whenever the dying register is the SET_SRC, which it is here, so that path fails too. I'm now considering whether optimize_reg_copy_1 could be blocked by inserting another set of k between the copy and m's death, or by forcing validate_replace_rtx to fail at the copy site.

If replacement fails, the death note never moves, so m still dies where it originally does, leaving a conflict and no shared preference — but I need a concrete reason for validate_replace_rtx to reject substituting k for m, since a plain shift instruction would normally accept it fine. I'm also wondering whether a mode mismatch via a SUBREG reference to m could prevent the death note from matching cleanly.

Another angle: the dead-code scan stops at the first JUMP, so if m's last use lies past the preheader boundary — right at the LOOP_BEG note — the optimization simply never reaches it, depending on how sched1 reorders insns relative to that note.

But if `k = m` actually lives in the preceding block (ending in a conditional branch) while t3v is in the next block, the dead-scan halts at the jump and misses the rewrite — yet cse, operating on the same extended basic block, would still fold t3v into reading k directly, which defeats the goal by letting m die at a plain copy that coalescing can then merge.

So I need t3v to read m in a way that survives both cse (no recognized equivalence) and copy propagation (no rewrite) while still compiling down to a bare move — the (u16) cast handles the first two but forces an andi instead of a move. I should check whether going through an HImode subreg of k avoids the mask and emits a clean move.

What about trying the cast in the opposite direction, where m itself is the unpromoted u16 loaded via lhu and then widened into k — in the mu16_m case this produced one fewer instruction with m and k apparently sharing a3, suggesting the zero-extend copy somehow became a no-op move that coalesced rather than emitting andi. I need to dig into the mu16_m diff around lines 133-145 to see how that zero-extend was eliminated.
