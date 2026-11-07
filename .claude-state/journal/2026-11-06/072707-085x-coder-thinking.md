---
ts: 2026-11-06T14:27:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Z7Z8kpxqPzmOm8UO0ns5
---
Still 6, same. So the copy is still folded (cse2 or combine) without adding a ref. Let me verify g2's flow refs by dumping.

Hmm, but dumping takes time. Let me think differently.

Actually, wait. Maybe the copy IS counted but the refs don't matter because the live_length changed. Let me dump g2's flow refs to check.

Actually, let me reconsider. The score is 6 with the SAME diff (t3/t2 swap). So the refs are likely still 11/11.

Let me try a different real-use: make i appear in the STORE address via a pointer computed with i, using the do-while(0) trick, where the pointer is used by the store (so live dest). E.g.:

```
do { d = dst; } while (0);
*d = out;
```
No i.

What about `do { d = dst + (i - i); } while (0);`? folds.

Hmm.

What if I use i to compute `dst` as a GIV: `d = src + n + i;`? Wait, dst = src + n, and then dst increments each iteration. If instead I compute `d = src + n + i` each iteration where src is the base (not incremented)... that's the array-index form.

Hmm.

Let me reconsider. What if I add a use of i that flow counts and that produces a REAL instruction which the target ALSO has? The target has exactly the instructions we have. So any real use must fold into one of them.

The existing instructions that could incorporate a use of i:
- `slt $2,$10,$12` (i < n)
- `addu $10,$10,1` (i++)
- `addu $11,$11,2` (dst++)
- `addu $9,$9,2` (src++)
- `sh $5,0($11)` (store)
- `lhu $7,0($9)` (load)

The increments: what if `src++` is expressed as `src = src + 1` where the "1" is `i - i + 1`? folds.

What if `dst++` is `dst += (i + 1) - i`? folds.

What if the increments are combined: `i++, src++` in one statement: `i++, src++;` — same RTL.

Hmm. What if `src` is advanced by a value derived from i: since i increments by 1 and src by 1 element, `src++` could be written as `src = src + (i + 1) - i;` folds.

What about using the loop counter as the store offset: `*(dst - i + i) = out`? folds.

All identity.

Hmm. What about a use of i that is real and folds into the slt via combine, but cse2 doesn't fold because the copy is across a block boundary that combine CAN cross? Is there a case where combine crosses blocks? No, combine is per-block.

Alternatively, what if the extra use is counted by flow but the instruction is deleted by sched1? sched1 doesn't delete.

Hmm.

Let me reconsider: maybe I don't need to add a ref to i. Maybe I can REDUCE dst's refs. dst = 11. If dst = 10, i wins. dst's refs: `dst = src+n` set at depth 2 (+2), store use at depth 3 (+3), increment set+use at depth 3 (+6) = 11.

What if I move the `dst = src + n` into the loop? Then the set is at depth 3 (+3) — worse (dst=12).

What if I remove the `dst = src + n` set by using `src + n` directly in the store? `*(src + n) = out;` — but then the address would be computed each iteration (src + n changes as src increments? No, src + n is wrong). Actually the store address is dst = src_initial + n + 2*k. If src increments, `src + n` would be wrong.

Hmm.

What if I use `dst` only in the store and increment, and compute the initial dst differently? The set is unavoidable.

What if dst's initial set is at depth 1? The `if (n > 0)` guard is inside the while (depth 1) and inside the `if (cmd==9)`. The block 13 is at depth 2 (inside the while). To get depth 1, dst would have to be computed outside the while — impossible (depends on arg0->data/n).

Hmm.

OK, let me look at whether the extra ref can come from a change in the loop's `n` comparison. What if the condition is `i < n` but written as `i < n && n > 0`? fold removes (n>0 known? no). Hmm, `n > 0` is not known inside the loop. Adding it would emit an extra comparison.

What if `while (i < n)` is written as `while (i < n)` and I use i in the body for the `if (out == 0 && px != 0)`? no.

Let me look at the actual target source from another angle: maybe the original had a `for` loop with i used in an array index that loop.c strength-reduced, and the STRENGTH-REDUCED code has an extra i ref in the comparison. Let me look at f3's generated loop to see how close it is. If f3's loop has i with 12+ refs but a different structure, maybe I can fix it.

Let me dump f3 and look at the loop and refs. Actually f3 scored 52 (COUNT), 239 ins. Let me look at f3's .s loop.

Let me dump f3.
