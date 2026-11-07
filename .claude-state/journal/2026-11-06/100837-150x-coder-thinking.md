---
ts: 2026-11-06T17:08:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YrS74yD2jmK6pnBXFOqj
---
The 0xE100008E constant (insns 563-564) is in t6 (14) in mine. In the target, this constant is in t7 (15) and the mask in t6 (14).

Note these constants are allocated *inline* (no pseudo): the RTL uses `(reg:SI 14 t6)` directly — because local-alloc assigned them. Each constant is a separate pseudo with 2 refs, life 2 insns. Their priority = 2/2 = 1.0, which is higher than the mask's 39/life. But there are 6 such constants; the first ones take the low regs (a2, t0, t6, s5...). Why t6 for the third?

The target's third constant is in t7 — the target has the mask in t6 (pinned), so the constants couldn't use t6.

In mine, the constants take t6 (the third one), and the mask gets t7.

To get the target allocation lever-free: the mask must be allocated BEFORE the constants (so it takes t6), or the constants must avoid t6.

The mask's priority is low because its live range is long. Can we shorten the mask's live range? Its def is at insn 571 (late, after all packet stores) and uses at 573+ (the last 12 statements). So the RTL live range is short! But the priority is computed as (death - birth) in *insn numbers*: the mask's birth 571, death ~600 → 30. Then priority = 39/30 = 1.3 > constants' 1.0! Hmm, that contradicts the outcome.

Wait, the mask reg 15 got t7, but t6 was taken by the constant at insn 563 — which is BEFORE the mask's birth (571). Local-alloc allocates in priority order, not insn order, but the *register conflict* matters: the constant (insns 563-564) and the mask (571+) have disjoint live ranges? Then both could use t6, and local-alloc would reuse t6 for the mask if it's free... but it assigned t7.

Hmm, actually local-alloc assigns one hard reg per qty; if two qtys don't conflict, they can share. But it allocated the mask to t7 instead of reusing t6. Because at the mask's birth, t6 is free (the constant died at 565). find_free_reg should pick the lowest-numbered free register — which might be t6 if t0-t5 are busy... The mask got t7.

Wait, the constants: a2 (6), t0 (8), t6 (14), s5 (21), ... These are *different* registers because the constants are all live simultaneously? No — they're each live for 2 insns and die before the next. Unless local-alloc's per-qty assignment doesn't reuse within the same block? It does reuse.

Hmm, look: the six constants are at insns 559-560 (a2), 561-562 (t0), 563-564 (t6), 565-566 (s5), ... Why different registers? Because local-alloc assigned them by priority order and each got the next free reg at its birth? No, they don't conflict with each other.

Oh! I bet these constants are NOT separate pseudos: the RTL shows `(reg:SI 6 a2)` etc. — they were allocated by local-alloc to hard regs directly. The 6 constants each have 2 refs and are used at different places; they could share. But they don't because... local-alloc's allocation is per-qty and the qty conflict graph is built from liveness; disjoint live ranges CAN share but local-alloc's find_free_reg uses `qty_phys_reg` per qty and the conflict sets. If they don't conflict, find_free_reg would return the same reg (reuse). Unless the constants' live ranges overlap.

Hmm, the constants are used at insns 570 (s7 ior), 76? Actually the constants are used in the `sw` instructions much later. Their live ranges may be long (from 559 to their use).

Anyway: the target has the 3rd constant (0x8E) in t7 and the mask in t6. Mine has the constant in t6 and the mask in t7.

How did the target get that? Because the mask was PINNED to t6, so the constant couldn't use t6 and took t7.

Lever-free, we need the mask to win t6. The mask's priority vs the constant's: the constant (2 refs, live 563→use at ~570? or 76?) — if its live range is 563 to 570 (7 insns), priority 2/7=0.29; the mask 39/30=1.3 → mask wins. But the mask was born at 571, AFTER the constant's assignment... priority order should still allocate the mask first.

Unless the mask's qty is not 13 refs. Let me check: reg 15 (t7) has how many refs? In the lreg summary, reg 87 used 13 times across 179 insns — but the mask is reg 15 at greg time. Hmm, the mask pseudo number is 87? In the greg dump, `(set (reg/v:SI 15 t7) ...)` means the pseudo was renamed to hard reg 15. The dispositions map 87 in 15. So pseudo 87 = the mask, with 13 refs, 179 insns (from the lreg list: "Register 87 used 13 times across 179 insns"). 179 insns! So its live range is huge (from insn ~16 to 195), not 30.

Because sched1 hoisted the mask definition to insn 16 (as we saw in the final asm), the lreg live range is 179 insns. So priority = floor_log2(13)*13/179 = 3*13/179 = 0.218.

The constants: e.g., pseudo 117 (10 refs across 12 insns)? Hmm, that doesn't look like a 2-ref constant.

Let me identify the pseudo of the 0x8E constant. In the lreg dump (after local-alloc), the constant insn shows `(reg:SI 14 t6)`. In the *pre-local-alloc* RTL it would be a pseudo. Let me look at the cse or flow dump for the constant.

Actually easier: in the lreg dump, look at the insns 563-564 (which are now `(reg:SI 14 t6)`). The disposition list tells us which pseudo → 14: 117 in 14 and 130 in 14. Pseudo 117: "used 10 times across 12 insns; dies in 5 places" — that's not a 2-ref constant. Pseudo 130 isn't in the lreg list I read (the list was truncated). Hmm.

Wait, the disposition list is from the greg dump (after global-alloc), but these constants were assigned by local-alloc (disposition "in 14" for a pseudo). Both 117 and 130 are in 14 at different times.

Let me directly find in the *lreg* dump the insn 563-564 region and see the pseudo number before allocation... the lreg dump is AFTER local-alloc, so it shows hard regs.

Use the cse or flow dump instead. Let me grep the flow dump for the constant -520093554.
