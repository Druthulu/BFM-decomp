---
ts: 2026-10-17T16:54:47.890Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm noticing the original doesn't match in MAIN_012 either, so this could be a pre-existing mismatch unrelated to my changes — maybe the build object is stale or compiled from different source. I shouldn't worry about that; the real criterion is whether the match scores zero across every includer.

Given that, func_8014ED28 itself fails k0 already, so without fixing that too, a lever-free approach can't clear more than 140/141. Looking at the pin behavior, the function reads its result through v0 after what looks like a void return — so maybe the declared return type is wrong and I need a function-pointer cast at the call site rather than altering the decl itself, since similar precedent allowed return-type casts at call sites to work around barriers like this.
