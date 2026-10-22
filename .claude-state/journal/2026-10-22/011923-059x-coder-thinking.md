---
ts: 2026-10-22T07:19:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_F80rbN1RizAxiDG4fKk5
---
Neither has the boost on the constant materialization (priority 1 for both). So the constant's placement difference isn't a boost.

Hmm, so what makes the tree's constant materialize at the top of the block?

In the tree, the chain is: [code_label 256, 450 (lui), 451 (ori), 259 (li v0,160), ...]. The constant is at the top.

In C2: [..., 266 (×127), 451 (lui), 452 (ori), 270 (div)].

The scheduler's ready list order... the constant's materialization (450/451) is a "birth" of pseudo 147 — but no boost.

Hmm, the difference might be the ORDER of the ready list ties. Hmm.

Alternatively — maybe the difference is not the scheduler but the RTL structure: in the tree, the constant's materialization is at the top because the DIVISION's expansion was placed differently.

Hmm, look at the tree's chain: the constant materialization (450, 451) comes right after the code_label 256 — the block head. That looks like the *sched1* placed it there, or the RTL order was already like that.

Let me look at the tree's .rtl dump (pre-sched) to see the original order. The .rtl dump is the RTL after reload (pre-sched1). If the constant is already at the top there, then the difference came from an earlier pass (reload / expand), not from sched1!

Let me check both .rtl dumps.

Actually — hmm, the `.rtl` dump might be the RTL before reload. Let me just look at where the constant materialization sits in both .rtl dumps.
