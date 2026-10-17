---
ts: 2026-10-17T05:51:45.369Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'll start with func_80168828 since it seems to be a single-name case. For each name, I need to check what the pinned register holds before the write—that's the incoming argument. Since callers currently invoke it without arguments, I need to trace the assembly to see what value is actually computed and loaded into that register before the call, so I can convert the signature to take a parameter and update callers to pass it explicitly.

Now I'm searching for callers of func_80168828 in MAIN_012, but grep only turns up the definition—the callers might be going through a function pointer table rather than a direct jal, so I need to check the raw assembly to confirm.

I'll trace each pinned `$aN` back through its `jal` call sites in `asm/` to turn it into an explicit parameter, updating callers by hand (verified with `make check`) and propagating the argument upward when a caller just forwards it. Then I'll rewrite the def through rung D, using `--all-defs` only for byte-identical cases, and handle function-pointer-only names by editing just the def and decls while still matching bytes exactly.
