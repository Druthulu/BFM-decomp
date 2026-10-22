---
ts: 2026-10-22T01:12:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Knu78z9uH0nUQ4VdVbu3
---
Still 2 for func_80191020.

Let me check the residual of q1 once more and think about the delay-slot difference:
```
136  bne a2,v0,cb0 | bne a2,v0,cb4
137  andi a1,a1,0xffff | sll a2,a2,0x8
```
Hmm, interesting: in mine, the bne's delay slot is the `andi` (the mask of the call argument) — which is computed MUCH later in the source (at the call). So the scheduler moved the andi *up* into the bne's delay slot?! That's the "reorg" hoisting the andi (which is independent) into the delay slot.

In the target, the delay slot has the `sll` (the speculative shift).

So the reorg (branch reordering) hoisted the *andi* in mine but the *sll* in the target. Hmm, and in the target there's ALSO a `sll a2,a2,0x8` at cb0 (the in-place shift) — so the target has the sll twice (once speculatively in the delay slot, once in place) while mine has the andi once.

Hmm! So in the target, the reorg hoisted the *sll* (a duplicate execution of the shift — the shift is idempotent-ish: the source does `sx = sx << 8` once; the reorg duplicated it into the delay slot speculatively, and the in-place one remains). GCC's reorg does that when the instruction is safe to speculate (the shift's result isn't used until later).

In mine, the reorg instead hoisted the `andi` (also safe to speculate) — hmm, and the andi is *not* duplicated (it appears once, in the delay slot) → hmm, then the andi in the jal's delay slot is missing? Hmm, in mine, where's the andi? At 137 (the bne's delay slot) — and the jal's delay slot has something else.

So: the target's reorg hoisted the sll into the bne's delay slot; mine hoisted the andi. The choice depends on the scheduler's order.

To flip it, maybe the *order* of the andi and the sll in the source matters. The source:
```
sx = sx << 8; /* in place, so reorg can steal it into the bne delay slot */
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
The andi is inside the call's argument expression (computed at the call). The sll is a separate statement before it.

Hmm, what if the argument were computed into a variable *before* the sll?
```
arg = (vol | (0x3000 | sx)) & 0xFFFF;   /* hmm, sx is shifted after */
```
Hmm, the order matters: the sll must come before the arg computation.

What if:
```
sx = sx << 8;
arg = (vol | (0x3000 | sx)) & 0xFFFF;
func_8002D4C8(0x9E5, arg);
```
The arg is a new local → the frame changes (the target's frame?). Hmm, risky.

Hmm, what if the andi's expression were written differently: `(vol | (0x3000 | sx)) & 0xFFFF` vs `((vol | 0x3000 | sx) & 0xFFFF)`? The same.

Hmm, what about the *cast* on sx? no.

OK, let me consider: the difference is 2 (one instruction misplaced). The developer's rule: 30 tries + 20 min → WALL. I have: 9 (variants) + 24 (combos) + 9 (p) + 10 (q) + 11 (old) = 63+ ✓, and ~1 h ✓.

So func_80191020 = WALL with the tag "sched1-reorg-delay-slot" or similar. Hmm, the walls.txt has "sched1-birth-boost" and "sched1-argcopy-hoist". A new tag: `sched1-reorg-speculate` — the reorg pass speculating the shift vs the mask into the bne's delay slot.

Similarly for D96C/EA24: the tag could be `sched2-order-li` hmm. The difference: the order of `li a0,409` and `lw v1,32(s0)`. Hmm, that's a sched2 (the final scheduling) or sched1 decision. Let me call it `sched1-order-li-load`? Hmm. Let me use `sched-order-swap`.

Hmm, hmm. Before finalizing these as walls, let me try ONE more idea for D96C/EA24: the "k sites" insight (the *number* of real 2nd sets matters). What if the v1 site gets 2 or 3 casts (v1 = (s16)v1 twice)? And the e site: the do-while.

Let me also try: the v1 site: `v1 = (s16)v1;` + the do-while; the e site: the do-while + a re-read.

Let me write a final quick batch for D96C/EA24 (multi-statement sites) and, if nothing, record the walls.

Actually, wait. Let me reconsider the D96C/EA24 difference once more. The target's case0 block:
```
1b3c: li a0,409
1b40: lw v1,32(s0)
```
and the case1 block:
```
1b60: li a0,409
1b64: lw v1,32(s0)
1b68: li a1,3
```
So in the target, BOTH blocks have the li before the lw. In mine, the order is swapped in the case0 block (and maybe the case1 block).

Hmm, since the two blocks are structurally identical, the scheduler treated them the same in the target. In mine, one is swapped.

The scheduler's order for two independent instructions (a constant load and a memory load) — hmm, in the target the *constant* comes first (it's cheaper/faster). In mine the *load* comes first.

What could change that? The scheduling cost model depends on the block's contents. Hmm, the do-while at the e site adds instructions to the case1 block (not case0). Hmm, but the case0 block is the one that differs.

Hmm! Wait: which block is the *e* launder in? The e launder is in case1. And the case0 block differs in the order. Hmm, but the blocks share code? The `shared` block is common. Hmm, the *scheduling* is per basic block; the case0 block ends with `goto shared`.

Hmm, so why would the case0 block's order differ? Because the *register pressure* or the block's live ranges differ (the e value's live range).

Hmm, hmm. Let me try the "k sites" idea: what if BOTH sites get multiple statements? E.g. the v1 site: `v1 = (s16)v1;` × 2, and the e site: the do-while × 1.

Let me write a final generator with a few of these and run it for both items. If no luck → WALL.
