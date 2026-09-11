# func_8017D494 (ov_SC04_011_jr_8017D494.c) — T7 agent c37 — CLOSED, score 0 (and all 44 slider sites of the class)

## (a) The residual
Lever-free (`body_free.c`): score 10, REG-caller, 952 = 952 instructions. `&g.sz1` (sp+208) and `&g.sz2` (sp+212), both
hoisted into the OUTER loop's preheader, get t8/t9 swapped (target: sz1 → t9, sz2 → t8), 5 sites. Count equal, order
equal: pure allocation order.

## (b) The pass and the decision
global.c `allocno_compare` (`global.c:590-610`): `pri = (int)(floor_log2(refs) * refs / live_length * 10000)`, the int
truncation is the point; equal pri → lower allocno first. `alloc_table.py` on the lever-free body:

| pseudo | value | refs | live | pri (int) |
|---|---|---|---|---|
| r227 | &g.sz0 (sp+204) | 13 | 784 | 497 |
| r229 | &g.sz1 (sp+208) | 13 | 783 | 498 |
| r231 | &g.sz2 (sp+212) | 13 | 782 | 498 |

229/231 tie → 229 first → t8. The target allocated 231 first. Refs cannot differ (1 preheader def + 4 asm operands × loop
depth 3, `flow.c` refs weighting). Pseudo numbers follow the stsz3 operand order, which also fixes the preheader order, so the
target cannot have tied either: its live lengths differed. The live lengths are sched1's recount (`sched.c:3846-3861`,
written back at `sched.c:4946-4947`): every insn of the outer loop body counts once for each of the three (they are live
around the whole loop), and the back-to-back preheader defs make L227 = L229+1 = L231+2. Arithmetic over a uniform shift Δ
of the loop's sched1 insn count, requiring 231 > 229 > 227 strictly and 763/82/81 unmoved: **Δ ∈ {−10, −7, −2, +1, +4, +9}**
work; 0, ±1 (the wrong one), +2, +3 all lose. The tree's `__asm__ volatile("")` was exactly Δ = +1: an ASM_INPUT insn that
emits nothing.

So the job is: one more RTL insn inside the outer loop at sched1 that the final code does not contain. The invisible
insns this function already has at sched1 (`.sched` vs `.jump2`): 29 combine USE insns (dangling REG_DEAD notes from 3→2
combines of `short` field loads, `combine.c:10837-10845`), 2 self-copies (the F3/FT3 else-arm `za = g.sz1`, tied, deleted
by jump2 `jump.c:431-433`) and 15 insns merged by post-reload cross-jump.

## (c) The move that closed it (proved on bytes)
In `case 0: case 1:` (POLY_F4) only, give the final max its own name — the "one name per value" split:

```c
    s32 za, zb, zc;                          /* was: s32 za, zb; */
    ...
    za = g.sz0;
    if (za < g.sz1) za = g.sz1;
    zc = za;                                 /* was: if (za < zb) za = zb; */
    if (zc < zb) zc = zb;
    g.opz = zc;                              /* was: g.opz = za; */
    ((PolyF4 *)pkt)->rgbc = prim->w0;
    otp = (u32 *)(((zc >> 2) << 2) + ot);    /* was: ... (za >> 2) ... */
```

`zc = za` is RTL insn 1487 `(set (reg/v 486) (reg/v 484))` with REG_DEAD 484: both pseudos are block-global, they do not
conflict, global.c's copy preference (`expand_preferences`, `global.c:781-815`; used by `find_reg`, `global.c:1001-1071`)
puts both in a0, the copy is `a0 = a0` in `.greg`, and jump2 deletes it (`jump.c:431-433`, sreg == dreg) — absent from
`.jump2`. It exists at sched1, so the loop's live lengths become 785/784/783 → pri 496/497/498 → 231 first → t8 → the
target. Proved: `--try` score 0 (952/952), and the candidate object's objdump (with relocations) and `.rodata` diffed against
`.run/P36/delever/baseline/src/ov_SC04_011/ov_SC04_011_jr_8017D494.o` are identical. `.greg` of the close lists three
self-copies (860, 1123, 1487) where the lever-free body had two.

Spellings that also score 0: `if (za < zb) zc = zb; else zc = za;` (jump1 turns it into the copy + conditional set),
`zc = za; if (zb > zc) zc = zb;`, and renaming to z01/z23/z. The ternary `zc = (za < zb) ? zb : za;` does NOT (score 9).

**Propagation readout (read-only `--try`, no tree writes):** the same edit + deleting the slider line, applied to every one
of the 44 files carrying the `§45-B live-length slider` (35 inline TU copies + 9 shared headers
`src/shared/ov/func_8017{BEBC,C180,C24C,C294,C710,C8D0,CA80,D5C0,D898}__*.h`), scores 0 on all 44 at the function level.
Candidate bodies: `PACK/scratch/prop/*.c`, generator `PACK/scratch/prop.py`. The bank still judges the whole object.

## (d) GENERATOR PROPOSAL
When a REG residual is a pure swap between two allocnos whose `alloc_table` priorities are EQUAL as ints (same refs, live
lengths one apart across a bucket boundary), compute the set of live-length shifts Δ that split the tie in the target's
direction (`floor(K/L)` arithmetic over every allocno within ±Δ), and for Δ = +1 apply "name the result" at a site inside
the common live range: `x = a; if (x < b) x = b;` followed by uses of x → `y = x; if (y < b) y = b;` with the later uses
renamed to y, where x dies at the copy and x/y are both block-global (so global.c ties them and jump2 deletes the copy).
Score every candidate site — the site matters (the same edit in FT4 changes the code, score 40, because there the copy's
source does not die unshared).

## (e) What did not work (byte evidence)
- Every comparison flip (`a > b` ↔ `b < a`) in the body: code identical, Δ = 0 (30 of 58 sites), the other 28 change code.
- `continue`-style culls instead of nesting (lim, bbox x/y, flag, opz), `while` instead of `for`, `prim++` moved into the
  body, width changes of lim/nparts/j/nprim/i/code/w/wx/wy/wz/t32/ot, `(s16)` casts replaced by `mx = mxc` copies: all Δ = 0.
- Removing the F3/FT3 self-copies (Δ = −2 by loading sz1 straight into za): changes the load order, +4 insns (score 62).
- F4 `zb`/`za` as `if/else` pairs: split the tie (Δ = +1) but the copy's source is block-local, so local-alloc refuses the
  tie (`local-alloc.c` `combine_regs`, dest not local) and the copy survives into a load delay slot (score 2).
- `u16 lim` (the mechanical search's best, 4): splits the tie but changes the compare.
- Splitting a GTE macro into two Sony macros (e.g. `gte_stsxy01` + `gte_stsxy`) would be Δ = +1 but a volatile asm makes
  every later register reader depend on it (sched.c `reg_pending_sets_all`), so the addiu order changes — and it is an asm
  lever anyway. Not tried on bytes for that reason.

## (f) Where the method fell short
- METHOD_S103 has no bullet for a priority TIE split by live length; the S102/S103 entries are all about refs or live-length
  deltas of ONE pseudo. The decisive step was the Δ table (all allocnos live across the loop shift together, so only some
  Δ keep the rest of the order) — that is arithmetic a tool can print: `alloc_table.py` could flag int-priority ties between
  allocnos with distinct float priorities and list the Δ values that split them.
- A per-variant measure of the three live lengths (`PACK/scratch/dump.sh` + `lens.py`, ~1 s) turned the search from
  "score only" into "which invisible-insn count did this change": 90 % of natural rewrites are Δ = 0, which the score alone
  cannot distinguish from "no effect".
- The invisible-insn inventory (USE / self-copy / cross-jump, from diffing `.sched` against `.jump2` insn UIDs) named the
  candidate mechanisms in minutes; worth a tool (`grep -E '^\((insn|jump_insn)(:[A-Z]+)? '` — note the `:QI`/`:HI` mode
  tags reload puts on insn headers in `.greg`, which silently empty a naive grep).
