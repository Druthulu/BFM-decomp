---
ts: 2026-11-06T10:00:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XZ0leDS7ptyLULMmJS9w
---
Interesting details:
- `move v0,a0` at 38bc: arg0 kept in v0 (used for the loads). 
- `sw s0,16(sp)` then `move s0,a1` (d=arg1), then `sw ra,24(sp)`, `sw s1,20(sp)`.
- `lh s1,18(v0)` — s1ang loaded into s1.
- `jal ratan2` with delay slot `subu a1,v1,a1`.
- After: `addiu v0,v0,-1024` (ang - 0x400), `andi a0,v0,0xfff` (u5 into a0!)
- `sll s0,s0,0x10` (d = (s16)d), `andi s1,s1,0xfff` (u6)
- `bne s1,a0` with delay `sra s0,s0,0x10`.

So u5 is in a0 (the ratan2 result register), s1ang in s1, d in s0.

Interesting: u5 is a separate variable but it's just the ratan2 return minus 0x400 masked; it stays in v0/a0.

Now, without the pin, d goes to s1 and s1ang to s0. The keepalive on u5 was a scheduling barrier.

Let me first just remove both levers and see the full residual — that's what --explain showed: score 21 with register swap.

Now, how to make d take s0 and s1ang s1 with real C?

The allocation: which pseudo gets s0? In local-alloc, registers are assigned in order of `reg_qty[].n_refs` descending? Let me check gcc 2.7.2 local-alloc.c. Actually, global-alloc assigns hard regs to pseudos based on `allocno` ordering: `allocno_compare` compares `floor_log2(n_refs)`? Let me look.

Actually, both d and s1ang are live across a call, so they're in the "global" set and allocated by global-alloc. The order in which allocnos are considered determines who gets s0.

Let me read gcc 2.7.2 global.c for the sort.
