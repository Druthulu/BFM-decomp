---
ts: 2026-11-06T12:13:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g84mB1bTzFpl39GExdn3
---
`mnem` includes operands? mi.group(3) from objdump output — objdump -drz line format: `  0:	27bdffe0 	addiu	sp,sp,-32`. So mnem = "addiu\tsp,sp,-32" (the rest of the line). Yes! The diff output showed "sh	v0,22(s0)" — that's mnem with registers. Great, so the diff DOES show registers (I misread earlier: line 4 shows `sh v0,22(s0)`).

So the diff is fully informative.

Cluster A: mine has `srl a0,a0,0x6` then `sh v0,22(s0)`; target `sh v0,22(s0)` then `srl a0,a0,0x6`.

Let me see the context around index 310-320 in both. I need the target's insn list. Let me write a small script that dumps insns with index for the target (from baseline object) and for the candidate. I can reuse md.insns_from_object and oracle.baseline_path.

Simpler: write a script `.run/P40/T11/G31/G31/show.py` that takes TU FN [cand.o] and prints indices. For target, need the recipe's obj path. Let me look at oracle.recipes_by_src and baseline_path quickly.

Actually, I can use `--keep` on --try which prints the object's path. Then dump both. Let me check what --keep prints.

Alternative approach that's cheaper: the "explain" mode may already print full insns. Let me check --explain.

Honestly, I have the diff which shows the mismatch; I can infer context by knowing the C. Let me get a wider diff context by writing my own script that prints index, mine mnem, target mnem for a range. Let me write it — it's worth it for all 4 items.

I need the target insns. Let me find oracle.baseline_path and recipes.
