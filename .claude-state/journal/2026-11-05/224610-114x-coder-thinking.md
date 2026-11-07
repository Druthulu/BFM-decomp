---
ts: 2026-11-06T05:46:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mJtUmgAfibixNMuYv9N7
---
So `cse_rtx_addr_varies_p((mem:HI (reg q)))` returns 0 (address doesn't vary) if q's quantity has a known constant value (`qty_const != 0`). q = &D_800B9A02, a constant → qty_const known → varies=0. So the load is a "scalar variable" and survives the nonscalar store. That's the wall.

Key: `p->in_struct` is also relevant: if the load's mem were marked `in_struct`, the nonscalar store would invalidate it. `elt->in_struct = MEM_IN_STRUCT_P(inner_dest) || inner_dest != SET_DEST`. For a load `(mem:HI (reg q))`, `inner_dest` == SET_DEST (the dest is a register, not mem) — hmm, `sets[i].inner_dest` is the dest; for a load `set (reg) (mem)`, inner_dest is the reg, not a MEM → in_memory false. Hmm, so loads aren't in_memory entries?

Wait, the cse table entry for a load's *value* is the mem expression; `p->in_memory` is set when the entry's expression contains memory. Let me check `hash_arg_in_memory`. In `insert`, `elt->in_memory = hash_arg_in_memory`. For the load's src `(sign_extend:SI (mem:HI (reg q)))`, hash_arg_in_memory is set → in_memory true. `in_struct` = hash_arg_in_struct (MEM_IN_STRUCT_P of the mem) = false.

So invalidate_memory: all=false, nonscalar=true, p->in_struct=false → check `cse_rtx_addr_varies_p(p->exp)` → the exp is `(sign_extend:SI (mem:HI (reg q)))`. cse_rtx_addr_varies_p on a SIGN_EXTEND (not MEM) → falls to `rtx_addr_varies_p(x)` → recursively checks for varying addresses: the mem's address is a reg with a constant qty → the first branch requires GET_CODE(x)==MEM, but x is SIGN_EXTEND → skip → `rtx_addr_varies_p(x)` which checks subexpressions. Does rtx_addr_varies_p know about constant-valued regs? Let me check. It probably returns true for any MEM with a REG address (not knowing constants). Hmm, but then the entry would be invalidated and the load reloaded — contradicting the observed behavior.

Let me check rtx_addr_varies_p.
