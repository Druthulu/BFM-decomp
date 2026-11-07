---
ts: 2026-11-07T00:28:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hMM8wYER2DJE4u7LiWTX
---
in_struct comes from MEM_IN_STRUCT_P of the expression. For `(mem:SI (symbol_ref))`, MEM_IN_STRUCT_P is a flag on the MEM rtx set by the front end (in-struct flag from the alias info). In gcc 2.7.2, the `MEM_IN_STRUCT_P` flag is set for memory references into structures/arrays. For a load of a plain scalar global `D_80126B78` (an `s32 *` variable), the MEM would be scalar → in_struct = 0.

For `(mem:HI (plus (reg) (const)))` loads through a pointer cast — MEM_IN_STRUCT_P depends on how the front end marks it. Since we cast a pointer to `u16*`, the flag... In 2.7.2, the front end sets MEM_IN_STRUCT_P for aggregate member references; pointer dereferences of a cast pointer are scalar.

Key: `invalidate_memory(&everything)` at calls — all=1.

So the only way to force the reload in plain C is a call between the two uses. Not in the target.

Therefore the reload must come from a different mechanism. Let me reconsider: maybe cse DOES cache but the *value* doesn't survive because of register pressure, and reload/regalloc re-issues the load. In gcc 2.7.2, if cse substitutes a register for a load, the reg must hold the value; if it can't be allocated, the compiler... could rematerialize? No, gcc 2.7.2 doesn't rematerialize arbitrary loads (only constants/addresses).

Alternatively maybe the difference is in which pass merged the loads. Let me test a variant: make the second use read the pointer through a *different expression* that is not CSE-equal but compiles to the same instructions: e.g., 
use1: `*(u16 *)((u8 *)D_80126B78 + 0x12)`
use2: `((Unkstruct_800B5CB8 *)D_80126B78)->unk12` — if unk12 is a u16 at offset 0x12, RTL identical.

What if use2 uses an offset expression that folds to 0x12 only in the assembler, e.g., `*(u16 *)((u8 *)D_80126B78 + 0x10 + 2)` — folds at RTL build time to 0x12.

What if use2 reads via a local `u8 *p = (u8 *)D_80126B78;`? Same.

Hmm, what about reading through a *struct* pointer with a u16 member at 0x12 where the MEM has MEM_IN_STRUCT_P set → in_struct=1. Then... the store `sh v0,20(a1)` (a1 varying address, in_struct likely 0 for that store's dest) — nonscalar store invalidates entries with in_struct=1. But that store happens BEFORE the first use? Order: `sh v0,20(a1)` at 2dd4, then use2 at 2dd8. In the source, the store to obj+0x14 is part of the statement that also does use1's load. So in the *RTL stream*: load pointer (use1), load [ptr+0x12], load a0->unk2A, subu, addu, store obj+0x14, then use2's load pointer.

So if use2's load (pointer) were in_struct=1, the nonscalar store at obj+0x14 would invalidate it. But the *pointer* load `(mem (symbol_ref))` — could it be in_struct? If the source wrote it as `((struct X*)&D_80126B78)->field`... but that changes the symbol reference: &D_80126B78 is the address of the pointer variable, not its value.

Hmm. Alternatively: the store to obj+0x14's address is `(plus (reg a1) (const 20))`. Is that store "nonscalar"? In cse_insn, when processing a store, it builds write_data: `writes->nonscalar = ...` based on the destination's MEM_IN_STRUCT_P? Let me look at cse.c around 7599 and 7981 and the write_data setup.
