---
ts: 2026-10-17T18:37:58.519Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm realizing this dump is actually post-sched1, since in gcc 2.x the pass order is combine, sched, lreg, greg — so sched1 ran before lreg and must have moved insn 25 past the call at insn 30, confirming sched1 scheduled across calls.

Insn 25 sets s3, a call-saved hard reg with no dependency on the call, so sched1's backward list scheduler treated it as having low priority since its result isn't needed until a later block, letting it slot in after the call instead of before. To reproduce this with real C code, I'd need the dependency structure or priorities to force the scheduler to place it before the call instead.

Even if s3 were call-clobbered, since it's a pseudo live across the call, it'd get allocated a callee-saved register anyway, so that doesn't change the dependency picture. I'm now considering scheduling priority instead: how sched1's rank_for_schedule tie-breaks insns with no explicit dependency by original order, and whether the call acts as a barrier relative to a volatile asm the way it would for insn 25's placement.

I'm also trying other arrangements — moving the call into a different statement or block, or tying s3's computation to the a0 set — but none of these match the target, where s3 is set before the call and the s0 masking happens after it in the delay slot.

One idea is forcing insn 25 to depend on something earlier so it's scheduled before the call, but it has no real dependencies. This makes me think it's a scheduling priority issue: in backward list scheduling, insns with no consumers in the block get lower priority, so the order they're picked at the end of the block depends on how gcc's heuristic ranks them against the call and the branch.

I'm wondering whether restructuring how the call result is tested—forcing it into its own block somehow—would sidestep this scheduling quirk entirely.

I'm also considering whether putting the s3 assignment before a label would help, but that requires a real jump into it since dead labels get pruned, and I'm trying out loading the address through the index array or arg setup as alternate approaches.

Comparing the target's ordering against mine, I notice the call sits in a different spot relative to the s3 load and the zero-extension — in the target it's move/addiu/andi/move/move/la/jal/andi, while mine shifts la after the call. This makes me wonder how gcc 2.7's scheduler treats CALL_INSN with respect to dependency analysis, since that could explain why the ordering diverges.

That rule only blocks pseudos that don't already cross a call from moving across one, which doesn't apply here since insn 25 precedes the call. So the real explanation must be something else — maybe s3 wasn't just a pin but tied to how the pointer into D_800A6588 was actually computed in the original source, perhaps loaded via a `lui` instruction rather than a simple pseudo assignment.

I'm trying different reorderings of the source statements relative to the call, since the scheduler can only shuffle things within the block from the original program order, and so far placing the s3 computation before the call in every variant still gives the same six-instruction block.

I need to think about gcc 2.x's scheduling algorithm itself: it schedules backward from the last instruction, building a ready list of instructions with no unscheduled successors, and ordering them by priority (roughly the critical-path length to the end of the block) plus tie-breaking by insn order. I'm trying to work out whether higher-priority instructions actually end up placed earlier or later in that backward pass, since that would explain why the address computation stays before the call in the target.

But observed order is call, 38, 25, 40, so something must have blocked the call until later readiness — the call has anti-dependencies on earlier instructions (16, 11, 14, 22), and 38 also has an anti-dependency forcing it after the call. That means the call couldn't be scheduled until its anti-deps cleared, which likely explains why 25 ended up ready and placed ahead of it in the backward ordering.

Thinking through gcc's rank_for_schedule tie-breaking logic, it seems to come down to priority differences, then preferences for insns depending on the last scheduled one, then LUID ordering, possibly with special handling for call insns and register "birth" boosts in backward scheduling.

I'm wondering if insn 25 is being treated as a birthing insn for a register that reduces its scheduling priority or lifetime, and whether removing the hard-register pin on s3 or replacing it with a pseudo would change that behavior.

I should test a couple variants: one with just the s3 pin dropped, and another with all pins dropped entirely.
