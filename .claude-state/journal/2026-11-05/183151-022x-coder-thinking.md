---
ts: 2026-11-06T01:31:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GRw5jdZ0Pb6zx1IBIWRl
---
Ah I misread: mine's dec at 17bc: lw; j 1800; addiu v0,-1; and 1800 is the *shared store* `sw v0,28(s0)`. Then falls to 1804 epilogue. So cross-jump moved dec's store into the shared location at end of zero block, and zero's own store also targets 1800. Wait but zero's block at 17f8 li v0,29; 17fc sh zero,244; 1800 sw v0,28 — so zero's store is at 1800, and dec jumps to 1800 too. But then dec's delay slot `addiu v0,v0,-1` executes before the j? No: in MIPS, `j 1800` at 17c0, delay slot 17c4 addiu executes, then jumps to 1800 sw. So v0 = unk1C-1 stored. Correct. Zero's path falls through li 29; sh; sw. Both use the same sw instruction. That's correct and -2 instructions (dec lost its own sw, gained a j; and nop delay slot? Actually dec previously: lw; nop; addiu; j 180c; sw — 5 ins. Now: lw; j 1800; addiu — 3 ins? Hmm the store now shared. Saves 2.)

Target wants dec's own `j 180c; sw` and zero's own fallthrough sw. So target: zero 17f8 li; 17fc sh; 1800 sw (fall to epilogue 180c); dec 17bc lw; nop; addiu; j 180c; sw. So in target both stores exist separately (1808 and 17cc). Yes, target has sw at 1808 (zero) and 17cc (dec delay slot).

So to prevent cross-jump, the store insns must not be identical. But both must be `sw v0,28(s0)`... unless the target's two stores are actually *different* in a way objdump doesn't show (e.g., one has a reloc? no).

Wait — maybe the difference is in the *preceding* insn matching? find_cross_jump compares blocks and might match 2+ insns; it needs a minimum of 1. Hmm.

Hold on: maybe the trick is that in zero, the store isn't the last insn of the block in RTL order. The last insn might be `sh zero,244` and `sw v0,28` earlier? No, target order is li, sh, sw.

Alternatively — maybe cross-jump only merges when the two blocks' tails are equal AND the jump is a "conditional/unconditional" relation. There might be a way to make zero's block a different "kind" by adding a use of a value... 

Let me look at how other coders cracked barrier items. Search moves.md for "barrier" MATCH or "cross-jump".
