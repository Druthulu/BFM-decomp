---
ts: 2026-11-06T12:32:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KLNYqpq8xKWeNeyVYMDU
---
c2 = 62 — an improvement (the y2 min/max test order swapped: `if (y2 < mny) mny = y2; else if (y2 > my) my = y2;`). c1 = 69, c4 = 69.

Now I have 5 + 8 + 10 = 23 tries. Need 7+ more. Let me build on c2 (62): apply the same swap to the FT4 region and to the x2/x3 tests, and combine c1/c2/c4.

Variants:
e1: c2 + the FT4 y3 swap (line 267-268)
e2: c2 + c1
e3: c2 + the x2 swap (line 247-248)
e4: c2 + x3 swap (line 264-265)
e5: c2 + all swaps
e6: c1+c2+c4
e7: c2 + b3
e8: c2 + a2

Let me generate them from c2.c.

The texts:
- FT3 y2: (done in c2)
- FT4 y3: 
```
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
```
swap to:
```
                                            if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            else if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
```
- FT3 x2: `if (((PolyFT3 *)pkt)->x2 > mx) mx = ...; else if (... < mn) mn = ...;` → swap.
- FT4 x3: `if (((PolyFT4 *)pkt)->x3 < mn) mn = ...; else if (mx < ...) mx = ...;` → swap.

Let me check exact text for the x ones.
