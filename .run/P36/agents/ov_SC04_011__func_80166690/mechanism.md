# func_80166690 (ov_SC04_011_jr_8015C32C.c) — MATCH, score 0, no levers

**Result: score 0 (193/193 instructions, byte-identical).** Start 41 (COUNT, mine 189 / target 193);
the mechanical search's best over five traces was 16.

## (a) The residual in one sentence

Four instructions were MISSING, and every one of them was a `move rD,rS` sitting immediately after an
`addiu/addu rS,...` whose *result* is re-read by a following `sll rX,·,0x10` — i.e. the target keeps the
adjusted value in a **second** pseudo and copies it into the variable, where my text kept one pseudo:

| target | mine |
|---|---|
| `addiu v1,s3,-1` / `beq v1,v0` / **`move s3,v1`** | `addiu s3,s3,-1` / `beq s3,v0` |
| `addu v1,v1,v0` / **`move s0,v1`** / `sb v1,54(sp)` | `addu s0,v1,v0` / `sb s0,54(sp)` |
| `addiu v0,s2,-1` / **`move s2,v0`** / `sll v0,v0,0x10` / `bgez v0` | `lui v0,0xffff` / `addu s2,s2,v0` / `bgez s2` |
| `addiu v0,s0,-16` / **`move s0,v0`** / `sll v0,v0,0x10` / `bgez v0` | `addiu s0,s0,-16` / `sll v0,s0,0x10` |
| `addiu v0,s3,-1` / **`move s3,v0`** / `sll v0,v0,0x10` / `sra` / `bne` | `addiu s3,s3,-1` / `sll v0,s3,0x10` / `bne` |

The second give-away in the same residual: the target loads `li s2,15` and mine `lui s2,0xf`, and mine
sign-extends with `sra v1,s2,0x10` where the target needs `sll` **then** `sra`. Mine was keeping the
counters **pre-shifted into the high half** — a representation gcc only picks when the local is a plain
`int` whose every use is `(int)(x<<16)>>16`.

## (b) The pass and the decision, from the pinned cc1's own source

`short v = <int expression>;` expands to a **mode-narrowing copy** `(set (reg:HI v) (subreg:HI (reg:SI t)))`,
which on MIPS prints as `move`. Two passes each decline to delete it, and both refusals are conditional on
facts this function happens to satisfy:

1. **local-alloc — `combine_regs`, `local-alloc.c:1855`**
   ```c
   if ((already_dead || find_regno_note (insn, REG_DEAD, ureg))
       && reg_meets_class_p (sreg, qty_min_class[reg_qty[ureg]]))
   ```
   The copy's source is tied into the destination's quantity **only if the source dies in that insn**.
   Here the SImode temp does *not* die: the very next insn is the `sll …,0x10` of the sign-extended test
   (`if (sVar9 < 0)`, `if (sVar7 < 0)`, `while (sVar3 != -1)`). No `REG_DEAD` note ⇒ `return 0` (l.1881) ⇒
   two quantities ⇒ two hard registers ⇒ a real `move`. Proven on bytes.
2. **cse — the mode gate in `insert_regs`, `cse.c:1019-1021` and `cse.c:1029-1032`**
   ```c
   if (REGNO_QTY_VALID_P (regno) && qty_mode[reg_qty[regno]] != GET_MODE (x)) return 0;
   ...
   if (GET_CODE (classp->exp) == REG && GET_MODE (classp->exp) == GET_MODE (x))
        make_regs_eqv (regno, REGNO (classp->exp));
   ```
   A copy whose destination has a different mode from its source never joins the source's equivalence
   class, so `canon_reg` (`cse.c:2570`, `first = qty_first_reg[reg_qty[REGNO (x)]]`) cannot forward the
   source register into the copy's later uses. This is what decided the **last** instruction of the
   residual, below.

When the same locals are `int`, neither refusal fires: the assignment is a same-mode copy, the source dies,
`combine_regs` ties them, the copy vanishes — and combine then re-selects the whole counter into the
shifted domain (`lui 0xffff` / `lui 0xf`), which is where the extra 4-instruction gap and the register
scatter came from.

## (c) The move(s) that closed it

1. **Retype the four accumulators `int`/`unsigned int` → `short`, as ONE edit** — `uVar7`, `uVar8`,
   `uVar9`, `iVar3` (renamed `sVar7/sVar8/sVar9/sVar3`); this alone is what emits the five `move`s.
   41 → 34.
2. **Delete the five hand temps the levered text used to spell the truncation** (`w9`, `w7`, `w3`, `w3b`
   and the `+ zr` / `+ 0` sinks): `sVar9 = sVar9 - 1; if (sVar9 < 0) sVar9 = 0xF;` replaces
   `w9 = uVar9 - 1; uVar9 = w9 + 0; if ((int)(w9 << 16) < 0) uVar9 = 0xF;`. Same edit as (1).
3. **Rewrite the shift pair as ordinary short arithmetic**:
   `w = (sVar8 >> 1) + (sVar8 >> 3);` for `((int)(uVar8 << 16) >> 17) + ((int)(uVar8 << 16) >> 19)`
   (`sll v0,s1,0x10` once, then `sra v1,v0,0x11` / `sra v0,v0,0x13`, cse'd). `w` is `int`.
4. **Retype the colour temp `t` to the field's own width, `u8`** — 34 → 1 → **0**. See below.

The `t` step is the whole tail of the crack and is worth its own line. `t` only ever feeds `sb` stores into
`u8` fields of `Frame_80166690_80166690`:
* `unsigned int t` — score 34: each `t = sVar8` becomes a real sign-extension (`sll`/`sra`), 8 instructions
  too many, and it keeps the SImode temp alive so `sVar8 -= 16` grows a spurious `move` of its own.
* `short t` — score **1**: same mode as `sVar7`, so `insert_regs` puts it in `sVar7`'s quantity and
  `canon_reg` rewrites the first store's operand — `sb s0,62(sp)` where the target has `sb v0,62(sp)`.
* `unsigned short t` — score **1**: identical (mode size, not signedness, is the gate).
* `u8 t` — score **0**: HI→QI is a mode change, `cse.c:1030`'s equality fails, the quantities stay apart,
  and both `sb`s read the copy.

## (d) GENERATOR PROPOSAL

> When the residual is **COUNT with mine short by N**, and each missing instruction is a `move rD,rS`
> whose predecessor writes `rS` with an `addiu/addu` and whose successor re-reads `rS` through
> `sll …,0x10`, retype **every local that carries one of those values** from `int`/`unsigned int` to
> `short` in a **single** candidate (a group edit keyed on the residual's own missing-`move` set, not one
> declarator at a time), delete the hand temps that were spelling the truncation, and retype any local
> that only feeds `sb` stores to the destination field's own width (`u8`).

Two sub-rules that make it mechanical:
* **the group rule** — the width move only pays when applied to the whole set at once; `delever_search`'s
  R12 is per-declarator and its single-move scores here were 24/26/30/33 from 34, so its hill-climb could
  never reach the 4-way retype (best over 5 traces and 4,500 compiles: 16).
* **the sink rule** — a local whose every use is a store into a narrow field should be declared at the
  **field's** width, not at `int` and not at the source value's width. `short` vs `u8` was worth exactly
  one instruction here and is decided by `cse.c:1029`'s `GET_MODE` equality, so it is testable in one
  compile: if the residual is a single `sb rS` vs `sb rD` pair, narrow the temp one step.

## (e) What did NOT work (byte evidence)

* `short t` and `unsigned short t` — score 1 each, the `sb s0,62(sp)` / `sb v0,62(sp)` pair above.
* `unsigned int t` (i.e. only the four accumulators narrowed) — score 34, mine 201 / target 193.
* The mechanical search's whole shape (R7 do-while + R9 swap-stmts + single R12 width) — best 16 across
  runs g3/g5/s1/s2/s4/s7/s9. None of those moves is in the final text: the do-while was already right and
  no statement needed exchanging. **The residual class was correct (COUNT) and the family order was
  correct (R12 first) — only the arity of the R12 move was wrong.**
* `int w` vs `unsigned int w` — both score 0; `int` kept for readability.
* Renaming `uVar7/8/9`, `iVar3` → `sVar7/8/9`, `sVar3` — score 0, kept: the `u`/`i` prefixes now lie about
  the type.

Claims proved on bytes: every score above, and the `short`/`u8`/`ushort` A/B/C on `t`.
Claims NOT proved: I did not dump RTL, so `local-alloc.c:1855` and `cse.c:1029` are read from the source
and are consistent with every measurement, but they are inferences from the `--try` scores, not from a
`.lreg`/`.cse` dump. In particular I did not establish why, with `short t`, `canon_reg` forwarded `$s0`
into only the **first** of the two `sb`s and not the second — narrowing to `u8` made the question moot.

## (f) Where the method fell short

* **STEP 0 was unavailable: this pack has no `neighbours.txt`.** I substituted
  `grep -n '@class:\|@stuck:\|@crack:' <the tu>`, but the functions bracketing mine in the file are
  one-line `D_xxxx[*(u16*)(a0+2)]()` dispatchers carrying no note. The pack builder should either always
  emit `neighbours.txt` or the prompt should name the grep as the fallback.
* **The decisive instrument was not in the brief.** The residual's mnemonic diff is printed as a set of
  independent hunks and it hides the fact that the four missing instructions are *the same instruction*.
  Reading the target's whole function off the tree's own object —
  `mipsel-linux-gnu-objdump -drz build/src/<tu>.o` — made the pattern visible in one pass, and the
  branch-delay-slot placement of two of the `move`s (which the hunk view scrambles) was only legible there.
  Recommend adding to HOW TO WORK, before the corpus query: *dump the target function whole from
  `build/` and read it top to bottom against your candidate's `cand.o` under
  `.run/P36/engine/score/<alias>__<fn>/`.*
* The corpus query and the allocation table were not needed: the residual was a COUNT, not a register
  class, and `count first` (4 missing, all one shape) settled it. The register pairs printed in the header
  (`v1->a1 x3`, `s2->v1 x2`, …) were pure noise — a downstream consequence of the missing instructions.
* Total cost: 7 `--try` compiles.

## Bank note

`PACK/body.c` carries a leading `// @class: count` / `// @crack:` header (it scores 0 through
`--try --body`, so the splice accepts it). Drop it if `apply_body_core` splices differently.
The body is shared — `src/shared/ov/func_80166690__8e3d7914.h`, 126 copies.
