# func_80162438 (ov_SC04_011_jr_8015C32C.c) — MATCH, score 0, no levers

`.venv/bin/python tools/delever_search.py --try src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c func_80162438 PACK/body.c --body`
-> `score 0 (OTHER; mine 160 ins, target 160) — MATCH`.
Three `register u8 *t __asm__("$2")` pins (NEEDED at tree lines 3836 / 3847 / 3858) are gone; no `asm`, no added
`volatile`, no `__builtin_*`. 127 copies ride on this body.

## (a) The residual in one sentence

Three times over — once per `if (D_800B5xx == 0)` block — the target computes the item address into the **caller-saved**
`v0` and then copies it into the callee-saved `s1` (`addiu v0,s2,26024` / `move s1,v0`), while the lever-free text
computes it straight into `s1` (`addiu s1,s2,26024`): the target keeps a **register-to-register copy that my spelling let
gcc delete**, so mine is 157 instructions against 160 (class COUNT, score 10).

Counted first, per the brief: 3 instructions missing, all of them the same `move`, all at the same position in three
near-identical blocks — an insn-count defect, not a register-assignment one.

## (b) The pass and the decision, from the compiler's own source

`tools/reference/gcc-2.7.2/cse.c:7440-7501`, the block commented *"Special handling for (set REG0 REG1) where REG0 is
the 'cheapest', cheaper than REG1"*. Its guard is at **`cse.c:7454-7460`**:

```c
  if (n_sets == 1 && sets[0].rtl && GET_CODE (SET_DEST (sets[0].rtl)) == REG
      && NEXT_INSN (PREV_INSN (insn)) == insn
      && GET_CODE (SET_SRC (sets[0].rtl)) == REG
      && REGNO (SET_SRC (sets[0].rtl)) >= FIRST_PSEUDO_REGISTER
      && REGNO_QTY_VALID_P (REGNO (SET_SRC (sets[0].rtl)))
      && (qty_first_reg[reg_qty[REGNO (SET_SRC (sets[0].rtl))]]
	  == REGNO (SET_DEST (sets[0].rtl))))
    {
      rtx prev = PREV_INSN (insn);
      while (prev && GET_CODE (prev) == NOTE)
	prev = PREV_INSN (prev);
      if (prev && GET_CODE (prev) == INSN && GET_CODE (PATTERN (prev)) == SET
	  && SET_DEST (PATTERN (prev)) == SET_SRC (sets[0].rtl))
	{ ... validate_change (prev, & SET_DEST (PATTERN (prev)), dest, 1); ... }
```

On `t = base + 0x65A8; item = t;` every clause holds: the copy's source is a pseudo, `item` is `qty_first_reg` of the
quantity (`make_regs_eqv`, `cse.c:826-855`, promotes the **longer-lived, cross-block** pseudo to canonical: `item` is
written in all three blocks so `uid_cuid[regno_last_uid[item]] > cse_basic_block_end`), and **`prev` — the insn
immediately before the copy, notes skipped — is the `addiu` itself**. cse therefore rewrites the `addiu` to set `item`
directly and the copy becomes a dead store. PROVEN in the dumps: `body_free.c` enters cse as
`(insn 33 (set (reg/v 79) (plus (reg/v 74) 26024)))` + `(insn 36 (set (reg/v 75) (reg/v 79)))` and leaves it as a single
`(insn 33 (set (reg/v 75) (plus (reg/v 74) 26024)))` — the pin worked only because a hard `$2` fails the
`REGNO(SET_SRC) >= FIRST_PSEUDO_REGISTER` clause.

Break that adjacency and a second gate must also be cleared, or `combine` folds the copy instead: LOG_LINKS are built in
**`flow.c:2076-2091`** (`/* Make a logical link from the next following insn that uses this register, back to this
insn. */`) and only for **`y = reg_next_use[regno]`, the FIRST following use**. Put a use of the computed value between
the `addiu` and the copy and the single link lands on that use, so the copy carries no link back to the `addiu` and
`try_combine` is never offered the pair.

The rest is downhill and byte-confirmed in `PACK/scratch/m_{sched,lreg,greg}.txt`:
* `sched.c` sched1 sinks the store below the surviving copy;
* `local-alloc.c:1005` calls **`optimize_reg_copy_1` (`local-alloc.c:711-800`, the replace at `:771`)** on the copy whose
  source is *not* dead there — it rewrites the later store to read the copy's destination, which is why the target
  prints `sw s1,0(at)` and not `sw v0,0(at)`;
* the now short-lived `addiu` pseudo is block-local and takes the first free caller-saved colour, `v0`
  (`find_free_reg`, `local-alloc.c:2158`), while `item` crosses two calls and global alloc gives it `s1`;
* `reorg.c` `fill_slots_from_thread` steals the `addiu` into the `bnez` delay slot — legal precisely because it now
  writes `v0`, dead on the taken path.

## (c) The move that closed it

**In each of the three blocks, the store to `D_801EDC08[i]` was moved ABOVE the assignment to `item` and rewritten to
store the expression instead of the variable** — one statement exchange per block, and the `u8 *t` temp falls out:

```c
-   u8 *t = base + 0x65A8;
-   item = t;
-   D_801EDC08[0] = (s32)item;
+   D_801EDC08[0] = (s32)(base + 0x65A8);
+   item = base + 0x65A8;
```

## (d) GENERATOR PROPOSAL

**R20 `consumer_first`** — when the residual is COUNT-short by exactly one `move <callee-saved>,<caller-saved>` per site
and mine emits the target's `addiu`/`li` straight into the callee-saved register, take each statement `V = E;` whose
value is read by the very next statement `S` and offer `S[E/V]; V = E;` (the consumer hoisted above the assignment, with
`E` — or the temp holding it — substituted for `V` inside it); `V` must be a variable live beyond the enclosing block
and `E` must be side-effect-free.

This family is **invisible to the existing search**: `R9 swap-stmts` refuses the exchange because the two statements
share the identifier `V` (its independence guard), and a bare textual swap would read `V` before it is written. The
operand substitution is the whole content of the move, and it is what a search over statement order can never produce.
Two independent spellings of the same rule reach score 0 here (`PACK/scratch/final_A.c`, `final_B.c`), so the generator
can emit either the temp-free form or the keep-the-temp form.

## (e) What did NOT work, with byte evidence (`PACK/scratch/v{1,3,5}.py`)

Every spelling that leaves the copy adjacent to its `addiu` compiles to 157 instructions — score 10, unchanged:
`u8 *t = ...; item = t;` (the baseline), `register u8 *t`, `u8 *t; t = ...; item = t;`, `item = base; item = t + OFF`,
`item = &base[OFF]`, `s32 tv = (s32)base + OFF; item = (u8 *)tv`, `item = base + OFF` alone, a two-link chain
`t -> u -> item`, `D_801EDC08[i] = (s32)(item = base + OFF)`, and a dead `u8 *t` declared before the assignment.
Making `item` block-local instead (three per-block declarations) does not add the `move` either — it only swaps
`s0`/`s1` throughout and scores **22** (`va` dump: cse canonicalises the other way, to the temp).
Putting the second use **after** the copy — `t = ...; item = t; D_801EDC08[i] = (s32)t;` — is still 157: the use must be
**before** the copy, not merely present. An unrelated store between the two (`D_800B5BFF = 1;`) does keep the copy alive
but displaces six other instructions (166, score 37), so the generator should hoist a *consumer*, not any bystander.
R19 was checked first and refuted: `func_80024054`, `func_8001CE28`, `func_8001CE68`, `func_800242D0`, `func_801626B8`
and `func_800291DC` all match their real definitions in `src/800.c` / `src/shared/ov/` at arity 2, 2, 2, 3, 0, 1 — no
argument was dropped here, and the pins sat on `$2`, not `$4-$7`.

## (f) Where the method fell short

* The allocation table would not have helped and was not the instrument: the defect was a **missing instruction**, and
  the brief's own warning ("the residual text alone cannot tell you whether an INSTRUCTION IS MISSING or the REGISTERS
  ARE WRONG — count first") is what routed me to cse instead of `alloc_table.py`.
* What actually cracked it was neither the residual nor the compiler source alone but a **corpus query**: disassembling
  all 4,199 built objects and grepping for `addiu vN,<reg>,imm` + `move sM,vN` (`PACK/scratch/scan2.py`). 5,351 hits;
  the ones with *different* source and destination registers led to `func_8017FD14`
  (`src/ov_SC01_077/ov_SC01_077_jr_8017AE2C.c:5568`), an already-matched body whose lever-free lines
  `tags[0] = (s32)(prim + 0xC); pp = prim + 0xC;` are this exact shape — store first, assignment second. That corpus
  scan is worth a tool: **"find an already-banked function whose bytes contain my residual's shape, and read its C."**
* The pack's `history.txt` shows why the search stalled at 8: its best single moves were `R9 swap-stmts` at lines 3845 /
  3863-3865 — the unrelated `D_800B5xx = 1;` stores — because the one exchange that matters (`item = t;` against its own
  consumer) is exactly the one R9's shared-identifier guard forbids.
