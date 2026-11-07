---
ts: 2026-11-06T06:33:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nxaMc4Y9HQgBuCAa0wNl
---
Best pin-kept is 5 (p_swapbt, p_u32t) — same as w3. So PARTIAL:pin isn't reachable either (needs 0).

So item 2 = WALL, best = 33 (v_s16mod, lever-free).

Hmm, wait: v_s16mod has 106 insns and score 33 — it's the best lever-free body. Good.

Let me record item 2 as WALL: `cse-copy-merge` — mechanism: plain C merges `base = tmp` (cse) so the pseudo lives across the inner loop and takes a callee-saved reg; the same hard-reg pin blocks loop.c's array-giv + div-magic hoist (107 vs 106 ins); best 33.

Hmm, the wall tag should describe the primary blocker. There are two coupled: cse-copy-merge and loop-const-hoist. I'll use `cse-copy-merge` with the evidence mentioning the loop.c coupling.

Now let me clean up the variant files (keep a couple), write the results row and moves line, and move to item 3.

Actually, disk: my shard dir must stay < 200 MB. Let me check sizes and clean the dumps (I've read them).

Let me record now.

Evidence ≤ 140 chars: "cse merges base=tmp so the pseudo lives across the inner loop (107 ins); the $2 pin both keeps move $22,$2 and blocks loop.c array-giv/div-magic hoist; best 33 (s16 mod)".

That's about 150 chars. Let me trim.

Also I should delete dmp2/dmp3/dmp dirs (I've read what I need).
