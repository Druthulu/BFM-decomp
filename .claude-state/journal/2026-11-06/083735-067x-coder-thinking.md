---
ts: 2026-11-06T15:37:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vZVvA6YKmSRxTbSlfYTh
---
The target has:
```
move a0,s1
sll v0,a0,0x7
sll v0,a0,0x7
subu v0,v1,v0
bgez v0,...
```
So the target computes `d - n*128` twice: once for rem (before) and once for the test (with sll duplicated). The launder keeps the second computation.

Wait, target at 92: `move a0,s1` — n copied to a0. Then sll v0,a0,7 (n*128), then again sll v0,a0,7, subu v0,v1,v0, bgez.

Hmm, the duplicate sll suggests the target has TWO uses of n in the same expression? Or the reorg duplicated it into the delay slot.

Mine: `move v0,s1; sll v0,v0,7; ... bgez s6` — cse folded the test to `rem < 0` (s6 = rem).

So the fix: make n a real 2nd set or break the cse equivalence between `d - n*128` and rem.

Approach: `n = n;` no. What real-C move makes the recomputation survive? If the second test used `n` in a form cse can't equate: e.g. write the test as `if (d - (n << 7) < 0)` — cse still folds (same expression). 

What if we recompute `rem` after the test? e.g. reorder:
```
n = t;
if ((d - n * 128) < 0) { ... }   // test first
rem = d - n * 128;
```
Hmm, then the test's expression and rem's computation are the same; cse would fold rem into the test's result. But the target wants both computations.

Alternatively: make rem's computation use a *different* variable than n: `rem = d - t * 128;`? But t was negated... Actually t is negated if t<0 (line 47-49), so t = |n| — no.

Hmm, what about `rem = d - n * 128;` and the test `if ((d - n * 128) < 0)` where between them we do something that invalidates cse's table: a real 2nd set of `n`... 

Wait — the launder is `"=r"(n) : "0"(n)`: a second set of n. So the fix is a real 2nd set of n that is value-preserving. n = t, t = d/128. 

Since n's only use is `n * 128` in two places (and the launder), maybe `n = (s16)n` works if the value fits? d = unk102 - unk100; these are s32 fields? Let me check the types: `((Unkstruct_800B5CB8 *)param_1)->unk102` — probably s32. Hmm.

Actually wait: what does `n * 128` produce? If n were s16, the multiply would be sll anyway (n*128 = n<<7). If n fits in s16... unknown.

Let me try the "real 2nd set" variants:
- b1: `n = (s16)n;` (may add sll/sra)
- b2: `n = n & 0xFFFF;` no.
- b3: `n = n * 1;` folds.
- b4: `n = (n << 0);` folds.

Hmm. What about a different approach: instead of a 2nd set of n, break the equivalence of the *expression* by making rem's computation different from the test's: e.g. compute `rem = d - n * 128;` and test `if (d - (n * 128) < 0)` — same.

What about using a temp: `s32 q = n * 128; rem = d - q; if (d - n * 128 < 0)`: cse folds the second to the first.

What about computing rem via a *different* arithmetic identity: `rem = d - (n << 7);` and the test `(d - n * 128) < 0` — combine turns both into the same.

Hmm.

The launder makes n a new value, so `d - n*128` after it is a fresh expression, and rem (computed before) isn't equivalent. The target: it computes n*128 twice (the second one is in the test). So the target's C likely has exactly this: n = t; rem = d - n*128; <something>; if (d - n*128 < 0).

So I need a real C statement between that makes n opaque. Value-preserving real 2nd set of n...

Idea: `n = t;` where t is a *different* variable that cse can also equate... no.

Idea: use the dead-reset on a variable involved: e.g. `t = 0;`? t is used later at line 71 (`i < t`) and line 77 (`t << 7`). No.

Idea: use a `do{}while(0)` block around the test to split the EBB — cse might not fold across? The fold is within the same block (line 50-52 are adjacent). A do-while between them: `do { } while (0)` with nothing? That's a barrier-ish (C0535 allows do-while splits). Actually the moves say do-while(0) splits cse1 EBB. But here both statements are in the same block; wrapping the `if` in do-while(0) makes a new block: `rem = ...; do { if ((d-n*128) < 0) rem = -rem; } while (0);`. cse1 processes the outer block (rem=...) then the inner block. Does cse1 start a new table for the inner block? cse1 processes extended basic blocks: a new block that's not part of the EBB starts fresh. A do-while creates a block boundary → new EBB → cse table cleared → the expression isn't known → recompute!

That's promising and it's an allowed C move (with the !FAKE comment). Let me test:
- c1: wrap the if in do{}while(0).
- c2: wrap rem computation.

Also try `n = (s16)n;`.

Let me create gen.py for item 3.
