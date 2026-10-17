---
ts: 2026-10-17T10:37:06.956Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm considering reusing the variable `t` since it's already used as a register for a computed value earlier, but since its first assignment lives in an outer loop rather than the current basic block, it's treated as a global allocno spanning multiple blocks rather than a local one.

I want to run a quick battery of variants targeting path 1, aiming for a score where the loop retains the literal 8 (similar to the pin case scoring 10 with the j/k swap intact). I'm testing things like reusing `t = 8` directly, wrapping the size in a struct-style macro, declaring the size at function scope and initializing it at the top instead of inside the loop, and trying alternate field types or pointer casts for the store.

Rather than guessing at placement effects on lifetime, I should actually check the real gcc-2.7.2 `loop.c` source in `scan_loop` to see how `savings` is computed and what threshold determines whether a constant gets hoisted into a register like `$v0`.

c29 hit path 1 in plain C by sharing a variable with an earlier literal 8, but that was flagged as steering. I'll check the exact loop move rule in the pinned compiler source to see what else keeps the 8 in the loop before trying more variations.
