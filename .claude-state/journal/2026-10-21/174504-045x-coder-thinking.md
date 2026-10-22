---
ts: 2026-10-21T23:45:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_t9OsGBeY8ucyLqfqfOPC
---
Excellent! This is the key doc: `.run/P36/engine/residual_moves.md` — "lane B" map. Row 6:

"**Give the address a pointer local used ≥2× in one EBB, or remove it** (`p = &D_x; … p->f … p->g`) | cse (`find_best_addr`) → global | `cse.c:2622-2700`: an address in the table is replaced by the cheapest equivalent — `ADDRESS_COST(REG)=1` (`mips.h:2895`) vs `SYMBOL_REF` = 2 unless `SYMBOL_REF_FLAG` (`mips.c:1600-1620`) → every `(mem (symbol))` in the EBB becomes `(mem (reg))`; the pseudo then survives calls (`invalidate_for_call` kills hard regs only, `cse.c:1725`) and crosses them in an $s-reg | ... | **Kill it with the §373 dead-reset or the §153 launder; create it with a pointer local / a second `&SYM` argument in the same EBB.**"

So:
- The address pseudo is created by find_best_addr replacing (mem (symbol)) with (mem (reg)) — i.e. the address of a MEM in the EBB gets a register.
- It can be KILLED with the §373 dead-reset or the §153 launder.

Wait — but in our case, the address in question is a *pointer value* (passed as a call argument), not a MEM dereference. Hmm, but `sp10[5]`, `sp10[2] = 0` etc. are MEMs with symbol addresses. Hmm! The MEMs are `sp10[0..2]` (stores) and `sp10[5]` (load). Their address is sp+16..sp+20, sp+26.

Hmm, the address pseudo in our case holds sp+24 — the address of the second arg. Hmm, that's a pointer value, not a MEM.

Hmm, but find_best_addr applies to MEMs. So the (mem (symbol)) → (mem (reg)) substitution would create a register holding the base address (sp+16) for the MEM accesses. That's the "address pseudo" — it holds the BASE address, i.e. sp+16, not sp+24!

But our diff shows mine has `addiu s0,sp,24` — a register holding sp+24.

Hmm, so which is it? Let's reconsider: mine[4:7]: `sw s0,32(sp); addiu s0,sp,24; move a1,s0`. So s0 = sp+24 = the value of the pointer p1 (sp10+4). This is the *pointer value* p1 = sp10+4, CSE'd between the two calls.

So it's cse unifying the two uses of the address expression (plus (symbol_ref sp10)(const 8)).

The doc row 6 says the address pseudo is created by find_best_addr from (mem (symbol)) → (mem (reg)). That happens for MEM accesses. Our MEMs: sp10[2], sp10[1], sp10[0] stores, and sp10[5] load. Their addresses are sp+20, sp+18, sp+16, sp+26. Hmm, the base pseudo would hold sp+16.

But we observe sp+24 in a register. Hmm, sp+24 is the address of sp10[4] — which is never dereferenced! It's only passed as a pointer argument. So find_best_addr wouldn't apply to it.

So the sp+24 register comes from cse unifying the two pointer-value uses.

Hmm OK. But the doc gives a hint: "**Kill it with the §373 dead-reset**". §373 = "THE DEAD-RESET CSE-BREAKER, THE PIN THAT BREAKS A sched2 ANTI-DEP, AND WHY AN `asm` CAN NEVER RAISE PRIORITY".

Let me read C0414 (§373).

Also "§153 launder" = the address-rematerialisation launder (what we have).

Let me read C0414.
