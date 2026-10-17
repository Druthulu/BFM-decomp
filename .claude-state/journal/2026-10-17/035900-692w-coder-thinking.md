---
ts: 2026-10-17T09:59:00.082Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6749d345bbfe00cf
model: claude-opus-5-5[1m]
effort: medium
turnId: c3f78c69-d425-4e5c-8c54-1a89f13910d6
---
I'm realizing the macro form changes how the compiler generates code: casting to a pointer lets gcc CSE the base address into a register, whereas treating it as an array symbol uses direct %hi/%lo addressing with an index. This means I need to actually change the extern declaration from a plain scalar to a proper array type to match the expected codegen.

Declaring it as `extern Spark_t D_801A6B40[];` should keep `(s32)&D_801A6B40` and pointer-offset arithmetic working identically to the scalar version, since taking the address of an array yields the same symbol address. But I should double-check every usage across the file to make sure nothing treats it as a plain scalar assignment, since that would break with an array type.
