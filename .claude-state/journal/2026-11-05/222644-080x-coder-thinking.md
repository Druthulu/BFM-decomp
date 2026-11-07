---
ts: 2026-11-06T05:26:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MTeR6jLs4YAPl1b1qQrC
---
Now I understand the cse behavior:
- A store at a varying address that is a PLUS (array/struct element) with mode != QImode → `nonscalar = 1` (invalidates all but scalar variables), but NOT `all`.
- So the global `*q` load is a *scalar* variable (MEM_IN_STRUCT_P false, not a PLUS address? `(mem:HI (reg))` — a plain reg address) → treated as a scalar, NOT invalidated.

Wait, the global load `*q` is `(mem:HI (reg q))` — address is a REG, not a PLUS. `cse_rtx_addr_varies_p` true (reg). The store is `(mem:SI (plus (reg ptr) 8))` → PLUS → nonscalar only. So the scalar load survives. That's the wall.

To make cse invalidate the global load, the store must set `all` (address not PLUS and not MEM_IN_STRUCT_P, mode != QImode) — e.g., a store through a plain register address `(mem:SI (reg))`. Hmm: `*p2 = ...` is `(mem:SI (reg))` → that WOULD set all. But that store is *after* the *q reload we care about... Actually the sequence:

1. `ptr[2] = ...` (PLUS store) — doesn't invalidate scalar `*q`.
2. barrier (invalidates everything)
3. `p2 = ...` uses `*q` → cse should reload if invalidated. In the target it reloads.
4. `*p2 = ...` store through reg.

In the lever-free candidate, the second use of `*q` at step 3 is forwarded from step 1's load because the PLUS store didn't invalidate scalars.

Could we make the first store not a PLUS? E.g., store via `*(u32 *)((u8 *)ptr + 8)` — still PLUS. Via a plain `u32 *p8 = &ptr[2]; *p8 = ...`? The address is still PLUS at RTL.

What if we store through a `struct` pointer: `((S *)ptr)->f0 = ...`? Still PLUS.

What if the store is to a plain pointer `*ptr = ...` (no offset)? Then the address is `(reg)` → `all = 1` → invalidates the scalar → cse reloads! But the source is `ptr[2]` (offset 8). We can't change the address.

Hmm, what about making the *load* of `*q` not scalar: if `*q` were loaded through an address that's a PLUS, e.g. `*(u16*)((u8*)&D_800B9A02 + 0)`? The address might become `(plus (symbol_ref) (const_int 0))` — a PLUS with a symbol? `cse_rtx_addr_varies_p` — a symbol_ref address doesn't vary, so no. Hmm.

What if the load is `((u16 *)&D_800B9A02)[0]`? Same.

What if we declare `D_800B9A02` as an array `u16 D_800B9A02[1]`? Then `D_800B9A02[0]` → `(mem:HI (symbol_ref))` — doesn't vary.

The wall is: the scalar global load is cached across the PLUS store. To break it, the store must be `all`-invalidating. A QImode store would also be treated as `all` (since `GET_MODE != QImode` fails → all=1). Wait: `if (! ((MEM_IN_STRUCT_P || PLUS) && GET_MODE != QImode)) writes_ptr->all = 1;` For a PLUS store with QImode → the condition `((...) && GET_MODE != QImode)` is false → `!false` = true → all=1. So a **QImode store** at a PLUS address invalidates everything! Because char stores can alias anything (ANSI).

But our store is SI. Can't change.

What about adding a QImode store somewhere? That would emit code. No.

OK so the cse wall stands for the 75820 family. Unless... we restructure so the second use of `*q` is not the same cse value. E.g., use a different variable/expression that cse can't equate. But cse equates by memory address; any load from D_800B9A02 is the same.

Could we force the reload via *statement order*: move the `*q` load to after the store by re-reading through a pointer variable assigned after? `q = (u16*)&D_800B9A02;` is already before. What if we recompute `q` after the store? cse still knows `q` = the same constant address (it's a pseudo holding a constant address; cse propagates). Unless we reassign q from something opaque.

Hmm — "launder" is a lever, not allowed.

So the family is a wall. Let me now consider: maybe the *target* doesn't need the frame if... no, the target has it.

Alright. But before declaring walls, let me check whether the *target build* for these functions really has the frame. The score-0 orig body has the clobber and frame 16. The target in build/ is the reference; the orig body scores 0, so yes.

Now, the brief says: a WALL needs ≥20 min and ≥30 scored tries on that item. I'll generate 30+ candidates per item and score them. Let me design a candidate set of real-C moves (C0505 catalog):

For the family:
1. Reorder statements (move p2 block before the store).
2. Split declarations / init at decl.
3. s16/u8 widths.
4. Pointer reuse (p2 = p + ...).
5. Use u16 for q.
6. Compute index once: `s32 i = *q * 4;` and use p+i.
7. Reorder the three parts.
8. Use `*p2 = (*p2 & mask) | ...` variations.
9. Merge the acc block.
10. `acc += ...` vs `acc = acc + ...`.
11. Use a local `u8 *b = p + *q*4;`.
12. Change the struct member access `D_800AE7BC[*q].f0` to `*(u32**)&D_800AE7BC[*q]`.
13. etc.

Most won't fix the cse cache issue. But we need 30 tries and the best score.

Hmm, wait. Actually, let me reconsider the whole shard. 5 items, and the expected output is a results row each. Perhaps the expert expects mostly walls, and the value is the evidence. The moves.md entries for similar items show PARTIAL/WALL with best scores. So WALL is a legitimate outcome.

Let me now be efficient. Time budget: started 22:09. Let me target finishing by ~00:30.

Plan:
- Item 1 (80150170): ~25 min, 30+ tries → likely WALL (barrier forces reload of a[2]/b[2] via cse-store-forward; plus frame). Record.
- Items 2-4 (family): same wall, but each needs 30 tries? The brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". So per item. But 3 near-identical items... I'll do a shared candidate generator and score 30+ variants per item. Since they're near-identical, the same candidates apply. That's fast with sc.sh (each candidate ~1-2 s? Let me measure).
- Item 5 (80180D38): barrier in an early return; try to crack.

Let me measure sc.sh speed first with a batch of candidates for item 1.

Actually, before the grind, let me look at item 5 (80180D38) since it might crack, and item 1's mechanism. Let me first check item 5's barrier-free score.

Also, I should check: does the barrier in 80180D38 also create a frame? It's `__asm__ __volatile__("");` — no memory clobber! So no frame artifact. Its purpose: prevent the compiler from... let me see the diff.

Let me run the baseline for item 5.
