---
ts: 2026-10-17T16:57:33.852Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm considering whether to run a parallel investigation on item 2 while continuing item 1's experiments, and I'm examining another code site at offset 0x108 where a loaded value gets compared against 255 and then copied into a0 before an addiu adjustment—trying to figure out whether v1 gets reused afterward.

Looking at the else branch, v1 ends up dead after the join, matching the same copy pattern seen before. I'm wondering if the original source had something like a temp variable check (`if (temp_v1 != 0xFF)`) that wouldn't produce a copy at all, meaning the copy in the target binary might stem from an inlined function call where gcc 2.7 generates parameter pseudos—though I'd expect cse to eliminate those unless something about how cse handled canonical registers in this case kept the redundant copy alive.

I'm also considering whether combine could have merged the copy differently depending on which register was treated as canonical, and whether reorg's delay-slot filling from predecessor blocks might explain why the copy survives before the branch test rather than being optimized away.

I'm trying to construct a scenario where a label sits between the copy and the subtraction within the same block, perhaps through a merged control-flow path where a jump target reintroduces the copy before the dead check. Still working through whether the original test condition could be structured differently to naturally produce this unnatural-seeming pattern.

I'm wondering whether combine could simplify a shift-then-compare-to-zero pattern using known sign-bit information, but cse would likely rewrite any reuse of the original register to the canonical copy first, which blocks that path unless the original register survives untouched somehow.

So maybe the trick is that the HImode value isn't promoted at all — if the compiler loads it directly from memory as a 16-bit value rather than through a sign-extending register copy, cse might not create that problematic equivalence in the first place.

I'm starting to suspect there isn't a clean fix here and I should just accept the limitation rather than keep chasing this edge case.

Trying a short-lived copy variable still fails since its lifetime stays confined within the extended basic block, so CSE still rewrites it back to the canonical v0 and the copy dies. This pushes me to reconsider whether CSE's jump-following behavior (flag_cse_follow_jumps and cse_skip_blocks, both enabled at -O2 in this version) extends the block boundary across the conditional jump in a way that changes which variable survives.

Since the test precedes the copy, v0 stays canonical and the use gets rewritten there, so I'm circling back to the same wall: every plain register copy gets eliminated either by cse or by combine. The mechanism seems to be that the then-block copy dies into a combine fold, while the pre-branch copy gets absorbed by cse's canonicalization of the test. I should check the elapsed time against the best known score of 17.

Trying other partial configurations with fewer pins doesn't help since pin is the only lever kind here, so that's equivalent to the original. I'll lock in WALL at 17 and move on to writing up the notes and results.
