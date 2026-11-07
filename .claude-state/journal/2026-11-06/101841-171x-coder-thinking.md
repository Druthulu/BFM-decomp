---
ts: 2026-11-06T17:18:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_amznUKnn1Ws77Ho5gN3M
---
The disposition list is by regno. No allocation order info.

Let me instrument differently: run cc1 with `-dl` and also check `qty_phys_sugg`... no dump.

Empirical test of the suggestion hypothesis: if the mask has a suggestion for t7, we could change the surrounding code so the suggestion disappears. Hmm.

Actually — WAIT. I recall `combine_regs` for `(set (reg t7) (const_int ...))`? No.

Let me look at the mask's def in the RTL: `(set (reg/v:SI 87) (const_int 16711680)) {movsi_internal2}` and `(set (reg/v:SI 87) (ior (reg 87) 65535))`. No copy from a hard reg.

Hmm, but the *0xE100008E constant* is `(set (reg:SI 117) (const_int -520093696))` — also a plain constant.

Both are constants; neither should have suggestions.

So why t6 vs t7? Let me reconsider: maybe find_free_reg's `used` includes the *hard regs used by already-allocated qtys*? No, it uses regs_live_at (original hard regs only) — but local_alloc's `reg_is_born`/`wipe_dead_reg` for hard regs builds regs_live_at from the ORIGINAL hard regs in the RTL (a0-a3, s0-s7, etc. from calls and explicit regs). Since this function has no calls, the only hard regs live are... none? Then all GR_REGS would be free and the first qty would take v0!

But the output shows the mask in t7, so regs_live_at must reflect something. Actually the pseudos' allocation is propagated by setting `reg_renumber`, and the RTL is then updated via `reg_renumber` at reload. For the *dump*, `print_rtl` uses the original regnos; the final assembly uses reg_renumber.

The key: `regs_live_at` is computed in `block_alloc` BEFORE allocation, from the RTL's hard regs only. But there's also `qty_phys_reg` conflict handling: in the main loop, after find_free_reg returns a reg, there's no cross-check against other allocated qtys! The check is that `regs_live_at` was updated when a qty is allocated? Let me look at block_alloc's structure: it does two passes over insns: first pass allocates qtys (reg_is_born etc.), then the priority loop calls find_free_reg. During the first pass, hard regs in the RTL are tracked. The allocated qty's hard reg is NOT added to regs_live_at.

Hmm, but then two conflicting qtys could get the same hard reg! Unless find_free_reg's `used` includes `regs_live_at` which includes... the pseudos? No.

I must be missing something. Let me look at `mark_life` / `regs_live_at` and whether allocated qtys are marked. Search for "qty_phys_reg" usage near block_alloc... Actually, in gcc 2.7.2 local-alloc, after the main allocation loop there's a second phase: `find_free_reg` is called with the `used` set built from `regs_live_at`, and *allocated* registers ARE marked because after each qty is allocated, the code does:

Looking at the loop, no marking. Hmm, but the original algorithm: the first pass over the block (`block_alloc`) computes liveness of *hard* regs only; pseudo qtys' conflicts are tracked via `qty_death`/`qty_birth` in the *same* priority loop? No...

OK, I clearly don't remember this algorithm well enough. The empirical result stands: the mask goes to t7 robustly.

Given the time (10:19, 14 min), let me consider trying the *reverse* experiment: what if the 0xE100008E constant is removed/renamed so the mask gets t6? E.g., if I change the p2 packet's constant to a different value (wrong program, but as an experiment) and the mask moves to t6, that would confirm the conflict. Not useful for a crack.

Actually, here's a thought: what if we make the 0xE100008E constant *shared* with another packet constant (same value)? The six constants are all different. If two packets used the same constant, cse would share it... changing bytes.

Let me try the opposite: what if the mask is used *before* the constant's store in the source? The mask's uses are all after the packet stores. If we move the first mask use earlier (e.g., the p0 unk0 update right after the p0 block), the mask's birth moves earlier and might conflict differently. But that changes instruction order (the target's tail is at the end). sched1 might reorder anyway.

Hmm, the target's tail is after all packets. Moving a use earlier would change the code.

I'll stop here and record item 3 as a WALL. But I need 20 min; I'm at 14. Let me spend 6 more minutes on a few more variants (cheap) and then finalize.

Let me try some variants of the *other* competing constants: change the *order* of the six packet blocks? No (order matters).

What about making the p2 constant store use a different variable type: `*(u32 *)(p2+4) = 0xE100008E;` — same.

Try: change the six constants' *values*? No.

Try: use `q2` as `volatile u32 *`? h1 tried volatile on the store — 21.

Try: declare q0..q5 as `u32 *` vs `volatile u32 *` — no.

Try: assign the constants to variables declared in each packet block (block scope): `u32 c = 0xE100008E; *q2 = c;` — the pseudo's birth would be near the store (not hoisted?). Let me try this for all six: each block declares `u32 c; c = 0x...; *qN = c;`.

Actually the store value is already a pseudo created at the store; naming it shouldn't change.

Hmm, what about making the constant's materialization *not* single-set by using the value twice in the same block: `*q2 = 0xE100008E; p2[0x10] = (u8)0xE100008E;`? Wrong program.

Let me just do a few more and finish.
