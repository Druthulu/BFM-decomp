---
ts: 2026-11-06T21:03:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5T3LL8i4PzEZ7bRBKJHA
---
Now clear: block 1 pseudos: 78 and 79 both got hard reg 2 (v0)! But the assembly shows $3 for addu. Wait... "Register 78 in 2", "Register 79 in 2". Hmm. Then the .s should have $2 for both. Unless the .s was produced with a different compilation.

Hold on: `cc1_dumps_tu.sh` compiles with `-dr -ds ...` and `-o $tag.s`. The .s is the final output. If both 78 and 79 are in $2, the addu would be `addu $2,$2,-256`.

But the .s shows `addu $3,$2,-256`. So the .lreg dump and .s disagree?! That can't be. Unless the .lreg dump is from local-alloc's *input* (before assignment) and "Register 78 in 2" is from a *different* function section... no, it's within our section.

Wait, maybe -dl dumps AFTER local-alloc, and the register assignments shown are correct, but then a later pass (global alloc? no, global runs before local) ... hmm. Actually order: greg (global alloc) → lreg (local alloc) → ... → sched2 → asm. Hmm, but reload could change things: reload (insn 143+) may spill and reassign? Reload doesn't renumber registers generally but can insert moves using different regs. Also, `-O2` with `-mips1`: no delayed-branch scheduling? The .s we saw used macros (.set nomacro) with $2/$3.

Wait, actually maybe the .s is from the *dump* compile (with -dr etc. flags) while the .lreg is also from that same compile. Same compile, so consistent. Something's off.

Let me look at the .s again around the 0x58 block... It showed:
```
lhu $2,88($16)
#nop
addu $3,$2,-256
sll $2,$3,16
```
Hmm. And .lreg says reg 78 in 2, reg 79 in 2.

Maybe reg 78 = the sll result? Let's see: block 1 insns 26..36. Let me print them.
