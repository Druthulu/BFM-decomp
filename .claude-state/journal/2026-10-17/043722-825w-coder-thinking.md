---
ts: 2026-10-17T10:37:22.771Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I'll write a small scratch script that extracts the function section from the dump file, then for each insn/jump_insn/code_label/note splits on top-level markers at line start and prints its uid with a flattened, truncated one-line pattern.
