---
ts: 2026-11-06T06:17:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hElpV2XglKfRALKCs8s1
---
w4 is worse (36). The second do-while disturbed other allocations. Let me check the diff... Actually, maybe wrap only the arg copy differently.

Alternative: keep w2 and add a *use* of otz before the copy that survives. Hmm.

Let's reconsider: In w2, combine folds 151+164. What if we split by putting a *label* — e.g. a `goto` — between? That would change control flow.

What about putting the func_801823D4 call inside an `if (i < 12)` (always true)? It creates a conditional block; combine won't cross. But it adds a branch (bnez) — extra insn. No.

What about the do-while wrapping only the *arg*? can't.

Hmm, w4's 36 suggests the second do-while boosted many refs. Let me look at what w4's diff is — maybe just registers.

Alternatively: wrap the *first* call in do-while (as w2, good) and put the a0 copy inside the same loop block right after? i.e.

```
do {
    otz = RotTransPers4(...);
    otz = func_801823D4(otz, -0x1A);
} while (0);
```
Then both in the same block → combine folds. No.

Hmm. What if we wrap the *copy* alone in a do-while but place the do-while *after* the call inside the first loop... same block.

Let me think again about how func_8018302C was cracked: "the copy wrapped in do-while(0) (loop-shaped live range) — or v1,v0 survives". The copy was a standalone statement `v = t;`? Wrapping a copy statement in do-while(0) gives the copy a loop-shaped live range... The do-while creates a loop block containing the copy; the source (t) is defined outside. Combine won't fold across the loop boundary because the loop can execute multiple times (in RTL terms), so the copy's source isn't dead.

Wait, but in my case the "copy" IS the call's argument setup, not a C statement. To wrap it, I'd need the C statement `otz = func_801823D4(otz, -0x1A);` — the a0 copy is part of that statement. That's what w4 did, and it disturbed things (score 36). Maybe the disturbance is because the *call* moved into a loop block, changing the loop structure for loop.c/sched.

Hmm. w4's score 36 — let me look at the diff to see if it's a different class of problem. Actually let me first check whether the move pair is fixed in w4.

Let me run dt.sh on w4 with tail 6.
