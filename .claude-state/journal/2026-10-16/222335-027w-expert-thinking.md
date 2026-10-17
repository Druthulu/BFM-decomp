---
ts: 2026-10-17T04:23:35.218Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9545e292ce6b8e9d
model: claude-opus-5-5[1m]
effort: medium
turnId: 2945ba12-d858-46e9-8016-11c66319475a
---
Since the asm isn't extracted for matched functions, the coder can disassemble from the build objects directly. I'll define "copy" as bodies matching byte-for-byte via normalized objdump output — if addresses match but bytes differ, that's a distinct function needing no unification. Now I'm sketching the coder briefs, keeping the number small to limit blast radius if something fails.

Since parallel coders would collide on the shared build directory during gate checks, I'll run them sequentially instead: c1 handles the md_SC07_004 pair, cascade, func_8016BF50, and dedup row; c2 handles the lying_exceptions callees and return-type lies; c3 handles the same-address copies. Each commits after its own per-binary checks, with a final full gate pass at the end. I also need to verify the exact flags for rung D's apply mode — I'll have the coder check the help output rather than guessing the syntax. Writing the c1 brief now.

I'll tackle this in three batches: fixing the a0 parameter issue and ANSI prototype, resolving the lying_exceptions callees and return-type lies, and handling same-address copies carefully—excluding addresses that merely share an overlay slot but hold unrelated functions. Each change goes through restruct rung D and the make-clean gate sequentially.
