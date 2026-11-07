---
ts: 2026-11-06T17:18:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LF0TFCGgbWeigzjLtfeJ
---
"We give shorter-lived quantities higher priority. Quantities with more references are also preferred."

So the priority = refs^? / life. The mask has more refs but a longer life; the constant has fewer refs and a short life.

Let me compute with the real numbers:
- mask: refs 13, life = death-birth. From the flow dump (before sched1): "Register 87 used 13 times across 61 insns" → life 61. pri = 3*13*4/61 = 2.56.
- constant 117: flow dump — let me find its line. The constant is used at UID 170 (store) and defined at 563. Hmm, its life in UIDs = 563-170 = 393! That gives pri = 1*2*4/393 = 0.02.

So the mask (2.56) should be allocated way before the constant (0.02). Then the mask takes the lowest free reg.

At the mask's allocation, which regs are in `used` (regs_live_at across its live range 429..572)? The mask is live over the tail; the s-registers hold the pointers (p0..p5, ot, etc.), the a/t registers hold temps. The lowest free register in GR_REGS would be... v0 (2)? No: at the mask's live range, v0/v1/a0..a3/t0..t9 are used by the and/or sequences. So the free ones might be exactly t6 and t7.

find_free_reg scans regno 0 upward and picks the first free. If t6 (14) is free, the mask gets t6. It got t7 → t6 was NOT free across the mask's live range. What's live at t6 during 429..572? The 0x8E constant? Its live range is 170..563, which overlaps 429..563! So if the constant's qty were already allocated t6, the mask can't. But the constant has much lower priority (0.02 vs 2.56) → it's allocated AFTER the mask.

Unless the constant's qty got a *suggestion* (qty_phys_sugg) from a copy insn, which is allocated in the FIRST loop (before the priority loop) — "Try to put each quantity in a suggested physical register, if it has one."

The constant 117 might have a copy/arith suggestion for t6! Where from? A `movsi` from a hard reg? Hmm.

Or: the mask itself might have a suggestion for t7? Then the first loop would give the mask t7 before anything.

That's plausible! The mask's qty might have a *copy suggestion* to t7 from some insn, causing the first loop to allocate it t7.

Which insn? The mask is defined as `(set 87 (const_int 16711680))` — a constant load; no suggestion. Hmm.

Let me look at the "Try to put each quantity in a suggested physical register" loop: it only runs for qtys with qty_phys_num_sugg or copy_sugg != 0. These suggestions come from combine_regs when a pseudo is copied to/from a hard reg.

Could the mask have a copy suggestion? If the mask were copied from a hard reg... no.

Alternatively, the constant 117 has a suggestion for t6 (e.g., `(set 117 (const_int ...))` where the previous value in t6?). Unlikely.

Hmm, let me test empirically whether suggestions are involved: if I remove the constant's REG_EQUAL note... can't from C.

Let me try to find which qty gets t6 first by looking at the lreg dump's ordering of the "Register X used" lines — maybe those are printed in qty_order? The lines I saw were ascending regno (72,73,74...). Actually dump_local_alloc in 2.7.2 prints:

Let me check dump_local_alloc.
