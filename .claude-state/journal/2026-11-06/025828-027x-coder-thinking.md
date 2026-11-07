---
ts: 2026-11-06T09:58:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EzDoYWNpGePQthSVexGH
---
That's a different function (same TU file but different address). Not helpful.

Let me search for the exact body in the sibling TUs — the comment says declarations were conformed to ov_SC02_035_jr_8017BEBC.c:5139 and :5117. Those lines are `extern void func_8017E8D8(...)`? Wait line 5139 area shows func_80180C10. Hmm the line numbers don't match (maybe file changed). Whatever.

Let me take a different approach: check if there's another overlay TU that contains the *same* function body (the "jr" functions are shared code compiled into multiple overlays). Search src for the distinctive line `CAST_WIDTH(s32, a1, 0xE0) = 1;` or `D_80126CBA`.
