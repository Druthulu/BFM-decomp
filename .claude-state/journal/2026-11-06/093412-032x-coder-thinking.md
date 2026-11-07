---
ts: 2026-11-06T16:34:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vKPF13WmKBACx4NHspHL
---
c38 score 5! c39 score 5. Interesting: reordering block1's calls to (D2D44, D468FC, D2AA0, D2D8D4) prevents the merge (317 vs 318, only missing li v0,1 + 4 order diffs = 5). So the merge is prevented by the reorder, and the residual is the reorder itself (4 insns) + 1.

c43 (both reordered) merges again (307) → 24.

So the merge can be prevented at the cost of 4 insns of order. Best lever-free so far = 5. That's a much better "best" for the WALL.

Can we get the merge prevented with fewer than 4 bytes-differing insns? c18 was (D2D44, D2D8D4, D468FC, D2AA0) → 15 (8 extra?). Hmm c18 315 ins; c38 317 ins. The merge is prevented in both; c38's order differs from target by 4 positions? Let me think: target block order = D2D44, D468FC, D2D8D4, D2AA0. c38 = D2D44, D468FC, D2AA0, D2D8D4. Only two insns swapped (D2AA0 and D2D8D4) → but calls + delay nops = 4 insns differ. Score 5 = 4 order + 1 li.

Can we prevent the merge with a *single* differing insn while keeping the rest in target order? The reorder must differ from block2. If block2 stays target order and block1 is target order except one call moved, then at least 2 insns (call+nop) differ → score ≥ 3 (2 + 1). 

What about making one block's *delay slot* differ? The calls' delay slots are nops (from sched). If in block1 we could get the scheduler to put something else in a delay slot... that's the target's actual layout though.

Alternatively, use a real-C construct that makes one block's RTL differ by exactly one insn that emits 0 bytes... that's the barrier again.

So the WALL best is likely 5. Good enough: WALL with best 5, evidence: barrier→jump2 cross-jump merges the two identical 4-call blocks (10 ins); only a byte-changing reorder prevents it; keepalive→expand void return (li v0,1). Tag: jump2-crossjump-arms.

Hmm wait, but can we keep the target's order AND block the merge via the *if condition* making one block reachable differently? E.g., in block1, use `goto ret` vs fallthrough? Target has both j.

What if block1's `goto ret` is written as `return;`? No — the function continues after (no, the goto goes to the ret label at the end, which does func_80010A98(); v0r=1). A `return;` would emit jr ra directly, different bytes.

OK. Let me record item 1. Tries so far: 42 + 6 = 48 scored, time: started 09:26:57, now let me check. Need ≥20 min. Let me check the time and also verify c38 is lever-free (grep for asm/register).

Also I should double check c38/c39 with the diff to confirm it's the merge + li only.
