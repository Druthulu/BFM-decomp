# `func_8017BF14` — behemoth #4, 4,763 ins, `ov_SC03_116` — COLD-START REPORT

**Session 20, 2026-07-25.** Cold start: no prior draft, no `h_norm`/`h_seq` sibling
(family size 1), 0 callees.

---

## 1. FINAL NUMBER (measured, `tools/match_one.py`, the CANDIDATE gate)

```
python3 tools/match_one.py func_8017BF14 --c .run/giants/s19_func_8017BF14_b1.c \
  --asm-subdir asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C
-> DIFF  func_8017BF14   mine=4763 ins, target=4763 ins, 45 mismatched
```

| metric | value |
|---|---|
| instruction count | **4763 / 4763 — EXACT** |
| opcode histogram L1 distance | **0 — EXACT** (every mnemonic count agrees) |
| stack frame | **EXACT** — frame `0x360`, all **127 slots at the target's offsets** |
| register-masked structural alignment (anchored) | **4760 / 4763 = 99.94 %** |
| byte-identical instructions | **4718 / 4763 = 99.06 %** |
| **NOT A MATCH** | 45 instructions differ |
| pin-free fallback | `s19_func_8017BF14_b1_pinfree.c` → 4763/4763, **789 mismatched**, 100.0 % structural |

The whole-binary SHA1 arbiter (G3/P9) was **not** run — the task forbade touching the
build tree. `match_one` is the candidate check only.

**Class: three register-grant ties.** No structural, length, scheduling-of-blocks,
frame, or expression-shape divergence remains.

---

## 2. THE DECODE

### 2.1 What it is

The **four-light-box** member of the volumetric-light renderer family:

| member | ins | overlay | status |
|---|---|---|---|
| `func_8017BEBC` | ~500 | ov_SC03_099 | MATCHED (unlit ancestor) |
| `func_8017CA80` | 952 | ov_SC03_090 | MATCHED |
| `func_8017F510` | 1511 | — | MATCHED (behemoth #3) |
| `func_8017D960` | 3338 | ov_SC03_090 | MATCHED (behemoth #2, **3 light boxes**) |
| **`func_8017BF14`** | **4763** | ov_SC03_116 | **this one, 4 light boxes** |

`h_norm`/`h_seq` reported family size 1 and the prompt said "no matched relative".
That was true of the *hash* families but **false of the codegen family** — cookbook §71's
callee-set fingerprint could not fire because this function has **zero callees**. The
relative was found instead by **reading the target's globals**: `D_800A5E60` (the packet
cursor) is grepped in `src/`, which lands directly on the matched `func_8017BEBC`.
**Generalisable: for a 0-callee giant, fingerprint by its DATA symbols, not its callees.**

### 2.2 Signature and why it is a leaf

`void func_8017BF14(s32 arg0, s32 lim)` — `sw $a1, 0xB0($sp)` at entry proves arg1.

Every other family member opens with `lim = func_800491EC() + *(s32*)(arg0+0x64);
func_800547D8(arg0+0x10,&mtx); func_80052E38(&mtx);`. Here the caller has already done
that work and passes `lim` in. Consequences, all visible in the frame:
no `$ra` save, no `MATRIX2 mtx` local, and **no 0x10-byte o32 argument area** — so
`tmpxy[4]` starts at `sp+0x00` instead of `sp+0x10`.

### 2.3 Loop nest (2 loops, 414 labels, 0 `jal`)

```
for (j = 0; j < nparts; j++, part++)                 // idx 214..4746, stride 0x14
    build box[8] from part->xx/yy/zz
    gte_ldv3c/rtpt/stsxy3 x2 + gte_ldv0/rtps/stsxy x2 -> sxy[8]
    gte_stszotz(&g.otz);   if (lim >= g.otz) {
    screen bbox X in [-0xA0, 0xA1)  and  Y in [-0x6E, 0x6F)
    for (i = 0; i < nprim; i++, prim++)               // idx 504..4742, stride 0xC
        gte_ldv3(va,vb,vc); gte_rtpt(); gte_stflg();  if (!(flag & 0x7F85E000)) {
        gte_nclip(); code = w & 7; vd = vtx + (w & 0xFFF8); gte_stopz();
        if (g.opz > 0) switch (code) {                // range tree, cases 6,7 then 2,3
          case 6/7: TRI  -> 3 vertices, 3 colours
          case 2/3: QUAD -> 4 vertices, 4 colours
        }
```
Codes 0,1,4,5 are dropped (they are the untextured F3/F4 cases of the unlit ancestor).
gcc emits the 4-case switch as the balanced range tree
`code<2 → skip; code<4 → quad; code>=8 → skip; code<6 → skip; else tri`.

### 2.4 The four light boxes

Stride `0x1C`, `{ s32 enable; u16 cx, cy, cz; s32 range; }` at
`D_80197C28 / D_80197C44 / D_80197C60 / D_80197C7C`.

Falloff geometry differs from the 3-box sibling:

| | `func_8017D960` (3 boxes) | `func_8017BF14` (4 boxes) |
|---|---|---|
| low radius | `RLO = R - 0x80` | `RLO = R - 0x200` |
| x-axis ramp | `A = R - d` | `A = (R - d) / 4` |
| z/y-axis ramp | `A = (A*(R-d)) >> 7` | `A = (A*((R-d)/4)) >> 7` |
| colour sum | `c = a0+a1+a2` | `c = a0+a1+a2+a3 + 0x10` |
| unlit rgbc | `tp[0] & 0xFF000000` | `(tp[0] & 0xFF000000) \| 0x101010` |

The `/ 4` is a **signed divide** (`bgez / addiu 3 / sra 2`), not `>> 2`.
The `+ 0x10` ambient bias is applied before the `> 0x80` clamp.

### 2.5 The frame (0x360)

```
0x000 tmpxy[4]      0x010 box[8]        0x050 sxy[8]
0x090 g{otz,flag,opz,sz0..sz3}
0x0B0 lim   0x0B8 j   0x0C0 i   0x0C8 vd   0x0D0 ot   0x0D8 pkt
0x0E0 f2    0x0E8 f3
0x0F0/0x0F8/0x100  x3, z3, y3
0x108 prim  0x110 nprim  0x118 vtx  0x120 nparts  0x128 part
0x130..0x1D0  hi0y,lo0z,hi0z,lo1x,...,hi3z          (21 s16 slots, 8-byte pitch)
0x1D8..0x230  cx0,cy0,cz0 .. cx3,cy3,cz3            (12)
0x238 r0   0x240 r1lo   0x248 r2lo   0x250 r3lo
0x288..0x2D0  LICM-hoisted sign-extended bounds (9 s32 + 1 staging slot)
0x328/0x330   reload-spilled vertex coords (y0, z2)
0x338..0x358  s0-s7, fp     (NO $ra — leaf)
```
`lo0x`, `hi0x`, `lo0y` never get s16 slots: they live only as the hoisted
sign-extended `0x288/0x290/0x2A0` copies.

---

## 3. FOUR ORIGINAL-SOURCE COPY-PASTE ARTEFACTS (all byte-proven)

The 4th light box was **bolted onto a copy of the 3-box source by hand**, and the hand
edit was incomplete in four places. Every one of these was *read off the target*, and
every one removed a measured delta.

| # | artefact | proof in the target |
|---|---|---|
| 1 | `r3lo = r2 - 0x200;` — box 3's low radius comes from box 2's **range variable** | `addiu $t6, $s0, -0x200` at idx 93 reuses the register box 2's `lw D_80197C6C` filled. Spelling it `D_80197C6C - 0x200` re-loads the global (+2 ins, and it re-materialises `lui/lw`). No sign-extension is emitted because the result is `sh`-truncated. |
| 2 | only **six** of the eight radius variables are zero-initialised | entry emits exactly 3 `move rX,zero` + 3 `sh $zero` = r0,r1,r2,r0lo,r1lo,r2lo. `r3`/`r3lo` are left uninitialised — precisely the init list the 3-box version needed. |
| 3 | the box-3 ATTEN **kill test** still says `r2` in 3 of the 7 hand-written copies | all 24 `sll $v0,$s0,16` (r2 sign-extension) sites enumerated: 3 per vertex-group inside box 2, **plus exactly three extras** at idx **1471, 1504** (tri v0 z and y) and **2178** (tri v2 z). All other copies use `$s6` = r3. |
| 4 | quad-lit `rgb2`/`rgb3` take their `<< 16` term from **c1** | the target CSEs **one** `sll $a0,$a0,16` (idx 4641) and re-uses `$a0` at idx 4647 and 4652. Writing `c2<<16`/`c3<<16` costs +2 `sll`. |

Modelling these is not optional cosmetics — #3 alone was `sra+11 / sll+9` and #4 was the
last `sll+2`.

---

## 4. THE LEVERS THAT MOVED THE NUMBER (measured)

Metric below is **byte-identical %** from the anchored aligner
(`.run/giants/bf14_ali.py`), which is length-drift-proof.

| # | lever | before → after |
|---|---|---|
| L1 | unlit `cb = (tp[0] & 0xFF000000) \| 0x101010` | len −64 → −62; retired the whole `or`/`ori`/`lui` histogram delta |
| L2 | artefacts 1 + 3 (box-3 kill register per copy, `r3lo = r2 - 0x200`) | shape 89.15 % → 96.96 %; killed `sra+11 / sll+9` |
| L3 | artefact 4 (quad-lit `c1 << 16`) | killed the last `sll+2` |
| **L4** | **`s32 c0,c1,c2,c3;` declared inside the two CULL blocks** | **52.26 % → 92.86 % — the single biggest lever, and it is what spills `r1lo`** |
| **L5** | **`s32 f0,f1,f2,f3;` moved to immediately after `u8 *pkt;`** | **73.00 % → 83.98 %, and ALL 127 stack slots then match exactly** |
| L6 | `u32 rgbw;` per emit arm | 93.45 % → 94.21 % (with L7) |
| L7 | RC-15 zero-byte ref dial on `mny`, head of the TRI cull block | 93.47 % → 94.21 % |
| L8 | `cb` 2-statement accumulator + quad-lit rgb 3-statement accumulator | 99.06 % → 99.12 % |
| L9 | four register pins: `va→$t2`, `w→$a1`, `f0→$s3`, `c1→$a0` | 94.21 % → **99.06 %** |

### 4.1 L4 — why declaration scope, and not a dial (cookbook §76)

The whole −62 length residual was **one** decision: the target spills `r1lo` to `0x240`
and reloads it 21 times (`lhu` + load-delay `nop` at each of 3 axes × 7 vertex-colour
groups = exactly the measured `lhu −21` / `nop −21` / `sh −2`), while every draft kept
it in `$fp`.

`$fp` is register 30 — the **last** register a plain-ascending `find_reg` scan reaches
(MIPS defines no `REG_ALLOC_ORDER` in gcc-2.7.2, verified in
`tools/reference/gcc-2.7.2/config/mips/mips.h`). So `r1lo` was the *marginal* allocno:
the target simply had **one more competitor** than my draft.

Declaring `c0..c3` inside the two cull blocks supplies that competitor the way the
compiler actually models it: at function scope `c0..c3` have a death in each of the four
emit arms, so `local-alloc.c:472` (`REG_BASIC_BLOCK >= 0 && REG_N_DEATHS == 1`) refuses
them and they become global allocnos; per cull block they are 1-death **local** pseudos,
local-alloc places them, and `global.c:668-671` re-marks those placements as **hard
registers** for global-alloc's conflict scan — removing them from the global pool and
pushing `r1lo` onto the stack.

An `__asm__` ref-dial on `mn`/`mx`/`my`/`mny` inside the lit arm reached the same spill
(84.78 %) and was found *first*; declaration scope is both better (92.86 %) and real C.
**Lesson: when a spill is missing, look for the missing LOCAL allocno before reaching for
a ref dial.**

### 4.2 L5 — the stack-slot order is a declaration-order ORACLE (new, generalisable)

Spilled pseudos are given stack slots in **pseudo-number order** (`reload1.c: alter_reg`),
and pseudo numbers are handed out in **declaration order** (`expand_decl`). Therefore the
target's stack layout is a direct read-out of the original declaration order.

Target: `pkt` at `0xD8`, then **two `lw:9 sw:9` slots at `0xE0`/`0xE8`** (the f2/f3
flags), then three `lhu:7 sh:1` slots (`x3,z3,y3`), then `prim/nprim/vtx/nparts/part`.
My draft had the flags declared late, so everything above `0xD8` was shifted by `0x10`.
Moving one declaration line fixed **every** slot: 127/127.

This is a cheap, deterministic, repeatable technique — `.run/giants/bf14_slots.py`
prints the slot census side by side and any mismatch is a declaration-order bug.
**It should go in the cookbook.**

### 4.3 L9 — pins are safe *here*, and §72 still holds

Cookbook §72/§74: a `register __asm__` pin is a **preference, not a reservation**, and
the real hazard is a caller-saved pin spanning a `jal`. **This function has zero `jal`s**,
so that hazard cannot arise — which is exactly why pins are usable on this family member
and were a trap on the others. Four pins bought 94.21 % → 99.06 %.

§72 was nevertheless reproduced: adding a 5th and 6th pin (`c0→$t4`, `c2→$t2`, both
values the target genuinely puts there) made it **worse — 92.86 %**. Pins do not compose.

A **pin-free** draft is preserved at `.run/giants/s19_func_8017BF14_b1_pinfree.c`
(4763/4763 ins, 789 mismatched, 100.0 % structural, exact frame) for anyone who wants the
conservative variant.

---

## 5. DO-NOT-RE-BUY TABLE (every lever measured, neutral or negative)

Baselines are stated per block because the base moved as levers landed.

### 5.1 Neutral — no effect at all

| lever | result |
|---|---|
| declaration-order permutations of `r0..r3 / r0lo..r3lo` (5 orders swept) | neutral (±4 on a 4526 base) |
| swapping `rN` / `rNlo` assignment order inside each box's `if` (all 4 boxes) | neutral |
| `a0v..a3v` / `d` / `tp` declared per cull block | neutral |
| `a0v..a3v` / `c0..c3` / `d` declared inside the lit arm | neutral |
| moving the whole r-declaration block (top / bottom / before lo-hi / before centres) | neutral |
| declaration position of `s16 my,mny,mx,mn` (6 anchors swept) | **neutral — cannot substitute for the L7 dial** |
| splitting `f0,f1` before `pkt` and `f2,f3` after | neutral |
| `x2,y2,z2` split out / declared late | neutral |
| arm-declaration ORDER (`tp`/`rgbw`/`cb` before vs after `u32 *otp;`) | neutral (4 permutations) |
| `vd` computed later; `va`/`vb` assignment swapped | neutral |
| second ref dial on any of f0..f3, x0..z2, mn/mx/my/mny, w, wz, vw, vzw, i, j, nprim, at prim/cull scope, on top of the best base | neutral or worse (40 probes) |

### 5.2 Negative — actively harmful

| lever | result vs its base |
|---|---|
| `s16 x0..z2` declared per cull block (`xyz_cull`) | 92.86 % → **57.23 %** |
| `s32 f0..f3` declared per cull block (`f_cull`) | 92.86 % → **67.16 %** |
| ref dial on `mn` in the lit arm, once `c_cull` is in | 92.86 % → **63.20 %** (the two levers do the same job and collide) |
| `cb` declared per emit arm | 94.21 % → **91.31 %** |
| `a0v..a3v` per cull block, on top of `c_cull` | 92.86 % → **90.32 %** |
| pinning `c0` and `c2` in addition to `c1` | 99.06 % → **92.86 %** |
| `rgbw` as a 3-statement accumulator in **both** arms | 99.06 % → 98.22 % (quad-only is +0.02 %) |
| `base = D_800AF630` rematerialised at use / hoisted late | 52.26 % → 52.11 % |
| `prim`/`nprim` read order swapped | neutral-to-worse |
| `f0=0..f3=0` in forward instead of reverse order | 92.86 % → 92.78 % |

### 5.3 Rejected diagnoses (each was measured and refuted)

* **"the −62 is missing code."** It was not: the opcode-histogram delta was
  `nop −34 / lhu −21 / sh −2 / addu +1` — a pure spill signature. Confirmed by
  §78's rule: *a `nop` present in the target and absent from the draft is a register
  fact, not missing code.*
* **"`r3lo` comes from `D_80197C88 - 0x200`."** Measured: that spelling re-loads the
  global (`lui/lhu` + `addiu`) instead of reusing `$s0`. It scored *better* on the raw
  mismatch counter purely because it shuffled the allocation — a metric trap. The
  anchored aligner and the slot census disagreed, and they were right.
* **"the box-3 ATTEN is uniform across the 7 copies."** Refuted by enumerating all 24
  `sll $v0,$s0,16` sites: three copies differ.
* **"declaration order can replace the `mny` ref dial."** Six anchor positions swept, all
  neutral. Declaration order moves the *tiebreak*; the dial moves `reg_n_refs`
  (× loop depth) and therefore the `allocno_compare` **score**. They are not
  interchangeable.

---

## 6. THE REMAINING 45 INSTRUCTIONS

Three independent register-grant ties. No structural residual.

**(a) The prim-word producer temps (≈8 ins, idx 508–514, 539–542).**
Target: `andi $v1,$a1,0xFFFF` / `srl $a0,$a1,16` / `addu $t2,$t6,$v1`.
Draft: the `andi` result is written straight into `$t2` (`va`'s register) and the `addu`
is in-place. This is `combine_regs` (`local-alloc.c:1825`) tying the producer chain into
`va` — which the **`va→$t2` pin invites**, because a pinned pseudo is a hard register from
the start and local-alloc will always tie into it. Removing the pin unties the chain but
costs 4 % elsewhere. *Most promising next move: keep the tie broken by giving the two
offsets their own named, multi-death variables (raising their death count above 1 so
`local-alloc.c:472` refuses them), rather than by removing the pin.*

**(b) `c0` and `c2` grants (≈15 ins).** Target `c0→$t4, c1→$a0, c2→$t2, c3→$a2`; draft
gets `c1` (pinned) right and `c0→$t2, c2→$a2`. Pinning them directly is refuted (§5.2).
The lever is `allocno_compare` order among the four, i.e. their relative ref counts —
reachable by a variable-REUSE merge (§45-A / RC-14), which was **not** swept for `c0..c3`
and is the obvious next experiment.

**(c) The quad-lit rgb accumulator (≈20 ins, idx 4635–4653).** Target accumulates in
`$v1` and stores from `$v1`; the draft accumulates in `$v0`. Three one-slot
store/shift transpositions ride along with it (`sll $v0,$a0,8` before vs after
`sw $v1,-0x20($t3)`). **Before calling these a scheduling residual, run §76's attribution
primitive** (`-fno-schedule-insns` and `-fno-schedule-insns2`): if the pair keeps source
order under both, it was fixed at RTL expansion and the lever is statement order, not
`sched.c`. That test was *not* run here and is the cheapest remaining probe.

### Single most promising next move
**Sweep variable REUSE across `c0..c3` and the `a0v..a3v` accumulators** (merge two temps
into one, §45-A / RC-14 MERGE) to move `allocno_compare` priority. That is the one §76
lever class this session never reached — declaration scope was swept exhaustively,
reuse was not. It targets residual (b) directly and plausibly (c) as well.

---

## 7. TOOLS BUILT (all preserved in `.run/giants/`, ~0.3–0.8 s per probe)

| tool | what it does |
|---|---|
| `bf14_cc.sh` / `bf14_score.sh` / `bf14_probe.sh` | compile + score one draft (0.28 s) |
| `bf14_mk.py` | lever generator; **every transformation asserts it applied**, so a "neutral" reading can never be a silent no-op |
| `bf14_sweep.sh` | 8-way parallel lever sweep |
| `bf14_full.py` / `bf14_side.py` / `bf14_win.py` | masked diff, side-by-side, windowed side-by-side |
| `bf14_hist.py` | opcode-histogram delta — **alignment-free, length-drift-proof** |
| `bf14_shape.py` | difflib shape diff with sp offsets masked |
| **`bf14_ali.py`** | **anchor-segmented aligner** — segments the function at the 56 `mult` sites and aligns each segment independently. Plain difflib gets hopelessly lost in this function's repeated blocks (it once reported a bogus 1,836-instruction insertion); anchoring fixes it. Reports both register-masked and byte-level alignment. |
| `bf14_segh.py` | per-segment length + opcode delta — localises a drift to one ATTEN axis |
| `bf14_land.py` | landmark drift table (`mult` index deltas) |
| **`bf14_slots.py`** | **stack-slot census vs the target — the declaration-order oracle of §4.2** |
| `bf14_regmap.py` | register-correspondence census; exposes allocation *cycles* rather than a list of diffs |
| `bf14_struct.py` | label / branch / loop map of the target |

### Reusable methodology notes
1. **Anchor your aligner.** On a function with 7 near-identical 400-instruction blocks,
   raw `difflib` is worse than useless — it reports confident nonsense. Segment on a rare
   opcode first.
2. **The opcode histogram is the honest early metric.** Index-wise "mismatched" is
   dominated by length drift and will rank a *worse* draft higher (this happened, §5.3).
3. **The stack-slot census is a free oracle for declaration order** (§4.2).
4. **The register-correspondence census turns a wall of diffs into cycles.** Seeing
   `$t2→$t3→$t5→$t4→$t2` as a rotation, and `$s3↔$s4` as a swap, is what made the last
   5 % tractable.

---

## 8. FILES

* `.run/giants/s19_func_8017BF14_b1.c` — best draft, full dossier header. **45/4763.**
* `.run/giants/s19_func_8017BF14_b1_pinfree.c` — pin-free variant. 789/4763, 100 % structural.
* `.run/giants/bf14_*.py`, `.run/giants/bf14_*.sh` — the harness.
