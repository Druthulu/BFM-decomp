---
ts: 2026-11-06T12:51:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PsUdcqKwuSuHd2tOsNuA
---
No luck. j2 with goto still 407 — the goto to the immediate next label was deleted.

Let me try a different goto target: put the label after the `ub = ua + rec->h - 1;`... no.

Another idea: make the else arm *fall through to the join via a label placed elsewhere*. 

Alternatively: maybe I can prevent dbr from filling by making the branch's delay slot already occupied by a real insn. In the target, the delay slot has `andi v1,t0,0xffff`. In f1, the delay slot is the move. What if I add a real statement between the branch and the else that gcc schedules into the delay slot? Hmm, the delay slot insn comes from the block before/after.

In e2, the delay slot is `andi v1,t0,0xffff` — a real insn from the ua/ub computation. And e2's structure is right except the arms are swapped. So in e2, dbr did NOT thread the else (the else was out-of-line as `j`+move). 

So: e2's source has `if (!tc) { ua = ub; } else { ua = ub - 0x100; }` and gcc out-of-lines the else (tc arm) and threads the move into the j's delay slot (the move at ba88 is in the j's delay slot, not the beqz's).

Target: out-of-line = the else (move), fall-through = tc arm with j, and the tc arm's addiu is in the j's delay slot.

So in both, the *then* arm is the fall-through and the else is out-of-line. In e2 the then arm is `ua = ub` (move) and it's in the j's delay slot (as the then arm fall-through). In target the then arm is `addiu`.

So if the then arm is the tc arm (`if (tc) {...}`), gcc should out-of-line the else (move) → target! But f1 does something different: it threads the else's move into the *beqz* delay slot and drops the j entirely (407 insns).

Why the difference? In f1, the else block's move goes into the beqz delay slot (executed always). In e2, the then block's move goes into the j's delay slot.

The difference between f1 and e2 is only the source arm order... and the resulting branch polarity (beqz vs bnez). Hmm.

Wait, maybe in f1 the difference is which block ends up where. Let me check f1's full layout again:
```
ba7c andi v0,a1,0x10
ba80 beqz v0,ba8c      ; !tc → ba8c
ba84 move a0,v1        ; delay slot: ua=ub (else)
ba88 addiu a0,v1,-256  ; tc arm
ba8c lbu v0,0(s2)      ; join
```
Yes: the else's move is in the beqz delay slot and the tc arm is the fall-through, then join. Only 3 insns in the if (beqz, move, addiu) vs target's 4 (beqz, j, addiu, move).

For target, the move is at ba8c and the beqz jumps there; the fall-through is j+addiu. That requires the j.

Since gcc chose the shorter form in f1, real C can't easily force the longer one... unless the else's move isn't movable into the delay slot. 

dbr's condition for filling a delay slot with an insn from the branch target ("thread"): it requires the insn to be `simplejump_p`-safe etc. A move is safe.

What if the else arm's move is not a `move` but an `addiu a0,v1,0`? Then it's still movable.

What if the else arm is `ua = ub;` but ub is in a *hard* register (pinned)? Hmm.

What if `ua` is used after the join *and* on the tc path? a0 is ua. On the tc path a0 is set by addiu. Fine.

OK here's another angle: what if I make the tc arm TWO insns so that the fall-through block can't be threaded and gcc picks the out-of-line else? e.g.:
```
if (tc) {
    ub = ub - 0x100;
    ua = ub;
} else {
    ua = ub;
}
```
Then the then arm = subu+move (2 insns), else = move (1). Target has addiu a0,v1,-256 in one. Mine would be `addiu a0,v1,-256` then `move a0,a0`? The move would be copy-propagated away → back to 1 insn. Ugh.

What about `ua = ub - 0x100;` written as `ua = ub; ua -= 0x100;`? f2-ish = 10.

Let me try one thing: `if (tc) { ua = ub - 0x100; } else { ua = ub; }` but with the else arm assigning a *different* variable `ub2` that is then used:
```
if (tc) {
    ua = ub - 0x100;
} else {
    ub2 = ub;
}
ua = (tc) ? ua : ub2;   // hmm
```
Too many insns.

I think this is a genuine wall. 13-15 min in, ~45 scored tries. Let me record it as WALL with tag dbr-delay-fill and move on. Actually — one more cheap idea: the `tc` variable is s32. What if `tc` is declared as `u32` or the mask is `0x10`... no effect on the branch.

And what about `if (tc) { ua = ub + -0x100; } else { ua = ub; }`? same.

Let me stop and record. Item 1: WALL, best 3, tag dbr-delay-fill, evidence: "dbr: fills the beqz delay slot with the else's `move a0,v1` and drops the j; target keeps an out-of-line else + j (408 vs 407); all 4 barriers gone, best 3."

Now write notes.md, append results row, append moves.md line.

results.tsv format: `dir file func kinds result best tries wall evidence` (tabs).
Row: `func_8001DA34__800	src/800.c	func_8001DA34	barrier	WALL	3	<N>	dbr-delay-fill	<evidence ≤140 chars>`

Let me count tries: b1,b2,b3,b4 (4), c2a-d (4), c3a-d (4), c4a-c (3), combo, combo_nb2 (2), d2a-d (4), e1-e6 (6), f1-f4 (4), g1-g4 (4), h1-h4 (4), i1-i3 (3), j1-j3 (3) = 45. Plus orig baseline and win.c rescores. Say 45.

Evidence must be ≤140 chars: "dbr fills the beqz delay slot with the else move, drops the j (407 vs 408); target keeps out-of-line else + j. arms-swapped = 3, other shapes 10+" — that's ~150. Trim: "dbr fills beqz delay slot with else's move a0,v1 and drops the j (407 ins); target keeps out-of-line else+j (408). All 4 barriers gone, best 3" = 140ish. Let me count later.

Let me write the files.
