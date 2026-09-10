# func_8017DBE4 (ov_SC06_010_jr_8017A4AC.c) — T7 agent c35 — CLOSED, score 4 -> 0

## (a) The residual in one sentence
Instruction COUNT and every register are identical (12 vs 12); only the FRAME differs: mine `addiu sp,-32 / sw ra,24(sp)`,
target `addiu sp,-24 / sw ra,16(sp)` — an 8-byte (4 rounded to 8) stack slot is allocated for a pseudo that no
instruction references.

## (b) The pass and the decision
- The lever-free text `p = (s32)&D_801B2028; ... p += new_var; *(s8 *)p = 0;` makes pseudo 74 (`p`) SET TWICE
  (insn 11 `set 74 sym`, insn 20 `set 74 (plus 75 74)`), 4 refs (`.flow`: "Register 74 used 4 times across 5 insns").
- combine merges i1=11, i2=20, i3=23 into one `sb zero,%lo(D)(at)` store (`.combine`: 2 successes). The ref bookkeeping
  after a successful combine, `combine.c:2304-2313` (i2) and `:2329-2337` (i1): `reg_n_sets` is decremented and
  `reg_n_refs` zeroed only when the sets reach 0. For i2 the decrement is SKIPPED because `i2dest_in_i2src` (insn 20's
  source `(plus 75 74)` reads 74 — a self-referencing `p += r`); for i1 it goes 2 -> 1. So reg 74 leaves combine with
  no instruction but `reg_n_sets = 1, reg_n_refs = 4`.
- `.lreg`: "Register 74 used 4 times ... dies in 0 places; ST_REGS or none" — regclass saw no use, so no class;
  `.greg`: "1 regs to allocate: 74", disposition list has only 75 -> 74 gets `reg_renumber = -1`.
- reload's `alter_reg` (`reload1.c:2331-2352`): `reg_renumber[i] < 0 && reg_n_refs[i] > 0 && no equiv` ->
  `assign_stack_local` of 4 bytes -> frame 16 (args) + 4 slot + 4 ra = 24 -> rounded 32; ra moves to 24(sp).
- The tree's `register s32 p __asm__("$4")` removed the pseudo entirely (a hard reg has no stack slot), which is the
  only thing the pin was doing.
All of the above is read off this function's own dumps (`scratch/dumps_a0/a0.i.{cse,flow,combine,lreg,greg}`) — PROVEN.

## (c) The move that closed it
Write the store as ONE expression with no multiply-set temporary — the natural array spelling, with the table typed as
its sibling `func_8017D9A0` (same TU, line ~4448) already types it:

    extern u8 D_801B2028[];
    D_801B2028[param_1[0x2c / 4]] = 0;
    ((void (*)(s32 *))func_80146C3C)(param_1);

Byte-proven (score 0). Controls, also byte-proven score 0:
- `c4.c`: keep the original shape but single-assign `p = (s32)&D_801B2028 + param_1[0x2c/4];` -> 0. This isolates the
  cause to the two-set `p` (not the types, not the call).
- `c1.c` (`s8` table, void call) and `c3.c` (`u8` table, `func_80146C3C()` via the in-TU void decl) -> 0.
The call is written at the callee's REAL arity (`src/shared/ov/func_80146C3C.h`: `void func_80146C3C(u8 *a0)`) — zero
bytes, because `$a0` still holds `param_1` at the `jal` (the target's callee reads it implicitly).

## (d) GENERATOR PROPOSAL
When the residual is FRAME-ONLY (same instruction count and registers, `addiu sp` / `sw ra,N(sp)` offsets 8 larger) and
no load/store touches the extra slot, find a local that is assigned more than once where one assignment reads itself
(`x += y`, `x = x op y`) and whose every use folds into an address — rewrite it as a single assignment
(`x = a + b;`, or inline it into the access): combine skips the `reg_n_sets` decrement for a self-referencing i2
(`combine.c:2306`), the ghost pseudo keeps `reg_n_refs > 0`, and `alter_reg` gives it a stack slot (`reload1.c:2331`).
Detector: `.greg` "N regs to allocate" lists a pseudo absent from the dispositions whose `.lreg` line says
"dies in 0 places; ... or none".

## (e) What did not work
Nothing needed; the mechanical search (history.txt) reached 2 with a statement swap and stayed at 2 [COUNT] — every one
of its moves kept `p += new_var` (a self-referencing two-set pseudo), so none could remove the ghost slot.

## (f) Where the method fell short
The residual class printed "OTHER" and the method's counting step is framed around instructions; a frame-size-only
residual deserves its own row ("ghost stack slot") with the `.greg` detector above — it is readable in one grep and
the fix is a one-line rewrite.
