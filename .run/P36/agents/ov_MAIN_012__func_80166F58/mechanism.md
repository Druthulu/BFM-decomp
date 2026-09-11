# func_80166F58 (ov_MAIN_012_jr_8015A3C8.c) — P36 S104 agent d2

**Result: score 0 in plain C on the first `--try`** (69/69 ins; no pin, no asm, no volatile, no do-while). Levers 5 → 0.
The same text (only the `D_801xxxxx` table symbol substituted) also scores 0 in all 7 other TUs that carry the lever
spelling: ov_SC07_007, ov_SC02_037, ov_SC03_107, ov_SC07_010, ov_SC07_006, ov_SC01_077, ov_SC07_011
(`scratch/port_<sym>.c`, each `--try` printed `score 0 … MATCH`).

## (a) The residual in one sentence
The target sign-extends each parameter in place (`sll/sra a1,a1,16`) and then copies it into its callee-saved home
(`move s4,a1`, the same for `a2`/`s1`); the lever-free body writes the `sra` straight into `s4`/`s1`, so it is 2 instructions
short per parameter (COUNT, 67 vs 69). Instructions are missing; the registers are not wrong.

## (b) The passes and decisions (all read in the dumps `scratch/dumps_match/`, `scratch/dumps_free/`)
- **expand / cse.** `p2 = (short)t2`, where `t2` already holds `(short)param_2`, expands to a SECOND `ashift/ashiftrt 16`
  pair into `p2` (insns 25/26 in `.rtl`). That is a shift, not a `(set REG0 REG1)`, so cse's register-copy folding
  (`cse.c:7440-7474`) never sees a copy, and nothing merges `t2` and `p2` (the pair is still there in `.cse`, `.cse2`).
  In the free body `p2 = t2` IS a REG copy and cse folds it: one pseudo, written directly by the `sra`, lives in `$s4`.
- **combine.** `simplify_shift_const`, `combine.c:7926-7942` ("(ashiftrt (ashift foo C1) C2) and FOO has more than C1
  high-order bits equal to the sign bit"): `t2` has 17 sign-bit copies (recorded by `set_nonzero_bits_and_sign_copies`,
  `combine.c:779`), so the pair collapses to `count = 0`, i.e. the plain copy `(set (reg 78 p2) (reg 76 t2))` (`.combine`
  insn 26). combine does it AFTER cse, so no pass folds that copy any more. `t2` has a second use (`eq = (t2 == t3)`,
  the `xor` insn 35) so combine cannot instead fold the `sra` into `p2`.
- **local-alloc.** `update_equiv_regs` → `optimize_reg_copy_1` (`local-alloc.c:700`, called at `:1007`): the copy's source
  `t2` dies later in the same block, so the later reader (the `xor`) is rewritten to read `p2`/`p3` and `t2` dies at the
  copy (`.lreg` insn 35 reads `(reg 78)`,`(reg 79)`; insn 26 carries `REG_DEAD 76`). `t2` is now a two-insn local
  quantity and gets the dying `$a1` of its own `sll`; `p2` crosses the calls and goes global to `$s4`. Hence
  `sll a1; sra a1; move s4,a1` — exactly the target (and the `xor s4,s1` the target shows).

The tree's levers faked exactly this: the pins put `t2` in `$5` and `p2` in `$20`, and the SHB launders stopped cse from
seeing `p2 = t2` as a copy.

## (c) The move that closed it (R71 port of the banked ov_SC04_011 header `src/shared/ov/func_80166F58__3728db8a.h`)
1. `p2 = t2;` → `p2 = (short)t2;` and `p3 = t3;` → `p3 = (short)t3;` (re-extend the already-short value into the home).
2. `eq = (p2 == p3);` → `eq = (t2 == t3);` (compare the pre-copy temps: the second use of `t2` is what keeps combine
   from merging the `sra` into `p2`).
Both are load-bearing, proved on bytes: only the `p3` copy plain → score 2 (`scratch/v_p3plain.c`); `eq = (p2 == p3)` with
both re-extensions → score 4 (`scratch/v_eqp.c`); `short t2, t3` locals with plain copies → 4 (`scratch/v_shortlocals.c`).
Declaration order was reordered to the header's (`t2,t3,p2,p3`) but it is not what closed it (the extension statements are).

**Why the naive splice was a COMPILE-ERROR:** the header defines `s32 func_80166F58(...)` and the table `D_8018E9E0`;
ov_MAIN_012 declares `extern void func_80166F58(s32, s32, s32, s32);` later in the same TU (lines 7932, 7980 —
"conflicting types"), and its record table is `D_80184418`. The function has no `return` statement, so `void` vs `s32`
is byte-neutral. Those two renames are the ENTIRE port.

## (d) Generator proposal
When a lever class has a lever-free banked twin of the same function name and size in another overlay (`related.txt`
already finds them), port the twin's body mechanically: substitute every extern symbol that differs by position in the
disassembly (here only the `%hi/%lo` table `D_8018E9E0`→`D_80184418`, found by pairing relocations of the two target
objects) and take the return type from the target TU's own later `extern` prototype — then `--try`. For the residual
class itself: **"when the target shows `sra aN,aN,16; move sK,aN` and mine shows `sra sK,aN,16`, spell the home as a
re-extension of a named short temp (`t = (short)arg; home = (short)t;`) and give the temp one more later use"**.

## (e) What did not work (byte evidence)
The mechanical search (`history.txt`, 2,292 compiles across R2/R4/R7/R9/R10/R18) and the free sweep's `free_016.c`
("swap-stmts") all stayed at 4: none of those generators writes a redundant `(short)` re-extension, and none moves a
use from the home back to the temp. Single variants above: 2, 4, 4.

## (f) Where the method fell short
Nothing needed beyond the brief's R71 lead: the port closed on the first `--try`. The one gap is tooling: the splice that
produced the COMPILE-ERROR should have been retried with the TU's own return type and its own table symbol — both are
readable from the target TU (a later `extern` prototype; the pack's own `body_tree.c` names `D_80184418`). A generator that
does that substitution would have closed this class (8 TUs) with zero agent time.

## (g) Structs question
**No — structs are not the missing piece here.** The residual is scalar: two parameter sign-extensions and the copies
into their call-crossing homes (expand → combine `combine.c:7926-7942` → local-alloc `local-alloc.c:700`). No memory
access is involved, so the aggregate-vs-scalar channel (`expr.c:4568-4577`, `sched.c`/`cse.c` alias decisions) cannot
touch it. Tested on bytes with a body-local `typedef struct { u16 kind; u8 pad[0x2A]; s32 owner; u8 pad2[0x28]; } Ent;`
for the 0x58-byte records at `D_8011D030` (`e->kind`, `e->owner`, `e + 1`): with the port → score 0
(`scratch/v_struct.c`); with the free body's plain copies → score 4 (`scratch/v_struct_free.c`). The struct is
byte-neutral and a readability option for the structs phase (fields: `+0x00 u16 kind`, `+0x2C s32 owner`, stride 0x58).
