---
ts: 2026-10-17T16:26:33.149Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm noticing scheduling order within the block stays the same either way. The pin on `ang` to register a0 forces an early hard-register assignment, while without the pin it would only get a0 via the call-arg copy at the end—so I'm wondering if the target version actually had `ang` as a longer computation that naturally needed the a0 load first, rather than a plain pseudo.

I'm also considering that the global being loaded could alias with the stores through the pointer `p`, which would block the scheduler from reordering the load past those stores—so moving the `ang` load earlier in the source wouldn't help, since the scheduler can't push a load below a potentially-aliasing store anyway.

Maybe instead I should try reordering `bx`/`by` earlier before the `p` stores, though that risks putting them in the wrong spot. Or perhaps the fix is simpler: changing `ang`'s declared type to s16/u16 while keeping `bx`/`by` as s32.
