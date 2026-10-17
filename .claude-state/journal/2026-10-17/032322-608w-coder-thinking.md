---
ts: 2026-10-17T09:23:22.952Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
I'm checking whether SC06_018's SCAN macros contain asm and can be left alone. Now I'm sketching a plan for a scratch expander tool: given a translation unit and a list of asm-bearing macros (plus parents that inherit asm through composition, like CHAIN and LAST for F14C), it would parse out the #define blocks—handling line continuations, names, and parameters—to isolate what needs expanding.

Working through the substitution logic: for statement-level uses, the macro call would be replaced by its indented body lines, with parameters substituted via word-boundary matching while being careful to skip string literals (since some bodies contain inline asm strings like "=r" that could collide with parameter names like `p`). For inline uses like LAUNDER embedded in expressions, the call gets replaced with the body text directly in place, and I need to handle trailing semicolons after statement-macro uses correctly.

I'm deciding to drop the old use-line markers entirely and instead place new `!FAKE:` comments directly on the expanded lever lines that contain inline asm, tagging them as expanded from the per-TU macro so orphan-marker checks don't fail when old comments land on non-lever lines.

For preprocessor identity, the plan is to run cpp on the before/after versions with the right include flags and compare token streams while stripping line markers and whitespace differences.

Let me check the Makefile to see exactly how it invokes cpp for the .c→.o rule and what include paths it's using per-TU.

I'll write a scratch expander that inlines each macro use with parameter substitution and marks lines containing `__asm__`, then verify correctness by diffing cpp token streams before/after and confirming with R22. For F14C, I'll also expand its CHAIN and LAST wrappers, since leaving them wrapped around an inlined `__asm__` would turn them into per-TU asm macros.
