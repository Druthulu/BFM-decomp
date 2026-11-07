---
ts: 2026-11-06T10:22:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XtZY5RaR9iZxWdBLbuoB
---
f3's globals order: 78 81 97 77 82 79 76. The globals r78 (13 refs, live 8), r81 (15 refs, live 10), r77 (13 refs, live 27, crosses call), etc.

Interesting: r78 and r81 have very high refs (13, 15) because of the do-while loop weighting. They prefer a3.

The caller-saved allocation: r80 (v0, 5 refs live 6), r82, r79, etc.

Hmm, the target's caller-saved: cur=a0, iVar4=v1. Mine: cur=v1, iVar4=a3.

The difference is which qty gets which caller-saved reg. This is complex.

Let me step back. I'm at score 2 with f2 and 22 with f3. The in-place shift is the issue. 

What if I use `div = (s16)div;` (f2) but make the temp get s0? The temp is a local qty. Its priority: refs 2, live 2 → 10000. In local-alloc, it gets the first free caller-saved reg (v1). To make it get s0, s0 must be the first free... but s0 is a callee-saved reg and the temp doesn't cross a call, so it prefers caller-saved. Hmm.

Alternatively, make the temp cross the call — impossible (it's born after the call).

OK. Let me reconsider f3's caller-saved shift. In f3, `cur` is in v1 instead of a0. Why? Because the sign-ext temp disappeared, freeing a qty slot. Let me look at the .greg order and which qty is `cur`.

Hmm, this is deep. Let me try a targeted reorder: in f3, move `cur = ang & 0xFFF;` to different positions and see if cur→a0.

Let me batch:
- h1: f3 with cur computed right after ang
- h2: f3 with cur computed after a's mask
- h3: f3 with `a = a & 0xFFF` moved after the shifts
- h4: f3 with the shifts as `div <<= 16; div >>= 16;`

Let me test.

Actually, wait. Let me reconsider the do-while placement. The do-while was around the final if/else (the divisions). That boosted div's refs. But it ALSO boosted the refs of everything inside (iVar4, q, etc.) — see r78/r81 with 13/15 refs. That's what shifted the caller-saved allocation.

What if I put the do-while around a SMALLER region that contains div but not the other temps? The div is used in the divisions. The `iVar4` and `q` are also there. Hmm.

Alternatively, use a different ref-boost mechanism for div: e.g., a do-while around just the two divisions (not the `if (q==0)`)? That's what we have.

Hmm. What if the do-while is around only ONE division? That would boost div by 1 (refs 8 → floor_log2(8)=3, 3*8/26 = 9230 > a 6086). And boost fewer other temps. Let me try: wrap only the `if (diff >= 0) { q = diff / div; ... }` in do-while? Hmm, that's asymmetric and might change code.

Actually, maybe wrap just the division statement: `do { q = diff / div; } while (0);` in both branches? That's 2 do-whiles. div refs +2. Other temps +1 each.

Hmm.

Let me think about the target's caller-saved allocation: cur=a0, iVar4=v1, q=v1. In the target, these are block-local temps. The allocation order: local-alloc assigns by priority. `cur` (refs? live?) gets a0, iVar4 gets v1.

Hmm, in the target, `cur` is in a0 — a0 is the 3rd caller-saved (after v0, v1). Why a0? Because v0 and v1 were taken by other temps at cur's birth.

This is getting too deep. Let me consider: maybe I should NOT use the do-while and instead find another way to boost div's refs that doesn't perturb the caller-saved allocation.

Alternative ref boost: use div in a comparison that's already there? Hmm.

Actually — here's a cleaner idea: the division `diff / div` — what if I use `div` in the `q == 0` check indirectly? No.

What about making `a`'s refs lower by 1 (to 6)? Then div (7) vs a (6): floor_log2(6)=2, 2*6/23=5217 < div 5384 → div wins! And no do-while needed → no perturbation.

How to reduce a's refs from 7 to 6 without changing instructions? a's refs: def, andi(use+def), bne(use), subu(use), addiu(use), addiu(use) = 7.

If the mask `a = a & 0xFFF` is folded into the comparison... hmm.

What if `a` is not masked in place but the mask is applied at the comparison: `if ((a & 0xFFF) == cur)`, and the later uses use a masked temp? Then a's refs... 

Hmm.

What if the `t = a + 0x1000` and `t = a - 0x1000` use `cur - diff` instead of `a`? They're algebraically different.

OK, let me try the do-while but with a smaller scope to avoid perturbing iVar4/q. What if the do-while wraps only the division, and the rest stays:

```
if (diff >= 0) {
    do { q = diff / div; } while (0); // !FAKE: do-while
    if (q == 0) q = 1;
} else {
    do { q = diff / div; } while (0);
    if (q == 0) q = -1;
}
```
This boosts div by 2 (both divisions in loops) and q/iVar4 by 2 each too. Hmm.

Alternatively, wrap the whole function body in a do-while(0)? That boosts everything by 1, including a and div equally — no relative change. Hmm.

Wait, the relative boost: div is used 2 times in the loop (both divisions) + bnez checks; a is used 3 times in the loop. If the loop contains both, a gets +3, div +2. That's what happened? But f1 improved... Let me check: f1's do-while wrapped only the final if/else (the divisions), which does NOT contain a's uses (a is used earlier in the else block: diff, t, t). Wait, the do-while wrapped `if (diff >= 0) {...} else {...}` which is AFTER `diff = cur - a` and the t blocks. So a's uses are outside the loop. Good. So only div and q/iVar4 are boosted.

f1's div refs: 7 + 2 (2 divisions) = 9? And a stays 7. div wins. 

But the do-while also boosted q and iVar4, shifting their allocation.

Hmm. What if the do-while wraps ONLY the division statement in each branch (not the if(q==0) checks)? Then q and iVar4 get less boost. Let me try:
```
if (diff >= 0) {
    do { q = diff / div; } while (0);
    if (q == 0) { q = 1; }
} else {
    do { q = diff / div; } while (0);
    if (q == 0) { q = -1; }
}
```
Let me test this.

Also, let me try wrapping only ONE division:
```
if (diff >= 0) {
    do { q = diff / div; } while (0);
    if (q == 0) q = 1;
} else {
    q = diff / div;
    if (q == 0) q = -1;
}
```
div refs +1 → 8 → floor_log2(8)=3 → 3*8/26 = 9230 > a. Might be enough.

Let me test these two.
