---
ts: 2026-10-17T11:39:28.806Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm trying to figure out the real reason laundering the base address matters here—thinking about whether gcc 2.7 on MIPS keeps a loaded address register alive across multiple uses for CSE purposes, since the slot computation and the u16 loads both depend on that same constant base.

I'm testing whether the base pointer could arise from something gcc can't fold immediately, like loop-invariant code, a static struct cast, or a register preserved across function calls, but each alternative still ends up looking like a pure constant symbol+offset that gcc would normally fold cleanly.

Thinking further about cse.c's internals, I wonder if find_best_addr considers a register holding the base symbol equivalent to the constant address, weighing the address cost tradeoffs between `(const (plus sym off))` and `(plus reg const)` on MIPS, which could explain why the compiler might choose to keep the base in a register rather than fully folding it.

I'm trying a few alternate declarations for base—maybe an extern array indexed with a negative offset, or a cast through u32 pointer arithmetic—to see which one makes the compiler fold the address the same way as the target assembly.

That reminds me how gcc 2.7 on MIPS keeps a symbolic address live in a register when it's reused as a value in arithmetic rather than purely folded into a memory operand, which matches how `base` gets combined with the -0x34 offset here.

Maybe it's just that the register isn't live there and cse prefers the canonical form regardless. Given my budget, I'll just try a few quick variations empirically rather than keep theorizing.
