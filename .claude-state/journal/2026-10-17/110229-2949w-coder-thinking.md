---
ts: 2026-10-17T17:02:29.018Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm checking my notes on how the compiler avoids hoisting loop invariants out of the loop body—specifically that using a goto-based loop structure rather than a for/while construct prevents GCC's loop.c from generating NOTE_INSN_LOOP_BEG markers, which is what triggers invariant hoisting in the first place.

So I'll try rewriting the inner `for (; j < 2; j++)` loop as an explicit goto loop, converting the continue statements into jumps to a "next" label that increments j and loops back. This should keep things like the address loads and other invariants inside the loop body unhoisted, matching the target's structure more closely.
