---
ts: 2026-11-07T01:10:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ck6hKxnFSVTtgxewXNHN
---
No reload_cse in gcc 2.7.2. So the prior note's "reload_cse" was a guess or refers to another mechanism. In gcc 2.7.2, the relevant post-reload copy propagation could be in `cse.c` (cse2, after reload?) or `flow.c`.

Hmm. The pipeline: -dc (cse), -dt (cse2), -dj (jump), -dJ (jump2), -dd (dbr). There's a cse2 pass after reload? In gcc 2.7.2, cse runs twice: `cse` and `cse2` (after reload? no, before). Hmm.

Let me instead look at the dumps for my candidate: which pass turned the store's base into $4? The .sched2 or .dbr dump would show. Let me check the dumps I have (e1.*): sched2, dbr, jump2.

Let me grep the dbr/sched2 dump for "516".

Actually the .s output already shows the final. Let me look at .i.dbr (the delayed-branch pass) or .i.sched2 (post-reload scheduler).

The pass that changed the base register: could be "flow" (dead code/copy prop) or the post-reload scheduler. Since the store is in the delay slot (dbr), the .dbr dump is after sched2.

Let me grep the .rtl/.sched2/.dbr for the store.

Actually, more efficient: let me test a few candidates directly and see which breaks the $4 base. The key is what determines the base at the final stage.

Hypothesis A: the store's base pseudo is *the same pseudo* as the call arg (because `new_var` and `(u8*)s0` are cse-folded into one pseudo), and the allocator gave it $4? No — the first store uses $16, so the pseudo is in $16.

So the store base is $16 at allocation, and something replaced it with $4 (the call arg copy) later. That's a copy-propagation after allocation: it must be in the post-reload scheduler or dbr? No, those don't change operands.

Hmm, but the .s shows `move $4,$16` before `jal` and the store uses $4. If the store's RTL operand was $16, a pass must have rewritten it.

In gcc 2.7.2, `reload` does copy propagation for the delay slot? No.

Wait — maybe it's not a rewrite: maybe the *store* was originally `sw $2,516($4)` because the compiler computed the address from $4: i.e., the store's base pseudo was allocated $4, not $16!

Look at the .lreg/alloc for this function. Let me dump the alloc table (I have dumps_e1 with .lreg).

If the store's base pseudo (new_var) got $4 (a0) and the first store's base (s0) got $16, then the source's two different expressions (`(char*)s0 + 0x200` and `new_var + 0x204`) are two pseudos with different registers!

The source:
```
  *((s32 *) (((char *) s0) + 0x200)) = v0;    // base = s0
  *((s32 *) (new_var + 0x204)) = v0;          // base = new_var (= (char*)s0)
```
If new_var's pseudo is separate from s0's and gets $4... but new_var = (char*)s0 is a copy; why would it get a different reg? Because the copy `new_var = (char*)s0` was placed AFTER the call? No...

Let me look at the .lreg dump for this function.
