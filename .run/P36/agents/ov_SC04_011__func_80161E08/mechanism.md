# func_80161E08 (src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c) — score 0, MATCH

3 `__asm__("move %0,%1")` levers removed. `--try` score **0** (mine 175 ins, target 175).
The same rewrite also closes the sibling **func_80162438** in the same TU at score 0
(160/160), removing 3 more `register u8 *t __asm__("$2")` pins. 6 lever sites, one reading.

## (a) The residual in one sentence

COUNT, mine 172 / target 175: in each of the three guarded blocks the target computes the
stored pointer into a scratch `$v0` and then copies it (`addiu v0,s2,off` ; `move s1,v0`),
while every natural spelling of `p = base + off;` folds the copy away into a single
`addiu s1,s2,off` — **three instructions MISSING, not miscoloured** (COUNT FIRST: the count of
missing `move`s equals the number of blocks, i.e. the number of times the value is both
*stored to the table* and *kept in a variable*).

## (b) The pass and the decision, read from the compiler's source, proven on the dumps

The scratch register survives because the value has **two consumers**, and the merge that
would remove it is only ever offered to the *first* one.

1. **expand** — `expr.c`, `expand_assignment` with `want_value`: `p = (D_801EDBB0[i] = X)`
   materialises `X` in a *compiler* temp T (`reg:SI 100`, no `/v`), stores T, then copies
   T into the *user* pseudo `p` (`reg/v:SI 74`). Proven: `scratch/dumps/dumps_v4/v4.i.flow`
   insns 70 / 74 / 76. In the plain `p = base + off;` spelling there is no temp at all —
   `v2.i.flow` insn 68 sets `reg/v:SI 74` directly, so there is nothing to fold and nothing
   to keep (that is why a bare temp `t = base+off; p = t;` also scores 15: it is propagated
   away before flow even runs — see (e)).
2. **flow** — `flow.c` gives T's def exactly one LOG_LINK, to its **first** use, the store:
   `v4.i.flow` insn 74 carries `(insn_list 68 (insn_list 70 (nil)))`, insn 76 (the copy)
   carries **none**. combine walks LOG_LINKS, so the pair (addiu → copy) is never even
   proposed. The pair it *is* offered, (addiu → store), fails because `(set (mem …) (plus …))`
   is not a `sw` (`combine.c` `recog_for_combine`). Belt and braces: were the link there,
   `added_sets_2 = ! dead_or_set_p (i3, i2dest)` — **`combine.c:1458`** — would be true (T is
   still live at the store), forcing combine to keep I2's set inside the merged pattern and
   producing a two-SET PARALLEL that MIPS cannot recognise.
   Proven: `v4.i.combine` still shows insns 70 / 74 / 76 unchanged.
3. **sched** (first pass) sinks the store below the copy to cover the `la` argument setup:
   `v4.i.sched` insn order 70, 76, 83, …, 74.
4. **local-alloc** — `optimize_reg_copy_2` (**`local-alloc.c:874`**, called at `local-alloc.c:1015`)
   then rewrites the *store's* source from T to `p`, which is why the target stores `$s1` and
   not `$v0`: `v4.i.lreg` insn 74 is `(set (mem D_801EDBB0) (reg/v:SI 74))`. T's only remaining
   use is the copy — but combine is long past, so the copy stays. `combine_regs` cannot tie the
   two: it only tables block-local pseudos (`reg_basic_block[regno] >= 0`, `local-alloc.c:992`)
   and `p` spans three blocks.
5. **global-alloc** — `tools/alloc_table.py v4 func_80161E08` prints `r74  pri 11250.0  refs 9
   live 24  blk None  ; dies in 3 places; crosses 4 calls` → a global allocno on the
   callee-saved bank, `$s1`; T is block-local, dead at once, no calls crossed → `$v0`.
   Hence `addiu $v0,$s2,off ; move $s1,$v0`.

## (c) The move that closed it

- Fold the table store into the assignment so the pointer has two consumers:
  `p = base + 0x65A8; D_801EDBB0[0] = p;`  →  `p = D_801EDBB0[0] = base + 0x65A8;`  (×3, one per block).

Equally byte-identical (score 0), kept here as the alternative spelling if the chained
assignment is judged less readable: store, then read the slot back —
`D_801EDBB0[0] = base + 0x65A8; p = D_801EDBB0[0];` (cse's store-to-load forward produces the
same RTL). The chained form was banked: one line instead of two, and it does not depend on cse.

## (d) GENERATOR PROPOSAL

**When the residual is COUNT with `mine: addiu <callee-saved>,<base>,K` against
`target: addiu <caller-saved>,<base>,K ; move <callee-saved>,<caller-saved>` (a missing
reg-reg copy of a value that the body both STORES to a global/array slot and KEEPS in a
variable), rewrite the pair `v = <expr>; <slot> = v;` as the chained assignment
`v = <slot> = <expr>;`** — that gives the value a second consumer, so flow hands the only
LOG_LINK to the store and combine never folds the copy. Mechanically detectable: the two
adjacent statements share the identical RHS variable, and the diff's extra `move`'s
destination is the variable's register.

Scope measured: closes `func_80161E08` (3 sites) and, unchanged, `func_80162438` (3 `$2`
pins, score 0) in the same TU — the two are the same shape over `D_801EDBB0[]` / `D_801EDC08[]`.
Eight further TUs in ov_SC04_011 declare `extern int D_801EDC08[]` and are worth the same probe.

## (e) What did NOT work, with byte evidence

| spelling | score | why |
|---|---|---|
| `body_free.c` (`p = base + off;`) | 15 | one pseudo, one `addiu $s1` |
| block-local `u8 *t = base+off; p = t;` (`v1`) | 15 | T has ONE use; the copy is propagated away before flow (`v2.i.flow` insn 68 already sets `reg/v 74` directly) |
| function-scope `t` (`v2`) | 15 | identical to v1 |
| `D_801EDBB0[i] = p = base+off;` (`v3`) | 15 | wrong nesting: the copy into `p` is the INNER assignment, so `p` is the only pseudo again |
| `t = base+off; D_801EDBB0[i] = t; p = t;` (`v7`) | 6 (REG-caller, 175 ins) | the copy DOES survive (count right) but the explicit temp is live across the store at allocation time and lands `$a0`, not `$v0` — `a0->v0 ×6`. Order matters: the copy must be adjacent to the def |
| drop `p`, re-read `D_801EDBB0[i]` at the use site (`v6`) | 30 (174 ins) | the calls invalidate the memory, so cse reloads: `lw` instead of `move`, plus `s1->s0 ×2` |
| `p = D_801EDBB0[i] = base+off;` (`v4`) | **0** | banked |
| `D_801EDBB0[i] = base+off; p = D_801EDBB0[i];` (`v5`) | **0** | alternative |

## (f) Where the method fell short

- **`neighbours.txt` was not in this pack** (only `tu.txt`, `body_tree.c`, `body_free.c`,
  `residual.txt`, `sites.txt`, `history.txt`, `tu_free.c`). STEP 0 still paid for itself: the
  function's own comment header at `ov_SC04_011_jr_8015C32C.c:3555` names the residual exactly
  ("target computes each pointer into scratch `$v0` then `addu $s1,$v0` … natural C ALWAYS
  coalesces that copy"), and `grep -n D_801EDBB0 <tu>` found the sibling `func_80162438` whose
  header at :3780 repeats it. Both headers, however, assert the crack is **impossible** without
  an inline-asm `move` — that conclusion is now refuted on bytes. **A `@stuck:` note that says
  "needs a lever" should be re-tested, not trusted**; ship `neighbours.txt` in every pack.
- The mechanical search's 2,070-compile trace (`history.txt`) never reached 13→0 because its
  generator families all move *statements* (swap, hoist, block, width, param-copy); none of them
  **fuses two statements into one expression**. That is the missing family, and (d) is its rule.
- The residual text alone cannot distinguish "the copy is missing" from "the registers are
  wrong". Counting first (172 vs 175, three blocks, one `move` each) settled it in one step, and
  `objdump -drz build/src/.../ov_SC04_011_jr_8015C32C.o` on the *built* object gave the exact
  target neighbourhood the residual elides — worth making a standard pack file.

## Files

- `PACK/body.c` — the banked text (`.run/P36/agents/ov_SC04_011__func_80161E08/body.c`)
- `PACK/mechanism.md` — this file
- `PACK/scratch/` — v1…v7 candidates, `sib.c` (the proven func_80162438 rewrite), `dumps/` (cc1 `-df -dl -dg` for v2 and v4), `mk.py`/`mk2.py`/`run.sh`
