---
ts: 2026-11-06T17:03:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xqzFFputaKt4HaL8jQa2
---
z7 = 18 (same as z4). The first computation matches better but the second uses v0/v1.

Interesting: in z7, the FIRST computation is close: mine[75] `sll s0,v0,0x10` vs target `sll s0,s0,0x10` — only the shift's source differs (v0 vs s0). And the second computation's temp is v0/v1.

Hmm, z6 got the shift right but the bgez wrong. z7 got the bgez right but the shift wrong.

Let me combine: the target wants the `%` temp in s0 AND the bgez on v0. In z6 (manual expansion with n), cse replaced q with n in the bgez. In z7 (natural q%4), the temp is v1/v0 (not s0) but the bgez is on v0.

What if we write the manual expansion with a separate temp variable that's NOT n, but n is the result? E.g.:
```
q = rand();
t = q;                 /* t = the %4 temp */
if (q < 0) t = q + 3;
t = t >> 2;
t = t << 2;
n = q - t;
m = n << 16;
if ((rand() & 1) == 0) m = -m;
```
where t is a new variable. The bgez would test q (v0), and t... would be allocated where? t is short-lived → v1. Still not s0.

Hmm, the target's temp in s0 is really the pin. Let me look at the pinned source's RTL to see whether the `%4` temp is literally n (the pinned hard reg). In the pinned source, `n = q; if (q<0) n = q+3; n >>= 2; n <<= 2; m = (q-n)<<16;` — n is a hard reg $16. So yes.

So the original's `%4` temp was s0. Since the same gcc chose s0, there must be a reason. What if the original source used the SAME variable for the `%4` temp in BOTH computations AND for the first modulo, making it one pseudo whose first range crosses a call? That's z3/z5-like.

In z5/z6, the first computation's n WAS in s0 (the %4 part), but the bgez tested s0 instead of v0.

Hmm, target: `bgez v0; move s0,v0; addiu s0,v0,3` — the branch tests q, the copy is in the delay slot, the addiu uses q. This is exactly the `%` expansion of `q % 4` where the temp is a *separate* pseudo copied from q. In z6 the compiler used n itself as the temp (since the source assigns n = q then modifies n), so the branch tests n.

To get the target's form, the source must be `q % 4` (temp separate), AND the temp must be s0.

What makes the `%` temp s0 in the target? If the temp pseudo is live across a call. In `m = (q % 4) << 16;` the temp dies before the sign call. Hmm.

Unless the sign rand is evaluated BEFORE the modulo in the source! Consider:
`m = (q % 4) << 16; if ((rand() & 1) == 0) m = -m;`
Evaluation: q%4 then rand. The temp dies before rand.

What if the source is:
`if ((rand() & 1) == 0) m = -((q % 4) << 16); else m = (q % 4) << 16;`
Then the rand is evaluated first, and the % temp is computed in each arm... cse would compute it once before the branch.

Hmm.

What if the original code is:
```
m = (rand() % 4) << 16;
if (rand() & 1) m = -m;
```
Two rand calls. The `%` temp: rand() returns, then the expansion. No crossing.

I'm going in circles. Let me try the hypothesis that the first modulo's s0 and the %4's s0 come from ONE variable used for both, with the `%` expansion temps being the variable itself. In z5/z6, the bgez issue arose. What if the variable n is used for the first modulo via `n = rand() % 0x1000;` (z3) and the %4 via the manual expansion with a SEPARATE temp? Then n is one pseudo crossing the call (s0), and the %4 temp is separate (v1). But the target's %4 temp is s0.

Hmm, what if the %4 temp IS n too, but the bgez uses q because the source is `n = q % 4;`? Then n = the result, the temp is separate. The temp would be v1.

Argh.

Let me approach differently: use the local-alloc dump to see what the target (pinned) RTL looks like and what the natural unpinned allocation would be. Maybe the pin's real effect is not on n at all but on the *whole block's* allocation (reserving $16 changes the qty order). The wall list has "global-hardreg-reserve — the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it". That's exactly this wall! So this item may be a known wall: the pin's $16 reservation is what makes the temps take s0.

But the brief says to try to crack it with real C moves. The moves.md has "pin | func_80184F18 | MATCH — u16 t (HImode copy escapes cse equiv) + u = arg2 + 0xD40 late..." etc.

Let me look at the pinned RTL: in the target, the `%4` temp and n are the same hard reg $16. Since n is a register variable, ALL assignments to n use $16. The compiler's expansion of the manual code assigns to n directly.

So to reproduce: we need the variable n (the one used in the manual expansion) to be allocated $16. Since the variable crosses a call only if live across one...

WAIT. In z5/z6, n WAS in s0 for the %4 part! The remaining diff is just the bgez (testing n vs q). Let me fix that: the bgez tests q in the target. In z6, cse replaced q with n in `if (q < 0)`. Why? Because n = q (a copy), and cse propagates n into the use of q. If we prevent that copy-propagation (e.g., by not writing `n = q;` but `n = q + 0;`? no)...

The target's expansion: `move s0,v0` (n = q), `bgez v0` (test q), `addiu s0,v0,3` (n = q+3). So the comparison uses q and the add uses q. In z6: `move s0,v0`, `bgez s0`, `addiu s0,s0,3` — both use n. Cse propagated n back to q's uses (since n == q after the copy). 

To stop that, make n not obviously equal to q at the test point... The test is `if (q < 0)`. If we write the condition using a separate comparison that cse can't fold: e.g. `if (q < 0)`. Hmm.

What if the source is `n = q; if (q < 0) n = q + 3;` — cse sees n = q and rewrites the uses of q to n (or vice versa). In the target, the uses of q stay q. This suggests the target's source had the temp separate from q (the `%` expansion), and the temp was s0.

OK here's another idea: maybe the `%` temp is s0 because the original source's expression made the temp live across the *first* modulo's call. Consider the source ordering: maybe the original computes both velocity values' modulos first, then the signs? E.g.:

```
q1 = rand();
q2 = rand();  ... 
```
No.

Time is passing (10:07 now, ~13 min). Let me try a couple more targeted variants:

Variant z8: manual expansion with a separate temp `t` and n as the result, where n is used for both the first modulo and the result:
```
n = rand() % 0x1000;   (n crosses the call)
func(..., n, ...);
...
q = rand();
t = q; if (q<0) t=q+3; t>>=2; t<<=2;
n = q - t;    /* n assigned again */
m = n << 16;
if ((rand()&1)==0) m = -m;
```
Here n crosses a call in its first range → n in s0; the temp t is separate → v1. But the target's temp is s0. Hmm.

Actually hold on. Let me re-examine the target's second computation's bgez: `bgez v0,8ed4; move s0,v0; addiu s0,v0,3`. The branch tests v0 = q. The temp s0 = n. So the temp IS n. If the source were `n = q; if (q<0) n = q+3;`, cse might keep q in the test if q is used elsewhere... q is used at `m = (q-n)<<16`. So q is live. Cse wouldn't replace q with n because q is still live and n is a copy — actually cse might rewrite the comparison to use n (same value, cheaper?). Hmm.

In z6, cse rewrote the test to n. In the target, it didn't. Difference: in the target, n is a HARD REGISTER ($16), so cse treats it differently (a hard reg copy can't be propagated as freely?). Yes! With the pin, n is a hard reg; cse can't substitute a hard reg for q in the comparison because... actually cse could, but the copy to a hard reg is a real set.

So the pinned source's shape differs from the unpinned one in cse's copy propagation. We need to stop cse from propagating n into q's uses.

Idea: make n's assignment not a plain copy: `n = q;` is a copy. What if we write the expansion as `n = q & 3`? No, that changes the algorithm for negatives.

What if we reorder: `if (q < 0) n = q + 3; else n = q;`? Then the test on q stays, and n gets q in the else. The target's code: `bgez v0; move s0,v0; addiu s0,v0,3` — the `move s0,v0` is in the branch delay slot, which corresponds to `n = q` in the else path (executed unconditionally as a copy). With `if (q<0) n=q+3; else n=q;`, the compiler would emit: bgez v0, L; move s0,v0 (delay); ... L: addiu s0,v0,3? Hmm, the branch structure: `if (q<0) n=q+3; else n=q;` → bgez v0, else; (then) addiu s0,v0,3; j; else: move s0,v0. That's a different layout.

Alternatively `n = q + (q < 0 ? 3 : 0);` → the test is on q, and n = q + 3 or q. That's a real C spelling! Let's see: `n = q + (q < 0 ? 3 : 0);` compiles to `slt/ bgez...`. Hmm, might emit a branchless `sra`-based sequence.

Let me try: replace `n = q; if (q < 0) n = q + 3;` with `n = q + (q < 0 ? 3 : 0);`. Hmm, the compiler might emit: `sra at,v0,31; andi at,at,3; addu n,v0,at` — different code. Not target.

The target's code is a branch. So the source is an if.

What if we write the if without a preceding copy:
```
if (q < 0) {
    n = q + 3;
} else {
    n = q;
}
```
The branch tests q. Let's see what gcc emits. Then the rest `n = n >> 2; n = n << 2;`.

But the target's `move s0,v0` is in the delay slot of the bgez, which corresponds to a fall-through copy. With if/else, the copy is in the else arm — the compiler might sink it into the delay slot. Let's test.

I'll build z8 with:
```
q = rand();
if (q < 0) n = q + 3; else n = q;
n = n >> 2;
n = n << 2;
n = q - n;
n = n << 16;
if ((rand() & 1) == 0) n = -n;
CAST_WIDTH(s32, ent, off) = n;
```
This is z6 with the if/else. Let me test.
