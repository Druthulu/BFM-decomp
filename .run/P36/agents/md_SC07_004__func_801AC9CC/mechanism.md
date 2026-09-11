# func_801AC9CC (md_SC07_004) — P36 S104 agent e27 — score 10 (lever-free; sweep best 2) -> 0, ZERO levers (was 1 `"memory"` barrier + a 16-byte `s16 sp10[8]`)

(a) Residual: lever-free, 48 vs 47 ins and a frame 8 bytes too big (48 vs 40). The target loads the 0x30 field TWICE (`lh v0,48(s0)`
for the `== 0` test, `lhu a3,48(s0)` for the value passed on); lever-free, cse gives the value load the test's register
(`move a3,v0`), and a dead shift temp gets a stack slot. The tree's barrier kept the two loads apart (any memory write
invalidates a varying-address cse entry, `invalidate_memory` `cse.c:1701-1718`, `note_mem_written` `cse.c:7539-7580`), and its
`s16 sp10[8]` (16 bytes; the callee only touches +0..+7) padded the frame.

(b) Pass and decision (dumps `scratch/dumps_free/`, `scratch/dumps_a6/`, `scratch/dumps_f1/`):
- The original reads the field ONCE into a 16-bit local and tests the LOCAL: `a3 = F30; if (a3 == 0) a3 = 6;`. The test
  sign-extends the HImode pseudo (`(ashift (subreg:SI a3) 16)` + `ashiftrt 16`, f1.i.cse insns 47/48). combine folds the load
  (i1, insn 45) + both shifts into `sign_extend:SI (mem:HI)` = `lh`, but a3 is still live after i3, so i1's set is ADDED back
  (`added_sets_1`, `combine.c:1460`, PARALLEL built `:1644-1664`) and split out as `newi2pat` = the kept `lhu a3`: two loads of
  one address with no copy — exactly the target's `lh v0` / `lhu a3`.
- Because `newi2pat != 0`, `combine.c:2303-2311` does not zero the ref count of i2dest (the ashift temp, reg 80): `.lreg`
  "Register 80 used 2 times across 6 insns in block 2; ST_REGS or none", no disposition in `.greg` -> reload gives it a slot
  (the S103 c35 / e3 orphan-slot class, `reload1.c:2331-2352`). f1.s: `.frame $sp,40 # vars= 16` = 8 (the vector) + 8 (orphan).
  So the target frame is an 8-byte vector PLUS the orphan, not a 16-byte array.
- Lever-free text had the order reversed (s32 `v0 = F30` test first, then `u16 a3 = F30`): cse replaces the second load by the
  first's register (same `mem:HI`), combine folds the load into the test's extension, a3 becomes `(subreg:HI v0)` = `move a3,v0`.
All three claims proven on dumps; the close proven on bytes (`--try` 0, 47/47).

(c) Moves (joint; body.c = scratch/f/f1.c, score 0):
1. `s16 sp10[8]` -> `s16 sp10[4]` (an SVECTOR-sized vector: the callee writes +6, `*(s16 *)(a0 + 6) = 0` in
   src/ov_SC07_002/ov_SC07_002_jr_8017C8D0.c:2742) — frame 48 -> 40 once the orphan exists;
2. the two reads of 0x30 collapsed into ONE `s16 a3 = *(s16 *)(arg0 + 0x30); if (a3 == 0) a3 = 6;` (the barrier and the `v0`
   test temp deleted);
3. readability: the call result stored directly (`*(s32 *)(arg0 + 0x2C) = func_8017D7D4(...)`), `+= 1` on the 0x2 counter.
   Also 0: `v0` kept (f4), `v1` inlined into the if/else (f2), `(*(u16 *)…)++` (f3).
Enumeration (scratch/gen1.py, e2/, 80 bodies with the 8-byte vector): 14 zeros — every one reads the value first (`vf_before`);
`u16`/`s16` a3 with a `mem`/`v0`/`a3`/`(s16)a3` test all close. With the 16-byte array the same text scores 6 (frame only, a6.c).

(d) GENERATOR PROPOSAL: when a `"memory"` barrier separates two loads of the SAME field (one sign-extended for a test, one
kept for a value) and a local array is larger than the callee uses, delete the barrier, read the field once into a 16-bit
local that the test reads (`x = F; if (x == 0) x = K;`), and shrink the array to the used size — combine's added-set split
re-creates both loads and its orphan temp re-creates the frame slot the padding faked.

(e) Did NOT work (bytes): test load before the sp10 stores + value after (a1: 4 — the stores invalidate cse but the scheduler
cannot sink the test load past the in-struct frame stores, `true_dependence` `sched.c:817-839`, `memrefs_conflict_p` returns 1
for fp vs arg0 bases `sched.c:614-662`); value load before the stores + test after ("between", 2 with the 16-byte array, 8
with the 8-byte one — `lhu a3` stays above the stores); `if/else` and the ternary in the call (a2/a3/a5: 10-21 — cse still
merges the loads). The free sweep's best 2 (R18 bystander) was the "between" shape.

(f) Method gap: the frame was the tell — the free body's +8 frame is a combine orphan, and the TREE's frame "matched" only
because the array was padded to 16. The generators never shrink an array (R12 changes scalar widths only) and never merge two
reads of one field into one local, so the right text scored 6 for them and the joint move was invisible. A rule "count the
array's used bytes against the callee" plus d10's "count dead pseudos against the frame" would have found it.

(g) Structs: plausibly yes for readability, NO for the lever. `arg0` is an object (u16 at 0x2/0x6/0xA/0xE, void* at 0x20,
s32 at 0x1C/0x2C, s16 at 0x30/0x32, a sub-object at 0x34) and `sp10` an SVECTOR {vx, vy, vz, pad}. The decision here is
cse's same-MEM equivalence and combine's added-set split over a scalar local; a COMPONENT_REF gives the same `mem:HI`, so a
struct would not change it. A struct SVECTOR local (COMPONENT_REF stores, still in-struct) would keep the same stores; not
tested (no SVECTOR typedef in the TU's includes — a6c.c failed to compile for that reason).

(h) Joint check (e27): the three e27 body.c files (func_801AC9CC, func_801AD068, func_801AE82C) spliced into one copy of the tree TU and compiled through the recipe (`md_SC07_004__func_801AC9CC/scratch/joint.py` -> `scratch/joint/joint.o`): `.text` sha1 ad583f4dfb0c and `.rodata` identical to the baseline snapshot, relocations and symbol table identical; the only byte difference is the source-path string in `.strtab`.
