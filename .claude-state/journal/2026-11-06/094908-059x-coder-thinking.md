---
ts: 2026-11-06T16:49:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EXMxMXpmxXV21641fMsR
---
All 6 or worse. The s16 variant is still 6. Let me check w6_htop's diff — maybe it's the same swap.

I need to flip the allocation. Let me look at the tie groups and priorities more carefully. Maybe I can influence via the `s0` increment position or `a`'s type.

Another idea: change the *mask/expression* to reduce h's refs. h's nrefs is 4 (per the dump). Why 4? h is defined once and used once in the C, but the RTL has 76 used at insn 35 only. Hmm, reg_n_refs might count REG_DEAD notes? No. Let me check the actual RTL again: reg 76 appears at insn 30 (def) and insn 35 (use) → 2 references. But the stats say "Register 76 used 4 times across 3 insns". So nrefs 4. Maybe reg_n_refs counts both the def and use twice? Whatever — all the relevant regs have 4.

Let me compute the priorities using the actual qty birth/death. Actually, let me look at the .lreg dump's allocation output to see the assigned hard regs and confirm the order. The .lreg dump is after local-alloc; the final .s shows the result.

Alternative approach: change the *life* of the h group by moving the `s0 = s0 + 1;` statement. The h group {76,81,82} spans insns 30..39. The t group {77,83} spans 25..39. If I move `s0 = s0 + 1` between... the death of 82 is at insn 39 (the addu), independent.

Hmm, what determines the qty death? The last use of the group. 82's last use is insn 39. Both groups die at 39. Births: t 25, h 30. So t's life (28) > h's (18). t has lower priority.

To make t's priority higher, t's life must shrink below h's. t is born at 25 and its use is at 39 (the addu). That's inherently long.

Alternatively, lower h's priority by making its life longer: h born at 30, used at 35 (the <<4). If I could make h's use later... the expression `(h << 4)` is used in the address computation; it's naturally at 35.

What if I restructure the expression so h's load is used later? E.g., compute `h` earlier (in the previous iteration?) no.

What if h is used twice: `(h << 4)` and something else? That would raise nrefs but maybe also extend life.

Hmm, let me think about the tie group {76,81,82}: it's formed by ties. The group's qty birth = 76's birth (30), death = 82's death (39). What if the tie chain is broken, e.g., if 81 doesn't tie with 76? Then the groups change and priorities differ.

The tie at insn 35: `81 = 76 << 4` with 76 dying → tie. If 76 did NOT die at 35 (e.g., h is used again later), no tie → 81 is its own qty (life 35-37, pri high) and 76 is its own qty (30-35, pri 8/10=0.8). Hmm.

What if h is used later too: e.g., `func(..., (s16)(... + a + h), ...)`? That changes the code.

Let me think about the target's tie structure. In the target, 76 (h) = $3, 81 = $3, 82 = $3 — so they ARE tied. And 77 (t) = $2, 83 = $2 — tied. So the tie structure is the same; only the group allocation order differs.

Group priorities (from the qty):
- t group: birth 25, death 39.
- h group: birth 30, death 39.
nrefs: let me get them from the dump: 76 nrefs 4, 77 nrefs 4. Same. So h group has a higher priority (shorter life).

Unless the qty's nrefs for a tied group is the SUM. In combine_regs, after tying: `qty_n_refs[sqty] += ...`? Let me read the tie completion code.
