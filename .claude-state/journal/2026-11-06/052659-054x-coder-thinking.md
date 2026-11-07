---
ts: 2026-11-06T12:26:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_efqpyXchBcuqm3ajl6eJ
---
Still 19. The keepalive is a wall for the lever-free body.

But wait — maybe I should attack the keepalive differently: the asm `"r"(pb) x5` — maybe its real effect isn't ref count but that it makes pb's pseudo "used in asm" which sets a flag (asm operands get `REG_N_REFS` and also `reg_alternate_class` / "asm operand can't be in a register that's clobbered"...). Also, asm operands mark the pseudo as needing a hard register? No.

Hmm — actually, asm operands in gcc force the pseudo to be in a register and, importantly, `asm_operands` insns have `volatile` here, and gcc marks asm operands with `REG_N_REFS` AND treats them as "used in asm" which prevents them from being allocated to a call-clobbered... no.

Let me consider: maybe the 5 refs push pb's priority above k's. To emulate with real C I need refs. What if pb is used in a comparison or as a condition... adds insns.

Alternative: LOWER k's priority by shortening its live range: k = m is used throughout the loop. What if I move `k = m;` inside the loop? Then it's re-defined each iteration — target has one move before the loop. No.

Alternatively lower j's or m's.

I'm at ~25 min on this item, ~22 tries. Let me try a couple of quick "ref boosting" ideas that are legitimate real-C and cost no instruction:

The expression `D_800AE7BC[*pb].ot[2]` appears 3 times in the first region (lines 36-38) and 2 in the loop (86, 89). What if I write `*pb` in a way that cse doesn't merge but the codegen is the same? E.g. `pb[0]` vs `*pb` — same.

What about using `pb` where `p` is used? no.

OK — one more idea, cheap: the asm is `volatile("" :: "r"(pb) x5)`. Since pb is a pointer constant, maybe I can give it refs by making the STRUCT access use it as a base in an extra place where the address is folded into the instruction (no extra insn): e.g. `D_800AE7BC[*pb].ot` used as `op = D_800AE7BC[*pb].ot;` (already). 

I'll stop here on the keepalive. Decision for item 2: neither kind cracked → WALL. Best lever-free = v0.c at 21. Hmm, but k0 (keepalive removed, barrier kept) = 19. "best = lowest score of a lever-free body" — lever-free means both kinds gone = 21. So best = 21.

Hmm, that's a weak outcome. Let me reconsider the barrier once more: 2 points, ORDER. If I crack the barrier and keep the keepalive → PARTIAL:keepalive, score 0. That's much more valuable than a WALL. The barrier residual: the lui/ori constant build hoisted above the y store.

Idea: what if the constant 0x64808080 store is written with a different width/type so that gcc emits it differently... e.g. `*((u32 *)(q - 0x10)) = 0x64808080;` — could split into two s16 stores? No.

Idea: make the y store's value `y` used elsewhere after, so the sh can't move: no.

Idea: what if the lui/ori pair is for the *q-0x10* store, and we make the *address* computation come later: `*(u32 *)(q - 0x10) = ...` — the store's address is q-0x10, computed as an offset. In target the sw is at 149 with -14(a1) (a1 = q+2?). Hmm.

Alternative: reorder so that the 0x64808080 store is the FIRST of the four stores (right after the y store) — then the lui/ori would come after the y store naturally? But sched1 could still hoist the lui/ori above the y store (they're pure). Hmm, but the store itself would be forced after the y store (memory ordering), and the lui/ori feeding it could still float.

o4 = 12 (moved OT before Y) — worse.

Let me try: put the 0x64808080 store FIRST among the four (o7), and also try a variant where `y`'s store comes after the 0x64808080 store... no, target order has y at 141 first.

Alternatively: what if I make the constant's build depend on a value that's only available after the y store? E.g. compute 0x64808080 as `(0x6480 << 16) | 0x8080` — same insns, but the shift is an extra insn.

What about `0x64808080` written as `0x64800000 | 0x8080`? gcc folds at compile time.

Hmm, what about using a u8 pointer for the 0x78 store etc.? no.

New idea: the sh at 141 is `*(s16 *)(q - 10) = y;`. What if I write it as a store through a different pointer variable `s16 *qq = (s16 *)(q - 10);`? Then the store's address is a new pseudo, and the lui/ori... no effect on ordering.

What if I make the y store a *volatile*? Not allowed (a new lever).

OK: what about making the constant build part of a store that depends on the y value? e.g. write the 0x64808080 store as `*((u32 *)(q - 0x10)) = 0x64808080 | (y & 0);`? That's a launder (identity) — forbidden.

Let me check whether the reorder comes from sched1 or sched2 using cc1 dumps... that costs time but might reveal a cheap lever. tools/cc1_dumps_tu.sh. Let me check its interface.

Actually, cheaper: I recall in gcc 2.7.2, `sched_analyze_asm`:
```c
static void
sched_analyze_asm (insn)
{
  ...
  /* If the asm is volatile or has a memory clobber, treat it as a barrier */
```
Let me grep the reference source for "ASM" in sched.c. That tells me whether a loop note also blocks. Let me do a quick grep — cheap.
