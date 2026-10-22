---
ts: 2026-10-22T12:51:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_3RanqIagPz2PXvYxUUNG
---
The key is `reg_qty[REGNO(x)]` — the quantity of the pseudo. A pseudo gets a quantity = the number of sets (reg_n_sets). If a pseudo has 2 sets, `qty_const` for that quantity is... hmm, actually `qty_const` is indexed by quantity number, and each pseudo has its own quantity number q (next_qty++). So `qty_const[q]` is per-pseudo-ish (per quantity class). The condition `GET_CODE (x) == REG && classp && ! qty_const[reg_qty[REGNO(x)]] && ! elt->is_const` → the class contains a constant → qty_const[q] = the constant.

Hmm, so this happens when the pseudo's class contains a constant. The class is the equivalence class of the pseudo. If the pseudo has 2 sets (one to the constant, one to something else), the class would contain both → the "classp" chain would contain a const elt → qty_const[q] gets set anyway?! Hmm.

BUT: `qty_const` is only meaningful if the pseudo is set ONCE. Where's the check? In cse.c, `reg_qty[reg] = next_qty++` in `make_regs_eqv`/... Actually the quantity of a pseudo is determined by `reg_n_sets` — hmm, cse's `reg_qty` is assigned in `record_equiv`...

Let me look at where cse handles a SET of a pseudo to a constant: `cse_basic_block`, case SET. Let me look for "is_const = 1" and the quantity check.

Actually, in cse.c there's a concept: "reg_qty[N]" is the quantity number of reg N; a pseudo with a single set has its own quantity. When a pseudo is set twice, the two sets are in different "quantities" (cse splits the pseudo into quantities). Hmm, no: cse's `make_regs_eqv` splits.

Let me look at how cse handles the case where a pseudo is set to a constant twice with different values: the second set would create a new quantity.

I recall in cse.c:
```c
	  /* If this is a set of a pseudo to a constant, and the pseudo has
	     more than one set, don't record the constant. */
```
Let me grep for "reg_n_sets" in cse.c.
