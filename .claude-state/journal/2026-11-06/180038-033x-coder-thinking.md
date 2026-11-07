---
ts: 2026-11-07T01:00:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OTsV5QXe4lvAtRGGXyGF
---
x09 (flag init at decl) gets 101 ins (matching the target's ins count!) but score 59. Interesting.

Best stays 43. That's 23+12 = 35 tries (plus base). We've hit ≥30 tries.

Time check: need ≥20 min on item 1. Started ~17:57; now? Let me check date. And let me consider one more idea before walling.

Actually, let me think about x09's 101 ins: with flag initialized at decl, the compiler keeps `flag` live longer? It scored 59.

One more important idea: the *parameter copy* structure. The target's prologue order is p,b,c,a (s3,s0,s1,s2). In mine, the order is p,b,c,a too (move s0,a0; move s1,a2; move s3,a3; move s2,a1) — same order, different regs.

The register permutation: mine p=s0, b=s1, c=s3, a=s2. Target p=s3, b=s0, c=s1, a=s2.

Note that a=s2 matches. So the cycle is p→s0→? mine: s0=p, s1=b, s3=c; target s0=b, s1=c, s3=p. So it's a 3-cycle.

Priorities: p 11379, b 3333, a 1944, c 1666. Allocation order: p, b, a, c → p=s0, b=s1, a=s2, c=s3. Target order: b=s0, c=s1, a=s2, p=s3 → priorities b > c > a > p.

To flip: need b > c > a > p. Currently p > b > a > c.

Reducing p below c: p refs 11→? p's live 29: need floor_log2(r)*r < 1666*29/10000 = 4.83 → r=4 (f=2, 8) no; r=3 (1*3=3) yes → priority 1034. So p refs must drop to ≤3. Can't: p is used 8+ times.

Unless p's live length is much larger. If p's live were 100 (not 29): 330000/100 = 3300 → p between b(3333) and c? 3300 < 3333 → b > p > c > a? Then order b, p, c, a → b=s0, p=s1, c=s2, a=s3. Not target.

If p's live were 150: 2200 → order b, c, a, p? a=1944 < 2200. Hmm: b 3333 > c 1666... wait a=1944 > c=1666. Target wants b > c > a. Current b > a > c. So we ALSO need a's priority below c's. a refs 2? live 10 → 2000; c refs 3 live 18 → 1666. To flip a below c: a refs 2 live > 12 → e.g. live 13 → 1538 < 1666. So lengthening a's live range would flip a and c.

And lengthening p's live to >100 would put p below b but still above c (3300 > 1666). To get p last, live > 198.

So two live-length levers. Live length is set by flow analysis per pseudo; extending a's live range means keeping the variable alive longer in the source (using it later). E.g., use `a` after the loop in a dead way... but a dead use would be eliminated. A real use adds an instruction (target has none).

Hmm, what about a's live length: a is used in the loop (`a <<= 4`, `a >> 28`). Its live length 10? That seems short for a loop variable. Actually the prior numbers may be from the lever-free body with different structure.

This is a deep hole. The evidence says WALL: 35 tries, best 43, all lever-free bodies; the target's two copies and 3-cycle are pin/launder artifacts.

Let me do a couple more directed attempts at the *live length* lever (cheap to test):
- y00: a used after the loop via `p[3] = a;`? That adds a store — target has none. No.
- Hmm.

Actually, let me reconsider: what about splitting p into a pre-loop pseudo and a tail pseudo, with the tail pseudo being the SAME as q? I.e.:

```
  p += 5;
  q = p;
  ...
  q = <loop result>;
  r = q;
  *((u16 *)(r-8)) += 6;
```
i.e., drop `p = q` and use q for the tail. Then the tail's base is q (a0 in the target? no, target uses s3).

No.

I'll wall item 1. Best = 43 (lever-free). Wall tag: check walls.txt for "callee-saved-order".

Let me read walls.txt.
