---
ts: 2026-10-22T21:42:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nu4Jl9GlHcZrxzQaweCN
---
No luck. Let me try the RTL dump approach to see where the order is decided — but first, let me consider whether the "both u8" (t_u8, score 1 REG) can be fixed: in t_u8 the copies were `move v1,v0` then `move a0,v1`. If I could make testval's copy read v0 instead of v1: cse merged testval and byteval (both QImode, same value). If byteval's QImode value were made distinct from testval's by a real operation that produces no code... 

What if byteval = src (u8) and testval = (u8)src but testval is assigned from `src` *before* byteval truncates? Both QI from the same SI value → merged.

What if byteval is u8 but assigned `byteval = src & 0xf;`? cse: (and:SI v0 0xf) known → folded.

What if byteval = src and testval = src where src is u32 but testval declared s8 (signed char)? Then the subreg is signed → sign extension? testval is 0..15, so s8 = u8 in range; the branch `testval != 0` on a signed char subreg: gcc would sign-extend → maybe adds sll/sra. Hmm, m_u8_s16 gave 2 ORDER.

Given the pattern (all single-mode variants = 2 ORDER), the two-copy order looks like a sched1 birth-order tie that no source reorder reaches — exactly the `sched1-birth-order` wall in walls.txt (G16 func_801372B0: "sched1 orders two independent insn births opposite to source; reorder moves the other").

Wait, that wall says reorder moves the *other* one — i.e., swapping source order swaps which is first, and you can't get both right. But here swapping source order doesn't even move it. Hmm.

Hold on! Maybe the order is decided by *priority* where the $4 copy is closer to the branch. In func_801372B0's wall the same shape appears.

Before concluding, let me check the RTL dump to see which pass. tools/cc1_dumps_tu.sh usage: let me look at its help and how hdump.sh works (for headers, hdump.sh does header pass dumps). I'll use hdump.sh with an absolute outdir under my shard dir. Let me read hdump.sh.
