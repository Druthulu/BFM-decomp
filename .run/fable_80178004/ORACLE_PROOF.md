# func_80178004 — oracle proof artifacts (Phase 26, Fable5 session 2026-07-15)

closest.c = best PIN-FREE draft (structural match; residual = register identity only).

The gdb oracle (oracle2.gdb) patches exactly THREE integers mid-compile on closest.c/v05.c:
  at local_alloc:  reg_n_deaths[72] = 2     (72 = the param walker `p`)
  at global_alloc: reg_n_refs[72]  = 4      (true value: 44 — byte-fixed by the 6 store blocks)
                   reg_n_refs[74]  = 15     (74 = uVar6/a2<<16; true value: 11)
With those three values the compile produces the target's ENTIRE first half + callee-saved
assignment byte-exact (s2/s1/s0, constants a3/a0/a1, tags a2, puVar3->a0 with real copy,
giv->addiu a1,a0,0xC). Residual drops 126 -> 78, all in known downstream classes.

Repro:
  .run/fable_80178004/runorc.sh v05        # oracle1 (deaths+refs72)
  # oracle2 adds refs[74]=15; see oracle2.gdb; cmp.py prints the masked diff.
