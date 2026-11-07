---
ts: 2026-11-06T17:13:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3gC6j2SfmYCLQsC6zsps
---
b43's residual: the first computation's temp is s0 for the %4 part but the result goes to v0; the second computation's temp is v1. The register mismatch is only in the temp's register.

Time: 19.1 min. Let me spend 1 more minute and then record at 10:14.

Let me record the wall now (10:14+). Actually the rule: ≥20 min. Item start was 09:54:00 (approx; the item 2 cleanup printed 09:54:00, then I read item 3). Let me say start 09:54. 20 min → 10:14. It's 10:13. One more command will pass it.

Let me copy b43 to win.c and score it once more, then write the results row at 10:14.

Wait — for a WALL, should win.c be the best lever-free body? The brief's DONE WHEN: "each MATCH/PARTIAL has its win.c scoring 0". For WALL, the win.c should presumably hold the best attempt. The results row format says "best = lowest score of a lever-free body". I'll put b43 (score 10) as win.c.

Let me also record the wall tag. Candidates from walls.txt:
- cse-copy-merge: "cse merges a copy the target keeps in its own reg (G22x)" — close but here cse merges a copy and rewrites a branch.
- lreg-qty-priority: "local-alloc qty priority gives the hard reg to the other pseudo".
- global-hardreg-reserve: "the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it (G08b)" — not exactly.
- cse-copy-merge fits best: cse merges the q/temp copy and canonicalizes the temp, rewriting the branch; the target keeps the branch on $v0 because the temp is a hard reg.

A new tag could be `<pass>-<what>`: `cse-copy-canonical` — cse's make_regs_eqv prefers the pseudo temp over the hard call-result reg, so the branch is rewritten to the temp; the target's branch stays on $v0 (only a hard-reg temp keeps it). Let me use a new tag `cse-copy-canonical` and define it in the evidence.

Hmm, the walls.txt says "A new tag: <pass>-<what>, lowercase, defined in the coder's results evidence." I can add a new tag. But should I append it to walls.txt? The brief says walls come from walls.txt or a new tag; I'll use `cse-copy-canonical` and define it in the evidence. I won't edit walls.txt (not in my allowed writes: "write only under .run/P40/T11/W48/ plus appends to .run/P40/T11/moves.md"). Right — I cannot edit walls.txt. So a new tag defined in the evidence is fine.

Evidence ≤140 chars: "cse make_regs_eqv (cse.c:840) makes the pseudo temp canonical over hard $v0 and rewrites the branch; target branch tests $v0, only a hard-reg temp keeps it".

Count: ~150. Trim: "cse make_regs_eqv makes pseudo temp canonical over hard v0, rewrites branch to temp; target branch tests v0 (needs hard-reg temp = pin)". ~130. Good.

Best: 10. Tries: let me count all scored tries on item 3:
1 win, 2 z1, 3 z2, 4 z3, 5 z4, 6 z5, 7 z6, 8 z7, 9 z8, 10-19 b1-b10, 20-29 b11-b20, 30 b21, 31 b22, 32 b24, 33 b26, 34 b27, 35 b28, 36 b30, 37 b31, 38 b32, 39 b33, 40 b36, 41 b37, 42 b38, 43 b39, 44 b40, 45 b41, 46 b42, 47 b43, 48 b44, 49 b45, 50 b46, 51 b47, 52 b48, 53 b49, 54 b50, 55 b51.
So 55 scored tries. (b25, b35 compile errors not counted.)

Good, ≥30.

Let me now write win.c (b43), record results, moves, notes. Time check first.
