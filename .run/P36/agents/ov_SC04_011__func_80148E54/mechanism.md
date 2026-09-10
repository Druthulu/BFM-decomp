# func_80148E54 (ov_SC04_011 / src/ov_SC04_011/ov_SC04_011_after.c) — T7 residue

**Status: NOT CLOSED. Best score 6 (COUNT; mine 66 ins, target 67)** — the untouched lever-free text,
cleaned (`PACK/body.c`, one variable, the stale `// !FAKE:` comment dropped). The mechanical search's
best of 4 (`R14 param-width arg0 s32->u16` + `R10 param-copy arg0`) is a *worse* body: it lies about
the parameter's type, does not restore the missing instruction, and buys its 2 points by shifting the
`lbu` base. ~90 hand-reasoned spellings were compiled through `--try` this session; the mechanism is
now read from the compiler's source AND from the RTL dumps, and the class is argued **unreachable
body-only** for this particular function. The same is true of its twin `func_80148D44`.

## (a) The residual in one sentence

The target computes the masked angle into a caller-saved register and then copies it into the
callee-saved register that carries it across the switch — `andi a0,v0,0xfff` … `move s1,a0`, the copy
landing in the delay slot of the first dispatch branch — while every lever-free spelling folds the
copy away and writes `andi s1,v0,0xfff` directly, one instruction short (66 vs 67).

```
target                    mine
addiu v0,v0,-1024         addiu v0,v0,-1024
andi  a0,v0,0xfff         andi  s1,v0,0xfff
lbu   v1,169(s0)          lbu   v1,169(s0)
li    v0,83               li    v0,83
beq   v1,v0,3628          beq   v1,v0,3624
move  s1,a0     <- extra  slti  v0,v1,84      (reorg fills the slot from the fall-through)
```

The copy is **unconditional and in the entry block** — proven, not assumed: it is in the delay slot of
`beq v1,v0,3628`, and it cannot have been stolen from that branch's target thread because the 0x73
branch at `0x35e4` reaches the same target `0x3628` with a `nop` slot and still needs `s1`. And the
producer's value has **exactly one use** in the whole target: `a0` is written at `0x35b0` and read only
at `0x35c0` (`s1` likewise: written `0x35c0`, read once at `0x3660`).

## (b) The passes and the decisions — two killers, both dump-verified

**Killer 1 — cse1, `cse.c:7439-7502`** ("Special handling for `(set REG0 REG1)` where REG0 is the
cheapest"). The guard is
```c
  if (n_sets == 1 && … GET_CODE (SET_SRC (sets[0].rtl)) == REG
      && NEXT_INSN (PREV_INSN (insn)) == insn
      && … (qty_first_reg[reg_qty[REGNO (SET_SRC …)]] == REGNO (SET_DEST …)))
    { rtx prev = PREV_INSN (insn); while (prev && GET_CODE (prev) == NOTE) prev = PREV_INSN (prev);
      if (prev && GET_CODE (prev) == INSN && SET_DEST (PATTERN (prev)) == SET_SRC (sets[0].rtl)) { … } }
```
It rewrites the *producer's* destination to the copy's destination and turns the copy into a dead
store. **Verified on the real spliced TU:** `.jump` holds
`(insn 40 (set (reg/v:SI 73) (and:SI (reg:SI 85) (const_int 4095))))` followed by
`(insn 43 (set (reg/v:SI 86) (reg/v:SI 73)))`; in `.cse` insn 43 is gone and insn 40 sets reg 86
directly. So §455's reading — "combine merges a single-use def into its copy" — names the wrong pass
for the adjacent case: **cse gets there first**, and its precondition is `prev` (skipping only NOTEs).

**Killer 2 — combine, `combine.c:1458` + `flow.c:2086-2091`.** Break cse's adjacency (put any real insn
between producer and copy) and cse leaves the copy alone — but then `try_combine (i3 = the copy,
i2 = the producer)` fires: `added_sets_2 = ! dead_or_set_p (i3, i2dest)` is 0 because the producer dies
at the copy, the substitution recognises as `andsi3`, and i2 is deleted. **Verified on dumps** with
`s32 k = *(u8 *)(arg0 + 0xA9);` inserted between them (variant `w4`): the copy is still present in
`.cse`, and `.combine` shows `(insn 47 (set (reg/v:SI 86) (and:SI (reg:SI 85) (const_int 4095))))`
with insn 40 a `NOTE_INSN_DELETED`.

**The three blockers `can_combine_p` actually admits** (`combine.c:803-960`), i.e. the complete
lever-free option set:
1. **No LOG_LINK** — `flow.c:2086` builds one only when `y && (BLOCK_NUM (y) == blocknum)`, so a real
   `CODE_LABEL` between producer and copy blocks combine outright.
2. **The producer still live at the copy** — `dead_or_set_p` false ⇒ `added_sets_2` ⇒ the merged
   pattern would be a PARALLEL of two sets, unrecognisable on MIPS ⇒ combine fails.
3. **A CALL between them** — `combine.c:929`, `INSN_CUID (insn) < last_call_cuid && ! CONSTANT_P (src)`.
(The tree body uses a fourth, forbidden one: the `launder` `asm` on `$4` sits between them and
`can_combine_p` refuses ASM_OPERANDS, `combine.c:868-870`. `.combine` for the tree body shows
`(insn 42 (set (reg/v:SI 4 a0) (and …)))`, `(insn 44 asm_operands)`, `(insn 47 (set (reg/v:SI 87)
(reg/v:SI 4 a0)))`, and sched1 then sinks insn 47 past the `lbu`/`li` so reorg can fill the slot.)

**Why the register is `a0` and not `v0` is NOT a separate problem.** With the launder but *no* pin
(diagnostic `d1`) the copy survives, but sched1 keeps it adjacent to the producer and local-alloc gives
the short-lived quantity `v0` — score 4, `andi v0,v0,0xfff ; move s1,v0`. In the target the copy is
scheduled *after* `li v0,83`, so `v0` is occupied and first-fit hands out `a0`. The colour follows the
schedule; **the only real problem is keeping the copy at all.**

## (c) Why this body cannot pay for any of the three blockers

- **Blocker 2 (a second read) has no free home.** The producer's value has exactly one consumer in the
  target's 67 instructions, and every instruction in the entry block is accounted for (`lbu`, `li`,
  `beq`). Any second read costs an instruction. Worse, per agent a-80166F58's Step 3 (independently
  confirmed here), a second read placed *after* the copy is neutralised anyway: `cse.c:canon_reg`
  re-canonicalises it onto the copy's destination and the producer drops back to one use. It must sit
  **before** the copy — where there is nothing for it to be. C's own folding kills the free candidates:
  `tmp & 0`, `tmp - tmp`, `tmp ^ tmp` are gone at `fold-const.c` before expand (measured: `p3`, `p4`
  score 6), and a dead second reader (`s32 dead = tmp;`) is deleted by flow (`p1`, `p2` score 6).
- **Blocker 1 (a label) has no free home either.** A label emits no bytes, so the target *could* carry
  one — but it must be referenced or jump1 deletes it (`goto L; L:` measured: `w3`, `y3` score 6/8),
  and **no branch in the target targets any address between `0x35b0` and `0x35b4`**. Paying for a real
  join costs the diamond's branch (`y5`, `y6`, `z10`, `r1`, `r3`: 67 instructions but the extra one is
  a `nop` or a compare, never the copy).
- **Blocker 3 (a call) is impossible:** the only call before the switch is the `ratan2` that *produces*
  the value, so `INSN_CUID (producer) > last_call_cuid` always.

**Cross-check against the binary.** I scanned all 4,284 objects under `build/src` for the shape
"ALU insn writing a caller-saved register, no control flow, then `move sN,<that register>`"
(101 distinct hits). Every lever-free precedent I read pays one of the two prices:
- `func_8015D1B8` (`ov_SC03_099_jr_8015C32C.c:1725`) — `sum` has **two** uses (`*(u16*)(obj+0x10) =
  sum & 0xFFF;` then `keep = sum;`); the drafter's own comment says "AFTER the store — this is what
  keeps the `$s0` copy alive".
- `func_8014DD8C` (`src/shared/ov/func_8014DD8C.h:18`) and `func_8018CBB0`
  (`ov_SC03_001_jr_8018B8DC.c:4058`) — a **narrow (`s16`) local with two consumers** (lane B 1c-1).
- `func_80180CFC` (`ov_SC06_032_jr_8017C24C.c:5487`) — `iVar1 = t;` followed by `t = t << 16;`, a real
  second read of `t` *before* it is overwritten.
- `func_801864E4` (`ov_SC05_010_jr_8018473C.c:4076`) — `sel = cond ? A : B; start = sel;`, a **join
  label** between producer and copy.
None of the four shapes exists in `func_80148E54`, and none can be created in it for zero bytes.

## (d) GENERATOR PROPOSAL

**R20 "copy-keeper pair" (a paired move, plus a cheap unreachability predicate).** When the residual is
COUNT and the missing instruction is a reg-reg `move S,C` whose source `C` is written by the
*immediately preceding* instruction in mine, emit ONE candidate per (separation × blocker) pair — the
nearest independent following statement moved *between* the producer and the copy (which is the only
thing that defeats `cse.c:7454`) **crossed with** one of combine's three blockers (a second read of the
producer inserted *before* the copy, an if/else diamond whose merge label sits between them, or a call
moved between them) — because neither half changes the score alone, which is exactly why every
single-move family in the registry sits at the same number on this class; and *before* spending the
compiles, refuse the class outright when (i) the producer's value has exactly one consumer in the C
text and (ii) no branch in the target targets an address strictly between the producer and the copy,
since then all three blockers are unaffordable and the body is unreachable body-only.

This is new against the four docstrings in `tools/delever.py`: `sink_merges` (R15) sinks a merge
statement into if/else arms, `constant_holders` (R16) deletes a literal-holding local,
`constant_run_splits` (R17) splits a run of equal constant stores, `bystander_moves` (R18) walks an
independent statement within its block — all four are *single* moves over whole statements, and none
of them is aimed at `cse.c:7454`'s adjacency precondition. It is also distinct from a-80166F58's
proposed R19 ("second use before the copy"), which is one of R20's three blocker legs and is offered
there without the separation half and without the unreachability gate.

## (e) What did NOT work — the byte evidence (all `--try` on the real TU, ~90 compiles)

| spelling | score |
|---|---|
| one variable `s32 ang = EXPR;` (`PACK/body.c`) | 6 (66 ins) |
| two variables adjacent; chained `ang = tmp = EXPR;`; nested block; `do { ang = tmp; } while (0)`; `(ang = tmp, 0)`; `(s32)` cast; `const`/`u32` producer; declaration order swapped | 6 each |
| an intervening statement before the copy (`s32 k` / `u8 k` = the switch subject) | 6 (cse defeated, combine folds — dump-verified) |
| lane B 1c-2 "re-set the SOURCE": `tmp = 0;` after the copy, `tmp = 0;` inside the case, `ang = 0;` after the switch, `tmp` reused for the second `ratan2` result | 6 each (flow deletes the dead store) |
| lane B 1c-1 widths — 8 producer/destination width combinations **with** the intervening statement, and 6 single-variable narrow declarations (`u16`,`s16`,`short`,`unsigned short`) | 6 each; `u8`/`char` 11 (a real `andi 0xff` appears). Confirms the residual_moves ledger row: combine folds a narrowing of a value already masked to 12 bits |
| free second reads: `tmp & 0`, `tmp + (tmp&0)` in the subject expression, `s32 dead = tmp;` before or after the copy | 6 each (fold-const / flow remove them) |
| `goto L; L:` between producer and copy | 6 (jump1 deletes the jump, then the label) |
| `while (0) {}`, `if (arg0) {} else {}`, `switch (0) { default: … }`, `switch (arg0) { default: … }` between them | 6 each |
| **`ang = tmp;` moved inside `case 0x53:`** | 9, **67 ins, the copy present** — the block boundary really does keep it, but in the wrong block |
| `if (k == 0x53/0x41) { ang = tmp; } else { ang = tmp; }`, `?:` with equal arms | 8 / 4, 67 ins — the 67th instruction is a `nop` or a hoisted compare, never the copy |
| diagnostic (levers, not bankable): launder alone, no pin | 4, **67 ins, the copy present as `andi v0,v0,0xfff ; move s1,v0`** — proves the colour is a consequence of where sched1 puts the copy |

## (f) Where the method fell short

- **§455's one-line reading named the wrong pass.** "combine merges a single-use def into its copy" is
  true only once the two insns are non-adjacent; for the adjacent form the killer is `cse.c:7454`, a
  transformation with a *completely different* precondition (the immediately preceding insn). Chasing
  combine first cost an hour of hypotheses that could not have worked. A pass attribution in a cookbook
  entry should carry the `file:line` and the dump line that proves it — this one now does.
- **The residual print does not say which side of the copy the extra instruction lives on.** "insert
  `move s1,a0` after `beq`" reads as a scheduling fact; the load-bearing facts (the copy is
  unconditional, its source has exactly one consumer, and no branch targets the gap) all had to be
  recovered by hand from `objdump` on `build/src/ov_SC04_011/ov_SC04_011_after.o`. Printing the
  *neighbourhood* of a COUNT insert, plus the target's use-count for the registers involved, would have
  named the class in one look.
- **The engine has no way to represent "two moves, neither of which changes the score".** The beam drops
  a child that is not better and tails a child with the parent's score *and* diff signature, so a pair
  whose first half is byte-neutral is structurally out of reach. That is the finding behind R20 and it
  applies to every copy-survival class, not just this body.
- **`--try` and the search share one scratch TU per pack** (`.run/P36/engine/score/<pack>/`). Two of my
  batch runs came back as a bare Python traceback that re-running fixed; a per-invocation scratch dir
  would make agent sweeps safe to run alongside anything else.
- **A "no branch targets this gap" check is computable and would have ended the search in 30 seconds.**
  It is offered as the R20 predicate above.

## Twin

`func_80148D44` has the byte-identical residual (score 6, mine 67 / target 68, `andi a0,v0,0xfff` …
`move s0,a0`, `s0->a0 x1`) and the same census: its producer `a` has exactly one consumer, its
`d = (s32)D_80126C01;` already separates producer from copy (so cse is already defeated there and
**combine alone** is the killer), and no branch targets the gap. The reading transfers verbatim; the
*text* does not (the twin reads globals, not `arg0` offsets), and since this body did not close there
is no body text to share. If a future move closes one, it will close the other.
