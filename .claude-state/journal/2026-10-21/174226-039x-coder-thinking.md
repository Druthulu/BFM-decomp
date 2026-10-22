---
ts: 2026-10-21T23:42:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_faBXhrin1xnADyU1hEMu
---
This is the local-alloc for block-confined pseudos. The key: "Only the pseudos that die but once can be handled" — local-alloc handles a pseudo whose live range is within one basic block and which dies once. It assigns regs by "qty" (quantities) and the priority ordering.

In gcc 2.7 local-alloc, the "qty" mechanism: within a block, quantities are formed by merging regs that don't conflict; then qtys are sorted by priority and assigned hard regs in order (the best reg first).

The priority: pri = floor_log2(n_refs)*n_refs*size/(death-birth). Constant pseudos get their priority decreased (reg_live_length *= 2 for reg_equiv, but that's for global-alloc; in local-alloc, the note says "Note that the statement below does not affect the priority in local-alloc!").

Let me look at how a "constant register" priority is decreased in local-alloc. Search for "decrease the priority" in the file: it was in update_equiv_regs (global part). In local-alloc (block_alloc), the qty priority is computed from n_refs, size, birth/death.

Key: within a block, quantities that don't conflict are merged into one qty (a "quantity" = a set of regs that can share a hard reg). Then qtys are sorted by priority and assigned hard regs: the first qty gets the "best" reg ($2?), etc.

So: which hard reg does the first qty get? In `allocate_qty` / `find_reg`, the reg selection prefers... In gcc 2.7 local-alloc, the hard regs are allocated in the order of the "reg alloc order" for the class, which for MIPS is: $2 (v0), $3 (v1), $4-$7 (a0-a3), $8-$15 (t0-t7), $24-$25 (t8-t9), $0 (zero), $31 (ra), $16-$23 (s0-s7)...

So the first qty (highest priority) gets $2 (v0), the second gets $3 (v1), etc.

In the target (pinned c1=$3), c1 is a hard reg from the start, so it's excluded from the qty assignment. The remaining pseudos: the byte loads (each a separate qty? or merged), the constants.

Now, in the unpinned version, the byte-12 pseudo and c1 both end up needing $2/$3: c1 got $2, byte-12 got $3.

Priority: c1: n_refs=3, size=1, (death-birth) = small (its live range in the block: from set to last use). byte-12: n_refs=2, range long (from its load to its store, spanning much of the block) → 2*2/(large) vs 3*1/(small) → c1 higher priority → c1 gets $2. ✓.

For the target, we want the constants (0xA0 etc.) to get $2 and c1 to get $3. But wait — in the target, c1 is pinned to $3, so it's out of the picture, and the other constants/bytes get $2 etc. But the target's byte-12 got $6 (a2)! Why not $3? Because in the target, the qty for byte-12 conflicts with... hmm, if c1 is hard $3, then the byte-12 qty could get $3? But c1 occupies $3 → byte-12 gets $4? ($4=a0 is live across the call?) The byte-12's live range spans the AddPrim call setup where a0/a1 are used → conflict with $4/$5 → $6 (a2) is free. ✓ consistent.

So in the unpinned version, to get byte-12 into $6, c1 must take $3 (or $2) and a0/a1 must be live during byte-12's range.

Wait, in my unpinned candidate byte-12 got $3 (v1) — because $2 was taken by c1+constants, $3 was free. If c1 took $3, byte-12 would need $6 (as $4/$5 conflict). Hmm, but would $4/$5 conflict? In mine, byte-12's range: from its load (271c) to its store (275c) — the same as the target. In mine, a0/a1 are set at 2708/270c (later than in the target: in the target `move a0,s2` was at position 55, `addiu a1,s0,12` at 57, both before the byte-12 load at 271c). In mine, `move a0,s2` is at 2708 (after byte-12's load at 2704?). Hmm.

So in mine, a0/a1's live ranges start later, so they might not conflict with byte-12 → byte-12 could get $4? But it got $3. Because the priority order: c1 first ($2), then byte-12 ($3), then others.

OK so the whole thing hinges on: c1 must NOT be the highest-priority qty, and it must conflict with the $2-holding qty.

Approach: give c1 a LONGER live range (so lower priority) and ensure it conflicts with the constants' qty.

The conflict: c1's range overlaps the constants' ranges. If I set c1 early (before the 0xA0 stores) → conflict + long range → lower priority → the constants (short ranges) win $2 → c1 gets $3.

But m01 (c1 set right after the byte group) gave 11 with const in v0. Hmm! So it didn't work. Why? Because with c1 set early, its range is long BUT the constants' ranges are even shorter... Let's compute: pri = floor_log2(n_refs)*n_refs*size/(death-birth).

Constants 0xA0: n_refs = 3 (1 set + 2 uses) → floor_log2(3)=1 → 1*3*1 = 3 → /(death-birth). If its range spans 2 insns → 3/2 = 1.5.
c1 (set early): n_refs=3 → 3/(long range, e.g. 10 insns) = 0.3.
byte-12: n_refs=2 → 1*2 = 2 /(long range ~20) = 0.1.

So 0xA0 (1.5) > c1 (0.3) > byte-12 (0.1). So 0xA0 should get $2 first... but m01 gave const -160 in v0!

Hmm, unless the ranges are computed differently, or the "constant register priority decrease" applies: in local-alloc's block_alloc, is there a decrease for constant pseudos? The comment in update_equiv_regs said "Note that the statement below does not affect the priority in local-alloc!" — that was about reg_live_length *= 2 (global). Hmm.

But hold on: maybe in local-alloc, constant pseudos are handled via "equiv" and get a special priority. Let me look at block_alloc's qty ordering and the "not_preferred_regs" logic. Let me read more of block_alloc (lines 1180-1400).

Actually, wait. There's a much more relevant thing: in the RTL, the constant -160 might not be a separate pseudo at all! GCC 2.7's `combine` might have turned `c1 = -0xA0` into a constant that gets substituted directly into the `sh` instructions (since a constant store can be done with an immediate? No, `sh` needs a register; but combine can create `(set (mem) (sign_extend (const)))` → the machine would need a register).

Hmm, but in the target the constant IS in a register ($3) and shared between two stores. So it's a pseudo with 2 uses.

Let me look at how local-alloc decides which reg the qty gets. Let me read the rest of block_alloc and the qty allocation function.
