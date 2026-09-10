# func_8016CBC0 (src/ov_SC04_011/ov_SC04_011_jr_8016AB6C.c) — MATCH, score 0

T7 agent, P36 S102, 2026-09-10. One NEEDED site: `register unsigned int zr __asm__("$0")`, read three
times as `x = y + zr`. Start 55, mechanical best 11 (g5), **final 0** — 128 copies.

## (a) The residual in one sentence

COUNT, mine 205 vs target **209**: the target has three `move rD,rS` insns that mine does not
(each one the second half of a `addiu rD,rS,-1` / `move rS,rD` decrement pair), plus one extra insn
where mine keeps `uVar9` permanently pre-shifted (`lui v0,0xffff` + `addu s1,s1,v0` for `-1`,
`lui s1,0xf` for `= 15`) and the target keeps it raw (`addiu a0,s1,-1`, `li s1,15`).

**Counted first, as the brief says.** Four instructions are MISSING, not mis-coloured; the register
pairs line (`a3->a1 x11 …`) was a consequence, not the defect. The `$0` pin was hired to fake exactly
those three `move`s: `iVar3 = w3 + zr` emits `addu rD,rS,$0`.

## (b) The pass and the decision, read from the compiler

**cse1** (`toplev.c:2865`, `cse_main(…, after_loop = 0)`), register-equivalence entry:

    tools/reference/gcc-2.7.2/cse.c:1005  insert_regs()
    :1018-1020   if (REGNO_QTY_VALID_P (regno) && qty_mode[reg_qty[regno]] != GET_MODE (x)) return 0;
    :1029-1032   if (GET_CODE (classp->exp) == REG && GET_MODE (classp->exp) == GET_MODE (x))
                     make_regs_eqv (regno, REGNO (classp->exp));

**Two pseudos are entered into one equivalence class only when their MODES ARE IDENTICAL.** Proven on
the dumps of this very TU (both spliced through the real recipe, `tools/cc1_dumps_tu.sh`, dumps kept in
`scratch/dumps/dumps_{int_v,shrt_v}/`):

* all-`int` body, `.rtl` (expand) — `(set (reg/v:SI 81) (plus:SI (reg/v:SI 80) (const_int -1)))` then
  `(set (reg/v:SI 80) (reg/v:SI 81))`, a same-mode reg-reg copy;
  `.cse` — **both insns are gone**, collapsed to `(set (reg/v:SI 80) (plus:SI (reg/v:SI 80) -1))` and
  the branch canonicalised onto reg 80 (`canon_reg`); the dead copy is swept by `delete_dead_from_cse`
  (`toplev.c:2867`). One register, one insn → `addiu s2,s2,-1`.
* `short` body, `.rtl` — `(set (reg:SI 108) (plus:SI (subreg:SI (reg/v:HI 80)) -1))`,
  `(set (reg/v:HI 81) (subreg:HI (reg:SI 108)))`, `(set (reg/v:HI 80) (reg/v:HI 81))`;
  `.cse` — the HImode copy is folded away but **the truncating store survives**:
  `(set (reg/v:HI 80) (subreg:HI (reg:SI 108)))` with `(reg:SI 108)` still live into the compare
  (`ashift (reg:SI 108) 16`). A `subreg` destination is not a copy for `insert_regs`, so no
  equivalence is made; combine cannot merge insn 123 into it either (reg 108 has a later use), and it
  reaches reload as `move s2,v1`.

**loop** (`toplev.c:2895`) owns the second half. With `unsigned int uVar9` every use is `(short)uVar9`,
so `strength_reduce` mints a derived induction variable `reg 205 = uVar9 << 16` (loop-inserted insns
499/500/502 in `.loop`), and **combine** then distributes the shift over the decrement —
`.combine` shows `(set (reg:SI 206) (const_int -65536))` + `(set (reg:SI 205) (plus (reg:SI 205) (reg:SI 206)))`,
i.e. `lui v0,0xffff; addu`, and `(set (reg:SI 205) (const_int 983040))` = `lui s1,0xf` for `uVar9 = 15`.
A HImode pseudo cannot be that `<<16` giv, so narrowing `uVar9` deletes the whole shifted
representation: `addiu a0,s1,-1`, `li s1,15`, and the `sll`/`sra` pair back at each use — the target.

MIPS has **no `PROMOTE_MODE`** (`config/mips/mips.h`, comment only at :2622), which is why a `short`
local is a genuine HImode pseudo here and this lever exists at all.

## (c) The moves that closed it

1. `int iVar3; int w3; unsigned int w3b;` → `short iVar3; short w3; short w3b;` — the outer-count chain.
2. `unsigned int uVar9; unsigned int w9;` → `short uVar9; short w9;` — the sub-index chain (`w9` must be
   SIGNED: the `< 0` test is the whole point of the variable).
3. `unsigned int uc;` → `unsigned short uc;` — `uc` is a colour component; left `unsigned int` the body
   scores 4 (ORDER), so its pseudo mode is load-bearing for the schedule too.

Readability edits, each re-proven at score 0: the three `+ 0` pin residues written as plain copies
(`iVar3 = w3;`), `(short) uVar9` dropped from both `&sub[…]` (now redundant), `((int)(w9 << 16)) < 0`
written `w9 < 0`, and the latch's `uc = iVar3 - 1; w3b = uc;` collapsed to `w3b = iVar3 - 1;` so `uc`
stops doubling as a counter. The `while` test loses its cast: `while (w3b != -1)`.

## (d) GENERATOR PROPOSAL — R20 "narrow the counter chain"

**When the residual is COUNT and the target carries `move rD,rS` insns that mine lacks, each immediately
after an `addiu rX,rY,±1` whose destination differs from mine's in-place `addiu rY,rY,±1`, narrow EVERY
local in that counter's def-use chain — the counter, its `± 1` temp and its copy-back temp — to `short`
(or `unsigned short`) in ONE candidate, and offer the cross product over the chains, not over the
declarations.**

Why it must be chain-scoped and joint, measured on this body (each number is one `--try`):

| candidate | score |
|---|---|
| start (all `int`/`unsigned int`) | 55 |
| `uVar9` alone → `u16` | 45 |
| `w9` alone → `s16` | 72 |
| `iVar3` alone → `s16` | 51 |
| `uc` alone → `s16` | 24 |
| uVar9-chain only (2 decls) | 43 |
| iVar3-chain only (4 decls) | 43 |
| **both chains (6 decls)** | **0** |

Every single-declaration move and every single-chain move scores WORSE than the mechanical search's own
best-11 path, so a beam over R12's one-declaration candidates cannot reach the answer from either
direction — g3/g5/s1/s2/s4/s7/s9 spent 4,811 compiles and stalled at 11. The joint candidate is one
compile. Signedness is free everywhere except where a `< 0` (or `>>`) test reads the variable, so the
generator should offer `short` first and `unsigned short` second per chain (2^k for k chains, k ≤ 2 here
= 4 compiles, versus 4,811).

The chains are readable straight off the residual: group the target-only `move rD,rS` insns by rS (the
copy's destination = the counter's hard register), then map that register back to the source variable
through the `addiu` it follows.

## (e) What did NOT work, with byte evidence

* `unsigned short iVar3` + `unsigned int` temps → **8** (mine 211): the two extra insns are
  `andi a0,s1,0xffff` / `andi v0,s2,0xffff`. A *zero-extended* narrow local read into an SImode
  expression pays for the extension; only when the DESTINATION is narrow too does the arithmetic stay
  HImode and read the register raw. This is the trap: `u16` gets the `move` but buys an `andi`.
* `short uVar9` with `unsigned short w9` (body_free's `((int)(w9<<16))<0` form) → **14**, mine 207:
  the unsigned `w9` changes what the test computes. `w9` must be signed.
* Dropping `(short)` from `&sub[(short) uVar9]` while `uVar9` was still `unsigned short` → **9**
  (mine 207). It is only redundant once `uVar9` itself is signed `short`.
* Collapsing `a2 = (unsigned)(col & 0xFF); a2 = a2 >> 3;` into one statement → **17** (mine 210). The
  two-statement split is load-bearing (an `srl` moves across the schedule); left alone.
* `uc` widened back to `unsigned int` once it was colour-only → **4 (ORDER)**. Its pseudo mode still
  matters; kept at `unsigned short`.

## (f) Where the method fell short

* **`sites.txt` says "pin $0" and nothing about how many times it is read.** The one site had three uses,
  and the count of target-only `move`s (three) matched them exactly — that is the single most useful
  number in this residual and neither `sites.txt` nor `residual.txt` states it. A one-line
  "site line 2874: pin `zr`, 3 uses at lines 48/71/129" would have pointed at the answer immediately.
* **`tools/alloc_table.py` was never needed and would have been a detour.** The residual's register-pairs
  line (`a3->a1 x11, a0->a1 x3, …`) advertises a colouring problem; the defect was four missing insns.
  The brief's "count first" rule is what saved the run — I suggest the residual header print
  `mine N ins, target M ins (**M-N MISSING**)` in the class line, ahead of the pairs.
* **`history.txt` is misleading as written.** It reports R12 width moves reaching 11 and, separately,
  a list of "best-scoring single candidates" — all of which are single-declaration moves. Nothing in it
  says the family had ALREADY been proven necessary but insufficient; an agent that trusted the best-11
  path (do-while + inline + two widths) would have kept perturbing a dead end. The history would be far
  more useful if it recorded, per family, *the best score reachable with that family alone*.
* Line numbers in `history.txt` (`@2869`, `@2870`) do not agree with the tree's line numbers for the
  same declarations (`iVar3` is at 2868 in the file); they cost a few minutes to reconcile.
* `tools/cc1_dumps_tu.sh` needs the TU's own directory on the include path for `#include "../shared/…"`;
  from a scratch work dir it fails `CPP-EMPTY` until you plant a `shared` symlink one level above `t.c`.
  Worth saying in the script's usage line.
