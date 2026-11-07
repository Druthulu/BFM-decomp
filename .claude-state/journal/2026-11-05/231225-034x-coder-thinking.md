---
ts: 2026-11-06T06:12:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JkAv1u0SYtiaaYacNn4o
---
No hard reg 16 in the .lreg RTL for that function. So where does the conflict with 16 come from?

Hmm — maybe I'm misreading: "72 conflicts: 72 73 ... 2 3 4 5 16 29" — maybe these aren't all "conflicts" in the matrix but the entry includes... hmm. Actually wait: maybe the .greg dump section I read (line 1947) belongs to a DIFFERENT function than the .lreg section at 2316! The .greg dump might be from a different function ordering. Let me check: .greg line 1947's function header ";; Function func_801804A0" and the dispositions. And .lreg at 2316 is func_801804A0. Both fine.

But: the .greg dump at line 31 showed `16 s0` — that's an earlier function's RTL.

OK here's another thought: in global.c, conflicts with hard regs come from `hard_regs_live` which is initialized at function entry from... let me check: `global_conflicts()` sets up `hard_regs_live` at the start of the function with the incoming hard registers? Actually there's `regs_set_between_calls` etc.

Honestly, the mechanism doesn't matter that much. What matters: r72 (param) got $17, r73 got $16. The allocation order line: 78 77 134 140 72 167 73 ... So r72 is allocated 5th. Before it, 78,77,134,140 took v0/v1/a0/a1. So when r72 is allocated, the callee-saved regs $16.. are all free; it should pick $16. But it got $17!

Unless... global.c assigns from the *lowest-numbered free* register, but skips regs in the allocno's conflict set. r72 conflicts with 16, so it can't take $16 → takes $17. Then r73 conflicts? r73 conflicts list: "72 73 74 75 76 80 2 3 4 5 29" — no 16, so r73 takes $16.

So indeed r72 conflicts with hard reg 16. That conflict must come from the RTL of this function. Where? The .lreg dump is AFTER local allocation (local-alloc runs before global? No — order: cse, then local-alloc, then global-alloc). Hmm, actually gcc order: ... flow, local-alloc, global-alloc (greg), reload. The .lreg dump is after local allocation. So by then some pseudos are in hard regs (locals). Maybe a local pseudo got $16 in local-alloc? Then r72 would conflict with it — but then the hard reg 16 would appear in .lreg.

Let me search .lreg function section for "(reg:... 16" or "16 s0" patterns generally.

Actually my awk searched `reg[^ ]* 16` within parens which requires "(reg... 16" then ")". Let me just grep "s0" in the .lreg section.
