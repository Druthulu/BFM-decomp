---
ts: 2026-11-06T05:00:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fDYNqAUGHUfWH1Te6yQ1
---
invalidate_memory removes entries with `p->in_memory && (all || ...)`. The store's dest entry has in_memory=1 (MEM dest). So a later store with all=1 removes it. That's what we need.

So we need a store that sets all=1 and doesn't emit an instruction. Alternatively, a store that cse treats as all=1 but flow/combine deletes.

What about a store to a *local stack slot through a QImode variable address*, e.g., `*(u8 *)((u8 *)&local + k) = 0;`? The address is PLUS(reg, reg) QI → all=1. flow won't delete it. combine won't.

What if the address is a bare register `(reg q)` — all=1. q must be a register with unknown value; flow won't delete.

Hmm what if the store is to a *dead* stack slot through a bare register whose value is known to be the slot address but cse can't fold because it's a variable? If q = &local (a known constant), cse folds q to the stack address (fixed, not varying) → no all=1.

Wait, `cse_rtx_addr_varies_p` — what counts as varying? Let me check: probably `rtx_addr_varies_p` returns true if the address contains a register that isn't... Actually for a fixed stack slot, the address is (plus (reg fp) const) — is that "varies"? Let me look at cse_rtx_addr_varies_p.
