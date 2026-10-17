---
ts: 2026-10-17T17:03:31.055Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
The goto loop seems to lose its strength reduction benefit compared to the target, with register differences showing up in the outer loop too. I'm going back to candidate a4, scoring 25, where the li 8 constant got hoisted — the pin must be preventing that hoist, so I need to think about natural ways to stop a constant from being hoisted.

One idea: loop.c won't move a constant set if it's assigned more than once (n_times_set > 1) or the register is marked may_not_optimize, so if `size = 8` were set separately in both the if and else arms, it wouldn't be considered invariant, though that risks producing two li instructions instead of the single one in the target's common tail. I'm also wondering whether the move depends on some savings threshold in loop.c's constant-motion logic rather than purely the set count.

Looking closer at loop.c's threshold formula, moving an invariant depends on `threshold * savings * lifetime` versus the loop's total instruction count, so with `size` only used twice nearby, its lifetime is tiny, and unless savings and threshold push the product high enough, the set stays inside the loop rather than being hoisted. This suggests that keeping `size` as a literal used directly in each store, each needing its own pseudo register, would shrink the lifetime enough to prevent the compiler from floating it out — matching the behavior we need.

If a call existed, the threshold would halve and the move wouldn't happen, but this loop has no call so that path is closed. I'm trying other angles, like forcing a single-use store to change codegen, but that doesn't seem to help either — need to think about whether the inner loop placement changes anything structurally.

Another angle: if `size` gets assigned multiple times within the loop, loop.c's n_times_set check matters, but cse might collapse a redundant second assignment of the same constant value since it tracks known equivalences for registers.

I'm also considering splitting the assignment across both if-arms—since each arm sets size=8 separately, that's two separate sets, so n_times_set=2 and it wouldn't get hoisted as invariant. But if the tail ends identically in both arms, jump2's cross-jumping optimization could still merge them into a shared insn before the join point.

Still, the target has `li v0,8` sitting mid-loop at position 196, right after the lhu/addu sequence, not hoisted into a separate arm—meaning it must genuinely belong to the common block rather than being duplicated and merged. That contradicts the two-separate-arms idea, so I need another way to pin the assignment exactly where the original places it.

Maybe loop.c's may_not_optimize logic is relevant here—registers get flagged when they're set in a way that isn't a clean full REG destination, like through a subreg or STRICT_LOW_PART, which would block invariant motion. But a plain `size = 8` is a full SET, so that doesn't obviously apply unless the promotion creates a partial write somehow.

Making it volatile or address-taken would force memory access instead, which isn't what I want either, so I should look for a different lever that scores correctly without those side effects.

Keeping pin alive while cracking keepalive seems like the right path—score 10 for that configuration. I want to boost j's reference count so it outranks k, possibly using the `do{}while(0)` trick with the required `!FAKE` comment, which the brief explicitly permits as an allowed move.

For k, I'm weighing whether to eliminate it by substituting `m` directly instead of copying `k = m`, since k's only uses are indexing into D_80115140 and computing k2. I should check the a5 diff first to see which substitution variant actually works.
