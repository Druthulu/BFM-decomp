# func_801AD068 (md_SC07_004) — P36 S104 agent e27 — score 5 -> 0, ZERO levers (was 1 `$3` pin)

(a) Residual: REG only (95/95): the guard value `v1 = *(s32 *)(arg0 + 0x1C)` lands in `$a0` where the target keeps it in `$v1`
(5 instructions: the load, both `slti`, the `subu`, the `sll ...,3`). Same instructions otherwise.

(b) Pass and decision (dumps `scratch/dumps_free/`, `scratch/dumps_c5/`; `tools/alloc_table.py`):
- Free text: the value `v0` computed in both arms is ONE pseudo r78 (`v0 = (0xF - v1) << 5` / `v0 = v1 << 3`), then
  `a0 = r78 & 0xF8`. r78 gets hard-register preferences `v0,a0` (`set_preference`, `global.c:1535-1610`: the `a0 = r78 & 248`
  set, first operand). `expand_preferences` (`global.c:781-822`) then copies r78's preferences to the guard r74, because r74
  DIES (REG_DEAD) in insns whose single-set destination is the global allocno r78 (insns 60 `r78 = 15 - r74`, 69
  `r78 = r74 << 3`) and the two do not conflict. `.greg`: "74 preferences: 4". Order `78 74 72`: r78 takes v0, r74 conflicts
  v0 and `find_reg` honours its surviving preference (`global.c:1037-1071`) -> `$a0`.
- Close: `func_80016450((v1 >= 12 ? (0xF - v1) << 5 : v1 << 3) & 0xF8, 1);`. fold distributes the constant AND into the
  arms (`fold-const.c:3338-3367`: `(c ? a : b) & K` -> `c ? a & K : b & K`, taken because K is constant), so r74 now dies in
  insns whose destinations are one-block LOCAL temps (c5.i.lreg insns 57 `r81 = 15 - r74`, 63 `r84 = r74 << 3`; reg_allocno
  < 0), `expand_preferences` never fires, and `.greg` shows NO preference for 74 -> first free register after `v0` = `$v1`.
  Both arms now end in `r78 = rX & 248` (2 in `.greg`); with rX in v0 and r78 in a0 (copy preference) both are
  `andi a0,v0,0xf8`, and the post-reload cross-jump (`jump.c:2371`, `toplev.c:3142`) merges them into the target's single
  `andi` at the join (1 in `.jump2`) — the arm-1 `j` + `sll v0,v0,5` delay slot follows.
All claims proven on dumps (the preference lines, the insn dests, the 2 -> 1 andi count); the close on bytes (`--try` 0).

(c) Moves (body.c = scratch/c/c5.c, score 0):
1. the if/else computing `v0` + `func_80016450(v0 & 0xF8, 1)` -> ONE call whose argument is the ternary, the mask outside:
   `func_80016450((v1 >= 12 ? (0xF - v1) << 5 : v1 << 3) & 0xF8, 1);` — `v0` deleted, the pin deleted;
2. the stale comments about the pin and the swapped arms removed (the rest of the body is body_free.c unchanged).
The arm order matters: `v1 < 12 ? v1 << 3 : (0xF - v1) << 5` scores 5 (COUNT 94 — the arms' layout, the `j` + slot, flips).
One call per arm (c1/c2: 11, c3 `else if`: 14) is worse: the AND then feeds `$a0` directly and cross-jump merges more.

(d) GENERATOR PROPOSAL: when a caller-saved REG residual moves a value that DIES in the arms of an if/else computing one
variable which is then masked/offset by a constant into a call argument (`.greg` shows the dying value inheriting a
`preferences:` line), rewrite the if/else + use as ONE expression `(c ? A : B) OP K` — fold pushes `OP K` into the arms,
the dying value's last uses become local temps, `expand_preferences` (global.c:781) no longer passes the hard-register
preference on, and cross-jump re-merges the duplicated tail. Keep the tree's arm order.

(e) Did NOT work: the free sweep's 190 compiles (R7 block/do-while, R8 temp, R10 param-copy, R18 bystander) all stay at 5 —
none touches the if/else shape. Per-arm calls (c1-c3, 11-14); the natural-order ternary (c6, 5).

(f) Method gap: the allocation table printed `prefers a0` on r74 but not WHY; the answer was `expand_preferences`
(global.c:781), which copies preferences along REG_DEAD edges into global allocnos — not in METHOD's list. A column
"preference inherited from rN via insn U" in `alloc_table.py` would have named it immediately. Step 14's "goto -> structured"
family generalises: an if/else assigning one variable -> a ternary is equally out of reach of every generator.

(g) Structs: NO for this lever — the decision is global.c's preference propagation over scalar pseudos. `arg0` as a struct
(0x1C s32 timer, 0x20 pointer to a sprite with u16 0x12/0x18/0x1A/0x1C, 0xCC/0xD0 handles, 0xE0/0xE4 deltas — the file
already has `Obj_801AD068`) would read better for the u16 updates, and `Align1W_801AD068` is already the struct the unaligned
write-backs need; not tested (nothing left to close).

(h) Joint check (e27): the three e27 body.c files (func_801AC9CC, func_801AD068, func_801AE82C) spliced into one copy of the tree TU and compiled through the recipe (`md_SC07_004__func_801AC9CC/scratch/joint.py` -> `scratch/joint/joint.o`): `.text` sha1 ad583f4dfb0c and `.rodata` identical to the baseline snapshot, relocations and symbol table identical; the only byte difference is the source-path string in `.strtab`.
