---
ts: 2026-10-22T06:47:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_WERCeAN0MScRKWcvDOue
---
The ready list shows priorities with 7f000001 (boost) on insns 68, 56, 35, 24, 27, 40.

Now let's find which RTL insn numbers correspond to what. The .rtl dump (post-reload? tree.i.rtl) has numbered insns. Let me look at the cand dump's ready list too and compare.

Then map insn numbers to instructions via the .rtl or .sched dump's insn listing.

Let me look at the cand sched dump readylist.
