---
ts: 2026-10-17T17:08:30.527Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm thinking about loop-invariant hoisting thresholds from moves.md — specifically how the threshold compares against savings times lifetime versus instruction count, and whether shrinking the lifetime (distance between set and use) by placing the set immediately before its uses could push a borderline case below threshold.

I'm also recalling other conditions in loop.c that can block hoisting, like "maybe_never" for insns after conditional branches, or the rule that a set isn't movable if the register is used before being set in the loop. I'm trying to recall the exact invariant_p condition checking consecutive sets and dependencies that determines movability.

So the logic says a register is non-movable if it's used across basic blocks even when not a user variable with the loop-test exception, or if it's a user variable with the set guaranteed under maybe_never and used outside its block. So to construct a failing case, I need a user variable like "size" that's set after a conditional branch (making maybe_never true) and then referenced in a different basic block than where it's set.

I'm also considering whether the set could instead happen before the branch at the top of the loop, which would make maybe_never false and leave the register trivially movable—so that path doesn't produce the counterexample I want. Another angle is examining what happens if the register is set twice in different arms, since that could hit a different code path through n_times_set and consecutive invariant sets.

But since common code later reuses size after multiple instructions, I need it stored in a register that survives, which rules out v0.
