# func_801898E4 (ov_SC03_001_jr_80189030.c) — P36 S104 agent d12

**Result: score 0, ZERO levers** (the tree has 5 lever lines: pins `$19` x2, `$20` x2, `$0` x1 → 0). `PACK/body.c`.
The same text (with only the per-overlay `D_` names changed) also scores 0 on the class's other three copies:
- `src/ov_SC05_017/ov_SC05_017_jr_80186270.c` func_80186B24 → `PACK/scratch/func_80186B24_body.c` (score 0)
- `src/ov_SC03_124/ov_SC03_124_jr_80185C98.c` func_8018654C → `PACK/scratch/func_8018654C_body.c` (score 0)
- `src/ov_SC04_018/ov_SC04_018_jr_80186570.c` func_80186E24 → `PACK/scratch/func_80186E24_body.c` (score 0)

## The moves (all three needed together)
1. `s32 b;` → `s16 b;` (the sweep's R12 already found this: 63 → 24).
2. ONE `count` for both lists: delete `descCount`, write `count = D_801EB56C[sel]` and `while (i < count)` in phase 5.
3. ONE `table` for both lists: delete `table2`, write `table = D_801EB574[sel]` and `b = table[i]` in phase 5.
4. Delete `id` (`id = b + 0`, the husk of the `$0` pin) and write `b + 0x62` / `D_800A6586[b]` directly.

Byte evidence for "jointly needed": 1+4 alone = 24; 1+2+4 (count merged only) = 17; 1+3+4 (table merged only) = 31;
2+3+4 with `s32 b` = 63; all four = 0. Removing the pre-existing `s32 pad[2]` breaks it (20) — it stays.

## (a) The residual
After the width move (24, REG-callee, 611 = 611 ins): a callee-saved permutation — `count` in `$s1` (target `$s3`), `table` in
`$s3` (target `$s4`), phase 1's hoisted `D_801EED54` base in `$s4` (target `$s3`), phase 3's hoisted `130` in `$s4` (target `$s1`).
Before the width move (63, COUNT, 610 vs 611): a missing `move s1,a0` in phase 5 (`b` kept across `func_800291B4`).

## (b) The passes and decisions (proved on bytes and on the dumps `scratch/dumps_c1`, `scratch/dumps_bd`)
- The missing `move s1,a0`: with `s16 b`, each SImode use of `b` is `(sign_extend:SI (reg:HI b))`, lowered as
  `ashift`/`ashiftrt`; combine's `simplify_shift_const` (`combine.c:7933-7942`, `num_sign_bit_copies` — `b` came from a
  `zero_extend` of a byte) reduces it to `(set (reg:SI 311) (subreg:SI (reg:HI 75) 0))` (insn 811 in `.combine`). That is a
  mode-changing copy, so it survives as its own pseudo: `b` (HI) dies at it in `$a0`, r311 crosses the call in `$s1`. With
  `s32 b` there is one pseudo and the `lbu` loads straight into `$s1`. The tree's `id = b + zr` ($0 pin) was faking this copy.
- The permutation: `find_reg` (`global.c:945-966`) tries, in pass 0, only registers already in `regs_used_so_far`, in
  `REG_ALLOC_ORDER`; a register is used for the first time only in pass 1. Allocation order is by `allocno_compare`
  priority (`global.c:587`). Separate `count`/`descCount`: `count` (r81, pri 2307) is live phases 2-3 only, so it does not
  conflict with r290/r311 (phase 5's `b` copy, `$s1`) or `tmpl` (r80, `$s1`, phase 1) → pass 0 gives it `$s1`; `table` (live from
  entry: the `default:` arm never sets it) then conflicts `$s0,$s1,$s2` → `$s3`, pushing the `D_801EED54` base to `$s4`.
  Merged: `count` (r81, refs 15, live 253, pri 1778.7) now spans phases 2-5, conflicts `$s0` (cnt r73), `$s1` (r311), `$s2`
  (`i`) → pass 0 fails, pass 1 takes the first new register `$s3`; `table` (r82, pri 1232.9) → `$s4`; the `D_801EED54` base
  (r108) → `$s3` (count is dead in phase 1); the phase-3 `130` (r254) → `$s1` (tmpl dead, r311 not yet born). All read off
  `tools/alloc_table.py bd` + a uid-paired `.lreg`/`.greg` map (`scratch/finalregs.py`; `scratch/bd_final.txt`).
- Why the tree needed the pins: the pins `$19` on `count` AND `descCount`, `$20` on `table` AND `table2` were the original's
  single variables, split in two by the decompiler; each pin pair was restoring one pseudo's conflict set.

## (c) The source move that closed it
Merge the two same-role locals into one (S103 c18's MERGE, here across two whole phases), plus the S103 c4 width move on `b`.

## (d) GENERATOR PROPOSAL
**When a body's levers pin two DIFFERENT locals to the SAME hard register (`register … count __asm__("$19")` and
`register … descCount __asm__("$19")`), try renaming the later-defined one to the earlier and deleting its declaration**
— a same-register pin pair is the signal of one original variable the decompiler split; apply it for every such pair
jointly (here two pairs), and combined with the best R12 width candidate. Corollary: a `$0` pin feeding `x = y + zr` into a
single-use temp → delete the temp and use `y` (the pin was faking a subreg copy a narrower `y` produces).

## (e) What did not work
- The sweep's R2/R4/R7/R8/R9/R18 moves and the other widths: all stuck at 24 (`history.txt`) — none changes which
  pseudos conflict, and the order is decided by distinct priorities (declaration order is dead, `global.c:604-610`).
- Either merge alone (17, 31): the `count` merge without the `table` merge leaves `table` taking `$s3`… and vice versa.
- `s32 b` with the merges (63): the `b` subreg copy disappears.

## (f) Where the method fell short
- The regen dir has no score index: I had to re-score all 282 files (~12 min) to find "the lowest-scoring file"; it was 24,
  the same as the width move `history.txt` already names. A `scores.txt` in the regen dir would save that.
- `tools/alloc_table.py` prints `-` for every global allocno's hard register; pairing `.lreg`/`.greg` insns by uid (as
  `scratch/finalregs.py` does; the `.greg` RTL prints `(reg:SI 17 s1)`) gives the final assignment for every pseudo and was
  what made the conflict argument readable. Worth folding into alloc_table.
- The biggest hint was in `body_tree.c` itself — two pins on one register. No generator reads that.

## (g) Structs
No. The levers here were allocation-conflict levers (which pseudos exist and how long they live), not memory-dependence
ones; no aggregate-vs-scalar access decision (`expr.c:4568-4577`, `sched.c:817`) is involved, and the close needed none.
Struct types would still help readability: `D_8010EDE8` is an array of 12-byte records (`+0` name pointer, `+4` s16
value; `D_8010EDEC` and `D_8010F468 - 0x67C` are BOTH `0x8010EDEC`, i.e. the same `+4` field read as u16), and `D_8010F468` an
array of 8-byte records (`+0` name pointer). Not tested on bytes (not needed for the close).
