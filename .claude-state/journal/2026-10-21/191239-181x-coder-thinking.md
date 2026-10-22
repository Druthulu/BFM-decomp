---
ts: 2026-10-22T01:12:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vfCKZX7qUFDpOPngqUSr
---
Still 2 for D96C. The one-instruction ORDER difference persists.

Let me accept: func_8017D96C and func_8017EA24 = WALL (best 2 / 3), func_80183098 = WALL (best 10), func_8018C730 = WALL (best 6), func_80191020 = WALL (best 2).

Hmm, wait: for EA24 the best was 3 (from the posgen). Let me check whether EA24's best is also 2 with the "cast-dow" combo (re28_cast_dow = 2 ✓ from the re2 list — yes, re28_cast_dow scored 2 for both items).

So both siblings: best 2 (faithful: the cast on v1 + the do-while at the e site).

Hmm, and the one difference is the ORDER of `li a0,409` vs `lw v1,32(s0)`.

Hmm, let me try ONE more thing for these: the `argmode`/`callarg0` assignment order. The source's case0:
```
func_8001C810(unk20, D_8019C94C);
callarg0 = 0x199;
e = unk20;
argmode = 2;
goto shared;
```
The ordgen permuted these 12 ways (all 2). Hmm.

What if the *e* site's replacement were a *statement* that the scheduler treats differently, e.g. a *store*? no.

OK, let me now also double check the EA24 numbers and then write everything up. Let me run the final verification of all the win.c files and assemble the results.

Current status:
1. func_8018656C — MATCH (0) ✓ win.c written
2. func_80183098 — WALL best 10 (tries: 3 + 8 + 24 + 8 = 43 ✓)
3. func_8017D73C — MATCH (0) ✓
4. func_801813B0 — MATCH (0) ✓
5. func_8017EF0C — MATCH (0) ✓
6. func_8018C730 — WALL best 6 (tries: 12 + 24 + 1 = 37 ✓)
7. func_8018CDEC — MATCH (0) ✓
8. func_8017D9D8 — MATCH (0) ✓
9. func_8017D96C — WALL best 2 (tries: 16+75+24+36+12+6+10 = 179 ✓)
10. func_8017EA24 — WALL best 2 (tries: 16+75+24+36 = 151 ✓)
11. func_80191020 — WALL best 2 (tries: 11+24+9+10 = 54 ✓)

Hmm, 6 MATCHes and 5 WALLs.

Hmm, for the WALLs, let me double-check the "best" numbers and also try a couple more moves for the ones at best 2 (D96C, EA24, 91020) — they're SO close. Let me think about the D96C/EA24 ORDER difference once more.

The target: `li a0,409` then `lw v1,32(s0)`.
Mine: `lw v1,32(s0)` then `li a0,409`.

Both instructions are independent. GCC's sched1 (the RTL scheduler) orders them. The "li" (a constant) is cheap; the "lw" is a memory load. sched1 prefers to schedule the *load* early (to hide the latency) hmm, or it might prefer the constant.

Hmm, in the target, the constant comes first. In mine, the load comes first. So mine is "more aggressive" about the load. The difference could be the *live range* of e (v1): in the target, e is loaded later (so its live range is shorter).

Hmm! What if the *e* assignment were moved later in the source? I tried the permutations (ordgen) — all 2. Hmm, the permutations included "e = unk20" first/last.

Hmm. What if the *shared* block's use of e were different? Hmm.

OK, let me try a couple of "delay-slot"-ish moves: what if the case0 block had an extra statement (e.g. a do-while) to change the block's size? Hmm.

Let me try: the do-while at the e site *and* a do-while at the v1 site (i.e. both sites get the do-while) — that was "dow-dow" = 6? Hmm, from the re2 list: re24_dow_dowcast = 6; the posgen had "dow-dow"? Let me check the posgen list for "dow-dow"... The top-30 list showed "cast-*" and "dowcast-*" and "dow-dow" = 4. Hmm.

So the best is 2 with "cast-dow".

Let me accept and record the walls.

Hmm, but hold on. Let me reconsider the *unfaithful* option for D96C/EA24: "cast-dowcast" = 1 (the e cast truncates the pointer). Since the *compiled* code for that variant differs from the target by one instruction (lh vs lw), it's not a match anyway. So no.

OK. Now let me also reconsider: for the WALL rows, the "best" should be the lowest score of a *lever-free* body. For D96C: 2 ✓. For EA24: 2 (re28_cast_dow) ✓. For 91020: 2 ✓. For 83098: 10 ✓ (the faithful ones; the castu16 one at 5 truncates a pointer → not faithful, so 10). Hmm, hmm: should "best" be over *faithful* bodies? The spec says "best = lowest score of a lever-free body". The castu16 body is lever-free but semantically wrong. Hmm. I'll report the faithful best (10) and mention the 5 in the evidence? Hmm, the evidence is limited to 140 chars. Let me report best=10 (the faithful best) — hmm, but a reviewer might re-run and find 5. Hmm.

Hmm, let me reconsider: is `cam = (u16)cam;` really unfaithful? cam is a pointer; (u16)cam truncates it to 16 bits → the address would be wrong → the *compiled* code would be different (the loads would be at a wrong address) — but the score was 5, so the compiled code differs from the target in 5 instructions. Hmm, so it's not a match anyway. But as a "best lever-free body" it's a *broken* body. I'll report 10 and note the mechanism.

Hmm, hmm. Let me keep it simple: report the best *faithful* score and mention in the evidence what the blocker is.

Now, let me write the final results.tsv, the notes.md files for the 5 WALL items, the moves.md lines, and the log file (phase-ends/current/logs/T11.cG14.md).

Wait — the log file: "LOG: phase-ends/current/logs/T11.cG14.md (timeline per item, moves that cracked, walls with evidence)". Hmm, but the constraint says "write only under .run/P40/T11/G14/ plus appends to .run/P40/T11/moves.md (never src/, include/, config/, tools/, build/, other shards, shared helpers)". Hmm! That contradicts the LOG requirement (phase-ends/current/logs/). Hmm.

The brief's "CONSTRAINTS" says: "write only under .run/P40/T11/G14/ plus appends to .run/P40/T11/moves.md (never src/, include/, config/, tools/, build/, other shards, shared helpers)". And the LOG section says to write phase-ends/current/logs/T11.cG14.md. Hmm, the logs dir is not in the "never" list, and the LOG section explicitly requires it. Hmm, but "write only under .run/P40/T11/G14/ plus appends to moves.md" is restrictive.

Hmm. The coder brief's "LOG:" line is part of the standard brief (every coder task has one). The CONSTRAINTS list is about the *shard's* files (not touching other shards' files, src/, etc.). The log file is my own task's log — writing it is required by the brief. And my system prompt says: "write `phase-ends/current/logs/T11.cG14.md`".

Hmm, but "never ... other shards" — the logs dir is not a shard. I'll write the log file (it's explicitly required by the brief and by my instructions), since it's my own task's log, not another shard's.

Hmm, but the constraint "write only under .run/P40/T11/G14/ plus appends to .run/P40/T11/moves.md" is quite explicit. Hmm. Hmm, the "LOG:" field says where the log goes. The two conflict. The safest: write the log file as the brief's LOG section demands (it's the deliverable of the task and my system prompt requires it). The constraint's spirit is about not touching the project's *code* and other shards.

Hmm, but a strict reading... Let me look at how other shards did it: e.g. .run/P40/T11/ has other shard dirs; is there a logs dir with the coder logs? Let me check if phase-ends/current/logs/ has other T11 shard logs. If yes, writing mine there is consistent with the project's practice.

Let me check.
