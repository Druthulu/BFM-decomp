---
ts: 2026-11-06T17:01:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_d0EJHbUdVKVkxmBcUg5O
---
z4 (natural q%4, n = q%4) gives 119, with the first computation's temp in v0/v1 (not s0) and 2 extra insns in the second.

Hmm, worse. Note the first computation now uses v1/v0 differently.

Let me reconsider. Maybe the answer is to make n a *function-scope* variable whose live range crosses a call because it's used in BOTH velocity computations *without being killed*. For that, the second computation would need to use the first n... 

Wait, actually, look at the target again: s0 is used for n in comp1 (8e94-8ea4), m in comp1 (8eac-8ebc), n in comp2 (8ecc-8edc), m in comp2 (8ee4-8ef4). Between comp1's m and comp2's n, there's a `jal rand` (8ec0). The register s0 holds m across that call (m is stored at 8ec4 after the call). Then n2 is born in s0 right after.

So s0 is the "m/n" register, and m is naturally s0 (live across calls). n is short-lived but local-alloc picks s0 because... at n's birth in comp2 (8ecc), s0 is still live with m? m was stored at 8ec4 (after the jal at 8ec0), so s0 dies at 8ec4. Then n2 is born at 8ecc. v1 free? At 8ecc, v1 holds... `andi v0,v0,1` at 8ee8 later; at 8ecc v1 is free. So find_free_reg would pick v1.

Hmm, unless local-alloc's qty ordering makes s0 chosen because it's a "copy suggestion" from m? n2 = q (a copy from v0), no suggestion.

OK, let me try yet another approach: make the `%4` temp and m the SAME variable. E.g.:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
n = (q - n) << 16;      /* reuse n for the result */
if ((rand() & 1) == 0) n = -n;
CAST_WIDTH(s32, ent, 0x10) = n;
```
Now the variable n holds the result (live across the sign call → s0!). And the temp part is also n (same pseudo, multi-set). Then n is live across the sign call → callee-saved → s0. And the `%4` temp's early range: n is set to q at the start, modified, then set to the result; the whole pseudo n has a range crossing the sign call → n_calls_crossed > 0 → all of n in s0!

That's promising and natural C. But note the target stores `m` — using n instead of m changes nothing semantically. The variable m would then be unused (could remove it). Let me try:

```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
n = (q - n) << 16;
if ((rand() & 1) == 0) n = -n;
CAST_WIDTH(s32, ent, 0x10) = n;
```

The target's RTL for this: n set at the move (delay slot), addiu, sra, sll, subu, sll, negu, store. The liveness: n is set, used, set, used... The pseudo n has multiple sets; its live range crosses the sign call (the value (q-n)<<16 is live from the subu/sll to the store, crossing the sign call). So n crosses a call → s0.

But the target's `%4` temp part: `move s0,v0; addiu s0,v0,3; ...` — in this source, the temp IS n (the same variable), so it's s0. 

Let me test this variant.
