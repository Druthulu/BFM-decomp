---
ts: 2026-11-06T11:03:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RNPmDbKazrolJNANFUY6
---
All variants are ≥4; x_ns16 = 4 (best). No crack.

Time: ~04:45. I've spent ~15 min on this item. Let me try a couple more targeted things, but I should also handle the 4th item.

Given the pattern (all walls), maybe I should be efficient: for item 3 and 4, do a reasonable set of tries (30+) and record walls. The task is a "singleton crack shard" but if these are genuinely walled, that's the honest result.

But wait — let me reconsider. The moves.md and walls.txt show many similar items cracked. Maybe there's a smarter real-C move for the RC-12 opaque copy. Let me grep the cookbook for "opaque copy" / "RC-12".

Actually the walls list has `cse-opaque-copy` as a WALL tag (from G07): "the plain copy t = v is dissolved by cse/combine; the target keeps an opaque $0-add copy (move s8,v0); no plain-C spelling survives". So this class is a known wall.

But our case isn't a copy of a value; it's a constant 3 that must survive noop-move deletion. Hmm.

Let me check: is there a known MATCH for a similar shape? moves.md line 74: "pin | func_801EE8C4 | MATCH — s32 a = arg0 (1st store target), param arg0 reused for the p1 load; p2 own local: param pseudo's stale refs (a0 copy combined) reorder local-alloc qtys (G02)". Not our case.

Given time, let me do a quick sanity check on the second big item (func_8018B238) to see if its lever-free base scores similarly, then decide.

Actually, let me try one more idea for the n=3: what if `n` is assigned `3` via a *different constant type*: `n = 3u;`? or `n = 3L;`? Hmm.

Or `n = (n = 3);`? no.

What if the else branch is `n = 4 - 1;`? combine folds to 3. But the *rtx* might be different at cross-jump time? combine runs before jump2. Folds.

What about `n = D_80115126 == 3 ? 3 : 3;`? folds.

What about making the outer else's n assignment depend on something opaque but real: `n = i + 3;` with i = 0? i is assigned 0 AFTER the n block (`i = 0;` comes after). If I move `i = 0;` before the if, then `n = i + 3` in the else would be `addiu v0,s?,3` — not `li v0,3`. Wrong.

What about `n = 3 + (D_8011511A - D_8011511A);`? folds.

Hmm.

What if the target's `li v0,3` is not the else's n=3 but something else? Let me check the target: f80 li v0,3 in the delay slot of the bne at f7c. Then f84 loads D_8011511A... The else branch target is fb4 (the loop start after `beqz v0`?). Actually f7c bne v1,v0,fb4: if D_80115126 != 3, jump to fb4. At fb4: `beqz v0,1010`. And v0 = 3 (from the delay slot copy!). So the else path jumps to fb4 with v0=3, then beqz v0 → not taken, then fbc move s3,v0; fc0 loop.

So the else's `n = 3` was compiled into the delay slot (copied from fb0 `li v0,3`, which is the fall-through of the inner then's `n=3`). So the two n=3 sites ARE cross-jumped: fb0 is the shared `li v0,3` (the inner then's n=3), and reorg copied it into the bne's delay slot.

Hmm, wait: the inner then's n=3 is at fb0 (after the call). The outer else jumps to fb4. So the cross-jump merged the else's n=3 into the then's n=3 at fb0. And reorg copied fb0 into the bne delay slot.

So a plain C `n = 3` in both places gives this cross-jump, but the noop-move deletion removes the else's `n=3` because v0 already holds 3.

Wait, if the else's `n=3` is deleted, then the bne's target would be different. In my base, the target at 60 is a nop (the delay slot is empty) — meaning the cross-jump target exists but the delay slot wasn't filled? The diff at position 60: mine nop vs target li v0,3. And at 73/83 the branch targets differ.

So in my base, the cross-jump target exists (the code is otherwise similar) but the delay slot isn't filled with the li. Hmm, and the branch offsets differ by 4.

Let me look at my base's listing around 55-65 to understand.
