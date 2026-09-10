# func_80139BE0 (ov_SC04_011_jr_801380E0.c) — MATCH, score 0, lever removed

Lever removed: the one NEEDED site, a `launder` (`__asm__("" : "=r"(t) : "0"(t))`) at line 923.
Final: **score 0 (39/39 instructions, byte-identical)**. Body: `PACK/body.c`.

---

## (a) The residual in one sentence

The target keeps a QI→SI zero-extend of the already-masked byte (`andi $v0,$v0,0x60` **then**
`andi $a1,$v0,0xff`) which our lever-free C folds to a single `andi $a1,$v0,0x60` — one instruction
short (COUNT, mine 38 / target 39), the two `bnez`/`j` displacement rows being only the shift the
missing instruction causes.

## (b) The pass and the decision, read from the compiler's own source

The function's block-1 RTL before combine (`.i.flow`; regenerate with `PACK/dump.py <body> <tag>`, which splices the body into the real TU and runs cpp + cc1 `-dr -dj -dc -df -dl -dg -dS`) is **four** insns,
not three:

```
18: (set (reg:QI  77) (mem:QI (plus (reg 72) 34)))                    lbu
19: (set (reg:SI  78) (and (subreg:SI (reg:QI 77)) 96))               andi 0x60   <- the expander narrows
20: (set (reg/v:SI 76) (zero_extend:SI (subreg:QI (reg:SI 78))))      andi 0xff   <- ...and re-extends
26: (set (reg/v:SI 81) (zero_extend:SI (subreg:QI (reg/v:SI 76))))    andi 0xff   <- `idx = (u8)t`
```

Insns 19+20 are one statement: `*(u8*)p & 0x60` is expanded as an AND in QImode plus a zero-extend
(the constant fits the narrower type), so the `andi 0xff` the target keeps is *always generated*.
Two combines then remove two of the four:

* `(19,20)` — adjacent, `reg 78` dies in 20, so `added_sets_2 == 0`; the merge always succeeds.
  **It cannot be blocked from C** (nothing can be placed between two insns of one expression).
* `(20',26)` — this is the one the target does not do. `subst` folds
  `(zero_extend (subreg:QI (and X 96)))` to `(and X 96)` in
  **`simplify_and_const_int` `combine.c:6734` (`constop &= nonzero`) / `:6777` (`if (constop == nonzero) return varop`)**,
  because `nonzero_bits((and X 0x60)) == 0x60` and `0xff` covers it.

The only gate that can stop `(20',26)` without a `volatile`, a pin or an intervening set of the
*load's* temp is
**`try_combine`'s `added_sets_2 = ! dead_or_set_p (i3, i2dest)` — `combine.c:1458`**: if `t` does not
die in i3, combine must keep i2's set too, builds a two-SET `PARALLEL` (`combine.c:1644-1669`), and
`recog_for_combine` (`:1692`) finds no MIPS pattern for it → the whole combination is abandoned and
**both** `andi`s survive. (`can_combine_p`'s `use_crosses_set_p` route, `combine.c:803`/`:900`, also
blocks it — see (e) — but only by re-setting the byte's own pseudo, which costs a `nop` and the wrong
registers.)

So `t` must be live past the extend **at combine time** and dead again **before local-alloc**, or the
target's allocation (`t` = `$v0`, immediately reused by `slti $v0,$v1,7`) is unreachable. Nothing
between combine and local-alloc deletes insns except combine itself, so the extra reference has to be
one combine folds away: with `nonzero_bits(t) == 0x60`, `t >> 8` is turned into `0` by
`simplify_shift_const` (ASHIFTRT→LSHIFTRT at `combine.c:7758-7763`, then the count exceeds the known
width), the `+ 7` collapses, the shift insn is deleted, and `distribute_notes` puts `REG_DEAD (reg/v 76)`
back on the extend.

## (c) The move that closed it

**One move:** write the outer guard's bound as `if (h < 7 + (t >> 8))` — a second, identically-zero
reference to `t` after `idx = (unsigned char)t;`, whose consumer (the `slti`) is independent of `idx`.

Proved on bytes (`.i.combine` of the winning text, `PACK/dump.py PACK/body.c v16`): insn 20 survives as
`(set (reg/v 76) (and (subreg:SI (reg:QI 77)) 96))`, insn 26 survives as
`(set (reg/v 81) (zero_extend (subreg:QI (reg/v 76))))` **carrying `REG_DEAD (reg/v 76)`**, and the
shift/add insns are `NOTE_INSN_DELETED`. Allocation then matches the target exactly
(`t`=`$v0`, `idx`=`$a1`), and `reorg` fills the `beqz` slot with `slti $v0,$v1,2` — not with the
extend — because the extend reads `$v0` which the `slti` overwrites.

Five other spellings of the same move also reach score 0 (all plain C, no `volatile`/asm/pin):
`if (h < (7 | (t >> 8)))`, `if (h < 7 + (t >> 7))`, `if (h < 7 + (t & 0x80))`,
`if ((h & ~(t >> 8)) < 7)`, `if ((h | (t >> 8)) < 7)`.

## (d) GENERATOR PROPOSAL

**When the residual is COUNT with a missing `andi rD,rS,0xff` (or `0xffff`) immediately after an
`andi rS,rS,<mask≤0xff>` whose result has exactly one consumer, take the local `t` holding the masked
value and append an identically-zero term built from it — `+ (t >> 8)` for a byte mask, `+ (t >> 16)`
for a halfword mask — to the constant operand of the FIRST comparison after the narrowing statement
that does not already consume the narrowed value.**

Mechanically: locate the statement `X = (T)t;`/`X = t & 0xff;` that produced the extend, find the next
statement in the same basic block whose expression does not mention `X`, and rewrite its integer
literal `K` as `K + (t >> W)` where `W` = bit width of the mask (8 / 16). Score it; if the residual
becomes REG rather than COUNT, the term landed in a block that keeps `t` alive too long — move it one
statement earlier. Cheap to enumerate (5 spellings × the candidate statements) and every candidate is
plain C, so a wave can run it unattended behind the byte gate.

Preconditions the generator must check (each one refuted a spelling here):
1. the zero term's consumer must be independent of the extend's result (`idx |= t >> 8;` and
   `idx = (u8)t | (t >> 8);` both fail — combine merges the whole chain and folds everything: 38 ins);
2. it must be in the SAME basic block as `t`'s definition and AFTER the extend (`&&`-guards create a
   real branch: 41 ins; a use in an arm keeps `t` live into that block and loses the allocation: 45 ins);
3. it must fold in combine, not in `fold` (`t & 0`, `t - t`, `t * 0` are folded by the front end and
   leave no reference at all).

## (e) What did NOT work, and the byte evidence

| spelling | score / ins | why (proved) |
|---|---|---|
| `unsigned char t = ... & 0x60; idx = t;` | 4 / 38 | the promoted-QI store is the same `zero_extend`, folded by `:6777` |
| `idx = t & 0xff;` | 4 / 38 | identical RTL to the `(unsigned char)` cast |
| `t = load; t &= 0x60;` (two sets of `t`) | 4 / 38 | `i2dest_in_i2src` changes only bookkeeping, not the fold |
| `v = D[(unsigned char)t >> 5]` in the arm | 4 / 38 | the extend merges into the `srl` in ITS block instead |
| `int b = load; int t = b & 0x60; b = lhu; idx = (u8)t;` | 6 / 40 | `use_crosses_set_p` DOES block the fold (both `andi`s appear), but reusing the pseudo makes the `lhu` anti-dependent on the `andi`, so it cannot fill the `lbu` load-delay slot → a `nop`, and the byte load is forced into `$v1` |
| `b = h;` as the blocker | 4 / 38 | cse deletes the copy before flow (matches `residual_moves.md` Class 3 row 2: "`x = x` will not do — cse deletes it") |
| `b = h < 7;` as the blocker | 10 / 38 | gcc gives the compare a fresh pseudo; nothing sets `b` between |
| `return t;` (live-out to the epilogue) | 12 / 41 | the fold IS blocked, but `t` then needs a register across the whole function (`$a2`) plus the init and the `$v0` copy |
| `v = D[t >> 8];` in an arm | 14 / 45 | `t` live-out blocks the fold, but with no LOG_LINK across blocks the `sra` is emitted and the arms split |
| `idx |= t >> 8;` / `idx = (u8)t | (t & 0x80);` | 8, 4 / 38 | the zero term shares a consumer with the extend, so combine folds the pair |
| `if (h < 7 && t < 0x80)` / `if ((t & 0x80) == 0 && h < 7)` | 10, 4 / 41 | `&&` builds a real second branch that jump2 does not remove |

## (f) Where the method fell short

* `sites.txt`/`residual.txt` describe the *output* delta; nothing in the pack says the function's
  pre-combine RTL has **four** insns for these three. Reading `.i.flow` was what turned a hopeless
  "make an `andi 0xff` appear" into a bounded "block one of two named combines". A `--dumps` mode on
  `delever_search --explain` (splice + cpp + cc1 `-df -dc`, ~2 s — the script I had to write by hand is `PACK/dump.py`) would put that in every pack for free.
* The tree's existing comment above the function ("No pure-C spelling survives that fold when the def
  and the extend sit in the SAME basic block (verified: u8 local, (u8) cast at the use, `& 0xff` at the
  use, u8-via-int, u16 hold, hard-register pins)") is true for every spelling it lists and was still a
  false conclusion: it enumerated re-spellings of the *fold* and never the *liveness* gate that decides
  whether the fold is attempted. A refuted-list in a pack should record the gate each attempt was aimed
  at, not just the text.
* The mechanical search burned 2,378 compiles here across seven runs at a flat best of 4: every one of
  its generators (R6/R7/R8/R10/R12) rewrites the *defining* statement, and none of them can add a
  reference to a value elsewhere. The generator in (d) is the missing family.
* One honesty cost worth flagging to the coordinator: the term is a semantic no-op, so the source now
  says something the original almost certainly did not (whatever kept `t` alive in the original was
  probably a real second use that we cannot recover). It is plain C — no pin, no `asm`, no `volatile`,
  no builtin — and it carries a comment saying exactly that, but it is an *invented* expression, not a
  recovered one. If the phase would rather keep the launder than invent a term, this is the fork.
