---
ts: 2026-11-06T10:07:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8qFE2bCg8CBlSNFXmgh3
---
In the RTL, `insn 131: a0 = reg 73` (the s0 variable is reg 73? no, s0 was reg 72 earlier... hmm reg 73 might be a copy). Then call. So there IS a move a0,<pseudo> in the RTL. But the final asm has nop! So the move got moved into the delay slot in target (`move a0,s0`), and in mine... the disassembly showed nop at 920. But the RTL says insn 131 sets a0. 

Maybe in mine, s0 (reg 72) and reg 73 are coalesced such that a0 = reg 73 is a no-op? Let me look: the call arg is `reg/v:SI 73`. If reg 73 is assigned to a0 ($4), then `a0 = a0` is a no-op → nop. And reg 73 would be... a copy of s0? Let me find where reg 73 is set.

Actually earlier alloc_table: r73 pri 4000, 2 refs, live 5, conflicts v0,sp, prefers a0. So r73 prefers a0 → global-alloc gave it a0. Then insn 131 `a0 = reg73(a0)` becomes a self-move → deleted by reorg/copy propagation → nop!

So the compiler created a separate pseudo reg73 for the call argument (a copy of s0/reg72), and global-alloc assigned reg73 to a0 (due to the copy preference). Then `a0 = reg73` is a no-op.

In the target (orig), the pin on s0 ($16) forces reg73's copy to be `a0 = $16` — a real move into the delay slot.

So the issue: reg73 (the argument copy) gets a0 due to the copy preference, making it a no-op. To fix lever-free, we need the argument to be a direct use of s0 (no copy pseudo), i.e., the call takes reg72 (s0) directly.

Why is there a copy pseudo reg73? Because the call arg is `(s32)s0` with the function cast? The cast `((void (*)(s32))func_80146C3C)(s0)` creates a conversion. Let me try calling `func_80146C3C((u8*)s0)` (v2) — but v2 still had score 7. Let me check v2's diff specifically for the nop.

Actually, maybe the copy pseudo arises from the `(s32)` cast on s0. Let me try `func_80146C3C((u8 *)(s32)s0)` or `func_80146C3C((u8 *)s0)`.

Let me check v2's diff.
