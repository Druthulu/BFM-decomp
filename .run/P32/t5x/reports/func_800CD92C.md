# func_800CD92C (md_MAIN_009, 247 ins) — Fable arm (t5x) — **MATCH 247/247, real TU, zero pins**

Deliverable: `.run/P32/t5x/fable/func_800CD92C.c` (N9b). `match_one` MATCH; `rtu_match --split md_MAIN_009 --source md_MAIN_009`
MATCH in the real TU; relocation audit (R1c) 2×D_800A71D0 (lw/sw), 2×D_800ABA24 (la + `lw D_800ABA24($3)`), 12×D_800BAE22 —
identical to the target's `%hi/%lo` counts. Externs spelled as the TU's file-scope lines 224-226 (`extern u8 *D_800A71D0;`
`extern u32 D_800ABA24[];` `extern u16 D_800BAE22;`); no typedefs, no `register`, no `__asm__` (the Opus draft's five §17
pins are gone — the prior `extern u32 D_800A71D0` now CC1-FAILs in the TU because func_800CD674 was banked with `u8 *`).

## What the residual actually was (read from the compiler + `-dS/-dl` dumps, not guessed)
The Opus draft's 15 was NOT "sched2 prologue weave steered by nothing". Two independent mechanisms, both decided in sched1
and local-alloc, both fixed by spelling the addPrim the way libgpu's `P_TAG` bitfield macros expand:

**1. m24's register is a REF-COUNT effect, not a pin.** `qty_compare` (local-alloc.c:1579) = floor_log2(n_refs)·n_refs·size /
(death−birth) with `qty_n_refs = reg_n_refs` (local-alloc.c:297) — FLOW's count, computed before combine (toplev.c:2983 vs
3004) and not adjusted by combine (combine.c:56). la (13 refs, life 342) beats an unpinned m24 (13 refs, life 420) → la=$9
(E1 measured: 41 mismatched — Opus's "dropping the m24 pin → 41"). The libgpu `setaddr(p, getaddr(ot))` bitfield store
re-masks its already-masked value (`store_fixed_bit_field` must_and, expmed.c:608-620): pre-combine RTL `(and (and ot m24)
m24)`, folded by combine's associative rule (combine.c:3140-3170 → `simplify_binary_operation` AND op0==op1, cse.c:3930) to
ONE `and` — but m24 keeps 19 refs → 4·19=76 > la's 39 → m24 first → $9, la $10, FF00 $11. Spelled `(ot & m24) & m24` with
`u32 m24 = 0xFFFFFF` (E3: identical bytes to the pinned draft, closeness 15, m24 "used 19 times" in `-dl`).

**2. tp8D/tp8F float because the TAG LOAD is a multi-set pseudo.** sched1 `try_split`s every insn before scheduling
(sched.c:4826; mips.md:3210 `large_int` → lui+ori) and `update_flow_info` → `update_n_sets` bumps `reg_n_sets` to 2
(sched.c:4617/4234), so every 0xE10000xx constant is an unboosted pri-1 floater (pinned or not — E2 no-pins had the identical
stall picks). Backward list scheduling consumes a floater only in an EMPTY ready-list cycle; each RMW chain has exactly one
(the `lhu→sll` latency gap, cost 2 queue): base trace stalls T-44/54, 81/91, 116/126, 150/160 = prim (k−1)'s two gaps eat
prim k's constant (tp87→r5, tp86→r4, tp8F→r3, tp8D→r2; tp8B/m24/tp89 reach the top). In the target's sched2 top block
(= ascending LUID of the pri-1 pool, memory ops hazard-first) tp8D/tp8F sit BELOW li5, i.e. they floated. The bitfield
RMW expands `t = *p; t &= FF00; t |= v; *p = t` on ONE pseudo (expand_binop target reuse): `reg_n_sets`=3 → no birthing
boost (sched.c:2490) → the tag load is not glued to its `and` and fills the `lhu→sll` gap instead (N1 trace T-52,
N7 stall list shrinks to one) → tp8D/tp8F float, and local-alloc's life order gives tp8B $16, tp86 $17, tp8D $18, tp8F $19,
tp87 sharing $16 (N6/N7 dumps). Spelled `{ u32 v = (ot & m24) & m24; u32 t = *(u32 *)p; t &= 0xFF000000; t |= v;
*(u32 *)p = t; }`.

**Two sub-lessons inside #2 (each cost one probe):**
* `v` must be a FRESH expression: `v &= m24` in place makes a 4-ref/2-insn qty (pri 2.0 > p's 1.6) that is allocated
  before `p` and takes $2 → the 178-diff $v0/$v1 swap (N4/N6).
* `v` (the OT read) must precede `t &= FF00`: the FF00 constant is force_reg'd where the `and` is expanded; if its UID is
  below the index `sll`'s, sched1's boosted tie (LUID rule) picks the `sll` first and FF00 drops into prim 1's `lhu→sll`
  gap; the unboosted tag load then lingers into the store stream, is memory-unit `blocking insn 81` each cycle, and its
  bubble (T-207) takes the highest-LUID floater = tp8F's `ori` → the closeness-2 `li $t7`/`ori $s3` swap (N7 vs N1 traces).

## Why the natural libgpu form itself is NOT the draft (measured, for the record)
N1 (struct fields + `P_TAG` bitfield addPrim + `/s` index) reproduces the whole prologue/body SHAPE (239 ins, only −8),
but any struct/array/cast spelling of D_800BAE22 goes through `change_address → memory_address → force_reg` (constant
address, pre-cse) = one shared `la $11,D_800BAE22` + 12 `lhu 0($11)`, which steals $11 and shifts every later register.
The target's 12 `lui/lhu D_800BAE22` gas-macro loads mean the original read it as the plain scalar the TU declares. A `/s`
tag store with a plain scalar index would CSE the second `lhu` (§364: cse.c `note_mem_written` sets `all=0` for a
MEM_IN_STRUCT_P or PLUS-address non-QI store, `invalidate_memory` then spares non-struct fixed entries), so the tag store
stays the non-`/s` `*(u32 *)p` while the mask/pseudo SHAPE of the bitfield expansion is kept by hand. The OT side keeps the
t3 levers (ARRAY_REF lvalue, block-scoped `oi`) — N6 showed the OT spelling is irrelevant to the prologue.

## Levers measured (all in `.run/P32/t5x/work/func_800CD92C/`, dumps in `dumps_<variant>/`)
| variant | change | result |
|---|---|---|
| base (Opus t3) | 5 pins | 15 |
| v_unpin8D8F | tp8D/tp8F inline, other pins kept | 245 ins (alloc shift) |
| e1_m24unpin | m24 plain local | 41 (la takes $9) |
| e2_nopins | everything plain | 241 ins, frame 16 |
| e3_dblmask | m24 plain + `(ot&m24)&m24` | **15, byte-identical to base** (m24 $9 by 19 refs) |
| n1_libgpu | struct fields + P_TAG bitfields + `/s` index | 239 ins (−8 = the `la` index), prologue SHAPE = target |
| n2A/B/C/D, n3 | other `/s` index spellings (array, cast, asm-label alias) | `la` in all but A; A is non-`/s` and CSEs to 6 loads (222) |
| n4_inplace | E3 + in-place `t`/`v`/`o` temps, no pins | 247, 178 ($v0/$v1 swap) |
| n5_otonly / n6_tagonly | bisect | OT side inert (241); tag side = 178 |
| n7_tagT | in-place `t`, fresh `(ot&m24)&m24`, FF00 first | **2** (`li 5`/`ori $s3` swap) |
| n8_u8ptr | n7 + TU's `extern u8 *D_800A71D0` | 2, rtu compiles |
| n9a / n9b | FF00 after the OT read | **MATCH** (both instruments) |

## Cookbook-worthy generalizations (for the coordinator's harvest)
* **REF-COUNT ALLOCATION LEVER:** a mask/constant's local-alloc priority counts flow-time refs; a source that produces a
  combine-foldable redundant use (`(x & m) & m`, the bitfield must_and) raises the pseudo's priority at zero bytes. This is
  how libgpu's bitfield addPrim puts the 24-bit mask in `$t1` ahead of the OT base in every SPRT/POLY function — check
  `-dl` "used N times" before pinning a mask register (§17 pins are a symptom-fix here; §501-E shows their side effects).
* **UNBOOSTED TAG LOAD = STALL FILLER:** an in-place RMW temp (multi-set) frees the `lhu→sll` gaps that otherwise eat
  the split large-constant floaters; the "prologue weave" of hoisted `lui/ori` pairs is decided by which pseudos are
  single-set in the RMW chains, not by any prologue-side lever (extends map §S7/§S2).
* **Struct-member GLOBAL access = one `la`:** `change_address → memory_address` force_regs a constant address pre-cse; a
  target with N `lui/lhu SYMBOL` macro loads read a plain scalar — do not spell it as a struct field.
* **Statement order inside an RMW block sets the UID tie among boosted insns** (FF00 vs the index `sll`): materialize a
  mask constant AFTER the address expression it competes with.
