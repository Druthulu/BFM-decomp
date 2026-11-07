---
ts: 2026-11-06T03:23:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n2Y1dCI7w2tWLFemIn2I
---
The write_data bits:
- "writing in a structure element at variable address invalidates all but scalar variables" → nonscalar = 1.
- invalidate_memory: removes entries where `nonscalar && p->in_struct` or `cse_rtx_addr_varies_p(p->exp)`.

The D_80126B78 entry: its expression is `(mem:SI (symbol_ref D_80126B78))` — in_struct? The global is `s32 *D_80126B78` — a scalar pointer variable. So p->in_struct = 0. And `cse_rtx_addr_varies_p (p->exp)`: the address is a symbol_ref (fixed) → doesn't vary. So the entry is NOT invalidated by a struct store at a variable address. Hence cse keeps it → no reload. So the struct store does NOT help for a *scalar* global.

To invalidate the scalar global's entry, we need the store to be "anything else at variable address" → `all = 1`. That happens when the store is not in a struct and not a fixed address? The comment says: "writing in anything else at variable address invalidates everything". So a NON-struct store at a variable address → all=1 → invalidates everything, including the fixed scalar global!

Wait, but our current store IS a non-struct store at a variable address (`*(u16*)(obj+0x14)` with obj a variable) → should set all=1 → invalidate the global → reload. But cse didn't invalidate (mine reused). Hmm.

Let me read how write_data is set: `invalidate_from_clobbers`? The function that sets the bits is `note_mem_written` or `set` handling. Let me look at the code that fills `writes`. Search "nonscalar" in cse.c.
