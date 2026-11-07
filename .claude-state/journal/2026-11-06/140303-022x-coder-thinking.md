---
ts: 2026-11-06T21:03:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k98N02fCjWaeH76vibW0
---
The .lreg dump doesn't print insns (only headers?). Maybe -dl is "local-alloc" and the RTL is in another dump. Hmm, .rtl is -dr (RTL dump after? -dr = rtl dump). The .lreg may only print the register info + blocks. Let's look at the .sched or .rtl for block 1 RTL with reg numbers.

Actually easier: .lreg printed "Register N in M." lines at the end? lines 140-141 show ";; Register 78 in 2." etc. That's odd.

Let me instead look at .rtl (final RTL after all passes?) Hmm -dr dumps after "final" (post-reload). Let me grep .lreg around line 136-141.
