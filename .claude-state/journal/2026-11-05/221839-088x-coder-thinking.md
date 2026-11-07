---
ts: 2026-11-06T05:18:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v7kbh9QeBoJYhpgzTcSm
---
Now append the results.tsv rows. Let me use printf with tabs. One row per item. Let me do item 1 first.

Evidence ≤140 chars.

Item 1 evidence: "reorg eager fill takes li v0,128 into bnez slot; stop_search_p stops only on asm/jump/label; li no trap, epilogue live-in is sp only"
Length: let me count ~135. OK.

Item 2 evidence: "do-while on a1-free ifs keeps load after store and alloc (a1 refs 7); union-member read of EA6 forces cse reload; 141/141 0"
~125. OK.

Let me append with a python one-liner? The brief says scripts, not inline python -c. Use printf via bash. That's a shell builtin; fine.

Actually, "One action per command". Let me do item 1's row, then item 2's row, separately.
