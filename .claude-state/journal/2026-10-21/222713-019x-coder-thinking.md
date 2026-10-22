---
ts: 2026-10-22T04:27:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CQBTSlfoJgRMFlgNIQXL
---
Many includers. The header item: MATCH requires score 0 on every includer. But wait — the function body is identical in each includer, so the compiled code should be identical... unless the surrounding TU affects register allocation (e.g. different calling context). Actually within one TU, the function is compiled with the same flags, so identical. But the tryinc.py helper exists for header items where multiple includers might have differing code (e.g., inlining contexts or different surrounding functions). Hmm, for a static function? If the function is static and only used in some TUs, gcc might optimize differently.

Let me check the header: is the function static or extern?

Let me read the header file fully (small).
