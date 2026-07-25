# func_8017F510 (behemoth #3, 1,511 ins, `ov_SC03_006`) — session 19 report

## Verdict

**CRACKED. `match_one` = MATCH (1511 ins). PIN-FREE.**

```
python3 tools/match_one.py func_8017F510 \
  --c .run/giants/s19_func_8017F510_b4.c \
  --asm-subdir asm/ov_SC03_006/nonmatchings/ov_SC03_006_jr_8017AE2C
-> MATCH (1511 ins)  func_8017F510
python3 tools/symcheck.py func_8017F510 --c .run/giants/s19_func_8017F510_b4.c \
  --asm-subdir asm/ov_SC03_006/nonmatchings/ov_SC03_006_jr_8017AE2C
-> SYMS-OK  func_8017F510   12 symbols agree
```

Start of session: 97 mismatched (`ADDRESSING/srl!=addu`, profile=cse), reproduced exactly.
Class of the residual at each stage: 97 → 10 (`OPCODE-MIXED`) → 2 → **0**.

`match_one` is the CANDIDATE gate (it masks jal/HI16/LO16 and compiles standalone).
The whole-binary SHA1 rebuild (G3/P9) is still the arbiter and has **not** been run
(the task forbade touching the build tree). Independent re-verification was done with a
private pipeline (`.run/giants/s19_cc.sh` + `s19_full.py`): `mine=1511 target=1511 0 mismatched`.

Deliverable draft: `/home/musashi/bfm-decomp/.run/giants/s19_func_8017F510_b4.c`
(full 130-line dossier header, same style as b3).

---

## A / B / C — per the brief

| Residual | Status | Byte-evidence |
|---|---|---|
| **A** — 2 ins @ tgt[118..120], `addu $a2,$v1` / `srl $a3,$v1,16` transposed | **CRACKED** | `-fno-schedule-insns` AND `-fno-schedule-insns2` both leave the pair in source order ⇒ it is RTL **expansion** order, not scheduling. Source must be `mny = wy;` then `my = wy >> 16;`. That alone = 36 mismatched (registers flip). Adding one zero-byte `__asm__ __volatile__("" :: "r"(mny))` at the head of the tri cull block = **MATCH**. |
| **B** — 3 ins ×2 @ tgt[864..870] and tgt[1454], OT tag vs 0xFFFFFF order | **CRACKED, and the brief's diagnosis was wrong** | It is not a sched.c ordering choice. It fell out for free with lever L2 (`cb` reused as the unlit rgbc temp). With the unlit rgbc granted `$a1`, the two-insn `0xFFFFFF` constant (also `$a1`) cannot be materialised until rgbc dies, so sched2 slides it below the single-`lui` OT tag — the target's order. **A register grant, observed as a schedule diff.** |
| **C** — ~93 ins, "c3 must get `$a2`" | **CRACKED, but the brief's seed model was incomplete** | It was not one seed. It was two independent allocator decisions plus one qty-tie: (i) `otp`'s allocno CLASS (local vs global) which decided `$a0`/`$a2` **and** where the 0xFFFFFF constant landed; (ii) `cb`'s density, which decided the cb/c3/tp 3-colouring; (iii) the lit rgb OR-chain qty tie. c3 does not have its own lever — it moves when `cb` out-ranks `tp`. |

---

## The five decisions (mechanism + citation), in the order they were cracked

### L1 — `otp` declared **per emit arm** (all four), not at function scope
* 97 → (see L2); alone it is 1515 ins / 99.2 % structural.
* `local-alloc.c:472` gate is `REG_BASIC_BLOCK >= 0 && REG_N_DEATHS == 1`. A function-scope
  `otp` has 4 deaths ⇒ **global** allocno ⇒ `combine_regs` (`local-alloc.c:1825`) cannot tie
  the `(g.opz>>2)<<2` shift chain into it (K8, global-alloc has no coalescing) ⇒ the target's
  in-place `sra $a0 / sll $a0 / addu $a0,$a0,$s4` is unreachable.
* **The bigger effect** is second-order and is the reusable finding:
  `global.c:668-671` re-marks every pseudo that local-alloc already placed
  (`reg_renumber[i] >= 0`) as a **hard register** for global-alloc's conflict scan.
  With `otp` global-in-`$a2`, the per-tail 0xFFFFFF constant (a local qty) took `$a0`,
  which then appeared as hard-reg conflict `4` in `;; 142 conflicts: … 2 3 4 5 29`,
  making `otp = $a0` (the target) *structurally impossible*. Freeing `$a2` moved the
  constant to `$a1` and `otp` to `$a0`. **Read the `;; N conflicts:` hard-reg tail of the
  `.greg` dump before reasoning about priorities — it encodes local-alloc's choices.**
* Scoping `otp` only at the innermost-`if` level (shared by the lit and unlit ARMS) is a
  **no-op** — it still has 2 deaths in 2 blocks. The arm granularity is what matters.

### L2 — `cb` reused as the unlit `rgbc` temp  → **97 → 10**
```c
cb = (tp[0] & 0xFF000000) | col;
((PolyFT3 *)pkt)->rgbc = cb;      /* was: pkt->rgbc = (tp[0]&0xFF000000)|col; */
```
* §45-Lever-A / RC-14 MERGE applied to a *colour base*. `cb`'s `reg_n_refs` goes 27 → 39
  (refs are counted `× loop_depth`, here 3), so its `global.c:594 allocno_compare` priority
  crosses `tp`'s and the grant order becomes **cb → `$a1`, c3 → `$a2`, tp → `$a3`**
  instead of tp → `$a2`, cb → `$a1`, c3 → `$a3`.
* Measured priorities in the b3 baseline (from `t.i.lreg` + `floor_log2(n)*n/L*10000`,
  verified to reproduce the `;; N regs to allocate:` order exactly):
  `otp 44444 > tp 37037 > cb 34839 > c3 29605`. Target needs `cb > c3 > tp`.
* Residual **B** disappears with it (see table).

### L3 — one shared `u32 rgbw` temp for the lit rgb word  → **10 → 2**
```c
rgbw = cb | c0 | (c0 << 8) | 0x800000;
((PolyGT3 *)pkt)->rgb0 = rgbw;    /* ×3 in the tri tail, ×4 in the quad tail */
```
* From the `.lreg` local-alloc results (`;; Register N in M.`): the baseline had
  `553,555,556 → $v0` (one qty, chain + result tied by `combine_regs`) and `554 → $v1`;
  the target has `553,555 → $v1`, `554 → $v0`, `556 → $v0` — i.e. the result is a
  **separate** qty and the `sll` temp out-ranks the chain in `qty_compare`
  (`local-alloc.c:1579`, same `floor_log2(refs)*refs/(death-birth)` formula).
* Routing the result through a **multi-set** variable (4 sets / 4 deaths) fails the
  single-death gate, so the tie cannot form and the block's qty priorities re-rank.
* Tell that this was a *priority* problem and not an *expression-shape* problem: only the
  **first** chain of each lit tail was ever wrong — rgb1/rgb2/rgb3 already matched.

### L4 — box-build y pair: `mny` first + one zero-byte density dial  → **2 → MATCH**
```c
wy = part->yy;
mny = wy;
my  = wy >> 16;
...
if (my >= -0x6E && mny < 0x6F) {
    __asm__ __volatile__ ("" :: "r" (mny));   /* zero-byte RC-15 ref dial */
```
* **Attribution (the load-bearing measurement):** the pair keeps source order under
  `-fno-schedule-insns` *and* under `-fno-schedule-insns2` ⇒ **expansion order**, so the
  original really is `mny` first (which also matches the MATCHED sibling `func_8017CA80`).
* But `mny`-first alone = 36 mismatched: the **second**-defined variable has the shorter
  `REG_LIVE_LENGTH` (106 vs 108 — exactly the 2 insns between the defs) hence the higher
  `allocno_compare` priority (`5*46/106 = 21698` vs `5*46/108 = 21296`) and takes the lower
  register `$a2`. The target wants the *first*-defined (`mny`) in `$a2`.
* RC-15's ref axis fixes it: the dummy sits at `loop_depth 3`, so `flow.c` adds
  `reg_n_refs += 3` (46 → 49) for ~+1 live length ⇒ `5*49/109 = 22477 > 21698` ⇒ `mny`
  granted first → `$a2`, `my` → `$a3`. Emits only `#APP/#NO_APP`; the compile is 1511 ins exact.
* **Placement is load-bearing** (RC-11 caveat): the identical dummy inside the box-build
  statement stream costs **+9 instructions** (its `#APP` kills maspsx's delay-slot hop).
  At the head of a cull block it is byte-free. Same dial in *both* cull blocks also MATCHes.
  Swapping the `s16 my, mny, mx, mn;` declaration order also MATCHes ⇒ decl order is **not**
  load-bearing here (the priorities are not tied).

---

## Every lever tried, with its measured result (do-not-re-buy list)

Baseline b3 = 97 mismatched, 1511 ins.

### Declaration-scope sweep
| Lever | Result |
|---|---|
| `za,zb` at innermost-`if` (per case) | 97 (neutral) |
| `otp` at innermost-`if` (per case) | 97 (neutral) |
| `tp` at innermost-`if` (per case) | 111 |
| `cb` at innermost-`if` (per case) | **1509** — the `lui 0x800000` hoists into the tp-load delay slot, −1 nop per lit tail |
| `otp+tp` per case | 111 |
| `za,zb,otp,tp,cb,uvw` per case (the sibling's literal shape) | 1509 |
| **`otp` per ARM (×4)** | **1515 ins, 99.2 % structural** — otp → `$a0`, 0xFFFFFF → `$a1` (both target); +4 nops because `tp` then squats in `$a1` |
| `tp` per ARM | 1513 |
| `otp+tp` per ARM | 1513 |
| `otp` per ARM + `tp` per case | 20 |
| **`otp` per ARM + `cb`-merge** | **10** |
| `otp` per ARM + `cb`-merge + `tp` per case | 10 (neutral) |
| on the 10-base: scoping `za/zb`, `tp`, `cb`, `uvw`, `f0`, `d` (case or arm) | 10 — all neutral |
| on the 10-base: `c0..c3` per case / per arm | 38 |
| on the 10-base: `x0..z3` per case | 1507 |

### Expression / temp shape
| Lever | Result |
|---|---|
| `(c0 << 8) \| cb \| c0 \| 0x800000` | 1532 |
| `cb \| (c0 << 8) \| c0 \| 0x800000` | 1532 |
| `cb \| (c0 \| (c0 << 8)) \| 0x800000` | 1532 |
| `cb \| c0 \| ((c0 << 8) \| 0x800000)` | 1526 |
| `(cb \| c0) \| ((c0 << 8) \| 0x800000)` | 1526 |
| `c0 \| cb \| (c0 << 8) \| 0x800000` | 15 |
| shared `sh8 = c << 8;` temp | 1509 |
| named `w0 = tp[0];` temp | 16 |
| `cb` split into two statements | 14 |
| shared temp for the three packet x-stores | 10 (neutral) |
| **shared `rgbw` temp for the lit rgb word** | **2** |

### Box build (residual A)
| Lever | Result |
|---|---|
| `mny` before `my` (on the 97-base) | 44 |
| `mny` before `my` (on the 10-base) | 36 |
| + `s16 mny, my, mx, mn;` decl swap | 36 (no tie to break) |
| decl swap alone | unchanged |
| `wz = part->zz;` moved between the y pair / before it / all-loads-first | neutral at every base |
| y pair before x pair | 71 / 63 |
| x pair order swapped | 12 / 4 |
| dedicated box-build y variables | 92 |
| dedicated box-build x+y variables | 1510 |
| `__asm__("" :: "r"(mny))` inside the box-build statement stream | **1520** (+9: `#APP` kills the delay-slot hop) |
| `__asm__("" :: "r"(mny))` *before* the cull `if` | 2 (no effect — wrong side of the last use) |
| **`__asm__("" :: "r"(mny))` as first statement inside the tri cull block** | **MATCH** |
| same, inside both cull blocks | MATCH |
| same, either variant + decl swap | MATCH |

### Pins (diagnostic only — NOT shipped)
| Lever | Result |
|---|---|
| `register u32 *tp __asm__("$7")` | 63 |
| `register s32 c3 __asm__("$6")` | 65 |
| `tp→$a3` + `c3→$a2` | 65 |
| `tp→$a3` + `c3→$a2` + `otp→$a0` | **22** — the diagnostic that proved residual C was a 3-value allocation, and isolated the true residual set (A 2 + rgb-chain 10 + unlit-rgbc 4 + OT-tag 6 = 22) |

### decomp-permuter
Re-seeded at the **new** base (score 10) after fixing the harness (`base.c` needed the six
engine typedefs inlined, and the `PolyGT3`/`PolyGT4` typedefs hoisted above the GTE `#define`
block or `hide_asm` swallows them into the b64 pragma). ~5,800 iterations at `-j14`:
**0 improvement** — its randomisers destroy this shape (scores jump to ~1450). Consistent with
the s18 result at base 97 (3,663 candidates, 0 improvement). The permuter is confirmed
**spent** on this function at every profile tried.

---

## The generalisable lesson (proposed cookbook entry)

Four of the five decisions were **local-vs-global allocno CLASS** choices, and C expresses that
class only through **declaration scope** and **variable reuse**:

* narrow a value's scope until it has **1 death in 1 basic block** → `local-alloc` handles it:
  it ties into its producer chain (`combine_regs`) and takes a low scratch;
* widen or merge a variable so it has **several deaths** → **global** allocno: it enters the
  `allocno_compare` density contest and takes an `$aN`/`$sN` by priority.

Neither pole is reachable by statement order, expression shape, register pins, or the permuter —
which is exactly why 3,663 + 5,800 permuter candidates and every s18 hand lever stalled at 97.

Two supporting rules worth banking:

1. **`global.c:668-671`** — pseudos that local-alloc already placed are re-marked as *hard
   registers* for global-alloc. So a global allocno's `;; N conflicts: … 2 3 4 5 29` hard-reg
   tail is a **read-out of local-alloc's decisions**. When a target register looks structurally
   impossible ("otp can never be `$a0`, it conflicts with 4"), the fix is upstream in
   local-alloc, not in the density race.
2. **A reordering next to a reused scratch register is usually an allocation symptom, not a
   scheduling cause** (extends the §H `reg_renumber`-swap oracle finding). Residual B here was
   filed as "pure sched.c ordering" and was in fact 100 % a consequence of which register the
   unlit `rgbc` was granted.

And one attribution primitive that settled residual A in one shot:
**compile the same draft with `-fno-schedule-insns` and with `-fno-schedule-insns2`.** If a
two-instruction transposition survives both, it is RTL *expansion* order — i.e. plain source
statement order — and no scheduling lever will ever move it.

---

## Artifacts preserved (all under `.run/giants/`)

| File | What |
|---|---|
| `s19_func_8017F510_b4.c` | **the MATCHing draft** (dossier header) |
| `s19_f510_report.md` | this report |
| `s19_cc.sh` | one-draft compile through the pinned triple into a private work dir, with `-da` RTL dumps |
| `s19_full.py` | uncapped index-wise masked diff (`match_one` caps at 40) |
| `s19_side.py` | side-by-side mine/target listing over an index range, mismatches starred |
| `s19_mk.py` / `s19_sweep.py` | the lever/scoping variant generators used for the sweeps |
| `s19_probe.sh` | one-line score for a variant (parallel-safe) |

Working variants and dumps live in `.run/s19/` (untracked); the two dumps worth keeping are
`.run/s19/w_base/t.i.{lreg,greg}` (the 97-baseline allocno stats/priorities that the analysis
above is computed from) and `.run/s19/w_m1/t.i.{lreg,sched}` (the 10-baseline rgb-chain RTL).
