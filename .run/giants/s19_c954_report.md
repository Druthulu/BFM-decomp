# func_8017C954 (behemoth #5, 1,194 ins, `ov_SC06_029`) — session 20 report

## Verdict

**CRACKED. `match_one` = MATCH (1194 ins).**

```
python3 tools/match_one.py func_8017C954 \
  --c .run/giants/s19_func_8017C954_b1.c \
  --asm-subdir asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017AE2C
-> MATCH (1194 ins)  func_8017C954
```

Independent re-verification with a private pipeline (`.run/giants/c954_cc.sh` +
`c954_full.py`, same pinned triple, separate work dir):

```
mine=1194 target=1194  0 mismatched
b3_align: register-MASKED 1194/1194 = 100.0%   register-KEPT 1194/1194 = 100.0%
```

`symcheck` reports `SYMS-DIFF … MISSING jtbl_801DB70C` — that is the **name** of the
compiler-emitted `.rodata` jump table, not a code difference. The table my compile
emits is byte-identical in content:

| index | my `.rodata` offset | target `jtbl_801DB70C` | arm |
|---|---|---|---|
| 0,1 | 0x980 | 0x8017D2D4 − 0x8017C954 = 0x980 | C (POLY_F4) |
| 2   | 0xBE4 | 0x8017D538 − base = 0xBE4 | D (POLY_FT4) |
| 3   | 0xEB8 | 0x8017D80C − base = 0xEB8 | **E (new)** |
| 4,5 | 0x5D4 | 0x8017CF28 − base = 0x5D4 | A (POLY_F3) |
| 6,7 | 0x794 | 0x8017D0E8 − base = 0x794 | B (POLY_FT3) |

`match_one` is the **candidate** gate. The whole-binary SHA1 rebuild (G3/P9) is the
arbiter and has **not** been run — the task forbade touching `src/`, `config/` or the
build tree. Two integration items for the banker: the `jtbl_801DB70C` rodata carve,
and `extern s32 D_801DCCA0;` (already declared in the TU at
`src/ov_SC06_029/ov_SC06_029_jr_8017AE2C.c:3302`).

Deliverable draft: `/home/musashi/bfm-decomp/.run/giants/s19_func_8017C954_b1.c`
(~160-line dossier header, b4/b5/b2 style).

Starting point: base = the matched 952-ins `func_8017CA80` renamed → 1129 mismatched,
`SIZE-MISMATCH/short`. Progression: 1129 → 1069 (structure decoded, −3 ins) → 37 → 28 → **MATCH**.

---

## The delta vs the matched base `func_8017CA80` (952 ins)

Identical skeleton — same 3-call prologue, same Part[] outer loop / 8-corner AABB /
otz + screen-bbox reject, same Prim[] inner loop, same OT insert, same
`D_800A5E60 = pkt`. **+242 instructions in exactly two places:**

### 1. Prologue, +14 ins — two replicated grey colour words

```c
pkt = D_800A5E60;
ot  = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
d   = D_801DCCA0;                       /* fade / flash level */
colA = (d << 16) | (d << 8) | d;        /* -> spill slot 0x108 */
e = d * 2;
if (e > 0xFF) e = 0xFF;                 /* u32  =>  `sltiu $v0,$a1,0x100` */
colB = (e << 16) | (e << 8) | e;        /* -> spill slot 0x110 */
part = …; nparts = …; vtx = …;          /* AFTER the clamp branch */
```

`e` must be **unsigned** (the target compares with `sltiu`, not `slti`). The split of
this block around the clamp `if` is directly readable from the target: sched.c cannot
move insns across a basic-block boundary, so everything emitted before
`bnez $v0,.L8017CA00` is in source before the `if`, and `part`/`nparts`/`vtx` — emitted
after — are in source after it. First guess was right, first try.

### 2. The switch gains a **fifth arm**, +228 ins

`case 2` and `case 3` split (proved against the real `jtbl_801DB70C` in
`asm/ov_SC06_029/data/tail21.data.s`, table above). `case 2` keeps the base's FT4 body
verbatim — including the now-dead `if (code == 3) g.opz = za + 0x200;`, i.e. the
original author copy-pasted. `case 3` = **arm E**, which emits **two** packets per prim:

* **P1** — POLY_FT4 (0x28, OT tag `0x9000000`): same geometry and UVs as arm D, but
  `rgbc = colA | 0x2E000000` (GPU 0x2E = textured quad, semi-transparent) instead of
  `tp[0]` — so `tp[0]` is never read at all.
* **P2** — a 7-word (0x1C, OT tag `0x6000000`) overlay:
  `+0x00` tag, `+0x04` `0xE1000040` (GPU **E1 draw-mode**, semi-transparency mode 2 =
  `B − F`, i.e. subtractive), `+0x08` `colB | 0x2A000000` (GPU 0x2A = flat quad,
  semi-transparent), `+0x0C…+0x18` the four screen-xy words.
  `pkt[3] = 6;` writes the `P_TAG` len byte by hand before the tag word overwrites it
  (a PsyQ `setlen()` habit).

Arm E also differs from arm D in how it loads the 4th vertex:

```c
vv[3] = *(SVECTOR2 *)vd;      /* SVECTOR2 align = 2  =>  mips.c output_block_move   */
gte_ldv0(&vv[3]);             /* (align < 4) emits the target's lwl/lwr + swl/swr   */
```

and it `gte_stsxy`'s the 4th projected vertex into `tmpxy[3]` (not straight into the
packet) because **both** packets need all four xy words.

### Frame (0x298) — matches exactly

```
0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 vv[4] |
0xC0 mtx  | 0xE0 g{otz,flag,opz,sz0..sz3} | 0x100..0x26F 46×8-byte spills |
0x270..0x294 saved regs (s0-s7, fp, ra)
```

The §79 frame-slot oracle did the decoding: the *only* sp offsets used in 0xA0..0xBF
are 0xB8/0xBB/0xBC/0xBF, and `mtx` sits at 0xC0 rather than the base's 0xA0 — so a new
**0x20-byte** object is declared between `sxy` and `mtx` and the 8-byte copy lands at
its +0x18. `SVECTOR2 vv[4]` with only `vv[3]` used reproduces it (gcc allocates a whole
array regardless of which elements are referenced).

Spill order (§79 = pseudo number = declaration order):
`lim 0x100, colA 0x108, colB 0x110, nprim 0x118, nparts 0x120, part 0x128, i 0x260,
(part+0xC giv) 0x268` — note **nprim before nparts**, which is why the draft declares
`u32 nprim;` ahead of `s32 nparts;` unlike the base.

---

## Every lever tried, with its MEASURED result

The quoted metric for the first three rows is `c954_reg.py` **register-KEPT
aligned-identical %** (length-drift-proof; `match_one`'s index-wise count is useless
while the length is off). Once the length hit 1194 the metric is `match_one`.

| # | Lever | Measured |
|---|---|---|
| — | base (952-ins `func_8017CA80` renamed) | 1129 mismatched, SIZE-MISMATCH/short |
| — | + prologue colour block + `vv[4]` + case-2/3 split + arm E (**b1**) | 1191 ins, masked 95.9 %, **kept 62.6 %** |
| **L1** | `__asm__ __volatile__ ("" ::: "$3")` after arm E's y min/max | **kept 94.9 %** (masked 98.8 %) |
| **L2** | `u32 nprim;` declared before `s32 nparts;` | +3 structural ins → kept **95.2 %**, masked **99.2 %** |
| **L3** | arm E P1 store order: 4×xy, `tp`, rgbc, 3×uv | kept **95.5 %**, masked **99.4 %** |
| **L4** | **two separately-scoped `otp`s in arm E** (one per OT insert) + first insert reads `za` | 1202 → **1194 ins**, **37 mismatched** |
| **L5** | arm E P2 store order: len, +0x08 colour, +0x0C xy0, +0x04 `0xE1000040`, +0x10/+0x14/+0x18 | **28 mismatched** |
| **L6** | **zero** `__asm__ volatile ("")` live-length sliders | **MATCH** |

### L1 — the dominant lever, and the reusable finding

`my`, `mny`, `mx`, `mn` are four `s16` **global** allocnos (pseudos 103..106; refs 103,
live length 245..282). The target grants them `my=$a2 mny=$a3 mx=$t0 mn=$t1` — exactly
what the matched 952-ins base compiles to, and the base's grant is byte-identical to
this function's in all four *unchanged* arms.

Adding the fifth arm makes `my` and `mny` **lose their hard-register conflict with
`$v1`** and instead acquire a *copy preference* for it. Straight from the `.greg` dump:

```
;; 103 conflicts: … 2 12 29          <- $v1 (3) absent
;; 103 preferences: 3                <- and now preferred
```
vs. the four-arm control, where all four read `… 2 3 12 29` and have no preference.
`my` therefore takes `$v1` and the **whole quad slides one slot down
`reg_alloc_order`** — `v1,a2,a3,t0` instead of `a2,a3,t0,t1`. One slide renames ~40 %
of every switch arm (arms A–D fell from 97–98 % kept to 57–63 %).

Bisected to the statement: with arm E truncated right after its y min/max the conflict
survives; adding **any** block after it — even
`if (!(g.flag & 0x7F85E000)) { pkt += 4; }` — destroys it. A *small* 5th arm, or a
verbatim duplicate of arm D, does not break it, so it is the size/shape of arm E, not
the arm count.

Only `"$3"` works. `__asm__ volatile("")`, `"$2"`, `"$4"` and `"memory"` clobbers are
all exact no-ops here (each measured). The dial emits `#APP / <empty> / #NO_APP`, i.e.
**zero instructions** — the compile is 1194 EXACT with it and 1182 without it.

**Generalisable:** when a giant's residual is "a whole block of registers renamed by one
slot", read the `;; N conflicts:` **and** `;; N preferences:` lines of the `.greg` dump
for the highest-priority allocno in the block. A *missing* hard-register conflict plus a
*new* copy preference is the signature of a one-slot slide, and it is one dial away —
not forty bugs. (Extends §76: the allocno **class** lever has a sibling, the allocno
**conflict** lever, and C reaches the latter only through what happens to be live.)

### L4 — the family's `otp` lever, applied inside a single arm

One `otp` used by both OT inserts has **2 deaths** → `local-alloc.c:472`
(`REG_BASIC_BLOCK >= 0 && REG_N_DEATHS == 1`) rejects it → global allocno →
`combine_regs` (`local-alloc.c:1825`) cannot tie the `(za>>2)<<2` shift chain into it,
so the chain needs a separate `$v0` scratch. `$v0` is exactly the register the four
`lw/sw` xy pairs use, so the scheduler can no longer put `sra/sll/addu` into their
load-delay slots and **maspsx emits three `nop`s** — those three nops plus the extra
`lw`+`lui` were the entire remaining length drift. Scoping each insert's `otp` in its
own block makes both 1-death/1-block pseudos, the chain ties in place in `$a0`, and the
nops become the target's `sra $a0 / sll $a0 / addu $a0,$a0,$s0`.

The first insert must read **`za`**, not `g.opz`: `g`'s address is taken by the gte
macros, so `g.opz` would have to be re-loaded after the aliasing `pkt` stores and could
never be hoisted into the delay slots. (Arm D keeps `g.opz` — it has the conditional
`+0x200` — and that is exactly why the target's arm D holds `za` in `$v1` while arms C
and E hold it in `$a0`.)

### L6 — the §47 slider, with the opposite sign

The matched 952-ins base ships **one** `__asm__ volatile ("")` to split the
`&g.sz1` / `&g.sz2` allocno tie. Here the correct count is **none**:

| sliders | result |
|---|---|
| **0** | **MATCH (1194)** |
| 1 | 1193 ins, 1090 mismatched |
| 2 | 1194 ins, 28 mismatched |
| 3 | 1194 ins, 10 mismatched |
| 4 | 1194 ins, 28 mismatched |
| 5 | 1193 ins, 1088 mismatched |

Same mechanism: `allocno_compare` (`global.c:594`) gives the three `&g.szN` pointers
refs 16 and live lengths within 2 of each other, so `int(4*16*10000/L)` puts them one
apart and *every static instruction added anywhere in the outer loop* re-ranks them.
The final 28 mismatched instructions were exactly this — a 3-cycle on
{`vtx`, `&g.flag`, `0x7F85E000`} (`$s7/$s5/$s6` → `$s6/$s7/$s5`) and a swap on
{`&g.sz1`, `&g.sz2`} (`$s1` ↔ `$t8`) — and they all fell in one edit.

---

## Do-not-re-buy list (byte-measured; each entry is scoped to its base — §80(i))

### On the b1 base (1191 ins, kept 62.6 %)

| Lever | Result |
|---|---|
| **all 24 permutations** of `s16 my, mny, mx, mn` | **all exactly 62.6 % / 95.9 %** — the four are not tied |
| 9 positions for that declaration in the decl list | all exactly neutral |
| `colA/colB` declared first / last / adjacent to `d,e` | 62.4 / 62.5 / 62.6 (neutral-to-worse) |
| `ot` hoisted above the three calls | 61.7 % (worse) |
| `ot` moved after the clamp `if` | −1 ins, much worse |
| `e = d << 1` instead of `d * 2` | exactly neutral |
| `nprim` read before `prim` in the part loop | 62.6 % (neutral) |
| dedicated arm-E min/max vars — function-scope, block-scope, x-only, y-only | 59.6–62.6 % (all neutral or worse) |
| reversed y comparison in arm E | 62.5 % |
| `t32` temp for `tmpxy[2].vx/.vy` in arm E | 55.4 % |
| `gte_ldv0(vd)` instead of the `vv[3]` block copy | 53–57 % and loses the target's lwl/lwr |
| arm E y-block **before** x-block | 75.0 % kept, +7 ins — right REGISTERS, x/y swapped. **The diagnostic** that proved the residual was one allocno slide |
| two separately-scoped `otp` (before L1/L2/L3) | 64.7 % |
| first `otp` from `za` (before L1) | worse |
| `x_e1swap` (P2 colour before E1) | exactly neutral **on this base** — it only pays at 37 |

### On the clobber base (kept 94.9 %)

| Lever | Result |
|---|---|
| first `otp` from `za` **alone** | 92.2 % — flips a `$fp` tie in the head (pseudo 78 `j` vs 80 `part`, both refs 8, lengths 985/984 → 984/983) |
| same + one extra zero-byte slider | 94.8 % (tie restored, but still +7 ins) |
| `otp` assignment moved right after `g.opz = za` | identical to leaving it in place (sched normalises) |
| six P1 store orderings (`tp` first / rgbc first / `tp` mid / no `uvw` / rgbc after x2 / x3 last) | 95.0–95.5 % |

### On the MATCH base

| Lever | Result |
|---|---|
| remove the `"$3"` dial | 1182 ins, 1081 mismatched |
| replace it with `""`, `"$2"` or `"memory"` | 1182 ins, 1085 mismatched |
| separate arm-E min/max vars (x, y, or both) | 1182 ins, 1081–1084 mismatched |
| arm E y-block before x-block | 1194 ins, 172 mismatched |
| P2 orderings: E1 last / len last / E1+len / colour+2×xy | 92 / 176 / 39 / 37 mismatched |

**§80(i) confirmed again, twice.** `x_e1swap` measured *exactly neutral* at kept 62.6 %
and was worth −2 mismatched at 37. The `za` lever measured *worse* on the clobber base
and became *necessary* two levers later. Both were on the discard pile.

---

## The one honest caveat

Lever L1 is a hand-placed **register-clobber dial**, not a construct a 1998 programmer
would have typed. It is byte-free (empty template; `#APP`/`#NO_APP` only) and the
compile is 1194 EXACT, so the delivered object is the target — but it stands in for
whatever the original source did to keep `$v1` busy across arm E's y min/max, and that
source shape has not been found. Fourteen "natural" spellings were tried and measured
(table above). **The single most promising next move** is to find it: bisect further
*inside* the `if (!(g.flag & 0x7F85E000))` block that first destroys the conflict, and
compare the `t.i.lreg` (post-local-alloc) RTL of the four-arm control against the
five-arm draft over arm A's y2 block — the value the target keeps in `$v1` there is a
two-block copy pseudo, and finding which local-alloc decision moves it off `$v1` should
name the missing statement. Until then the dial is a documented, measured stand-in and
the byte result is unaffected.

---

## Artifacts preserved (all under `.run/giants/`)

| File | What |
|---|---|
| `s19_func_8017C954_b1.c` | **the MATCHing draft** (dossier header) |
| `s19_c954_report.md` | this report |
| `c954_cc.sh` | one-draft compile through the pinned triple into a private work dir, with `-da` RTL dumps |
| `c954_probe.sh` | one-line `match_one` score for a variant (parallel-safe) |
| `c954_score.sh` | length-drift-proof score (b3_align masked % + kept %) |
| `c954_probe2.sh` | score **plus** the my/mny/mx/mn grants and their `$v1` conflict flag |
| `c954_full.py` | uncapped index-wise masked diff (`match_one` caps at 40) |
| `c954_side.py` | side-by-side mine/target listing over an index range, mismatches starred |
| `c954_reg.py` | **per-region** aligned-identical report (head / dispatch / 5 arms / tail) — the tool that made this crack tractable |
| `c954_alloc.py` | allocno census: rank / refs / live length / `allocno_compare` priority / granted hard reg |
| `c954_slots.py` | §79 frame-slot census, target vs draft |
| `c954_regmap.py` | register-correspondence census |
| `c954_mk.py` / `c954_sweep.sh` / `c954_sw.sh` | asserting variant generator + 8-way parallel sweeps |

Working variants and RTL dumps live in `.run/c954/` (untracked). The two dumps worth
keeping are `.run/c954/w_dump/t.i.{lreg,greg}` (the b1 baseline, where `my`/`mny` lack
the `$v1` conflict) and `.run/c954/w_abl_noEd/t.i.greg` (the four-arm control, where
they have it) — that pair *is* the L1 finding.
