---
ts: 2026-10-22T07:07:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_drxxhkRrJneMIKW1SVUw
---
Interesting: cand29 (`while (0) { rgb = rgb; }`) and cand30 (`for(;0;)`) also give score 4 — same as the do-while. So the loop construct (any) creates the LOOP notes → the same effect.

All the "loop" variants give score 4 (the li in the delay slot).

So the best lever-free body is score 2 (cand01: the plain removal) — wait, the best is the LOWEST score: 2 (cand01 and many others). The loop variants give 4.

So best = 2 with the plain removal (no launder, no loop).

Hmm! But wait: for a WALL row, "best = lowest score of a lever-free body". The lever-free body = no launder. cand01 is lever-free (score 2). So best = 2.

Hmm, but hold on: is the do-while "lever-free"? The constraint says `do{}while(0)` only with `// !FAKE: do-while` — so a do-while is allowed as a plain-C move (it's listed in the C0505 catalog? "loop shape" is in the catalog ✓).

So best = 2 (cand01: the plain removal of the launder).

Hmm, so the WALL for item 3: the launder is needed for two things: (1) the 2nd set of the pinned $16 pseudo (sched1 birthing boost), (2) an RTL insn between the move and the call's arg setup (which keeps the `li a0,16` out of the jal's delay slot). Plain C can supply (1) via a loop construct (do-while/while(0)/for) but that costs the delay-slot fill (score 4); the plain removal gives score 2.

Let me double check: is there any variant that gets the delay slot right? What if the loop is placed AFTER the call but the boost... no.

Hmm, let me try one more thing: what if we use BOTH: the do-while (to fix the move/li order) AND something to fix the delay slot? The delay-slot problem: the li ends up in the jal's delay slot.

What if the li is NOT adjacent to the call? It always is (reload puts it there).

Hmm, what if the call had a different structure...

What if the SECOND call (func_8004914C) or another call is affected... no, the first call is the issue.

Let me try: what if we make the call's argument NOT a constant but a variable that is 16, so the arg setup is a `move a0, sz` — different instruction. No.

OK, one more experiment: what if the loop construct is placed between the move and the call but with a body containing an instruction, so that the LOOP notes + an insn appear between? E.g.:

```
rgb = arg2;
temp_v0 = func_80010A08(0x10);
```
Hmm no.

What about a do-while whose body is an instruction that the target has — e.g. move the `*(u8 *)((u8 *)temp_v0 + 7) = 0x42;` store INTO a do-while placed... it needs temp_v0.

Hmm! What about this: put the do-while (with the store of 0x42 inside) right after the call:

```
rgb = arg2;
temp_v0 = func_80010A08(0x10);
*(u8 *)((u8 *)temp_v0 + 3) = 3;
do { *(u8 *)((u8 *)temp_v0 + 7) = 0x42; } while (0);   // !FAKE: do-while
*(s32 *)((u8 *)temp_v0 + 4) = rgb;
...
```
The loop notes would be after the call → the entry block's chain: [move s2,a0, move s4,a1, move s0,a2, li, call, ...] — the li's position relative to the move would be like cand01 (score 2)? But the loop might change the scheduling.

Hmm, we want the LOOP notes between the MOVE and the LI. The li is created by reload before the call. The loop notes are in the source-order position of the do-while. So the do-while must be between `rgb = arg2;` and the call in the SOURCE. And its body must be an instruction we can afford... but any statement between them emits an instruction → +1 insn.

UNLESS the body is an instruction the target has elsewhere and we REMOVE it from its place! E.g., the target's `*(u8 *)((u8 *)temp_v0 + 3) = 3;` — no, needs temp_v0.

Hmm, what about `sw s0,24(sp)`? That's the prologue's.

What about this: `rgb = arg2;` → what if we write it as a do-while body?
```
do { rgb = arg2; } while (0);   // !FAKE: do-while
```
That's cand24 (score 8) — the loop's insn (the copy) is inside the loop, so the chain has the loop notes around the move → the move ends up after the li.

What about:
```
rgb = arg2;
do { } while (0);   // !FAKE: do-while
```
= cand34 (score 4).

So the best loop variant is 4 and the plain removal is 2.

Therefore: best = 2 → WALL for item 3 with a new wall tag. Let me name it: `sched1-boost-dbr-delay` hmm. The wall tag format: `<pass>-<what>`: e.g. `sched1-birth-boost-dbr-delay`.

Let me write the evidence: "gcc -O2: 99 ins = target; the tree's re-tie gives the pinned $16 pseudo a 2nd set (kills sched1's birthing boost) AND leaves an RTL insn between the birth and the call's arg setup (keeps li a0,16 out of the jal delay slot); plain removal = li hoisted before the move (score 2), a do-while fixes the order but the li falls into the delay slot (4)".

That's ≤140 chars? Let me count later; the evidence should be ≤140 chars. I'll trim.

OK. Now, I've spent ~1 hour on item 3 (over the 30-min budget). I have 4 more items. Let me be much more efficient on them: for each item, first look for an analogous move in moves.md (there are MANY launder MATCHs with known recipes):
- "launder -> real 2nd set pv &= mask" (G11)
- "launder -> pv = *p; pv &= 0xFF000000 split" (G05/WH1)
- "dead-reset CSE-breaker" (G10, G15 item 1)
- "do { } while (0) + v0 = (s16)v0"
- "pointer reuse"
- "n = (s16)n at both sites"
- "out-only launder -> real 2nd set pv = *p; pv &= 0xFF000000; *p = pv | ..."

The recipe for a launder on a PINNED var: give the var a REAL 2nd SET via a compound assignment (e.g. `pv &= 0xFF000000`) — this is the G11 recipe.

Let me now look at item 4 (func_80190D70 in ov_SC06_032_jr_801902EC). Note moves.md line 59: "keepalive,launder | func_801902EC | MATCH — per-segment q: ..." — that's a different function (func_801902EC).

Let me look at the next item's source. Time is precious; let me move fast.

First, let me write up item 3's results (results.tsv row + notes.md) so it's not lost, then move to item 4.

results.tsv row format: `dir file func kinds result best tries wall evidence` (tabs).
dir = func_8018FB5C__ov_SC06_032_jr_80182890
file = src/ov_SC06_032/ov_SC06_032_jr_80182890.c
func = func_8018FB5C
kinds = launder
result = WALL
best = 2
tries = 34 (count: 9+9+7+6+6 = 37; let me count precisely: cand01..cand34 minus the ones that failed = 33 scored + 1 compile error = 34 tries)
wall = sched1-birth-boost-dbr-delay
evidence = "gcc -O2: 99 ins = target; re-tie gives $16 a 2nd set (kills sched1 birth boost) and an RTL insn before the call's arg setup; plain drop = 2, do-while = 4"

Let me count the tries: scored candidates: cand01,02,03,04,05,06,07,08,09 (9), cand10..cand18 (9), cand22..cand28 (7), cand29..cand34 (6) = 31 scored + cand14 compile error = 32 tries. Plus the orig (the tree body) isn't a try. So tries = 32.

Let me write the row and notes, then move on.

Also append to moves.md: "launder | func_8018FB5C | WALL sched1-birth-boost-dbr-delay — ... (G15)".

Let me do thatnow.
