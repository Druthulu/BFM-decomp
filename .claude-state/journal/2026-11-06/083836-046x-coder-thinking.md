---
ts: 2026-11-06T15:38:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_io1TXEff0qjsK37YXCoT
---
Key: `if (... || CONSTANT_ADDRESS_P (addr)) return;` — cse does not try to keep a register address for a constant address. So `(plus (symbol_ref) 24)` is a constant address → cse returns early, and later when it materializes, it uses the constant.

So a constant address can't be kept as a register-derived address via find_best_addr. That's why it folds.

The launder makes mb a REGISTER (not constant), so `mb + 24` is not CONSTANT_ADDRESS_P → cse handles it, and keeps the register base.

So we need mb to be a REG (not a constant expression) at the point of `mb + 0x18`. Plain C cannot make a variable assigned a constant be a non-constant to cse... unless the variable's value is set by something cse considers unknown.

Wait: what if we set mb from a *parameter* or a load, but arrange it to be the same address at runtime? No.

What about using `(u8 *)&D_800AF630` but the target is a *different* symbol that is also a constant... no.

Hmm, what if the base is the address of a *local* array that the linker places... no.

OK, so maybe this item is a WALL (cse-const-addr). But wait — the brief says MATCH or WALL with evidence. Before declaring a wall I need ≥20 min and ≥30 scored tries. We're at maybe 12 tries. Let me think of more approaches, but this looks like a genuine wall: plain C can't hold a constant address in a register without cse folding it.

But hold on — there might be a way: make the *second* use not share by using a struct copy or a different expression tree that cse doesn't fold to the same hash. The hash is computed on the RTL expression; two identical constant expressions hash the same. So they will always merge.

Unless the two expressions differ in RTL, e.g. one is `(plus (symbol_ref) (const_int 24))` and the other is `(plus (symbol_ref) (const_int 8) (const_int 16))`? fold_rtx folds them to the same. Hmm.

What if one is `(plus (symbol_ref) (const_int 24))` and the other is `(symbol_ref + 24)` via a different base type (e.g. pointer to a 4-byte struct then +6)? fold_rtx would fold to +24.

What if one use is `(reg)` holding the address and the other is constant? To get a reg holding the constant address, we need cse to have put it in a register — cse does materialize constants in registers when beneficial. E.g.:
```
u8 *mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
The first use through mb: cse sees mb as equivalent to the constant symbol. `mb + 24` folds to the constant expression. Same as the second. Merge.

Hmm.

What if we make the base pointer *opaque* by taking it through a function-like construct that gcc can't see through, but that produces no code? E.g. a `static inline`? No inline in C89? The compiler may not inline.

What about `mb = (u8 *)&D_800AF630; if (mb) ...`? That adds a branch.

Honestly, this looks like the cse-const-addr wall. But let me check the exact wall evidence tag and whether the moves file has an entry for this function already (maybe another shard tried it). grep moves for func_8018AD9C.
