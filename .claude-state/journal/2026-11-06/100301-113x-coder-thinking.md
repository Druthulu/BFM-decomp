---
ts: 2026-11-06T17:03:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2fzJaO9mJ9wwu5IpMjdd
---
z6 now has `subu s0,v0,s0` and `sll s0,s0,0x10` — matching the target! The only diff: mine has `move s0,v0` at 8e90 BEFORE `bgez s0`, then `bgez s0; nop; addiu s0,s0,3`. Target: `bgez v0; move s0,v0; addiu s0,v0,3`.

So mine tests s0 (n) instead of v0 (q), and the addiu uses s0 instead of v0. The target tests q and adds to q.

This is because in mine, after `n = q`, the compiler replaced the use of q in `if (q < 0) n = q + 3` with n (cse: n == q). In the target, the comparison uses v0 (q) and the addiu uses v0.

How to keep the comparison on q? If q and n are separate variables, cse may still equate them (n = q is a copy). In the target, the `%4` expansion is `q % 4`: the compiler's expansion is `temp = q; if (q < 0) temp = q + 3; ...` — the comparison uses q, the temp is a copy. So the target's source is likely `q % 4` (the compiler's expansion), not our manual `n = q; if (q<0) n=q+3;`.

But z4 (natural `n = q % 4`) gave 119 with different allocation. Hmm, z4's expansion used v0/v1 because n (the result) was in v0/v1.

Wait — with `n = q % 4`, the temp is a compiler temp (not n), and n is the result. In z4, the temp went to v1/v0 and n to... The target has everything in s0.

Hmm. Let me think about `m = (q % 4) << 16` (no n variable at all):
```
q = rand();
m = (q % 4) << 16;
if ((rand() & 1) == 0) m = -m;
```
The `%` temp is a compiler temp; the result goes to m. In the target, the temp AND the result are s0. m is live across the sign call → s0. The temp is short-lived → v1. But the target has the temp in s0 too... 

Unless local-alloc ties the temp to m: the temp dies at the subu, and m is born at the same insn. local-alloc can reuse the same register if the qty order assigns... Actually local-alloc's find_free_reg for m (born at the subu, live across calls) picks s0. The temp (born earlier, dying at the subu) picks v1. But in the target both are s0.

Hmm, unless the RTL is `(set (reg m) (minus (reg q) (reg temp)))` and local-alloc uses a copy suggestion to put temp and m in the same reg? There's `qty_phys_copy_sugg`: if there's a copy `m = temp`, they'd be tied. But here m = q - temp, not a copy.

I wonder if the target's original used a different expression: maybe `m = (q % 4) << 16;` where the compiler's `%` expansion uses m as the temp? Actually gcc's expand for `q % 4`: it computes the modulo into a temp, then the `<< 16`. The temp could be the same pseudo as m if the tree reuses it.

OK let me just try `m = (q % 4) << 16;` (no n) and see.
