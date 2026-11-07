---
ts: 2026-11-06T15:14:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Rbsd8UU7rLSO0zcxwP7L
---
The t==5 test is `(insn 642 (set reg189 (const_int 5)))`? No, that's a constant load. The comparison for `if (t == 5)` would be a `(set (reg) (eq (reg t) (reg 189)))` or a compare. Hmm, let me look at the actual jump_insn around the t==5 test.

Let me look at the region around insn 640-660 in the .rtl dump to find the jump_insn for `if (t == 5)`.

Actually, the relevant question is where `if (t != 3)` disappears. Let me find the second `(const_int 3)` compare. Search for `(ne` or `(eq` with const_int 3 near the t pseudo.

Hmm, gcc might have represented `if (t != 3)` as `(set (reg) (ne (reg t) (const_int 3)))` then a jump on that reg.

Let me search the .rtl dump for "const_int 3" within the function region and look at contexts.

Given time constraints (item started ~08:15, now ~08:25), let me be pragmatic. The score is 4; maybe I should try a few more shapes and if no luck, record WALL with best 4.

But wait — actually let me reconsider. The launder is at a place where t is tested `t != 3`. What if instead of keeping the compare, we can get the same code with a different *branch* that the compiler can't fold: the target's `bne s0,v1,71c` where v1 = 3. What if we write `if (t != (s16)3)`. Folds.

What if we use the OTHER launder-like trick that's allowed: the `do{}while(0)` block split (C0535). The fold here is cse's jump-equivalence recording, which is per EBB. If we put a label between the t==5 branch and the test, cse's record_jump_cond would be invalidated at the label (cse resets at labels? It processes per extended basic block; a label starts a new block). The do-while(0) may or may not survive to cse.

Let me test g5/g6/g7 (do-while variants). Quick.

Also try: putting the test after an `if (s1) { }` (no).

Let me generate:
g1: `if (a1 != 3) goto sel_094;`
g2: `do { } while (0);` between the t==5 branch and the test
g3: `do { if (t != 3) goto sel_094; } while (0);`
g4: `while (1) { if (t != 3) goto sel_094; break; }`
g5: wrap the whole t==5 body in do-while(0)
g6: `if (t != 3 && 1) goto sel_094;`
g7: `if (t != 3 || 0) goto sel_094;`

Let me test.
