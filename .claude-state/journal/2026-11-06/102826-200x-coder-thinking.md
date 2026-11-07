---
ts: 2026-11-06T17:28:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RxKfB0wfO4XSCT3lXhCL
---
Big function with 172 registers. The sh16 pseudo: let me find it in the lreg dump (search for the insn computing `sll` with the angle or the >>31). Actually easier: find the block containing the sh16 code and see which regs are assigned.

Let me find the sh16 pseudo by searching for `ashift` with the angle... Or find the pseudo whose defs are in two blocks and used once.

Alternatively, let me look at the final asm from the dump (nd.s) around the sh16 code and map registers.

Actually the residual is known: sh16 v1 (mine) vs v0 (target). In the target's build (pinned), sh16=$2.

What if I look at which pseudo number sh16 is and its priority? In the flow dump, find the variable... The source's sh16 is a local variable declared at the top; its pseudo is created at the first reference (in the if). Let me search the flow dump for the shift insns: `(ashift:SI ... (const_int 16))`.

Let me grep the flow dump for "const_int 16" near the sh16 block.
