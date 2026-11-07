---
ts: 2026-11-06T17:10:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SDSOPQ4kI7l6bOvAJeHq
---
a1 compile error (probably the regex replaced m24 in the declaration line leaving junk). a2/a3 23 (slightly worse), a5/a6 21 (same).

Let me look at a1's error and fix the inline variant properly. Also, let me think about the allocation order.

The target has the mask in t6 and the 0x8E constant in t7. In mine, the constant takes t6 (allocated before the mask). To flip, either:
- the mask must be allocated earlier (higher priority), or
- the constant must not take t6.

The constant 0xE100008E is used at one place (insn 170). Its lreg live range is 12 insns (hoisted by sched1 to insn 5). Priority 0.67 vs mask 0.87.

Hmm, but the mask's lreg live range is 179 insns — wait, in the flow dump it's 61 insns, in lreg 179. Sched1 hoisted the mask definition to insn ~16, extending its range to 179. If sched1 had NOT hoisted it, its lreg range would be 61 and priority 39/61=0.64 — LOWER than the constant's 0.67! Interesting: so the mask's hoisting actually raised its priority above the constant's... but it still got t7.

Hmm, my numbers may be off. Let me compute from the actual lreg dump lines:
- 87: "used 13 times across 179 insns" → pri = floor_log2(13)*13/179 = 39/179 = 0.218 (size cancels).
- 117: "used 10 times across 12 insns" → if 117 is the constant qty with 10 refs?? That can't be a 2-ref constant.

I think the pseudo numbers in the lreg summary don't correspond to the flow dump's numbering due to local-alloc's qty merging. Let me instead find the constant's qty in the lreg dump directly: search for "const_int -520093554" in the lreg dump and see which reg it uses.
