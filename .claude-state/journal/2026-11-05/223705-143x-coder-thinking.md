---
ts: 2026-11-06T05:37:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iSv0LVshemTvPwIPBYwh
---
Still 2. It's 22:36, item 3 at 18 min. 2 more minutes.

Let me look at l4's diff once more: the extra `sh a0,24`. Maybe I can make the fence a *load-only* of a location that's a store to a different memory... no.

Actually, what about making the extra store get *merged* with store3 by placing the fence right next to store3? l13 did that (b[0]=u88 duplicated right after store3) → score 3, 43 ins. Hmm, that made the count 43 (the fence and one other store deleted).

What if the fence `b[0]=u88` is placed right after store3 and the b[1]=b[1] fence between store2/3? l16 did something like that → 31.

OK. I'll record the WALL with best 2 (l4).

Wait, hold on. Let me reconsider l4: it has 46 ins (target 45) and one extra store. If that extra store is a duplicate of store3, and the target has exactly 6 b stores, then l4 has 7. The diff shows only that one extra. So if I could get it deleted, it'd be 0.

The extra store is `sh a0,24` — the fence `b[0] = u88;` placed between store5 and store6 in the source. The scheduler moved it up to position 24 (right after store3), making it adjacent to store3's `sh a0,24`? If they're adjacent duplicates, cse should delete one. But cse runs *before* sched1, so at cse time the fence is far from store3 (not adjacent) — cse's redundant-store detection might require adjacency or memory tracking. Hmm.

What if I place the fence in the *source* right after store3 (l13)? Then at cse time they're adjacent → cse deletes one → but then the fence is gone and store4/store5 die (43 ins, score 3).

The fence must survive cse to fence flow, then be deleted later. But cse is the pass that deletes redundant stores; if it deletes the fence, it can't fence flow (which runs after cse).

Unless flow runs *before* cse! Let me check the pass order: in gcc 2.7.2's rest_of_compilation, `flow_analysis` (life_analysis) runs BEFORE cse? Let me check: the sequence is roughly:
1. jump_optimize
2. ... 
3. `life_analysis` (flow) — deletes dead stores
4. cse
5. ...
Actually, `reg_scan` + `flow_analysis` runs early (to compute register info for cse). Then cse. Then more flow.

If the dead-store deletion happens in the EARLY flow pass (before cse), then the fence only needs to exist at that point, and cse can delete it later! That's what l4 shows: the fence survived to the output, though. Hmm.

So the fence wasn't deleted by cse. Why? Because cse doesn't delete stores that are redundant? Maybe cse doesn't do redundant-store elimination at all; the deletion I saw earlier was flow's dead-store (last_mem_set).

If cse doesn't delete stores, then the fence can't be removed after flow. So any fence store survives → +1 insn → not a match.

Unless the fence is deleted by flow itself: flow deletes a store if it's dead (last_mem_set equal). The fence `b[0]=u88` is followed (in program order) by `b[2]=u8C` (different) → not deleted. And its value equals the current memory content, but flow doesn't check values.

Hmm, what about `combine`? It can delete redundant insns. Or `dbr`/`reorg`? No.

What about `cse2` (the second cse)? Maybe cse2 deletes redundant stores. If the fence survives cse1 and flow, cse2 might delete it. But l4 shows it survived to the output. Hmm.

OK. WALL, best 2 (l4). It's 22:37; item 3 at 19 min. Let me wait one more minute and record.

Actually, let me try one last thing: a fence that is a *dead store to a dummy local* — flow would delete it (if a later store to the same dummy follows). E.g.:
```
dummy = 0;   (fence)
... 
dummy = 0;   (later store to the same location)
```
Flow's reverse scan: the later dummy store sets last_mem_set=dummy; the earlier dummy store compares equal → deleted! And in between, the b stores are protected (last_mem_set changes to dummy after the fence).

But the later dummy store itself must also be deleted... it would be the only remaining store to dummy. Unless it's before another dummy store. Circular.

Hmm, but what if the dummy is stored twice at the END (after all b stores)? Then the earlier dummy store (the fence) is deleted by flow, and the later one remains → +1 insn. Still +1.

What if the dummy is `b[1]` (which has a real store earlier)? The fence `b[1] = b[1]` and the real `b[1] = ...` earlier: flow's reverse scan: the real b[1] store is BEFORE the fence in program order? Order: b[1] = expr (early), ..., fence b[1]=b[1], ..., store3. Reverse: store3 (last=b0), fence (b1 vs b0 → kept, last=b1), ..., the real b[1] store (b1 vs b1 → deleted!). That would delete the REAL b[1] store (which the target needs). Bad.

Unless the real b[1] store is protected by another fence. Circular.

OK. WALL. Let me record item 3 now (19-20 min by the time I finish writing).

Let me write notes, results, moves.

Tag: `flow-dead-store` — new tag. Evidence: flow.c insn_dead_p (last_mem_set + rtx_equal_p) deletes a repeated store to the same frame-relative slot; the barrier's memory clobber clears last_mem_set; best 2 (l4: fence store survives, +1 insn).

Let me record.
