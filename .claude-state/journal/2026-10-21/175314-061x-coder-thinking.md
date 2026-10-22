---
ts: 2026-10-21T23:53:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IRNl5TMk5qTWljuJwYb8
---
`delete_reg_equiv (regno); reg_tick[regno]++;` — so on a set of a pseudo, its reg_equiv is deleted and reg_tick is bumped. This is called from `update_stmt`.

Now, the key: after the second set of a pseudo, its reg_equiv is deleted → a later use of that pseudo does NOT get the value forwarded (the reg_equiv is gone until the new set records it).

Hmm — `update_stmt` is called when a pseudo is SET. It deletes the reg_equiv and bumps reg_tick. Then the new set is recorded by cse's `record_cse` → `update_reg_equiv`? Hmm.

So the flow for `p = pb;` (a copy):
- cse processes the SET: dest = p, src = pb.
- cse's record_cse: p's new value is pb's value. cse would look up pb's reg_equiv (if any) and record p = that value.

So if pb has a reg_equiv (a recorded value), p inherits it → p becomes a CONST pseudo with the symbol_ref → coalesced. THAT's the coalescing mechanism.

So to prevent it: pb must NOT have a reg_equiv at the time of the copy. pb's reg_equiv is deleted when pb is set (update_stmt) and re-established by cse's record_cse for the new set.

Hmm, but the new set's value IS the symbol_ref → so pb gets reg_equiv = symbol_ref right after the set. Then the copy forwards it. ✗

Hmm, so when is a pseudo's reg_equiv NOT a simple value? If the value is a REG (another pseudo), then reg_equiv = that reg, and cse's `record_cse` would... hmm, if the value is a REG, cse records it in the equivs table (not as a reg_equiv) and the copy p = pb stays a copy of a reg → p is a real pseudo → local-alloc must copy.

So: if pb's value is a REG (not a constant), the copy is real!

When is pb's value a REG? When pb = <something that's in a register>. E.g. `pb = pc;` where pc is a pseudo. But then cse forwards pc's value...

The chain: pc = &D_800B99DC (a constant) → pb = pc → cse: pb's value = pc's reg_equiv = symbol_ref → forwarded → pb is a CONST pseudo. ✗

So cse always collapses the chain to the constant. The ONLY way to have a REG value is if the source's reg_equiv is deleted and not re-established — i.e., the source is set to a value that cse can't record as a constant...

Hmm! What if the source is set to a value that is itself a REG (a pseudo) whose reg_equiv was deleted? Circular.

**What if the source's value is the result of a MEMORY LOAD?** Then the value isn't a constant. E.g. `pb = *some_ptr;` → a load. But we need the address.

Hmm, what about `pb = (u16 *)some_int;`? The int's value...

OK, radically: what if the value isn't a constant address but a computed pointer expression whose rtx is not a constant, e.g. `pb = (u16 *)((u8 *)&D_800B99DC + 0)`? Still folds to a constant address.

What if the address is computed via a pointer ARITHMETIC on a global pointer variable? e.g. `pb = D_800B99DC_base + 0;` where D_800B99DC_base is a global pointer → a LOAD. ✗

Hmm, what if pb's value is a REG because the address is the result of an expression involving a load? no.

**So: within gcc-2.7.2, a copy of a constant address is always collapsed.** The asm launder is the only way (it creates a hard-reg value).

Hmm, but hold on! The value in the target IS in v0 (a hard reg) and copied to s0. What if instead the source pseudo's value is a REG because of a *reload* artifact?

Hmm, what about this: gcc's `find_best_addr` (cse.c) — the doc said: "an address in the table is replaced by the cheapest equivalent — ADDRESS_COST(REG)=1 vs SYMBOL_REF=2 → every (mem (symbol)) in the EBB becomes (mem (reg))". So a MEM whose address is a symbol_ref gets its address replaced by a REG — and that reg is a PSEUDO holding the address! And that pseudo is a real pseudo (not CONST) because it was created by cse to hold the address.

So: if we have a MEM access `*(u16 *)&D_800B99DC` in the preheader, cse's find_best_addr would create a pseudo holding the address and replace the MEM's address with (mem (pseudo)). Then that pseudo is a real pseudo (its value is the symbol_ref... hmm, is it CONST?).

Hmm, find_best_addr in cse.c: it looks for a register to use as the base. Let me read it (cse.c:2622-2700 per the doc).

Let me read find_best_addr.
