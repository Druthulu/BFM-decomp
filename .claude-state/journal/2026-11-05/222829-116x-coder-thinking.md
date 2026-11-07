---
ts: 2026-11-06T05:28:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_I0q51fy4tAzqimfebWoC
---
The pattern doesn't match. The register number for sp in the dump might be different, or the address is a pseudo. Let me look at the function's dump directly. Let me find where our function's RTL is. The dump includes function names? Let me grep for "func_8014DF94" with context.

Earlier: line 234, 3089, 55640 in the .flow dump reference the source file path. Let me look at the context around line 234.

Actually, the dumps are from cc1 with `-d` flags; they typically have the function name in a header comment. Let me grep for the function name as a word.

Hmm, the three hits were the source file path in line notes. The function itself might be labeled. Let me look at the .flow dump near the function's insns — search for "D_80078E" or the call to func_8014E284.

Let me grep for "func_8014E284" in the flow dump.
