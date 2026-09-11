# func_8017F768 — e9 (P36 T7 S104) — score 13 (sweep best 13) -> 0, ZERO levers (was: 2 NEEDED pins `$17`, `$4`)

(a) Residual: COUNT-class 13, two defects. (1) The ratan2 angle: target `andi a0,v0,0xfff; move s1,a0` and the
`func_801898A4` call reads the live `a0`; lever-free `andi s2,v0,0xfff` and `move a0,s2` at the call (the angle and
the heading variable merged into one pseudo). (2) The heading (`0x800` / angle) and the distance swap `$s1`/`$s2`, and
`li s1,2048` sits in the `beqz` delay slot in the target but is hoisted above `jal func_80013294` in mine.

(b) Pass/decision (dump-verified: `scratch/dumps_base`, `dumps_w1`, `dumps_x2`, `dumps_z4`; `tools/alloc_table.py`):
  1. cse, `make_regs_eqv` (cse.c:826-862) + the `(set REG0 REG1)` swap (cse.c:7440-7474): with `s32 s1; … s1 = angle;`
     the copy is a same-mode REG copy, the longer-lived `s1` becomes the class head, the andi is rewritten to set `s1`
     directly (`.cse` insn 147 `(set r74 (and r115 4095))`) and the call argument reads `s1` -> `move a0,s1`.
     Declared `s16`, the copy is a truncation into a HImode pseudo (a SUBREG move, not a REG-REG copy of the same mode),
     so cse makes no equivalence the SImode call argument can be canonicalised to: `angle` stays its own pseudo
     (z4 table: r75 refs 3 live 13 "prefers a0"), global gives it `a0` and the copy stays -> the target's
     `andi a0; move s1,a0`. (w1 alone: 13 -> 10.)
  2. sched1 hoists `s1 = 0x800` (set before the `if`) above `jal func_80013294` (`.sched` insn 88 above call_insn 81),
     which lengthens the heading's live range: `allocno_compare` (global.c:594-610) then ranks it BELOW the distance
     (w1: heading r74 4 refs / live 55 = 1454.5 < distance 3/20 = 1500 -> distance takes `$s1`). Set inside the first arm
     instead, it cannot move above the branch; its live length drops to 47 (z4: 1702.1 > 1500 -> heading `$s1`,
     distance `$s2`) and reorg fills the `beqz` delay slot with it from the fall-through thread — the target's
     `beqz …; li s1,2048`.

(c) Moves (joint — each alone fails: s16 width only = 10, 0x800-in-arm with s32 = 5):
  - the heading local `s32 s1` -> `s16 dir` (it is only ever stored to an `s16` global and passed on);
  - `s1 = 0x800;` moved from before the `if` into the `dist < 0x200` arm (the arm that keeps the default heading).
  Byte-neutral readability (all at 0): `s0 = a0` param copy deleted (d24), `dist` declared `s16` (the `(s16)` cast on the
  call result dropped), `D_801274EA = dir;` without the redundant cast, `s1/s2` renamed `dir/dist`.

(d) GENERATOR PROPOSAL: when a variable is initialised to a constant BEFORE an if/else and reassigned in one arm only
(`v = K; if (c) {…} else {… v = x; …}`) and the residual has a callee-saved swap or the constant's `li` in the wrong
place, move `v = K;` into the other arm (it stops sched1 hoisting it across a call and shortens its live length); and
when a copy `v = t;` merges `t` into `v` (a `move aN,<v's reg>` at a call that reads `t`), narrow `v` to the width of
its consumers (s16/u16) so the copy becomes a SUBREG move cse does not unify.

(e) Did not work: moving `s1 = angle;` later in the arm (v1/v3: 13; after the inner if, v2: 24); `s16`/`u16` on `angle`
or on `s2` alone (w3/w4/w5: 13); `u16 s1` = `s16 s1` (w2 10, x3 0 — either narrow width works; body uses `s16`, the
global's type). The sweep's R2/R7/R8/R9/R17/R18 moves all stayed at 13.

(f) Method: the tree's lever comments were accurate about the SYMPTOM ("coalescing kills that copy unless the value is born
in $a0"; "`s1 = 0x800` floats out of the beqz delay slot") but both causes were upstream of allocation: the copy's
mode (cse) and the constant's position (sched1). METHOD's c4 row ("a copy deleted because two locals shared a WIDTH")
was the right row; the allocation table confirmed the second move's arithmetic in one run.

(g) Structs: no. Both decisions are about scalar locals (a same-mode copy in cse, a constant set's placement in sched1);
the object `a0` (+0x05 u8, +0x14 s32, +0x20..+0x32 s16 fields) as a struct would change spelling only.
