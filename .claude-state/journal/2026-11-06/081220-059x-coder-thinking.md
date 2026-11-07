---
ts: 2026-11-06T15:12:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h71ve44AeYhSsWZg90U6
---
All score 4 — same residual, meaning none changed the branch structure; the compiler folded all of them. Hmm, f7 also 4.

So the compiler always knows t==5 in that block and folds the test. To keep it, we need t's value to be unknown.

Hmm — what if we make the *t==5 test* not use t directly but the value to be opaque? Wait, we need the branch `bne t,3` to exist. The only way is t opaque.

What plain-C makes t opaque? Let me think about the "real 2nd set" moves: `pv = *p; pv &= mask;` — a real 2nd set. Here we could add a real 2nd set of t that is value-preserving: `t = t | 0;`? folds. `t = t + 0;` folds. `t = t & 0xFFFF`? folds to 5.

The moves that cracked: `pv &= 0xFF000000` — a real 2nd set where the value changes (it's a different value, and subsequent code uses the new value). In our case, the value must stay 5.

What if we assign t a *different but equivalent* expression that the compiler can't fold: e.g., `t = (s16)(a1 << 16 >> 16);`? The compiler knows a1's low 16 bits are 5 → folds.

Hmm.

What about using a bitfield: `struct { s16 t:16; } bf; bf.t = t; t = bf.t;`? gcc would keep it in a register/memory. Might generate extra insns.

What about making t's type `s16` and assigning from a `u8`? No.

What about the dead-reset move (C0414): "dead-reset cse-breaker". Let me read C0414.
