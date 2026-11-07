---
ts: 2026-11-06T17:17:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2oxj9XWqiavOhMi7ZZOe
---
h1 (volatile) still 21 — interesting: the mask still t7 even with a volatile store. h3 broke (211 ins).

Time: 12 min. Let me think about whether the mask's t7 is decided by *combine* rather than local-alloc. Combine runs before sched1 and local-alloc. Combine might combine the mask's constant with a register... no.

Let me look at the lreg dump's actual assignment comments again: "87 in 15" and "117 in 14". Maybe I can find the allocation ORDER by looking at `qty_order`. The lreg dump may print the qty order in the "Register N used..." lines — let me check the order of those lines: they were 72,73,74,... ascending. Hmm.

Alternatively, let me test the hypothesis that the register is chosen by *birth order in the chain*: the constant is born at chain position 5, the mask at 16. If local-alloc allocated in chain-birth order (not priority), the constant (5) would get t6 and the mask (16) t7 — exactly what we see!

But local_alloc sorts by priority... unless the priority values are equal or the sort is unstable? qsort with a deterministic tie-break by qty number.

Hmm, wait: maybe the mask's qty has a *lower* priority than the constant's because of the refs/life numbers in UID terms. Let me compute with UIDs properly:
- constant 117: refs 2; birth UID 563, death UID 664 → life 101; pri = 1*2*4/101 = 0.079.
- mask 87: refs 13; birth UID 571, death UID ? (the last and). The ands use UIDs 429..549, all < 571. So death = max UID = 572? Hmm, if the uses have UIDs < birth, the lreg summary "used 13 times across 179 insns" suggests the span is 179. Maybe the mask's uses are at UIDs up to 750.

If the mask's life is 179: pri = 3*13*4/179 = 0.87 > 0.079. Mask wins.

Unless `qty_n_refs[87]` is not 13. 

I wonder if the mask's qty is actually *tied* to the 0xFF000000 constant's qty (both are masks used in the same expressions)? No.

Let me try a direct experiment to see if priority matters: artificially give the mask 30 uses by adding 18 more `and`s? That changes bytes.

Alternatively, let me look at local-alloc.c's qty_compare usage: maybe the sort is `qty_sugg_compare_1` when there are suggestions. Let me look at line 1455-1520.
