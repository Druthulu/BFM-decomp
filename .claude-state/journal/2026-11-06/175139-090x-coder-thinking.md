---
ts: 2026-11-07T00:51:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QrfXqKmL604qYlkaDJma
---
Target: s0 = D_800AF630 (base, no offset), then two `addiu a0,s0,24`.

So the compiler kept the *symbol base* in s0 and computed +24 at each call site.

In mine: s0 = D_800AF630+24 (the sum) and the calls pass `move a0,s0`.

Which C produces the target? If the source is `func_8004914C(&D_800AF630[0x18]); func_800491AC(&D_800AF630[0x18]);` — the address is `(plus (symbol_ref) 24)`. The compiler would materialize that address: lui+addiu with %lo(D_800AF630+24) folded → s0 = the sum, then move. That's MY shape, not the target's.

For the target, the compiler materialized the BASE and did two addiu's — meaning cse/combine did NOT fold the two `mb+0x18` into one constant, and the base was kept in s0.

Hmm, so how would the original C produce that? Maybe the original C used `mb` for something else too, or the two calls used *different* variables.

Wait — maybe the original C is:
```
func_8004914C(&D_800AF630[0x18]);
... other code ...
func_800491AC(&D_800AF630[0x18]);
```
and the two address computations are in different basic blocks (there's code between them)? In the target, the two calls are adjacent (c6c8 and c6d0) with nothing between. So no.

Alternatively, the original C might have used a `u8 *mb = &D_800AF630;` and then `func_8004914C(mb + 0x18); func_800491AC(mb + 0x18);` — cse folds mb+24 to a constant, keeps the sum in s0. My shape.

So the target's shape requires the base to be kept. What if the two uses are `mb + 0x18` and `mb + 0x18` where `mb` is NOT known to be constant — i.e., the original C had `mb` loaded from memory. E.g.:

```
u8 *mb = D_800AF630_ptr;  /* no */
```

Hmm. OR the original C passed `&D_800AF630[0x18]` to the first and `&D_800AF630[0x18]` to the second, and the compiler kept the *symbol* in s0 because the constant `D_800AF630+24` was expressed as `(plus (symbol_ref) 24)` and reload's `mips_move_1` split it... 

Hmm, let me test the simplest variants and see the score:
- w2: no local mb; direct `func_8004914C((u8 *)&D_800AF630 + 0x18);` twice.
- w3: `func_8004914C(&D_800AF630[0x18]); func_800491AC(&D_800AF630[0x18]);`
- w4: mb local as now (w1).

Also:
- w5: use a `u32` base: `u32 base = (u32)&D_800AF630; func_8004914C((void *)(base + 0x18)); ...`
- w6: `s32 off = 0x18; func_8004914C(mb + off);` — off is a constant variable; cse may fold.

Let me try a batch. The function is big (397 ins) so each score takes longer (~1-2 s). Fine.

Let me create variants by editing the three `mb` blocks. The pattern per face:
```
    mb = (u8 *)&D_800AF630;
    func_8004914C(mb + 0x18);
    [launder removed]
    func_800491AC(mb + 0x18);
```

Variants:
- v2: `func_8004914C((u8 *)&D_800AF630 + 0x18); func_800491AC((u8 *)&D_800AF630 + 0x18);` (drop mb entirely)
- v3: `func_8004914C(&D_800AF630[0x18]); func_800491AC(&D_800AF630[0x18]);`
- v4: keep mb but declare it at the top (function scope)
- v5: `mb = (u8 *)&D_800AF630; func_8004914C(mb + 0x18); mb = (u8 *)&D_800AF630; func_800491AC(mb + 0x18);` (re-assign)
- v6: dead reset between: `mb = 0;` then re-assign
- v7: `u8 *mb2 = (u8 *)&D_800AF630;` for the second call
- v8: pass `mb + 0x18` and `mb + 0x18` where mb is declared as `volatile`? no.

Let me write a generator that rewrites all three occurrences.

I'll write gen.py for item 3.
