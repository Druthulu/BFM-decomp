# func_8017DC80 (ov_SC07_002, 346 ins) — S83 pointer (residual 46: frame 0x60 vs 0x70 = TWO reload spill slots the target
has and the draft lacks, then the whole prologue/constant order shifts)
Prior: .run/P32/t3/reports/func_8017DC80__opus__*.md; §500-C/D-2 (GTE macros, /s lattice, pinned derived pointers, cse1
across func_80010A08(8), the `#line`-equalised ASM_OPERANDS). The target's first insns after the frame are `lui/addiu $a0 =
D_800AF648` then `sw $s4` — an argument address materialised BEFORE the callee-saved saves are complete → a call (`func_…(&D_800AF648)`)
is the first statement and its arg set-up is scheduled into the prologue. +16 frame bytes = two 8-byte alter_reg pseudo slots
(§172 producer 1): two values spilled in the target (the "reload-slot frame") — find which two pseudos the target keeps in
memory (their `lw`/`sw` at 0x10..0x1F) and give them the live ranges that force reload to spill them (long ranges crossing the
GTE blocks with all $s regs taken), rather than pinning them to registers.
