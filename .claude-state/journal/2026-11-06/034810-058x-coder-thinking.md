---
ts: 2026-11-06T10:48:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vk1MqsRnbMF0ivwRcHu4
---
So a basic block ends after a CALL_INSN or JUMP_INSN (the next insn starts a new block). Therefore the else-block starts after `jal func_8012A828` and its delay slot. That's the block containing the stores and the load. The barrier doesn't split it (it's an INSN).

But the barrier affects cse1's EBB. And sched1 works per basic block. So with the barrier, the load and the address are in the SAME basic block → local-alloc sees them in one block.

Then why did the target's t get v0 (first) while my v_addr got t v1 (first)?

Hmm, maybe the barrier DOES affect local-alloc: local-alloc allocates per basic block using the block's regs; the asm creates a REG_UNUSED/... no.

Wait, maybe in the target the barrier makes the load's pseudo *not* live before the barrier... no.

Let me look at the orig's actual compiled output vs v_addr to see the difference in the register assignment region. Orig = target. In the target, the load is `lw v0,196` and the address `lui v1`.

Let me examine the allocation table for orig to understand. There's tools/alloc_table.py, used by hdump. But for a TU we need dumps. Hmm.

Alternative empirical approach: since v_addr3 has correct regs and only the load position wrong, and v_addr has correct order but swapped regs, maybe I can find a variant with both. The variable is which pseudo is "second" in source.

What if I keep `t` first in source but make the *address* variable's definition earlier/later? Hmm.

What if the address is computed via a different expression that yields a different allocno priority? E.g., `s32 a = (s32)&D_801907C4;` at declaration time (init at decl) — a's live range starts at the decl point (function top?) Actually the declaration is at the top of the else block; init at decl would compute it at the block start.

Hmm, what about making `a` a pointer: `u8 *a = &D_801907C4;` and `unk58 = (s32)a;`. Same.

Let me think about local-alloc's priority: In local-alloc, `qty_compare` sorts by `(reg_qty)`, using `qty_n_refs * qty_min_class`... Actually gcc 2.7.2 local-alloc sorts qties by `floor_log2(qty_n_refs) * qty_size` etc. Let me look at the actual comparator.
