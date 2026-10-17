---
ts: 2026-10-17T09:52:31.698Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6749d345bbfe00cf
model: claude-opus-5-5[1m]
turnId: c3f78c69-d425-4e5c-8c54-1a89f13910d6
---
The change replaces 12 verbatim `__asm__` bodies (each with its `// !FAKE:` marker) with the C drafts that already matched. Callers' declarations stay byte-identical: the K&R-empty prototypes and the 6-arg cast at md_MAIN_027.c:502 stay, and the drafts adapt to them. func_80184440 is the exception: it moves only if a carve puts it in the `_o0` region at -O0. Otherwise it keeps its asm and I report the evidence.
