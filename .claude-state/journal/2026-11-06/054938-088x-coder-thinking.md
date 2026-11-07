---
ts: 2026-11-06T12:49:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RVB8FqOt7vyDeUOiA483
---
Key: entries are removed if `all` (a store to something that may alias anything), or `nonscalar && p->in_struct` (a non-scalar store kills struct entries), or the address varies.

The store to `unk10A` (a struct member) sets `nonscalar` → kills struct entries. And the load `unk10A` is `in_struct` (mem/s) → killed. So the store itself invalidates. But then how does forwarding work? Because cse1 processes the store first: `cse_insn` for the store puts the value into the table with in_memory... The load later finds the stored value's *register equivalence* (cse records that the MEM's contents equal the stored value? no).

Hmm, actually the forwarding is done by `cse_insn`'s handling of `(set (mem) (reg))` followed by `(set (reg2) (mem))`: cse does "store forwarding" via the table entry for the memory expression: when a store's value is a register, cse inserts the MEM expression as an equivalence of the stored register? I recall cse.c's `cse_insn`: "If this is a store, ... record the equivalence between the value and the memory location" — `invalidate_memory` is called for stores, and then cse inserts `src_eqv`...

Regardless: the fix used in the original was a memory clobber asm which makes `writes->all = 1`.

Lever-free alternative that sets `all`: a store whose address "varies" or that cse considers possibly-aliasing everything: e.g. a store through a pointer of unknown origin (`*p = x` where p is a pointer variable). `D_801F32D0 = 0` is a known scalar (not all). A store through `(u8 *)param_1` with a *variable* offset would set `all`? In cse.c, `writes->all` is set when the store's address is not a "fixed" address (e.g. involves a register? no...). Let me look at how writes->all is computed (in cse_insn: "if (GET_CODE (x) == MEM) ... writes->all |= ...").

Actually in cse.c:
```
	  if (GET_CODE (dest) == MEM)
	    {
	      /* Store the equivalent value */
	      ...
	      writes->all = 1? 
```
Let me grep for "->all".
