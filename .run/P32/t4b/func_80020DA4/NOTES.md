# func_80020DA4 (main/800, 100 ins) — S83 hand probes
Residual: idx 91 `mflo $t0` vs target `mflo $a2` (+ the dependent sra). Target reuses lo0's dying register for m13.
P1 `lo0 = lo0 * hi2` / `lo0 *= hi2` (reuse the multiplier's variable so combine_regs ties the product to lo0): REGRESSES to
101 ins / 80 mismatched — the whole allocation re-shapes (lo0's live range now covers m13's uses; the prologue loads move).
So the tie is NOT a variable reuse. Remaining hypothesis: local-alloc `qty_phys_sugg`/`combine_regs` on the (set m13 (mult lo0 hi2))
insn requires lo0's qty to be a LOCAL qty dying there; in the draft lo0 (param, `(s16)e0`) may be a GLOBAL allocno (multi-block)
so no suggestion applies. Test next (Fable): make lo0's last use block-local (recompute `lo0` from e0 inside the block that
holds m13, or move m13's statement into lo0's block) and read `-dl` for "Register N … dies in 1 places" + the tie.
