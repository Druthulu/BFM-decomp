---
ts: 2026-11-06T14:17:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BNz0WBFOneFKUCXZVaHW
---
All still 6. a1 MIXED means the reorder changed scheduling. The others still REG-caller.

Interesting: a4/a5 (i += 1 / i = i + 1) still REG-caller at 6 — did they change the ref count? Let me check a5's refs by dumping? Or maybe they produce identical code (no score change means the reg swap persists). If i = i+1 removes the increment extra ref (if any), it would lower i further, still dst wins.

Let me now try the array-index formulation, and also try adding a use of i in the setup that might survive.

Actually, let me reconsider the numbers: i=11, live 39; dst=11, live 36. I need +1 ref on i or -1 on dst.

Wait — what about the `slt` at the bottom: `slt $2,$10,$12` uses i and n. What if I write the condition as `(i - n) < 0`? gcc folds to `i < n`. Or `while (i <= n - 1)`? That would emit `addiu n-1` + slt with different operands. No.

What about `while (i < n)` where n is a signed compare — fine.

Hmm. Let me look at whether there's a way to make the store use i as an offset while keeping the pointer dst. E.g.:
```
*dst = out;   ->   dst[i - i] = out;
```
`i - i` folds at tree level. What about `dst[0 * i]`? folds.

What about `*(dst + (i & 0))`? folds.

What if the use of i is genuinely needed but combine can eliminate: e.g., 
```
s32 k = i;   // copy
...
dst[k] = out;   // uses k, but k == i
```
This adds a copy instruction (`move`). cse would propagate k=i and delete the copy. Since cse2 runs before flow, it's gone. No.

Hmm, unless the copy is across a block boundary where cse can't propagate but combine can... unlikely.

Let me think about dst reduction via the STORE. The store `*dst = out` uses dst. What if the store is written through a different expression that still uses dst once? e.g., `*(u16 *)dst = out` — same.

What if I combine the store and increment: `*dst++ = out;`? RTL: store uses dst, then dst = dst + 2. Same refs.

Hmm.

What about making dst's live range LONGER (lowers priority)? dst live=36. If extended to 40, priority 33/40=0.825 < i 0.846. How to extend dst's live range without code change? Add a use of dst AFTER the loop (dead use) — but it must survive flow's liveness (flow computes live_length before dead code elimination?). A use after the loop would extend live_length. But it would emit an instruction. Unless it's a use that combine/flow removes after counting... flow is the pass that computes live_length; a use after the loop would be counted. Then the instruction must be removed later (by combine? combine doesn't remove arbitrary insns; sched doesn't; reload doesn't). So no.

Wait — actually, dead code elimination: where does gcc 2.7.2 delete dead code? In jump.c `jump_optimize` (before flow) and in `delete_dead_code`? Also flow's `mark_used_regs` marks only used insns; unused insns are deleted in `flow_analysis`? Let me check: flow.c `flow_analysis` deletes insns not marked `block_live`? There's `delete_unreachable_blocks`? Hmm.

Actually, a dead store/use that has no side effect but is in a live block is NOT deleted by flow. It would remain -> extra instruction.

OK. Let me try a completely different approach: change the loop so that the condition uses i in a way that requires a value that's already computed. For example, the loop counter could be `i` but the loop bound expression could reference i... no.

Alternatively — and this is promising — change the ROLES: make `i` the destination pointer's counter and `dst` the index? No.

Let me look at the actual target source hints: the comment says the src keepalive keeps "src above i, below the mfhi temp" — that's sched1 priority. And the i keepalive "lifts i over dst in the $t2 race". So the author needed +3 refs on i. Maybe the real-C crack is to make the loop use `i` in a way that naturally adds 3 refs, e.g., as the loop bound index.

Let me try the array-index formulation now. I'll write it.

Variant b1:
```
                    n = arg0->w * arg0->h;
                    i = 0;
                    src = arg0->data;
                    dst = src + n;
                    if (n > 0) {
                        do {
                            u16 px;
                            s32 r, g, b, out;
                            px = src[i];
                            ...
                            dst[i] = out;
                            i++;
                        } while (i < n);
                    }
```
But `src[i]` and `dst[i]` with i as an index: gcc/loop.c strength reduction might produce exactly the pointer increments and eliminate the index multiplications. Let me test.

Also b2: keep src pointer but index dst: `dst[i] = out;` with dst = src + n? That would be dst[i] = *(dst + i*2) — but dst doesn't advance, so the address changes. Not equivalent unless dst = src+n and i indexes... Actually `dst[i]` where dst=src+n and i counts 0..n-1 gives src+n+i, not src+n (constant). Wrong semantics.

So b1: src[i] and dst[i] where dst = src + n (the second half). Then `dst[i]` = src[n+i]... and src[i] = src[i]. So the transform writes to src[n+i] from src[i]. Correct! And i is used in both.

But then the pointer increments would be strength-reduced by loop.c. Let me test.

Let me write b1.
