---
ts: 2026-10-22T08:16:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_uPV9X4GdYc9AxNjIsi8q
---
w6 (hoisted copy) gives EXACTLY the target shape:
```
lh v0,0(a0)
nop
bnez v0,40
move v1,v0      <- the copy in the delay slot!
j 44
li v0,30
40: addiu v0,v1,-1
```
That's the target's structure! (`move v1,v0` in the bnez delay slot, `addiu v0,v1,-1` in the else block.)

w5 (same block) → sll/sra (the sign extension materialized) ✗.

So the hoisted copy (in the entry block, use in the else block) works.

Now let me apply this to the real 80182ED4:

```c
        t = ((Unkstruct_80182ED4 *)arg0)->unk84;
        tmp = (s16)t;
        u = tmp;
        if (t == 0) { ...; t = 0x1E; }
        else { t = u - 1; }
```

Concern: u is live across the calls in the t==0 branch → callee-saved reg. In w6 there were no calls. Let me test in the real function.

Hmm, but in w6, `u = tmp` was hoisted and u is live across the branch. In our function the calls are in the t==0 branch. u is dead on that path → shouldn't need callee-saved.

Hmm, but gcc's global_alloc: u is a global pseudo (live across the branch). gcc's global_alloc assigns hard regs; for globals it prefers callee-saved regs but checks "the pseudo is live across calls". The live-across-call computation in gcc's global_alloc uses `live_across` per block. In the t==0 block, u is dead → not live across the calls there.

Hmm, but there's a subtlety: gcc's global_alloc has a rule that a global pseudo that is NOT live across any call can still use a call-clobbered reg, but the ORDER of preference puts callee-saved first. Let's just test.

Let me write c6 with the hoisted copy and score it.

Note: `tmp` must be declared at the top (C89 style, gcc 2.7). Let me put `s16 tmp;` at the function scope.

Also note: the target's `move v1,v0` is at the bnez delay slot. In our version, the hoisted copy is before the branch → the delay-slot filler should put it in the bnez delay slot. But there's also the first branch `beqz v0,813c` (the unkC2 test) whose delay slot is a nop — the copy comes after that branch (it depends on the lh which is after). ✓

Let me write it.

One concern: the hoisted `u = tmp` executes on the t==0 path too (where u is dead). The copy `or v1,v0` would be in the delay slot → executes always ✓ (matches the target).

Let me write c6 and score.
