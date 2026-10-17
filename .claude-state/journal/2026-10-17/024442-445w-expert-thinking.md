---
ts: 2026-10-17T08:44:42.808Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I'm working through the SHB macro across its 136 files, distinguishing the 3 volatile occurrences (which just need a rename to ENGINE_SHB) from the 133 non-volatile ones that need a shared definition added to a common prelude header, using an inline asm trick to preserve the value without actual side effects.

I'm also weighing whether removal/laundering sites get re-judged elsewhere, and checking that the two macro definitions stay single shared rows rather than per-TU duplicates, which should satisfy the residue rules. Then I shift to the other macro groups—RTP_SND and the various XFER/DRAW/LAUNDER/COPY variants—starting to map out how many files each touches.

Expanding these multi-line asm macros inline at their call sites would eliminate the per-TU definitions while making each use its own ledgered body-level asm site, which is byte-neutral but hurts readability; moving them into a new shared header instead would really just be hiding the lever rather than resolving it, so I'm leaning toward trying plain-C replacement per use first and only falling back to inline expansion where that fails.

So uses that go cause the def to go if all uses are removed; remaining SHB-family duplicates get consolidated into a shared prelude like the GTE consolidation, while one-off macros get expanded inline at their call sites as ledgered body-level asm. Now I want to check what XFER's 16 multi-line asm uses actually look like before deciding how to expand them.
