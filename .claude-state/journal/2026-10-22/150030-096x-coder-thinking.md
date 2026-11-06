---
ts: 2026-10-22T21:00:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LQQzXT5DMoGabZW9wm3N
---
y4 (no by pin) still 4 ORDER — interesting, so the by pin isn't needed for the register (or it lands in s4 anyway).

Let me check y4's diff — maybe the residual is the same. If dropping the pin doesn't change the score, keep it (it's allowed to stay).

I've spent 25 min on item 3 (14:50 → 15:15). The WALL bar (≥20 min, ≥30 tries) is met: 36 prior + 24 mine = 60 tries.

Let me check the diff of y4 quickly, then wall at 4 with a sched1 tag.

Actually, let me reconsider the sched1 log once more: the key is "launching 152 before 165 at T-117" — the bx load was launched after ax. The birth boost: 0x7f000001 priority insns are those whose operands just became ready. GCC's sched1 uses `INSN_PRIORITY` and a special `birth` mechanism (sched.c: `priority = INSN_PRIORITY(insn) ... if (insn is in the "born" list) priority = 0x7f000001`?).

In the target, the order is by, ax, bx — the loads bx then ay. So the target's sched1 kept the source order. In mine, sched1 reordered because of the birth boost.

Since sched1's decisions depend on the RTL's uid order and dependencies, and the prior coder tried ~36 variants, I'll wall.

Wall tag: `sched1-order` — new? The walls list has `sched1-argcopy-hoist`, `sched1-birth-boost`, `sched1-chain-priority`. This one is a birth-boost-driven order of two independent addiu's (by vs ax) plus ay vs the index chain. The best fit: `sched1-birth-boost` (existing) — "sched1 vs local-alloc birthing-insn priority boost against a local-alloc constant". Hmm, not exactly. A new tag `<pass>-<what>`: `sched1-birth-order`? Let me define: `sched1-birth-order` — sched1's birth boost launches ax (165) before by (161) and ay before the index chain; the target keeps source order. Hmm, but the rule says a new tag must be defined in the evidence. OK.

Let me verify the y4 diff (same residual) and write it up.

Actually, wait. Let me try ONE more thing that could flip the birth order: make `ay`'s load later in the RTL by moving `ay = out.vx;` *after* `by = bx - 0x5D;` (v3 did that = 4). And make the `bx` load first (already).

What about making `ax`'s computation use `by`? No.

What if `ax` is computed as `ax = ay + 0x7B;` where `ay` is loaded *later* (after by's add)? v3: bx load, by add, ay load, ax add, bx add → score 4. Its diff might differ. Let me check v3's diff.

I'll do one final check of v3 and y4 diffs, then wall.
