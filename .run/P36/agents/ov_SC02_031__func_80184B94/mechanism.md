# func_80184B94 (ov_SC02_031) — P36 S104 d27 — score 0, zero levers

## (a) The residual
Score 6, COUNT: after `jal func_800132BC` mine emits `lw v1,D_801274D8; move a0,v0; slt v1,v1,v0` (the move fills the
load slot, reorg forwards the copy's source into the slt) and keeps the result in `a1` with a final `move v0,a1`;
the target emits `move a0,v0; lw v1; nop; slt v1,v1,a0`, `move v0,zero` in the beqz slot and the result straight in
`v0`. Same instruction count, different order + one register.

## (b) The pass and decision (read in the source, confirmed in the dumps of scratch/md/)
- body_free: `uVar2 = 0` is a PSEUDO (74) set in the call's block. sched1 (`.sched`, block 5) hoists it and the
  load `D_801274D8` (latency 2, queued, "launching 65 before 62 with no stalls") above the call-result copy
  `(set 73 (reg 2))`; 74 is then set while `$v0` still holds the call value, conflicts with reg 2 (`.greg`:
  "74 conflicts: 73 74 2 3") and global.c gives it `a1` → the extra `move v0,a1`. With the copy directly before the
  slt, reorg.c:3480-3493 rewrites the slt to read `$v0` (validate_replace_rtx) and the copy fills the load slot.
- the target: both returns are CONSTANTS, so jump1 turns `if (!(D<i)) goto L; if (!(i<D2)) goto L; v0=1; ... L: v0=0`
  into `v0 = 0; if (D<i) v0 = (i<D2)` — the store-flag case (1) at jump.c:1140-1210 and the `x = b; if (...) x = a`
  hoist at jump.c:700-760 (x may be the hard reg `$v0`: no SMALL_REGISTER_CLASSES on MIPS). The hoisted insn writes
  HARD `$v0` in the call's block; the call-result copy reads `$v0`, so sched.c's anti-dependence keeps the `$v0 = 0`
  after the copy. At T-3 only `$v0 = 0` is ready; at T-4 both the copy and the load are ready and the load is placed
  nearer its use → order copy, load, (stall), slt — the target's `move a0,v0; lw; nop; slt`. No result pseudo exists
  any more, so nothing conflicts with `$v0` and the final move disappears.
- Proven on bytes: all of the above is read off `.jump`/`.sched`/`.greg`/`.dbr` of scratch/md (mini TU, which
  reproduces the real TU's residual exactly) and confirmed by `--try` = 0.

## (c) The move that closed it
Delete the result local `uVar2` (and its `= 0` initialiser) and write the tail as one condition returning
constants: `if (D_801274D8 < iVar1 && iVar1 < D_801274DC) { return 1; } return 0;`. The nested-if spelling
(`if (iVar1 > D) { if (iVar1 < D2) return 1; } return 0;`) also scores 0.

## (d) GENERATOR PROPOSAL
When a `$2`-pinned (or any) result local is initialised to 0 and conditionally assigned a comparison
(`r = 0; if (A) r = (B); return r;`, or `if (A) return B; return 0;`), rewrite it as `if (A && B) return 1; return 0;`
— constant returns let jump1's store-flag + hoist put a HARD-`$v0` set in the block, whose anti-dependence on the
call-result copy fixes sched1's order (jump.c:700-760, 1140-1210).

## (e) What did not work (byte evidence, `--try`)
- `if (D<i) uVar2 = (i<D2); else uVar2 = 0;` → 5 (register swap v0/a0 remains; the `else` constant is re-hoisted into
  the pseudo, jump.c:739).
- `if (D >= i) uVar2 = 0; else uVar2 = (i<D2);` → 5; `if (D<i) return i<D2; return 0;` → 5; `(u32)` cast on the call,
  a second copy through `uVar2` → 5. For `if (D<i) return i<D2; return 0;` the `.sched2` dump shows `$v0 = 0` left in
  the block AFTER the branch (the `x = a` arm is an slt with its own load, so jump.c:736-745 finds no condjump directly
  before it) and the load again hoisted over the copy (lw; move; slt reading v0). The other three show the same bytes;
  their dumps were not read (hypothesis: the same reason).
- `return D < i && i < D2;` (a value, not constants) → 6.
- The regen sweep's best (6) files were semantically broken (`return (0)`, an emptied if) — not usable starts.

## (f) Where the method fell short
The residual printed as a register pair (v0->a0, a1->v0) and the sweep (R2–R34) only mutates declarations and
statements in place; the defect was a SCHEDULING order decided by a hard-register anti-dependence that exists only
when the returns are constants — no generator rewrites "flag variable + return flag" into "return constants". The
S104 step-14 pattern (structured rewrite of the control flow) was the right family; this is its value-return cousin.
Also: `delever_search --try` cannot try a function defined in an `#include`d shared header (func_8013E448); I used a
mini-TU harness with a pinned-header control (scratch/copies.md).

## (g) Structs answer
No. The lever here is a `$2` pin faking the ordering constraint that a hard-register `$v0 = 0` imposes in sched1; it
is decided by the return statements' shape (constants vs a pseudo), not by memory accesses. Typing `param_1` as an
actor struct with a `u16` field at +6 changes only the first block's `lhu` addressing (already matching) and no
aggregate-vs-scalar dependence in sched.c/cse.c touches the call-result copy. Not tested on bytes (no memory access
is involved in the residual).

## Copies (scratch/copies.md)
func_8017F644 (ov_SC04_005), func_8017E9E8 (ov_SC05_009), func_8017F080 (ov_SC04_007, 2 pins) all `--try` 0 with
the same tail; func_8013E448 (src/shared/ov/func_8013E448.h, 136 TUs, 1 pin) compiles byte-equal to the pinned header
in a mini-TU control — needs the whole-object gate.
