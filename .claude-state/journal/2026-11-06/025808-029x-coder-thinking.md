---
ts: 2026-11-06T09:58:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1QWaMvciKTRCexq6RJxR
---
Key: "Order the qtys so we assign them registers in order of decreasing length of life." qty_compare orders by decreasing live length (death - birth). So the qty with the longest life gets allocated first → gets the lowest free reg (v0).

So target: t has longer life than tb? In target, t is used at unk4C (52) and redefined at 55 and used 59/61 — so t lives 52..61, longer. tb lives 53..58. So t (longer) → v0, tb → v1. That matches target!

Mine: t in v1, tb in v0 — so mine's t has SHORTER life than tb? How? In mine source, the order of statements is the same. Hmm. Unless in mine, `t` at 52 is a different pseudo from `t` at 55? No, same variable, but local-alloc splits by... Actually GCC may create separate pseudo-registers per assignment if not live across? No, a user variable is one pseudo unless copy propagation splits it. cse/reg alloc: the first `t` (unk4C) and second `t` (unk50) might be merged or not. But both mine and target use the same source structure, so same.

Wait — mine's t is in v1 for BOTH defs (52 and 55) and tb in v0. So t is one pseudo living 52..61. tb lives 53..58. t's life is longer, should get v0. Unless qty_compare ties? Hmm.

Wait, maybe I misread. Let me recompute live lengths in terms of insn numbers. qty_birth/death are insn uids. Mine:
- t birth at 52 (lw v1,76), death at 61 (sh v0,10). Wait line 61 `sh v0,10(s0)` uses v0 not v1! Mine line 59 `addiu v0,v1,-8` uses v1 and defs v0; line 61 `sh v0,10(s0)`. So t's second def (lw at 55) is v1, then addiu v0,v1,-8 defs a new temp v0 used at 61. So t's live range: 52..59 (last use at 59). And tb: 53..58. t is longer (52-59 vs 53-58) → t should get v0. But mine gives t v1.

Hmm, so my life-length reasoning must be off. Maybe there's another qty: the result of addiu (v0) and the call result... Let me reconsider: local-alloc allocates ALL block-local quantities in this block, not just t/tb. The block includes the loads from D_8011F75C etc. Actually the block is the whole `if ((cnt&7)==0)` body — from insn 11 to ~61. Many quantities: v0,v1,a0,v1... but those are hard regs or global. The pseudos: t, tb, and maybe others.

Wait, insns 11-28 are a struct copy `*(Blk32*)(s0+0x38) = *(Blk32*)D_8011F75C;` — a 32-byte copy using v0,v1,a0 as scratch (these are global scratch, not pseudos). The copy uses hard regs directly.

Then t and tb and the addiu temp. Also `p` is used (a2). p is a global pseudo (across branches) → global alloc.

So local qtys: t, tb, and the addiu temporary (a new pseudo for t-8), and maybe the call result.

Hmm, if there are 3+ qtys: t, tb, addiu-temp. t lives 52-59, tb 53-58, addiu-temp 59-61. t longest → v0. Still expects v0.

But mine has t in v1. So maybe t is NOT one qty — maybe cse split? Or maybe the `li a0,2274` at 56 (call arg) interferes: a0 is used at 56 and the call at 60. Hard.

Hold on: maybe `t` is actually a GLOBAL pseudo in mine because it's used across... no.

Let me reconsider: maybe the barrier is what made t/tb different. In the original (with barrier), t got v0 and tb v1 (target). Without barrier, t v1, tb v0. The barrier `__asm__ __volatile__("" ::: "a0")` is at the very END (before the final call), clobbering a0. That affects the final call's a0 setup only. But it also affects... hmm, the barrier is in the `cnt >= 0x20` path, which is a different basic block. So it shouldn't affect the `cnt<0x20` block's local alloc.

But removing the pins s0 and tb: s0 pin removal shouldn't change t/tb. tb pin removal obviously: tb was forced to v1, now free.

So lever-free, local-alloc picks t=v1, tb=v0. Target t=v0, tb=v1.

How to make t get v0? Make t's live range longer than tb's by a real-C change. Currently t: 52..59 (birth 52, death 59); tb: 53..58. If I extend t's life or shorten tb's.

Actually wait, why did t get v1 then? Let me look at qty_compare: it sorts by decreasing life. Maybe birth/death are not insn indices but the qty's first/last insn. t first=52, last=59 → life 7. tb 53..58 → life 5. t first in order → v0. Unless find_free_reg for t returns v1 because v0 is occupied by something live at t's birth (52). At insn 52, what's live? v0 was used at 51 (sh v0,26(a2)) — dead. But maybe the struct copy's scratch... no.

Hmm, alternatively, maybe the qty ordering uses `qty_compare` which sorts ascending by (death - birth) then... let me read qty_compare.
