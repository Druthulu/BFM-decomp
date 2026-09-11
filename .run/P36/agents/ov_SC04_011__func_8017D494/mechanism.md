# func_8017D494 (ov_SC04_011_jr_8017D494.c) — T7 agent c37 — IN PROGRESS

## (a) The residual
Lever-free: score 10 (REG-caller, 952 = 952): `&g.sz1` (sp+208) and `&g.sz2` (sp+212), both hoisted into the outer loop's
preheader, get t8/t9 swapped (target: sz1 → t9, sz2 → t8). Same instruction count, same order; pure allocation.

## (b) The pass and the decision
global.c `allocno_compare` (`global.c:590-610`): `pri = (int)(floor_log2(refs)*refs/live_length * 10000)`; ties broken by
allocno number. `.greg`/`alloc_table.py` on the lever-free body: r229 (&g.sz1) refs 13 live 783 → 498; r231 (&g.sz2) refs 13
live 782 → 498 (int) → TIE → lower allocno (229) first → t8. The target allocates 231 first. Live lengths are sched1's
recount (`sched.c:3846-3861`, written back `sched.c:4946-4947`): every insn of the outer loop counts once for each of the
three hoisted addresses (227/229/231 defined back to back in the preheader, so L227 = L229+1 = L231+2).
Arithmetic: the tie splits the right way iff the loop body's sched1 insn count changes by **+1** (227/229/231 → 496/497/498)
or **−2** (498/499/500); 0, −1 (227 ties 229 → 227 first), +2 (227 ties 229) all lose.
The tree's `__asm__ volatile("")` lever is exactly the +1: an ASM_INPUT insn that emits nothing.

(work continues — see below)
