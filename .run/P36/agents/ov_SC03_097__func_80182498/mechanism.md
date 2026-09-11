# func_80182498 (ov_SC03_097) — score 0, ZERO levers, FIRST --try (agent e37, P36 S104)

(a) Residual (free body, 17, COUNT 193 vs 185): three extra callee-saved registers (`s5`/`s6`/`s7`) and a 16-byte bigger
    frame — mine keeps `&sv` (`sp+48`), `&out` (`sp+56`) and even `sp` itself across the calls and passes them by `move`;
    the target rematerialises `addiu a1,sp,48 / addiu a2,sp,56 / addiu a0,sp,16` at the SECOND `ApplyMatrixSV` while the
    matrix pointer `m` (`sp+16`) does live in `s4` for the four EARLIER calls. The tree's three levers: two `launder
    out-only` on `svp`/`outp` and a `$29` pin spelling `sp + 0x10` (the free body's `u8 *spr` is uninitialised — that is
    the `s7 -> sp` pair).

(b) Pass + decision. `expand_call` precomputes each register argument with `force_operand`, so every `m`/`sv`/`out`
    argument is a fresh pseudo `= (plus fp K)`; cse1 unifies the later ones with the first (`cse_insn`, the SET_SRC
    replaced by the cheaper equivalent register) — that is the `s4` for `m`, and it would be an `s5`/`s6` for `sv`/`out`
    too, if the second `ApplyMatrixSV` were in cse1's reach. The tree's `ang = -0x400; if (bit) ang = 0x400;
    RotMatrixZ(ang, m); ApplyMatrixSV(m, sv, out);` keeps everything in ONE extended block: `beqz -> L; li; L:` is a
    branch around a block that cse SKIPS (`cse.c:8149-8170`, `invalidate_skipped_block`), so the table survives to the
    second call and all three addresses are unified. The levers break exactly those three equivalences.

(c) The move — the call in BOTH arms of the if:
        if (p->f0 & 1) RotMatrixZ(0x400, m); else RotMatrixZ(-0x400, m);
    and both `ApplyMatrixSV(m, sv, out)` calls plain. The if/else JOIN label has two uses, so cse1 neither follows nor
    skips into it (`cse.c:8106`): the second `ApplyMatrixSV`'s three address pseudos start from an empty table and stay
    `addiu`s, the first block still unifies `m` into `s4`, and the post-reload cross-jump (`jump.c:2371`) merges the two
    identical `move a1,s4; jal RotMatrixZ` tails back into one call with `li a0,±0x400` per arm (reorg then hoists the
    else arm's `li` into the `beqz` delay slot). Score 0 on the first `--try`.

(d) GENERATOR PROPOSAL: when a body carries `launder`/pin levers on CALL ARGUMENTS whose residual is extra callee-saved
    address holders across a later call, and an `x = A; if (c) x = B; call(x, …)` precedes that call, rewrite it as
    `if (c) call(B, …); else call(A, …);` — the join label with two uses ends cse1's extended block; more generally a
    "cse must forget these" lever is a label-use-count question (this session's third instance: this, func_8017F7E4's
    `switch`, and S103 c10).

(e) Nothing else was tried (first `--try` closed it). NOT tested: whether `ang` as a `switch`/ternary inside the call
    argument closes too (predicted NO — a `?:` in the argument keeps one block).

(f) Method: read the target block by block (the `move a1,s4` in the jal delay slot AFTER the join vs the `addiu a0,sp,16`
    right after it is the whole tell) before any dump — no dump was needed. The whole-src grep found 12 copies.

(g) Structs: the shape is already struct-typed (`Rec_/Ot_/PTag_/Bidx_`); the decisive fact is cse's block boundary,
    which no type changes. A `MATRIX m` (Sony's typedef) instead of `s32 m[8]` + `Mat32_` cast would make the block copy
    `m = D_800AE620` a struct assignment with the same `move_by_pieces` bytes — a readability gain only.

Copies (the same three edits on each sibling's own tree text — scratch/port.py — all score 0; scratch/copies/LIST.tsv):
  func_8018B23C ov_SC03_014, func_801860E8 ov_SC03_118, func_8018EBCC ov_SC04_011, func_80187314 ov_SC06_000,
  func_801844D4 ov_SC02_028, func_80185E34 ov_SC03_104, func_80184918 ov_SC06_016, func_801829F8 ov_SC03_101,
  func_801865DC ov_SC03_024, func_8018234C ov_SC07_000, func_8018B2C4 ov_SC02_011, func_80185150 ov_SC07_002.
