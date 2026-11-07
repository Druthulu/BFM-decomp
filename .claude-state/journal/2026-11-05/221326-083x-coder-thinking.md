---
ts: 2026-11-06T05:13:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GRMpE3pQnqrJSMkgUd1T
---
The cse dump shows `(mem:HI (symbol_ref:SI ("D_80078EA6")))` — identical in both. So the cast did NOT change the MEM expression at cse time. Then why did u3 have 114 ins vs u2's 111?

Maybe the difference is in a pass BEFORE cse (e.g., the tree-level or expand), or the cast changed the *flow* pass's alias analysis.

Hmm, wait: maybe the cast changed the RTL *before* cse such that the two loads are in different basic blocks (e.g., the cast expression created a different insn order).

Let me diff the .cse dumps of u2 and u3. Let me generate u2's dump and diff.

Actually, a simpler test: the u3 body has `(s16)*(s16 *)&D_80078EA6`. What if the difference is that this expression is not recognized as a *constant-address* load and uses a different expansion... but the output insn count matched (114).

Let me diff the .flow dumps (before cse) to see where the difference appears. Let me run hdump for u2 and diff the .flow files.
