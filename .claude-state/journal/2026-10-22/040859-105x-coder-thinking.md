---
ts: 2026-10-22T10:08:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZKc5tvrUaGp0AMgW7qo5
---
This is a rabbit hole. Time management: ~2h40 spent. Let me now move to the remaining two items (8017DA30, 8017D81C, 8018389C — three items), give each ~20-30 min with ≥30 tries, and then write up.

Let me plan the remaining work:
- 8017DA30 (best 4): the target hoists the call's arg setup to the top of the arm; the launder anchored it. Mechanism: sched1/reload_cse sink the arg setup. Lever-free: maybe a different statement order or an extra temp.
- 8017D81C (best 20): constants materialized at their assignment vs first use; the launder's read births the pseudo at the assignment. Lever-free: maybe make the constants live across the call (declaration at the top, assigned after the call) — the notes tried that (v2: 19, frame grows).
- 8018389C (best 14): the magic 0x66666667 sunk next to its mult instead of the tail top + a v0/v1 swap.

Let me look at each and design batches.

Let me start with 8017DA30 (best 4). Let me read the def and the notes again.

Notes: Target (63 ins): the else arm's SECOND call is set up at the TOP of the arm (`move a0,s1` / `addiu a1,s0,36` / `lui a2,%hi(D_801817B0)` / `addiu a2,a2,0`, insns 36-39), then `li v0,51` (40), `jal func_80128EA8` (41) and the store `sb v0,39(a0)` in the delay slot (42).

The lever: `__asm__ __volatile__("" : "=r"(q), "=r"(p), "=r"(e) : "0"(q), "1"(p), "2"(e));` + two pins ($16 on ent, $4 on q).

Residual: every lever-free spelling lands on 4, all ORDER: ours emits `li v0,51` / `sb v0,39(a0)` EARLY (37-38) and puts `addiu a1,s0,36` in the call's delay slot.

So we need the call's arg setup at the top of the arm and the store in the delay slot.

Let me read the def (orig.c) for this item.
