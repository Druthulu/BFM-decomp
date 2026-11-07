---
ts: 2026-11-06T16:41:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qu8ORFqonwst7jODTRaq
---
At lreg (after local-alloc, before global), block0+block1 use 72 and block2 uses 73. That's local-alloc's doing: within block1 (the then block), the uses of 73 were replaced by 72 — because local-alloc combined the copy 73=72 into block1? Actually local_alloc rewrites reg numbers for block-local pseudos: 73 is global (used in 2 blocks), 72 is global too... Hmm.

Wait: the lreg dump is after local_alloc, which only handles block-local pseudos. The rewrite of block1 uses from 73 to 72 must have been done by cse (cse1 merges 73 into 72 within the EBB). Look at the cse dump for w1: entry+then form one EBB (entry falls through to then), and cse's equivalence made 72 canonical → then uses 72. The else is a separate EBB → uses 73.

In the pinned orig, self=73 is arithmetic so cse keeps 73 everywhere.

So the problem is cse's copy propagation: `self = arg0` is a copy; in the EBB (entry+then), cse replaces 73 with the canonical 72. In the else EBB, 73 remains.

Target: both arms use the *same* register a1. If cse merged 73 into 72 in the then block and 72=a1, and the else uses 73 which global-alloc assigns a0 → mismatch. If instead global-alloc assigned 73=a1 (conflict with a0), then both would be a1!

So we need 73 to conflict with a0 (hard reg 4). In the pinned orig, 73 conflicted with 4 because... let me look: "73 conflicts: 73 2 3 4 29". The conflict with a0 arises because 72 is defined from a0 and 73's def (insn 11) uses 72 at a point where a0's live range still covers? In global-alloc, hard reg a0 conflicts with 73 if a0 is live at 73's def or use. a0 (reg 4) is live from entry to insn 4 (its only use is in `set 72 a0`), so it dies at insn 4. Then a0 shouldn't conflict with 73 (defined at insn 11).

Unless the conflict comes from elsewhere: in the pinned orig, the mask pseudo 74 got a0 (block-local), and global_alloc counts hard reg conflicts from all insns. Hmm, the conflict list for 73 includes 4 (a0) — maybe because the `$0` register variable (reg 0) is... no, 4 is a0.

Hmm wait, maybe in the pinned orig, a0 is used at insn 4 and 73 is live at insn 4? No, 73 is defined at 11.

Let me look at the o1 greg dump more carefully with conflict details, or compare with w1. In w1: "72 conflicts: 72 73 2 3 4 29" and "73 conflicts: 72 73 2 3 29". So 72 conflicts with a0, 73 doesn't. In o1: "73 conflicts: 73 2 3 4 29" — 73 conflicts with a0!

The difference: in o1, insn 11 is `73 = 72 + $0`. Register 0 ($0) is a *fixed* register; does 73 conflict with 4? Hmm, the conflict list for 73 in o1 has 4 but not 72 — because 72 was coalesced into 73's qty (local-alloc tied them). So "73 conflicts: ... 4" reflects the union of 73's and 72's conflicts — 72 conflicts with a0, so the merged qty conflicts with a0.

In w1, 72 and 73 were NOT tied into one qty globally; 73 conflicts without a0.

So the fix: make local-alloc tie the param pseudo 72 and self 73 into one quantity (as it did with the arithmetic op), so that the merged global allocno conflicts with a0 and gets a1.

In w1, local-alloc did combine 73 into 72 in block1? The lreg shows block0/1 using 72 — that's cse, not local-alloc.

How do 72 and 73 become the same global allocno? In o1, 72 is a *local* pseudo? Let's check o1 lreg.
