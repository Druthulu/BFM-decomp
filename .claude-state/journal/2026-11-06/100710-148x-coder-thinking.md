---
ts: 2026-11-06T17:07:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SMtALU6vaSJzpMCkRuuo
---
In no-pin: reg 117 in 14 (t6) and 130 in 14 (t6)? Two pseudos in t6 — they're in disjoint live ranges. And 87 in 15 (t7), 98 in 17, 95 in 18...

So the mask (which pseudo?) got t7 (15) = reg 87? "Register 87 used 13 times across 179 insns" — 13 refs, 179 insns → that's the mask (m24). It's in t7 (15).

And the 0xE100008E constant: "Register 117 used 10 times across 12 insns"? No wait, 117 in 14 (t6) — the lreg list has "Register 117 used 10 times across 12 insns; dies in 5 places". Hmm, 10 refs.

Which pseudo is the constant? Let me find the insn with 0xE100008E in the greg dump and see its reg. Let me grep the greg dump for "0xe100" near the function.
