---
ts: 2026-10-21T23:45:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bWnVqmVT7PKGdGcTkaUz
---
All variants ≥ 11, best 11. The 11 seems to be a floor: the base difference (const in v0 vs v1, byte12 in v1 vs a2, one extra nop).

Note the structure of the difference is fixed: the c1 constant lands in v0 and the byte-12 in v1. Since none of my variants moved the -160 out of v0, the allocation is robust: c1 always wins $2.

Why? Because c1's pseudo is a "constant" pseudo with a short live range, and local-alloc gives the highest priority to the shortest-lived quantity. To beat it, the constants (0xA0, -0x78, 0x78) must have a SHORTER live range than c1 AND conflict with c1.

Currently: 0xA0's range = set + 2 uses (3 insns), c1's range = set + 2 uses (3 insns). Both n_refs=3, similar lengths. If they're in the same block and the tie-break is by qty number (order), then whichever appears first in the RTL wins $2.

c1 appears AFTER 0xA0 in the source (in the const block) → 0xA0 should have the lower qty number → 0xA0 wins the tie → $2 for the 0xA0 qty. But c1 got $2 in all variants!

Unless the qty grouping differs: 0xA0, -0x78, 0x78 might be in the SAME qty (no conflicts among them) — and that qty has n_refs = 3+3+2 = 8 (plus 12 byte pseudos? they conflict with the const block? the byte pseudos are short-lived, before the const block → no conflict → they could be in the same qty too!). So the big qty = all byte pseudos + all const pseudos = n_refs ≈ 12*2 + 8 = 32, size 1, and its death-birth = the whole block → pri = log2(32)*32/(long) = 5*32/long.

c1's own qty (conflicts with the big qty? only if their ranges overlap): if c1's set is adjacent to its uses and doesn't overlap the others' ranges, c1 could ALSO be in the big qty! Then the whole thing is one qty → one reg ($2) → c1 in $2. That's exactly what we see: all the constants and c1 in v0!

So c1 is NOT conflicting with the constants. To make c1 conflict, its live range must overlap theirs. But even then, in the variants where c1's set was moved earlier (p1/p2), the const still landed in v0 — maybe because c1's range still didn't overlap (the RTL might have been re-scheduled).

Hmm, wait: if c1's set is moved before the 0xA0 stores, c1's range spans them → conflict → separate qtys → then which gets $2? The big qty (all constants + bytes, n_refs ~32) vs c1's qty (n_refs 3). Priority: pri = log2(n)*n/(length). Big qty: 5*32/L where L is the big qty's live range (long). c1: log2(3)*3 = 3, /c1's length.

If L (big qty) is much longer than c1's length, c1 wins → c1 gets $2! That's what we observe. To flip, c1's range must be LONGER than the big qty's... impossible, or the big qty must be shorter.

Alternatively, make c1's n_refs larger: e.g. c1 used 3+ times? But the target has only 2 uses of the -160 value (sh 20, sh 36). Extra uses would add instructions.

Hmm. What if c1's range is long (spans the whole block) → pri = 3/L_c1; the big qty: 5*32/L_big. For c1 to win over the big qty we need 3/L_c1 > 160/L_big → L_c1 < L_big * 3/160 ≈ L_big/53. So c1's range must be ~50x shorter than the big qty's. The big qty's range is the whole block (say 60 insns) → c1's range must be < 1.2 insns. Not possible with 2 uses.

So the big qty always wins $2 as long as c1 is separate. And c1 shares the qty when it doesn't conflict. Either way c1 ends up in $2? No wait — if c1 is in the SAME qty as the constants, they all get $2 (that's the current case). If c1 is in a separate qty, c1 loses $2 to the big qty and gets... $3? But empirically (p1/p2 variants) the const was still in v0, meaning c1 was still in the same qty or won the tie.

Hmm, so how do I force c1 to be a separate qty AND lose the priority? Make c1's range overlap the big qty's range but be much longer... The formula: c1's pri = 3/L_c1 (L_c1 = death-birth in insns), big qty pri = 160/L_big.

If c1's range overlaps the constants' range, then c1 is a separate qty. But careful: the "qty" grouping in local-alloc is not about overlapping per se: a qty is a set of regs that can share a hard reg; two regs conflict if their live ranges overlap. So c1 conflicts with the constants if c1's live range overlaps any of their ranges.

The constants' ranges: 0xA0: [set, use, use]; c1: [set, use, use]. If c1's set is between 0xA0's set and 0xA0's last use, they overlap → conflict.

But my p1/p2 variants did that and c1 still got $2. So either the RTL didn't have the overlap (the compiler re-ordered?), or the priority favored c1.

Hmm, wait. Maybe the priority isn't the issue: maybe local-alloc's "qty" for c1 vs the big qty: when assigning hard regs, the qtys are sorted by priority, and each gets the next available reg in the class order. But there's a subtlety: local-alloc in gcc 2.7 for a block does "block_alloc" which handles qtys, but only for pseudos whose live range is confined to the block. The class order for MIPS: the "reg_alloc_order" for the general regs. If the first qty gets $2, the second gets... hmm, but MIPS's alloc order might be $2,$3,$4,... or reversed. In the target, the byte-12 got $6 (a2) — the 6th reg in the order $2,$3,$4,$5,$6? So the order is $2,$3,$4,$5,$6,... (a0-a3 after v0,v1). Actually MIPS reg_alloc_order for CALL_USED: v0($2), v1($3), a0-a3($4-$7), t0-t7($8-$15), t8,t9($24,$25), then s0-s7, then ra/zero.

In the target, the byte-12 got $6 = a2, i.e. the 4th reg in the order after $2,$3,$4,$5 — but $4 (a0) and $5 (a1) were unavailable (live for the call). So the byte-12 was the 2nd qty after c1($3) and the constants($2)... but the constants are in the same qty as the bytes? Hmm.

This is really intricate. Let me try a targeted experiment: make c1 conflict with the constants AND give the constants a shorter range than c1. The constants' ranges are inherently ~2-3 insns. c1's range must be > that but its n_refs is also 3 → pri_c1 = 3/L_c1 < 3/L_const → the constants win $2 → c1 gets $3 (if $3 free).

But empirically, moving c1's set earlier didn't do it. Why? Maybe because when c1's set is earlier, the RTL for `c1 = -0xA0` and the const block get re-scheduled such that c1's range is... or maybe the compiler's `combine` pass propagates the constant -0xA0 into the two sh instructions and eliminates the pseudo?! Hmm, if combine propagated the constant, the stores would be `sh $N,-160`... no, MIPS can't store an immediate.

Wait — maybe with c1 set early, GCC's cse/combine merged c1's value with... hmm, -0xA0 vs 0xA0: note -0xA0 = 0xFFFFFF60. The store `*(s16*)(p+0x14) = c1` stores 0xA0 as s16 = -160.

Hmm! Interesting: `sh` of -160 stores 0xFFA0. And the other constant 0xA0 = 160 stores 0x00A0. Different.

Let me look at the actual RTL/asm of a p1 variant to see where the -160 went. Use tryc.py on v_o0_p1_s32.c.

Let me check what registers the constants got in v_o0_p1_s32.c.
