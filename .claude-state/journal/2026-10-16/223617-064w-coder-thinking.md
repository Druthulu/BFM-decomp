---
ts: 2026-10-17T04:36:17.412Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5605ba96cc5ff027
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c792287-f11f-4848-8566-c39a9bb058a0
---
The K&R sites for SC07_000 turn out not to be load-bearing with explicit args — all nine match, so that's not relevant to the lying census exceptions. Now I'm checking the BCC0 shared header, which gets included by SC03_126/SC04_021/SC05_019 but not SC07, so it falls outside my constraint.

Looking closer, the related headers BBE0, BD78, and BEA0 each declare func_8016BF50 differently — one as a block-scope ANSI prototype, the others K&R. Changing just BCC0:9 to pass the argument explicitly would compile fine regardless, but making it a consistent ANSI prototype across all four headers would expand beyond the brief's named scope, which only calls out BCC0:9. I'm leaning toward editing all four since they're the same class of fix and genuinely needed for consistency, even though three of the binaries weren't explicitly listed.

The constraint list says "touch only" what's named, so I should respect that: edit BCC0:9 per the brief and just report the other three as findings rather than modifying them. Making the BCC0 call pass the argument while leaving the declarations as `void(s32)`/K&R stays consistent and safe. Let me commit the SC07 work now that it's green, then move on to sharing the body.
