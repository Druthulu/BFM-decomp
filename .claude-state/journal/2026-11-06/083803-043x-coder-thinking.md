---
ts: 2026-11-06T15:38:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kY7Uz8HFisFsQXYJO4tm
---
The catalog mentions: "A named derived pointer `q = p - k` that cse keeps as a REGISTER address (`find_best_addr`, `cse.c:2656-2721`) — the `la` lever." That's about cse keeping a derived pointer as a register address.

For our case, we want cse NOT to fold. Hmm.

Maybe the right move is the opposite: make the base a *named derived pointer* so cse keeps it as a register address rather than folding into the constant. E.g.:

```
mb = (u8 *)&D_800AF630;      /* base */
mb = mb + 0x18;              /* derived: cse keeps register address? */
func_8004914C(mb);
func_800491AC(mb + 0x18);   ??? 
```
No.

Hmm, wait. Let me reconsider: what if the target source is actually:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
and gcc *naturally* produces the addiu per call when the base is a *derived named pointer kept as register*? The "find_best_addr" move: a named derived pointer `q = p - k` that cse keeps as a REGISTER address. So if we write:

```
mb = (u8 *)&D_800AF630;
mb += 0x18;              /* derived named pointer */
func_8004914C(mb);
func_800491AC(mb);       /* ??? */
```
No — target has addiu per call, so the base register holds base, and each call adds.

Hmm, actually what if the target source has:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
and the compiler (real 2.7.2) DOES produce addiu per call when the variable is not laundered... but our compile produces the sum in s0. Wait, but this body IS the target source (with launder removed)? The launder was added by the decomp author because without it the code differed. So the original source presumably had something else.

Let me try to find the original PSX source shape. The function is func_8018AD9C in ov_SC06_033. This is the "POLY_GT4 emitter" (face rendering). The pattern with mb = &D_800AF630 + 0x18: The original source likely had something like:

```
SetRotMatrix((MATRIX *)0x1F800000?) 
```
No, these are func_8004914C/AC which are "set matrix" helpers. Actually func_8004914C and func_800491AC might be "SetRotMatrix" and "SetTransMatrix" — no.

The calls take `&D_800AF630 + 0x18` — a global matrix. Hmm.

What if the original code passed the *struct field*: `func_8004914C(&D_800AF630.matrix)`? Still constant.

The key question: how did the original compiler produce s0=base and two addiu? If the original code was `func_8004914C(mb + 0x18)` twice with mb constant, it would produce the sum like ours. So the original must have had something making mb non-constant. OR the original had a different expression like:

```
func_8004914C(&D_800AF630[6]);   /* u32 array index? */
```
Hmm, if D_800AF630 were declared as a `u32 *` or an array of a larger type, `&D_800AF630[k]` with a symbol still folds.

What if the original used a *struct pointer* and `->` field access with a field at 0x18 — `func_8004914C(&mb->field)` — cse folds to symbol+24. Same.

What if the base was loaded from a global pointer variable (like `D_800AF630` is itself a pointer variable, and mb = *D_800AF630_ptr)? Then there'd be a load. Target has `lui s0,%hi(D_800AF630); addiu s0,%lo` — no load. So the symbol itself is the address.

Wait, actually the target's `lui/addiu s0` could also be loading the *address* to pass somewhere... yes it's the address.

Let me look at the actual original assembly in the target to see if s0 is used for the base in all three sites, and whether there's any other use of s0 between. Let me disassemble the full target (orig.dis) and look at the s0 uses.
