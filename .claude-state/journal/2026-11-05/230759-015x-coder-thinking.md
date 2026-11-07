---
ts: 2026-11-06T06:07:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ob37dtaL7v2pX6V3vuQB
---
The whole function: mine puts `a0` (the param, saved across calls) in s1, and the loop pointer s2 in s0. Target: a0 in s0, loop pointer in s1. So the register assignment of the two callee-saved regs is swapped.

In the target, a0 param is in $16 (s0) and s2 (the loop pointer) in $17 (s1). Mine: a0 → $17 (s1), s2 → $16 (s0).

That's a global-alloc ordering issue. The pin `$18` forced s2 into $18; lever-free, s2 goes to $16.

So we need a real-C way to make the param pseudo win $16. Let me see the whole diff from the start to know what else differs. Let me get the full diff. Use --keep to get object path? Or run delever_search --explain. Let me just run the tool with more tail: dt.sh 120.

Actually, better: use `--explain TU FN` which reads one body's residual. But --explain uses the tree's body, not our file. Let me just get the full dt output into a file and read it.

I'll run the tool manually and save to a log under my item dir (allowed).
