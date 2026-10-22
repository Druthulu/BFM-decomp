---
ts: 2026-10-22T07:19:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_rbMrY3iUqyB5l7NiSuUF
---
The .rtl dumps (pre-reload? or post-reload) are nearly identical between the tree and C2 — the constant appears in the same places. So the difference arises later (in sched1 or reload).

Let me diff the two .sched dumps around the relevant region to see the chain order.

Tree chain (from the .sched listing): code_label 256, 450, 451, 259, ...
C2 chain: ..., 266, 451, 452, 270, ...

Wait, in the tree the chain after 451 is 259 (`li v0,160`), and in C2 after 452 is 270 (the division).

Hmm, so in the tree the constant is at the block head. Let me check the tree's .sched chain more fully to see the block structure (the case-0 block). Let me print the tree's .sched chain from the code_label 256.

And for C2 the same.

This tells me the scheduled order. But the question is WHY.

Since both .rtl dumps look identical in this region, maybe the difference is in the .dbr/.sched2 or in the reload's handling.

Hmm, wait: maybe the difference is not the constant's placement but the pseudos' allocation: the tree's magic ends in a0 (a hard reg at the sched stage? no, it's pseudo 147 in both).

Hmm, in the tree's .sched: `(insn 450 256 451 (set (reg:SI 147) (const_int 1717960704)))` — pseudo 147. In C2: `(insn 451 266 452 (set (reg:SI 147) ...))` — also pseudo 147. Same pseudo!

So the same pseudo 147, but in the tree it's at the block head and in C2 it's after the ×127.

So the SCHEDULER placed it differently. Both have priority 1 for the materialization insn. The tie-break: the ready list order (by UID, reverse insertion). In the tree, insn 450 (the lui) has a lower UID than the others? Hmm, in the tree the constant materialization has UIDs 450/451 (high) while the `li 160` has 259 (low). In C2 the constant is 451/452 and the li 160 is 270.

Hmm, so in the tree the chain has [450, 451, 259] and in C2 [266, 451, 452, 270].

Chain = reverse of launch order (per item 3). So in the tree, the launch order was: ..., 259 (li 160), 451 (ori), 450 (lui), ... i.e. the constant was launched LAST among these. In C2: ..., 270 (div), 452 (ori), 451 (lui), 266 (×127) → the constant was launched BEFORE the ×127.

Hmm, so in the tree the constant is launched last (lands first in the chain).

With equal priorities, the ready list order for ties = the most recently inserted first? If the constant (UID 450) was inserted into the ready list early (it's early in the RTL order? no, the RTL order has it late)...

Ugh, the RTL order: in the .rtl dump, where is the constant materialization relative to the ×127? Both dumps are identical there, so the RTL order is the same. So the difference is purely the scheduler's choice among ready insns.

Ties: gcc's sched1 ready list: `insert_to_ready_list` inserts the new insn at the FRONT if its priority >= the front's priority. So for equal priorities, the LAST inserted goes FIRST. The insertion order follows the RTL scan order. So among ready insns with equal priority, the one LATER in the RTL order is launched first.

In the tree: the constant materialization (450) is LATER in the RTL than the ×127? Let me check the RTL order: in the .rtl dump, the constant appears at lines 706 and 751, and the ×127 computation around 733-747. So the constant's materialization (line 706) is BEFORE the ×127 (733) in the RTL dump? Hmm, the .rtl dump is printed in chain order.

Hmm, but the .rtl dumps are identical between the tree and C2, so the RTL order is the same → the ready list insertion order is the same → the tie-break should be the same → the launch order should be the same! But it isn't.

Unless the ready list contents differ due to dependency availability (the ×127 becomes ready later, etc.).

Hmm, hmm. OR the .rtl dumps differ in the region I looked at (I only grepped the constants). Let me diff the two .rtl dumps properly (they're the same function, so a diff shows the differences).

Let me diff them.
