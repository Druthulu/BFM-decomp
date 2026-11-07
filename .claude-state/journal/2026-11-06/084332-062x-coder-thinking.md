---
ts: 2026-11-06T15:43:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BHXrQVYw1tyjst5uxL3d
---
The cse dump shows: reg 82 (mb) set to symbol_ref D_800AF630; then reg 140 = plus(reg82, 24) with REG_EQUAL const(plus(symbol,24)); then a0 = reg140, used by both calls. So cse created a *single* register 140 holding the sum and reused it for both calls.

So the mechanism is: cse folds `mb + 0x18` to the constant and materializes it once in reg 140; both calls copy from it. The target wants the base (reg 82) used with addiu per call.

With the launder, the asm makes reg 82 unknown, so the plus stays a register add, and cse can't share it as a constant.

Plain-C: need reg 82's value not to be a known constant. No plain-C construct achieves that for a symbol address. That's the wall.

Evidence: "cse1: mb=REG_EQUAL(symbol_ref) -> plus folds to REG_EQUAL(const(plus(sym 24))), one reg 140 reused by both calls (cse.c:6766-6850); CONSTANT_ADDRESS_P early-return (cse.c:2656)". ≤140 chars? Let me craft later.

But wait — the brief says evidence ≤140 chars. Fine.

Now, is a wall acceptable given the WALL rule requires 20 min? I'm at ~11 min for item 2. I should keep going to 20 min to make it a legitimate WALL attempt. Let me use the remaining ~9 min to test a couple more creative approaches and verify the wall.

One more idea from the cse dump: reg 140 is a *new* register created by cse (the sum). The target's reg 82 (base) is used with addiu. If we could prevent reg 82 from having REG_EQUAL(symbol_ref)... The REG_EQUAL comes from the assignment `mb = &D_800AF630`. If mb had a REG_EQUAL of something unknown, no fold.

What if mb is assigned from a *volatile* read? no.

What if mb is a *global* variable (not local)? Then its value is in memory; reads would be loads. But if declared file-scope static and assigned... same.

What if we *initialize* mb at declaration (`u8 *mb = (u8 *)&D_800AF630;`)? Same fold.

What if the assignment is `mb = (u8 *)&D_800AF630;` but the variable is `u8 * const mb`? same.

What if we use a *pointer to an array of structs* with a *variable index that's constant-folded late*? e.g. `mb = (u8 *)&D_800AF630; func(mb + (i << 3) + (i << 4))` where i=1? i is the loop variable... at the end of the loops i = 3. Hmm, i is used as loop counter and ends at 3. If we use i in the address, value wrong.

What about `param_2 & 1`? Not constant.

No legit way.

Let me also consider whether the wall could be cracked by a *different target shape*: maybe the target's addiu can be produced without keeping the base — e.g., if the sum is materialized once but with `addiu a0,s0,24` twice... no, that requires the base.

I'm confident. Let me also test one exotic: `func_8004914C((u8 *)&D_800AF630 + (0x18));` with parens — same.

Let me spend a few minutes on the *third* idea: maybe the launder can be replaced by a *barrier*... no, barrier is a lever kind too (not in our kinds? kinds is "launder"; a barrier would be a new lever of another kind — not allowed: "no new lever of any kind").

So the wall stands: best lever-free 6.

Actually hold on. Let me reconsider the C0414 dead-reset more carefully. The C0414 doc says cse's forward scan invalidates the equivalence at the second set, and flow deletes the dead set. In our c1, the sum reg 140 is a *new* pseudo created by cse; the dead reset on mb invalidates reg 82's equivalence but reg 140's REG_EQUAL(const...) is separate and persists. So the dead reset can't kill it. Confirmed by the dump.

But what if the dead reset is applied to the *derived* pointer (the sum)? If we name the sum:
```
mb = (u8 *)&D_800AF630;
sum = mb + 0x18;
func_8004914C(sum);
sum = 0;              /* dead reset of the SUM */
func_800491AC(mb + 0x18);
```
Then the second `mb + 0x18` is recomputed as a new reg (cse might still find the hash entry for the constant... but the hash entry's register was invalidated by sum=0!). This is exactly the C0414 pattern applied to the derived pointer! Let me test.

Variants:
- ca: sum = mb + 0x18; call(sum); sum = 0; call(mb + 0x18)
- cb: same but second call `sum = mb + 0x18; call(sum)` after reset.
- cc: p = mb + 0x18; f(p); p = 0; p = mb + 0x18; g(p).

The key: the constant expression's hash entry references the register holding the sum; resetting that register (p=0) invalidates it, so the recomputation must be a fresh addiu from the base. And the base (mb) stays in a register. This might produce target's addiu a0,s0,24!

Wait, but the reset `p = 0` is a dead set (p not used after) → flow deletes it. The doc says that's fine.

Let me test!
