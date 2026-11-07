---
ts: 2026-11-07T00:11:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_It4IMcPd0qd5mW5wxwzB
---
I could import delever_search and call score_file repeatedly with a namespace. That would avoid process startup. But the Scorer might be reused. Let me look further to see if there's a lighter function.

Actually, let me just use the tryinc.py wrapper in a loop but with fewer candidates: maybe 60 permutations is enough (or restrict to permutations where x0 stays late, etc.).

Actually, let me think about what's likely: the target's C order. Given the target assembly order:
```
move s1,a0     (x0 = a0?) 
move s2,a1     (y1 = a1?)
addiu s5,s2,-3 (y0 = a1-3)
addiu s0,s1,3  (x1 = a0+3)
addiu s2,s2,3  (y1 = a1+3)
li s4,255      (white)
addiu s1,s1,-3 (x0 = a0-3)
```
Hmm, this is the scheduled order. The RTL order is likely the C order.

Since sched1 mostly preserves order for independent statements, the C order is probably close: x0 first (move s1,a0), then y1/y0, then x1, then white, then x0's -3? That doesn't make sense.

Hmm, actually `move s1,a0` is `x0 = a0` then later `addiu s1,s1,-3` is `x0 = x0 - 3`. So the C might be `x0 = a0; ... x0 = x0 - 3;`? No.

Or the compiler does `x0 = a0 - 3` as move+addiu split by scheduling.

Let me just brute force the permutations of the 5 statements. 120 candidates.

Let me write a script that uses the tryinc wrapper via subprocess but in parallel? No, keep it simple: sequential, 120 × ~1.5s = 3 min.

Actually, let me first check the speed of one tryinc call: the earlier loop of 24 took... I didn't time it, but it completed reasonably. Let me time 1.

Let me just run the 120 in a script with output only for scores < 26.

Let me write it.

Actually, a smarter approach: only the *birth order* matters for qty numbering, and live lengths for pri. Let me generate all 120 permutations and score, printing all scores < 26.

Let me write the script to run tryinc via subprocess and capture.
