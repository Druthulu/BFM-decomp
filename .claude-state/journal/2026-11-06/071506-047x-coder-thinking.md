---
ts: 2026-11-06T14:15:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5eLdnihjOXRJUCT1PxuD
---
Interesting: `dst = dst + 2` produced `addiu t2,t2,4`! Because dst is `u16 *` and I wrote `dst = dst + 2` which adds 2 elements = 4 bytes. Oops. I should write `dst = dst + 1` (pointer +1 element = +2 bytes) or cast. Right.

Also the reg swap still happens. So the increment change didn't flip the allocation (and the +4 broke the code). Let me instead use `dst += 1;` or `dst = (u16 *)((u8 *)dst + 2);`. The latter might add code. `dst += 1` should be same as dst++ but maybe without REG_INC note? In C, `dst += 1` for a pointer is equivalent to dst = dst + 1, and gcc might emit the same REG_INC. Let me try `dst += 1`.

But also note: the allocation still gave dst t2 (higher priority). Hmm, did removing the increment extra ref lower dst? Apparently not enough or the REG_INC still present.

Let me test c3: `dst += 1;` and c4: `dst = dst + 1;`.

Wait, `dst = dst + 1` on a u16* adds 2 bytes. Let me test both.

Also, importantly, maybe I should directly test raising i: e.g., `i = i + 1` vs `i++` — no that lowers.

Hmm. Let me reconsider. Maybe the correct lever is to make i's live range or refs.

Let me try a different approach: what if I reorder the increments so that i is incremented before dst? The ref counts are the same. But sched1/sched2 might reorder? The final code is fixed by target; the order of increments in source affects scheduling only.

Let me think about the actual mechanism more concretely by testing. Let me test:
- c3: dst += 1
- c4: dst = dst + 1

And check scores.

Actually, the more promising lever: add a real reference to i. What if I change the loop condition to use i and n in a way that's still one slt but i appears... no.

Wait — here's an idea. The `while (i < n)` condition: what if I write `while (i < n && 1)`? folded.

Another: what if I write the do-while condition as `while (i < n)` but use i in the increment expression differently: `i = i + 1` gives i one fewer ref (no REG_INC). Not helpful.

Hmm, what about making `i` a `s16`? The brief mentions "s16/u8 widths". If i were s16, the RTL would use HImode ops, changing code. No.

Let me reconsider: perhaps I can make the loop use a *different* natural formulation where i is referenced in the store or load addressing. But the target code is fixed...

Actually, wait. Let me look at the target more carefully: maybe there's freedom in the code that produces the SAME instructions but different RTL ref counts. For example, the `slt` instruction `slt $2,$10,$12` compares i (t2) with n (t4). The target has i in $10. If the condition were `n > i`, gcc would still emit `slt $2,$10,$12`? Let me check: `n > i` is `i < n`, canonicalized by fold. Same.

What about `while (n - i > 0)`? That emits subu + slt? Actually `n - i > 0` might fold to `n > i` -> `i < n`. Hmm, gcc's fold might simplify.

What about `while (i != n)`? emits bne, different.

OK, let me look at this from the "live length" angle: dst live 36, i live 39. If I could shorten i's live range to 33, priority = 33/33 = 1.0 > 0.917. But i's live range is from i=0 to the slt. Shortening means moving i=0 later or the slt earlier — both change code.

Alternatively, extend dst's live range. dst's live is 36. To make dst priority < 0.846: 33/len < 0.846 -> len > 39. So dst live 40+. Extending dst's life would require a use of dst after the loop or before its def — changes code.

Hmm. So the only clean lever is +1 ref on i (i=12 gives 0.923 > 0.917) or -1 ref on dst (10 gives 0.833 < 0.846).

Let me verify the -1 dst ref idea by understanding how to remove exactly one ref. dst refs: 11. The `dst = src + n` set (1 ref at loop depth 1?), the store use, the increment. 

If `dst = src + n;` is moved inside the do-while (before the store), then dst's def is in the loop and its live range shrinks, AND the def counts at higher loop depth. But that changes code: the `addu $11,$9,$2` would move inside the loop. Unless... hmm, actually the target has it before `blez`. So no.

What if dst is initialized as `dst = src + n;` but written as part of the declaration `u16 *dst = src + n;`? Same RTL.

Let me look at how the ref count is actually distributed by examining flow.c more. Actually, let me just test empirically: dump variants and read the register table. I have a dump pipeline. But each dump is ~6.6MB and takes a few seconds. That's fine.

Let me test c3: `dst += 1`. Generate and dump, read refs for 160/162.

Actually, a cheaper approach: score with dt.sh (fast) and only dump if the register flips. Let me batch several variants and score them all with sc.sh.

Variants (all based on c1, asm removed):
- c3: `dst += 1;`
- c4: `dst = dst + 1;`
- c5: `src += 1;` (instead of src++) — lowers src refs, irrelevant to i/dst but harmless? Might change scheduling.
- c6: `i += 1;` instead of i++ (lowers i, bad).
- c7: reorder increments: `src++; dst++; i++;` etc.
- c8: `i++` -> `++i` (prefix) — might avoid the "post-increment" extra? In gcc, `i++` as a statement is the same as `++i`.
- c9: declare i as `u32`? no change.

Hmm. Let me think about adding a ref to i via the loop bound. What if I compute `n` using i? no.

Wait wait. Here's a cleaner idea: the target code has BOTH `src` and `dst` as pointers into the same buffer. dst = src + n. What if I eliminate `dst` and use `src[n]`? No.

Let me reconsider: the two asm keepalives were needed because the natural source had different ref counts. The comment says the src asm keeps "src above i, below the mfhi temp" and the i asm "lifts i over dst in the $t2 race". So the ORIGINAL game source likely had i referenced more naturally, e.g., the original loop might have been:

```
for (i = 0; i < n; i++) {
    px = src[i];
    ...
    dst[i] = out;
}
```
That would use i in both load and store addressing, adding refs to i. But then the codegen would have `sll` for i*2... unless the compiler strength-reduces to pointers (loop.c GIV). Hmm! If the original used array indexing with i, loop.c might strength-reduce into src/dst pointer increments, and i would be referenced more. But the resulting code would still have i in t2.

But our job is to match the target binary, and any C that produces it counts. So let me try the array-index formulation and see if gcc produces the same code with i having more refs!

Try:
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
But `src[i]` would need i*2 each iteration; loop.c may strength-reduce. However, the target increments src and dst pointers, so if loop.c strength-reduces both, we'd get extra induction variables. Risky. But worth a try.

Hmm, but the target's loop is a do-while with `i` as a simple counter and separate src/dst pointers. The cleanest match is our current structure.

Let me think about adding a ref to i in a way that produces no code: use i in a comparison that's already computed. E.g., the loop condition `i < n` — what if I also use i in the `if (n > 0)` guard? Like `if (i < n)`. Since i=0 at that point, `i < n` is equivalent to `n > 0`. That would use i in block 13 (depth 1), adding 1 ref to i, and the comparison would emit `slt` there — but wait, the target already has `blez $12,$L129` (n <= 0 check). If I write `if (i < n)` with i=0, gcc would emit `slt`/`bge` maybe with a different instruction (slt + beq vs blez). That changes code. Unless gcc knows i==0 and folds it. If it folds `0 < n` to `n > 0`, the ref to i might be deleted. Hmm, but if fold happens before flow's ref counting... The C front-end would fold `i < n` only if it knows i==0, which it doesn't (i is a variable assigned 0). So it'd emit slt. Bad.

What about using i in the `if (out == 0 && px != 0)`? no.

Hmm, what if I make i's increment appear twice in RTL without adding an instruction? E.g., `i = i + 1;` where the read i is also used elsewhere... 

Let me look at the target's ref distribution by examining the .flow dump? flow.c with -df prints the register info? Let me check the flow dump for the function.

Actually, the lreg dump's "used N times" is reg_n_refs. Let me look at the .flow dump to see if it lists per-insn.

Alternatively, let me look at the .rtl dump (before flow?) which shows the source-level RTL and pseudo numbering. That tells me how many occurrences each pseudo has. But refs are weighted by loop depth.

Let me try a completely different lever: change the LOOP STRUCTURE so that i is compared at the top and incremented at the bottom, e.g., a `for` loop. The target is do-while (bottom-tested with guard). Actually target:
```
    blez $12,$L129   # if (n <= 0) skip
$L131:
    ... body ...
    addu $11,$11,2
    addu $10,$10,1
    slt $2,$10,$12
    bne $2,$0,$L131
    addu $9,$9,2
$L129:
```
This is a do-while with a pre-guard. A `while (i < n)` loop would be top-tested: `slt; beq exit` at top and an unconditional jump at bottom, OR gcc's loop optimization converts to the do-while form with the guard. Actually gcc often converts `while` to the bottom-tested form via loop inversion? gcc 2.7.2 does have loop inversion in loop.c ("loop.c: ... convert while to do-while"). Let me test: write it as a `while (i < n) { ... }` loop and see if the code matches.

If the while-loop form produces the same code, does i get more refs? The top test `i < n` would be executed at loop entry AND at the bottom (loop inversion duplicates the test or restructures). Actually loop inversion creates a pre-test plus a bottom test. The pre-test uses i (before the loop) -> an extra use of i at depth 1 (outside the loop) and possibly the comparison is duplicated. Hmm.

But the target has only ONE slt (at the bottom) and a `blez n` guard. That's exactly what our do-while with `if (n > 0)` produces. If I write `while (i < n)`, gcc 2.7.2's loop inversion might produce: `if (i < n) { do { } while (i < n); }` -> pre-test slt + bottom slt = two slts. But target has one. Unless the pre-test is `blez n` (from `i < n` with i=0 folded? no).

Hmm. Let me just test a few variants quickly.

Actually, let me step back and consider the simplest possibility: maybe there's a real-C use of i in the *setup* that folds into existing instructions. Look at the target setup:
```
	lh	$3,-4($13)     # arg0->w
	lh	$2,-2($13)     # arg0->h
	mult	$3,$2
	move	$10,$0         # i = 0
	lw	$9,0($13)      # src = arg0->data
	mflo	$12           # n
	sll	$2,$12,1
	blez	$12,$L129
	addu	$11,$9,$2     # dst = src + n*2
```
The `move $10,$0` is i=0. If I write `i = 0` as part of something... e.g., `n = arg0->w * arg0->h; i = 0;` no ref.

What if `i` is used in computing dst: `dst = src + n + i;`? Since i is 0, gcc emits `addu $11,$9,$2` if it can fold i=0. Does gcc's RTL-level fold know i=0? At the tree level, no (i is a variable). At combine/jump, there's a REG_EQUAL note for i (i=0). jump.c's `no-op move`? Hmm, `dst = src + n + i` would emit `addu t, src, n` then `addu dst, t, i` = 2 instructions. Unless combine folds i via REG_EQUAL. Actually combine can substitute a known constant. i has REG_EQUAL 0 (from `(set reg160 (const_int 0))` with REG_EQUAL). combine might fold `plus (reg160) ...` if reg160 is a known constant with a REG_EQUAL note... Actually combine uses REG_EQUAL only in specific cases. Risky but testable.

Let me test the idea: `dst = src + n + i;` (i=0). Hmm, but `src + n + i` — pointer arithmetic: src + n + i = src + (n+i) elements. That's what we want semantically (i=0). Let me test.

Another idea: `dst = src + (n - i) + i;`? silly.

Let me batch test several variants. I'll write them all as files and run sc.sh.

Variants (from c1.c, asm-free):
- v1: `dst = src + n;` -> `dst = src + n + i;`   (adds i ref if not folded)
- v2: `dst++;` -> `dst += 1;`
- v3: `dst++;` -> `dst = dst + 1;`
- v4: `i++;` -> `i += 1;`
- v5: reorder: `dst++; i++; src++;` -> `i++; dst++; src++;`
- v6: `while (i < n);` keep, but change `if (n > 0)` -> `if (i < n)`  (risky)
- v7: combine increments: `*dst = out;` then `dst++; i++; src++;` -> use `dst[0]`? no.

Let me also consider: `i` could be declared `u32` vs `s32` — no code change, no ref change.

What about making `i` and `dst` share a register via copy propagation? no.

Let me run the batch.

Actually, the most promising is v1: add `+ i` to dst computation. If combine folds it away using REG_EQUAL, the ref might remain in flow's count (flow counts refs on the RTL before combine? Order: flow analysis runs before combine? Pass order in gcc 2.7.2: ... cse, loop, cse2, flow, combine, sched, local-alloc, global-alloc... Actually flow runs after loop? Let me recall: -df is flow. The pass order: jump, cse, loop, cse2, flow (flow_analysis computes refs), combine, sched, local-alloc, global-alloc, reload, sched2. Hmm, if flow runs before combine, then the ref to i in `dst = src + n + i` would be counted by flow (before combine folds it). Then combine removes the instruction, but the ref count used by global-alloc is from flow. That could work!

But careful: the pass order matters. Let me check toplev.c pass order.
