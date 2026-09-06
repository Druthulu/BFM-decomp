# func_80185810 (ov_SC03_105, 489 ins) — T4b hand pass row (d), S85 (2026-09-06, session 3a7e207c, Max, Fable 5.1, no agents)

**Outcome: BANKED byte-identical `commit:4004`** (bank.sh: rtu MATCH 489/489 in the real TU → splice → `make build
BINARY=ov_SC03_105 -j8` rc 0 → sha `d305ff6da199b52d0d44023766643a8b661ed524` == `config/check.ov_SC03_105.sha`).
ov_SC03_105 is now 100% C. Zero pins, zero fences, zero asm dials — the cousin's natural spelling.

## Step 0 — the §501-N sibling search (the whole crack)
- Twin oracle: `twins 0`, atlas knn: no entry for the function itself; the only reverse hit is `ov_SC02_027:80180b3c` at
  0.5501 (a "weak" cousin by the atlas's measure).
- Symbol grep (`D_801BC9B4` + `D_800A5E60`): only this overlay's own TUs (the matrix symbol is overlay-local bss).
- Shape grep (`0x200) << 2` = the getTPage bit chain): 20+ files; **`src/ov_SC02_027/ov_SC02_027_jr_8017D898.c:4810
  func_80180B3C` is the same billboard-sprite drawer** (POLY_FT4 off the D_800A5E60 bump, `code = 0x2C; code |= 2`,
  `tpage = getTPage-chain`, `code |= (w & 0x40) >> 6`, u/v from the sprite record, the v0 conditional, the P_TAG link).
- Its compiled window (`objdump -d build/src/ov_SC02_027/ov_SC02_027_jr_8017D898.o`, 0x34f8–0x3560) is
  INSTRUCTION-FOR-INSTRUCTION this target's rows 362–386 (only the base registers differ: t0/t1/t2 vs s0/s2/s1).
- Time from the first grep to the MATCH: ~25 minutes, one draft.

## The port (d1) and the pin/element census (all real-TU `rtu_match`, `--split ov_SC03_105_jr_80181C84 --source ov_SC03_105`)
| variant | change vs d1 | result |
|---|---|---|
| base (Fable v7) | — | DIFF 13 (rows 363–380), reproduced first |
| d1_sibport | cousin window ported; pins uu $4, cl $7, c40 $2 (cousin's) + mode $5, ot16 $6 (draft's) | **MATCH** |
| d2_nomode | − mode pin | MATCH |
| d3_noot16 | − ot16 pin | DIFF 4 (rows 343–346: the ot16 load sinks below the u/v loads) |
| d4 | − mode − ot16 | DIFF 4 (same rows) |
| d5_nocl | − cl pin | MATCH — the `$7` pin is NOT what keeps the andi alive |
| d6_min3 | − mode − cl | MATCH |
| d7 | d6 − c40 pin | MATCH |
| d8 | d6 − uu pin | MATCH |
| **d9_nopins** | **no pins at all** | **MATCH — banked** |
| d10 | ot16 pin only | MATCH |
| d11_f2polarity | d9 with `if (c) vv = vm - 0x100; else vv = vm;` | DIFF 42 (the packet block re-rolls from row 331) |
| d12_twoset_uu | d9 with `uu -= …; uu <<= shift;` instead of a fresh `u` | DIFF 63 (allocations move from row 218: t1↔t0, t2↔t1) |

Reading of the census: with the cousin's spelling every load in the window is a single-set birth (ot16, uu, cl, vm, u,
shift) so sched1's birthing boost ties them all and the LUID tie-break gives source order (the ot16 pin was only needed
while uu/cl were 2-set and unboosted). d3 shows the pin is load-bearing ONLY in the mixed form. The `andi $a3,$a3,0xFFFF`
survives as a lone insn (`vm = cl & 0xFFFF`, single set, consumers in the two arms — a lone insn is never simplified by
combine, and the lhu that sets `cl` has intermediate uses); the S83 report's "combine folds a fresh clx via nonzero_bits"
(F2 → 59) was the OTHER polarity + the 2-set `uu`, which d11/d12 reproduce as 42/63 — the andi was never the problem once
the block's births are all single-set. The branch polarity `if (!(tpage & 0x10)) vv = vm; else vv = vm - 0x100;` is
load-bearing (42 rows): the copy arm is the fall-through that coalesces away, leaving the target's
`beqz → skip; addiu $a3,-0x100` shape.

## Files
- `d1_sibport.c` … `d12_twoset_uu.c`, `rtu_*.log` (one per variant), `rtu/<variant>/` work dirs (ignored),
  `bank/func_80185810.c` (= d9 + the accurate header; the banked body), `check_all_preflight.log` (218/218 before the bank),
  `r22_{clean,extract,check}.log` (the fleet R22 after the bank).
