---
ts: 2026-10-22T00:14:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_MECuhxkdtdCc2ufxAbnW
---
Worse (19, and the frame grew to 40 bytes because x and y are now live across the call).

So init-at-decl is wrong (x/y become live across the call → callee-saved regs → a bigger frame).

OK. I'm way over time. Let me now do the bookkeeping and finish. Summary of results:

1. func_801627E8 (item 1) — MATCH (prior run, already in results.tsv).
2. func_80180D54 — MATCH (dead-reset, u1.c) — score 0.
3. func_801815D4 — MATCH (dead-reset, w1.c) — score 0.
4. func_8018483C — WALL, best 5 (the missing `move s0,v0`).
5. func_8017DA30 — WALL, best 4 (the ORDER residual).
6. func_80184828 — WALL, best 1 (the commutative operand order).
7. func_8017D81C — WALL, best 20.

Hmm, wait. Before finalizing 8017D81C, let me try ONE more thing, since the v1 residual was interesting: the x/y materializations are early in the target.

Hmm, what if x and y are assigned BEFORE the call `func_8001C2C4(v)`? Then they'd be live across the call → callee-saved ✗ (as v2 showed).

Hmm. What if the assignments stay after the call but the constant propagation is prevented by making the value's use non-foldable?

Hmm, one more idea: what if x's assignment is `x = -0x680;` and x is ALSO used in a `p[3] = 0`-like context? no.

Hmm: what if the stores use x in a way that requires a register: e.g. `D_80192CE0 = x;` — the store's value is x. gcc's constant propagation: it forwards the constant -1664 to the store → `sw v0,-1664(at)`? Hmm, no: the store's value must be in a register → `li v0,-1664; sw v0,0(at)`. gcc's cse would create ONE pseudo for the constant and reuse it ✓ (that's what mine does).

So in mine, the pseudo is born at the first use. In the target, at the assignment.

Hmm, what if the target's version had x's pseudo live from the assignment because the LAUNDER read it ✓ (the launder's input).

So without asm, the only way is to have x read somewhere between the assignment and the first store — with no code effect. Hmm.

What about a `do { } while (0);` with x inside? e.g. `do { v = x; } while (0);` — hmm, v = x would be a copy (an insn) unless v is dead. Hmm, if v is dead, gcc deletes the copy → the pseudo's lifetime shrinks ✗.

Hmm, what about `do { (void)x; } while (0);`? — a no-op statement; gcc deletes it entirely.

OK, WALL for 8017D81C.

Hmm, hold on. Let me reconsider the score 20 residual for v1 once more: the main issue is the position of the li's (18-19 vs 39-40) and the regs (v1/a1 vs v0/v1). Hmm, 20 points.

Hmm, what if the ORDER of the x/y/z assignments is changed (e.g. y before x)? The target: v1 = x (-1664) at 18, a1 = y (-3712) at 19, a0 = z at 20. So the source order x, y, z ✓ (as is).

Hmm, but in mine, the materialization happens at the uses, so the order follows the use order: D_80192CE0 = x (39), D_80192CE4 = y (40), D_80192CE8 = z (41?) hmm, and z is at 18 (pinned).

Hmm, so in mine, x → v0, y → v1. In the target, x → v1, y → a1. Hmm! The reg choice differs: the target uses v1 and a1; mine v0 and v1.

Hmm, and the "register pairs (mine -> target, count): v1->a1 x2" — hmm, that says mine's v1 ↔ target's a1 (2 places) — hmm, so mine's v1 = the target's a1 = y ✓, and mine's v0 = the target's v1 = x (not listed since the diff's pairing is partial).

OK. So both the position and the regs differ. The launder chose v1/a1/a0.

Hmm, so the launder's asm outputs were allocated v1, a1, a0 — hmm, interesting: a1 and a0 for y and z. Hmm, why would the asm's outputs be a1/a0? Because gcc allocates the asm's output regs considering the subsequent uses? Hmm.

OK, WALL. Let me now write everything up. Time to finish.

Let me now:
1. Write win.c for each MATCH item (80180D54 → u1.c; 801815D4 → w1.c; 801627E8 → win.c already exists).
2. Write notes.md per item.
3. Append rows to results.tsv.
4. Append lines to moves.md.
5. Write the log at phase-ends/current/logs/T11.cG10r.md.
6. Clean up the scratch (the cands dirs, the big files).

For the WALL items, the result is "WALL" with best = the lowest score of a lever-free body, and the wall tag.

Wait — for the WALL items, should I still write a win.c? The brief says "each MATCH/PARTIAL has its win.c scoring 0". For WALL, no win.c is required, but I could keep the best candidate. Hmm, "Per item append exactly one row to G10/results.tsv". For a WALL, the "best" = the lowest score of a lever-free body ✓ and the wall tag + evidence.

Let me determine the wall tags:
- 8018483C: new tag "cse-const-addr-copy"? Hmm. The mechanism: the target keeps a COPY of the constant address (lui/addiu into v0 then `move s0,v0`); gcc-2.7.2's cse forwards the pseudo's reg_equiv so the copy is coalesced away. Hmm, the existing tag "cse-const-addr" is: "cse folds or substitutes a constant/absolute address the target keeps base-relative". Not the same. A new tag: "cse-const-addr-copy" — hmm, per the format `<pass>-<what>`: "cse-const-addr-copy" ✓ (lowercase).
- 8017DA30: the existing tag "sched1-argcopy-hoist" ("sched1/reload_cse: arg-copy hoisted/sunk across the call setup") fits ✓ — the target hoists the call's arg setup to the top of the block; ours sinks it to just before the call and puts the a1 setup in the delay slot. I'll use the existing tag "sched1-argcopy-hoist".
- 80184828: the residual is a commutative operand order. Existing tags: "sp-stack-switch", "no-c-spelling", "hand-asm", "cse-const-addr", "sched1-argcopy-hoist", "sched1-birth-boost", "callee-saved-order", "flow-unused-result". Hmm, "sched1-birth-boost: sched1 vs local-alloc: birthing-insn priority boost against a local-alloc constant (T10 S17)". Hmm, our residual is the commutative operand order — a new tag: "commutative-swap" hmm, the format is `<pass>-<what>`: the pass here is combine/combine_regs → "combine-commutative-swap"? Hmm, or "caller-saved-swap". Let me use "combine-commutative-swap" (lowercase ✓).
- 8017D81C: the residual: the constant holders (x, y) are materialised at their first use instead of at the assignment (the launder's read of the variable keeps the pseudo alive at the assignment). A new tag: "cse-const-holder" hmm. Or "sched1-const-holder"? The mechanism is cse's constant propagation (the holder's pseudo is born at the use) + the birth boost. Let me use "cse-const-holder" — hmm, per the format `<pass>-<what>`: "cse-const-holder" ✓.

Hmm, and the evidence fields (≤140 chars): "gcc pass + mechanism".

Now the results.tsv format: `dir file func kinds result best tries wall evidence` (tabs).

For MATCH rows: wall = `-`, best = 0.
For WALL rows: result = WALL, best = the score, wall = the tag, evidence = the mechanism.

Let me count the tries:
- 80180D54: candidates tried: a1, b1 (prior), t5, d1, c1, c2, u1, orig, ... let me count MY tries: orig (baseline, launder), a1, b1 (prior run's), t5, d1, c1, c2, u1, x1, x3, v2, v4, v9, v11, v12 = let me count: 15. Hmm, "tries" = the number of candidates scored. Let me count precisely:
  1. a1.c (prior)
  2. b1.c (prior)
  3. orig.c (baseline, 0 with the launder — not a lever-free try, hmm)
  4. c1.c
  5. c2.c (written but not scored! hmm — I wrote c2 but scored c1 only) — I did NOT score c2. Let me not count it.
  6. d1.c
  7. t5.c
  8. u1.c → MATCH
  So the lever-free tries: a1, b1, c1, d1, t5, u1 = 6. Plus the baseline orig. Let me say tries=6.
  Hmm, "tries" — I'll count the lever-free candidates scored.
- 801815D4: 1 try (w1) → MATCH.
- 8018483C: x1, x3, v2, v4, v9, v11, v12 = 7 tries.
- 8017DA30: v1, v2, v3, v4, v7, v8, v9 = 7 tries.
- 80184828: v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11 = 11 tries.
- 8017D81C: v1, v2 = 2 tries.
- 801627E8: (prior run) — the results.tsv row already exists with tries=46. Skip (don't add a second row).

Now, the results.tsv already has a header + 1 row. I need to append 6 rows.

Let me now write the files. First, the win.c files:
- 80180D54: win.c = u1.c
- 801815D4: win.c = w1.c
- For the WALL items: no win.c required. Hmm, but maybe I should keep the best candidate as a reference. The brief says "each MATCH/PARTIAL has its win.c scoring 0" — only MATCH/PARTIAL need win.c. I'll skip win.c for the WALLs but keep the candidate files.

Let me write the win.c files and the notes.md files, then the results rows, moves.md lines, and the log.

Let me be efficient. First the win.c files (Write tool).
