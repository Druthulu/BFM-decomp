---
ts: 2026-11-06T11:51:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RInAsr0fH01Q6RTc65qX
---
So for equal priority and class, it sorts by INSN_LUID (original order) — so the source order would be preserved. That means the loads' order in the target (zz first) implies the RTL order was zz first!

So in the target, the RTL before sched1 has zz's load before xx's. That means the *expander* emitted them in that order — which happens if the C source order is zz then xx... but the source (with launders) has xx then zz.

Unless the loads are emitted by different means: `wx = part->xx; mn = wx; mx = wx>>16; wz = part->zz;` — the expander could reorder because `mn = wx` is a copy that's optimized, and the actual load of xx is *sunk* to its use?

Hmm, the target: `lw a1,-4(s1)` (zz) then `lw v0,-8(s1)` (xx). The xx value is used for `mn = wx` (a copy) and `mx = wx>>16`.

Wait, maybe the loads aren't xx/zz as I assumed. Let me re-check the struct layout. Part struct: maybe `xx` is at offset 4 and `zz` at 0? Let me check the Part struct definition.

If xx is at +4 and zz at +0, then -4(s1) = xx and -8(s1) = zz (since part++ makes s1 = part+0x20... wait, part starts at arg1+0x14, and s1 = part+0x20 after the increment; so -8 = part_old+0x18? Hmm, I need the struct size.

Let me check the Part type.

Actually: `part = (Part *)(arg1 + 0x14); ... for (j...; j++, part++)`. The increment `addiu s1,s1,32` (0x20) at fc8. So sizeof(Part) = 0x20. part_old = s1 - 0x20. -8(s1) = part_old+0x18, -4(s1) = part_old+0x1C. Hmm, that doesn't match xx/zz at the start of Part.

Hmm wait, the loads at fd4/fd8 happen *after* the addiu at fc8, so s1 = part_old+0x20 = part_new. -8(s1) = part_new-8 = part_old+0x18. Hmm.

Unless the loop is unrolled or the loads are from a different pointer. Hmm, s1 might not be `part`. Let me check the register mapping via alloc_table or by looking at the loop preamble.

This is getting expensive. Let me step back and consider the budget: item 2 started 04:47. It's probably ~05:10 now. I should wrap up item 2 soon.

Given v2 = score 3 (one insn order), and the barrier is the remaining blocker, this item is a WALL with best 3 (lever-free = both levers gone = v1 score 45; v2 keeps the barrier so it's not lever-free).

Wait: the WALL "best = lowest score of a lever-free body". Lever-free = all row kinds gone. v1 = 45. Hmm, but v2 (barrier kept) = 3. So the WALL best is 45? That seems bad. Let me re-read: "WALL (best = lowest score of a lever-free body)". Yes, 45 for v1.

Hmm, but that's a much worse outcome. Let me try harder to crack both.

Actually wait — v1 = both gone = 45, 795 ins (2 extra). v3 = barrier gone, launders kept = 42, 795. So removing the barrier adds 2 insns. Let me look at v3's diff to understand the barrier's role.

The barrier is `__asm__ volatile ("");` — an empty volatile asm with NO operands. In gcc 2.7.2, an asm with no operands and volatile → an `unspec_volatile` or `asm_operands` with no operands. It's a scheduling barrier for sched1? And it also prevents... hmm, it has no memory clobber, so it shouldn't affect cse memory.

Let me look at v3's diff (barrier removed).
