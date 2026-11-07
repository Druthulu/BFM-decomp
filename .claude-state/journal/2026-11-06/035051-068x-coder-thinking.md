---
ts: 2026-11-06T10:50:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gnMzbgDyI6w3sobXDbOI
---
Now find func_8018966C's lreg section. The .lreg dump prints the insn list with the qty numbers per block. Let me extract the region for this function. The dump file may be big; grep for the function label and print the surrounding lines.

The lreg dump format: it prints the function name? Let me grep "func_8018966C" in the .lreg file and find the block that contains unkC4 (offset 196 = 0xc4).

Better: find the block containing "196" loads. Let me grep -n "0xc4\|196" in the .lreg file.
