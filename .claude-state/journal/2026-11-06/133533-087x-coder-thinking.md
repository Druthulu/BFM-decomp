---
ts: 2026-11-06T20:35:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ff91kEqidLb6rQfzvBv1
---
The initial RTL (expand) is:
- 95: a0 = s0
- 98: r = -524288
- 101: v0 = 7
- 103: sh unk2
- 106: a0 = a0 (a self-copy! from the `q` register var?)
- 108: a1 = r
- 110: call

So the constant IS materialized at its source position (insn 98), and then `a1 = r` (insn 108) copies it to the arg register at the call. Later, combine/cse replaces the copy `a1 = r` with the constant itself and deletes insn 98 (since r dies). That's why the .lreg shows the const at 108.

So the mechanism: cse/combine propagates the single-use constant into the call arg copy. Specifically, `a1 = r` (insn 108) has a REG_EQUAL note (the constant), and combine/cse substitutes.

The launder makes r opaque, so `a1 = r` can't be replaced by the constant; the copy `move a1,r`... wait, but the target has `lui a1,0xfff8` and no move. Hmm: in orig (with the launder), insn 100 = a1 = const (-524288), insn 102 = the asm output a1. So the launder made r's materialization go directly into a1 (r's pseudo got a1), and the asm then re-ties a1.

Hmm, so in orig the constant insn writes a1 directly (the pseudo r was coalesced to a1), then the asm. In nolau, expand emitted `a1 = r` copy and combine folded it into `a1 = const`.

Real-C idea: prevent the copy from being folded by making r live after the call? If r were used after the call, the copy couldn't be deleted and the const would stay at 98. But then we'd have an extra use (an instruction or a dead use that survives).

What if r is used after the call in a *dead* way that survives because... no.

What if we use r after the call in a way that's free? For example, in the other arm? Different scope.

Hmm, what if we declare r at function scope (outside the if/else) and assign it in each arm? Then r might be live at the join... but its uses are per-arm.

What if we assign r in the then arm and also read it after the join (after the if/else) in a way that's free? E.g., `if (r) { }` — folded (r is constant).

Hmm.

What if the call's arg is written as `func_8012B178(q, r)` and we make r's pseudo NOT die at the call by adding a second use *inside the same arm after the call* that emits no code... impossible.

OK, I'm confident: WALL.

Wait, actually — one more idea. What about making the call's arg a *different* variable that is not constant-propagated because it's assigned from r in a way that creates a real copy? E.g.:
```
s32 rr = r;
func_8012B178(q, rr);
```
That adds a copy insn (a1 = rr or a move) → +1 insn. No.

What if `q` and `r` are swapped in the arg list and the callee... no.

OK. WALL.

Let me now also double check: is the score 10 the "lowest score of a lever-free body"? p2b=6 keeps the launder (not lever-free). p1b=8 keeps the barrier (not lever-free). Lever-free best = 10. Yes.

Set win.c = nolau.c (score 10).

Hmm, but wait: for a WALL, should win.c be the lever-free body? The brief: "DONE WHEN: every item of W49/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0." For a WALL there's no requirement that win.c scores 0; but writing win.c = the best lever-free body is sensible.

Now, the results row: dir, file, func, kinds=barrier,launder, result=WALL, best=10, tries=30, wall=dbr-delay-fill, evidence.

Evidence ≤140 chars: "reorg fills the bnez delay slot with the join's xori (stop_search_p stops only at asm); cse folds the 1-use r const into the call arg, lui lands in the jal slot". Let me count: ~145. Trim: "reorg fills bnez slot with the join xori (only asm stops stop_search_p); cse folds the 1-use r const into the call arg so lui lands in the jal slot". ~137. Good.

Hmm, but the wall tag: two mechanisms. I'll use `dbr-delay-fill` (existing tag) and mention the const fold in evidence. Alternatively a new tag `dbr-fill-const-arg`. The brief allows a new tag `<pass>-<what>`. Since there are two independent walls, one tag is limiting; I'll use `dbr-delay-fill` as the tag and note the second mechanism in evidence.

Hmm, actually — maybe I should double check one thing: does the *barrier* cluster also have a wall tag in walls.txt? `dbr-delay-fill dbr delayed-branch fill takes a fall-through insn the target leaves out of the slot (G18x)`. Yes, exactly cluster 1.

And cluster 2's tag could be `combine-argcopy-sink` (combine folds 1-use pseudo into call-arg set at the call). It's about combine folding a 1-use value into the call arg. That matches. So maybe the row should be `dbr-delay-fill` and the evidence mentions combine-argcopy-sink.

Let me write the notes with both mechanisms.

Time: item 3 started 13:19, ending ~13:55 → 36 min. Slightly over 30 min, but we're within the wall criteria. Let me record.

Actually, let me do a final check that win.c=nolau.c scores 10 and contains no barrier/launder asm.
