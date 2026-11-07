---
ts: 2026-11-07T00:50:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PC2H1gQkGsPF89cmiU2t
---
The launder is `__asm__("" : "=r"(mb) : "0"(mb));` — an asm that makes mb unknown after the first matrix call. The comment explains: cse unifies the second `mb + 0x18` through the class of the constant value, and combine folds the symbol.

So the pattern is: `mb = (u8 *)&D_800AF630; func_8004914C(mb + 0x18); [launder mb] func_800491AC(mb + 0x18);`

Without the launder, cse sees both `mb + 0x18` as the same constant expression and merges; the target has two adds off one base.

The real-C replacement: a "2nd set" of mb that changes its value in a way that's value-preserving but breaks the cse class. The catalog moves:
- C0414 dead-reset: `mb = 0;` between the calls, then re-set `mb = (u8 *)&D_800AF630;`? Hmm, but the target's code: two adds off one base — the base is loaded once and used twice (the comment says "two adds off one call-crossing base").

Wait, the target keeps two adds off one base — i.e., the base (D_800AF630) is materialized once and two `addiu a0, base, 0x18`? Or `addiu` twice?

The launder keeps "two adds off one call-crossing base": the base is in a register across the first call, then two adds.

Real-C moves for a 2nd set of mb that keeps the same value:
- `mb = mb;`? identity — a launder (banned).
- `mb = (u8 *)&D_800AF630; mb = (u8 *)&D_800AF630;`? cse would fold.
- The G-series move: "self-reassign stales cse" — e.g., `mb += 0;`? identity.

Hmm, the catalog says "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". So I need a REAL 2nd set that is value-preserving in a legitimate way, like the ones used in other items: e.g., `pv = *p; pv &= 0xFF000000;` (a real computation).

Here mb = &D_800AF630 (a constant address). A real 2nd set that preserves the value... e.g.:

```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630 + 0;   /* no */
```

What about using a different variable: `mb = (u8 *)D_800AF630;`? Hmm, D_800AF630 is `extern u8 D_800AF630[]` so `(u8*)D_800AF630` = the address.

Real moves that break cse without changing the code:
1. Re-load the symbol into a different local: `mb2 = (u8 *)&D_800AF630; func_800491AC(mb2 + 0x18);` — cse would still equate the two address computations... but with a *different variable*, cse's class for the constant `(plus (symbol_ref) 24)` would still merge.

2. A real 2nd set with a value that is unknown at compile time but equals mb: e.g., `mb = (u8 *)((u32)mb & ~0);` — identity launder, banned.

Hmm. Let me look at what the target code looks like, then decide.

Let me dump the target function.
