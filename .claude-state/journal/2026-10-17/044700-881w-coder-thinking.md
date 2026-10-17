---
ts: 2026-10-17T10:47:00.607Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I should jot down my attempts so far in notes.md before continuing. I'm trying another ordering hypothesis — maybe the source order is t3v, k, j, with t3v reading first and j being created last so it wins, testing whether reversing this produces the target output order.

But the scheduler in 2.7.2 picks instructions by rank with ties broken by insn LUID, preserving original order — so flipping order isn't that simple, it depends on register live lengths computed after scheduling. In the c13 arrangement j being born last gives it a shorter live length and lets it win, but in the target order j is born first, meaning j must win purely on reference count instead. That means either j has more refs than I assumed or k has fewer — and reducing k's refs would require one of the three uses of a3 in the inner loop to actually belong to a different pseudo register rather than k itself.

I'm checking whether that's even possible given k's liveness, and concluding it isn't since k is live throughout, so j needs more refs instead — likely t3v reads m giving k=11 refs, and j picks up an extra depth-2 reference (since reg_n_refs is weighted by loop_depth, with depth 1 at function level, 2 for the outer loop, 3 for the inner), pushing j to 13 refs and letting it outweigh k's 11.

Now I'm tracing through how gcc 2.7.2 actually expands a for-loop — the initial test, body, continue label, increment, and end — and whether loop.c or jump.c rotates the loop structure afterward, since that could explain where the extra j reference comes from.

What catches my attention is "duplicate_loop_exit_test" in jump.c, which copies the exit test to the loop's end as part of rotation, making the top-level test into a preheader test that CSE can fold away since j starts at a known value of 0, leaving no trace by the time flow analysis runs.

I'm now considering whether combine could be the real culprit instead — perhaps it's merging the `j = 0` initialization directly into its single use point, which would explain a reference to j disappearing from the final code without CSE being involved at all.

I keep circling back to flow's reg_n_refs counting, suspecting combine might leave stale reference counts since it doesn't recompute them after merging insns, so an extra j reference from before combine's pass could simply vanish without actually affecting generated code — and I'm now walking through how HImode increment of j would expand, with intermediate widening to SImode for the arithmetic before narrowing back, to see if that sequence hides an extra read or write of j that flow counts but combine later eliminates.

Checking whether k's set happens at depth 2 inside the outer loop preheader—yes, it does. I'm trying candidates where a sign-extension test like `(s16)j == 0` gets built from shift insns that combine merges down to a single j read, which doesn't give the double-depth-2 reference I need; so I'm trying variations like `j < 1` to see if that forces two separate reads of j in the RTL.

Now I'm wondering about the exit test itself—if cse makes it read the increment temp in our version, but instead the RTL reads j directly, then the depth-2 reference would land on j rather than the temp, changing which candidate wins allocation. That leads me to suspect a later pass, maybe cse2 running after the loop pass but before flow, could be substituting the temp back in for j, and I want to check the exact pass ordering in this compiler version to see if that's plausible.

I'm also considering whether combine could merge the subreg assignment to j with the later shift test, but combine typically only folds an earlier definition into a later use when the earlier destination dies at that point—and j stays live across the loop, so combine would normally have to keep both instructions rather than substituting directly.

I wonder if the source differs with something like `j = j + 1` producing extra refs, or if k isn't a simple copy of m but rather `k = i`, which gave identical output in my ki test. Shifting perspective, I'm now thinking about register allocation order — global alloc assigns j before k, mapping to specific hardware registers, and I'm questioning whether MIPS 2.7.2 even has a REG_ALLOC_ORDER or just picks the lowest available register.

The allocation order could matter if one variable conflicts with a2 due to a hard register being live across a function call — for instance, if k's lifetime overlapped with a call that sets a2 explicitly. But checking the inner loop, no calls happen there, and k's birth seems to come after the earlier call that sets a2=2, so that theory doesn't hold. I'm now considering whether some other block in the loop region uses a2 as a hard register that would force a conflict.

Another angle is copy preferences — if k had a preference for a3 through a copy relationship with another pseudo already bound to a3, the global allocator's preference logic could steer it there instead of a2.

I recall that set_preference checks reg_renumber for pseudos already allocated by local-alloc, redirecting src_regno to the hard reg they got assigned — so copy preferences can point toward locally-allocated registers too. Looking at the base table again, r99 with 8 refs and live range 11 prefers a2 and conflicts with a3, which is a useful data point.

So the choice seems to boil down to giving j a preference for a2 or k a preference for a3, but I need to trace where those preferences would actually come from — a2 preference would need j copied to/from a2, like being the 3rd call argument, but there are no calls in the inner loop, and similarly a3 would need k as a 4th argument which also doesn't apply. I'm now wondering whether parameter i or n, which arrive in a1 and a2 at function entry, factor into this, since n appears to get spilled to the stack early on.

Stepping back, I should check my budget: I've tried about 25 combinations without beating the known baseline of 4, and my stop rule is 20 consecutive tries without gain. The lever-free best stays at base 35, since the pin-based tests don't count toward that score. Let me try combining lever-free path-1 alternatives with tk_forj's fixed allocation but order-4 result, like pairing c29's shared size with tk_forj.

c29's shared size trick still counts as lever-free since it doesn't use pin/asm/volatile/builtin, so I want to try declaring a shared size variable at function scope and passing it into the call instead of a literal, mimicking c29's structure to see if it also hits 4. I'll also revisit the natural path-1 alternatives before committing to this.

Every loop form and spelling variant still lands on 10 or shifts order at 11-12, except `tk_forj` which fixes the allocation but costs 4 ORDER. I'll log these attempts, then run a path-1 battery on the lever-free body with `tk_forj` applied.
