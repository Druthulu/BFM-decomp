---
ts: 2026-10-17T11:46:14.403Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm checking that allocno size computation works out to one word for HImode registers, and noting that global.c's allocno stats could aggregate multiple pseudos tied together rather than tracking them individually.

I'm trying to figure out which pseudo variable could plausibly match the target's reference count and live range—testing whether it's the sign-extended index variable k, a function-scope constant like c3, a scaled loop variable t, or something tied to a second array lookup, but none of these quite fit since the target seems to use the index directly rather than through a subreg or sign-extension step.

I keep probing whether j's live length could actually equal k's rather than the other way around, wondering if scheduling reorders things so j is born at the same point, or if k somehow stays live longer by dying later at loop exit—but nothing cleanly explains the exact live-length and reference-count match yet.

I should just test it directly rather than reasoning abstractly — try swapping the order so `k = m` comes before `j = 0`, which would make k born first and possibly flip which variable wins priority in the scheduler. I'm also wondering if the scheduler's backward list scheduling assigns earlier final positions to higher-priority instructions based on critical path, which could explain why j=0 gets placed first.

Rather than keep theorizing about the scheduler's LUID tie-breaking, I should just try variants directly: swapping the assignment order of k and m, moving k's assignment before the for loop, or restructuring the init differently, and see which actually reproduces the ordering.
