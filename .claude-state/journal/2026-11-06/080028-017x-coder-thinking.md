---
ts: 2026-11-06T15:00:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Td3SMJwLX4bh32AaNV5D
---
Good. So body = bare function definition; spliced over the tree's function.

Now, orig.c should be the current def extracted. Let me create a small script to extract the def from src for each item. Actually I can use a Python script under .run.

Let me write a helper extract.py that takes src, fn, outfile and extracts the def (from the line where `void fn(` starts to the matching closing brace at column 0). Since format is consistent (closing `}` at column 0), I can do simple.

Let me first get the exact def line for each of the 5:
- 090: func_80188498 at 3019, ends 3120
- 091: func_80189340 at 2983, ends ?
- 093: func_801827DC at 2951
- 094: func_80185240 at 2996
- 098: func_80182C8C at 5573

Let me extract them with a script.

Also check whether they're identical bodies (all from ov_SC02_026). Likely the same function duplicated in different TUs with different names. Let me diff them.

Let me write the extract script.
