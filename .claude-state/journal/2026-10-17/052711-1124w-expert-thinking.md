---
ts: 2026-10-17T11:27:11.928Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: afda95bec87dc8de3
model: claude-opus-5-5[1m]
effort: medium
turnId: 40ed3811-7f18-4ac5-bd2c-b840c396141d
---
Now I have two real cracks confirmed, so I should think about starting propagation for them. The question is whether propagation work would collide with the crack coders' activity — but since those coders only operate in isolated scratch directories and don't touch source or the live build, propagation should be safe to proceed in parallel.

I'll move forward with propagating 80178970 (plus its variant) and 8013F350 (which also has a MAIN_012 variant worth porting), while leaving 80177B5C pending for now. The propagation process involves applying a body patch to an exemplar translation unit with clean source and current calibration, then running the propagate step across the rest.

Then I need to run the census check in strict mode, writing residue entries for remaining failures while preserving matched residue rows as-is, which rewrites the TSV before running R22 and committing. I'm noting that one exemplar's win.c references an SC04_011 global, and the 8013F350 exemplar is a bare definition, so both should work fine for the body-apply step — I'll flag the exemplar TU paths and let the coder sort out whether the SC04_011 copies belong in the residue set, plus clarify how cleared rows and uncracked attempts get handled before briefing the propagator.
