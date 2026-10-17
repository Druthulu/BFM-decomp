---
ts: 2026-10-17T10:53:08.539Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm comparing j and k's live lengths against their scheduled streams, noting that k dies in zero places at r198 while j doesn't. Checking the allocno priority formula in global.c's allocno_compare, since both have HImode size of one word, the size factor should be equivalent for j and k.

I'm now considering hard register preferences — j's initializer is just a const_int move, not a copy from a hard reg, so a2 isn't preferred that way. I'm checking whether k conflicts with a2 at its birth point in the preheader, but nothing seems live there except possibly the spilled parameter n, which isn't actually live in a register. I'm also ruling out other calls and local-alloc explanations, trying to find what actually drives the register assignment order between j and k.

Switching to think about scheduling priority instead — birthing_insn_p boosts priority for single-set registers live at block end, but j has two sets so it doesn't get that boost, meaning ties are likely broken by instruction order (luid) rather than priority. I'm now digging into how the backward list scheduler sorts the ready list to figure out why j ends up first in one variant and last in another.

That makes sense in backward scheduling: early scheduling of a birthing insn means placing it late in the block, shortening register lifetimes. So in the preheader, non-birthing j gets lower priority and ends up placed earlier, explaining why j appears first in the base output — though this seems to conflict with tk_forj where j was last, unless that for-init actually lands in a different block since notes don't split blocks on their own.

I'm uncertain whether adjust_priority runs on leaf insns that are ready from the start versus only insns that become ready later, so I should just check this empirically by comparing the scheduler dump's ready list and priorities for the preheader block across the base and tk_forj variants, maybe dumping the 4-callsite version to see what's actually happening.

Since j is set twice, it won't get the single-set live-register boost from `birthing_insn_p`, confirming the order is what drives scheduling. I'll now dump `v_callsz` and inspect sched1's decisions for the preheader block.
