# func_80185810 (ov_SC03_105, 489 ins) — S83 pointer (residual 35: [permuter] 4 emission windows; rows 343–347 = the
D_800A... `lui/addu/lhu` address group emitted AFTER two `lhu` field loads where the target emits it BEFORE; 363 `sh` vs `srl`)
Prior: .run/P32/t3/reports/func_80185810__opus__*.md; §500-C. Class: sched1 order of independent loads within a window —
the target's group order = RTL order (LUID tie-break) → the address computation `s4 + 0x10000 - 0x5C2E` must be BORN before the
two struct loads in the source (a named pointer/temp for the absolute-address lhu declared and assigned before the `s2` field
reads). Each of the 4 windows is the same class: read the window, find which independent insn the target orders first, give it
an earlier birth in the source (§47/§500-G birth lever) or a data dependence.
