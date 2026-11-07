---
ts: 2026-11-06T15:47:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uys5x8S9anEW2Xd51dYS
---
The crack:
```
m1 = mid;
call1(mtx+0x34, pin, m1);
m1 = 0;
m2 = mid;
call2(m2, &out);
```
So: dead-reset `m1 = 0;` then a *new* variable `m2 = mid;`. The dead store empties cse's equivalence class for `mid` so `m2 = mid` isn't merged; call2's argument materializes as the address.

For our item 5, the analogous form:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
mb2 = (u8 *)&D_800AF630;
func_800491AC(mb2 + 0x18);
```
Hmm, but here the value is a *constant symbol*, not a stack address. cse's class for the constant `&D_800AF630` — the dead-reset `mb = 0` empties the class, so `mb2 = &D_800AF630` is... hmm, the constant class entry for the symbol would be re-created.

Actually, in func_8014964C, `mid` is an address that was already materialized in a register (m1). The dead-reset removes the register from the equivalence class; `m2 = mid` then re-materializes the address (addiu a0,sp,32) instead of reusing s1.

For our case: `mb` holds the symbol address in s0. The target does `addiu a0,s0,24` — it uses s0 (the base) + addiu. So the base IS in a register (s0), and the +24 is added per call. In mine, s0 holds base+24.

So the difference: mine's `mb+24` got folded to a single address (s0 = base+24). Target: the base in s0, +24 added at use.

The launder makes mb opaque so `mb + 24` is a real add. But for the FIRST call (before the launder), the target also has addiu. So the launder must also affect the first call... 

OH WAIT. Maybe not: maybe in the target, the first call's `addiu a0,s0,24` is the result of the *same* expression being computed per call, and the base is in s0 because `mb` itself is used... Hmm, in mine, `mb+24` folded to symbol+24 → s0. In target, the first call's arg is addiu a0,s0,24 where s0 = symbol. So the first call's arg was NOT folded.

Why would the first call's `mb+24` not fold in the target? Because with the launder, mb is "redefined" later in the block, and cse... no, the first use comes before.

Unless the RTL order differs: cse processes the whole block; the launder's set of mb might come before the first call in RTL? No, source order.

Hmm, maybe the asm's output constraint forces mb to be in a register at the asm point, and since mb is live across the call, the allocator keeps the BASE in s0 and the two `mb+24` are computed at each use. For the first use, `mb+24` is `(plus mb 24)` where mb is the register — cse's fold_rtx would substitute mb's constant (symbol_ref) → `(const (plus symbol 24))`. Would cse do that? Only if mb's value is in the cse table as a constant. In mine it did.

With the launder, mb's value after the asm is unknown, but the first use is before. Hmm, unless cse processes blocks and the whole thing is one block, and the fold_rtx for the first call's arg happens... it should.

Wait, maybe the difference is elsewhere: in the target, the base in s0 might be a *different* pseudo than mb. Let me look at the target's RTL... this is taking time. Let me just try the dead-reset + new variable pattern and see.

Variants:
b1: 
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
mb2 = (u8 *)&D_800AF630;
func_800491AC(mb2 + 0x18);
```
with mb2 declared.

Actually, since the pattern appears 3 times with different variables, maybe simpler: keep `mb` assigned but re-assign it: 
```
mb = (u8 *)&D_800AF630;
call1(mb + 0x18);
mb = 0;
mb = (u8 *)&D_800AF630;   // real 2nd set
call2(mb + 0x18);
```
Hmm, the dead-reset then re-set. cse: mb = symbol; mb = 0 (invalidates); mb = symbol again. The second `mb+24` would be foldable to symbol+24 → same as mine.

Let me just test several quickly:
b1: dead-reset + new var mb2 (declared with the others)
b2: `mb = 0;` then `func_800491AC(((u8 *)&D_800AF630) + 0x18);`
b3: use a temp for the address: `u8 *a = mb + 0x18; call1(a); a = mb + 0x18; call2(a);`? cse merges.
b4: dead-reset of mb to 0 and use mb2 = mb (copy of the base before the reset)?

Actually, wait. Let me reconsider: the target's `addiu a0,s0,24` twice means the +24 is computed at each call, i.e., the expression `mb + 0x18` is NOT constant-folded and the base `mb` is in s0. In mine, it IS folded into s0 = symbol+24 and the calls do `move a0,s0`.

The dead-reset idea: `mb = 0;` after the first call invalidates cse's knowledge of mb's value. Then for the second call, `mb + 0x18` — but mb is 0. So we need a new variable holding the base. If we write `mb2 = (u8 *)&D_800AF630;` — a fresh constant set — cse knows mb2 = symbol again, and `mb2+24` could fold. BUT: in the target, s0 is the base and the second call does addiu a0,s0,24 — the base is in s0 and NOT folded.

Hmm, so maybe the mechanism: with the dead-reset `mb = 0`, the *first* call's `mb+24` also can't fold because... no.

Let me look at the cse dump for the orig to see exactly what happens. It's decisive and I have ~10 min for this item. Let me dump the orig cse and look at the first face region.

Actually, let me just try the variants first (cheap).
