# func_801834A4 (ov_SC03_105, 106 ins) — S83 hand analysis (residual 6, idx 82–89)
Target hoists ONLY the division's sign correction `sra $s5,$s4,31` (idx 36, into a callee-saved reg, reused at idx 90
`subu $v1,$t0,$s5`) and keeps const+mult+mfhi+subu inline; the draft's `half / 3` leaves the sra inline too. The S71 header
proves (loop.c movable thresholds) that from `half / 3` the const hoists whenever the sra does, and that the hand-expanded
high multiply `(s32)(((s64)half * 0x55555556) >> 32) - sign` keeps the const inline but pays +2 (mulsidi3 splits into a
register pair; the dead `mflo` survives combine) → 27. Untested: a spelling that yields `smulsi3_highpart` directly WITHOUT a
division — in gcc-2.7.2 only expand_divmod emits it; so the alternative is to make the DIVISION's sign correction come from
a separately-hoistable expression while the const/mult stay inline: e.g. divide a value the compiler cannot prove invariant
(`half` laundered per iteration: `__asm__("" : "=r"(h) : "0"(half))`) so const+mult+sra+subu all stay inline, then the
inline sra (idx 82) matches ONLY if the target's hoisted `$s5` is not the division's sra but the draft's own `sign` variable
kept live in $s5 (the target may be `pos[0] -= q - sign_var` with `q = h / 3` UNSIGNED-corrected...). Fable: diff the target's
idx 80–92 RTL-by-RTL against `expand_divmod`'s emitted sequence to see which insn the `subu $v1,$t0,$s5` is.
