---
ts: 2026-10-17T09:53:30.466Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6749d345bbfe00cf
model: claude-opus-5-5[1m]
effort: medium
turnId: c3f78c69-d425-4e5c-8c54-1a89f13910d6
---
I'm checking the function boundaries before writing a script to swap in the draft body, making sure I don't duplicate includes, externs, or typedefs that already exist in the file like F3_t and D-prefixed types.

I also realize since 800.c has 7 functions sharing the file, typedefs like F3_t or Src_t could collide between them, so I need to rename these uniquely per function (e.g. prefixed with the function's address) or declare them locally inside the function body. There's also a signature conflict: the existing extern declaration for func_80026514 says `void func_80026514()`, but the draft needs it to return a GT3_t pointer, so I need to resolve that mismatch before swapping the definition in.

Changing void to u8* in the K&R-empty declaration with the call-site cast means caller bytes stay identical, which the gate should confirm. As for the scratch typedefs, I need to keep them file-scope but uniquely named so I don't introduce header types, and I should avoid altering the struct pointer parameter types since that affects MEM_IN_STRUCT codegen.

Duplicate externs with identical types should be fine, with conflicts only surfacing at compile time. I check that `func_8001E378` matches the existing declaration style, and that the asm-label alias declarations for `func_80027058` used by callers don't conflict since they're separate C identifiers from the actual symbol name.

Now I want to look at each 800.c region directly, finding the line ranges from header comment to closing brace for every function in question.
