---
ts: 2026-11-06T16:49:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J2IPp6M8BAJXl2Gbd3jB
---
gte_SetRotMatrix is a macro in include/gte_inline.h. The .i doesn't contain it because cpp didn't process it? `grep gte_SetRotMatrix t.i` found nothing — meaning the macro was expanded (its body has no such name) or the include wasn't found. Let me check the .i around the function start to see whether the macro expanded.

Actually if the macro were expanded, we'd see ctc2 in the .i. Let me grep for ctc2 or the macro body.
