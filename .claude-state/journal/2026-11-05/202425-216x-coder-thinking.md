---
ts: 2026-11-06T03:24:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PipCasGTOGFgZ4ObcO7R
---
Key: for a varying address that is a sum (PLUS) — an array element — it does NOT set all=1 (only nonscalar=1), because array elements don't invalidate scalar variables. Our store `*(u16*)(obj + 0x14)` has an address that is a PLUS (obj + 20) → treated as an array element → nonscalar only → the fixed scalar global D_80126B78 is NOT invalidated. Hence no reload.

To force all=1, the store's address must be a varying address that is NOT a PLUS and not in-struct and not QImode. E.g., a store through a plain pointer `*(u16*)p` where p is a variable (address = (reg p), not a PLUS) → `cse_rtx_addr_varies_p` true, and the address is not PLUS, and MEM_IN_STRUCT_P? If we use a pointer variable `u16 *p = (u16*)(obj + 0x14); *p = ...;` the store's address is `(reg p)` — not a PLUS → all=1 → invalidates everything, including the global → reload!

And codegen: p = obj+20 (addiu) then `sh ...,0(p)` — an extra instruction unless reload folds the addiu into the store's address (base+offset). Since p is used twice (load and store) in `*p = *p + ...`, the addiu would be needed. Hmm, but the target's store is `sh v0,20(a1)` with a1 = obj, no addiu. If we use a pointer p, the compiler would emit `addiu p, obj, 20` (1 extra insn) unless folded.

But the reload of the global is +3 insns (lui/lw/lhu...). The target has those. Mine is short 1 insn (56 vs 57). Wait, mine is 56, target 57: the diff showed mine is missing 3 insns (lui/lw/lhu) but has 2 extra? Let me recount: the diff showed:
- delete mine[18:21] (3 insns) vs target nothing
- replace mine[28:29] target[25:29] (mine 1 insn vs target 4)
- replace mine[33:34] target[33:35] (1 vs 2)
- replace mine[35:36] target[36:37] (1 vs 1: nop vs lhu)
So mine has 3 insns early (the cached global load) and target has the reloads. Net -1.

If we use a pointer for the store, we might get the reload (3 insns) plus an addiu (+1) → 57? Interesting: 56 - 3 (remove the early cached load?) ... let me just test.

Actually, let me think: with a pointer p = (u16*)(obj + 0x14):
```
u16 *p = (u16 *)(obj + 0x14);
*p = *p + (unk2A - D_80126B78[0x12]);
[barrier]
unk2A = D_80126B78[0x12];
```
The store's address (reg p) → all=1 → invalidate the global → the second D_80126B78 load is re-emitted. And the first D_80126B78 load: it's before the store; fine. The addiu p = obj+20: if p is used twice (*p load and store), reload needs the address in a register → addiu. Target has no addiu. Hmm, but maybe reload folds it anyway: the load `*p` and the store `*p` both use (reg p); reload would allocate p to a register and emit addiu. The target has `lhu v0,20(a1); sh v0,20(a1)` with a1 = obj. So no addiu in the target.

Alternatively, use TWO pointer variables? No.

What if we use a pointer only for the *store* (and the struct access for the load)? The load's address (obj+0x14) is a PLUS → nonscalar; the store via (reg p) → all=1 → invalidates. Codegen: the store's address needs the addiu unless folded. If p = (u16*)(obj+0x14) is used once (store), reload may fold the addiu into the store's address → `sh v0,20(a1)`! And the load uses the struct/PLUS form → `lhu v0,20(a1)`. That could work!

But wait, the load is `*p` if we use p for both. Let me write:
```
*(u16 *)(obj + 0x14) = *(u16 *)(obj + 0x14) + (...);
```
The store's address is a PLUS → nonscalar, no all. To make the store's address a non-PLUS, use a pointer variable for the store's address:
```
u16 *q = (u16 *)(obj + 0x14);
*q = *(u16 *)(obj + 0x14) + (...);
```
Here q's address is (reg q) → all=1 → invalidate the global. The load uses obj+0x14 (PLUS). Codegen: q = obj+20 → addiu (unless folded into the store: since q is used once, reload could fold → sh 20(a1)). And the load is lhu 20(a1) or 20(a1)... The target has both 20(a1).

Let me test this. Also the reverse: load via pointer, store via struct.

Also: the second use of D_80126B78 (the unk2A store) must be reloaded; the first use (in the obj computation) is before the store. The invalidate happens at the store.

Let me test:
s1: q pointer for the store, struct for the load.
s2: q pointer for both (addiu risk).
s3: q pointer for the load, struct store.
s4: use `*(u16*)(obj + 0x14)` but with the address written as `*(u16*)obj + ...`? no.

Let me test s1-s3.
