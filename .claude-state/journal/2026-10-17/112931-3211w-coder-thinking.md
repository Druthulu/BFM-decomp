---
ts: 2026-10-17T17:29:31.824Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm trying to figure out why the test reads `cnt` from v0 rather than `mode`, since the canonical cse pass seems to promote mode instead. Maybe treating `cnt` as a 16-bit store rather than a plain copy would change the generated instructions to match what's expected, like using a shift sequence instead of a direct move.

Looking at the target disassembly, `mode` ends up in a1 via `andi`, then `cnt` is computed in v0 via `addiu`, and finally `mode` gets reassigned from `cnt` with a move -- so the compiler's register allocator treats mode as the longer-lived value. I want to try testing directly against the stored field instead of the local variable, and experiment with different orderings of the comparison and assignment to see which one reproduces this exact pattern.
