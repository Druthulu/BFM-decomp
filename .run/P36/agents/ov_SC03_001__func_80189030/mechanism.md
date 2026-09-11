# func_80189030 (ov_SC03_001_jr_80189030.c) — P36 S104 agent d19

**Result: score 0, ZERO levers** (the tree has 1 lever — a `__asm__ __volatile__("" :: "r"(p))` keepalive — 1 → 0). `PACK/body.c`.
The same text (with only the per-overlay `D_` names changed) also scores 0 on the class's other two copies:

| function | TU | file | score |
|---|---|---|---|
| func_80189030 | src/ov_SC03_001/ov_SC03_001_jr_80189030.c | PACK/body.c | 0 |
| func_80185C98 | src/ov_SC03_124/ov_SC03_124_jr_80185C98.c | PACK/scratch/func_80185C98_body.c | 0 |
| func_80186270 | src/ov_SC05_017/ov_SC05_017_jr_80186270.c | PACK/scratch/func_80186270_body.c | 0 |

(Copies found by grepping `[flagCount++] = 6`; the other files that call `func_80029178(0x11D)` have no `k = k + 2` and are other
functions. The copies were produced by the same mechanical transform applied to their tree text, which reproduces `PACK/body.c`
exactly when applied to `body_tree.c`.)

## The move (one idea, applied to both of its sites; both needed)
The two "search the threshold table" loops (`for (k = 0; k < 4; k++) if (iVar5 < D_801C1830[k]) break;`, one in the mode-3
block, one in mode 5's `case 3`) use `j` as their index instead of `k`; `k` keeps only the derived list count:
`k = j + 2;` (was `k = k + 2;`). `D_801C1838[k]` in case 3 becomes `D_801C1838[j]`. Nothing else changes.

Byte evidence for "jointly needed": mode-3 loop only (v1) = 19; mode-5 loop only (v6) = 37; both (v3) = 0. Also merging `cnt`
into `j` on top (v4) = 0 as well, `cnt` alone (v5) = 16; I kept the smaller edit (v3). Splitting `p` and/or `j` per loop
(va/vb/vc) = 13, unchanged.

## (a) The residual
13, REG-callee, 557 = 557 instructions: a pure `$s0`/`$s1` swap between the list-walk pointer `p` (mine `$s0`, target `$s1`) and
its loop counter `j` (mine `$s1`, target `$s0`) in both "found" loops of the mode-3 block. Nothing missing or extra (counted
on the full objdumps, `scratch/tgt.txt` vs `scratch/mine0.txt`).

## (b) The pass and the decision (proved on bytes and on the dumps `scratch/dumps_{fr,tr,v1,v3,v6}`, tables `scratch/at_*.txt`)
Global allocation order, `allocno_compare` (`global.c:587-610`): priority = `floor_log2(refs)·refs/live · 10000` (`:595-599`),
compared before anything else (`:602`). Refs are weighted by loop depth (`flow.c:2067`), so the pointer (three refs per
iteration: deref, increment use, increment set) outranks its counter (two).
- lever-free (fr): `p` r81 18 refs / 31 live → 23225.8; `j` r80 13 / 39 → 10000.0; `k` r79 24 / 36 → 26666.7.
  Order … r79 (k) → `$s0`; r81 (p) — no conflict with k (k dies at the loop-hoisted `(short)k` bound copy before the list
  loop) → `find_reg` pass 0 (`global.c:952`, only registers in `regs_used_so_far`) → `$s0`; … r80 (j) conflicts with p →
  `$s1`. Wrong.
- tree (tr, keepalive): the asm reads `p` on the `D_80115126 != 3` path where it was never set, so flow makes `p` live from
  function entry: 19 refs / 106 live → 7169.8 < j's 10000 → j is allocated first → `$s0`; p → `$s1`. The lever lowered p.
- body.c (v3): `j` now carries the two search loops as well: r80 34 refs / 68 live → 5·34/68 = 25000.0 > p's 23225.8. Order
  … r80 (j) → `$s0`; r81 (p) conflicts with j → `$s1`; `k` r79 is now 3 refs / 8 live (3750.0), is born where j dies
  (`k = j + 2`), so it still gets `$s0` late — exactly the target (`$s0` holds base, cnt, k, j and case-3's index).
  v1 (mode-3 loop only): j 21/54 → 15555.6 < 23225.8 → still wrong (19). v6 (case-3 only): j 26/53 → 19622.6 → wrong (37).
All three priorities read off `tools/alloc_table.py`; the order lines confirm r80 before r81 only in v3.

## (c) The source move that closed it
MERGE two same-width loop indices the decompiler split: the original used one `short` index (`j`) for every short search
loop and a separate variable only for the value derived from it. This is S103 c18 / S104 d12's merge, but between
DIFFERENT roles (the counter of a list walk and the index of two table searches), found by priority arithmetic, not by
"same register, same expression".

## (d) GENERATOR PROPOSAL
**When a REG-callee residual is a swap between a loop's walked pointer and that loop's counter (the counter loses), rename
the index of the body's other same-width, non-overlapping loops to the losing counter — all such loops jointly — rewriting
any post-loop `x = x + C` of the old index as `x = counter + C`, and accept when `alloc_table` shows
`floor_log2(refs)·refs/live` of the merged counter above the pointer's.** (A generator can enumerate: every same-typed local
whose live ranges do not overlap the counter's, every subset in merged form; the arithmetic prunes it before compiling.)

## (e) What did not work (byte evidence)
- The sweep's 13 families (R2–R26, `history.txt`): all 13 — block/do-while/swap/temp moves never change refs or live of p/j.
- Splitting `p` into two pointers, `j` into two counters, or both (va/vb/vc): 13 — each half keeps the same ratio.
- Merging `cnt` into `j` alone (v5): 16; only one of the two search loops (v1 19, v6 37): below the threshold, see (b).

## (f) Where the method fell short
- The lever pointed at the WRONG variable for a plain-C fix: the keepalive lowered `p`'s priority, the natural fix raises
  `j`'s. Reading the allocation table (step 4) before anything else was what exposed that it is a two-allocno priority race
  and that any source change raising `j` above 23225.8 would do; `k`'s 24 weighted refs in two short loops were the obvious
  pool. The method's merge advice (S103 c18, S104 d12) is phrased as "same role / same register pins"; it should also say
  "merge a DIFFERENT-role same-width local into the loser when the arithmetic says its refs would carry it over".
- No generator family merges locals across roles; R23 only splits.

## (g) Structs
No, not for this decision: it is pure allocation priority (refs/live of two pseudos), no memory-dependence channel
(`expr.c:4568-4577` vs `sched.c`/`cse.c`) is involved, and the close needed none. For readability: `D_801EB574[]`/`D_801EB56C[]`
are parallel arrays of 7 lists (pointer, byte count); `D_801EB58C`/`D_801EB572` are exactly their element 6 (0x801EB574+24,
0x801EB56C+6), and `D_801EF1F4` is an array of 16-byte records written at `+4` (a pointer/value) and `+8` (a small
number), whose addresses go into `D_801EF254[i]`. Writing the 7th check as `D_801EB574[6]` would change the relocation symbol the target uses (`D_801EB58C`) — the
split symbols stay as long as the linker map names them. Not tested on bytes (not needed).
