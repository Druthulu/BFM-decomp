---
ts: 2026-10-22T07:48:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UsWkA0riuPiyuamWNlIK
---
Confirmed in the trimmed TU: the tree's q-based stores are at 6, 4, 2 ($16) and cand01's at 4, 2, 0 — i.e. the q base was re-based by +2.

So the lever-free goal: keep q's init at D_801AAD6C+0 (addiu s0,s0,0) and the stores at 6, 4, 2.

Now, the re-basing is gcc's ivcanon "change the IV's init" optimization. What blocks it? The launder's extra set on q.

Let me check the .loop dump for the IV analysis in both. Let me grep for the IV info in tree.i.loop vs c1.i.loop.

Actually, the .loop dump prints the loop's optimization decisions. Let me diff them.

Hmm, time. Let me instead try to find the actual condition. gcc 2.7's loop.c `ivcanon` (the "ivcanon" pass) includes:

```
/* ivcanon_init_failure
   ivcanon_final_value
   ivcanon_iv_init
   ...
```
And `ivcanon_iv_init`:
```
static int
ivcanon_iv_init (struct loop *loop, struct iv_info *iv_info)
{
  ...
  /* If we have a non-negative add of the init, we can rewrite ... */
```
Hmm.

Actually, I recall the specific optimization: "ivcanon: the IV's initial value can be changed if all uses are at constant offsets AND the new init doesn't overflow" — gcc picks the init as "the use offset that makes the offsets as small as possible"?? Hmm.

Hmm, the re-basing picked +2 (making the offsets 4, 2, 0 instead of 6, 4, 2). So gcc chose to minimize the maximum offset. This is the "ivcanon_iv_init" optimization: "the IV's init is changed so that the offsets are smaller" — it needs the "use" offsets to be known.

Why doesn't the tree do it? Because with the extra set, the IV isn't a "simple IV" → the optimization doesn't apply.

So: I need q to have 2 sets in the loop body. Plain C...

**IDEA**: what if the loop body's q update is written as a compound on a DIFFERENT expression that yields a real 2nd set? Hmm.

**IDEA (promising!)**: what if we make the loop body's q increment go through the `off` variable? E.g.:
```
        off += 8;
        q = (s16 *)((u8 *)D_801AAD6C + off);
```
Then q has 1 set in the body (the recomputation) — and the address is recomputed each iteration (an extra addiu per iteration ✗ more instructions).

Hmm, but wait: the target's loop has `addu $19,$19,8` (off += 8) and `addu $16,$16,8` (q += 8) — TWO increments ✓. So the target computes both.

**IDEA**: what if q's increment is expressed via off: `q = (s16 *)((u8 *)D_801AAD6C + off + 8);`? Hmm, then q = base + off + 8 and the stores would be at q+6 = base+off+14 ✗ wrong.

Hmm.

**IDEA**: what if the pointer q is updated with a compound assign that gcc's ivcanon doesn't recognize as the IV pattern? E.g. `q = (s16 *)((u8 *)q + 8);` — hmm, I tried that (cand10, score 4).

Hmm, what if the update is `q = (s16 *)((u32)q + 8);`? Hmm.

**IDEA**: what if we make the q update have TWO sets in the body via an if/else? e.g.
```
        if (i == 3) { q += 4; } else { q += 4; }
```
✗ (a branch).

**IDEA**: what if the loop body ends with `q = q;` where q is a *volatile*... no.

**IDEA**: what if the second set of q comes from a `do {} while(0)` self-copy? `do { q = q; } while (0);` — cse might remove the self-copy (as in item 4 where it was removed: cand09 gave 191 ins vs 192). Hmm, but for a POINTER (not a register var), cse removes it.

Hmm, hold on: in item 3, `do { rgb = rgb; } while (0);` on a PINNED var survived. For a normal local it's removed.

Hmm! What if q were... hmm.

**IDEA**: What if the extra set is created by a compound assign that preserves the value: `q = (s16 *)((u8 *)q | 0);`? The `| 0` on an integer → folded to the value → then the cast → folded ✗.

**IDEA**: `q = (s16 *)((u8 *)q + 0);` folded.

Hmm, what about `q = (s16 *)((s32)q + 0);`? folded.

Hmm, what about a compound assign that preserves the pointer's value but isn't folded: `q = (s16 *)((u8 *)q);` — a cast to u8* then back to s16*: gcc folds the round-trip ✓.

OK. What if we use an INTEGER variable for the pointer and convert? E.g.:
```
s32 qi;   /* the byte offset of q */
...
qi = (s32)D_801AAD6C;
while (i < 4) {
    *(s16 *)(qi + 6) = 0;
    ...
    qi += 8;
}
```
Then there's no pointer IV at all → gcc's ivcanon can't re-base an integer IV? Hmm, it might! The integer IV would be re-based the same way.

Hmm, but the emitted code would differ (the stores would use an indexed addressing `sh zero,6(qi)` ✓ same as the target's `sh zero,6(s0)` ✓!). Hmm! Actually the target's stores ARE `sh zero,6(s0)` — an indexed store ✓. So spelling q as an integer offset might produce the same code ✓.

Hmm, but then the q[3]/q[2]/q[1] stores and the 4th store: the 4th store is (D_801AAD6C + off) — with qi = (s32)D_801AAD6C and off = 8*i, the 4th store's address = base + off while qi = base + 8*i → the same value → gcc might unify them again (as q[0]) ✗. Hmm, but if q is an integer (not a pointer), gcc's unification might not happen (different types/aliases) ✓!

Hmm! Interesting. But the risk: the "sh zero,6(s0)" form needs the base in a register ✓.

Hmm, but wait: with qi as an integer, the store `*(s16 *)(qi + 6) = 0;` — gcc would emit `sh zero,6(qi)` ✓ (an indexed store). And the 4th store `*(s16 *)((s32)D_801AAD6C + off)` → `lui at; addu at,at,off; sh zero,0(at)` ✓ (as the target).

Hmm, but would gcc merge the two (both are base+off)? The 4th store's address is (symbol + off) and qi's value is (symbol + 8*i) — hmm, gcc would have to know off == 8*i to unify. In the current C, gcc DID unify them (the store became q[0]) — so gcc knows off == 8*i (loop.c's IV analysis) ✓. So even with an integer qi, gcc might unify ✗.

Hmm.

OK, let me consider the alternative: maybe the re-basing can be prevented by a different route: what if the q stores use an offset that can't be reduced? Hmm.

Let me try to look at the loop dump to see the exact optimization. Let me grep the .loop dump for the IV analysis of the loop in both files.

Let me look for "ivcanon" or "Induction variable" in the loop dumps.

Hmm, the .loop dump in gcc 2.7 prints the loop optimization info. Let me diff tree.i.loop and c1.i.loop.

Let me do that — it's cheap since I have bothdumps.
