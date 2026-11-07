---
ts: 2026-11-06T06:04:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FxKqOLZ37Hd7GlhpQZgq
---
The cross-jump is in jump.c's jump_optimize, run as the "jump" or "jump2" pass. The `-dj`/`-dJ` dumps may not print a message for cross-jump (it's silent). So the evidence is the diff + the jump.c mechanism.

Note: `do_cross_jump` handles `GET_CODE(PATTERN(insn)) == RETURN`: it replaces a RETURN insn with a jump to the label before newlpos. In MIPS, the epilogue is a `return` pattern (`jr ra`); the two `return 0` blocks... Hmm, actually the merged blocks are the `j epilogue` jumps, not returns.

Anyway, the mechanism is cross-jumping in jump.c (jump_optimize), which is the pass behind the `jump2-crossjump-arms` tag. Good enough evidence with the source reference.

Let me now clean the item5 dump dir and update the notes.

Also, I should double check the wall tag: `jump2-crossjump-arms` is in walls.txt with "cross-jump merges byte-identical switch/if arms (incl. j+delay store); renaming the regs gives no plain-C split (T11 G18 func_8017D508)". Our case: byte-identical `return 0` blocks (j+delay move). Matches.

Let me update item5 notes and remove the dump.
