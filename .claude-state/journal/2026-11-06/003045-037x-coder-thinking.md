---
ts: 2026-11-06T07:30:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zPB19JHzI0d7Qut9UjBx
---
All 14 except worse. This confirms the a0 reservation is structural. Let me think about which pseudo could occupy a0.

What if the original source's first block has an extra live value: the return of func_800CAF84? no.

Wait, what about the stack argument setup? func_80146A6C takes 7 args; args 5-7 on stack. But that's in the if-block.

Let me reconsider: maybe in the target, the a0 pseudo is the *argument pointer for the struct copy's source*, i.e. the compiler used a0 as a scratch for expand_block_move? In target group1: `lw v1,52(v0); lw a1,56(v0); lw a2,60(v0); lw a3,64(v0); sw v1,56(s0); ...`. If expand_block_move used a0 as scratch, we'd see it. No.

Hmm, what if the target's a0 is reserved by the pseudo for `id` allocated by GLOBAL-alloc because the if-block is in a different basic block but `id` is live across the *function* due to being referenced in a REG_NOTE? No.

Let me test whether global-alloc assigned a0 to `id` and the first block's local-alloc sees a0 live because `regs_live_at` at the copies includes regs live at those insns — `id` isn't live there.

New idea: maybe the target has a0 reserved because the value `0x4B` (id) is materialized EARLY at the top of the first block in target's RTL, then moved/copied. No, li a0,75 is at insn 32.

Let me look at the actual RTL? That's expensive. Instead, use `--explain` with candidate text to see the NEEDED sites? No.

Alternative: maybe the difference is not a0 "used" but that local-alloc's `find_free_reg` for the SECOND load skips a0 because of `qty_phys_copy_sugg` or `post_mark_life` of the first quantity. The first load quantity got v1. The second load: find_free_reg iterates reg_alloc_order. If reg_alloc_order = {4,5,6,...}? Then the second would get a0 (4) unless a0 in used. If reg_alloc_order starts {2,3,4,5,...}, first gets v1? Hmm, v1 is reg 3. If order = {2(v0),3(v1),4(a0),...}, the first load would get v0, but v0 is live (the pointer). So it gets v1. Second: v0 live, v1 used → a0 in mine. In target: a1. So a0 is in `used` in target.

`used` = fixed_reg_set ∪ call_used_reg_set (if qty crosses call) ∪ regs_live_at[range] ∪ complement(class). The copy temps don't cross calls → used=fixed_reg_set. regs_live_at includes a0 if some pseudo is live there. 

Which pseudo? Since all copy temps are local, maybe the `v0` pointer? In target v0 is $2. `s0` $16, `s1` $17. `arg0` dead.

Unless there's a pseudo for the FUNCTION'S RETURN... void.

Hmm, is `struct16` copy maybe using `a0` as an intermediate address? Look: `*(Struct16 *)(s0 + 0x38)` — the destination address s0+0x38 computed with an addiu into a temp! In target: `sw v1,56(s0)` uses s0+0x38=56. No addiu.

What about the source address `v0+0x34`? loads use offsets from v0. No.

OK let me look at this from the P36 trace: maybe some candidate achieved 0 for a sibling function with the same shape, and there's a known move. Search moves.md for similar "global-hardreg-reserve" and check the mechanism. Already saw: func_801536DC G08b. Let me look at that item's notes to understand. It's in G08b shard. Let me search .run/P40/T11 for it.
