---
ts: 2026-10-22T07:17:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_6CvfZNChjpq7KzMvA6Jq
---
Very interesting!

In the TREE, the constant materialization (insns 450, 451) is placed right after the `code_label 256` (the case-0 block head) — i.e., at the TOP of the block. And the `li v0,160` (insn 259) comes after.

In C2, the constant materialization (451, 452) comes AFTER the ×127 computation (insn 266).

Note the tree's constant pseudo is 147 (a plain pseudo), and in C2 it's also 147.

Hmm, the tree's chain: [code_label 256, 450 (lui), 451 (ori), 259 (li 160), ...]. In C2: [..., 266 (the ×127), 451 (lui), 452 (ori), 270 (the division)].

So the difference: the tree's constant is materialized at the top of the block; C2's later.

Since the chain is the reverse of the launch order (per my item-3 finding)... hmm, but wait: is that right? Let me re-derive with the item-3 evidence: in cand01 the move (15) had the boost and ended up LATE in the chain. So chain = reverse of launch order. Hmm, but actually maybe the correct reading is: the boost makes the insn land LATE in the chain. Let me redo this: in item 3's cand01, insn 15 (the move, boosted) was at chain position 4 (after the li at 3). The li (18) was at chain position 3. So the boosted insn landed later ✓.

Here: in the tree, the constant's materialization (450, 451) is at the TOP of the chain = early. If the chain = reverse of launch, the constant was launched LAST. In C2 the constant is later in the chain = launched EARLIER.

Hmm, so in the tree the constant's materialization was launched last (low priority) and in C2 early (boosted?). Hmm, that contradicts my earlier reasoning. Let me not rely on the chain/launch direction; instead use the "priority boost" evidence directly from the traces.

Let me look for the boost status of insns 450/451 (tree) and 451/452 (C2) in the traces.

Actually, the trace prints "insn[N]: priority = ..., ref_count = ..." per insn. Let me grep for "insn[ 450]" in the tree's sched dump and "insn[ 451]" in C2's.

That tells us the priority (7f000001 = boosted).

Let me checkboth.
