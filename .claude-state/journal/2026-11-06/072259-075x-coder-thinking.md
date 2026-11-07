---
ts: 2026-11-06T14:22:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nPfti4rBzUfRtuDODXA2
---
Found it. In `propagate_block`, if `final && insn_is_dead`, the insn is deleted and `goto flushed`. Crucially, the deletion happens BEFORE the ref counting for that insn (the `mark_set_regs`/`mark_used_regs` calls are after this check). So a dead-store insn is deleted and its refs are NOT counted.

Wait: `insn_dead_p(PATTERN, old, 0)` — is it dead? A `t = i` copy where t is dead: the SET_DEST is t (dead), but the SET_SRC is i (a use). `insn_dead_p` checks whether the insn's stores are dead AND whether it has side effects. For a plain `(set t i)`, if t is dead, insn_dead_p returns 1, and the insn is deleted WITHOUT counting the use of i. So `t = i` (dead t) does NOT add a ref to i. Damn.

But the C0414 dead-reset `p = 0` after a use: the store to p is dead and deleted. It doesn't add refs to anything meaningful (p is the dest). Actually, it might add a ref to p? No — deleted before counting.

Hmm wait, but then how does C0414's dead reset affect cse? It's deleted by flow, but cse runs BEFORE flow (cse1 at 2865, cse2 at 2926, flow at 2983). So cse sees the dead reset (before flow deletes it), which breaks the equivalence, and then flow deletes it before sched1. That's the mechanism: cse sees it, flow deletes it. So the ref counting in flow never sees it.

OK so dead stores don't add refs. 

So how did the worked example func_80181F4C add a ref to p? Via `do { r = p + i; } while (0); *(s16 *)(r + 0xE) = -0x70;`. Here `r` IS used by the store. So `r = p + i` is a real computation that flows into the store's address. The do-while(0) splits the EBB so cse1 doesn't merge `r = p+i` into the store's address, but the final code is the same (the address is computed the same). So the ref to p (and i) is counted.

So to add a ref to i, I need a REAL computation using i that folds into existing code but survives cse1 (via do-while(0) split) and produces the same instructions.

What computation in the loop uses i and folds into an existing instruction? 

Idea: the loop condition `i < n` could be computed as a temp: `do { t = i < n; } while (0);` and then use t in the loop condition `while (t)`? But the loop condition is evaluated each iteration; the temp must be computed inside the loop. Hmm, `do { t = i < n; } while (0);` at the end of the body, then `while (t);` — the `while (t)` would use t, and the comparison `i < n` is real. The RTL: compute slt (t = i<n), then branch on t. The target has `slt $2,$10,$12; bne $2,$0`. Same instructions! And the ref to i is counted (in the slt). But wait, i was ALREADY used in the slt. Adding a temp `t = i < n` doesn't add a ref — it's the same slt.

Hmm.

Idea: use i in the load or store address. The load is `px = *src`. The store is `*dst = out`. If I compute `dst` from `src` and `i` each iteration: `dst = src + n - (n - i) + ...` no.

Hmm. What about the increments: `dst++` and `src++` and `i++`. Could I express `src++` in terms of i? Like `src = arg0->data + i;`? That would recompute src each iteration from the base, adding an sll+addu. Unless loop.c strength-reduces... Actually, `src = base + i` inside the loop is a GIV; loop.c might convert it to src += 1 (strength reduction)! And the `base + i` computation would be recognized as an induction variable and replaced by an increment. That's exactly strength reduction. But then the ref to i might remain in the GIV computation.

Hmm, this is the b1 territory.

Let me look at b1's loop to see if it's actually close. b1 scored 52 with 239 ins (one fewer). Let me look at b1's loop asm.

Actually, let me reconsider. The target's loop has `addu $10,$10,1` for i++. What if the original C was:

```
for (i = 0; i < n; i++) {
    px = src[i];
    ...
    dst[i] = out;
}
```
and loop.c strength-reduced src[i] and dst[i] into pointers src and dst, keeping i as BIV. The strength reduction creates `src += 2`, `dst += 2` and keeps `i++` for the comparison. The ref to i in the original src[i]/dst[i] indexing... After loop.c, those uses are replaced by the GIVs. So flow (after loop.c) sees i only in i++ and i<n. Same as ours.

Hmm, but maybe loop.c's GIV creation leaves a "compare" that uses i differently.

Wait, maybe I'm overanalyzing. Let me just test a few more variants based on the do-while(0) trick. Specifically, let me try to add a REAL use of i that folds into the existing code:

Variant: compute the dst pointer via a temp each iteration using i:
```
do {
    u16 *d = dst;
    ...
    *d = out;
} while (0);
```
No i.

What if: `d = src + i;`? That's not dst (dst = src+n). 

Hmm, what about the store address being `src[n + i]`? But src advances each iteration, so that's wrong.

Wait — what if I restructure the loop so that `src` and `dst` are NOT incremented, and instead the addresses are computed as `base + i`? Then i is used in the addresses. loop.c strength reduction would turn `base + i` into a pointer increment... and the final code would be the same as the target! And i's refs would include the address computations (if loop.c keeps them). Let me try:

```
n = arg0->w * arg0->h;
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
This is b1, which scored 52. But b1's loop.c produced a pointer comparison. Maybe because `dst[i]` where dst = src+n is a GIV that loop.c could combine with src[i]'s GIV (same base, different offset), creating a combined GIV. The pointer comparison optimization kicked in.

Let me look at b1's loop asm to understand.

Actually, maybe the issue is the do-while. The original might have been a for loop. Let me try the for loop with array indexing.

Hmm, but f1 (for with pointers) gave frame 32 (bad). Let me try f3 = for with array indexing.

Actually, let me step back and check the time. I started around 07:05. It's probably ~07:30 now. I've spent ~25 min on the first item. The budget is 20-30 min per item. But since this one function is 3 items, cracking it is high value.

Let me be strategic: let me test the do-while(0) + real-use trick in the most promising form, and the array-index for loop. If neither works in a few tries, record a WALL.

Actually, wait. Let me reconsider the worked example trick applied here: the trick added a ref to `p` by computing `r = p + i` and using r in the store. The analogous thing for us: add a ref to `i` by computing something with i that's used in an existing instruction.

What existing instruction could use i? The comparison `i < n`. What if I compute the comparison into a temp and use it in a way that folds?

```
do {
    s32 t;
    t = i < n;
    ...
} while (t);
```
Hmm, the slt computes t; then the branch uses t. Same code. But the ref to i is the same (1 use in slt). No gain.

What about computing `i` in the address of the store via a GIV-like expression that folds? 

Let me look at the actual target loop once more:
```
	lhu	$7,0($9)         # px = *src  (src = $9)
	andi	$2,$7,0x001f
	mult	$2,$16
	...
	sh	$5,0($11)        # *dst = out  (dst = $11)
	addu	$11,$11,2        # dst++
	addu	$10,$10,1        # i++
	slt	$2,$10,$12       # i < n
	bne	$2,$0,$L131
	addu	$9,$9,2          # src++
```

What if I write the load as `px = src[0];` and the store as `dst[0] = out;`? Then the addresses are `src + 0` and `dst + 0`, which fold to src/dst. No i.

What if the loop uses i for the store: `dst[i - i]`? folds.

OK, what if I change the loop so that instead of `dst++`, I use `dst = src + n;` recomputed? no.

Let me look at the b1 loop to see if the strength reduction is salvageable. Let me dump b1's .s and look at the loop.

Actually, a faster idea: let me test whether a `for` loop with array indexing produces the target loop with i having more refs. Let me create f3.

Also, let me test the "dead-reset" on i to see if it affects refs (maybe flow's ref counting happens in a first pass and deletion in a second? No — `final` pass deletes before counting, as we saw).

Hmm wait, actually there are TWO passes of flow? `flow_analysis` is called with `final` parameter. In toplev.c line 2983: `flow_analysis (insns, max_reg_num (), ...)`. Let me check the args — the `final` flag. If final=1, dead stores are deleted. Let me check.
