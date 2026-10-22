---
ts: 2026-10-22T10:07:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_0hIIPjMRCVuzqFdX5idQ
---
Useful techniques. §145(b): "A bare `p = r;` is a COMBINE BARRIER" — between `r = p + K` and r's uses, a redundant `p = r;` stops combine folding.

And §195-I: "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, §145(b)'s `p = r;` copy, or an asm re-tie) kills the fold; the pass is cse and the gate is `invalidate`'s `reg_tick++`".

So: a second SET of the pseudo kills cse's fold of the constant into the use!

So for item 8018483C: if p has a SECOND set (e.g. `p = r;` or `p += 0`), the fold is killed, and the copy might survive!

But `p += 0` is an identity statement (launder) — not allowed per the brief ("identity-statement launders do NOT count as a crack").

Hmm, but `p = r;` where r is another pointer variable with the same value — that's §145(b)'s copy barrier. Hmm, but that's also arguably a launder (a redundant copy that only exists to block an optimization). Hmm. The brief says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". A `p = r;` copy where r holds the same address is an identity statement → not a crack.

Hmm. So for item 8018483C, the lever-free route is blocked: any trick that keeps the copy alive is an identity/launder.

Hmm, wait. But hold on! What if the second SET is NOT an identity? E.g., what if the pointer p is legitimately set twice with different values in the original source? Not in our decomp.

Hmm. But actually — hmm! What if the second set comes from a legitimate pointer arithmetic: e.g. `p = &D_800B99DC;` and later `p = p + 0;`? identity.

OK. But WAIT: what about the cse fold being killed by a second set of a *different* pseudo in the equivalence chain? The note says "ANY second SET of a pseudo in the address's equivalence chain". The equivalence chain: the address's base pseudo. So the base pseudo p must have 2 sets.

Hmm, in the original source, maybe p WAS set twice! E.g.:

```c
    p = &D_800B99DC;
    ...
    for (...) { ... p = p + c0; }   /* the in-loop update! */
```

Look at the body:
```c
        c0 = D_801E86C0;
        *p = *p + c0;
        D_801E86C0 = c0 + 1;
```
Here p is not re-assigned (the store is through p). Hmm! But if the original source had `p = p + c0;` (an in-place pointer bump) instead of `*p = *p + c0;`... hmm, that's a different semantics (the original probably had a pointer bump!).

Hmm! Wait: the target's asm in the loop: let me look at how the store is done. If the original had `p = p + c0` (a pointer bump) then p has a second set → the fold is killed → the copy "move s0,v0" survives!!! But then the *store* would be through the bumped pointer... Let me look at the target's loop asm.

Let me dump the target's loop body.
