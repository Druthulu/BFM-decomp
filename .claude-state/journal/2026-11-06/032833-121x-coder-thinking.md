---
ts: 2026-11-06T10:28:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yfWmcraAsOf098zoLh4L
---
For func_80023BF0:
- barriers_off_pins_on (pins kept) = 52. So the 13 barriers ARE load-bearing (the pin alone isn't enough).
- pins_off_barriers_on = 76.
- nopin = 102.

So neither kind alone gives 0. The barriers were doing live-length arithmetic. No PARTIAL.

This is a WALL with best 102 (lever-free). But let me try to improve the lever-free body with real-C moves. The comment says the 13 fences are "pure §47 live-length arithmetic": 0→15, 8→13, 10/11/12→7, 13→MATCH. So a real-C move that changes live lengths equivalently could crack it.

The residual of nopin: 102, with a systematic register shift (t0→t1, a0→t0, etc.). That's a global alloc priority shift. The fences extended live lengths to fix priorities.

Real-C ways to extend a live length: use a variable later, or restructure. This is the hardest item.

Given the effort, let me do a batch of real-C variants and record WALL if no crack. I have limited time; item 4 started ~03:27, now ~03:35 (8 min). Budget 20-30 min.

Let me think about the mechanism: the fences after `pkt = D_800A5E60;` are 13 zero-byte barriers. They extend the live range of... `pkt`? Or they split the block so that sched1/alloc sees longer lives. "pure §47 live-length arithmetic" — adding empty asm insns makes the block longer, changing the live_length of pseudos (measured in insns). With 13 fences, the live_length of some pseudo increases, changing its allocno priority.

Which pseudo? The residual (nopin) has a systematic shift: everything is one register higher/lower. The comment: "13 is the minimum; 14 and 16 also match".

A real-C move to extend a live length: add uses of a variable. But any added statement emits code.

Hmm, the fences are placed after `pkt = D_800A5E60;` and before the if. They're in the block before the two big loops. Adding 13 insns extends the live range of `pkt` (and other live values) by 13 insns, which increases their priority... Actually live_length is used in allocno_compare: pri = refs*size/live_length. Longer live_length → LOWER priority. So extending pkt's life LOWERS its priority.

The comment says fences lower `pkt`'s priority? The residual after removing them: mine's registers shift. Hmm.

Actually the barriers also prevent sched1 from moving things across. But the comment explicitly says "pure §47 live-length arithmetic".

Let me look at the allocno priorities with/without fences to understand. But this is a 281-insn function; deep analysis will take time.

Alternative: maybe a real-C move can substitute. §47 is a cookbook technique; let me grep the cookbook index for §47 / live-length.

Actually the brief says the cookbook is C<nnnn>. Let me grep cookbook/INDEX.md for "live-length" or "fence".
