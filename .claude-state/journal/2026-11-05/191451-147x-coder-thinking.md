---
ts: 2026-11-06T02:14:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XhvJ3qZOQMlapppmXYZb
---
PATTERN code = 41. SET_SRC (fld[1] of PATTERN, offset 4) = 0x82d998c with code 51. Hmm, SET_SRC = 0x82d998c is a static address (binary data), code 51 = ? Let me map codes: 41, 51. Using rtx_name: let me print indices 41 and 51. Also, PATTERN's fld[0] (SET_DEST) at offset 8 = 0x89601ec.

Wait, SET_SRC = 0x82d998c looks like a constant object (e.g., const0_rtx / pc_rtx / a shared rtx in .data). code 51 might be LABEL_REF? Let me check rtx_name[51] and [41].

Actually — code 41 for the PATTERN means it's not SET (SET is a code ~23?). Let me query.
