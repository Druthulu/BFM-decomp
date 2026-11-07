---
ts: 2026-11-06T03:57:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Bu0ARz7zCxDXFMG3D92e
---
The hash includes MEM_IN_STRUCT_P via hash_arg_in_struct, which affects the hash value? Let me look at how hash_arg_in_struct is used in `hash_cse_reg_info`? Actually in cse_insn, `hash_arg_in_struct` is used to avoid... Let me look at how the hash is computed and whether in_struct distinguishes entries. The hash value itself: in `hash()` for MEM, it does `hash += (unsigned) MEM; x = XEXP(x,0); goto repeat;` and sets hash_arg_in_struct as an output flag — not in the hash. But then the table lookup compares with `rtx_equal_p`? Let me check cse_insn's hash lookup: it uses `htab_find_slot_with_hash`? In 2.7.2 cse uses `hash_cse` and `qty_const`... Let me look at how loads are recorded and matched. grep "in_struct" more.
