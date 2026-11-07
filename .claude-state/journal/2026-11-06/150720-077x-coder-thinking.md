---
ts: 2026-11-06T22:07:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JS0TJBd2rY6IkotuzS9e
---
w20 = 55 ins, score 26 — no move, and the whole register bank shifted (because iv2c is now live longer, adding pressure).

Not promising.

OK, decision: WALL for item 3. Best lever-free score = 4 (w13).

Wait, but w13's body is a restructured version (inverted copy). Is it "lever-free"? Yes: no asm, no launder. It has the existing pins.

Hmm, but is w13 really the best? Let me double check there's no lower score. All the b* were 5, w13 was 4, w20 26, w11 20, w9/w12 14.

So best = 4.

Now: the results row for item 3: WALL, best 4, tries = 30 (scored candidates). Let me count exactly: w1,w2,w3,w6,w7,w8,w9,w10,w11,w12,w13 = 11; b1..b19 = 19; w20 = 1 → 31. Good, ≥30.

Wall tag: from walls.txt — `combine-copy-merge` (combine merges a reg copy the target keeps). But the actual pass here is cse (cse1 propagates the copy and deletes it). There's also `cse-copy-merge` in walls.txt: "cse merges a copy the target keeps in its own reg (G22x)". That fits better: cse propagates iv2c == iVar2 into the compare.

Evidence: "cse1 make_regs_eqv propagates iv2c==iVar2 into the compare and deletes the copy (55 ins); the target's move is the launder's reload tie; combine also merges the sign-extend variants" — ≤140 chars.

Let me count: "cse1 propagates iv2c==iVar2 into the compare, deletes the copy (55 ins); target's move is the asm tie; combine merges every sign-extend/do-while variant" ≈ 150. Trim: "cse1 equates iv2c==iVar2, rewrites the compare and drops the copy (55 ins); target move is the asm's reload tie; sign-extend/do-while/2nd-use variants all 55" — ~150. Let me trim more: "cse1 rewrites the compare to iVar2 and deletes the copy (55 ins); the target move is the asm reload tie; 31 lever-free bodies, best 4 (w13 inverted copy)" ≈ 140. Good.

Now: win.c for the item = the best lever-free body (w13). Hmm — but should win.c be the best lever-free or the original partial? The DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0". For a WALL there's no such requirement. The brief says "WALL (best = lowest score of a lever-free body)". I'll copy w13 → win.c.

Hmm, wait. Actually, is that wise? If the expert later wants to continue from the best body, win.c = best is helpful. Yes.

Also, I should clean up the dump dirs (disk): dump_w2, dump_q1, dump_w6, dump_b1 under the item dir. And the --keep scratch at .run/P36/engine/score/... (that's a shared tool dir; the brief says --keep scratch is removed after use — I should remove that p1/p3 dir).

Let me check disk usage of my shard dir and clean up.

Also the results.tsv row and moves.md line and notes.

One more check: the item's `kinds` file says `launder`; my win.c (w13) has no launder. Good.

Let me do the cleanup and then write the files.

Actually hold on — before finalizing the WALL, let me reconsider one more possibility that I haven't tried: what if the copy is `iv2c = iVar2` and we place the *compare* before the copy... no.

What about making iv2c a **struct member copy**? no.

What about making the compare use `iv2c` via a *pointer*? no.

OK. One more: what about `one` NOT pinned (drop the pin)? The pin $2 is an existing lever; dropping it is allowed. If `one` is a plain int, the compare might allocate `one` to a different register, and iv2c might take v0... but the target needs one in v0. Hmm, and cse would still propagate.

No.

Let me finalize.

Actually, wait. Let me reconsider the score-4 body (w13) once more — it's tantalizingly close. The diff was exactly:
- 21: `li v0,1` vs `li a0,1`
- 25: `addiu v0,v0,1` vs `addiu a0,v0,1`
- 27: `move a0,v0` vs `move v1,a0`
- 29: `beq a0,v0` vs `beq v1,v0`

In w13, iv2c=v0, iVar2=a0. If iv2c were v1 and iVar2 a0, then:
- 21: `li v1,1` (iv2c = 1) — target `li a0,1` (iVar2 = 1). ✗ still.

So w13's shape is fundamentally different (the then arm sets iv2c, not iVar2). Not fixable by register shuffling.

The correct shape needs the then arm to set iVar2 = 1 (li a0,1) and the join to copy iv2c = iVar2.

OK. WALL.

Hmm, although... one more idea just came: what if the then arm sets `iVar2 = 1` AND the join copies, but the copy is `iv2c = iVar2` where iv2c is a variable that is ALSO assigned in the then arm... no.

Alright, finalize the WALL.

Actually, let me reconsider whether to record PARTIAL instead. The row kinds = launder. If I keep the launder, the result is PARTIAL:launder (which is what the item already was) — that would be a no-op for this task. The task wants me to remove it. Since I can't, WALL is right (best = 4, lower than the partial's 0? no — the partial scores 0!).

Hmm wait. The PARTIAL body (prev_win) scores 0 but keeps the launder. The WALL's "best" is the lowest score of a LEVER-FREE body = 4. That's the right metric.

Let me now write everything.

1. Copy w13.c → win.c.
2. results.tsv row.
3. moves.md line.
4. notes.md update.
5. Cleanup dumps.

Let me do the cleanup first (disk), then the row.

Disk check: my item dirs have dump dirs. Let me rm -rf them explicitly (not with a glob that could match win.c — I'll list explicit dir names).

Also remove the --keep scratch dir .run/P36/engine/score/ov_MAIN_012__func_80177EA4/p3? That's outside my shard. The brief says "--keep scratch is removed after use". Let me check if it exists and remove it. But it's a shared tool path (.run/P36/engine/score/...) — removing it is what the tool expects. Actually, `--keep` prints the path and says the caller should remove it. Let me remove that specific dir (the p3 subdir).

Hmm, careful: other coders may be using .run/P36/engine/score concurrently. I'll remove only the ov_MAIN_012__func_80177EA4 dir (mine).

Let me do it.
