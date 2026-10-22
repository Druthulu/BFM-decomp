---
ts: 2026-10-22T06:28:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_W4R3xi1yN1mrQWtAPscT
---
No improvement. Best remains 2 (q1 / v2_u16_aftervol_nest_volfirst_stmt).

Time: ~00:47. 44 minutes on the item. Over the 30-min guideline; time to write up.

Let me do the final bookkeeping:

1. Verify the best body one more time and save it as best.c in the item dir.
2. Append the results.tsv row.
3. Append the moves.md line.
4. Write notes.md in the item dir.
5. Write phase-ends/current/logs/T11.cG14b.md.

The results row format: `dir file func kinds result best tries wall evidence` (tabs).
- dir: func_80191020__ov_SC06_018_jr_8019059C
- file: src/ov_SC06_018/ov_SC06_018_jr_8019059C.c
- func: func_80191020
- kinds: launder
- result: WALL
- best: 2
- tries: 527 (473 this run + 54 earlier) — hmm, let me count precisely.

This run's scored tries: r 50 + t 10 + u 48 (first, buggy bodies) + u 48 (fixed) + v2 280 + w 14 + y 15 + z 8 + zz 4 = 477. Plus the earlier 54 = 531. Let me recount: 50+10 = 60; +48 = 108; +48 = 156; +280 = 436; +14 = 450; +15 = 465; +8 = 473; +4 = 477. So 477 this run + 54 earlier = 531.

I'll write 531.

- wall: a new tag. Let me define `dbr-delay-fill-2ndset`: the 2nd-set instruction of vol is ready before the bne, so the final pass parks it in the bne's delay slot where the target speculates the sll copy.

Hmm, per the walls.txt format: "<pass>-<what>", lowercase. The existing "dbr-delay-fill" is the reorg/delay-slot family. My case: the delay slot is filled by the final/reorg pass with the 2nd-set's instruction instead of the sll copy. I'll use `dbr-delay-fill-2ndset` and define it in the evidence.

- evidence: "gcc: the lever-free 2nd set of vol (u16 cast = 1 andi) is ready before the bne, so the final pass parks it in the delay slot where the target speculates sll a2,a2,0x8; the target has no extra andi (192 ins = 192, 2 differ)".

Let me make it ≤140 chars.

Let me also double check: the best body (q1) is exactly v2_u16_aftervol_nest_volfirst_stmt.c. Let me diff them to confirm, and verify the score once more.

Then, moves.md line: `launder | func_80191020 | WALL dbr-delay-fill-2ndset — mechanism (G14)`.

The format from the brief: `kind | func | MATCH: move / WALL tag — mechanism (G14)`. Looking at the existing lines: e.g. "launder | func_80183098 | WALL cse-const-addr — cse: find_best_addr rematerialises ... (G14)". So: `launder | func_80191020 | WALL dbr-delay-fill-2ndset — <mechanism> (G14)`.

Let me write the notes.md for the item dir too.

And the log: phase-ends/current/logs/T11.cG14b.md with the timeline (start/end time, minutes, tries per item), the moves that cracked (none), the walls with evidence, and the "Friction" section if any refused commands (yes: two refused commands — the find /home/musashi and the wrong path Write). Let me record those.

Refused commands:
1. `ls /usr/local/ /opt/ 2>/dev/null; find /home/musashi -maxdepth 3 -iname "*gcc*" 2>/dev/null | head -20` → refused by PA3: /home/musashi is outside this project. Route: I used the project card (`tools/card.py slice coder`) and the project's own tools instead.
2. The Write with the path /home/musashi/bfm-decomp/../.run/... → refused (outside the project). Route: used the absolute path under /home/musashi/bfm-decomp/.run/...

Let me write everything now. First, the best body and the verification.
