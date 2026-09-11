# func_801860B8 (ov_SC02_027_jr_8017D898.c) — d14, P36 S104 — CLOSED at 0, plain C, zero levers

Start: body_free.c 15 (MIXED), the regen sweep's best free_136.c 4 (ORDER). Final: `PACK/body.c` = **0** (76/76 ins,
byte-identical), no pin, no asm, no added volatile, no do-while, no dead initialiser (`__builtin_abs` was already in
body_free). Levers 3 -> 0.
The same text (with the per-overlay `D_` renames) closes the class's other two copies at 0:
- `src/ov_SC02_026/ov_SC02_026_jr_8017C180.c` func_8017EA88 (D_801D0148/D_801D014C) -> `scratch/copy_ov_SC02_026_func_8017EA88.c`
- `src/ov_SC02_028/ov_SC02_028_jr_80184BD8.c` func_80186A9C (D_801D3378/D_801D337C) -> `scratch/copy_ov_SC02_028_func_80186A9C.c`

## (a) The residual in one sentence
Equal count; in the tail block local-alloc tied `d = abs(v)` into `v`'s quantity (with cur and cur-prev), so abssi2
took its dest==src arm (`bgez; nop; negu v0,v0`) where the target has the MOVE arm (`bgez v1; move v0,v1; negu v0,v0`),
and every register of the block shifted (prev $v1 not $a1, e2 $v1 not $a0, flags $v1 not $v0).

## (b) Pass and decision (read in tools/reference/gcc-2.7.2/)
- local-alloc.c:1722 `combine_regs`, the tie at :1846-1851: it ties a SET register to a USED register that DIES in the
  insn — but returns 0 at :1845 when `reg_qty[sreg] >= -1`, i.e. when the destination is not a block-local, die-once
  pseudo. body_free's d is local and v dies at the abs: tied (mips.md:1526-1545 then picks the `nop` template).
- global.c:904 `find_reg` + the `.greg` order: a GLOBAL d is not tied by local-alloc; it is allocated by priority
  (`allocno_compare`, global.c:604) and lands on the lowest free register not in its conflicts (pass 0 only reuses
  registers already used, :955-960).
- The target's own objdump says which variables the author REUSED: the tail's three "wrong" values sit in the same
  hard registers as three EARLY-half values — D_80126CE0/the target `a` in $a1 (prev is $a1), the early
  D_801DA778 read in $a0 (e2 is $a0), `diff` in $v0 (|v| is $v0).

Proven on bytes and in the dumps (`scratch/dumps_FIN/`, `tools/alloc_table.py FIN`): the abs insn is
`(set (reg 76) (abs (reg 78)))` with reg 76 = `diff`, "dies in 3 places", a global allocno — local-alloc cannot tie it.
`.greg` order `76 122 81 75 113 74 79 73 82`: diff (r76, pri 30000) is allocated first -> $v0; cur (r75, conflicts
v0,v1) -> $a0; a (r74, conflicts v0,v1,a0) -> $a1 — exactly the target.

## (c) The moves (all three needed: dropping move 1 / 2 / 3 from body.c scores 3 / 12 / 10 — scratch/no{1,2,3}.c)
1. `prev` -> reuse `a` (`a = D_801DA77C; v = D_801DA778 - a + spd;`): prev joins a's global allocno ($a1).
2. name the early read `cur = D_801DA778; diff = cur - a;` and reuse `cur` for the second `*(s32 *)(arg0 + 0x20)` load
   (the old e2): e2 joins that allocno ($a0).
3. `d` -> reuse `diff` (`diff = __builtin_abs(v); ... = diff;`): the abs destination is a multi-death global, the
   local tie is refused (local-alloc.c:1845) and global gives it $v0 -> the move form of abssi2.
Byte ledger: 1 alone 15->13 (vE); d+flags sharing one variable (another way to make d non-local) 15->10 (vA);
1+prev/e2 sharing+d/flags sharing 3 (gen0/c0098, e2 dragged to $a1 by prev's conflicts); the full 1+2+3 = 0 (gx/c0160,
then body.c). An equivalent 0: flags and d share one `u16` variable instead of 3 (gx/c0162). The early block's
`D_801DA778 -= diff >> 2` spelling stays (0 either way).

## (d) GENERATOR PROPOSAL
When a register residual sits in a LATE block and the target's objdump shows a late value in the same hard register as
an EARLY value of a different variable, enumerate REUSES: rename each late local to an earlier-dead variable (or to
another late local) whenever their live intervals do not overlap — a set partition over the statement intervals, each
group optionally joined to an early variable (a/diff/a named early global read) — and score all of them. Here 114
partitions x {none, early-join} = 365 bodies (`scratch/genx.py`) found 4 zeros in ~3 minutes at -P6. This is S103 c18's
MERGE applied ACROSS statement groups with the early half, which no R2-R26 family generates (R23 only splits).
Probe of the sibling CLASS func_8012E364 (ov_SC03_099, 134 bodies at two marked pins since S103 c51; read-only
`--try`, `scratch/gen364*.py`, 775 bodies): best 3 lever-free (`scratch/e364/c0009.c`: flags+d share a u16, prev+e2
share a variable; only e2 is $a1 instead of $a0) — its early half keeps different registers ($a0 = `a`), so the
enumeration needs that function's own early-register map; not closed, left for its owner.
Special case worth its own rule: an abssi2 `nop` arm (dest==src) against a target `move` arm = the abs destination
must be non-local — reuse an earlier variable for it.

## (e) What did not work (byte evidence)
- all-struct typing of arg0 / arg0->0x20 (vS1-3, body-local typedefs): the D_801DA778 store floats
  (sched.c:869 output_dependence, MEM_IN_STRUCT_P vs scalar) but the tie stays and the 0x5C store / 0x70 load order
  flips: 21.
- hand-rolled abs in 5 spellings (vT1-5): all identical to `__builtin_abs` (15); the branch form keeps the tie through
  global.c's copy preference, and cse (cse.c:826-862 make_regs_eqv) re-canonicalises the test or the negation onto one
  register, so `test v / negu d,d` cannot be spelled as a branch (vW1: `negu v1,a1`, 20; vB1 s16 copy: 12).
- a global d whose other life does not conflict with v's register (d reused for tail+0x1000, vB): global.c's
  preference puts it back on $v1 (nop form), 11.
- joining late roles to early variables at random (gen1, 252 of 3176 scored): 29-44 when the join moves the early
  allocation; the joins that work are exactly those whose early register is the target's late register.

## (f) Where the method fell short
- METHOD step 3 lists the S103 c18 MERGE only for "the same role across blocks"; the close needed merging DIFFERENT
  roles whose registers coincide, read off the objdump per register across the whole function — the hunk view hides it.
- `tools/localalloc_sim.py`/lsim3 and `alloc_table.py` were accurate but only explain a candidate; the decisive step
  was an exhaustive reuse enumeration (cheap: 365 compiles). A tool that proposes reuses from "same hard register in
  target, non-overlapping lives" would have found it directly.

## (g) Structs answer
No. The lever was a register-allocation tie (local-alloc.c:1846 combine_regs + the global order), not a memory
dependence; struct field accesses change only MEM_IN_STRUCT_P (expr.c:4568-4577) and so sched/cse memory ordering.
Tested on bytes with body-local `Ent`/`Sub` typedefs (vS1-3): the scalar D_801DA778 store floats as predicted but the
tie is untouched, and the first block's 0x5C/0x70 pair reorders (the two struct accesses now conflict): 21. The
missing piece here was the original's TEMPORARY REUSE, not its types.
