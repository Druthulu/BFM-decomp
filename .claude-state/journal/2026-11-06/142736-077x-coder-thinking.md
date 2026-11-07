---
ts: 2026-11-06T21:27:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H3sc2CLMExKTALUqEyzF
---
The awk is matching the first function (func_80160C28?) — wait, this is item 2's TU (ov_SC03_110). The function func_80181BF0 is at line 11142 in .cse2. The grep found sets at relative lines 187, 276 — those are probably the call return and the sp20 load, both early. Hmm, but I expected a trailing `(set (reg:SI 2 v0) (reg/v:SI 16 s0))`.

Wait, the awk exits at the NEXT "Function func_80181BF0"? No — the pattern `/Function func_80181BF0/` matches the same line, but NR>n excludes it. So it prints until the next function header. Hmm, but "Function func_" patterns: the next function is func_80181C9C. My awk exits only on another "Function func_80181BF0", which won't occur. So it prints the whole rest of the file! That's why the grep found many. Let me fix: exit at any ";; Function".

Let me redo.
