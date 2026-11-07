---
ts: 2026-11-06T14:17:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VpY3rxZh9eeRVYJbrMYL
---
b1 gives 52 (COUNT, 239 ins) — much worse. The array-index form changed the code (loop.c didn't strength-reduce as hoped; it created different induction variables). So that's not it.

Let me step back and think.

Actually, maybe the key is that the extra refs don't need to produce instructions: the asm statements add refs to the reg without any instruction. Real C cannot do that directly. BUT, the refs are counted by flow from RTL. If I can create a use of i in an RTL insn that later gets deleted (after flow), that works. What deletes insns after flow?
- combine: deletes the insns it combines (replaces with a new insn).
- sched1: doesn't delete.
- reload: may.
- sched2: doesn't.

So combine must fold our use away. combine operates on a 3-insn window and does try_combine, substituting SET_SRC of insns into users. If I write:

```
i = 0;
...
dst = src + n + i;   // hmm
```

Wait, combine's window is limited to consecutive insns and it does `try_combine` when insns are related by data flow. If `i=0` and `dst = ... + i` are close and not separated by a branch, combine could fold. But cse2 runs before flow and would fold i=0 first (cse does constant propagation globally). Unless cse can't because of the branch between.

Key: `i = 0` is in block 13, and the use would be in block 13 too (same block, after i=0). cse2 would fold it. If the use is in block 14/17 (different block, after a branch), cse2 likely won't propagate the constant (cse doesn't do cross-block constant propagation except via EBB? Actually cse does propagate across blocks if the value is "not killed" — cse's `cse_basic_block` handles a basic block, and there's `cse_end_of_basic_block`; cross-block propagation only within extended basic blocks (no labels/jumps)). A branch (blez) ends the EBB, so i=0 from block13 won't propagate into block14. So cse2 can't fold a use of i in block14.

Then combine (after flow): combine works within a basic block and can use `reg_last_set_value`? Actually combine can fold a known constant if the set is in the same block and within the window (3 insns). But block14's start is far from i=0 (which is in block13). So combine won't fold a use of i in block14 either.

Hmm. So a use of i in block14 would emit an instruction and stay.

What if the use of i in block14 is folded by the *scheduler*? No.

OK, so adding a ref is hard. Let me look at reducing dst's refs instead.

dst refs = 11:
- set in block13 (depth2): +2
- store use in block17 (depth3): +3
- increment set+use in block17 (depth3): +6

To reduce by 1, I need to remove one occurrence or lower its depth.

Idea: Move the `dst = src + n;` into block 14 or 17? That changes code (the addu would move).

Idea: Make the store's use of dst count at depth 2 instead of 3? The store is inside the do-while (depth3). Can't change without moving the store out of the loop.

Idea: reduce the increment occurrences. `dst++` has set+use = 2 occurrences. What if dst is incremented via a form that yields only 1 occurrence? E.g., `dst += 1` -> same RTL. `dst = dst + 1` -> same. No way in C to increment a pointer with one RTL occurrence.

Hmm, but wait — what if we eliminate the increment by folding it into the store addressing? Like `*dst++ = out`? Same RTL.

What if the store is `dst[i] = out` and dst is NOT incremented? Then dst has: set (block13, +2) and use in the store addressing (block17, +3) = 5 refs, no increment. But the address would be `dst + i*2` each iteration -> extra instructions (sll + addu), unless loop.c strength-reduces. b1 tried dst[i] and got COUNT 52. But b1 also used src[i]. Maybe using dst[i] alone (with src as a pointer) would be better? Let me try: keep `px = *src; src++;` and `dst[i] = out;` (dst = src+n fixed). loop.c might strength-reduce dst[i] into a pointer. Hmm, b1's output showed `sh a1,0(t0)` with `addiu t0,t0,2` — it DID strength-reduce dst[i] to a pointer, but the induction variable was a different pseudo (t0) and i (t2) was incremented separately. The issue was the register numbering and the extra `addiu t2,t2,2` (i*2?) Actually the diff showed `slt v0,t0,t5` (comparing the dst pointer to something) — it changed the loop condition to compare the dst pointer. Not good.

Let me look at b1's actual loop to understand. Actually, score 52 is far; not worth it.

New idea: reduce dst refs by making the *initial* `dst = src + n` a copy that cse eliminates? If dst is defined in block13 and used in block17, its def counts. If instead dst is initialized inside the loop... no.

Hmm.

Let me reconsider the priorities. Maybe the live_lengths can be shifted differently. If I add a use of i that extends i's live range but also increases refs... no.

Wait, actually: maybe I can make dst's live_length LONGER by moving its definition EARLIER (before i=0, or before the mult). The target has `dst = src + n` AFTER `mflo n` and after `blez` (in the delay slot of blez!). The instruction `addu $11,$9,$2` is in the blez delay slot. If I move the C statement `dst = src + n;` earlier (e.g., right after `src = arg0->data;` and before `i = 0`), the codegen might still place it in the delay slot (sched1/reorg), but dst's live range in the RTL (before sched) might change? Actually flow's live_length is computed on the RTL after sched1 (since sched1 runs before flow). The order: flow is at 2983, sched1 at 3033. Wait! flow (2983) runs BEFORE sched1 (3033)! Let me recheck:

Line 2983: flow_analysis
Line 3004: combine_instructions
Line 3028-3033: schedule_insns (sched1)
Line 3049-3052: local_alloc
Line 3077-3080: global_alloc

So order: ... flow, combine, sched1, local-alloc, global-alloc. 

So flow computes refs and live_length on the pre-sched1 RTL. Then combine, then sched1 reorders. So the source statement order affects flow's live_length. Moving `dst = src + n` earlier in C extends dst's live range in the RTL, increasing live_length, lowering dst's priority!

Let me compute: dst live=36 currently. If I move `dst = src + n;` earlier (e.g., before `i = 0;` or before `n = ...`), the live range grows. Need dst live > 39 to drop below i's 0.846: 33/40 = 0.825 < 0.846. So extending dst's live by 4+ insns would flip it.

But does moving the statement change the generated code? The scheduler (sched1) may reorder, and the final code is determined by sched1+reorg. If sched1 keeps the same order, the code is identical. The target has dst computed late (delay slot of blez). Moving the C statement earlier might change sched1's result though.

Hmm, but sched1 uses INSN_PRIORITY (dependency-based), and the order of independent instructions depends on the original order + priorities. Moving the dst computation earlier might or might not change the final schedule.

Let me test: move `dst = src + n;` to before `i = 0;` or even before `n = ...`? It uses src and n, so must be after both are set. Current order:
```
n = arg0->w * arg0->h;
i = 0;
src = arg0->data;
dst = src + n;
if (n > 0) {
```
Options:
- Move dst before i=0: 
```
n = ...;
src = arg0->data;
dst = src + n;
i = 0;
if (n > 0)
```
This extends dst's live range? dst is born earlier (before i=0) and dies at the loop. The birth insn moves up by 1. live_length +1 or 2.
- Move dst right after n:
```
n = ...;
dst = src + n;  // but src not set yet!
```
Can't, src needed.

Hmm, what about moving `i = 0` LATER (after dst)? That doesn't change dst's birth, but changes i's birth (later -> shorter live -> higher i priority!). i's live 39. If i=0 moves later, i's live shrinks. But i=0 must be before the loop. Currently i=0 is before src and dst. If I move i=0 to just before the `if (n > 0)`, its birth moves later by 2 insns -> live 37, priority 33/37=0.892. Still < dst 0.917. Need i live <= 36: 33/36=0.917 tie with dst; tie-break by allocno number. Hmm.

Actually, wait: i=0 in the target is `move $10,$0` placed before `lw $9,0($13)` (src load) — i.e., i=0 comes BEFORE src=arg0->data in the target asm! So the source order i=0; src=... matches. Moving i=0 later would change the asm order (sched1 might reorder though).

Let me think about which is more promising: extend dst's live range. The target asm has dst computed in the blez delay slot, late. But flow's live_length is on pre-sched RTL. If I move `dst = src + n;` earlier in C, flow sees a longer dst live range, but sched1 might still schedule it into the delay slot (since it's the same dependency structure). This is a classic move that often doesn't change code!

Let me test: b2 = move `dst = src + n;` before `i = 0;` (so order: n; src; dst; i). Actually the current order is n; i=0; src; dst. To move dst earlier, I can reorder to n; src; dst; i. This changes both dst's birth (earlier: before i=0) and i's birth (later: after dst). Both help! dst live +1, i live -1.

Wait, but the target asm order is:
```
mult $3,$2
move $10,$0      # i = 0
lw $9,0($13)     # src = arg0->data
mflo $12
sll $2,$12,1
blez $12,$L129
addu $11,$9,$2   # dst = src + n
```
So i=0 before src. If I reorder C to n; src; dst; i, sched1 would need to move i=0 back before src to match. sched1 might or might not.

Let me just test empirically. Let me create b2, b3 variants:
- b2: order n; i=0; src; dst -> n; src; dst; i=0  (dst earlier, i later)
- b3: order n; src; dst; i=0 -> same as b2.
- b4: move dst to right after src, keep i=0 first: n; i=0; src; dst (same as current).
- b5: put dst declaration with initializer: `u16 *dst = src + n;` right after src.

Actually the C currently declares `u16 *dst;` at the top of the block and assigns later. Declaration order: n, i, src, dst. Pseudo reg numbers follow declaration order. dst is declared after src, so dst has a higher pseudo number. In the tie-break, lower allocno wins. If i and dst priorities tie, i (lower number) would win! That could be a lever: make them tie.

Hmm interesting. Let me think: if i and dst priorities are exactly equal, allocno_compare returns *v1 - *v2, so lower allocno number is allocated first. i is declared before dst, so i has a lower pseudo number -> i gets the first choice (t2). 

Currently i=0.846, dst=0.917, not tied. Need to bring them close.

Let me try moving the declarations and see.

Let me test several variants focusing on dst's live range and statement order. Let me create:
- b2: reorder statements to `n; src; dst; i=0` — wait that's src before i=0, changing the asm order? The target has i=0 before src load. Hmm, but sched1 might reorder. Let's test.
- b3: `n; i=0; src; dst` current.
- b4: `n; src; i=0; dst`? 

Let me also consider adding `i = 0;` after `dst = src + n;`:
- b5: `n; src; dst; i=0; if`.

Let me batch these.

Also, another idea: declare dst earlier (before i) so its pseudo number is lower. But the pseudo number affects tie-break; dst lower would be worse (dst wins ties). Actually we want i lower, which it already is.

Let me test b2/b5.

Let me generate them.
