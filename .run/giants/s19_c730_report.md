# func_8017C730 (behemoth #6, 1,061 ins, `ov_SC03_010`) — session 21 report

## Verdict

**CRACKED. `match_one` = MATCH (1061 ins).**

```
python3 tools/match_one.py func_8017C730 \
  --c .run/giants/s19_func_8017C730_b1.c \
  --asm-subdir asm/ov_SC03_010/nonmatchings/ov_SC03_010_jr_8017AE2C
-> MATCH (1061 ins)  func_8017C730
```

Independent re-verification with a private pipeline (`.run/giants/c730_cc.sh` +
`b3_align.py` + `c730_reg.py`, same pinned triple, separate work dir):

```
mine 1061 target 1061
b3_align: register-MASKED 1061/1061 = 100.0%   register-KEPT 1061/1061 = 100.0%
c730_reg: pro 80/80  part 55/55  proj 47/47  bbox 165/165  prim 56/56
          A:F3 127/127  B:FT3 131/131  C:F4 180/180  D:FT4 187/187  tail 33/33
frame 0x270 exact; every sp offset agrees with the target
undefined symbols: exactly the target's 11 externals, no more, no fewer
```

**The compiler-emitted `.rodata` jump table is byte-correct as well** — offsets
`0xA54 0xA54 0xD24 0xD24 0x64C 0x64C 0x848 0x848` relative to the function base,
identical to the target's `jtbl_8019EBA4` in
`asm/ov_SC03_010/data/tail21.data.s`:

| index | my `.rodata` offset | target `jtbl_8019EBA4` | arm |
|---|---|---|---|
| 0,1 | 0xA54 | 0x8017D184 − 0x8017C730 = 0xA54 | C (POLY_F4) |
| 2,3 | 0xD24 | 0x8017D454 − base = 0xD24 | D (POLY_FT4) |
| 4,5 | 0x64C | 0x8017CD7C − base = 0x64C | A (POLY_F3) |
| 6,7 | 0x848 | 0x8017CF78 − base = 0x848 | B (POLY_FT3) |

`match_one` is the **candidate** gate. The whole-binary SHA1 rebuild (G3/P9) is
the arbiter and has **not** been run — the task forbade touching `src/`,
`config/` or the build tree.

### ⚠️ Integration: this is a `jr` function — cookbook §81 applies

`jr $v0` at `.s:439`, jump table `jtbl_8019EBA4`. The 3-step carve chain is
**required** before banking, each step byte-gated on its own:

```
1. tools/jr_isolate_all.py ov_SC03_010 --only func_8017C730
   make extract BINARY=ov_SC03_010 && make build BINARY=ov_SC03_010  -> BYTE-IDENTICAL
2. tools/jtbl_carve.py     ov_SC03_010 --func func_8017C730
   make extract BINARY=ov_SC03_010 && make build BINARY=ov_SC03_010  -> BYTE-IDENTICAL
3. tools/harvest_verify.py --binary ov_SC03_010 --drafts <dir> --chunk 1
   then a FULL R22 (config changed => T2)
```

Second integration item: the draft carries a **`static inline` helper**
(`bandsetup`) at file scope. It is load-bearing (see L1) and must survive the
TU splice intact — `dedup_propagate` / `family_remap` drop non-`extern`
preamble constructs (§77), so **diff the preamble after any mechanical step**.

Deliverable draft: `/home/musashi/bfm-decomp/.run/giants/s19_func_8017C730_b1.c`
(~140-line dossier header, c954/b5/b2 style).

Starting point: the matched 952-ins `func_8017CA80` renamed → 240 divergent
target instructions / 77.4 % structural. Progression:
`77.4% → 94.4 → 94.9 → 98.1 → 98.7 → 99.2 → 99.8 → 100.0% = MATCH`.

---

## The delta vs the matched base `func_8017CA80` (952 ins)

Identical skeleton — same 3-call prologue (`func_800491EC` / `func_800547D8` /
`func_80052E38`), same `Part[]` outer loop (stride 0x14) with the 8-corner AABB
`rtpt/rtps` and the screen-bbox reject, same `Prim[]` inner loop (stride 0xC)
with `rtpt`/`stflg`/`nclip`/`stopz`, same 4-arm switch with the **same** case
grouping (verified against the real table), same OT insert, same
`D_800A5E60 = pkt`. **+109 instructions in seven places:**

### 1. Prologue, +36 ins — the `func_8004974C` feature

```c
lim = func_800491EC();                 /* NOT `+ *(s32 *)(arg0 + 0x64)` */
func_800547D8(arg0 + 0x10, &mtx);
func_80052E38(&mtx);
org.vx = 0; org.vy = 0; org.vz = 0;
bandsetup(&org, &hv);                  /* static inline, see L1 */
hmid = hv.vy + 0x100;
hhi  = hv.vy + 0x280;
hv.vy = hv.vy - 0x180;
```
with
```c
static inline void bandsetup(SVECTOR2 *o, SVECTOR2 *out)
{
    MATRIX2 rot; MATRIX2 inv; SVECTOR2 dv;
    ReadRotMatrix(&rot);
    PushMatrix();
    dv.vx = o->vx - rot.t[0];
    dv.vy = o->vy - rot.t[1];
    dv.vz = o->vz - rot.t[2];
    func_8004974C(&rot, &inv);         /* = TransposeMatrix */
    ApplyMatrixSV(&inv, &dv, out);     /* camera pos in WORLD space */
    PopMatrix();
}
```

This is the camera position transformed back into world space, from which a
**height band** is derived: `lo = y−0x180` (kept in `hv.vy`), `mid = y+0x100`,
`hi = y+0x280`. `hmid`/`hhi` are `s16`; `hhi`'s sign-extension is loop-invariant
and `loop.c` hoists it into the preheader spill at 0x148.

**`bandsetup`'s body is the byte-identical twin of the already-MATCHED
standalone `func_8017C294`** (`src/ov_SC02_004/ov_SC02_004_jr_8017AE2C.c:3285`)
— almost certainly the same source helper, compiled un-inlined in that overlay.
Finding that banked twin is what decoded the block; making it `static inline`
here is what made the addresses come out right (L1).

### 2. Part loop, +19 ins — a mid-height cull before the AABB is even built

```c
wz = part->zz;
wv = wz >> 16;
mid = (mny + my) / 2;                  /* s16 */
if (mid < hv.vy) continue;
if (hhi < mid) continue;
```
and the box is filled **per corner** (`vx, vy, vz` for box[0], then box[1], …),
not the base's "all vx/vy first, then all vz".

### 3. The part-level `lim >= g.otz` cull is GONE, −11 ins

There is **no `gte_stszotz` at all** in this variant, so the GTE result block
loses its `otz` word: only `flag, opz, sz0..sz3` exist.

### 4. Tighter screen-Y bounds

`±0x78/0x79` → **`±0x6E/0x6F`** at all 5 sites. The X bounds stay `±0xA0/0xA1`.

### 5. A redundant re-test of the band after the bbox cull, +10 ins

```c
t32 = mid;
if (!(hhi < t32)) mnc = hmid;
```
`hhi < mid` was already tested at the top of the part loop, so this branch is
never taken; `mnc` is dead afterwards and `hmid` has no other reader. Vestigial
source — see L4/L5.

### 6. A near-plane cull in the FLAT arms only

```c
A:F3  if (gsz0 < lim && gsz1 < lim && gsz2 < lim) break;                 /* +15 */
C:F4  if (gsz0 < lim && gsz1 < lim && gsz2 < lim && gsz3 < lim) break;   /* +20 */
```
The textured arms B/FT3 and D/FT4 do **not** have it. Arm C also gains the
`if (code != 0) gopz = za + 0x200;` half-step the base lacks (the base's arm C
has no conditional at all).

### 7. A distance-driven CLUT in the TEXTURED arms, +10 ins each

```c
uvw = tp[1] & 0x3FC0FFFF;              /* clear the CLUT-x field       */
cd  = gopz - 0x174;
if (cd < 0) cd = gopz - 0xF5;
pkt->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);
```
plus a stray **`gte_avsz3()` in arm B only** (`nop;nop;avsz3`; its OTZ result is
never read — it is in the target, so it ships). Arm B's half-step test is
spelled `if (code != 6)` (a `beq`), **not** the base's `if (code == 7)` (`bne`).

### Frame (0x270) — matches exactly

```
0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 mtx |
0xC0 org | 0xC8 hv | 0xD0 rot | 0xF0 inv | 0x110 dv |
0x118 gflag | 0x11C gopz | 0x120 gsz0 | 0x124 gsz1 | 0x128 gsz2 | 0x12C gsz3 |
0x130 hmid (HImode spill) | 0x138 nprim | 0x140 nparts |
0x148 loop.c's hoisted (s16)hhi | 0x240 part loop pseudo |
0x248..0x26C saved regs (s0-s7, fp, ra)
```
`rot`/`inv`/`dv` are the **inlined helper's** locals — stack *temps*, which is
why they sit after `hv` and before the GTE result words. The six GTE words are
**scalars**, stack-allocated lazily at first `&` (L2), which is why they land
*after* the helper's temps.

---

## Every lever, with its MEASURED drop-one ablation

Each row is `.run/giants/c730_abl.py`'s `match_one` result for the draft with
that single lever removed (base = the MATCHing draft).

| # | Lever | Ablation result |
|---|---|---|
| **L1** | `bandsetup()` is a **`static inline` helper**, not straight-line code | **1063 ins, 973 mismatched** |
| **L2** | the six GTE result words are six separate `long` **scalars**, not a struct | **61 mismatched** (every g offset wrong) |
| **L3** | arms A and C store rgbc as `*(u32 *)(pkt + 4)`, not `((PolyF3 *)pkt)->rgbc` | **1060 ins, 255 mismatched** (arm-C-only ablation) |
| **L4** | `t32 = mid;` launder before the redundant re-test | **2 mismatched** (`sra $v0` vs `sra $v1`) |
| **L5** | one zero-byte `__asm__ volatile ("" : : "r" (mnc))` | **1051 ins, 951 mismatched** |
| **L6** | `wv = wz >> 16;` computed **before** the band `continue`s, dedicated var | **51 mismatched** |
| **L7** | arm B's `otp = …` hoisted above the uv stores | **still MATCH** on this base (§80(i)) |
| **L8** | arm D uses a **separate** temp (`uvm`) for the CLUT mask | **11 mismatched** |
| **L9** | arm B masks `tp[1]` into `uvw` as a separate statement before the `cd` if | **17 mismatched** |
| **L10** | **zero** §47 `__asm__ volatile ("")` sliders | adding one → **15 mismatched** |
| **L11** | `gte_avsz3()` in arm B | **1058 ins, 457 mismatched** |
| **L12** | `u32 nprim;` declared before `s32 nparts;` (§79) | **4 mismatched** |

### L1 — the dominant lever, and the reusable finding

> **`&X` for a local at virtual-stack-vars offset ≠ 0 ALWAYS produces a pseudo,
> and cse ALWAYS merges two identical ones inside a basic block. If the target
> re-materialises the same `addiu $aN,$sp,K` at two call sites separated by a
> `jal`, the block is an INLINED FUNCTION.**

Mechanism, with citations:

* `expand_expr`'s `ADDR_EXPR` case (`expr.c:6260`) ends with
  `op0 = force_operand (XEXP (op0, 0), target)`. `expand_call` passes
  `target == NULL`, and `force_operand` on `(plus virtual-stack-vars K)` routes
  through `expand_binop (…, target = 0, …)` → **a fresh pseudo**. The single
  exception is `K == 0` — the address is then the bare `virtual_stack_vars_rtx`
  REG and `force_operand` returns it untouched.
* A **10-case bisect** (`.run/c730/f4.c … f10.c`, plus `c294.c`) proved exactly
  that: move the object so it is the FIRST declared local and gcc emits
  `addiu $a0,$sp,K` at each site; move anything ahead of it and gcc emits
  `addiu $s0,$sp,K` + `move` + `move`.
* cse then merges the two pseudos: nothing in `cse.c` invalidates an expression
  built on a **callee-saved** base register at a `CALL_INSN`
  (`invalidate_for_call` only touches call-clobbered hard regs), and
  `cse_end_of_basic_block` does not break at a call. `update_equiv_regs`
  (`local-alloc.c`) will not rematerialise it either — it requires
  `reg_n_refs == 2` (one set, one use) and `reg_basic_block < 0`.
* Inside an **inlined** function the helper's first local *is* at
  virtual-stack-vars offset 0, so its RTL contains `(set (reg a0) vsv)` once per
  call site; `integrate.c` substitutes `(plus fp K)` into **each** of them
  independently. Result: `addiu $a0,$sp,0xD0` twice — the target.

**Seventeen non-inline spellings were measured and all failed** (see the
do-not-re-buy table). The inline hypothesis was found by *scanning 1,200 already
built objects* for "the same `addiu $aN,$sp,K` materialised twice across a
`jal`, in a function that is not `INCLUDE_ASM`" — which is a cheap, mechanical,
reusable probe.

### L2 — a scalar's stack slot is allocated LAZILY; an aggregate's is not

`expand_decl` (`stmt.c:3412`) hands an aggregate a stack slot **immediately**
(`assign_stack_temp`), at its declaration position. A scalar gets a *pseudo*;
its stack slot is only created when `mark_addressable` → `put_var_into_stack`
fires at the first `&` — which for these six is **inside the loop**, i.e. after
the inlined helper's temps have been allocated. That is what puts them at
0x118..0x12F, in first-`&` order (`flag, opz, sz0, sz1, sz2, sz3`), and what
makes the spill area start at 0x130 and the frame come out 0x270.

With a struct, the block-scope variant reuses the helper's *freed* temp slot at
0xD0 (`assign_stack_temp` best-fit + `combine_temp_slots`), and the
function-scope variant lands at 0xD0 ahead of the helper. Both are wrong.

> **Rule: when the target's frame shows a group of scalars sitting AFTER an
> inlined callee's locals, they are separate scalars, not a struct — the frame
> map tells you the storage class, not just the declaration order (§79 extended).**

### L3 — `MEM_IN_STRUCT_P` is a scheduling lever

gcc-2.7.2's `true_dependence` treats a **varying-address in-struct** ref and a
**fixed-address scalar** ref as non-aliasing. Once L2 makes `gopz` a
fixed-address *scalar*, the `((PolyF3 *)pkt)->rgbc` store (in-struct, varying)
no longer conflicts with it and the scheduler hoists `lw $a0,0x11C($sp)` into
the `lw $v0,0($t6)` load-delay slot — deleting the `nop` the target has there
(§78: *a nop the target has and you lack is a liveness/aliasing fact*).
Spelling that one store as a scalar deref `*(u32 *)(pkt + 4)` restores the
conflict. Arms B and D do not need it — their delay slot is filled by `tp[1]`.

### L4 — the last two instructions

Residual after everything else was `sra $v0,$v0,16` where the target has
`sra $v1,$v0,16`: local-alloc's `combine_regs` had tied the `sll → sra`
producer chain into `$v0`. Laundering `mid` through the **already-busy** `t32`
gives the sign-extension its own allocno and the tie does not form. A *fresh*
local (`s32 _m2 = mid;`) measured **2** — i.e. no better than doing nothing.
**§78 reproduced: reuse an already-busy variable, never a fresh temp.**

---

## Do-not-re-buy list (byte-measured; each entry is scoped to its base — §80(i))

### The prologue `&rot`/`&inv` CSE (base: 1063 ins, 99.8 % structural)

Every one of these left the merge in place (1063 ins, `pro` 78/80 masked):

| Lever | Result |
|---|---|
| `s32 rot[8]` + `(void *)` casts + `*(s32 *)((u8 *)rot + 0x14)` (the banked `func_8017C294` spelling) | 1063, neutral |
| no `(void *)` casts / `&rot[0]` element form / `MATRIX2 *` pointer variable | 1063, neutral |
| `func_8004974C` moved before the `dv` computation | 1063, worse (99.5 %) |
| `org` zeroed after `ReadRotMatrix` | 1065, worse |
| `__asm__ volatile ("")` or `("" ::: "memory")` before the 2nd/3rd call | 1063, worse (99.5 / 99.7 %) |
| block-scope `register void * __asm__("$4")` pins on the arg registers (1, 2 and 3 of them) | 1063, exactly neutral |
| function-scope `register` pins, `void *` and `MATRIX2 *` flavours | 1063, exactly neutral |
| `goto _l1; _l1:` between the two uses (a basic-block boundary) | 1063 — `jump.c` deletes the label |
| merging `org`+`hv` into one `s16 ohv[8]` | 1063, neutral |
| declaring the five prologue objects in a nested block | 1063, neutral |

**The whole class was a dead end; the answer was `static inline` (L1).**

### The vestigial `mnc = hmid` block

| Lever | Result |
|---|---|
| plain `if (!(hhi < mid)) mnc = hmid;` (no dial) | DCE'd — loses 10 ins **and** the 0x130 spill slot **and** the 0x270 frame |
| `mnc = (hhi < mid) ? mnc : hmid;` | DCE'd |
| assigning to `mxc`, `t32`, `xmn1` instead of `mnc` | DCE'd |
| `"r" (hmid)` instead of `"r" (mnc)` in the dial | 1058, −3 ins |
| `"r" (mid)` only | 1055, −6 ins |
| dial *before* the `if` | 1062, +1 ins |
| `"=r"(mnc) : "0"(mnc)` launder form | 2 mismatched (same as the plain dial) |
| `if (hhi >= mid)` / `if (mid <= hhi)` / `if (!(mid > hhi))` | all exactly 2 |
| `register s32 _m2 __asm__("$3")` pin on `mid` | 4 mismatched (**worse** — §72: a pin is a preference) |
| `s32 _m2 = mid;` (fresh temp) | 2 — no better than nothing |
| **`t32 = mid;` (reuse an existing busy variable)** | **MATCH** |
| `xa32 = mid;` (another existing variable) | **MATCH** |

### Part-loop head (base: 1062 ins, `part` 49/55 masked, 36/55 kept)

| Lever | Result |
|---|---|
| all 4 orderings of `wx/wy/wz` reads at the top of the loop | 1062, 48–49/55 — all neutral-to-worse |
| `wz = part->zz` moved after `mid` | neutral |
| `wy = wz >> 16` left where the base has it (after the box stores) | neutral |
| **dedicated `wv`, computed before the culls** | **55/55 masked AND 55/55 kept** |
| dedicated `wv` computed after the culls | 1063, 48/55 |

### Arms B and D

| Lever | Result |
|---|---|
| `otp` hoisted in arm B only / arm D only | 1062 each (both needed at that base) |
| `cd` computed before the mask instead of after | 1062–1063, neutral to −1 |
| block-scope `cd` | pattern conflict, not measured |
| sharing one `uvw` in arm D | 11 mismatched |

---

## The one honest caveat

Lever **L5** is a hand-placed zero-byte `__asm__ volatile ("" : : "r" (mnc))`.
It emits `#APP` / `<empty>` / `#NO_APP`, i.e. **no instruction**, and the compile
is 1061 EXACT with it, so the delivered object *is* the target. But it stands in
for whatever the original source did to keep `mnc` live past
`if (!(hhi < mid)) mnc = hmid;` — twelve natural spellings were measured and all
were dead-code-eliminated (table above). The most likely reality is that the
1998 source had a *reader* for `mnc` further down that this variant no longer
has (the block is already provably vestigial: the `hhi < mid` test it guards was
decided ten instructions earlier and can never be true). **The single most
promising next move**, if anyone wants to retire the dial, is to look for that
reader in a *sibling* of this variant — grep the family's other `jr_8017AE2C`
overlays for a `func_8017C7xx` whose bbox cull consumes a value derived from
`hmid` (the `+0x100` band midpoint), and port its shape back.

---

## Artifacts preserved (all under `.run/giants/`)

| File | What |
|---|---|
| `s19_func_8017C730_b1.c` | **the MATCHing draft** (dossier header) |
| `s19_c730_report.md` | this report |
| `c730_cc.sh` | one-draft compile through the pinned triple into a private work dir, `-da` RTL dumps |
| `c730_probe.sh` | one-line `match_one` score for a variant (parallel-safe) |
| `c730_score.sh` | length-drift-proof score (b3_align masked % + kept %) |
| `c730_probe2.sh` | score plus a register-grant census |
| `c730_reg.py` | **per-region** aligned-identical report (pro / part / proj / bbox / prim / 4 arms / tail) — the tool that made this crack tractable |
| `c730_side.py` | side-by-side mine/target listing over an index range |
| `c730_mk.py` | asserting variant generator (~45 named levers; every pattern must apply) |
| `c730_sweep.sh` / `c730_sw.sh` / `c730_sw2.sh` | 8-way parallel sweeps (match_one / b3_align / per-region) |
| `c730_abl.py` | **drop-one ablation matrix** against the matching draft |

Working variants and RTL dumps live in `.run/c730/` (untracked). The pair worth
keeping is `.run/c730/f6.c` vs `.run/c730/f7.c` — identical code, one
declaration reordered — which is the whole L1 finding in two files: `f6` (object
is the first local) emits `addiu $a0,$sp,K` twice, `f7` (one declaration ahead of
it) emits `addiu $s0,$sp,K` + two `move`s.
