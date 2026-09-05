# func_800CD92C (md_MAIN_009, 247 ins) — S83 hand probes (residual 15: the {sw,lui,ori} tpage groups for $s2/$s3 must come
BEFORE the li block; the draft emits them after)
V1/V2/V3 birth the pinned tp8D/tp8F constants at the top / after m24 / after p: NO CHANGE (15 all) — with hard-reg pins the
RTL position of the constant set does not decide the sched2 order; the target's order = the constant loads INTO the just-saved
callee-saved registers scheduled right after their `sw` saves. Hypothesis for the Fable pass: the tpage values in the target are
NOT pinned hard registers but ordinary pseudos that global-alloc put in $s2/$s3 — the save/def adjacency then comes from the
prologue's own ordering (prologue_epilogue + sched2 anti-dependence sw→lui), while pinned hard regs are treated differently by
sched2 (no pseudo priority). Test: unpin tp8D/tp8F (§17: pins reproduce the allocation but the hoist happens in sched2 — the
S82 report) and steer their allocation by birth order/refs instead.
