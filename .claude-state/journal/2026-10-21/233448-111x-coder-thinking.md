---
ts: 2026-10-22T05:34:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SQ0Khzqs34HFm1UJLztD
---
Still 4. The residual is stubborn: the c6c load vs the q-0x48 load swap.

Time: 23:34. Let me now finalize:
1. Record item 2 (func_801536DC): already recorded (WALL, best 9, 32 tries) ✓ — but its wall time was 11 min. Hmm, I've since spent more time on item 2 (the n1-n12 batch) → its total wall time is now 22:59 → 23:30 = 31 min ✓ (the work on it is spread over the session). I'll report the total time spent per item honestly.

Hmm, for item 2, my recorded row says tries=32. I've since scored 12 more (n1-n12) → 44 tries. Let me update the row.

2. Record item 3 (func_8017849C): WALL, best lever-free = 35 (s9/m10/m12/t6 — 96 ins). Tries: the fresh-base ones: s1-s12 (12), t1-t9 (9), u00-u41 (42), v1-v7 (7), m00-m18 (15), plus the stale-base ones (invalid). Let me count the valid ones: 12+9+42+7+15 = 85, plus the partial probes (p_q*: 14, r000-r023: 24, zs0-zs11: 12) = 50 more → 135. Let me say 135 tries.

Hmm, that's a lot. Let me be accurate-ish: I'll count the scored candidates: fresh-base lever-free + partial probes. Let me just count the files: ls the item dir | wc.

3. Record item 4 (func_8018655C): WALL, best lever-free = 24 (w4/v1-v6/x06-x09/a*/b*). Tries: 10 (y) + 11 (z) + 7 (w) + 7 (v) + 10 (x) + 13 (a) + 13 (b) = 71.

4. win.c for each item = the best body.
5. Update the notes.md for each item.
6. Append the moves.md lines.
7. Write the log phase-ends/current/logs/T11.cG08c.md.
8. Clean up: remove the dumps, check the shard size.

Let me do this efficiently. First, the results rows + win.c + moves.md.

For item 3's win.c: the best lever-free = 35 (s9 = the three s32 copies in temps). Let me use s9 (96 ins).

Hmm, wait: for item 3, is 35 really the best? m10/m12 (the fresh-base permutations of the three copies) = 35 (96 ins) ✓ and s9 = 35 (96 ins) ✓.

For item 4's win.c: w4 (24).

For item 2's win.c: vV2_direct (9) — already copied ✓.

Let me now write everything. Note the evidence fields (≤140 chars).

Item 2 (func_801536DC): the wall tag "global-hardreg-reserve" ✓ (already recorded). Let me update the tries to 44.

Item 3 (func_8017849C): the wall tag: the mechanism = lever-free, loop.c creates an extra induction variable (p+0x0E) for the q-0x46 address → a 4th callee-saved reg (the frame is 40 vs 32) and the callee-saved bank order flips (p,q,i → $16/$18/$19 vs $17/$16/$18); the load temps take $2/$3 where the ROM has $4/$3. Tag: "loop-extra-iv" ✓.

Item 4 (func_8018655C): the mechanism = lever-free, the four loop variables (the counter and the call result in each of the two loops) are four global LO_REGs, so they take $16..$19 and `r` (a normal pseudo) never reaches $16 (the ROM has r in $16 with the counter pinned to $19 and the call result to $18). Best lever-free 24 (the call result via a temp). Tag: "global-lo-reg-count" hmm, or "greg-lo-reg-count". Let me use "greg-lo-reg-count".

Let me write the rows now.

Evidence for item 3 (≤140 chars):
"loop.c makes an extra induction var (p+0x0E) for q-0x46: 4 callee-saved regs (frame 40 vs 32) and the bank order flips p,q,i->$16/$18/$19 vs $17/$16/$18"
That's ~150 chars. Trim: "loop.c adds an induction var (p+0x0E) for q-0x46: 4 callee-saved (frame 40 vs 32), the bank order flips (p,q,i -> $16/$18/$19 vs $17/$16/$18)" ≈ 140. Let me count precisely later.

Evidence for item 4:
"lever-free the counter and the call result of BOTH loops are 4 global LO_REGs -> they take $16..$19 and r (a normal pseudo) never gets $16; best 24 (the call result via a temp)" ≈ 155. Trim.

Let me write the files with a script to control the tabs and lengths.

Also update the results row for item 2 (tries 32 → 44).

Let me do it now.
