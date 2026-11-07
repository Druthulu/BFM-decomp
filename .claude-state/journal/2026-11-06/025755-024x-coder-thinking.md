---
ts: 2026-11-06T09:57:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nyRKybMsDIDoHW5OAFnW
---
As expected, GCC discards the value in a void function. So we must change the return type.

Now let me check whether changing the definition to `s32` while callers declare `extern void` compiles and scores 0. Test with w3.c.
