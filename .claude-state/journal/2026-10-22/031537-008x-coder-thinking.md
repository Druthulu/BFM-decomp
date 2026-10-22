---
ts: 2026-10-22T09:15:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IyZAJYyd1gAjUust5cgc
---
The last one only 14 lines — extraction failed (found something else, maybe a forward declaration). Let me check cur_func_8018483C.c.

Also the extraction regex may match a call site. Let me refine: match lines that start at column 0 with a type and the function name followed by `(` and the line contains `{` or is a decl ending with `;`. For 8018483C, `void func_8018483C(s32 a0) {` at line 4288 — that should have matched. But maybe an earlier match occurred at some prototype line. Let me check.
