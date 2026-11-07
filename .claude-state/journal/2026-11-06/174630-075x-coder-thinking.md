---
ts: 2026-11-07T00:46:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5uUxAZSa1RRn2MzON6ii
---
The LOAD line in w16 is "            val = D_801B7A84;\n" — but the file has a blank line after it (from gen.py's template). Let me check: in w16 the lines were:

```
            func_8017F53C((s32)p);
            val = D_801B7A84;

            do { // !FAKE: do-while
```
So LOAD is followed by a blank line. Let me set LOAD = "            val = D_801B7A84;\n\n" and adjust.

Simpler: make all patterns robust by normalizing. Let me just rewrite gen2.py with the correct strings (LOAD includes the trailing blank line).
