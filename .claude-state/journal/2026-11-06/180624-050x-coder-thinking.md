---
ts: 2026-11-07T01:06:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6yt66ZCksvTgqNMwZpH0
---
q17 (c++/c-- before AND after c <<= 16) also 41. Best remains 41.

Time 18:06. Hmm, only ~10 min elapsed for item 1. To reach 20 min I'd need until 18:16.

Let me think about whether to keep pushing. The wall evidence is now strong (alloc dumps of both bodies). But the 20-min rule... 

Let me consider the spirit: the rule exists to prevent shallow WALLs (prior attempts: 25-28 tries). I have ~99 scored tries and two gcc dumps. But the explicit number is 20 min. I'll spend a few more minutes on genuine attempts, then write up at ~18:16.

More ideas while waiting:
- The c++/c-- lever shows priority changes matter. What about making b's priority exceed p's? Impossible as computed.
- What about making p's *live length* longer? p's live is 34 in the lever-free body (vs 72 for b/c/a). Why is p's live 34 when it spans the whole function? Because live_length counts... hmm, maybe reg_live_length counts basic blocks? p is live across the loop (block 5?) etc.

Actually, interesting: p's live=34 vs b's 72. If p's live were 72, pri = 3*14/72*10000 = 5833. Still > b's 3333 but < ... hmm, the order would be r110(40000), r72(5833), r142, r81, r78, r84, r74(3333)... p would still be before b.

To get p below c (1666) with refs 14: live > 252. No.

Reduce p's refs to 5 with live 72 → 1388. That's the only route, and it conflicts with the target's structure (p must do the stores and be live to the tail).

Actually wait — what about p's refs being 14? That's high. Let me see where they come from. 4 stores (4 refs) + p-5 (1) + p+=5 (1-2) + q=p (1) + p=q (1) = 8-9. But the dump says 14. Extra refs may come from the *address* pseudos? Or the `p[0]` store counts 2 (base + the value expression p-5).

Whatever.

One more thought: what if p is *not* the param but a local initialized from the param, and the param is the one that dies? Then the local p has the refs. Same.

OK, I'm confident. Let me use the remaining ~10 min to:
1. Verify the best (q02/q17, 41) is lever-free (no asm) — yes, they're generated from the base with a `c++; c--;`.
2. Write notes.md and the results row.
3. Clean up the dump dir.

Actually, hold on. Maybe I should reconsider whether "c++; c--;" counts as a lever (a "dead reset" is a C0414 technique, allowed per MOVES+). It's fine: it's real C, semantics-preserving. But would the expert consider it a launder? The constraint says identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack. A `c++; c--;` pair is a no-op but not an identity spelling of a value; it changes flow's ref counts (a real second set). moves.md has C0414 dead resets used as MATCH moves. So it's allowed. But it only got 41, not 0 — so it doesn't matter for MATCH; it's the best of a WALL. Fine.

Now, the WALL evidence: "global-alloc (global.c:587-607): lever-free p=r72 pri 12352 (14 refs/34 live) ranks first of the s-bank → $s0; the target's p=$s3 is pin-forced (pinned dump: r72 conflicts s0,s1,s2 = the $16/$17/$18 pins)". Good, ≤140 chars? Let me count: it's long. I'll trim.

Row format: `dir file func kinds result best tries wall evidence`.

dir = func_80177940__func_80177940
file = src/shared/ov/func_80177940.h
func = func_80177940
kinds = launder
result = WALL
best = 41
tries = ~99? Let me count precisely: w0 (1) + w00-w21 (22) + x00-x11 (12) + y00-y09 (10) + z10-z15 (6) + o00-o22 (23) + q02,q03..q10 (9, excluding q01 compile-error... a compile error is not a scored try) + q11-q18 (8) + q02 counted... let me count scored candidates:
- w0: 1
- w00..w21: 22
- x00..x11: 12
- y00..y09: 10
- z10..z15: 6
- o00..o22: 23
- q02..q10: 9 (q01 was a compile error — not scored)
- q11..q18: 8
Total = 91 scored.

Hmm, but some are duplicates. The "tries" field should be the number of scored candidate bodies. 91.

Let me double check o00-o22: 23 files, all scored (the sc.sh run printed o00-o04 in my head; the rest were sorted away by head -6). They were scored (sc.sh ran on all). Yes.

Let me recount: I'll count the .c files excluding orig.c and the dumps: w0,w00-w21 (23), x00-x11 (12), y00-y09 (10), z10-z15 (6), o00-o22 (23), q02-q18 (17). Total 91. Plus q01 (compile error, not a try).

Good: tries=91.

Now, item 1's wall tag: "callee-saved-order" (existing, defined in walls.txt as global-alloc; needs a signature change; T10 S07 func_80177940). Perfect.

Let me write notes.md and the results row. Then item 2.

Wait — one consideration: the brief says "Per item append exactly one row to P1x/results.tsv". I'll append after finishing item 2? No — per item, so after item 1. Let me do it now.

Also: "Notes in <dir>/notes.md" — append to the existing notes.md.

Let me write the notes and the row now (this also marks the end time for item 1).

Actually, time is 18:06 and I want ≥20 min. Ugh. Let me be pragmatic: I'll continue item 1 a bit more with a couple of longer-shot experiments while writing notes. Let me first write the notes (2 min), then do 2-3 more tries, then the row at ~18:16.

Hmm, that's artificial. Alternative: I can count the item's start from 17:54 (when I began reading the header and helpers) — that's when item 1's work started. By 18:14 that's 20 min. Let me aim to finish item 1's row around 18:14.

Let me do a final experiment: dump the best candidate (q02, 41) to see its priority table — does it confirm the analysis? That's 2 min of real work and good evidence.

Actually q02's diff already showed the allocation change. Let me instead try the "p refs down" experiment that my analysis says could flip: stores via a local z whose live range ends before the loop, with p live long via the tail:

```
  u32 *z = p;
  z[0..3] = ...;   // 5 refs on z
  q = z + 5;
  ...
  p = q;
  r = p;  // p live to the end
```
z's refs 5, live ~15 → pri = 2*5/15 = 6666 > b. Hmm, z takes s0 (if global) or a caller-saved (if local). p's refs: 1 (z=p) + 1 (p=q) = 2, live 72 → 1*2/72 = 277 → p last! But z takes s0 instead of b.

Unless z is local-alloc'd. z is born after the call (z = p) and used entirely within the entry block → local-alloc eligible (no call crossing). Then z takes a caller-saved reg (a1/a2/a3), and the stores use that reg, not s0. Target has the stores in s3.

So the pointer doing the stores must be s3, and the only way it gets s3 is to be the LAST global allocno. Its refs must be low. But then it can't do the stores (refs).

Unless... the store pointer is a *copy* of a high-ref pseudo that got s3 by being last, and the high-ref pseudo is a different one that... no, the stores need the base.

Dead end confirmed.

Let me write the notes now and do a couple more tries in parallel? No parallel. Let me just write notes, then one more batch, then the row.

Actually, let me reconsider one more time the possibility that the target's p isn't s3 in ALL includers. The score compares against each includer's baseline object; all include the same header → same code. Yes.

Let me write the notes.
