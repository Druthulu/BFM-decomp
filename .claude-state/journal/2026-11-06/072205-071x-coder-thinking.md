---
ts: 2026-11-06T14:22:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_djBesTO2PuuFhlT0GD4h
---
The trick: `u8 *r; do { r = p + i; } while (0); *(s16 *)(r + 0xE) = -0x70;` — the do-while(0) splits the cse1 EBB so the `r = p + i` computation isn't merged; then `r` is USED in the store `*(s16 *)(r + 0xE)`, so it's a real use that gets folded into the store's addressing (r+0xE becomes the address). The `do{}while(0)` makes the EBB boundary so cse doesn't merge `r = p+i` with the store's address computation, and it adds a loop-weighted ref to p (since the do-while is inside a loop, the ref gets loop_depth weighting). And the codegen is identical because the address computation is the same (r + 0xE = p + i + 0xE).

Wait, but this is a case where `r = p + i` is a genuine value used by the store. The do-while(0) creates an EBB split, so cse1 doesn't forward r into the store address; the add remains a separate pseudo but the final code is the same (the address is computed the same way). Hmm, actually the note says "0xE store". 

So the technique: introduce a temporary that computes part of an existing address, wrapped in `do{}while(0)` to prevent cse from merging it, so that the base pointer gets extra REG_N_REFS at loop depth, without changing the generated instructions.

For our case, I need to add a ref to `i` inside the loop. Can I restructure an existing address computation to use i? The loop has:
- `px = *src;` (load from src)
- `*dst = out;` (store to dst)

Neither uses i. But I could compute the address via a temp that involves i... but the address doesn't involve i (src/dst are pointers).

Hmm. Alternatively, use the do-while(0) trick to make an existing computation split so that i is referenced. But i is only in the slt and i++.

Wait, maybe I can restructure the loop to use i in the address in a way that folds back to the same code. For example, replace `dst` with `src + n` and index by i? No.

Hold on. Let me reconsider: the do-while(0) trick's essence is to create a real C use of the variable in a computation that is later folded into the same instruction. For i, is there an existing instruction that could be expressed with i?

The `slt $2,$10,$12` (i < n) is the comparison. The `addu $10,$10,1` is the increment.

What if I express the increment as part of a do-while(0)? `do { i = i + 1; } while (0);` — that's the same RTL.

Hmm.

What about the address: the loop could be written as `dst[i] = out` where dst is a base pointer that does NOT advance, and `src[i]` for the load, with `src` being the base. Then i is used in both addresses, and loop.c strength-reduces. But b1 tried that and got a different result.

Wait, b1 used `dst = src + n` and `dst[i]`, `src[i]`. Let me look at b1's loop asm to see how close it was. Actually, the strength reduction created extra GIVs. Hmm.

Let me reconsider the exact original. The target loop:
- src increments by 2 (element)
- dst increments by 2
- i increments by 1
- compare i < n

This is the canonical output of loop.c strength reduction for:
```
for (i = 0; i < n; i++) {
    px = src[i];
    ...
    dst[i] = out;
}
```
where src and dst are fixed base pointers. loop.c creates GIVs for src+i and dst+i, each incremented by 2, and keeps the BIV i for the comparison. So the ORIGINAL was probably array-indexed!

Then why did b1 score 52? Because I wrote `dst = src + n` and used `dst[i]` — maybe loop.c then had three GIVs (src+i, dst+i) and the combination differed. Or because the base pointers were different. Let me look at b1's generated loop to see.

Actually, the key: in b1, the loop condition became `slt v0,t0,t5` where t0 is a pointer, meaning loop.c replaced the BIV comparison with a pointer comparison (the "GIV comparison" optimization). That's a different loop.c path. Maybe because `src[i]` and `dst[i]` both index off pointers, loop.c decided to use a pointer comparison.

Hmm. Let me look at b1's loop more carefully. Actually, the diff showed the loop condition `slt v0,t0,t5` and increments `addiu t0,t0,2`, `addiu t2,t2,2` (i? no). It seems loop.c strength-reduced differently.

Wait, in b1 the C was:
```
n = arg0->w * arg0->h;
i = 0;
src = arg0->data;
dst = src + n;
if (n > 0) {
  do {
    px = src[i];
    ...
    dst[i] = out;
    i++;
  } while (i < n);
}
```
Here `src` and `dst` are pointers (src=arg0->data, dst=src+n), and src[i]/dst[i] index. This is a do-while with i as BIV. loop.c might not strength-reduce a do-while well, or it produced the pointer comparison.

The ORIGINAL likely was a `for` loop with array indexing. Let me try:
```
src = arg0->data;
dst = src + n;
for (i = 0; i < n; i++) {
    px = src[i];
    ...
    dst[i] = out;
}
```
But f1 (for loop with pointer increments) gave frame 32. Hmm.

Let me try the for loop with array indexing (f3):
```
n = arg0->w * arg0->h;
i = 0;
src = arg0->data;
dst = src + n;
for (i = 0; i < n; i++) {
    px = src[i];
    ...
    dst[i] = out;
}
```
Let me test f3.

Actually, wait. Let me reconsider the do-while(0) trick applied to our case more cleverly. The note's trick added a ref to `p` (a base pointer) by computing `r = p + i` and using r in the store. For us, we need a ref to `i`. What if I compute the dst address as `r = dst + i;` and store through r? That would add a ref to i! But the address would be wrong: dst already advances. Hmm.

Wait, actually, the loop's store is `*dst = out`. What if I write the store as `*(u16 *)((u8 *)dst) = out`? no i.

What if the load is `px = *(src + i - i)`? folds.

Hmm. Let me think about a semantically-equivalent expression using i that folds into the existing address. The store address is `dst`. Can I express `dst` in terms of i and another pointer? E.g., keep a base pointer `dst0 = dst` and index by i? That changes the address (dst0 + i vs dst). Unless dst = dst0 + i... 

Actually! Here's an idea. What if I keep `src` as the base pointer and compute the store address as `src + n + i`, i.e., `dst[i]` with dst = src+n? But b1 tried `dst[i]`. The issue was loop.c strength reduction. What if I use the do-while(0) to prevent loop.c from strength-reducing? Hmm.

Alternatively, use the do-while(0) trick to add the ref WITHOUT the address being folded. E.g.:

```
do { i = i; } while (0);   // identity launder — forbidden
```

No.

Let me think about what real use of i can be folded into an existing instruction:
- The slt: `i < n`. If I write `do { t = i < n; } while (0);`? That computes the comparison into t; but the comparison is already computed in the loop condition. Would combine merge them? Probably not (different blocks).

Hmm.

Let me look at the C0535 cookbook entry to understand the do-while(0) mechanism better.
