---
ts: 2026-10-17T14:12:20.293Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm tallying up S17's attempt counts and tracking remaining time budgets across S01, S09, and S17 to decide how to allocate the rest of my effort.

Let me think more carefully about S17's val-vs-const priority tradeoff: computing the life spans and reference counts needed to flip priority ordering, I find the required ratio needs R≥8 references, which doesn't match the current setup of 4 val refs, so that path seems blocked unless I can shift where the load lands in scheduling.

Permuting source order confirms sched1 picks the load position independent of source statement order, so I need another angle. Maybe the const 1 isn't truly a birthing register — perhaps it's actually derived from a different expression that happens to equal 1 only in this particular case, or perhaps val itself is computed differently (e.g., already sitting in $v0 from the call) rather than being a fresh constant load.

Another thought: maybe D_801B7A84 is declared volatile, which would force the compiler to preserve load ordering relative to other memory accesses — but that's a type change affecting the whole translation unit, not just this function, so it's a heavier lever than I want to reach for.

Switching to checking whether a switch-case structure with an inline assignment avoids the reload — but that bumped the instruction count too high to be viable. And the stores targeting offsets 0x18/0x1C/0x20/0x58 look like struct field writes rather than symbol references, so that's a dead end too — those symbols are what they are.

I'm settling on two candidates as the best result for this section, then moving back to reconsider S01's scheduling order with the remaining budget.

Tracing the backward scheduling for S01: after the call instruction is placed, its dependencies (the a0 setup, and two memory stores that don't conflict since their offsets differ) become ready together, and the li instructions become ready right after their respective stores are scheduled, immediately earning top priority and slotting in right above those stores.

I'm comparing this against the original target ordering, where the a0 copy for instruction 46 appears right next to the call rather than at the end like 25 does here — suggesting something about priority or tie-breaking by instruction order differs between these two cases, which I need to dig into further.

I'm stuck on both S01 and S09 walls, so let me try one more angle for S09: maybe the original source had the result of the first call fed directly as a struct pointer argument into the second, with GCC's CSE merging equivalent address computations like `mb + 0x18` across both calls.

Revisiting the target assembly, I notice the second `addiu a0,s0,24` wasn't unified with the first — suggesting the compiler treated the two occurrences as distinct constant expressions rather than reusing the same CSE class, per the cse.c behavior around unifying pointer-plus-constant expressions.

I'm wondering if calls.c's register-parameter precomputation logic explains why the argument expands directly into a hard register rather than a pseudo in some cases, so I'm scanning the loop that precomputes register parameters to see when that direct expansion happens versus when a pseudo gets allocated.

If the expensive value expression gets copied into a pseudo register rather than reused directly. But I'm reconsidering: if mb+24 is actually a constant address expression that folds at the tree level into an ADDR_EXPR with offset, then expanding it yields a constant rtx, not a register, so the pseudo-copy logic wouldn't apply here.

So my puzzle is that CSE should treat that constant the same way each time it's regenerated after the call, giving repeated lui/addiu loads rather than my s0-based caching across the call. I need to figure out where that s0 register preservation across the call is actually coming from — maybe it's not CSE but something in loop invariant motion or combine's address handling.

Let me just dump the actual RTL for b1 and trace through CSE directly on this site rather than theorizing further.

S17 caps out at best=2 (p072, order only), so with S01 and S09 still having budget left, I'll do one more deep check on S09 — looking at how a call-crossing pseudo shows up in b1 despite the literal `D_800AF630 + 0x18` having no `mb`, by dumping the RTL.
