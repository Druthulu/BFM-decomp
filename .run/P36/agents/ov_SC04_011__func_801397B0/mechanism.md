# ov_SC04_011:func_801397B0 — the rank-1 residue class (126 copies, one NEEDED pin on `$4`)

**Final: score 2 (ORDER), 89/89 instructions, EVERY register correct, one displaced independent store.**
~700 scored compiles. The mechanical search's best was also 2 but only through `R7 do-while @833`; the
lever-free move below reaches the same 2 with a plain statement relocation and no `do { } while (0)`.
`PACK/body.c` holds that text.

---

## (0) The declaration check (asked for first) — NOT the a2 case

`git grep -n 'func_801397B0' -- src include` → 1770 hits in exactly two forms:
`extern void func_801397B0(s32 a0);` and `extern void func_801397B0(s32 arg0);`. There is **no `(void)`
declaration anywhere in the tree**, and the pin is not on the parameter at all — it is on the *local*
`off` (`register s32 off __asm__("$4")`, `ov_SC04_011_jr_801380E0.c:818`). `func_80168828`'s situation (a
shared header declares the function `(void)`, so no C source can produce a read of `$a0`) does not apply.
Positive proof that this `$4` IS reachable from plain C: **three** different lever-free spellings below
produce the target's complete register assignment (`a1->a0 x10, a0->a1 x7` all closed, class REG → ORDER).

## (a) The residual in one sentence

`body_free.c` compiles to 89/89 instructions with the right opcodes and one exact colour exchange: the byte
index `off` = `((*(u8*)(e+0x20)) - 1) << 2` gets `$a1` and `t2` = `*(s16*)(b164+2)` gets `$a0`; the target
has them the other way round.

## (b) The pass and the decision (`file:line`)

`local-alloc.c` `block_alloc` (:1123-1512). Both contenders are block-0 quantities; MIPS defines no
`REG_ALLOC_ORDER`, so `find_free_reg` scans hard regs in plain regno order (:2158) and whichever quantity is
reached **first** takes `$4` and the other `$5` (`$2/$3` are held across that window by the `andi/sra/ior`
temps). The order is `qty_compare` (:1579): density `floor_log2(refs)*refs*size / (qty_death - qty_birth)`,
ties on qty number = birth order (:1622). `combine_regs` (:1722, tie test :1855) welds
`r85 (lbu) → r86 (addiu −1) → r74 (sll 2) → r76 (b1A8)` into ONE quantity — in every `.lreg` dump all four
carry the same hard register — so the contest is *that whole chain* against `t2`'s single pseudo.

Measured with `tools/alloc_table.py` on `-dl` dumps of the **real spliced TU** (never a standalone compile):

| spelling | `off` r74 | `t2` r78 | colours | score |
|---|---|---|---|---|
| `body_free.c` | 3 refs / 16 insns | 3 / 9 | off→`$a1`, t2→`$a0` | 12 |
| `do { b164 = off + b164; } while (0);` | **4** / 17 | 3 / 9 | off→`$a0` ✓ | 2 |
| zero-store moved out of the `lbu` window | 3 / 16 | 3 / 9 | off→`$a0` ✓ | 2 |

Two **distinct** mechanisms flip it, both byte-proven here:

1. **Loop-note reference weighting.** `flow.c:1401/2067` — `reg_n_refs[regno] += loop_depth`. A zero-trip
   `do { … } while (0)` keeps its `NOTE_INSN_LOOP_BEG/END` through jump1, so every reference inside it is
   counted twice; wrapping any statement that mentions `off` lifts the quantity's density past `t2`'s. Same
   mechanism the P36 ledger recorded for `func_80135D20` (`residual_moves.md`, row "1a-7 / open Q2"). Its
   price is `sched.c:2058-2074`: a mid-block LOOP_BEG/END is **also** a full scheduling barrier, so exactly
   one independent insn is stranded on the wrong side — score 2, class ORDER, for every one of the 60
   contiguous wrap ranges I enumerated.
2. **The source position of the bystander store `*(s32*)((u8*)buf + 0x00) = 0;`** — a lever-free move the
   engine never generates. Enumerating all 11 source positions of that one store, no wrap, no pin: **every
   position above the `off = …` statement and every position below the `t2 = …` load gives the target's
   registers**; only the three positions adjacent to `b164 = off + b164;` keep the wrong ones. Read from the
   post-`sched1` RTL (`-dS`): the failing spellings schedule that store *inside* the `lbu`→`addiu −1`
   interval (`lbu, sym, sw, addiu, sll, addu, lh`), the passing ones do not (`lbu, sym, addiu, sll, addu,
   lh, sw`). `sched1` rewrites `reg_live_length` from its own schedule before local-alloc runs, so one
   store's slot is enough to move the density.

## (c) The move(s) — one line each

* **MOVE A (in `PACK/body.c`, lever-free, readable):** move `*(s32 *)((u8 *)buf + 0x00) = 0;` up to just
  after `e = (u8 *)arg0;` → **score 2**, 89/89, all registers correct; residual = `sw zero,16(sp)` emitted at
  index 3 instead of 6. Identical result for the two other positions above `off = …`.
* **MOVE A′:** the same store moved *down*, below `t2 = *(s16 *)(b164 + 2);` (or any later position) →
  **score 2**, all registers correct, the `sw` at index 10 instead of 6.
* **MOVE B (the search's path):** `do { b164 = off + b164; } while (0);` → **score 2**, `sw` at 9 instead of
  6. Equivalent: `do { b1A8 = (u8 *)&D_80190AB8 + off; } while (0);` (score 2, strands `sh v1,28(sp)` at 21
  instead of 24 instead), and the wraps [15,17], [16,17], [16,24], [28,36].

## (b′) Why the last two instructions did not close — the tight reading

The target emits `sw zero,16(sp)` at index **6**, i.e. *between* the `lbu` and its consumer. That position is
not a free choice of the scheduler, it is forced by the memory dependence, and the dependence is forced by
the store's source position:

* store **after** the `lbu` in source → `anti_dependence` (`sched.c:845`) holds: the load is
  `(mem/s:QI (plus (reg 73) 32))` and the store `(mem:SI (plus (reg 30 $fp) 16))`; the first carve-out needs
  `GET_MODE (mem) != QImode` (it *is* QImode) and the second needs `MEM_IN_STRUCT_P (x) &&
  rtx_addr_varies_p (x)` (the store is not in-struct and `$fp` does not vary) — so neither fires and the
  store can never hoist above the `lbu`.
* store **before** the `lbu` in source → `true_dependence` (`sched.c:817`) holds by the same reading, and the
  store can never sink below the `lbu` — which is exactly the `sw` at index 3 that MOVE A leaves.

So the target's source has that store between `off = …` and `t2 = …`, i.e. **in the position `body_free.c`
already has it** — and in that position no spelling I tried gives `off` the density it needs. Since
local-alloc is deterministic in the post-`sched1` insn stream (identical here, register names aside) and in
`reg_live_length` (rewritten by `sched1` from that same stream), the only input left that can differ is
**`reg_n_refs`**, which `flow.c` computes on the PRE-combine RTL with loop-depth weighting and which no later
pass revises. **Conclusion: the original source gave this chain a fourth reference at flow time — either
through a loop note, or through a pre-combine insn that `combine` later deleted.** Every candidate I could
build for the second half of that disjunction (a copy through a second local, the index expression
duplicated at both uses, a named `u8`/`s32` intermediate, array-ref spellings) either was deleted before
flow (score unchanged, 12) or survived into codegen (32-37). That is the open door for the next agent.

## (d) GENERATOR PROPOSAL (one sentence)

> When the residual is REG-only on the caller-saved bank between a long-lived index chain and a short-lived
> value, generate one candidate per source position of each **bystander statement** in that block — a
> statement with no data dependence on either contender — because moving a single independent insn in or out
> of the interval between the chain's birth insn and its first consumer flips which quantity `block_alloc`
> reaches first, at zero instruction cost and with none of `R7 do-while`'s `sched.c:2058` barrier.

Concretely: add family **R18 "bystander relocation"** (for each single-insn statement S independent of the
contended values, emit "S moved before each other top-level statement of the same block"), and rank it
*ahead* of `R7 do-while` for the REG-caller class — here it closes the same 10 of 12 with a readable move
instead of a zero-trip loop. Bound it to statements whose RTL is one insn; cost is O(n²) compiles in the
block's statement count (11 compiles closed it here). Second, smaller rule: when an `R7 do-while` child
returns class ORDER with distance 1, do **not** treat it as a dead end — retry the same wrap on every *other*
statement that references the same value (5 such wraps here, each stranding a different insn) and pick the
one whose barrier falls where the target stream shows no crossing.

## (e) What did NOT work — byte evidence (all via `delever_search --try`)

| tried | score | why |
|---|---|---|
| merge the two `b164` statements into one initializer | 12 | identical RTL after cse |
| reuse the parameter as the offset (`arg0 = (…) << 2;`, drop `off`) | 12 | cse renames the reassigned parm; no `$4` copy-suggestion survives (`combine_regs` :1798 needs a block-local sreg, `e` is global) |
| `{ … }` plain block at both do-while sites | 12 | a block emits no LOOP note → no ref weighting (the control for mechanism 1) |
| move `b1A8 = … + off;` up (7 placements, wrapped and plain) | 12–43 | `sched1` rewrites `reg_live_length`; `off` stays 3 refs / 16 insns |
| `off` as `u32`/`int`/`short`/`s16`; `t2` as `int`/`u16`/`s16`/`short`/`u32` | 12–13 | no density change (13 = an added extend) |
| `off` declaration moved to 5 other slots | 12 | declaration order does not reach `block_alloc` here |
| swap the `t2`/`t0` loads; `*(s16*)b164`; `e[0x20]`; `buf[0] = 0`; `*buf = 0` | 12 | same RTL / same MEM flags |
| inline `hi`, `lo`, `t0`, `uu`, `vv`; reorder the three `|` terms; `hi |=` accumulation | 12–32 | changes the `or` tree (COUNT) |
| a named `u8`/`s32`/`int` temp for the `lbu` or for `x−1` | 32 | the copy survives cse *and* combine — 3 extra insns |
| a second local copying `off` (`off2 = off;`) | 12 | deleted before flow; `off` still 3 refs |
| the index expression duplicated at both uses (no `off` variable) | 37 | cse cannot reuse the load across the intervening `buf` stores → a whole second `lbu/addiu/sll` |
| the `b1A8` loads written inline off `&D_80190AB8 + off (+2)` | 19 | fold reassociates `(sym+off)+2` to `(sym+2)+off` → a second `addu` |
| do-while over all 60 contiguous statement ranges containing an `off` reference | 2 (best) | every flip strands exactly one independent insn |
| depth-1 sweeps of the engine's full `ALL_FAMILIES` generator (169 + 166 + 164 candidates) from each of the three score-2 nodes | 2 (best) | no second move recovers the stranded insn |

## (f) Where the method fell short

1. **`history.txt` records a move name and a score, not the residual the move left.** `R7 do-while @833 -> 2`
   hid the fact that the class had already changed REG → ORDER, i.e. 10 of the 12 were closed and the body
   was one bystander insn away. One `--explain --path` call (0.6 s) revealed it. The trace should carry each
   child's residual class and first differing mnemonic.
2. **The search's move families are all anchored on the lever site** (`delever.py:2448`, "the lever says
   where to look"). The move that closes 10 of 12 here touches a statement with no relation to the pin. For
   a `block_alloc` density residual, locality is the wrong prior: the density comes from the schedule, and
   the schedule comes from every insn in the block.
3. **`sites.txt` names the pinned register but not its opponent.** Naming `t2` and printing both contenders'
   `.lreg` lines would have made the first hypothesis the right one; a third of the budget went to deriving
   `qty_compare` by hand before dumping `.lreg` on the spliced TU. `tools/alloc_table.py` output against the
   `--try` scratch object belongs in the pack.
4. **`residual_moves.md` rows 1a-1 / 2a-1 state the density arithmetic per REGISTER; `qty_compare` is per
   QUANTITY** (`combine_regs` sums `qty_n_refs` and keeps UREG's birth). The per-register `.lreg` numbers
   mis-rank these two contenders — 0.19 vs 0.33 in *both* the flipped and the unflipped compile — so a tool
   that reads them literally will predict the wrong winner. Either the map should say so or
   `alloc_table.py` should group registers into quantities (it can: the pseudos of one quantity all print the
   same hard register in `.lreg`).
5. **No instrument prints `reg_n_refs` as flow computed it, before combine.** That single number is the one
   remaining degree of freedom in this residual (see (b′)); a `-df`-based counter of references per pseudo in
   the `.flow` dump, diffed against the `.lreg` number, would say immediately whether a candidate spelling
   bought the fourth reference — instead of inferring it from the colour that came out.
