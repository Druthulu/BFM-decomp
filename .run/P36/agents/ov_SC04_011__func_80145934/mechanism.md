# func_80145934 (ov_SC04_011_after.c) — the §5a cross-jump barrier, delevered

**Final score: 0 (MATCH, 62/62 ins).** Body: `PACK/body.c`. Sibling body also at 0: `PACK/sibling_func_80145A2C.c`.

## (a) The residual in one sentence

`COUNT`, mine 58 ins vs target 62: the target keeps TWO identical `la a0,D_80192964 / j <call>` blocks — the
`v >= 0x6A4` arm at `+0x20` and the `v >= 0x384` arm at `+0x80` — and the lever-free body has only one, because
gcc **cross-jumped** the first arm into the fifth (the first arm's conditional branch is inverted and retargeted:
`beqz v0,c4` where the target has `bnez v0,84`, then the whole 4-insn block is gone).

Counted first, per the brief: 62 − 58 = 4 = exactly one `lui/addiu/j/nop` block. This is a MISSING-INSTRUCTION
residual, not a register one; no allocation table was needed and none was consulted.

## (b) The pass and the decision, read from the compiler's own source

* The pass is **jump2** — `toplev.c:3142`, `jump_optimize (insns, 1, 1, 0)`, the only call with `cross_jump = 1`,
  run after reload/sched2 and **before** `dbr_schedule` (so the blocks it compares are `set a0,<symbol_ref>` +
  `jump`, with the delay-slot nops not yet inserted).
* The site is the unconditional-jump arm, `jump.c:1969` `if (cross_jump && simplejump_p (insn))`: for each `j L`
  it walks `jump_chain[L]` and calls `find_cross_jump (insn, target, 2, …)`; a hit runs `do_cross_jump`
  (`jump.c:2537`), which deletes the first block and retargets its jump; the surrounding
  conditional-branch-around-unconditional-jump rule then folds the branch, giving the `beqz` we see.
* `find_cross_jump` (`jump.c:2371`) needs `minimum` (=2) profitable matches. Each arm has only ONE insn before its
  jump, so the merge is paid for by the discount at `jump.c:2513-2517`:
  `if (GET_CODE (i1) == JUMP_INSN && JUMP_LABEL (i1) && prev_real_insn (JUMP_LABEL (i1)) == e1) --minimum;`
  — every arm of an else-if ladder is a conditional jump *around* a block ending in an unconditional jump, so the
  discount always applies and one matching insn is enough.
* The comparison itself is `rtx_renumbered_equal_p` (`jump.c:2470`), whose symbol case is a **string-pointer** test:

      case SYMBOL_REF:
        return XSTR (x, 0) == XSTR (y, 0);          /* jump.c:2440 */

  Two references to the same `extern` share one interned identifier, hence one string pointer, hence "equal".

**What the barrier was doing (proved on the RTL dumps, `PACK/scratch/d/j2_bar.txt` vs `j2_free.txt`):** the
`__asm__ __volatile__("" ::: "memory")` becomes `(insn 21 … (parallel [(asm_operands …) (clobber (mem:BLK …))]))`
sitting between the arm's `set a0` and its `jump`. `find_cross_jump`'s first step-back then compares a PARALLEL
against a SET, `lose`s at `jump.c:2470`, and — because the mismatching insn is not a `JUMP_INSN` — never reaches
the discount, so `minimum` stays 2 and the merge is refused. The lever-free dump shows the opposite outcome
directly: `jump_insn 15` has become `(ne …) (label_ref 136)` and the arm's two insns are gone.
So the site is a **liveness/identity fact, not an ordering one**: the barrier's only job was to make the two blocks
textually unequal to `find_cross_jump`.

## (c) The move that closed it — one line

* Declare a second name for the same symbol under its own asm label inside the body and use it in the `v >= 0x6A4`
  arm: `extern u8 aD80192964 __asm__("D_80192964"); … p = &aD80192964;`

That decl's `DECL_ASSEMBLER_NAME` is the *distinct* identifier `*D_80192964` (`varasm.c` `make_decl_rtl`'s asmspec
path), so `XSTR` differs, `rtx_renumbered_equal_p` returns 0 on the very first step-back, `minimum` stays 2, and the
two blocks survive. `assemble_name` strips the `*`, so the emitted instructions and the relocations are unchanged:
still `R_MIPS_HI16 / R_MIPS_LO16 D_80192964` in both blocks.

An asm label on a declarator is **class E** in `tools/lever_census.py:20` ("asm-label aliases — deferred to the
types phase, censused, not a Phase-36 lever"), classified at `lever_census.py:198`; it is existing house style
(`src/800_c.c:2084-2095`, `src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c:1906`, and function-local at
`src/ov_SC06_008/ov_SC06_008_jr_80135D20.c:1390`). The class-B barrier is gone.

### Byte proof
* `delever_search --try … func_80145934 PACK/body.c --body` → **score 0**, 62/62.
* Whole object, same recipe, candidate vs unmodified tree text:
  both `sha1 e3f001bb2b488179cc97ef44c7076939189e8a0e`, 130484 bytes — **bit-identical**, so the alias adds nothing
  to the symbol table or the relocations. (A hand-rolled pipeline first disagreed with the stored baseline by 48
  bytes; the negative control on the UNMODIFIED text disagreed identically, which exonerates the candidate and
  convicts the instrument — the extra `-I<srcdir>` a scratch-path compile needs is what costs those bytes.)
* Sibling `func_80145A2C`, same TU, same shape (`D_801929F4` at `>=0x6A4` and `>=0x384`), same move → **score 0**.

## (d) GENERATOR PROPOSAL

**R20 `symbol_aliases`:** when the residual is `COUNT` with the target holding an extra `lui/addiu/j/nop` block and
mine holding an inverted conditional branch to a later identical block (the cross-jump signature), find the address
constant that two arms of the same if/else chain share and re-issue the earlier arm's reference through a
body-local `extern <type> a<SYM> __asm__("<SYM>");` alias — one candidate per repeated `&D_xxxxxxxx` in the body.

Mechanically detectable with no search: the same `&IDENT` appears in two arms of one chain **and** the diff shows
`insert target[k:k+4]` of `lui/addiu/j/nop` — a one-candidate-per-repeat generator, not a beam. It is the exact
replacement for the `§5a cross-jump barrier` levers, whose whole population is this shape; the pack reports **126
copies with ONE NEEDED site**, and the two members tested here both closed on the first try.

## (e) What did NOT work, with byte evidence

| candidate | score | why |
|---|---|---|
| `goto call;` in the first arm + `call:` label before the tail (`scratch/c1.c`) | 11 | `rtx_renumbered_equal_p`'s LABEL_REF case (`jump.c:2432-2437`) calls two label-refs equal when `next_real_insn` of both labels is the same insn — two labels at the same position are indistinguishable to cross-jump, so a private label cannot separate the arms |
| ternary chain for the whole ladder (`scratch/c2.c`) | 60 | different expansion entirely; not the target's shape |
| temp in the arm, `void *q = &D_80192964; p = q;` (`scratch/c3.c`) | 11 | copy-propagated before jump2; identical RTL |
| tail rewritten as default-then-override, sibling style (`scratch/c4.c`) | 11 | the tail already matches; irrelevant to the residual |
| `p` retyped `u8 *`, call unfaked (`scratch/c5.c`) | 11 | same RTL |
| block-scope `extern u8 D_80192964;` redeclaration in the arm (`scratch/c6.c`) | 11 | a redeclaration reuses the SAME interned identifier, so `XSTR` is the same pointer — this is the pure-C attempt at the winning move and it fails for a precise reason |
| `(void *)((u8 *)&D_80192964 + 0)` (`scratch/c8.c`) | 11 | folded to the bare `symbol_ref` |

Also ruled out by reading rather than compiling: a `CODE_LABEL` before the arm's `set` cannot help either, because
`jump.c:2410-2414` treats a label in stream 1 as *free* (`--minimum; break;`), and stream 2's labels are skipped
outright by the walk at `jump.c:2392-2394`.

## (f) Where the method fell short

* The brief's "count first" rule was exactly right and cheap (4 = one block), but the classifier's label for the
  closed body reads `OTHER` at score 0, which is noise.
* The pack's `history.txt` shows 2,093 compiles across seven mechanical runs stuck at 11. Every one of them was a
  statement/declaration move; **no generator in the family can change a symbol's identity**, so the search space
  never contained the answer. The lesson generalises: when the residual is a whole missing BLOCK rather than a
  displaced or recoloured instruction, the defect is a block-level *equality* decision (cross-jump, jump threading),
  and statement moves cannot reach it — read `jump.c` before spending a beam.
* `sites.txt` said "BARRIER (not a pin)" and the brief asked whether it stood for ordering or liveness. It was
  neither: it stood for **symbol identity**. Worth adding as a third answer to that question.
* The whole-object check has no agent-safe tool. `--try` compares the function's instructions only; I had to
  hand-build the object twice (candidate + control) through `delever_oracle.compile_obj` to prove the alias adds no
  symbol-table delta. A `--try --whole` flag that does exactly that compare would be worth having, since a
  body-only bank whose object gains a symbol is precisely the failure mode an alias generator could introduce.
