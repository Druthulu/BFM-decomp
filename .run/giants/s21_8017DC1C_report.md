# `func_8017DC1C` @ `ov_SC07_006` — behemoth #8 (the last), 1,518 ins — **match_one MATCH**

**Result: `MATCH (1518 ins)`**, pin-free, **first full gate run**, one round.

```
{ echo '#include "common.h"';
  echo '#include "../src/shared/engine_types.h"';
  cat .run/giants/s21_func_8017DC1C_b1.c; } > probe.c
.venv/bin/python tools/match_one.py func_8017DC1C --c probe.c \
    --asm-subdir asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8017BEBC
=> MATCH (1518 ins)
```

**NOT BANKED.** `match_one` masks `jal`/HI16/LO16 and never links. The three things it is
blind to were checked independently and are all **clean** (§5).

---

## 1. What it is

A **morph / keyframe blender**. 25 statements, each blending one model's vertex block
from keyframe `b` toward keyframe `a` by the 1.12 fixed-point factor `t` (`$a0`):

```
d[i].vx = b[i].vx + (((a[i].vx - b[i].vx) * t) >> 12);   /* and vy, vz */
```

Zero `jal`, zero `jr $vX`: the 25 statements are **25 expansions of one `static inline`
helper**. Each expansion is 60–61 instructions; 25 × 60 + prologue/epilogue = 1,518.

The destination is resolved from a 0x14-byte header (`Morph_8017DC1C` in the draft):

| off | field | meaning |
|---|---|---|
| 0x04 | `mode` | `== 1` ⇒ +0x0C is a **pointer** to the vertex block; else the block is **inline** |
| 0x0C | `dst` (`u32`) | pointer, or a byte count skipped to reach the inline block |
| 0x10 | `n` | vertex count (both modes) |

25 `Morph_8017DC1C *` globals (`D_801BF4F4…D_801BF6AC`) × 39 `SVECTOR2 *` globals
(`D_801C1E14…D_801C1EB0`), all initialised pointer words in
`asm/ov_SC07_006/data/tail.data.s`. **10 of the 25 calls pass the SAME keyframe pointer
for both `a` and `b`** (blocks 1,2,3,4,8,9,10,11,15,16) — a genuine no-op blend in the
original, visible in the bytes as `addu $a3,$a2,$zero` after cse folded the duplicate load.

---

## 2. Finding the relative — the brief's warning was right, and §79 also fired

**§71 could not fire (0 callees), exactly as briefed.** Two things replaced it:

| method | outcome |
|---|---|
| **SHAPE fingerprint on the IDIOM** — `grep -rn '>> 12' src/` and histogram the expressions | Hit in **2 greps**: `src/ov_SC03_099/ov_SC03_099_jr_801380E0.c :: func_8013AD38` (MATCHED, ×134 fleet-wide) carries the *identical* blend idiom `D_800D45F4[k] + (((D_800D466C[k] - D_800D45F4[k]) * t) >> 12)`. That confirmed operand order (`base + (far - base) * t`) and the `s16`-array shape before I wrote a line. |
| **§79 frame oracle, used forwards** | `addiu $sp,$sp,-0x258` with **zero stack references** is the whole structural clue: 600 = 25 × 24, and 24 is what one expansion of the body's locals costs. Measured 1 body = 24, 2 = 48, 25 = 600. That is what said "25 in-place expansions", i.e. `inline`. |

**The false lead the brief warned about DID appear and was refused in one command.**
`src/ov_SC04_010/ov_SC04_010_jr_8017BEBC.c` *defines* `func_8017DC1C` and is MATCHED —
but its body is `void func_8017DC1C(void) { }`, an empty 2-line stub. Same address,
different overlay, different code. Cost: one `sed -n`.

> **Generalisation to bank: for a 0-callee function, fingerprint by the ARITHMETIC IDIOM,
> not the callee set.** `grep -rn '<the distinctive operator>' src/ | histogram the
> right-hand sides` finds a matched relative in one command when §71 is structurally
> blind. Here `>> 12` had 141/135/134-way repeats at the top of the histogram, and the
> 134-way row *was* the answer.

---

## 3. The build — round 1 only

| step | edit | result |
|---|---|---|
| p1 | one block, longhand, plain locals | shape correct at first compile; frame **24** |
| p2 | body hoisted to `static inline`, 2 call sites | frame **48**; the same-symbol `addu $a3,$a2,$zero` appears ✅ |
| p3 | **L2** — body assigns params to locals (`pb = b; pa = a;`) | the two preheader moves appear ✅ |
| p4 | **L3** — `i = o->n;` moved *before* the copies | head + loop exact except a 3-register giv permutation |
| p5 | **L4** — increment order `d++; pb++; pa++;` (6 permutations swept) | **2 blocks byte-exact** |
| b1 | replicate ×25 with the extracted symbol triples | **MATCH (1518 ins)** on the first full gate |

### The five levers

* **L1 `static inline`.** 0 `jal` + 25 identical bodies ⇒ expanded in place. Out-of-line
  `static` collapses the function to **199 ins**. The **discriminator vs a macro is the
  instruction count**, not the frame: macro = **1537** (+19), inline = 1518.
* **L2 params → locals.** `pb = b; pa = a;` then walk the locals. Incrementing the params
  directly makes the arg register and the loop biv one pseudo, `combine` folds the copy
  into the load, and **both** preheader moves (`addu $t2,$a3,$zero` / `addu $t0,$a2,$zero`)
  vanish — 2 moves × 25 = 50 instructions, and the length falls to 1493.
* **L3 `i = o->n;` before the copies.** Source order survives into the schedule: the target
  fills the `lw $t3,0x10($a1)` load-delay with the `pb` copy and the `beqz` delay with the
  `pa` copy. Put the copies first and the count load needs a `nop`, *and* the delay-slot
  reorg pass steals the `pb` copy into the `j` delay slot that the target leaves as `nop`
  (+11 ins). Folding it into `for (i = o->n; …)` is identical to putting it after (+11).
* **L4 increment order `d++; pb++; pa++;` — the REVERSE of the read order.** `loop.c`
  **prepends** each biv to `loop_iv_list`, so the preheader giv-init order
  (`$a3 = pa+4`, `$a2 = pb+4`, `$a1 = d+4`) is the reverse of the increment order.
  All 6 permutations measured (§4).
* **L5 index arithmetic, not a mask.** `(u32 *)&o->dst + (o->dst >> 2)` ⇒
  `srl 2; sll 2; addiu 0xC; addu` (4 insns). `(o->dst & ~3)` collapses to one `andi 0xfffc`
  (−25 ins). `dst` must be **`u32`** — `s32` gives `sra` and costs exactly 25 mismatches.

### New law worth banking — the `slti` law's mirror image

**L6 (do NOT "fix"):** the target's `addiu $vX,$zero,1` + `bne $v0,$v1` looks like §78's
"the limit was materialised into a register ⇒ it was a variable" signature. **It is not.**
`o->mode == 1` is an **equality** test, and MIPS has no `beqi`, so an equality constant is
*always* materialised into a register. §78's literal-position law is scoped to the
**ordered** comparisons (`<`, `<=`, `>`, `>=`) that `mips.c` can rewrite into `slti`.
Reading a materialised constant in a `beq`/`bne` as evidence of a source variable is a
false positive; that is 25 wasted edits on this function alone.

---

## 4. Do-not-re-buy table — `(edit, base) → result` (§80: all measured on the b1 MATCH base)

| edit | base | result |
|---|---|---|
| increment order `pa++; pb++; d++;` (natural read order) | b1 | **1518 ins, 295 mismatched** — REGALLOC-LOCAL; the giv registers permute |
| increment order `pb++; pa++; d++;` | probe (2 blocks) | 45/61 — worse |
| increment order `d++; pa++; pb++;` | probe | 49/61 |
| increment order `pa++; d++; pb++;` | probe | 44/61 |
| increment order `pb++; d++; pa++;` | probe | 49/61 |
| **`d++; pb++; pa++;`** | probe | **57/61 — the winner; the other 5 are spent** |
| drop the `pb`/`pa` locals, increment the params directly | b1 | **1493 ins, 1454 mismatched** (LENGTH-DRIFT −25) |
| `i = o->n;` **after** `pb = b; pa = a;` | b1 | **1529 ins, 1452 mismatched** (+11) |
| `for (i = o->n; i != 0; i--)` (fold L3 into the for-init) | b1 | **1529 ins, 1452 mismatched** — identical to the above |
| `(u8 *)&o->dst + (o->dst & ~3)` instead of the index form | b1 | **1493 ins, 1456 mismatched** (−25, one `andi` per block) |
| `dst` declared `s32` instead of `u32` | b1 | **1518 ins, 25 mismatched** — `sra` vs `srl`, exactly 1 per block |
| helper `static` (not `inline`) | b1 | **199 ins** — SIZE-MISMATCH, 25 real `jal`s |
| helper as a **macro** with the same body | b1 | **1537 ins, 1512 mismatched** (LENGTH-DRIFT +19) |
| local `typedef SVECTOR2` in the draft vs the shared one | b1 | **MATCH both ways** — byte-neutral; the shared spelling ships (§5) |
| moving the `Morph_8017DC1C` typedef above the `extern` block | b1 | **MATCH** — byte-neutral, fixes 25 `incompatible pointer type` warnings |

### Refuted diagnoses

* *"`ov_SC04_010` has `func_8017DC1C` matched — remap it."* — **No.** Its body is
  `void func_8017DC1C(void) { }`. Same address ≠ same code across overlays (the brief's
  warning (a), confirmed a second time).
* *"the 0x258 frame with zero stack references is dead storage / needs a padding array."*
  — **No.** It is 25 × 24 of per-expansion local slots and comes out **free**. Never hand-pad
  a frame before checking whether the body is expanded N times.
* *"the frame proves `inline` over a macro."* — **No.** The macro spelling also frames 600.
  Only the instruction count (1518 vs 1537) separates them.
* *"`addiu $vX,$zero,1` + `bne` means the 1 was a variable (§78)."* — **No.** See L6:
  §78 is scoped to ordered comparisons only.
* *"the two `addu …,$zero` moves per block are a regalloc artefact to be permuted away."*
  — **No.** They are source structure (L2); a permuter would never find them.

---

## 5. Banking — what `match_one` could not see, checked by hand

| blind spot | check | result |
|---|---|---|
| **§81** jump-table duplication | `grep -cE 'jr\s+\$(v0\|v1\|a0\|t[0-9])' <the .s>` | **0** — the only `jr` is `jr $ra`. **No carve chain needed.** |
| **§84** mis-derived `%lo` | `grep -cE '%lo\([A-Za-z_]\w*\+' t.s` | **0** — every `%lo` is a bare symbol, offset 0 |
| **§87** unresolvable symbols | all **64** `D_` symbols vs `dlabel`/`glabel` in `asm/ov_SC07_006/**` | **0 missing** |

### Decl plumbing — audited against the real TU

`src/ov_SC07_006/ov_SC07_006_jr_8017BEBC.c` (3,935 lines) is the target TU.

1. **None of the 64 `D_` symbols is declared anywhere in the tree today.** The draft's
   spellings (`extern Morph_8017DC1C *D_801BF4F4;` ×25, `extern SVECTOR2 *D_801C1E14;` ×39)
   are free choices and **establish the canon**. They are correct against the data:
   `D_801BF4F4 = .word D_801AD4DC`, `D_801C1E14 = .word D_801BFD0C` — initialised pointers.
   (`ov_SC04_002` declares a *different overlay's* `D_801BF4F4` as `M2C_UNK`; different
   binary, no conflict.)
2. **`SVECTOR2` is a SHARED type**, `src/shared/engine_types.h:998`
   (`typedef struct { s16 vx, vy, vz, pad; } SVECTOR2;` — byte-identical to what the draft
   needs). The TU already reaches it via `#include "../shared/engine_core.h"` →
   `#include "engine_types.h"`. **The draft therefore does NOT redefine it**, and is gated
   through the §77 probe copy. Do not add the include when splicing.
3. **`Morph_8017DC1C`** is a new file-local type. Name checked collision-free across
   `src/` + `include/`; follows the house `Type_<addr>` convention
   (`Cmd_80178D40`, `Blk_8016CF04`, …). If a later pass finds the same 0x14 header in
   `engine_types.h`, lift it — the draft's field offsets are the contract, not the name.
4. `func_8017DC1C` takes **one** argument. The TU currently carries
   `INCLUDE_ASM(... , func_8017DC1C);` at line 3780 with no prototype, so there is no
   arity conflict to resolve. Callers were not audited — that is a bank-time `audit-cdecl` job.

**Suggested chain:** splice → `make extract BINARY=ov_SC07_006 && make build BINARY=ov_SC07_006`
(byte-identical) → `tools/harvest_verify.py --binary ov_SC07_006 --drafts <dir> --chunk 1`.
No `config/` change is required (no carve), so this should be a T3 bank, not a T2.

---

## 6. Remaining residual classes

**None on the candidate gate.** Zero mismatched instructions, zero pins, zero
`__asm__` dials, no hand-placed anything. Every construct in the draft is plausible
original source: a `static inline` blend helper, a 0x14 model header, 64 global pointers.

The open work is entirely banking plumbing, which is the parent's.

---

## 7. Artifacts

| file | what |
|---|---|
| `.run/giants/s21_func_8017DC1C_b1.c` | **the draft — MATCH (1518 ins)**, bank-ready decls, full lever header |
| `.run/giants/s21_8017DC1C_report.md` | this report |
| `.run/giants/s22_compact.txt` | the target disassembly, one line per insn — the decode surface |
| `.run/giants/s22_cc.sh` | pinned-triple compile of one draft into a work dir (`cc1 → maspsx → as`) |
| `.run/giants/s22_norm.py` | side-by-side normaliser: cc1/maspsx asm vs a splat `.s`, `$N`→names, `lw $r,SYM`→`lui`+`lw` |
| `.run/giants/s22_score.py` | canonicalising scorer (`addu imm`→`addiu`, hex→dec, labels→`LBL`) — drives the permutation sweeps |
| `.run/giants/s22_p1..p5.c` | the five build probes (1 block → 2 blocks byte-exact) |
| `.run/giants/s22_a_{A,B,C,D,E,F,G,H}.c` | the eight drop-one ablations behind §4 |
| `.run/giants/s22_b0.c` | self-contained variant (local `SVECTOR2` typedef) — also MATCH, kept as the no-probe gate path |
