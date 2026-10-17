---
ts: 2026-10-17T11:04:38.103Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
The tree matches with base 491. I'm now tracing through the disassembly, examining the register setup loading the address of D_8011511C, saving return address and saved registers, and reading a halfword value before masking and branching on it.

The key question is why gcc 2.7.2 keeps the symbol address in a register rather than using the standard lui/lo macro expansion inline -- this suggests the address gets reused across multiple stores, so cse holds it in a pseudo register instead of re-expanding the lui/addiu each time.

Register addresses cost less than symbol addresses (1 vs 2), so find_best_addr should favor keeping a register base unless constant propagation already folded it earlier. This suggests the original source likely had the pointer computed via loop-invariant hoisting into a register, or a local pointer copy derived from a non-constant source.

I'm now comparing the prologue instruction ordering between my version and the target: mine has extra setup before the stack pointer adjustment, while the target interleaves the lui/addiu address computation with the register saves. Tracing through which instructions align shows the stack pointer adjustment maps to a later instruction in my sequence, with the save instructions needing to be reordered to match.

I'm also considering other scenarios in gcc 2.7.2 where a pointer to a global stays in a register rather than being folded by cse — maybe if the address comes from an indexed array access, is passed as a call argument, is loaded indirectly through another pointer, or appears inside a loop context, though none of these seem to match this particular case.

Digging into cse.c's find_best_addr logic, where it decides whether to substitute an address with an equivalent register versus leaving it as a constant symbol-plus-offset expression.

I'm trying to recall whether the comparison requires the constant's address cost to be strictly less than the register's, questioning if it's actually a less-or-equal check, and tracing where in `fold_rtx` the constant substitution for a MEM operand with a known-constant register actually happens.

So find_best_addr does fold, confirming earlier notes. Now I'm thinking about what original C pattern would produce that lui/addiu base register—likely an array access where the index isn't known as constant until after cse runs, so the base address computation survives into later passes rather than being folded away.

Another possibility is that the pointer assignment happens before a code label with multiple predecessors—cse resets constant equivalences at labels since gcc 2.7.2 lacks gcse, so the address wouldn't be recognized as constant past that join point and would remain in a register.

If pd only has one use, combine could still substitute the constant, but with multiple uses that elimination path is blocked. I'm also considering whether local-alloc's update_equiv_regs step, which handles registers set once with a REG_EQUAL note, might instead be responsible for creating a REG_EQUIV and replacing uses with the constant directly.

So I need a code label sitting between the assignment and its uses with no instructions in between — maybe a goto that jump passes eliminates, leaving a label with a single incoming edge and no inserted code.

But jump optimization would normally delete unused labels before cse1 runs, so a plain goto wouldn't survive. A loop header label (like from a for/while) could work instead, since loop notes keep structural labels alive, though the target's first block doesn't look like a loop itself. Maybe pd's uses are confined entirely to that head block, or there's some other construct where the lui/addiu for a1 is scheduled as the very first instruction in the prologue.

I wonder if making the base address non-constant could dodge cse, but cse folds constant arithmetic anyway, and there's no function call to produce a non-constant pointer. Perhaps pd is actually indexing into something else, or this pattern recurs in a sibling function that I could check against for clues.

I should check the cookbook entries C0505, C0119, C0087, C0287, and C0278 since those likely contain the expert's suggestions relevant to this.
