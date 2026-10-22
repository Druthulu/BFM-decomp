---
ts: 2026-10-22T08:50:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_3VWlvTgZNIcwbLbuRaZD
---
Excellent! There's a gcc-2.7.2-map doc: docs/gcc-2.7.2-map/regalloc.md. Let me read the relevant parts (it's probably >20k chars; let me check size and read the relevant range).

Key line 80: "Spill/reload reg identity = the first wholly-UNUSED call-clobbered reg in regno order (order_regs_for_reload :3922-3932 unused+call_used first, then unused callee-saved, then by ascending use count hard_reg_use_compare :3822)."

But our case isn't a spill — it's a reload of an address into a reg (the "reload" for a pseudo used as an address). Hmm, in this case, is it a reload or a "copy"? The preference "73 prefers 4" came from a copy into a0. If the copy were a reload (reload_inp), the reg choice would follow order_regs_for_reload → the first wholly-unused call-clobbered reg in regno order.

In our function, are any call-clobbered regs wholly unused? v0 (used), v1 (used), a0 (used), a1 (unused!), a2 (unused), a3 (unused), t0-t9 (unused). So the first wholly-unused call-clobbered reg in regno order would be a1 ($5)! But the base is a0. So it's not a spill-reload choice; it's a plain copy.

Hmm, so what created the copy into a0? Maybe the *expand* phase: the store's address `(plus (reg r73) 2)` → expand might create a copy into a "scratch" reg? Hmm, MIPS's mips.md for `sh`:

Actually! I bet the copy is created by *reload* for the address operand, and GCC's reload for a MEM address uses `reload_inp[j].out_reg` chosen by `find_reg`/`choose_as_reload_operand` — hmm, but the doc says order_regs_for_reload for spill/reload reg identity.

Let me read the gcc-2.7.2-map/regalloc.md fully (in ranges) — it may have the exact rule for "a pseudo used as an address gets copied into which reg".

Let me check its size first.
