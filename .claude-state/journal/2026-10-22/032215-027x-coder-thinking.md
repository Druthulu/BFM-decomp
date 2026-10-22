---
ts: 2026-10-22T09:22:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_RA7cijatxP9dqqp9s7A1
---
Only 1.1MB — great, dumps are small.

Now let's find the add in the RTL. Use rtl.sh-like extraction for the function across passes. Let me write a small extraction to show the function's insns in .rtl, .combine, .cse, .sched, .lreg passes and look for the "plus" tree with a1 and the shift.

Let me use the T10 rtl.sh with the dumpdir.
