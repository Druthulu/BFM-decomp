---
ts: 2026-11-07T00:54:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1PjKN3BvAZw0YWeNqyAk
---
OK. For header TU, --try splices the body into the raw header and then compiles the header's first recipe (recs[0]). With tryinc rotation we rotate recipes.

Let me check recs_for and how many includers. Let's just calibrate.

Write orig.c files first.

Item 1 orig.c: copy header body lines. Note the header body starts with `extern s32 func_80029504(void);` then function. Body file replaces just the function definition span (body_span of fn). So body file must be just the function definition, without the extern (the extern stays in the TU above).

Item 2 orig.c: just the function definition (no externs needed).

Let me write them.
