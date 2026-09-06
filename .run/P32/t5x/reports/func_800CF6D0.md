# md_MAIN_007:func_800CF6D0 — arm fable (P32 T5x, session 491895ad, 2026-09-05) — **MATCH 249/249, real TU, zero pins**

Deliverable: `.run/P32/t5x/fable/func_800CF6D0.c` (= work variant `d06` + header). `match_one` MATCH (249 ins);
`rtu_match --split md_MAIN_007 --source md_MAIN_007` MATCH in the real TU (work `.run/P32/t5x/rtu/func_800CF6D0/final`).
Relocation audit (law 1c): target `.s` D_800A5E60 x4, D_800AA60C x4, D_800B9A02 x24 — `objdump -r` on my object: identical.
Externs spelled as the TU's other drafts in this TU spell them (`extern u8 *D_800A5E60; extern u8 D_800AA60C[]; extern s16 D_800B9A02;`,
§500-F); the definition uses the TU's own prototype `void func_800CF6D0(s32, u32)` (TU line 208/221 — the `s32, s32` spelling is a
`CC1 FAIL: conflicting types`). No `#include`, no file-scope typedef (the `P_TAG` typedef is function-scoped as in func_800CF408).
Start: prior best `.run/P32/t3/opus/func_800CF6D0.c` closeness 137 (exact length). Ladder: 137 -> 30 (d02) -> 26 (d03) -> 10 (d04)
-> MATCH (d05 leaf, d06 real TU). `src/` and `config/` untouched. Scratch under `.run/P32/t5x/work/func_800CF6D0/` (`gen.py` = the
variant generator, `meas.sh`, `dump.sh` = a private copy of cc1_dumps.sh with `-dr -dj -ds -df -dc -dl -dg -dS -dR -dd`, `annot.py` =
sched trace/insn annotator, `qty.py` = local-alloc qty_compare estimator, `dumps_<tag>/`, `dumps_twin/` = the same dumps of the
banked twin md_MAIN_009/func_800CD92C for known-true comparison).

## The prior verdict was mis-attributed: three mechanisms, none of them sched1's rank_for_schedule
The T3 report called the residual "sched1 rank_for_schedule last-insn-class tie (QI stores grouped, loads floated, HI stores after) +
a $t1<->$t3 mask swap" and listed 19 field orders, pins, fences, volatile and /s-denial as inert. Read from the dumps:

### A. The QI/HI store split is **sched2**, and it is the `/s`-vs-fixed-address alias exemption — 137 -> 30
* `-dS` (sched1) OUTPUT of the T3 draft already has all 13 block-1 stores before the `lhu` (idx 10-30). The regrouping happens in
  `-dR` (sched2, post-reload): at T-185 the five `sh` stores and the `lw 0(p)` tag read are ready together at priority 2, ONE clock
  before the `lhu` (85) is launched; `schedule_select` picks a store over the load ("insn 76 has a greater potential hazard"), and the
  just-placed store then blocks BOTH loads for a cycle ("blocking insn 79/85 for 1 cycles"), so every `sh` lands after the loads.
* WHY the `sh`/`sw` stores were ready early: sched.c:838-845 `true_dependence` (and anti/output) exempts a `/s` store at a VARYING
  address in NON-QImode from conflicting with a non-`/s` FIXED-address read (`lhu D_800B9A02`). QImode `/s` stores get no exemption
  ("ANSI C allows character pointers to alias anything"), so the `sb`s must precede the `lhu` and the `sh`/`sw` need not — exactly the
  observed QI-before / HI-after grouping, in every block whose `lhu` came out of the queue one clock late.
* The target has all 13 stores before the `lhu` in every block => its non-QI field stores DID depend on the load => they are not `/s`:
  **cast stores `*(u16 *)(p + 0x12) = ...`**, the twin's spelling. (The T3 report measured "casts = 243 ins, sheds callee-saved regs" —
  that draft ALSO changed the tag RMW; with the twin's multi-set tag RMW the casts are the closer.) Then the 13 stores are pure
  LUID = source order; the target's per-block order is `len, tpage, code, clut, b0, g0, r0, x0, y0, u0, v0, w, h`, with the chained
  `*(p+8) = *(p+9) = *(p+0xA) = 0x80` giving 0xA, 9, 8.
* The hazard rank inside one priority group, from the traces (sched.c `schedule_select`/`potential_hazard`): **store > load > ALU**;
  a store just scheduled blocks a following load one cycle, never a store. Block 2's `sw $s0,4` before `sb $t7,3` and block 4's
  `sh $a1,0xE` above the ALU trio are consequences of anti-dependences on hard registers (`lui $s0` / `and $a1`), not source order.

### B. The OT write must be `/s` (P_TAG bitfield) — 30 -> 26
d02 spelled the OT write as a cast RMW; the tail then read `and/or/sw OT; lui $at; sw D_800A5E60` (5 rows). `D_800A5E60 = p` is a
non-`/s` FIXED store: only when the OT write is `/s` (varying, SImode) does the SAME exemption (output_dependence) let it float above
block 6's OT write to the target's idx 243-244 — §351's "the OT write must stay a P_TAG bitfield", now with the line cited.

### C. `la D_800AA60C` -> $t2 / 0xFF000000 -> $t3 is a FLOW ref-count tie — 26 -> 10
* `qty.py` over the sched1 output (suid order local-alloc scans): d03 `mhi` r94 13 refs, birth 35, death 218 -> QTY_CMP_PRI 8524;
  `ob` r75 **12 refs**, birth 42, death 213 -> 8421: mhi wins $t2 by 1.2%. The twin (matched): `la` r88 **13 refs**, life 170 -> 9176;
  mhi 13 refs, life 182 -> 8571: la wins. Same lives, one ref apart.
* The twin's 13th ref: its `la` is a compiler-made pseudo used in block 1's tag-side read TOO (`.cse`: 12 `addsi3` uses), and combine
  then does a 3-insn merge of `la` def + first `addu` + `lw` into `(mem (plus idx symbol))` — the raw-symbol `lui $at/addu/lw %lo`
  form of read 1 — re-emitting the `la` def as newi2pat because the pseudo is still used later. Flow ran BEFORE combine and combine.c
  never adjusts `reg_n_refs`, so the pseudo keeps 13 refs (§501-G(3)/§501-H(1), the same law from the other side).
* Lever: assign `ob = D_800AA60C;` BEFORE block 1 and use `(s32)ob + idx` in block 1's tag-side read as well (d04). The T3 draft's
  §351 base-split (raw symbol for read 1, `ob` assigned after) produces the SAME instructions but only 12 refs — the register swap.
* Side effect (d04: 10 rows, all frame offsets 0x20 vs 0x18): the folded first-read SUM pseudo (d05 r90 = `idx + ob`; the twin's
  r91, an identical `.lreg` line `used 2 times across 2 insns; dies in 0 places; ST_REGS or none; pointer`) is the ONLY pseudo that
  combine removes from the insn stream WITHOUT zeroing its ref count: combine.c:2313/2336 set `reg_n_refs = 0` for an i2dest/i1dest
  that vanishes in an ordinary merge (the 18 other dead temps r87, r92, ... have no `.lreg` line at all), but in this 3-insn merge the
  la def is re-emitted as newi2pat and the sum pseudo keeps `reg_n_refs = 2`. It is in no insn, so local-alloc never sees it and
  global-alloc leaves it, and reload1.c:2309 `alter_reg` (`reg_renumber < 0 && reg_n_refs > 0 && no reg_equiv`) gives it a 4-byte
  `assign_stack_local` slot -> the MIPS frame rounds to 8 -> `.frame vars=8` = the target's 0x18 (4 saves + 8). The T3 draft needed
  `u32 pad[2]` (§358) only because it lacked that pseudo; with the ob-first spelling the pad double-counts -> remove it (d05 = MATCH).
  Measured: d03 (no sum temp, pad) vars=8; d04 (sum temp + pad) vars=16; d05 (sum temp, no pad) vars=8; twin (no pad) vars=8.
  No `(use (reg` USE-orphans in any `.combine` — this is a THIRD §172 frame producer, distinct from the USE-orphan one.

### D. Everything else = the twin's byte-proven shape (§501-H), transliterated
Multi-set tag RMW `t = *p; t &= 0xFF000000; t |= v; *p = t;` (no birthing boost on the tag load -> it fills the lhu->sll gap and
the 0xE10000xx floaters reach the top; `$s0` shared by 0xE100008B/0xE1000087 with zero pins), `v` (the OT read) BEFORE `t &= FF00`,
`(ot & m24) & m24` with `u32 m24 = 0xFFFFFF` (19 refs -> $t1), `p->x0 = arg0 + 0x100` as expressions (the third ties into `$a0`,
local-alloc combine_regs on the dying arg), `p += 0x18`, `D_800A5E60 = p` last. The (u16) cast on the s16 `D_800B9A02` gives `lhu`.

## Inert / not needed (measured this session or superseded)
* `u32 pad[2]` with the ob-first spelling: +8 frame (0x20) — the T3 lever is superseded, not wrong for its draft.
* Array-indexed OT without `ob` (`*(u32 *)(D_800AA60C + idx)`, d01): 254 ins / 191 — with a `u8[]` symbol cse does not build the
  single `la`; the explicit `ob` variable is the spelling for this TU's `extern u8 D_800AA60C[]` (the twin's `u32 D_800ABA24[]` gets it free).
* Cast OT write (d02): the tail stops floating (B).
* The T3 inert list (pins, fences, volatile, /s-denial subsets, 19 field orders) stands for THAT draft; none of it was the lever.

## Variant ledger (all under .run/P32/t5x/work/func_800CF6D0/)
| v | change | closeness |
|---|---|---|
| d00 | T3 opus draft (struct-member stores, plain tag, P_TAG OT write, pad[2]) | 137 |
| d01 | twin transliteration, OT array-indexed on the u8 symbol, no ob | 191 @ 254 ins |
| d02 | + explicit `ob` base-split (assigned after read 1), cast OT write | 30 |
| d03 | + P_TAG bitfield OT write | 26 |
| d04 | + `ob` assigned before block 1 and used in read 1 | 10 (frame 0x20) |
| d05 | - pad[2] | **MATCH** (leaf) |
| d06 | prototype `(s32, u32)` per the TU | **MATCH** (leaf + real TU) |

## Cookbook-worthy generalisations (for the harvest)
1. **QI-vs-non-QI store regrouping around a fixed-address load = the sched.c alias exemption, in sched2.** A `/s` store at a varying
   address in HI/SI mode never depends on a fixed-address non-`/s` read; a QImode one always does. If the target keeps all field stores
   before such a load, spell the non-QI stores as casts (or the read as `/s`). Diagnose in `-dR`, not `-dS`.
2. **"Inert" field-order sweeps on `/s` stores are expected**: LUID only orders stores that are READY together; a dependence split beats it.
3. **A register tie between a `la` and a mask constant is a flow ref-count dial**: give the address variable its first use where the
   compiler's own pseudo would have had it (before the raw-symbol first read) and let combine fold the constant back; +1 ref, same bytes.
4. **An unexplained 8-byte frame under a combine-folded address = a reload slot for a ref-count survivor (combine.c:2313/2336 vs a
   newi2pat 3-insn merge; reload1.c:2309), not a §172 USE-orphan** — the tell is a `.lreg` line `used 2 times ... dies in 0 places;
   ST_REGS or none` for a pseudo that no insn mentions. Ablate (`.frame vars=`) before adding `pad[2]`.
