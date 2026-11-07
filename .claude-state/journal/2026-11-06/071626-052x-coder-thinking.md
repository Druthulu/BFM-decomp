---
ts: 2026-11-06T14:16:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aDaQisMasAoytkFxFdEc
---
loop_depth starts at 1 (not 0), incremented at LOOP_BEG notes. So a block outside any loop has depth 1. Inside one loop: depth 2. Inside two: depth 3.

So: block 13 (inside the while, outside the do-while) has depth 2. Block 14 (inside the do-while, inside the while) has depth 3. That matches: src asm in block13 adds 2; i asm in block14 adds 3. 

Now count refs:
- i: `i=0` set in block13 (depth 2) = +2. `i++` in block17 (depth 3): set +3, use... the increment is `(set reg160 (plus reg160 1))` — occurrences: dest reg160 (+3) and src reg160 (+3) = +6. `slt` use in block17: +3. Total = 2+6+3 = 11. ✓ Matches!
- dst: `dst=src+n` set in block13 (depth2) = +2. store use `(mem (reg162))` in block17? Wait, block 17 is the latch (insns 388-407). But the store `sh $5,0($11)` is at insn 391 which is in block 17 (first 388). Hmm, earlier I saw the store at insn 391 in block 17. And the store is inside the do-while (depth 3). So store use +3. `dst++` in block17: set +3, use +3 = +6. Total = 2+3+6 = 11. ✓ Matches!

So dst = 11, i = 11 without asm. The target i = 14 = 11 + 3 (one asm use in block14 at depth 3).

Now, to flip: i needs +1 ref (i=12 -> 3*12/39 = 0.923 > dst 33/36=0.917), OR dst needs -1 (dst=10 -> 3*10/36=0.833 < i 33/39=0.846).

How to get exactly +1 ref on i? A use of i at loop depth 1 (outside any loop) would add 1. Or a use at depth 2 (block13) adds 2 -> i=13, priority 39/39=1.0 > 0.917. That works too (2 refs).

Or a use of i at depth 3 adds 3 -> i=14, exactly target.

But any added use must not change the emitted instructions.

Now, which block? If I add a use in block 13 (the setup, depth 2), it adds 2 refs, but it must fold away by combine (after flow). Also it must not extend i's live range (i is born in block 13 anyway, so a use after the birth is fine).

What real C use of i in the setup folds via combine but not cse? Hmm.

Alternatively, add a use in block 14 or 17 that's part of an existing instruction.

Idea: The store `*dst = out` — what if the address is written as `dst[i - i]`? cse folds to dst. No ref kept? cse would replace `i-i` with 0? Actually `i - i` is folded by fold at the tree level (it's `minus` of identical operands -> 0). So no.

Idea: use i in the loop condition in a way that doesn't emit an extra instruction: `while (i < n)` — already there. What if the condition is `while (i < n && i >= 0)`? With i unknown, this emits an extra compare/branch. No.

Idea: `i` is used in the `dst` computation: `dst = src + n + (i & 0)`. `i & 0` folds to 0 at tree level.

Idea: `dst = src + n + (i - i)`. folds.

Hmm.

What about a use that combine removes: `dst = src + n; dst = dst + i;`? Two statements: the second adds i. cse2: dst is a variable; `dst + i` with i=0 known by cse? cse does constant propagation and would fold i to 0, then `dst + 0` -> dst, and the assignment becomes a no-op, deleted. So cse2 removes it before flow. No ref.

The problem: cse2 (before flow) folds constants. combine (after flow) also folds. So we need something cse2 CANNOT fold but combine CAN.

cse2 can't fold a use of i if i is not a known constant in cse's tables. But i IS a known constant (0) after `i = 0`. Unless cse loses track of i across the loop (cse processes the CFG; i=0 is in block13, and the use in block14/17 — cse may not propagate across block boundaries? cse does propagate values across blocks within extended basic blocks. If block13 ends with a branch (blez) and block14 is a separate EBB, cse might not propagate the constant across. Hmm! The `if (n > 0)` branch splits the EBB. So i=0 in block13 may not be known inside block14's EBB.

Wait, but the asm at insn 329 (i keepalive) is in block14. If I put a real use of i in block14, cse2 might NOT know i==0 (cross-block), so it won't fold. Then the use emits an instruction, and combine (after flow) might not remove it either. Hmm.

But combine could remove it if it's part of an existing computation. For instance, if I add i to the store address: `dst[i] = out`? That changes addressing.

OK here's another thought: what if I use i in an existing instruction where it's harmless? The `slt` already uses i. The `i++` uses i.

What if I change `src++` to `src += (i - i) + 1`? folds.

Hmm.

What about making `i` also the destination pointer offset in the initialization: `dst = src + n;` -> `dst = &src[n];` same.

Let me think about dst reduction instead. dst=11. Remove 1 ref. dst occurrences: set in block13 (2), store use block17 (3), set+use in dst++ block17 (6). 

If I move the `dst = src + n;` into the loop? No, changes code.

If I change `dst++` to something that produces the same `addu $11,$11,2` but with fewer counted refs: e.g., `dst = (u16 *)((u8 *)dst + 2);`. This is a cast; the RTL would be `(set dst (plus dst 2))` still 2 occurrences. Same.

If I write the store as `*(dst) = out` and increment as `dst += 1` — same.

What if dst is not a separate variable but an expression `src + n` used in the store? That would compute the address each iteration (extra instruction). No.

Hmm. What if the store uses a different base: `dst` vs `src[n + i]`? no.

Let me reconsider. Maybe the cleanest is to make i's increment generate MORE refs naturally. Currently i++ = set with dest+src (2 occurrences) + slt (1). What if I write `i += 1` — same. What if `i = i + 1` — same RTL.

What if I write `++i` and use the value: e.g., `i++` at the bottom, but also use i in the body? 

Wait — what if the loop uses `i` to index into `dst` for the store, but we keep a pointer `dst` too? Like `dst[i]`? No.

Hmm, let me look at this from a different angle: maybe the target's ref count for i is naturally 14 because the original C used i in a *third* place that got optimized into the same instructions. For instance, the original might have been:

```
for (i = 0; i < n; i++) {
    px = src[i];
    ...
    dst[i] = out;
}
```
Then loop.c strength-reduces src[i] and dst[i] into pointers, but the i refs might remain in the RTL (the pointer increments are derived). Let me just test this formulation and see what code and refs result.

Actually, let me look at the .loop dump for the current version to understand how loop.c sees it. But more efficient: just try variants and score.

Let me create a batch of candidate bodies and score them. I'll generate:

v1: array-index form:
```
n = arg0->w * arg0->h;
src = arg0->data;
dst = src + n;
if (n > 0) {
    for (i = 0; i < n; i++) {
        px = src[i];
        ...
        dst[i] = out;
    }
}
```
But `src[i]` where src is u16* — loop.c strength reduction may or may not produce the exact pointer increments. Let me test.

Hmm, this is getting long. Let me timebox: I have 5 items, 20-30 min each. Let me be systematic but efficient.

Let me first quickly test a batch of small variants (cheap, sc.sh). Then for promising ones, dump refs.

Batch 1 (all from c1.c, asm-free):
- a1: `dst = src + n;` -> `dst = src + n; i = i;`? no, that's a self-assign, gets deleted.
- a2: reorder i++ before dst++.
- a3: `dst += 1;`
- a4: `dst = dst + 1;`
- a5: `i += 1;` (lower i — check direction)
- a6: `i = i + 1;`
- a7: move `i++` to the top of the loop body.
- a8: `while (i < n)` -> `while (n > i)`.

Let me generate and score all at once. Note: sc.sh takes multiple files.

Let me create them.
