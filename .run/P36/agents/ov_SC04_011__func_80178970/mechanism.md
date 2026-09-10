# func_80178970 (ov_SC04_011) — the call-result copy that `combine` deletes

**Final score: 2** (lever-free start 6; mechanical best 3). **NOT a bank.** The `$2` pin is
NEEDED-BY-CONSTRUCTION: no plain-C body can produce the missing instruction. Evidence below.

## (a) The residual in one sentence

The target keeps the call-result copy `move v1,v0` and so returns its answer in `$v0`; my lever-free
body has that copy deleted, which pins the call result to `$v0` for the whole test and pushes the
result variable to `$v1`, costing one instruction (14 vs 15) plus a trailing `move v0,v1`.

Target (`build/src/ov_SC04_011/ov_SC04_011_jr_801734BC.o`, `func_80178970`):

    jal func_801789AC / nop
    move  v1,v0          <-- the copy:  v  = call result, in $v1
    beqz  v1,54e0
    move  v0,zero        <-- delay slot: r = 0,           in $v0
    lui/lh v0,D_801F1638 / nop
    sltiu v0,v0,1        <-- r = (D_801F1638 == 0),       in $v0
    lw ra / addiu sp / jr ra / nop

Both `r` and `v` want `$v0`; the whole residual is which one gets it.

## (b) The pass and the decision (`file:line`), read then proved on bytes

**Pass: `combine`, not either allocator.** Bisecting the cc1 pass dumps (`-dr -dj -dc -dl -dg`, faithful
minimal TU, calibrated: it reproduces the tree's own 14-instruction output exactly) shows the copy
`(set (reg/v:SI 73) (reg:SI 2 v0))` alive through `.rtl`, `.jump`, `.cse`, `.loop`, `.flow`, and **gone in
`.combine`**, substituted into the branch as `(if_then_else (eq (reg:SI 2 v0) (const_int 0)))`.

`can_combine_p`, **`tools/reference/gcc-2.7.2/combine.c:914-917`**:

    || (! all_adjacent
        && (((GET_CODE (src) != MEM || ! find_reg_note (insn, REG_EQUIV, src))
             && use_crosses_set_p (src, INSN_CUID (insn)))       <-- :917

`use_crosses_set_p` (**combine.c:10127-10130**) returns 1 only if some insn *between* the copy and its use
sets a register named in `src` — here `src` is the hard register `$v0`. The MIPS port never fires the
neighbouring "don't extend the life of a hard register" guard (**combine.c:944-957**), because that arm is
`#ifdef SMALL_REGISTER_CLASSES`, which `config/mips/mips.h` does not define. So on MIPS a call-result copy
whose pseudo dies at its single use is **always** folded into that use, and `$v0` stays live to the test.

Downstream consequence, read from the `.greg` dump of the free body:

    ;; 1 regs to allocate: 72        (72 = r)
    ;; 72 conflicts: 72 2 29         <-- conflicts with hard reg 2

`r` is cross-block (set in bb0 and bb1, used in bb2), so local-alloc skips it and `global.c`'s `find_reg`
(**global.c:962-970**, first fit in `regno` order) takes the lowest hard reg not in `used`; `$v0` is in the
conflict set, so `r` gets `$v1` and the return needs `move v0,v1`.

**Proved on bytes.** With the tree's pin `register int r __asm__("$2")`, `r = 0` expands to
`(set (reg/v:SI 2 v0) (const_int 0))` — a *hard* `$v0` write sitting between the copy and the branch — and
the `.combine` dump shows insn 11 surviving verbatim, giving `move $3,$2 / beq $3,$0 / move $2,$0`.
`--try` on `body_tree.c` scores **0**; on every lever-free spelling it scores >= 2.

## (c) The source move that got closest (6 -> 2)

**Early return: sink the result variable's zero-initialiser past the branch by turning
`r = 0; if (c) r = E; return r;` into `if (c) return E; return 0;`.**

That drops the residual from 6 to 2 and deletes the variable `r` entirely: the two `return`s write
`(reg/i:SI 2 v0)` directly, so nothing is left to conflict with `$v0`, the trailing `move v0,v1` and the
register swap all disappear, and the remaining difference is exactly the one missing `move v1,v0`.
It is also strictly more readable than the pinned original. It is *not* bankable (score 2).

## (d) GENERATOR PROPOSAL (one sentence)

**R-early-return:** when the residual is COUNT with `mine = target - 1` and the only register pair is
`result_reg` swapped between `$v0`/`$v1`, rewrite the function's single result variable
`T r; r = K; if (c) r = E; return r;` into `if (c) return E; return K;` — and, when the one remaining
missing instruction is a `move $vN,$v0` immediately after a `jal`, **stop the search and mark the `$2` pin
NEEDED-BY-CONSTRUCTION** (see (e)), instead of spending the 400-compile budget.

The classifier for the second half is exact and cheap: *residual class COUNT, `mine = target - 1`, the sole
inserted target instruction is a register-register `move` whose source is `$v0` and which is the first
instruction after a `jal`'s delay slot.* That shape is unreachable in plain C on this compiler; recognising
it converts a wasted search into a one-line verdict. `sites.txt` here already says `NEEDED`, and 127 copies
of this body share the shape — the classifier retires all of them at once.

## (e) What did NOT work, and why it cannot (byte evidence)

For the copy to survive, an insn between it and the test must set the hard register `$v0`
(combine.c:917). In plain C on gcc 2.7.2/MIPS only two things write `$v0`: a `call`, and a `return`
statement (`expand_return` emits `(set (reg/i:SI 2 v0) ...)` directly — visible as insn 32 in the
early-return body's `.cse` dump). A `return`'s hard write is always emitted *after* the branch that guards
it, and adding a call adds a `jal`. Hence no plain-C body can place a `$v0` write in that window; only the
`register … __asm__("$2")` pin can, which is exactly what `sites.txt` records.

~40 spellings scored with `--try` (each ~0.8 s). Every family and its best score:

| family | spelling | score |
|---|---|---|
| baseline (lever-free) | `v=call(); r=0; if(v) r=D==0; return r;` | 6 |
| **early return** | `if (v) return D==0; return 0;` (also `if(!v)`-form, braces, `!D`, `unsigned v`, `else return 0`, extra block) | **2** |
| merge `r` and `v` | `r=call(); if(r) r=D==0; return r;` / `r=v;` / `if(v) v=D==0; return v;` | 3 |
| declaration order / decl-first | `int v; int r;` swapped, one-line, initialiser form | 6 |
| `r` initialised before the call | `r=0; v=call();` | 10 (spills to `$s0`) |
| call inlined into the test | `if (call()) r=D==0;` | 10 (`r` crosses the call -> `$s0`) |
| ternary / `?:` / if-else assigning `r` | `r = v ? (D==0) : 0;`, `if/else` both arms | 5 |
| statement-order & control-flow barriers | `goto`, label, `while(v){…break;}`, `for(;;)`, `do/while(0)`, `switch` | 6 (all flattened by `jump.c` before combine) |
| second use of `v` to block combine | `return v;` / `else r = v;` | 2 (cse's `record_jump_equiv` folds `v` to `0` on the taken path *before* combine, so the second use is gone) |
| second use that survives cse | `r = v;` (merges the two pseudos) | 3 (survives combine — `.combine` keeps insn 11 — but then one pseudo takes `$v0` and regalloc coalesces the copy away) |
| `register` keyword (plain C, no asm) | `register int r;` / `register int v;` | 6 / 2 — **no effect**, as `combine.c:951` predicts (`SMALL_REGISTER_CLASSES` undefined on MIPS) |
| temp for the condition | `c = v != 0; if (c) …` | 3-6 |
| reuse `v` in the taken arm | `v = D_801F1638; r = v == 0;` | 6 |

Two of these are worth keeping as measured facts: the `r = v` spelling **does** keep the copy past combine
(so the combine reading is falsifiable and was falsified in the right direction), and the plain `register`
keyword provably does nothing at `-O2` on this port.

## (f) Where the method fell short

1. **The brief points at the wrong pass.** It sends you to `local-alloc`/`global`/`alloc_table.py` for a
   register-swap residual. Here the deciding pass was `combine`, three passes earlier, and the allocator
   behaviour was a *consequence*. The step that actually solved it — grep each `-d*` dump for the differing
   insn and report the first pass in which it disappears — is one shell line and should be a tool
   (`tools/pass_bisect.py <tu> <fn> <insn-pattern>`), shipped inside the pack. Everything after that
   reading was mechanical.
2. **The pack does not carry the target's own listing.** `residual.txt` prints only the differing blocks, so
   the first thing I did was `objdump -drz build/.../*.o`. Fifteen lines of target mnemonics in the pack
   would remove that step from every agent.
3. **`residual.txt` splits one decision into three rows.** The "register pairs `v1->v0 x1`", the missing
   instruction and the two tail rows are all one fact. A `COUNT` residual whose inserted instruction is a
   `move` from a call's return register deserves its own printed class.
4. **Tool bug (affects every parallel agent).** `--try` failed twice with
   `FileNotFoundError: .run/P36/delever/includers_cache.tmp -> includers_cache.json` at
   `tools/delever.py:657`: the temp file has a fixed name, so concurrent agents clobber each other's
   `os.replace`. Use `tempfile.mkstemp` in the same directory (or an flock) — with ~20 agents running this
   silently costs retries and could be mistaken for a candidate that "crashes the compiler".
