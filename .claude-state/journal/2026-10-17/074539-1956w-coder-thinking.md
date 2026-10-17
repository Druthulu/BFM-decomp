---
ts: 2026-10-17T13:45:39.149Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm still puzzled by the CSE behavior across this extended basic block, wondering if the two calls happening consecutively matters, or if declaring D_800AF648 differently (as an array versus a plain extern) could change how the symbol reference is treated, though casting the callee pointer types doesn't seem to be the issue.

My next thought is whether GCC 2.7's MIPS backend splits address loads into HIGH/LO_SUM pairs or keeps them as a single `la` pseudo-instruction, since CSE would only be able to reuse the symbol value if a pseudo register actually holds it -- which raises the question of whether expand_call stages arguments through pseudos before moving them into a0, since that would explain why a direct call still gets CSE'd despite a0 being a hard register invalidated by the call. I'm also considering whether the two function calls might actually reference subtly different symbols or struct members that I'm not seeing from the decompiled output.

I'm also wondering whether this comes down to CSE's cost model: on MIPS, `rtx_cost` for a SYMBOL_REF is higher than for a register, so CSE would favor substituting a register once it's seen the value -- but that still requires the pseudo to persist across the intervening call, which brings me back to the extended-basic-block angle: maybe inserting a label (via an empty `if` or `do {} while(0)`) between the calls without emitting any code would change how CSE's follow-jumps logic treats the block boundary.

Now I'm considering loop constructs specifically, since `do { } while(0)` might emit `NOTE_INSN_LOOP_BEG`/`LOOP_END` notes in gcc 2.7's codegen, and if `cse_end_of_basic_block` treats those notes as a block boundary, that could explain why the compiler doesn't carry the symbol's value across -- even though the "loop" itself gets optimized away later by jump optimization since it only runs once.
