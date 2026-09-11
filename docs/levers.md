# Levers — the register pins and compiler hints, what they cost, and what to do about them

> **What this is.** The living record of every compiler-forcing construct in this decompilation: how many there are, how they
> got in, how they come out, and — the part that outlives the project — whether a decomp should refuse them from its first
> bank or clean them up at the end. The numbers below are **generated** (R75); the argument is written from them.
>
> **Maintained:** updated at the close of every Phase-36 task (`tools/lever_progress.py --snapshot "<task>"`, which also
> re-renders the tables here). Sources: `tools/lever_census.py` for the counts, `.run/P36/delever/ledger.jsonl` for the
> campaign, `docs/lever-progress.tsv` for the series a chart is drawn from.
>
> **Audiences:** the post-100% chart and the project story · the wiki (a "Levers" page) · `decomp-architect/` (the day-one
> kit: the rule a new project should adopt at its first bank, §"What we would do from day one").

---

## 1. What a lever is

A **lever** is a construct that exists only to force the compiler's output — it says nothing about what the program does.
This project's C is full of them because bytes were the only thing being optimised:

| class | what it looks like | why a drafter reached for it |
|---|---|---|
| **A** register pin | `register s32 x __asm__("$16");` | name the register the allocator must use |
| **B1** barrier | `__asm__ __volatile__("" ::: "memory");` | stop the scheduler moving code across a point |
| **B2** launder | `__asm__("" : "=r"(x) : "0"(x));` | break a value's history so cse/combine cannot see through it |
| **B3** keep-alive | `__asm__("" : : "r"(x));` | keep a dead value live |
| **B4** hand-placed instruction | `__asm__("addu %0,%1,$zero" …)` | emit exactly this instruction |
| **B5** GTE op | `__asm__("lwc2 …")` behind a per-TU macro | *not a lever* — Sony's coprocessor idiom; consolidated, not removed |
| **C** volatile | `*(volatile s32 *)(p + 4)` | force a reload |
| **D** bare `register` | `register int i;` | a hint gcc 2.7.2 at `-O2` ignores |
| **E** asm-label alias | `extern u16 aD800B9A02 __asm__("D_800B9A02");` | a second typed view of one symbol |
| **F** builtin | `__builtin_memcpy(&a, &b, N)` | a struct assignment in disguise |
| **G** attribute | `__attribute__((packed))` | a layout the type layer should carry |

Classes **A and B are the ones this phase drives to zero.** C and D stay if the bytes need them (ordinary C, ledgered and
counted, not marked). E, F and G belong to the canonical type layer and are the **types phase's** work (R95).

---

## 2. The numbers

<!-- BEGIN GENERATED: lever_progress.py -->

### Milestones — the count, at each moment a census ran

| date | milestone | pins | asm | **class A+B sites** | bodies | distinct | GTE levers | per-TU asm macros | C | D | E | F | G | HEAD |
|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|
| 2026-09-09 | T6 r1 (rung R's first class) | 20512 | 13445 | **33957** | 12578 | 1758 | 462 | 314 | 1722 | 50 | 7428 | 445 | 76 | `1761a3125` |
| 2026-09-09 | T6 d1 (rung D's four exemplars) | 20508 | 13445 | **33953** | 12574 | 1758 | 462 | 314 | 1722 | 50 | 7428 | 445 | 76 | `8fac96651` |
| 2026-09-09 | T6 p1 (four classes propagated) | 19982 | 13445 | **33427** | 12048 | 1755 | 462 | 314 | 1722 | 50 | 7428 | 445 | 76 | `a2da99b13` |
| 2026-09-09 | S101 rung G g1 (the guided search's first run: 1 of 16 exemplars, 132 bodies) | 19982 | 13313 | **33295** | 11916 | 1754 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `623e55340` |
| 2026-09-09 | S101 rung G g2 (wider beam + R10/R12/R13/R8-cse: 1 of 16, 132 bodies) | 19718 | 13313 | **33031** | 11784 | 1753 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `584031c71` |
| 2026-09-09 | S101 rung G g3 (the next 64 classes: 13 of 64, 1,516 bodies) | 18442 | 12583 | **31025** | 10268 | 1740 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `5ae0b5ceb` |
| 2026-09-09 | S101 rung G g4s (the 13 explained names, 38 classes: 3 of 38, 133 bodies) | 18309 | 12583 | **30892** | 10135 | 1737 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `068781ae0` |
| 2026-09-09 | S101 rung G g5 (the head re-drawn wide: 5 of 70, 62 bodies) | 18261 | 12545 | **30806** | 10073 | 1732 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `1ec67f667` |
| 2026-09-09 | S101 rung G g6 + g6b (the tail: 47 + 63 of 400 small classes, 93 + 186 + 47 bodies) | 17954 | 12404 | **30358** | 9747 | 1624 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `2f3ce92a1` |
| 2026-09-10 | S102 T7 a1 — func_80156044 closed by an agent (merge-point expression sunk into the if/else arms, both $2/$3 pins gone); 130 bodies banked (1 + 129 propagated) | 17694 | 12404 | **30098** | 9617 | 1623 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `5a8bd1021` |
| 2026-09-10 | S102 T7 s1 — the R15 sweep of the head: 6 exemplars closed by the sink alone (267 bodies), no drafting tokens | 17427 | 12270 | **29697** | 9350 | 1617 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `861dd0651` |
| 2026-09-10 | S102 T7 a2 — func_80168828: the constant-holder pin deleted and one adjacent swap closes it (125 bodies, 1 of 2 pins off; the $4 pin is forced by the header's (void) declaration) | 17302 | 12270 | **29572** | 9350 | 1617 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `c00ffe5d4` |
| 2026-09-10 | S102 T7 s3 (partial, the run crashed in propagate) — the constant-holder draw: 10 bodies closed | 17266 | 12267 | **29533** | 9326 | 1594 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `975850ff8` |
| 2026-09-10 | S102 T7 s3b — the constant-holder draw re-run after the propagate fix: 1 of 80, 6 bodies; 59 of 80 hit the compile budget | 17260 | 12267 | **29527** | 9320 | 1593 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `5603a114c` |
| 2026-09-10 | S102 T7 s5 — the first broad TAIL sweep with R15/R16/R17/R18: 285 of 800 bodies closed lever-free, no drafting tokens | 17029 | 12175 | **29204** | 9035 | 1308 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `449acd8cb` |
| 2026-09-10 | S102 T7 s6 — the last never-attempted exemplars: 25 of 337; the fresh pool is now empty | 16996 | 12152 | **29148** | 9010 | 1283 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `67e91ad4d` |
| 2026-09-10 | S102 T7 s7 (stopped early to restore agent cadence) — 5 of 207 judged at the wider width | 16989 | 12151 | **29140** | 9005 | 1280 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `724c68859` |
| 2026-09-10 | S102 T7 a7 — func_801287B8: a truncated local extern was faking a  pin; the missing call argument restored through a function-pointer cast (127 bodies) | 16862 | 12151 | **29013** | 8878 | 1279 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `bb0e95c7c` |
| 2026-09-10 | S102 T7 a4 — func_8016C49C: one do-while on the function's LAST statement doubles a loop-note reference weight and flips allocno_compare (126 bodies) | 16736 | 12151 | **28887** | 8752 | 1278 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `9f5b22176` |
| 2026-09-10 | S102 T7 burst — a8/a12/a18/a19 banked (132+118+119+134 bodies): the call-arity class twice, a MEM_IN_STRUCT_P alias flip, and a sequence-point split | 15965 | 12019 | **27984** | 8249 | 1275 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `fb6c857f7` |
| 2026-09-10 | S102 T7 burst — a5/a9/a11/a16/a25 banked; the MISSING CALL ARGUMENT class confirmed six times independently (m2c dropped arguments at unprototyped and indirect call sites) | 15324 | 11390 | **26714** | 7612 | 1271 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `c6b380fcd` |
| 2026-09-10 | S102 T7 burst — a22 banked (126); a14 REFUSED as an invented zero term; a6/a10/a15 read without closing | 15198 | 11264 | **26462** | 7486 | 1270 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `374c8a0e9` |
| 2026-09-10 | S102 T7 s8 — the first R19 sweep: 3 of 55 classes closed by restoring a dropped call argument, 2 compiles each | 15193 | 11263 | **26456** | 7483 | 1267 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `f3de70fce` |
| 2026-09-10 | S102 — 16,759 lying call declarations repaired free (3,439 units, R22 218/218); levers unchanged, truth improved | 15193 | 11263 | **26456** | 7483 | 1267 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `51028a78d` |
| 2026-09-10 | S102 T7 b1 — func_801651B8: the hand-walked pointer folded back into the index, one induction variable instead of two (127 bodies) | 15066 | 11136 | **26202** | 7356 | 1266 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `8c0e7c549` |
| 2026-09-10 | S102 T7 b3 — func_8016CBC0: two counter chains narrowed TOGETHER (128 bodies); single declarations could never reach it | 14938 | 11136 | **26074** | 7228 | 1265 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `acba5c59d` |
| 2026-09-10 | S102 T7 wave b — b2/b5/b5s/b6 banked plus R19 and R20's own closes (766 bodies): a chained assignment, a symbol alias defeating cross-jump, and the store hoisted above its copy | 14541 | 10374 | **24915** | 6577 | 1259 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `9d78fc408` |
| 2026-09-10 | S102 T7 b7 — func_80166690: four accumulators retyped short in ONE edit, the truncation temps deleted, the colour temp typed to its destination field (126 bodies) | 14415 | 10374 | **24789** | 6451 | 1258 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `17d192d24` |
| 2026-09-10 | S102 T7 b8 — func_80135888: a guarded do-while defeating cross-jump, a duplicated block replaced by goto to shed one loop-weighted reference, and a two-arm temp inlined (134 bodies, the largest class) | 13879 | 10240 | **24119** | 6317 | 1257 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `0d92d1029` |
| 2026-09-10 | S102 wave b close — 8 agent closes banked (b1/b2/b3/b5/b5s/b6/b7/b8), b4/b9 read without closing; R19/R20/R21 added; fleet 218/218 | 13879 | 10240 | **24119** | 6317 | 1257 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `f96af3e48` |
| 2026-09-10 | S103 c2: func_8013D8FC closed by agent c2 (the walked-pointer merge, now generator R22), 131 bodies | 13748 | 10240 | **23988** | 6186 | 1256 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `82da34b39` |
| 2026-09-10 | S103 wave c: c4/c6/c1/c7/c3/c5/c8 closed (two new generators R22/R23) + func_8017EEC0's parameter; 8 classes, ~1,000 bodies | 11271 | 8935 | **20206** | 5277 | 1249 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `205331765` |
| 2026-09-10 | S103: c12 twins func_80148E54/D44 + c10 func_80135A4C (395 bodies) | 10873 | 8403 | **19276** | 4879 | 1246 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `2e61220bd` |
| 2026-09-10 | S103: c11 func_80175AB8 (124 bodies) | 10623 | 8153 | **18776** | 4754 | 1245 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `e6a8f3505` |
| 2026-09-10 | S103: c14 func_801670E4 + c16 func_8013D178 (261 bodies); R23 widened | 10227 | 7488 | **17715** | 4491 | 1243 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `625251626` |
| 2026-09-10 | S103: delever_regen R22+R23 over the whole residue — 17 classes / 22 bodies with no agent (header-TU scoring fixed) | 10204 | 7488 | **17692** | 4469 | 1226 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `a06070572` |
| 2026-09-10 | S103: c18 func_80176734 (128 bodies) | 9172 | 7101 | **16273** | 4340 | 1225 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `164825b5d` |
| 2026-09-10 | S103: c20 re-draw func_8013DD68 (128 bodies) | 8914 | 7101 | **16015** | 4211 | 1224 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `9f2b6b24a` |
| 2026-09-10 | S103: generator R24 (word-read addPrim) + its regen pass (2 classes, one a 140-object header) | 8912 | 7101 | **16013** | 4209 | 1222 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `5eb46b267` |
| 2026-09-10 | S103: c15 func_80135EB0 (128 bodies; a do-while on the a4 precedent) | 8654 | 6585 | **15239** | 4080 | 1221 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `a620e1880` |
| 2026-09-10 | S103: re-draws c24 func_8012956C + c23 func_80133784 (252 bodies) | 7765 | 6077 | **13842** | 3826 | 1219 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `ae87bf75a` |
| 2026-09-10 | S103: re-draws c25 func_80166F58 + c26 func_80133CD4 (254 bodies); R25 regen 3; propagate's stale-hash fix | 7512 | 5571 | **13083** | 3567 | 1215 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `96820256c` |
| 2026-09-10 | S103: re-draw c21 func_801397B0 (125 bodies; do-while ref-weight) | 7386 | 5571 | **12957** | 3441 | 1214 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `44f7f8ddb` |
| 2026-09-10 | S103: re-draw c30 func_8017B614 (125 bodies) | 7260 | 5319 | **12579** | 3315 | 1213 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `5ddbc3a7f` |
| 2026-09-10 | S103: c33 func_80169058 + func_80168D94 (12 bodies) | 7236 | 5295 | **12531** | 3303 | 1211 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `a2a1fc186` |
| 2026-09-10 | S103: c36 + c35 (four ov_SC07_006/ov_SC06_010 classes, 39 bodies); R19 reads cast arity | 7186 | 5295 | **12481** | 3260 | 1207 | 462 | 314 | 1590 | 50 | 7680 | 445 | 76 | `dd5e44c24` |
| 2026-09-10 | S103: extern-variant re-propagation (97), R19 cast regen (8 classes), c39 + c41 + c34 + c32 closes | 6926 | 5107 | **12033** | 3090 | 1164 | 462 | 314 | 1590 | 50 | 7688 | 445 | 76 | `7d5964b27` |
| 2026-09-10 | S103: c38 + c40 (four tier classes, 30 bodies) | 6910 | 5093 | **12003** | 3060 | 1160 | 462 | 314 | 1590 | 50 | 7688 | 445 | 76 | `321b540e7` |
| 2026-09-10 | S103: c42 func_80186A8C + func_80182058 (10 bodies) | 6900 | 5088 | **11988** | 3050 | 1158 | 462 | 314 | 1590 | 50 | 7688 | 445 | 76 | `2a4f28f83` |
| 2026-09-10 | S103: c46 minimum-lever (133 bodies, 23 -> 1), c43 + cross-address port (14+12), c44, c45 (+R26), c37 + 43 cross-address copies, port-scan | 5893 | 4048 | **9941** | 2946 | 1144 | 456 | 314 | 1590 | 50 | 7713 | 445 | 76 | `8bc06a2cb` |
| 2026-09-10 | S103: c50 func_80136824 zero levers (130); c49 func_8013F350 2 levers (133) | 5500 | 3528 | **9028** | 2816 | 1144 | 456 | 314 | 1590 | 50 | 7713 | 445 | 76 | `aada3bdc2` |
| 2026-09-10 | S103: c47 func_8013D9B0 2 GTE asm (133), c48 func_80140958 2 levers (133), c52 four R26 closes | 3069 | 2323 | **5392** | 2662 | 1134 | 456 | 314 | 1590 | 50 | 7733 | 445 | 76 | `433aa0701` |
| 2026-09-10 | S103: c56 ports func_8013D9B0 to ov_MAIN_012's class (7); c54 func_8017B238 (8) | 3061 | 2315 | **5376** | 2654 | 1131 | 456 | 314 | 1590 | 50 | 7733 | 445 | 76 | `c02fc7cd5` |
| 2026-09-10 | S103 end: R26 regen 28 classes (71 bodies) + c55/c53 five classes | 2932 | 2299 | **5231** | 2569 | 1098 | 456 | 314 | 1590 | 50 | 7782 | 445 | 76 | `0ef49b515` |
| 2026-09-10 | S103 end: c51 func_8012E364 2 levers (134); scrub of 46 orphan markers | 2798 | 2299 | **5097** | 2569 | 1097 | 456 | 314 | 1590 | 50 | 7782 | 445 | 76 | `94520756e` |
| 2026-09-10 | S104 T7: free sweep (5 classes) + agents d1–d9 (all 0; 8 with zero levers, d4 one marked do-while) | 2730 | 2233 | **4963** | 2498 | 1077 | 456 | 314 | 1590 | 50 | 7782 | 445 | 76 | `910875139` |
| 2026-09-10 | S104 T7: sweeps (all-families, R27) + agents d11–d19 all at 0 with zero levers | 2578 | 2175 | **4753** | 2383 | 1019 | 456 | 314 | 1590 | 50 | 7780 | 445 | 76 | `91ae94a64` |
| 2026-09-10 | S104 T7: d17 + R28–R33 pass (4) + R27 remainder | 2565 | 2167 | **4732** | 2373 | 1011 | 456 | 314 | 1590 | 50 | 7780 | 445 | 76 | `13069c142` |
| 2026-09-10 | S104 T7: agents d21–d27 (d29 parked) + the shared header | 2515 | 2146 | **4661** | 2336 | 996 | 456 | 314 | 1590 | 50 | 7780 | 445 | 76 | `1d42fff3c` |
| 2026-09-10 | S104 T7: d30–d33 + the R23/R34–R36 pass (16) | 2478 | 2125 | **4603** | 2301 | 973 | 456 | 314 | 1590 | 50 | 7780 | 445 | 76 | `93e2a9170` |
| 2026-09-11 | S104 T7: TU batches e1–e7 + regen passes | 2394 | 2079 | **4473** | 2210 | 895 | 456 | 314 | 1590 | 50 | 7787 | 445 | 76 | `4de2fb06a` |
| 2026-09-11 | S104 T7: TU batches e5–e13 (ov_SC02_017 TU at 0) | 2370 | 2066 | **4436** | 2187 | 873 | 451 | 314 | 1589 | 50 | 7788 | 445 | 76 | `860ed9153` |
| 2026-09-11 | S104 T7: TU batches e14–e25 | 2317 | 2023 | **4340** | 2118 | 806 | 451 | 314 | 1589 | 50 | 7788 | 445 | 76 | `b5b701750` |
| 2026-09-11 | S104 T7: TU batches e18–e29 + R39b/R42 passes | 2279 | 1993 | **4272** | 2090 | 780 | 451 | 314 | 1589 | 50 | 7790 | 445 | 76 | `edd427861` |
| 2026-09-11 | S104 T7: e30–e34 batches | 2257 | 1970 | **4227** | 2068 | 758 | 451 | 314 | 1589 | 50 | 7792 | 445 | 76 | `a4f043bc3` |
| 2026-09-11 | S104 T7 close: e35–e38 resumed after the usage limit | 2227 | 1925 | **4152** | 2033 | 727 | 451 | 314 | 1589 | 50 | 7800 | 445 | 76 | `765704ca5` |
| 2026-09-11 | S105 f2 (4) + R44/R22 regen (3) | 2217 | 1915 | **4132** | 2027 | 721 | 451 | 314 | 1589 | 50 | 7800 | 445 | 76 | `0076a9d2e` |
| 2026-09-11 | S105 f1 (4) | 2212 | 1913 | **4125** | 2025 | 719 | 451 | 314 | 1589 | 50 | 7800 | 445 | 76 | `389373f6d` |
| 2026-09-11 | S105 f3 (4 + 1 proven) | 2203 | 1908 | **4111** | 2021 | 715 | 451 | 314 | 1589 | 50 | 7800 | 445 | 76 | `cadb6cacc` |
| 2026-09-11 | S105 f4 (5) + f5 (7) | 2188 | 1889 | **4077** | 2009 | 703 | 451 | 314 | 1589 | 50 | 7800 | 445 | 76 | `4a503fce1` |
| 2026-09-11 | S105 f7 (6) + R22 regen (1) | 2179 | 1886 | **4065** | 2003 | 697 | 451 | 314 | 1589 | 50 | 7800 | 445 | 76 | `d85a4e387` |

### The campaign — every batch, from the ledger (derived on every render)

| batch | date | rungs | bodies first judged | sites removed | rewritten | sites closed later | bodies made lever-free |
|---|---|---|---:|---:|---:|---:|---:|
| `t3_tus1` | 2026-09-09 | A,B | 176 | 211 | 4 | 0 | 0 |
| `t3_scrub` | 2026-09-09 | scrub | 1 | 0 | 0 | 0 | 0 |
| `tus1` | 2026-09-09 | A,B,replay | 1,392 | 3,241 | 101 | 0 | 0 |
| `tus2` | 2026-09-09 | A,B,replay | 2,752 | 3,501 | 4 | 0 | 0 |
| `tus3` | 2026-09-09 | A,B,replay | 2,513 | 2,910 | 15 | 0 | 0 |
| `tus4` | 2026-09-09 | A,B,replay | 2,224 | 2,012 | 131 | 0 | 0 |
| `tus5` | 2026-09-09 | A,B,replay | 1,225 | 1,811 | 10 | 0 | 0 |
| `tus6` | 2026-09-09 | A,B,replay | 1,409 | 1,667 | 0 | 0 | 0 |
| `tus7` | 2026-09-09 | A,B,replay | 1,407 | 1,853 | 2 | 0 | 0 |
| `tus8` | 2026-09-09 | A,B,replay | 602 | 432 | 0 | 0 | 0 |
| `tus9` | 2026-09-09 | A,B,replay | 1,901 | 2,234 | 10 | 0 | 0 |
| `tus10` | 2026-09-09 | A,B,replay | 362 | 408 | 3 | 0 | 0 |
| `headers1` | 2026-09-09 | A,B,replay | 200 | 301 | 1 | 0 | 0 |
| `headers2` | 2026-09-09 | A,B,replay | 171 | 197 | 2 | 0 | 0 |
| `gte1` | 2026-09-09 | gte | 399 | 0 | 0 | 0 | 0 |
| `gte2` | 2026-09-09 | gte | 244 | 0 | 0 | 0 | 0 |
| `sweep1` | 2026-09-09 | sweep | 4 | 0 | 0 | 0 | 0 |
| `sweep2` | 2026-09-09 | sweep | 3 | 0 | 0 | 0 | 0 |
| `sweep3` | 2026-09-09 | sweep | 134 | 0 | 0 | 0 | 0 |
| `r1` | 2026-09-09 | R | 0 | 0 | 0 | 134 | 134 |
| `d1` | 2026-09-09 | D | 0 | 0 | 0 | 4 | 4 |
| `p1` | 2026-09-09 | D | 0 | 0 | 0 | 394 | 394 |
| `p1b` | 2026-09-09 | D | 0 | 0 | 0 | 132 | 132 |
| `g1` | 2026-09-09 | G | 0 | 0 | 0 | 2 | 1 |
| `g1p` | 2026-09-09 | G | 0 | 0 | 0 | 262 | 131 |
| `g2` | 2026-09-09 | G | 0 | 0 | 0 | 2 | 1 |
| `g2p` | 2026-09-09 | G | 0 | 0 | 0 | 262 | 131 |
| `g3` | 2026-09-09 | G | 0 | 0 | 0 | 17 | 13 |
| `g3p` | 2026-09-09 | G | 0 | 0 | 0 | 1,989 | 1,503 |
| `g4s` | 2026-09-09 | G | 0 | 0 | 0 | 3 | 3 |
| `g4sp` | 2026-09-09 | G | 0 | 0 | 0 | 130 | 130 |
| `g5` | 2026-09-09 | G | 0 | 0 | 0 | 7 | 5 |
| `g5p` | 2026-09-09 | G | 0 | 0 | 0 | 79 | 57 |
| `g6` | 2026-09-09 | G | 0 | 0 | 0 | 66 | 47 |
| `g6b` | 2026-09-09 | G | 0 | 0 | 0 | 72 | 63 |
| `g6bp` | 2026-09-09 | G | 0 | 0 | 0 | 39 | 30 |
| `g6p` | 2026-09-09 | G | 0 | 0 | 0 | 275 | 186 |
| `a1` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `a1p` | 2026-09-10 | E | 0 | 0 | 0 | 258 | 129 |
| `s1` | 2026-09-10 | G | 0 | 0 | 0 | 10 | 6 |
| `s1p` | 2026-09-10 | G | 0 | 0 | 0 | 391 | 261 |
| `a2` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 0 |
| `a2p` | 2026-09-10 | E | 0 | 0 | 0 | 124 | 0 |
| `s3` | 2026-09-10 | G | 0 | 0 | 0 | 39 | 24 |
| `s3b` | 2026-09-10 | G | 0 | 0 | 0 | 1 | 1 |
| `s3bp` | 2026-09-10 | G | 0 | 0 | 0 | 5 | 5 |
| `s4` | 2026-09-10 | G | 0 | 0 | 0 | 18 | 3 |
| `s5` | 2026-09-10 | G | 0 | 0 | 0 | 325 | 285 |
| `s6` | 2026-09-10 | G | 0 | 0 | 0 | 56 | 25 |
| `s7` | 2026-09-10 | G | 0 | 0 | 0 | 8 | 5 |
| `a7` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `a7p` | 2026-09-10 | E | 0 | 0 | 0 | 126 | 126 |
| `a4` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `a4p` | 2026-09-10 | E | 0 | 0 | 0 | 125 | 125 |
| `a8` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `a8p` | 2026-09-10 | E | 0 | 0 | 0 | 262 | 131 |
| `a12` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `a19` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 1 |
| `a18` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `a12p` | 2026-09-10 | E | 0 | 0 | 0 | 117 | 117 |
| `a19p` | 2026-09-10 | E | 0 | 0 | 0 | 399 | 133 |
| `a18p` | 2026-09-10 | E | 0 | 0 | 0 | 124 | 124 |
| `a5` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 1 |
| `a5p` | 2026-09-10 | E | 0 | 0 | 0 | 500 | 125 |
| `a9` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `a9p` | 2026-09-10 | E | 0 | 0 | 0 | 256 | 128 |
| `a25` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `a16` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `a25p` | 2026-09-10 | E | 0 | 0 | 0 | 250 | 125 |
| `a16p` | 2026-09-10 | E | 0 | 0 | 0 | 130 | 130 |
| `a11` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `a11p` | 2026-09-10 | E | 0 | 0 | 0 | 124 | 124 |
| `a22` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `a22p` | 2026-09-10 | E | 0 | 0 | 0 | 250 | 125 |
| `s8` | 2026-09-10 | G | 0 | 0 | 0 | 6 | 3 |
| `b1` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `b1p` | 2026-09-10 | E | 0 | 0 | 0 | 252 | 126 |
| `b3` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `b3p` | 2026-09-10 | E | 0 | 0 | 0 | 127 | 127 |
| `s10` | 2026-09-10 | G | 0 | 0 | 0 | 2 | 2 |
| `b2` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 1 |
| `b5` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `b6` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 1 |
| `b5s` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `b2p` | 2026-09-10 | E | 0 | 0 | 0 | 378 | 126 |
| `b5p` | 2026-09-10 | E | 0 | 0 | 0 | 125 | 125 |
| `b6p` | 2026-09-10 | E | 0 | 0 | 0 | 378 | 126 |
| `s10p` | 2026-09-10 | G | 0 | 0 | 0 | 128 | 128 |
| `s10q` | 2026-09-10 | G | 0 | 0 | 0 | 15 | 15 |
| `b5sp` | 2026-09-10 | E | 0 | 0 | 0 | 125 | 125 |
| `b7` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `b7p` | 2026-09-10 | E | 0 | 0 | 0 | 125 | 125 |
| `b8` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 1 |
| `b8p` | 2026-09-10 | E | 0 | 0 | 0 | 665 | 133 |
| `c2` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c2p` | 2026-09-10 | E | 0 | 0 | 0 | 130 | 130 |
| `c4` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 1 |
| `c4p` | 2026-09-10 | E | 0 | 0 | 0 | 532 | 133 |
| `c6` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 1 |
| `c6p` | 2026-09-10 | E | 0 | 0 | 0 | 516 | 129 |
| `c1` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 1 |
| `c1p` | 2026-09-10 | E | 0 | 0 | 0 | 625 | 125 |
| `c7` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 1 |
| `c7p` | 2026-09-10 | E | 0 | 0 | 0 | 665 | 133 |
| `c3` | 2026-09-10 | E | 0 | 0 | 0 | 6 | 1 |
| `c3p` | 2026-09-10 | E | 0 | 0 | 0 | 786 | 131 |
| `c5` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c5p` | 2026-09-10 | E | 0 | 0 | 0 | 125 | 125 |
| `c8` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 1 |
| `c8p` | 2026-09-10 | E | 0 | 0 | 0 | 504 | 126 |
| `c12` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 2 |
| `c12p` | 2026-09-10 | E | 0 | 0 | 0 | 524 | 262 |
| `c10` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 1 |
| `c10p` | 2026-09-10 | E | 0 | 0 | 0 | 399 | 133 |
| `c11` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 1 |
| `c11p` | 2026-09-10 | E | 0 | 0 | 0 | 620 | 124 |
| `c14` | 2026-09-10 | E | 0 | 0 | 0 | 7 | 1 |
| `c14p` | 2026-09-10 | E | 0 | 0 | 0 | 924 | 132 |
| `c16` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c16p` | 2026-09-10 | E | 0 | 0 | 0 | 129 | 129 |
| `s103_r22r23` | 2026-09-10 | E | 0 | 0 | 0 | 15 | 14 |
| `s103_r22r23p` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `s103_r22r23_hdr` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 3 |
| `s103_r22r23_hdrp` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c18` | 2026-09-10 | E | 0 | 0 | 0 | 11 | 1 |
| `c18p` | 2026-09-10 | E | 0 | 0 | 0 | 1,408 | 128 |
| `c20` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `c20p` | 2026-09-10 | E | 0 | 0 | 0 | 256 | 128 |
| `s103_r24` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 2 |
| `c15` | 2026-09-10 | E | 0 | 0 | 0 | 6 | 1 |
| `c15p` | 2026-09-10 | E | 0 | 0 | 0 | 768 | 128 |
| `c24` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 1 |
| `c24p` | 2026-09-10 | E | 0 | 0 | 0 | 504 | 126 |
| `c23` | 2026-09-10 | E | 0 | 0 | 0 | 7 | 1 |
| `c23p` | 2026-09-10 | E | 0 | 0 | 0 | 882 | 126 |
| `c25` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 1 |
| `c25p` | 2026-09-10 | E | 0 | 0 | 0 | 617 | 124 |
| `c26` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c26p` | 2026-09-10 | E | 0 | 0 | 0 | 130 | 130 |
| `s103_r19r25` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 3 |
| `s103_r19r25p` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c21` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c21p` | 2026-09-10 | E | 0 | 0 | 0 | 125 | 125 |
| `c30` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 1 |
| `c30p` | 2026-09-10 | E | 0 | 0 | 0 | 375 | 125 |
| `c33` | 2026-09-10 | E | 0 | 0 | 0 | 8 | 2 |
| `c33p` | 2026-09-10 | E | 0 | 0 | 0 | 40 | 10 |
| `c36` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 2 |
| `c36p` | 2026-09-10 | E | 0 | 0 | 0 | 18 | 12 |
| `c35` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 2 |
| `c35p` | 2026-09-10 | E | 0 | 0 | 0 | 27 | 27 |
| `c34` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 2 |
| `c34p` | 2026-09-10 | E | 0 | 0 | 0 | 49 | 23 |
| `c32` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c32p` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `c39` | 2026-09-10 | E | 0 | 0 | 0 | 11 | 2 |
| `c39p` | 2026-09-10 | E | 0 | 0 | 0 | 66 | 12 |
| `s103_extern_variants` | 2026-09-10 | D,E,G | 0 | 0 | 0 | 307 | 112 |
| `s103_r19cast` | 2026-09-10 | E | 0 | 0 | 0 | 10 | 6 |
| `s103_r19castp` | 2026-09-10 | E | 0 | 0 | 0 | 8 | 4 |
| `c41` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `c41p` | 2026-09-10 | E | 0 | 0 | 0 | 27 | 17 |
| `c38` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 2 |
| `c38p` | 2026-09-10 | E | 0 | 0 | 0 | 14 | 14 |
| `c40` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 2 |
| `c40p` | 2026-09-10 | E | 0 | 0 | 0 | 12 | 12 |
| `c42` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 2 |
| `c42p` | 2026-09-10 | E | 0 | 0 | 0 | 12 | 8 |
| `c43` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 2 |
| `c43x` | 2026-09-10 | E | 0 | 0 | 0 | 24 | 12 |
| `c46` | 2026-09-10 | E | 0 | 0 | 0 | 14 | 0 |
| `c46p` | 2026-09-10 | E | 0 | 0 | 0 | 1,848 | 0 |
| `s103_port` | 2026-09-10 | E | 0 | 0 | 0 | 11 | 7 |
| `c44` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 2 |
| `c44p` | 2026-09-10 | E | 0 | 0 | 0 | 37 | 14 |
| `c45` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 2 |
| `c45p` | 2026-09-10 | E | 0 | 0 | 0 | 51 | 23 |
| `s103_port2` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 2 |
| `c37` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `c37x` | 2026-09-10 | E | 0 | 0 | 0 | 43 | 43 |
| `c50` | 2026-09-10 | E | 0 | 0 | 0 | 6 | 1 |
| `c50p` | 2026-09-10 | E | 0 | 0 | 0 | 774 | 129 |
| `c49` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 0 |
| `c49p` | 2026-09-10 | E | 0 | 0 | 0 | 132 | 0 |
| `c47` | 2026-09-10 | E | 0 | 0 | 0 | 25 | 1 |
| `c47p` | 2026-09-10 | E | 0 | 0 | 0 | 3,325 | 133 |
| `c52` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `c52p` | 2026-09-10 | E | 0 | 0 | 0 | 16 | 16 |
| `c48` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 0 |
| `c48p` | 2026-09-10 | E | 0 | 0 | 0 | 264 | 0 |
| `c54` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `c54p` | 2026-09-10 | E | 0 | 0 | 0 | 14 | 7 |
| `s103_r26b` | 2026-09-10 | E | 0 | 0 | 0 | 27 | 27 |
| `s103_r26bp` | 2026-09-10 | E | 0 | 0 | 0 | 22 | 22 |
| `c55` | 2026-09-10 | E | 0 | 0 | 0 | 6 | 2 |
| `c55p` | 2026-09-10 | E | 0 | 0 | 0 | 24 | 8 |
| `c53` | 2026-09-10 | E | 0 | 0 | 0 | 8 | 3 |
| `c53p` | 2026-09-10 | E | 0 | 0 | 0 | 58 | 23 |
| `s103_port4` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 2 |
| `s103_scrub` | 2026-09-10 | scrub | 3 | 0 | 0 | 0 | 0 |
| `c51` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 0 |
| `c51p` | 2026-09-10 | E | 0 | 0 | 0 | 133 | 0 |
| `s104_all_part1` | 2026-09-10 | E | 0 | 0 | 0 | 6 | 5 |
| `s104_all_part1p` | 2026-09-10 | E | 0 | 0 | 0 | 14 | 12 |
| `s104_d2` | 2026-09-10 | E | 0 | 0 | 0 | 40 | 8 |
| `s104_d1` | 2026-09-10 | E | 0 | 0 | 0 | 10 | 10 |
| `s104_d3` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_d5` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_d6` | 2026-09-10 | E | 0 | 0 | 0 | 24 | 8 |
| `s104_d8` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_d9` | 2026-09-10 | E | 0 | 0 | 0 | 6 | 6 |
| `s104_d7` | 2026-09-10 | E | 0 | 0 | 0 | 18 | 6 |
| `s104_d4` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_d10` | 2026-09-10 | E | 0 | 0 | 0 | 35 | 7 |
| `s104_part2` | 2026-09-10 | E | 0 | 0 | 0 | 50 | 38 |
| `s104_part2p` | 2026-09-10 | E | 0 | 0 | 0 | 56 | 38 |
| `s104_d11` | 2026-09-10 | E | 0 | 0 | 0 | 8 | 4 |
| `s104_d12` | 2026-09-10 | E | 0 | 0 | 0 | 20 | 4 |
| `s104_d13` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 5 |
| `s104_d15` | 2026-09-10 | E | 0 | 0 | 0 | 12 | 4 |
| `s104_d18` | 2026-09-10 | E | 0 | 0 | 0 | 9 | 9 |
| `s104_d14` | 2026-09-10 | E | 0 | 0 | 0 | 9 | 3 |
| `s104_d19` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 3 |
| `s104_d16` | 2026-09-10 | E | 0 | 0 | 0 | 10 | 5 |
| `s104_d17` | 2026-09-10 | E | 0 | 0 | 0 | 8 | 4 |
| `s104_new5` | 2026-09-10 | E | 0 | 0 | 0 | 5 | 4 |
| `s104_r27` | 2026-09-10 | E | 0 | 0 | 0 | 10 | 3 |
| `s104_d22` | 2026-09-10 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_d24` | 2026-09-10 | E | 0 | 0 | 0 | 16 | 4 |
| `s104_d23` | 2026-09-10 | E | 0 | 0 | 0 | 21 | 7 |
| `s104_d25` | 2026-09-10 | E | 0 | 0 | 0 | 3 | 3 |
| `s104_d26` | 2026-09-10 | E | 0 | 0 | 0 | 7 | 7 |
| `s104_d21` | 2026-09-10 | E | 0 | 0 | 0 | 14 | 7 |
| `s104_d27` | 2026-09-10 | E | 0 | 0 | 0 | 6 | 5 |
| `s104_d30` | 2026-09-10 | E | 0 | 0 | 0 | 7 | 7 |
| `s104_d33` | 2026-09-10 | E | 0 | 0 | 0 | 12 | 4 |
| `s104_d31` | 2026-09-10 | E | 0 | 0 | 0 | 12 | 4 |
| `s104_d32` | 2026-09-10 | E | 0 | 0 | 0 | 9 | 3 |
| `s104_new4` | 2026-09-10 | E | 0 | 0 | 0 | 17 | 16 |
| `s104_new4p` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 1 |
| `s104_d37` | 2026-09-10 | E | 0 | 0 | 0 | 8 | 4 |
| `s104_d35` | 2026-09-11 | E | 0 | 0 | 0 | 12 | 4 |
| `s104_d38` | 2026-09-11 | E | 0 | 0 | 0 | 2 | 2 |
| `s104_d39` | 2026-09-11 | E | 0 | 0 | 0 | 6 | 3 |
| `s104_d34` | 2026-09-11 | E | 0 | 0 | 0 | 14 | 7 |
| `s104_part3` | 2026-09-11 | E | 0 | 0 | 0 | 44 | 37 |
| `s104_r31r35` | 2026-09-11 | E | 0 | 0 | 0 | 7 | 3 |
| `s104_r31r35p` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 1 |
| `s104_e1` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 1 |
| `s104_e4` | 2026-09-11 | E | 0 | 0 | 0 | 3 | 3 |
| `s104_e3` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 1 |
| `s104_e7` | 2026-09-11 | E | 0 | 0 | 0 | 5 | 5 |
| `s104_e2` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 1 |
| `s104_e6` | 2026-09-11 | E | 0 | 0 | 0 | 25 | 18 |
| `s104_e8` | 2026-09-11 | E | 0 | 0 | 0 | 3 | 3 |
| `s104_e9` | 2026-09-11 | E | 0 | 0 | 0 | 10 | 4 |
| `s104_e5` | 2026-09-11 | E | 0 | 0 | 0 | 10 | 10 |
| `s104_e10` | 2026-09-11 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_e13` | 2026-09-11 | E | 0 | 0 | 0 | 6 | 2 |
| `s104_e11` | 2026-09-11 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_e12` | 2026-09-11 | E | 0 | 0 | 0 | 7 | 6 |
| `s104_e14` | 2026-09-11 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_e16` | 2026-09-11 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_e17` | 2026-09-11 | E | 0 | 0 | 0 | 14 | 8 |
| `s104_r39` | 2026-09-11 | E | 0 | 0 | 0 | 6 | 6 |
| `s104_e15` | 2026-09-11 | E | 0 | 0 | 0 | 7 | 4 |
| `s104_r40r41` | 2026-09-11 | E | 0 | 0 | 0 | 2 | 2 |
| `s104_e18` | 2026-09-11 | E | 0 | 0 | 0 | 5 | 5 |
| `s104_e19` | 2026-09-11 | E | 0 | 0 | 0 | 6 | 4 |
| `s104_e20` | 2026-09-11 | E | 0 | 0 | 0 | 8 | 4 |
| `s104_e24` | 2026-09-11 | E | 0 | 0 | 0 | 4 | 4 |
| `s104_e21` | 2026-09-11 | E | 0 | 0 | 0 | 5 | 5 |
| `s104_e23` | 2026-09-11 | E | 0 | 0 | 0 | 7 | 4 |
| `s104_e25` | 2026-09-11 | E | 0 | 0 | 0 | 13 | 5 |
| `s104_e22` | 2026-09-11 | E | 0 | 0 | 0 | 5 | 3 |
| `s104_e26` | 2026-09-11 | E | 0 | 0 | 0 | 31 | 10 |
| `s104_e28` | 2026-09-11 | E | 0 | 0 | 0 | 14 | 6 |
| `s104_e27` | 2026-09-11 | E | 0 | 0 | 0 | 7 | 4 |
| `s104_e29` | 2026-09-11 | E | 0 | 0 | 0 | 7 | 2 |
| `s104_r39b` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 1 |
| `s104_r42` | 2026-09-11 | E | 0 | 0 | 0 | 3 | 2 |
| `s104_e33` | 2026-09-11 | E | 0 | 0 | 0 | 5 | 4 |
| `s104_e34` | 2026-09-11 | E | 0 | 0 | 0 | 8 | 4 |
| `s104_e30` | 2026-09-11 | E | 0 | 0 | 0 | 8 | 3 |
| `s104_e31` | 2026-09-11 | E | 0 | 0 | 0 | 13 | 5 |
| `s104_e32` | 2026-09-11 | E | 0 | 0 | 0 | 9 | 5 |
| `s104_e36` | 2026-09-11 | E | 0 | 0 | 0 | 15 | 8 |
| `s104_e35` | 2026-09-11 | E | 0 | 0 | 0 | 6 | 3 |
| `s104_e38` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 1 |
| `s104_e37` | 2026-09-11 | E | 0 | 0 | 0 | 53 | 23 |
| `s105_f2` | 2026-09-11 | E | 0 | 0 | 0 | 6 | 3 |
| `s105_f2_minlever` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 0 |
| `s105_r44r22` | 2026-09-11 | E | 0 | 0 | 0 | 13 | 3 |
| `s105_f1` | 2026-09-11 | E | 0 | 0 | 0 | 4 | 2 |
| `s105_f1_minlever` | 2026-09-11 | E | 0 | 0 | 0 | 3 | 0 |
| `s105_f3` | 2026-09-11 | E | 0 | 0 | 0 | 14 | 4 |
| `s105_f4` | 2026-09-11 | E | 0 | 0 | 0 | 13 | 5 |
| `s105_f5` | 2026-09-11 | E | 0 | 0 | 0 | 20 | 7 |
| `s105_f7` | 2026-09-11 | E | 0 | 0 | 0 | 9 | 5 |
| `s105_f7_minlever` | 2026-09-11 | E | 0 | 0 | 0 | 2 | 0 |
| `s105_r22b` | 2026-09-11 | E | 0 | 0 | 0 | 1 | 1 |
| **total** | | | **17,122** | **20,778** | **283** | **30,360** | **10,743** |

*Generated by `tools/lever_progress.py --render` from `.run/P36/census/lever_census.json` and `.run/P36/delever/ledger.jsonl`; the series lives in `docs/lever-progress.tsv` (R75: published numbers are generated, never typed).*

<!-- END GENERATED -->

---

## 3. How they got in

Nobody sat down to write 34,000 levers. They arrived one bank at a time, over five phases, each time as the cheapest way
past a real wall:

- **Phase 18** researched gcc 2.7.2's register allocator and produced *the pin toolkit* (cookbook §17). It worked: the wave
  close-rate went 33% → 56% → 90% in one phase. Pins were the difference between a wave that banked and a wave that did not.
- **Phases 19–29**, the family campaign, scaled that: one cracked exemplar remapped across up to 134 overlays, and every
  lever in the exemplar was copied with it. **This is why the count is in the tens of thousands and the distinct count is in
  the hundreds** — 12,578 bodies carry class A/B sites, but only 1,758 distinct texts.
- **Phase 23's** local-model tier and **Phase 30–31's** autonomous lanes drafted at a rate no human reviewed line by line;
  a pin that made the byte gate go green was, correctly for those phases, a win.
- **§501-E** (Phase 32) then replaced pins with *launders* on some functions — trading one lever for another. That recipe is
  explicitly out of bounds in Phase 36.

Two facts about that history matter for the argument below. First, **the knowledge needed to remove a lever did not exist
when the lever was added** — the §31 codegen map (Phase 23), the allocation-order reading (`alloc_table.py`, Phase 32) and
the §501-P/Q/R producer censuses all came later. Second, **Phase 32 measured the thing that makes this a debt rather than a
cost**: on the last four functions of the frontier, *every* pin came off byte-identical once the source shape was right
(R73). A pin was rarely load-bearing. It was a shortcut around finding the shape.

---

## 4. How they come off — the ladder, and what each rung is worth

| rung | what it does | cost | measured yield |
|---|---|---|---|
| **A** strip-all | remove every lever in a body at once, compile, compare | 1 compile | see the campaign table above |
| **B** greedy | re-add sites one at a time to find the minimal needed set | ≤ sites+1 compiles | the residue after A |
| **C** exemplar/replay | a multi-copy class judged once, replayed to every copy | 1 compile per copy | most of the fleet's copies |
| **R** recipes | the cookbook's byte-neutral **shape** recipes, mechanically (R2 declaration order · R3 initializer split · R4 one declaration moved through the run · R5 operand order of one commutative operator · R6 a single-set temp inlined at its use · R7 one statement wrapped in a block) | 1 compile per candidate | **134 of 134 bodies in 6.0 min, 3,243 compiles** (batch `r1`) |
| **D** permuter | decomp-permuter seeded with the **lever-free** body against the target bytes | ~12 min per exemplar | **5 of 16 exemplars, 665 of 2,131 bodies behind them, 0.69 h** |
| **E** agents | one agent per surviving class exemplar, with the pack | tokens | Phase 36 T7 |

**RUNG R IS A REPLICATION ENGINE, NOT A DISCOVERY ENGINE — measured, S99.** On a class whose shape rung D had already found it
closed **134 of 134 bodies in 6 minutes**. On 300 residue bodies where nobody had found the shape yet it closed **0 of 300 at
`--cap 40` (12,110 compiles, 4.6 min) and 0 of 300 at `--cap 400` (17,140 compiles, 6.0 min)`**. Two things make that a real
result rather than a budget problem: the instrument was checked on one body by hand (every candidate COMPILES and returns
DIFFERS — nothing was erroring out silently), and 17,140 compiles over 300 bodies is ~57 candidates each, so **the cap was
never the binding constraint** — ten times the depth produced 42% more candidates and closed nothing. The recipe rung banks a
KNOWN shape across a class for free; it has nothing to say about a shape that is not in its list. Growing it means finding
more shapes (rung D, then agents), and harvesting each one back into the rung so it sweeps the population for free.

**The two rungs feed each other.** Rung D's wins are not exotic: each is a small nameable source shape — a statement wrapped
in a block (`flag = 0;` → `do { flag = 0; } while (0);`), a single-set temp inlined at its use. Every one of them became a
rung-R recipe the same session, and rung R then banks the whole class **mechanically, as a one-line diff in the real
source**, where banking the permuter's own output would paste a pycparser-reprinted body into a phase whose entire purpose
is readability. Rung D is the *scout*; rung R is the *harvest*.

**What the residue looks like.** After rungs A–C the survivors split by the *starting distance* of the lever-free body from
the target, not by how many sites they carry: exemplars 8–29 mismatched instructions away closed (5.9 s to 651 s); those
70–276 away did not close in 12 minutes, and every one of those is a body where removing a hand-placed **instruction**
lever changed the instruction *count* and shifted everything after it. None is a wall — they improved 78→9, 52→3, 50→3,
37→2 — they are seeds for a longer run or for an agent.

**An instrument warning that cost two campaigns** (cookbook §454): a search harness whose target is *assembled from a
disassembly listing* is not measuring your code. `objdump` prints the pseudo-instruction `move` for `addu rX,rY,$zero` and
GAS assembles `move` as `or`; a listing's `%hi`/`%lo` pairs come back resolved with no relocation. The scorer read 28 for a
body that was byte-identical, so score 0 was unreachable and two campaigns reported "0 of 16" about a population that was
fine. **Seed any byte search with a body that already matches and require base score 0 before believing a yield.**

---

## 5. The question that outlives the project: prevent, or clean up at the end?

The honest answer is **neither extreme**, and the evidence points at a specific middle.

**What the numbers say.** The mechanical rungs (A/B/C) removed or rewrote **21,061 sites across 17,119 bodies** — the
campaign table's own totals — against **33,957** still standing: **38% of the class A/B population came off with no
understanding at all**, by strip it, compile, compare. Those levers were never load-bearing. They were speculative, added by a drafter that had no
cost signal for adding one, and a *single compile at bank time* would have refused them. That is the strongest measured
claim in this document: **more than a third of the debt would never have existed if banking a function had asked "does it
still match without this?" once.**

**What the history says against blanket prevention.** The pin toolkit is why Phase 18's waves closed at all, and the
knowledge to *replace* a pin with the right source shape did not exist until Phases 23–32. A rule of "no levers, ever"
adopted in Phase 18 would have stalled the project at ~56% for months, in exchange for a debt that a later phase paid off in
weeks with better tools. Deferring was not obviously wrong; **deferring silently was.**

**The rule we would actually adopt from day one** — and the one the day-one kit should carry:

1. **A lever is allowed, and it is a marked, ledgered debt from the moment it is banked.** One comment at the bank site
   naming the class and what it forces (`// !FAKE: pin $16 — without it gcc allocates x to $17`), and a census that counts
   them. Phase 36 had to *re-derive* that reason for 34,091 sites, function by function, years after the fact; writing it
   once at bank time is nearly free and is the difference between a debt and an archaeology project.
2. **The bank-time trial: compile the body once without the lever before accepting it.** One compile. It would have refused
   ~37% of the population at the moment of creation, when the context was hot.
3. **Publish the count as a first-class metric next to the match percentage.** A number nobody publishes is a number nobody
   pays down. This project's lever count was invisible until the phase that removed them.
4. **Levers get the harvest → toolify treatment, exactly like idioms.** When a wave learns the shape that replaces a lever
   class, that shape becomes a mechanical recipe and sweeps the banked population — instead of the lever propagating with
   every family remap (which is how 1,758 distinct bodies became 12,578).
5. **Do NOT block a phase on lever-freedom.** Keep the byte gate as the only gate; let the marker and the count carry the
   debt forward. A cleanup phase with mature tooling is genuinely cheap — rung A/B is a few hours of compute for a third of
   the population, and rung R banks a 134-copy class in six minutes.

**In one line for the kit:** *ban the silence, not the lever.*

---

## 6. For the wiki and the kit

- **Wiki page ("Levers")** — sections 1, 2 and 5 of this document, plus the current chart. The count belongs beside the
  match percentage on the progress page: a project that is 100% matched and 34,091 levers deep is not finished, and saying
  so plainly is the difference between this decomp and the ones the community complains about (`docs/gen3-standards.md`).
- **`decomp-architect/`** — section 5's five rules, as a Phase-1 kernel (a lever is a marked debt; the bank-time trial; the
  published count; harvest→toolify for levers; never block the byte gate on it) with this document's measured numbers as
  the provenance. The taxonomy in section 1 transfers unchanged to any gcc-era PS1 decomp.
- **Parked for the endgame (Drew, 2026-09-09):** train a **gcc 2.7.2 LoRA on the final clean asm/C pairs** and release it for other
  decompilations to use when cracking. Not now, and not on today's corpus: our 363,214 matched pairs are (asm → C-*with*-levers), so
  training on them teaches a model to PRODUCE pins. The corpus worth releasing is the one this phase creates — lever-free C beside its
  bytes — which is another reason to finish the removal before the project ships its dataset.
- **The story** — the arc is: a toolkit that unlocked the project (P18) → a family engine that multiplied it 134× (P19–29) →
  a phase that measured the debt for the first time (P36 T1) → mechanical removal of a third of it (T4) → a scout-and-harvest
  loop for the rest (T6) → zero (T7). The interesting beat is not the cleanup; it is that **the shortcut that made the
  project possible was also the thing it had to spend a whole phase undoing**, and that both were the right call at the time.

---

## 7. Maintenance

Run at the close of every task that changes the count, and at every phase close:

```
.venv/bin/python tools/lever_census.py --sites --check -j 16     # the count, and 0 UNMARKED
.venv/bin/python tools/lever_progress.py --snapshot "T6 r1"      # appends the milestone row, re-renders §2
```

`tools/lever_progress.py --check` fails when the series' last row is not this tree — a stale series is a wrong chart.
