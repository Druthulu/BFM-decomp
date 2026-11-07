---
ts: 2026-11-06T08:33:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xF1o7eIlbgEqV0p44Uzv
---
Good: objfn.sh dumps candidate fn; and for target I need the build object. Maybe there's a similar tool that disassembles the target from build. Let me check tools/ for a "target" helper, e.g. tools/objdiff or md module. Actually delever_search has md.insns_from_object; and it knows the base object path from build. I can write a tiny script under my shard dir that imports md (markdown? "match data"?) and prints target insns. Let me look at how delever_search computes `base` (the target object) — lines ~200-260.
