---
ts: 2026-10-21T23:55:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_DhJwmcaQXME9itNjTTUR
---
Same 17. The do-while didn't change anything (the set is still folded).

I've spent ~40 min on item 3. Let me record it as a WALL (best 17) with a tag, and move on. I'll name the tag: "const-fold-return" — "combine folds the constant 1 into the return copies; the pseudo dies, so $2 stays free for the compare temp; the ROM's single li $2,1 in the chain block needs the hard-reg pseudo".

Wait, but the results.tsv format wants: `dir file func kinds result best tries wall evidence` where result=MATCH|PARTIAL:<kinds>|WALL, best = the lowest score of a lever-free body (17), tries = number of attempts (I'll count: nopin(prior), A, B, C, D, E, F, G, H, I, J = 11 by me + the prior nopin), wall = tag, evidence = "gcc pass + mechanism ≤ 140 chars".

Let me now move to the next items and come back to item 3 later if time permits.

Actually hold on. Before walling item 3, let me try ONE more idea that just came to me: what if the "1"-pseudo's copies are not foldable because the arms return it through a *different* function-level construct — e.g. the function's return type is s32 but the value returned is a `u16`? no.

Hmm, alternatively: what if we make the "1" be a variable of type `s32` but assigned from the *comparison* `arg2 == v1` in a way that produces 1 in all arms... no.

Hmm, what about this: the four arms could return a value derived from a variable that's set to 1 in a way that gcc materializes in the chain block: e.g. `v0 = 1;` where the copy is `set $2, v0` — the copy is foldable ONLY if the pseudo's value is known to be 1 at that point. gcc's combine does this. BUT if the pseudo is a *volatile* or has "preserved" attributes...

What if the pseudo's set is in a DIFFERENT basic block than the copies (so combine can't fold)? E.g. if the "1" is set in the outer block (before the mask test) and used in the inner block. Then combine would need to prove the value across the branch — it can (constant propagation) but maybe it doesn't fold across blocks! Hmm! Interesting: gcc's constant propagation (cse) works per-block but propagates constants across blocks via "jump threading"...

Let me test: set v0 = 1 BEFORE the mask test:
```c
    v0 = 1;
    if (*(u16 *)((u8 *)arg1 + 0x0) == 0) return 0;
    ...
```
But then v0 is live across the whole function → the "1" set would be at the function entry (ins ~0) → the bytes would differ (an extra `li v0,1` at the top) ✗.

Unless gcc sinks it. Let me just try: variant K with `v0 = 1;` right before the mask test.

Hmm, but that would also change the head (ins 0..19 must match exactly). The head has no `li v0,1` → so the set must NOT be materialized at the entry. If the pseudo survives (not folded) and is allocated $2, then the set `li $2,1` would be materialized... at the entry (where it's assigned) → ins 0 ✗.

Unless gcc sinks it into the inner block (the scheduler can sink a set into a deeper block if it's dead elsewhere? "RTL sinking" — gcc does sink sets of pseudo regs into the blocks where they're used, when the pseudo is local). Hmm! If the pseudo is local to the function and used only in the inner block, gcc's "sink" pass might move the set into the inner block ✓ — and then the delay-slot placement could follow ✓.

That's a plausible crack! Let me test variant K:
```c
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0;
    s32 v1;
    v0 = 1;
    if (*(u16 *)((u8 *)arg1 + 0x0) == 0) {
        return 0;
    }
    ...
```
Let me also test variant L: `v0 = 1;` inside the `if (*(u16*)(arg1+0x5E) != arg2)` block but before the mask test.

Let me write both and score.
