---
ts: 2026-11-06T10:40:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yPnNWuiSc5FxVSTwJ50M
---
No change. So the load is hoisted regardless. Why? sched1 hoists loads aggressively at the top of the block; alias analysis: `*(s32*)((s32)a0+0xC4)` — the address is (plus reg const), and the preceding stores are to constant offsets from the same reg. In gcc 2.7.2, dependence is determined by rtx: `true_dependence` on MEMs with different addresses — it computes if the addresses are provably different: `(plus (reg) 92)` vs `(plus (reg) 196)` with the same base reg → the addresses differ (different constants) → no dependence, regardless of alias sets? Actually alias sets are checked first; if the alias sets conflict, it still compares the rtx addresses to see if they can be proven distinct. Since both are base+const, they're distinct. So no dependence.

Hmm. So we need something else to hold the load.

Wait, maybe the barrier's real effect here isn't scheduling but *block splitting*: the asm volatile memory clobber creates a barrier that sched1 treats as a block boundary. Without it, the whole block is scheduled as one; sched1 hoists the load. In the target, the load is at its source position — which is what you get if sched1 does not reorder within a smaller block.

Real-C block split... What about `do { } while (0)`? The cookbook C0535: "do{}while(0) splits cse1 EBB". Interesting! A do-while(0) creates a NOTE_INSN_LOOP? Actually `do{}while(0)` is optimized away but might leave a loop note that affects scheduling. C0535 says it splits cse1 EBB and cracked a sched1-birth-order item. Let me read C0535.
