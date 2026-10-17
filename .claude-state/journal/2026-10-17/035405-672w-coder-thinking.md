---
ts: 2026-10-17T09:54:05.849Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6749d345bbfe00cf
model: claude-opus-5-5[1m]
effort: medium
turnId: c3f78c69-d425-4e5c-8c54-1a89f13910d6
---
I'm checking whether other declarations of these functions elsewhere in 800.c or other files could conflict—since those are separate translation units, there shouldn't be an issue. The asm-label extern alias in the caller seems fine to leave as is, though I want to verify how gcc handles defining the function within the same unit.

Next, I'm checking whether gte_inline.h is already included in 800.c and whether the needed GTE macros and MATRIX/SVECTOR types are available via common.h. Then I'm laying out a plan for each function: func_8001E378 just needs a body swap since the signature matches; func_800249F0 and func_80025CBC need their internal typedefs renamed with unique suffixes to avoid collisions; and func_80026514 is trickier since its forward declaration returns void but the real definition returns a pointer type, so I'll need to update the extern declaration to match while keeping the caller's cast compatible.

I'm also working through func_800268D0, func_80027058, and func_80027200 similarly, checking whether each has an existing forward declaration that needs its return type updated to match the new definitions, and I plan to grep for all these declarations to confirm.

I'll update each conflicting K&R-empty extern to match the draft's return type, since callers already use casts so call bytes won't shift. Next I'll check other declarations of the 800.c targets and whether gte_inline.h is included.
