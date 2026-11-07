---
ts: 2026-11-06T12:40:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3xwlI0FL3tV0lvulLRKm
---
My counting is wrong because objdump lines have 3 tab-separated parts only for insns; label lines have fewer. Also the delay-slot indentation. Hmm, `parts[-1]` gives mnemonic+operands but with tabs? Let me print raw lines 12234..12300 to see the structure.

Actually let me just print raw lines with the address and decode. Simpler: print lines from start to start+80 raw.
