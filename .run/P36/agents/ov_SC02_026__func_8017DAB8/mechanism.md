# func_8017DAB8 (ov_SC02_026_jr_8017C180.c) — d37, P36 T7 S104

**Result: score 0, ZERO levers** (before: 2 NEEDED pins, `$16` on `s0` and `$2` on `flag`; after: none).
The same text closes all three other copies at 0 (the table is at the end).

## (a) The residual
Lever-free (`body_free.c`, 42, COUNT 98 vs 97): two faults at once.
1. `flag` (always 1 on every path to its one use) is a pseudo that lives across `func_8001C214`, so global allocation
   gives it `$s2` (an extra save/restore pair; the in-arm `flag = 1` is deleted by cse as already-known, so the
   target's `li v0,1` after the call is missing): +2 −1 = +1 instruction.
2. The `$s0`/`$s1` swap: the target keeps `a0` in `$s1` and the `+0xDC` pointer in `$s0`; mine does the opposite.

## (b) The pass and the decision (proven on the `.greg`/`.lreg` dumps, `scratch/dumps_*`)
Global allocation order, `allocno_compare` (`tools/reference/gcc-2.7.2/global.c:595-603`):
priority = `floor_log2(refs) * refs / live_length * 10000`, higher first, and the first allocno gets `$16`.

| body | pointer pseudo(s) | a0 pseudo | who gets `$16` |
|---|---|---|---|
| `body_free.c` + constant store only (`scratch/B.c`) | two per-arm pseudos, 4 refs / live 8 → **10000** each | 22 refs / live 61 → **14426.2** | a0 (wrong) |
| merged `s0` + `flag` variable kept (`scratch/A.c`) | one pseudo, 8 refs / live **17** → **14117.6** | 14426.2 | a0 (wrong) |
| merged `s0` + constant store (**body.c**) | one pseudo, 8 refs / live **16** → **15000.0** | 14426.2 | `s0` (target) |

The `flag = 1` insn sits inside the merged pointer's live range (`s0 = load; flag = 1; if (s0 …)`), so it adds exactly
one to the live length: 16 → 17 drops 15000 to 14117.6, below a0's 14426.2. Neither move closes alone (A = 42,
B = 30); only the joint edit does (method step 5).

## (c) The moves that closed it
1. `flag` deleted: the store is `*(u8 *)(a0 + 0xC0) = 1;` (the variable was 1 on every path). The target's
   `li v0,1` in `beqz s0`'s delay slot and the `li v0,1` after the inner if are reorg filling/redirecting around the one
   `li v0,1; sb` at the join (outcome proven on bytes; I did not read the `.dbr` for the individual steal decisions).
2. The two per-arm `s32 s0 = *(s32 *)(a0 + 0xDC);` merged into ONE function-scope `s32 s0;` (S103 c18: same register,
   same role, same expression in both arms → one original variable). Its refs double (4 → 8) while the live length only
   doubles, and `floor_log2` lifts it from 2 to 3: 10000 → 15000.
3. (readability, not needed for the bytes) the `goto tail;` chain rewritten as `if { …; func_8012AD50(a0); } else { … }`
   with the shared final call, and the `v1` read-modify-write as `|= 0x1000000`. `scratch/C.c` (goto kept, moves 1+2
   only) also scores 0, so the structured shape is a free choice here; the structured one is delivered.

## (d) Generator proposal
When a pinned local is assigned the same constant on every path to its single use, replace the use by the constant
and delete the local; and when two block-scoped locals of the same name are loaded from the same expression in sibling
arms, hoist them into one function-scope variable — always try the two together (the second's priority gain is
cancelled by the first's extra live insn).

## (e) What did not work
- Constant store alone (B): 30, pure `$s0/$s1` swap — two per-arm pointers at priority 10000 each lose to a0.
- Merge alone (A): 42 — `flag` still costs `$s2`, and its `li` lengthens the pointer's live range to 17.
- Merging `a1` as well (`scratch/m2.c`): also 0, not needed.

## (f) Where the method fell short
Nowhere significant: `alloc_table.py` on three spliced TUs explained both failures and the close in arithmetic. The sweep
could not reach it because no generator deletes a variable in favour of a constant it provably always holds, and the
per-arm merge (R-inverse of R23) was never tried jointly with it.

## (g) Structs answer
No. The deciding numbers are ref counts and live lengths of the pointer and `a0` pseudos; an actor struct for `a0`
(`+0x20` obj ptr, `+0x70` s16 index, `+0xDC` sub-record ptr with `+0x0/+0x4` model ptrs and `+0xC` flag, `+0xC0/+0xC1`
u8 flags, `+0xBC/+0x58` ptrs, `+0x5C/+0xAE` u16, `+0xC4` bit word) would emit the same MEMs off the same pseudos and not
change `allocno_compare`'s inputs. The struct is still the right READABILITY type for the structs phase; it is not
needed for the bytes.

## Copies (all `--try` 0 with this text, symbols renamed)
| function | TU | file |
|---|---|---|
| func_8017DAB8 | src/ov_SC02_026/ov_SC02_026_jr_8017C180.c | PACK/body.c |
| func_80181F38 | src/ov_SC02_027/ov_SC02_027_jr_8017D898.c | PACK/scratch/ov_SC02_027__func_80181F38.c (TU declares the D_ symbols at file scope; no body-local externs) |
| func_80180040 | src/ov_SC02_028/ov_SC02_028_jr_8017D898.c | PACK/scratch/ov_SC02_028__func_80180040.c |
| func_80180BFC | src/ov_SC03_092/ov_SC03_092_jr_8017FE88.c | PACK/scratch/ov_SC03_092__func_80180BFC.c |
