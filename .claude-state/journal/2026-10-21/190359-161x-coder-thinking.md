---
ts: 2026-10-22T01:03:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZvMeQGTBgvvM9jKgRag5
---
The else branch in z2's compiled output is `subu v0,v1,a0` (sum - x) — the SAME as the target! So GCC kept the *first* assignment (`diff = sum - x`) and dropped the re-computation?!

Hmm, how? The re-computation `diff = *(s16 *)(s1 + 0xA) - sum;` after `diff = sum - *(s16 *)(s1 + 0xA);`...

OH WAIT. I bet GCC's CSE recognized the *commutative* pair: `sum - x` and `x - sum` are different, but... hmm.

Hmm, hold on: maybe GCC's *tree* level folded the re-computation into the original expression? Hmm.

Hmm, whatever the mechanism (maybe GCC's fold noticed that the second assignment is dead because... hmm, it's NOT dead: it's the value used in the comparison).

Hmm! Unless: the comparison `diff < 0x10` — GCC may have used the value from *before* the re-computation? No...

Hmm, hmm. Let me think: GCC's RTL for the else branch:
```
diff_1 = sum - x       (subu v1,a0)
diff_2 = x - sum       (subu a0,v1)
if (diff_2 < 16) ...
```
The comparison would be on diff_2 → `subu v0,a0,v1; slti v0,v0,16`. But the observed code is `subu v0,v1,a0` (diff_1!).

So GCC *did* fold the second assignment away. How? Because of the *do-while*! The do-while creates a loop; GCC's loop optimizer might have... hmm.

OR: GCC's CSE with the "commutative" knowledge: `x - sum` and `sum - x`... no.

OR: maybe GCC's *value numbering* (cse.c) noticed that `diff_2 = x - sum` and `diff_1 = sum - x`... no.

Hmm, hmm! Wait. Maybe the fold is in the *tree* level: GCC's fold for `a - b` vs `b - a`... no.

Hmm, let me look at the *if* branch of z2's compiled output: `subu v0,a0,v1` (x - sum) — the same as the target's if branch ✓. And the else branch: `subu v0,v1,a0` (sum - x) ✓ = the target.

So BOTH branches match the target, i.e. GCC dropped my re-computations entirely?! Hmm, in the if branch, the re-computation is `diff = x - sum` — the same as the original → CSE folds it (the same expression) ✓ (that's fine and expected).

In the else branch, the re-computation is `diff = x - sum` — the *negation* of the original `sum - x`. GCC dropping it would be a bug... but the compiled code shows the original value used.

Hmm! Unless GCC's fold recognized: the comparison `diff < 0x10` where diff = x - sum... and the *else* branch is entered when x - sum < 0 (i.e. sum - x > 0). Hmm.

Hmm, whatever. Hmm, but hold on: is the *behavior* correct? The compiled code is byte-identical to the target → the behavior is identical → the crack is faithful *in effect*. But the C source is confusing/wrong-looking (it computes diff = x - sum after diff = sum - x).

Hmm, this bugs me: the C says one thing and the compiler does another (dropping the second assignment). That's a *compiler-dependent* behavior — fragile. And a reviewer would say the C is wrong.

Let me instead find a *clean* variant for the else branch: the re-computation should be the *same expression* as the original assignment in each branch:
- if branch: `diff = *(s16 *)(s1 + 0xA) - sum;` (the same as the original) ✓
- else branch: `diff = sum - *(s16 *)(s1 + 0xA);` (the same as the original) ✓

That's a clean "real 2nd set" in both branches (each re-computing the same value). Let me build that variant and score it.

Let me write it by hand.
