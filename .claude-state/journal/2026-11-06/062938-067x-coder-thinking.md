---
ts: 2026-11-06T13:29:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yUeC6Gr9mi5X15p80z1o
---
Now I see: insn 288 is `(set (reg/v:SI 4 a0) (plus (reg/v:SI 74) (const_int 4)))` = aa (a4 pseudo!). And insn 310 is the nn set. But in the source, nn (116) comes BEFORE the chain (118-121). Yet the RTL order has the chain at 293-305 and nn at 310.

Wait — that means gcc *deferred* the nn assignment. Why? Because `nn` is a hard register ($5) and `(s32)buf` is a constant address; gcc's expand for an assignment to a hard register... Hmm, actually maybe cse/fold moved it? No.

OH. I bet it's because of the `__asm__ __volatile__("" ::: "memory")` in the orig! In the nobar body I removed the asm line entirely. But the RTL numbering (310) is from the NOBAR dump. Hmm.

Hold on, maybe the insn numbering reflects a *reordering done by cse or jump*: the "insn 310" chain (next pointers) shows 302 → 310 → 305. So the RTL chain order is 302, 310, 305. That's the *scheduled* order (after sched1), not the original order! The dump prints the scheduled RTL. The insn UIDs are the original expansion order (293-305 chain, then 310). Hmm, but the UID assignment: 288 (aa), then 293,295,297,299,302 (chain), 305 (store), 310 (nn). If expand emitted nn (source line 116) before the chain (118+), nn's UID would be < 293.

Unless expand reordered: `nn = (s32)buf` where buf is an array → the address is a constant; gcc's expand_expr for the assignment to a hard reg... The tree for `nn = (s32)buf` is a MODIFY_EXPR with the address; expand might emit it at its position (293). But it's 310.

Hmm, maybe the UIDs are assigned after some pass that recreated the insn. Or maybe the source order is different: let me check the *spliced TU*: my splice replaced the body from orig.c, and orig.c line 116 has nn. So the RTL should follow.

Whatever the reason, the key point: the addiu's RTL insn is created after the chain. So at sched1, the source-order tie-break gives it a late placement. In the orig (with asm), the asm forced it before the asm.

Hmm, actually, maybe the real reason: gcc's expand emits `nn = (s32)buf` as a `(set (reg:SI 5 a1) (symbol_ref?))`... no, buf is a local array; its address is `(plus (reg fp) (const 16))`.

Wait, maybe cse *did* move it: cse's `canon_reg`... no, cse doesn't reorder insns.

Hmm, but the dump is after sched1, which REORDERS the insns and renumbers the NEXT/PREV chain but keeps UIDs. The UID order 305 < 310 is the *original* order. So indeed the original RTL had the store (305) before the nn set (310).

Could expand really emit the nn assignment after the chain? Let me test by looking at the .rtl dump (before any passes) for the nobar TU. Search for the addiu in nobar.i.rtl.

Actually — I wonder if this is because `nn` is assigned from `(s32)buf` where the cast of an array address to s32 is a *no-op conversion*, and the assignment to a hard register gets deferred by the "expand_assignment"? No...

Let me just check the rtl dump.
