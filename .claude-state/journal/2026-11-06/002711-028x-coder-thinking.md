---
ts: 2026-11-06T07:27:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P0GGIMI1YXIXLyOdbNjk
---
Same. So pin/keepalive removal doesn't change: a0 excluded in target only. So there must be a real difference in the source structure producing the a0 reservation. 

Hypothesis: the target's 4 loads are not all in one basic block! If one of the copies is separated (e.g. cse1 block boundary), local-alloc allocates per block and the a0 use... Hmm.

Alternative hypothesis: a0 is reserved because of the `id` pseudo being assigned to a0 by global-alloc AND local-alloc's rule: `local-alloc` doesn't allocate a hard reg that is live at block boundaries. But id is not live across.

Wait wait. Maybe the direction is opposite: in the target, the FIRST copy's temp gets v1, and the others a1-a3 because the allocator's register order list is not a0,a1,a2,a3. GCC 2.7 local-alloc iterates over `reg_alloc_order`? Let me look at local-alloc.c in tools/reference. Actually I recall in GCC 2.7 local-alloc.c `block_alloc`: it uses `regs` array from `reg_alloc_order`? Let me read.
