# func_8017D960 (behemoth #2, 3,338 ins, `ov_SC03_090`) — session 20 report

## Verdict

**CRACKED. `match_one` = MATCH (3338 ins). PIN-FREE.**

```
python3 tools/match_one.py func_8017D960 \
  --c .run/giants/s19_func_8017D960_b5.c \
  --asm-subdir asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80
-> MATCH (3338 ins)  func_8017D960

python3 tools/symcheck.py func_8017D960 \
  --c .run/giants/s19_func_8017D960_b5.c \
  --asm-subdir asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80
-> SYMS-OK  func_8017D960   21 symbols agree
```

Independent re-verification through a private pipeline (`.run/giants/d960_cc.sh` +
`d960_full.py`, own work dir, no shared build): `mine=3338 target=3338  0 mismatched`.
`b3_align.py`: register-MASKED **3338/3338 = 100.0 %**, register-KEPT **3338/3338 = 100.0 %**.

`match_one` is the CANDIDATE gate. The whole-binary SHA1 rebuild (G3/P9) is the sole
arbiter and has **not** been run — the task forbade touching the build tree.

Deliverable: **`/home/musashi/bfm-decomp/.run/giants/s19_func_8017D960_b5.c`**
(full dossier header in the b3/b4 style).

Trajectory, all measured: `1806 → 333 → 325 → 190 → 106 → 67 → 54 → 33 → 12 → 8 → 0`.

---

## 1. The −4 length drift — resolved, and the prior diagnosis was wrong

The prior summary read "3,334/3,338, one fold OR-chain error left". **The −4 was never in
the colour chain.** Aligning the b2 baseline hunk-by-hunk (`b3_align.py`) attributes it
exactly: **4 emit tails × 1 instruction**, at `tgt[1643]`, `tgt[1688]`, `tgt[3234]`,
`tgt[3281]` — the four sites where the target materialises the `0xFFFFFF` OT mask.

```
        TARGET                                 b2 DRAFT
 1636  lw   $v0, 0x4($a1)      ; tp[1]     lw   v0,4(a2)
 1637  nop                                 lui  a0,0xff        <-- b2 fills the slot
 1638  sw   $v0, -0x18($t2)                sw   v0,-24(t2)
 1639  lw   $v0, 0x8($a1)                  lw   v0,8(a2)
 1640  lui  $v1, 0x9000000>>16             ori  a0,a0,0xffff
 1641  sw   $v0, -0xC($t2)                 sw   v0,-12(t2)
 1642  lw   $v0, 0xC($a1)                  lw   v0,12(a2)
 1643  lui  $a1, 0xFFFFFF>>16              lui  v1,0x900
 1644  ori  $a1, $a1, 0xFFFF               sh   v0,0(t2)
 1645  sh   $v0, 0x0($t2)                  addiu t2,t2,40
```

Both sides emit the same three constant-forming instructions (`lui`+`ori` for `0xFFFFFF`,
`lui` for the OT tag) and have three `tp[]` load-delay slots to fill. The target's
`0xFFFFFF` lives in **`$a1`, the same register as `tp`**, so it *cannot* be materialised
until `tp`'s last load retires — it lands in the last slot, and the first slot stays a real
`nop`. The b2 draft's `0xFFFFFF` lives in `$a0`, free from the start, so maspsx hoists it
into the first slot: one fewer instruction, four times.

**Root cause, one level up:** `u32 *otp;` at function scope has **4 deaths**, so
`local-alloc.c:472` (`REG_BASIC_BLOCK >= 0 && REG_N_DEATHS == 1`) refuses it → global
allocno → `combine_regs` (`local-alloc.c:1825`) cannot tie the `(g.opz>>2)<<2` chain into
it, and `otp` squats in `$a2`. Via `global.c:668-671` (pseudos local-alloc has already
placed are re-marked as **hard registers** for global-alloc's conflict scan) that pushes
`tp` off `$a1` and the `0xFFFFFF` constant onto `$a0`.

**Fix — L1: declare `u32 *otp;` inside each of the four emit arms.**
One edit: `mine=3334 → 3338 ins`, `1806 → 333 mismatched`, 98.8 % → 99.3 % structural.
This is `func_8017F510`'s L1 (cookbook §76) applied unchanged. It also collapsed the whole
"OT-tag vs 0xFFFFFF ordering" residual class that the b2 dossier listed separately.

---

## 2. The nine levers (all individually necessary — drop-one ablation measured)

Baseline b2 = `3334 ins / 1806 mismatched / 88.3 % byte-aligned`.

| # | Lever | Mechanism | Ablation (drop it from the MATCHing draft) |
|---|---|---|---|
| L1 | `u32 *otp;` **per emit arm** (×4) | `local-alloc.c:472` 1-death gate → `combine_regs` tie; `global.c:668-671` knock-on | **3334 ins, 1646 mismatched** |
| L2 | **no register pins** (5 removed) | a pin is a preference (§72); gcc finds the target light-box allocation itself | 8 mismatched |
| L3 | `u32 vw, vzw;` dedicated vertex-word temps | reusing `w`/`wz` (also prim-word + `part->zz`) inflates `reg_n_refs` (`global.c:594`, ×loop-depth 3) so they outrank the scratch pool | 96 mismatched |
| L4 | RC-15 zero-byte dial `__asm__ __volatile__("" :: "r"(mny))` at the head of the **tri** cull block | `mny` is defined first but lives longer → `allocno_compare` ranks `my` above it; +3 refs flips the grant to `mny→$a2, my→$a3` | 39 mismatched |
| L5 | `base = D_800AF630;` as the **first statement** (before the 3 calls) | makes it call-crossing → callee-saved `$s0` (target) instead of `$v1`; also fixes the `D_800A6610` / `sw $s7` emission order | 9 mismatched |
| L6 | `f2 = 0; f1 = 0; f0 = 0;` (reverse order) | `$s2`/`$t6` init order, 2 sites × 2 ins | 4 mismatched |
| L7 | `u32 cb;` shared colour base — tag constant in the lit arms **and** `tp[0]&0xFF000000` in the unlit arms | (a) a VARIABLE tag is opaque to `fold`'s `associate:` reassociation; (b) the extra refs win `$a0` for the unlit rgbc | 181 mismatched |
| L8 | `u32 rgbw;` shared lit-rgb result temp | multi-death variable breaks the `qty_compare` tie so the `sll` temp is granted first and takes `$v0`, leaving the accumulator `$v1` | (folded into L7's ablation) |
| L9 | `s32 za, zb;` **per case** (both innermost cull blocks) | flips the quad z-max grant `za→$a0`, sz1-temp→`$v1` | 8 mismatched |

`L2/L5/L6/L9` each look like "only 4–9 instructions" in isolation; the point is that all
nine are simultaneously required — the ablation column is measured against the *matching*
draft, not against b2.

### L7 in detail — `fold` will not leave a literal tag in the first `|`

The target's colour chain is, at all 7 sites:

```
or   $v1, $c, $a0      ; $a0 = 0x34000000 (GT3) / 0x3C000000 (GT4)
sll  $v0, $c, 8
or   $v1, $v1, $v0
sll  $v0, $c, 16
or   $v1, $v1, $v0
sw   $v1, ...
```

i.e. `((c | K) | (c<<8)) | (c<<16)` evaluated strictly left to right. With `K` a *literal*,
gcc-2.7.2's `fold` (`fold-const.c`, the `associate:` block / `split_tree`) always hoists the
constant out of the first `|` and re-emits `c | ((c<<8) | K) | (c<<16)` — 5 instructions in
the wrong operand shape. **Seven parenthesisations were measured and every one folds**
(table below). Making `K` a *variable* is the only thing that stops it; that is the same
device `func_8017F510` used (`cb = (tp[0] & 0x2000000) | 0x34000000`).

### L8 in detail — a pure `qty_compare` tie

From the `.lreg` dump of the 54-mismatch draft, one chain is pseudos 1137/1139/1141
(accumulator, tied by `combine_regs`) and 1138/1140 (the `sll` temps):

* accumulator qty: 6 refs, `death−birth` = 5 → `floor_log2(6)*6/5*10000` = **24000**
* each temp qty:   2 refs, `death−birth` = 1 → `floor_log2(2)*2/1*10000` = **20000**

so the accumulator is granted first and takes `$v0` (`find_free_reg` scans ascending —
MIPS defines no `REG_ALLOC_ORDER` in 2.7.2). Routing the result through a **multi-death**
variable (`rgbw`, 7 sets/7 deaths) prevents the whole chain from becoming one high-priority
qty, the temps are granted first and take `$v0`, and the accumulator gets the target's `$v1`.
Measured `54 → 33` with `uvw`, `→ 12` with a lower-ref carrier.

---

## 3. Every lever tried, with its measured result (do-not-re-buy list)

All numbers are `match_one` "mismatched" at 3338 ins unless an instruction count is shown.
Probe cost ≈ 0.7 s (`.run/giants/d960_score.sh`).

### Stage 0 — single levers on the b2 baseline (1806)
| Lever | Result |
|---|---|
| **`otp` per emit arm** | **3338 ins, 333** — the entire length drift |
| `nopins` | 1798 |
| `tp` per arm | 1802 |
| `uvw` per arm | 1806 (neutral) |
| dedicated `rgbw` temp, 4-term expr | 1806 (neutral) |
| 3-statement `uvw` accumulator (`b2_rgbchain`) | 3333 ins, 2016 — 99.0 % masked but **76.0 %** byte |
| 3-statement dedicated-`rgbw` accumulator | 3333 ins, 2016 / 76.1 % |
| inline `D_800AF630` (drop `base`) | 3330 ins, 3207 |
| `otp` / `tp` per *case* | C89 parse error (the insertion point is not a block head) |

### Stage 1 — on `otparm` (333)
| Lever | Result |
|---|---|
| **`nopins`** | **325** |
| `uvw` per arm / dedicated `rgbw` | 333 (both neutral) |
| `tp` per arm | 3336 ins, 1800 |
| 3-statement accumulator | 3337 ins, 2031 / 78.0 % byte |
| inline `D_800AF630` | 3334 ins, 3217 |

### Stage 2 — colour-chain expression shape, on `otparm+nopins` (325)
| Expression | Result |
|---|---|
| `c \| K \| (c<<8) \| (c<<16)` (b2) | 325 |
| `(c\|K) \| (c<<8) \| (c<<16)` | 325 |
| `((c\|K) \| (c<<8)) \| (c<<16)` | 325 |
| `K \| c \| (c<<8) \| (c<<16)` | 325 |
| `(c<<16) \| (c\|K) \| (c<<8)` | 326 |
| `(c\|K) \| ((c<<8)\|(c<<16))` | 191 / 94.8 % |
| `(c<<16) \| (c<<8) \| c \| K` | 192 / 94.8 % |
| `kk = K;` fn-scope, `c\|kk\|(c<<8)\|(c<<16)` | 3334 ins, 1747 |
| `col = c\|K;` fn-scope, `col\|(c<<8)\|(c<<16)` | 3347 ins, 2759 / **51.4 %** |
| `kk` per **arm**, `(c\|kk)\|(c<<8)\|(c<<16)` | 690 — 99.6 % masked (structure right) but **79.6 %** byte: a fresh local pseudo in `$a0` wrecks the ATTEN blocks via `global.c:668-671` |

**Conclusion: the tag must be a variable AND must not be a fresh short-lived local.**
Reusing an already-busy variable (or a fn-scope one) is what works.

### Stage 3 — which variable carries the tag constant (on 325)
| Carrier | Result |
|---|---|
| **`d`** (the ATTEN distance temp) | **190 / 94.6 %** |
| **`xb32`** | **190 / 94.6 %** |
| `uvw` | 196 |
| `mxc` | 212 |
| `za` | 3342 ins |
| `zb`, `w` | 3334 ins |
| `t32`, `xa32`, `mnc` | 2900–3000 (length drift) |
| `wz` | 2728 / **27.1 %** |
| `ot` | 1854 / **56.7 %** |

### Stage 4 — f510-derived levers, on the 190 base
| Lever | Result |
|---|---|
| **`vw`/`vzw` dedicated vertex-word temps** | **106 / 96.9 %** |
| `mny` dial, tri cull block only | 163 |
| `mny` dial, both cull blocks | 163 |
| `base` hoisted before the calls | 181 |
| `f2,f1,f0 = 0` order | 186 |
| `wz = part->zz` moved down to its first use | 186 |
| dedicated `cb` for the unlit rgbc | 190 (neutral) |
| inline `D_800AF630` | 3334 ins |

### Stage 5 — stacking (on `…+vw` = 106)
| Stack | Result |
|---|---|
| `+ mny dial (tri only)` | **67** |
| `+ mny dial (both blocks)` | 70 |
| `+ basetop` | 97 |
| `+ fzero` | 102 |
| `+ cbmerge` | 106 (neutral) |
| `+ wzlate` | 3339 ins |
| `+ dial + basetop` | 58 |
| `+ dial + fzero` | 63 |
| **`+ dial + basetop + fzero`** | **54** |
| tag carrier re-swept at 54: `d`=`xb32`=54, `uvw`=60, `mxc`=76, rest worse | |

### Stage 6 — routing the lit rgb result through a variable (on 54)
| Carrier | Result |
|---|---|
| `uvw` | 33 / 99.2 % |
| **`t32` / `za` / `code`** | **12 / 99.6 %** |
| `wz` | 45 |
| `zb` | 3342 ins |
| `w`, `xa32`, `xb32`, `mnc`, `mxc` | length drift, 2900–3000 |

### Stage 7 — routing the *unlit* rgbc through a variable (on 12)
| Carrier | Result |
|---|---|
| **`mnc`** | **8** |
| dedicated `cb` / `uvw` | 12 (neutral) |
| `mxc`, `xa32`, `za`, `code` | 14 |
| `wz` | 47 |
| `w`, `zb` | 3334 ins |
| `xb32` | 2960 |

### Stage 8 — per-case declaration scoping (on 8)
| Lever | Result |
|---|---|
| **`s32 za, zb;` per case** | **0 — MATCH** |
| `s32 a0v, a1v, a2v;` per case | 8 (neutral) |
| `s32 c0..c3;` per case | 26 |
| `s16 x0..z2;` per case | 935 / 44.1 % |
| `s32 f0, f1, f2;` per case | 3340 ins / 43.2 % |

### Stage 9 — cleaning up the shipped spelling (all re-measured)
| Spelling | Result |
|---|---|
| tag on reused `d` + result on `t32` + unlit on `mnc` | MATCH (first hit) |
| dedicated fn-scope `kk` for the tag | MATCH |
| `kk` per lit arm | 516 |
| dedicated fn-scope `rgbw` for the result | MATCH |
| **one shared `cb` for tag *and* unlit rgbc + `rgbw` for the result** | **MATCH — shipped** (it is also `func_8017F510`'s shape) |
| dedicated `cb` used *only* for the unlit rgbc | 3334 ins |
| `prim = …; nprim = …;` order swapped | MATCH (free either way) |

---

## 4. Generalisable findings (cookbook candidates)

1. **A negative length drift can be a *delay-slot* artifact, not a missing computation.**
   Four "missing" instructions here were four `nop`s the target pays and the draft filled.
   Whether a constant can be hoisted into a load-delay slot is decided by *which register it
   was granted*, i.e. by the allocator — so a length drift can be an allocation bug. The
   correct first move is still "fix the length", but the lever may be nowhere near the
   instructions that differ. (Extends the §76 note that a schedule diff is often a grant in
   disguise; here it is a *length* diff that is a grant in disguise.)

2. **`fold` never leaves a literal in the first term of an `|` chain (gcc-2.7.2).**
   `(c | K) | X | Y` is always re-associated to `c | (X | K) | Y`. If the target shows
   `or acc, var, K` as the *first* instruction of a chain, the constant was a **variable** in
   the original source. Seven parenthesisations were measured; none survives. This is a
   cheap, decisive tell — worth a cookbook line next to §76.

3. **"Make it a variable" has two independent, separately-tunable effects**, and the second
   one is where drafts stall: (a) it is opaque to `fold`, fixing *structure*; (b) it creates
   an allocno whose *class* and *ref count* decide the registers. A **fresh, short-lived
   local** gets the structure right and the allocation catastrophically wrong (690 mismatched
   / 79.6 % here, with the damage 300 instructions away in the ATTEN blocks). Reusing an
   already-busy variable, or a function-scope one, gets both.

4. **The matched sibling is the highest-value oracle in a family.** Five of the nine levers
   (`vw/vzw`, the `mny` dial, `base` first, `cb`, `za/zb` per case) were read straight off
   `func_8017F510` / `func_8017CA80` and each paid immediately. Reading the two matched
   relatives took ~5 minutes and was worth more than every expression-shape sweep combined.

5. **A `register __asm__` pin that is "safe" can still be wrong.** The five b2 pins passed the
   §74 audit (no `jal` spans them) and were still costing 8 instructions at the end; removing
   them was strictly better at *every* stage measured. Second data point (after
   `func_8017F510`) that this family cracks pin-free.

---

## 5. Family payoff

All five unmatched `h_norm`/`h_seq` siblings are **3,338 instructions** and differ from
`ov_SC03_090` only in the 15 light-descriptor symbols (5 per box × 3 boxes):

| Function | Overlay | Light-box symbols |
|---|---|---|
| `func_8017D960` | `ov_SC03_089` | `D_801C67F8` / `D_801C6814` / `D_801C6830` |
| `func_8017D960` | **`ov_SC03_090`** | `D_801CBC68` / `D_801CBC84` / `D_801CBCA0` (**this crack**) |
| `func_8017D960` | `ov_SC03_104` | `D_801C0370` / `D_801C038C` / `D_801C03A8` |
| `func_8017E778` | `ov_SC03_091` | `D_801D25B8` / `D_801D25D4` / `D_801D25F0` |
| `func_8017CD9C` | `ov_SC03_102` | `D_801B9B00` / `D_801B9B1C` / `D_801B9B38` |

Everything else (`D_800A5E60`, `D_800A6610`, `D_800AF630`) is shared. Straight
`tools/family_remap.py` territory: ≈ **16,690 instructions of distinct code** behind this
one crack.

---

## 6. Artifacts preserved (all under `.run/giants/`)

| File | What |
|---|---|
| `s19_func_8017D960_b5.c` | **the MATCHing draft** (dossier header, 9 levers documented) |
| `s19_d960_report.md` | this report |
| `d960_mk.py` | the lever/variant generator — every lever in this report is a named, self-checking transformation (it asserts its edit applied, so a "neutral" reading can never be a silent no-op) |
| `d960_cc.sh` | one-draft compile through the pinned triple into a private work dir (`-da` for RTL dumps) |
| `d960_score.sh` | 0.7 s probe: `mine/target/mismatched` + both `b3_align` percentages |
| `d960_full.py` | uncapped index-wise diff (`match_one` caps at 40) |
| `d960_side.py` | side-by-side mine/target listing over an index range, mismatches starred |
| `d960_hist.py` | bucketed histogram of byte-divergent target indices (localises a cascade fast) |
| `b3_align.py` | (pre-existing) the aligner that attributed the −4 drift |

Work dirs and RTL dumps live in `.run/s20/` (untracked). The one worth keeping is
`.run/s20/w_dump/t.i.{lreg,greg}` — the 54-mismatch baseline whose `qty_compare` numbers the
L8 analysis is computed from.

## 7. Not done here

* The whole-binary SHA1 gate (G3/P9) — the task forbade touching the build tree.
* The five family remaps — the caller owns those.
