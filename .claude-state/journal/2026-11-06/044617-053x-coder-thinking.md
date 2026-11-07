---
ts: 2026-11-06T11:46:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_O2gIplm7P0CGuFfEx0DA
---
exp_equiv_p for MEM compares the elements (address and mode) but NOT MEM_IN_STRUCT_P or MEM flags. So two MEMs at the same address/mode are equivalent regardless of in_struct. So the struct-member trick does NOT make cse treat them as distinct in exp_equiv_p.

But the moves.md lines say struct-member reads force a reload. How? Because of the *hashing* (hash_arg_in_struct) affecting whether a store invalidates them. The reload is forced not by load-load distinction but by a STORE between them that invalidates the scalar entry but not the in_struct entry (or vice versa). Let me reconsider.

In func_80175820: "struct-member u16 load sq->v for D_800B9A02 (in_struct): the nonscalar ptr[2] store invalidates it, cse re-loads *q after the store". So the store is between the two loads, and the in_struct marking makes the store invalidate the load.

In our function, the stores (0xCE, 0xCC) are AFTER the d0 load, not between. So no store between the top load and d0 load. Hmm.

Wait — actually, is there a store between? Let me re-read the target order:
1 lh v0,208(a1)   <- top load 0xD0
...
11 lh a0,208(a1)  <- d0 reload
14 sh v1,206(a1)  <- store 0xCE
15 sh v1,204(a1)  <- store 0xCC

No store between. So the reload is genuinely a second load with no intervening store. The barrier (memory clobber) is what forced it. There's no store to exploit.

Hmm. So the only way is to make the two loads non-equivalent in exp_equiv_p. Since exp_equiv_p compares address and mode, I need different addresses or modes.

Different mode: top load s16, reload u16? But target reload is `lh` (s16). If I make the top load u16 (`lhu`), that's wrong. If I make the reload u16, wrong (lhu). 

Hmm, but wait — the target reload `lh a0,208(a1)`. Could it be produced by a u16 read that's then used as s16? `d0 = *(u16*)(a1+0xD0);` would be `lhu`. No.

Different address expression that folds to the same? exp_equiv_p compares the actual RTX address. If I write the reload as `*(s16*)(a1 + 0xD0)` and the top as `*(s16*)(a1 + 0xD0)`, same. If I write the top as `*(s16*)(a1 + 0xCE + 2)`? folds to same. 

What if the top uses a different base register that's equal? No.

Hmm. What if I make the reload go through a different pointer variable `a3 = a1; d0 = *(s16*)(a3+0xD0);`? exp_equiv_p compares addresses; a3+0xD0 vs a1+0xD0 — if a3 and a1 are different pseudos (not cse-equal), the addresses differ → not equivalent → reload survives! But a3 = a1 copy would coalesce, making a3 == a1 (same pseudo) → equivalent. Unless the copy is opaque. Circular.

What if a3 is derived differently, e.g., `a3 = (u8*)(a0v + 0xD0)` and reload is `*(s16*)a3`? The address `(plus a0v 0xD0)` vs `(plus a1 0xD0)`. If a0v and a1 are different pseudos... but a1 coalesces to a0v. Hmm. If a1 coalesces to a0v (same reg), then addresses equal.

OK so the reload is tied to the a1/a0v coalescing.

Let me reconsider: maybe the whole function is a WALL for these opaque copies. But let me check the G07 lineage: func_800D0D7C, func_8003DF8C were "resident_jr" functions (resident = main binary). Our function is ov_SC05_008. Different.

Let me look at whether there's a sibling in the SC05 cluster that was cracked. Let me grep moves.md for "SC05" or func_8018xxxx. Hmm.

Actually, let me reconsider the problem from the target's register allocation. The target has:
- a0 = a0v (arg)
- a1 = copy of a0v
- v0, v1, a2, a0 (reused for d0)

The `move a1,a0` suggests a1 is a distinct pseudo. The `move v1,a0` (cpy=d0) suggests cpy distinct.

Given the difficulty, let me check: is there a known crack for "entry addu copy"? Let me grep moves.md for "entry" or "move a1,a0" or "addu $a1".

Let me also check the cookbook index for "opaque copy" or "cse-opaque".

Let me grep cookbook index.
