---
ts: 2026-11-06T05:07:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FQAeh3cTi5dsTlZ9T2IU
---
All three MATCH. Now write notes.md per item, results.tsv rows, moves.md lines.

results.tsv format (tabs): `dir file func kinds result best tries wall evidence`.
- dir = item dir name (as in list.tsv, e.g. func_8017F5A4__ov_SC07_010_jr_8017AE2C), file, func, kinds, result, best, tries, wall, evidence.
- MATCH rows: wall `-`. best = 0 presumably. tries = number of scored candidates.
- evidence = gcc pass + mechanism ≤140 chars.

Item1: dir func_8017F5A4__ov_SC07_010_jr_8017AE2C, file src/ov_SC07_010/ov_SC07_010_jr_8017AE2C.c, func func_8017F5A4, kinds barrier, result MATCH, best 0, tries? Let me count candidates scored: a1, b1,b2,b3,b4,b5,b6,b7,b8 = 9 (b7 win). Say 9.
evidence: "sched1: do-while(0) store per byte keeps the next lbu below the sb (no hoist); direct a0[] avoids the pointer copy — 22/22".

Item2: dir func_800D0214__resident_jr_800D00E4, file src/resident/resident_jr_800D00E4.c, func func_800D0214, kinds barrier, MATCH, best 0, tries: a1,b1-b11 (11), c1-c5(5), d1,d2(2), e1-e6(6), f1-f4(4), g1-g5(5) = 1+11+5+2+6+4+5 = 34. Hmm, let me count: a1(1), b1..b11 = 11 → 12, c1..c5 = 5 → 17, d1,d2 = 2 → 19, e1..e6 = 6 → 25, f1..f4 = 4 → 29, g1..g5 = 5 → 34. Yes 34 tries.
evidence: "greg/cse: store via `s32 *q=&D_800A2E20` decl'd at top + do-while(0) around the D_800C7C64 store keeps its addr late and mask in v1 — 43/43".

Item3: dir func_8013A2BC__func_8013A2BC, file src/shared/ov/func_8013A2BC.h, func func_8013A2BC, kinds barrier, MATCH, best 0, tries: a1, h1-h5(5), i1-i3(3), j1,j2,j4(3), k1-k4(4), l1,l2(2), m1,m2(2) = 1+5+3+3+4+2+2 = 20. Plus baseline orig (not a try). Say 20.
evidence: "cse: dead reset `v0=0` after the sh kills the store->reload equivalence (mem D_80127524 -> reg); delete_dead_from_cse drops it; reload survives, 141/141 includers".

Wait: for item3, MATCH means score 0 on every includer; I verified FAILS=0 over 141.

Now moves.md append lines:
`kind | func | MATCH: move / WALL tag — mechanism (G20x)`
- barrier | func_8017F5A4 | MATCH: do-while(0) around each byte store keeps the next lbu below the sb; direct ((u8*)a0)[i] (no pointer copy) (G20x)
- barrier | func_800D0214 | MATCH: `s32 *q=&D_800A2E20` at top + do-while(0) around the D_800C7C64 store (addr stays late, mask v1) (G20x)
- barrier | func_8013A2BC | MATCH: dead reset `v0=0` after the sh breaks cse store->reload; deleted by delete_dead_from_cse; 141/141 includers (G20x)

moves.md is append-only, allowed ("appends to .run/P40/T11/moves.md").

Notes per item: write <dir>/notes.md with details.

Then write the log phase-ends/current/logs/T11.cG20x.md. Wait — LOG: phase-ends/current/logs/T11.cG20x.md. But the system says never read phase-ends/*/logs; writing is required by the brief. The brief says LOG: phase-ends/current/logs/T11.cG20x.md. Hmm, but the harness prompt says "write phase-ends/current/logs/T<n>.c<k>.md". OK, write it.

Also results.tsv: the header line already exists. Append 3 rows with tabs.

Let me check the "FRESH" requirement: at each item's start diff orig.c against the def in the current src file. I copied orig.c at the start of each item from the current src. Since no src changes happened during my run (no git/make), they're current. But the requirement says if it differs, regenerate. They were generated fresh now, so fine.

Let me write notes and files.
