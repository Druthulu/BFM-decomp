# func_80030F80 (src/800_b_2.c) — S104 agent e2 — NOT closed in plain C; minimum-lever body at 0 (1 lever -> 1 lever)

## (a) The residual
Lever-free: score 19, COUNT, 341 vs 343. ONE local defect; everything else is branch-offset fallout. At `case 3:` the
target RE-READS the voice's u16 index (`lhu v0,0(s0); nop; sll v0,v0,2`) while mine reuses the dispatch's `lhu a0,0(s0)`
(`sll v0,a0,2`): 2 instructions missing (the lhu and its load-delay nop). Case 2 in the target DOES reuse that `$a0`
(it is `func_8003D3B4(idx, 1)`), and the bottom `st == 0 || st == 3` path reuses its own index load too — only case 3
reloads. The case-3 `sb zero,0x46(s0)` must also stay AFTER the table `lw` (it lands in the jal's delay slot, and
`move a0,zero` is stolen into the dispatch `bne`'s slot).

## (b) The pass and the decision (read in the source; the dump facts are PROVEN, the target-side reading is inference)
cse. The dispatch index read `(set (reg:HI 88) (mem:HI (plus p 10)))` and case 3's `(mem:HI (plus p 10))` are the same
hash-table entry (canon_hash MEM ignores in_struct, cse.c:1942-1956; exp_equiv_p has no MEM case). cse1 reaches case 3 on
the path `127 -> 224 TAKEN -> 229 -> 232 fallthrough -> case 3` (`;; Processing block from 127 to 163`, plus the same from
38 and 107): label 229 has one use and a BARRIER before it, so `cse_end_of_basic_block` follows it (cse.c:8118, follow-jumps
branch), and jump1 already deleted case 3's own label by inverting `if (dsp==3) goto L3; goto end;` — case 3 is a
fall-through, no label stops the scan. On that path nothing invalidates memory, so the read becomes `reg 112`.
PROVEN on the dumps (`scratch/dumps_F`): the load is gone in `.cse` (cse1), not later.
The target's reload has to survive BOTH cse passes: a do-while(0) around the dispatch reads (NOTE_INSN_LOOP_END stops cse1's
scan, cse.c `! after_loop && NOTE_INSN_LOOP_END`) keeps the load through cse1 (`scratch/dumps_M`: 19 HI loads in `.loop`
vs 18), but cse2 (after_loop = 1, the note ignored; toplev.c:2926) deletes it again once loop.c has rewritten both
addresses to the same `$s0` giv. So whatever the original had is a memory invalidation (a varying-address store, a call,
or an asm clobber: note_mem_written cse.c:7539-7580, invalidate_memory :1701, calls :7240-7247) or a surviving label on
the dispatch path in BOTH passes. The final code has no store, call or branch target there.
The ORDER half: any store placed before the read to force the reload (`p[0x50] = 0;` first — the history's best, 5)
also forces `sb` before `lw`: sched1/2 cannot reorder a varying QI store and a varying SI load (true_dependence both
varying, sched.c:817), so the `sb` fills the lhu's load-delay slot and dbr gives the jal `move a0,zero` — 5, ORDER. The
target's order needs the READ first and the reload anyway, which only a pure invalidation gives.

## (c) The moves
None closes in plain C. Delivered body.c = the tree's text with its ONE lever re-marked per METHOD step 9 (the lever is
already the minimum: the dispatch-block `__asm__("" : : : "memory");`, which the S69 header's item 12 already placed at the
only zero-cost spot — after the lbu, outside every delay-slot thread). Lever count 1 -> 1. `--try` = 0.

## (d) GENERATOR PROPOSAL
When a COUNT residual is exactly one missing reload of a field a dominating block already loaded, first dump `.cse`
vs `.cse2`: if a do-while(0) keeps it through cse1 but cse2 deletes it, stop — no plain-C spelling exists, emit the
minimum-lever `"memory"` clobber at the dominating block's end and mark it; the sweep's 329 compiles (history) and this
agent's 20 hand spellings all sat in that class.

## (e) What did not work (bytes, all scored with --try)
- idx as `s32`/`u32`/`int` (19): expand always loads the u16 into a HI pseudo first (flag_force_mem at -O2), so every read
  is the same `(mem:HI (plus p 10))`.
- `switch (sv[*(u16 *)(p + 0xA)])` with case 2 re-reading (19); `switch (sv[idx = …])` (19); dsp as `u8` (19); switch on `st`
  (19); `((u16 *)p)[5]` / a `u16 *pid` temp for either read (19): cse canonicalises all of them.
- `default: break;` (19); `case 1: break;` (11 — adds a compare to the tree); a block-local `s32 m` in case 3 (19).
- Grouped `case 3: case 0: if (dsp != 0) {…}` (19) — the right idea (a label at case 3's head), but cse1 threads the
  `dsp == 0` jump past the inner test and DELETES the group label (label use count drops to `to_usage`, cse_basic_block's
  continuation, cse.c:8519-8520 `--LABEL_NUSES (to) == to_usage`), so the path reaches case 3 again. `if (dsp == 3)`: 47.
- do-while(0) around the index read / the dispatch reads / an empty one at case 3's head: 19 (cse2, see (b)).
- `p[0x50] = 0;` before the read (history best): 5, ORDER — see (b).
- A body-local `struct V54 { …; u16 id @0xA; …; u8 unk50 @0x50; … }` for the index reads and the store: 19.

## (f) Where the method fell short
The method has no row for "a reload that must survive TWO cse passes": the do-while(0) barrier (allowed-and-marked, rule 8)
looks like the fix and fixes cse1, and only the pass-by-pass load count (`.cse`, `.loop`, `.cse2`) shows cse2 undoing it.
A `tools/` helper that prints, per dump, the count of loads of one address would have settled it in one command.

## (g) Structs
Tested (above): a struct type changes nothing here. The mem hash ignores in_struct (cse.c:1948-1951), and the only
in_struct channel into cse — `invalidate_memory`'s `nonscalar && p->in_struct` (cse.c:1712-1714) — needs a store on the
path, which the target does not have. In sched, a struct field store vs a struct/array load are both varying addresses,
so the `sb`-after-`lw` order is not freed either (sched.c true_dependence). The lever is not a structs-phase item; it is
the one place this function's original source must have had a real barrier (or a construct the decompiler flattened).
The same voice record IS typed elsewhere in the TU — `Ent30D80` (func_80030D80: `unk0A` id, `unk40` callback, `unk44`,
`unk4E`, `unk50`, `unk51`) — so the structs phase can re-spell this body's `*(u16 *)(p + 0xA)`, `p[0x50]` etc. as fields
for readability at zero byte cost, lever unchanged.
