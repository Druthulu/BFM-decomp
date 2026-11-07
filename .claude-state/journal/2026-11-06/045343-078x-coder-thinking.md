---
ts: 2026-11-06T11:53:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v7UwNSPhe6usAeRbQa1H
---
`invalidate_memory`: removes entries where `all || (nonscalar && p->in_struct) || cse_rtx_addr_varies_p(p->exp)`.

`cse_rtx_addr_varies_p` returns true if the address involves a register that varies (not a fixed symbol). Our address is `(plus (reg s0) (const 6))` — a register-based address, so `cse_rtx_addr_varies_p` is TRUE! So ANY store invalidates our entry!

Wait, but then how did cse forward the store into the load? Because the store's own entry is added AFTER invalidating. The sequence: store insn → invalidate_memory removes old entries → then insert the store's dest value into the table. Then the next load finds it. Right.

So to prevent forwarding, I need an intervening store to invalidate the entry between the store and the load. But the target has NO instruction between sb +6 and lbu +6. So cse must not have recorded the store in the first place, OR the load's lookup hash differs.

Wait, unless the intervening store is to a DIFFERENT address and `nonscalar`/`all`... but `cse_rtx_addr_varies_p(p->exp)` is true for our entry (register-based address), so ANY store would remove it. But there's no store between.

So the only way is: don't record the store's dest (src_elt == 0), or make the load's hash not match.

Hmm, `src_elt == 0`: the store's source is `(subreg:QI (reg:SI 75) 0)`. Is a subreg looked up? In cse_insn, the src is processed; for a SUBREG, `fold_rtx`/`lookup`. If the reg 75 has an entry, the subreg might be simplified via `gen_lowpart_if_possible`. If reg 75 is a register whose value is known (it's the result of subu), cse may have an entry for reg 75's value. 

Wait, does cse track arithmetic results? It does global value numbering: `(set (reg 75) (minus (reg 78) (reg 73)))` — the src is `(minus ...)`, which cse looks up; if not found, it creates an entry? cse only records values it has seen. For the DEST reg 75, it inserts `reg 75 = (minus ...)` into the table. Then the store's src `(subreg:QI (reg:SI 75) 0)` — cse looks up the subreg; `gen_lowpart_if_possible` on the known value `(minus ...)`? It would produce `(subreg:QI (minus ...) 0)`? Hmm.

Actually the dump showed insn 30's src as `(subreg:QI (reg/v:SI 75) 0)`. cse recorded dest = `(mem/s:QI ...)` with src_elt = the entry for `(subreg:QI (reg 75))`. It did record it (since forwarding happened).

To make src_elt == 0, the store's source must not be in the table. What if the store value is a **MEM** expression? E.g., `*(u8*)(arg0+6) = *(u8*)(arg0+7);`? Not our case.

What if the store source is a value computed with a mode that cse can't lowpart? 

Hmm.

Let me look at line 7219 / 7169: `elt->in_struct = sets[i].src_in_struct`. And the hash of the load includes in_struct. Let me check `hash_rtx` at 1951 more carefully — is in_struct part of the hash value?

Line 2027: `int save_hash_arg_in_struct = hash_arg_in_struct;` — and hash_arg_in_struct is a global set during hashing. The hash VALUE itself (hash_arg_in_struct) is returned? Let me look at hash_rtx's return.

Actually `hash_arg_in_struct` is a flag output; `hash_rtx` returns the hash. Does it incorporate in_struct into the returned hash? Let me check line 1951 context.
