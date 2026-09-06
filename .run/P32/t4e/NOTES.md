# T4c hand pass (S85, 2026-09-06, session 3a7e207c, Max, Fable 5.1, no agents) — the last two main rows

Drew's directive after the T4b close: "do that now, lets crack these before closing the phase." Both rows were
"final verdicts" (PROVED at 1 / PLATEAU at 4). Both fell. Step 0 (the §501-N/P shape grep) found the cousins but the
cracks came from two compiler mechanisms the earlier censuses had missed.

## A. `main:func_80032A74` (422 ins, 800_b_2) — PROVED wall → BANKED `commit:4007`
* The S84 "PROVED" verdict enumerated every stack-slot producer and refuted each; it missed one: **combine's
  reference bookkeeping skips the decrement when the deleted insn's dest also appears in its source**
  (`i2dest_in_i2src`, combine.c:2306). A local `x = <load>; x -= 0x100; ... (u8)x ...` compiles to the plain `lbu`
  the direct spelling gives (the self-update folds into the (u8) use, then the load merges into the use), yet `x`
  keeps stale `reg_n_refs` with no insns, regclass never sees it (`ST_REGS or none`), and reload's initial
  `alter_reg` loop (reload1.c:658) mints an 8-byte slot in regno order — after the a0/a1/a2 parameter spills = 0x48.
* Reproducers (`ghost/`, `tools/cc1_dumps.sh`): g1–g5 (copy+const chains: no — cse folds them before flow),
  h1–h7 (no-op self-mask into a load-absorbing use: no — the def merges first), **k4/k5/k7/k14/k16/k17: YES**
  (`vars= 8`, `GHOST … -> SLOT`; the self-update must be one the def cannot absorb and the use must be a
  word-width `(u8)`/`& 0xFF` conversion), k8/k11–k13/k15/k18: no (byte-STORE hosts fold nothing).
* The bank = the S84 `u16` TU-clean draft (422/422 code) + `gx = dd->unk07; gx -= 0x100; flag = (u32)sub <
  (u32)(u8)gx;` in the `dd->unk06` arm. rtu MATCH first probe (a1). gate_main: "BANKED 1 … 143dbb89 BYTE-IDENTICAL".

## B. `main:func_80039308` (518 ins, 800_c) — PLATEAU 4 → BANKED (this session), ZERO pins
Route, in order (every step measured in the real TU, `rtu_*.log`):
| step | change | result |
|---|---|---|
| base | S84 best (Fable draft: 5 pins, `u16 sav[8]`) | DIFF 4 (49/50, 412/415) |
| b1 | Y4 (direct `*(s16 *)(p + 6) = arg1`) − dead `sav` + the ghost chain on `s0[1]` | DIFF 6: frame FIXED (412/415 gone), else head lost (440–452) |
| b2–b9 | k2 copies/masks/decl order | no change — the else head is not a k2 priority effect |
| b10/b11/b12 | **reuse s18 as the else compare temp and s17 as the else pointer** (the target's $t0/$t1 = arm 1's s18/s17) | b11 **DIFF 2** (49/50 only) |
| b13–b25 | vbase unpinned / body placements / dead mentions / `+=` arms | never hoisted: a USER VAR after the inner loop is never a movable (loop.c:695-700: user var + maybe_never + multi-block uses), and cse1 folds the arms onto `vol` (cse.c make_regs_eqv: the later-mentioned reg wins) |
| b24/b26/b29 | block-top temp (copy-first, `+=` arms) | hoisted ✓, order [li 2][sll] ✓ — but refs 3 → priority 100 → $fp, 37 rows |
| b34 | **three inline `(b2 * 0x100)` + copy-last through a block-local** | hoisted as ONE movable (combine_movables, savings 3) → refs 7 → **$s2 ✓**; but copy-last → vol dies at the tests → $a0 (240 rows, one cause) |
| b35–b42 | pins/sliders for vol=$a1 | perturb (tie / pan→$a1 / order) |
| b45/b46 | shift born before the s17 join | unmatched extra sll |
| s1–s8 (reproducer) | copy-first spellings | **only `u16 vol` keeps the arms on the hoisted reg**: the copy is a subreg move, not a plain copy → `vol` never joins the quantity |
| b52 | **`u16 vol`, no vbase variable, copy-first `vol = b2 * 0x100`, arms `(b2 * 0x100) ± X`** | **MATCH 518/518** |
| b54/b55/b56 | drop the `two $2`, `mp/mv2 $4` pins | all MATCH → **b56 = zero pins, banked** |
| b53 | `vv = (u16)(vol - tmp2)` merged | DIFF 2 (the subu/andi register split) — the two-statement form is the original's |

Laws (cookbook §501-Q/R): a hoisted invariant read N times in the body needs a TEMP with N uses — inline the
expression N times and let combine_movables merge (a named variable set after a jump never hoists; a named
variable is also what cse folds the arms onto); a `u16` accumulator turns the copy-first assignment into a subreg
move that cse cannot canonicalize, which is how the arms keep the hoisted register while `vol` is born before the
tests ($a1, the first branch's delay slot); the else head's registers were the note-on arm's variables reused.

## Files
`a1_ghost_unk07.c` (32A74 bank body), `b1…b56*.c` + `rtu_*.log`, `bank/func_80032A74.c`, `bank/func_80039308.c`,
`slate_*.json`, `gate_main_*.log`, `ghost/{g,h,k,r,s}*.c` (reproducers), `dump_tu.sh` (real-TU cc1 dumps from an rtu
work dir), `alloc_table.py` (global allocation order/priorities from the dumps), `dumps_*/` (ignored, regenerable).
