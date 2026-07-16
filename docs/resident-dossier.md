# The resident wall dossier — 14 remaining stubs (Phase-28 T5)

> **Status: the flag-plant did NOT reach 100%.** The resident is **21 -> 14 stubs**, **131/145 = 90.34%** byte-identical (was 124/145 = 85.52%). This records what is left and *why*, per function, from a 16-agent wave that drafted every non-jtbl stub against the whole-binary byte-gate (G3/P9 — the sole arbiter).

> **Read this before re-attacking any of them.** Each entry is the agent's own byte-grounded analysis: the levers tried, the exact gcc pass that blocked it, and why. That analysis cost ~2.4M tokens and is the durable asset (R30) — the 7 banks were the cheap part.

## The measured law (independently reconfirmed)

The agents self-reported **11 match_one MATCH**; the whole-binary gate banked **7 (64%)**. All 4 blocked MATCHes died on `conflicting types`, not codegen. **A match_one MATCH is a CANDIDATE, not a bank** (cookbook §52b). `gate_stage`'s deterministic recovery banked **0/5** on the plumbing class.

⚠️ **The wave ran on a broken instrument.** `match_one`'s `--work` defaulted to a *shared* `.run/match`, so parallel agents compiled into the same scratch — one agent found another's function in its own `t.c` and reported it. Fixed in T5 (private `<fn>.<pid>` dir). Verdicts below may carry that noise; **the gate results do not** (it is the arbiter).

## 1. BANKED (7) — byte-gated, R22 140/140

| fn | nins | the lever that closed it |
|---|---:|---|
| `func_800CEFD0` | 77 | goto-loop (label:/goto, not while(1)) suppresses loop.c invariant motion -> D_800D3488/D_800A651C stay inline GAS macros while the explicit `u8 *base = &(*(u8*)&D_800AF630)` local still lands in $s0; matched on 2nd iteration. |
| `func_800D0D7C` | 45 | Three stacked levers: `>=` condition polarity (fixed block order/branch sense), RC-12 $0-add opaque copies (`r=now+zr`,`h=arg0+zr` -> the $a2=$a3 and $t0=$a0 moves + the unfoldable `andi $a2,0xFF`), and an unused 8-byte local to restore the phantom `vars=8` frame -- the pin and the frame fight each  |
| `func_800D1B80` | 22 | Two levers: (1) `if (x!=0){body;return DsMix(p);} return 0;` NOT early-exit `if(x==0)return 0;` — fixes block layout/branch polarity (12->1 mismatch); (2) RC-12 $0-add opaque copy `p = arg0 + zr` (zr pinned $0) gives the sb its $a0 base — 4 plain `u8 *p=arg0;` spellings all lost to cse2 canon copy-p |
| `func_800D1E28` | 37 | Placing `result = 2` BETWEEN the call and its test (r = call(); result = 2; if (r != 0) goto test;) fixed both residuals at once: fills term2's delay slot from BEFORE the branch (killing dbr's steal+retarget L80->L84, restoring term3's nop) AND conflicts result with live $v0 -> $v1 falls out natural |
| `func_800D1FC8` | 62 | S13 mid-body param copy (sh=arg1 after the deltas) denied $a1 to the global ptr -> $a2/$a3, pin-free; then qty_compare density: hoist pair-2/3 global loads into t1/t2 (lw span 2 > lhu span 1) while pair-1 stays un-hoisted (its lw merges with block-local dx). 0 mismatches, reproduced. |
| `func_800D29F8` | 172 | Closed by volatile D_800B9A02 read as *(volatile u16*)&sym (kills CSE -> 6 reloads; INDIRECT_REF path force_regs the const addr -> la+lhu+preheader copy) + the real libgpu bitfield addPrim (store_bit_field masks value 0xFFFFFF before dest 0xFF000000 -> fixes const order/LUID tie-break + or operand o |
| `func_800D2D10` | 39 | §43 K&R s16 params (n, flag) got 38/39; the last delta was gcc CSE-merging `d = val>>28` into `idx` — §17 pin `register unsigned int d __asm__("$8")` kept the copy alive ($t0 + addu $v1,$t0,$zero) and shifted i/n-1/&table onto $t1-$t3 → MATCH. |

## 2. PLUMBING (5) — the loose-typing def-side wall, NOT codegen

These reached **match_one MATCH standalone** and failed *in-TU* on `conflicting types`: the resident TU already declares the symbol with an incompatible type. This is the Phase-16 loose-typing wall (the original engine uses one symbol at contradictory types across sites), and `gate_stage` recovered **0/5**. **The C is byte-correct; the TU cannot hold both spellings.**

| fn | nins | blocked on | agent's analysis |
|---|---:|---|---|
| `func_800CFE60` | 161 | `PLUMBING: src/resident/resident.c:977: conflicting types for` | MATCH 161 ins (verified 2x, isolated work dirs). Six levers: split the 2 call results (else a 7th $s reg); (u32) casts for srl not sra; RC-3 pins base=$s4/mode=$s3 (densities .162 vs .122 differ -> decl swap is a no-op, range-shaping unreachable); read the high half via its own s |
| `func_800D0214` | 43 | `PLUMBING: src/resident/resident.c:1031: conflicting types fo` | 43/43 ins, ins 2-15 byte-exact; stuck on S2 birthing boost — the single-set `lh` chunk temp sinks to its consumer (target keeps it at source position => original had reg_n_sets(chunk)>=2, unreachable in C since chunk dies at `*p=chunk`); that sink sets Lv 8-vs-5, losing the local |
| `func_800D1658` | 47 | `PLUMBING: src/resident/resident.c:1440: conflicting types fo` | §52a non-coalescing delay-slot copy wall CRACKED via hard->hard pin pair (v=$2 + ret=$16, both required — either alone lets cse/global-alloc kill the addu $s0,$v0,$zero copy → 44 ins) + single-return convergence (goto out) to keep the sll/sra tail from const-propagating + a $3-pi |
| `func_800D1984` | 22 | `PLUMBING: src/resident/resident.c:1677: conflicting types fo` | if/else merged-return layout closed 12->1; RC-12 $0-add opaque copy (register int zr __asm__("$0"); p = arg0 + zr) closed the last one — store base $a0 needs a 2nd pseudo cse's canon_reg can't fold back onto $s0. Notable: RC-12 firing on a 22-ins stub, not a giant. |
| `func_800D24A0` | 87 | `PLUMBING: src/resident/resident.c:2306: conflicting types fo` | Prior-art func_8013EE10 shape (u16* v=&D_80115112, base q=(char*)v-2, E4 struct-fold on D_80115168) gave 87/87 with a pure $a1/$a2 swap; RTL dump showed a REAL ~9x allocno-priority gap (counter 7refs/36 vs base 3refs/68), not a §47 plateau -> closed with a register pin q=$5 on th |

## 3. DIFF (4) — genuine gcc-2.7.2 codegen residuals

| fn | nins | close | class | the byte-grounded verdict |
|---|---:|---:|---|---|
| `func_800D2650` | 99 | 4 | regalloc-order | §37 /s-dep lever (MEM_IN_STRUCT_P on the D_800B9A02 load) closed 79->4 by restoring the CSE-killing store<->load dep (cascaded: reload + &D_800B9A02 hoist to $t4 + const-8 un-hoist); stuck at §47's allocation-vs-emission coupling on the two hoisted stack params — .lreg proves cy(78)=2refs/12len(equiv-doubled)=pri1666 loses $v1 to col(79)= |
| `func_800CFAD0` | 59 | 5 | sched | 52->35->5 via separate-globals (dodges cse use_related_value sym+3 rebasing) + chained r0=g0=b0=0x80 + §37 /s dep lattice (fixed all regs); stuck on S5: sched1 `blocking insn 114 for 1 cycles` — 0xE1000085 is a 2-insn unboosted const so no ALU filler wedges between two stores, tag lw loses the mem-unit hazard and lands idx 6 not 9; 100 st |
| `func_800D0E30` | 37 | 12 | regalloc-order | 37/37 ins, idx0-12 exact (u8 dummy[16] -> RTL prologue schedules addiu $sp into the delay slot; u32 hi/lo block `shorten` fixing the ior order; u16 a promoted-subreg gives the addu $a1,$a0,$zero copy). Stuck on ONE fact: allocno_order is b(pri 16000)->m(7500)->a(3750) so b takes $v1; target needs a->m->b (b last => LL>64, unreachable). In |
| `func_800D27DC` | 135 | 48 | regalloc-order | POLY_FT4+addPrim builder: structure byte-exact (135/135, prologue/preheader/cross-jump/delay slots all match) via macro-OT (not a named `e` local: addPrim double-evaluates ot -> two temps -> evicts `out` from $a1, 131->74), `s16 i` + `for(i=0;i<count;i++)` on the param directly (mints the single blez + two-pseudo counter + loop.c's `addu  |

## 4. jtbl — DEFERRED (5), not attempted

`func_800D0488` · `func_800D00E4` · `func_800D02D0` · `func_800D128C` · `func_800D06E8`

Jump-table dispatchers. They need the **per-function rodata-island carve** (the Phase-7 workflow; cookbook **§53**), which the resident has no split infrastructure for. Deliberately NOT forced: sweeping a jr function without its carve is *exactly* how the '≈0% families don't template' doctrine was manufactured (P28 T1 — the same mistake cost two phases of strategy). `func_800D00E4` already has a written dossier in-source at `src/resident/resident.c:861-867` (external jtbl `jtbl_80113ED8` HI16/LO16 vs gcc's own anonymous `.rodata` table).

## 5. What would actually finish the resident

1. **The 5 PLUMBING** are the highest-value target and are *not* a compiler problem — they need a TU-level type reconciliation the current tools do not do (`canon_sig_reconcile` / `reconcile_tu` / `cast_call_sites` all banked 0 here). A resident-scoped variant of the §41 def-side lever is the lead.
2. **The 5 jtbl** need the rodata-island carve ported to the resident (§53 + the Phase-7 workflow).
3. **The 4 DIFF** are the real tail: `func_800D2650` (close=4) and `func_800CFAD0` (close=5) are permuter-class seeds; `func_800D0E30` and `func_800D27DC` carry named intrinsic verdicts (read their notes — both name the exact allocno/priority mechanism).

## 6. Open instrument question (logged, does not block)

`func_800CEDFC` (the resident's vram base **+4** — the first function) and `func_800D33E0` are **defined in `resident.c` but absent from `sig_image`**, while `make audit-corpus` reports 0 PHANTOM + 0 TRUNCATED. Either the second oracle has a boundary blind spot or those are not image functions. `progress.py` counts them (145) while corpus and sig_image agree at **144** with an empty set difference both ways. -> T7 `audit-binaries`.

