---
ts: 2026-11-06T09:12:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p9IvqrC5jqona0igGsFL
---
Item 4: explicit note says "the function RETURNS the slot (`void *` signature, expand_value_return stmt.c:2505; the TU's extern is `void`)". So a return of a value from void fn — expand_value_return may keep it in v0 if there's a `return;` at the end? Interesting: the note says the function returns the slot via v0. If we write `return (void*)base;` in a void fn, GCC drops. But `expand_value_return` at stmt.c:2505... maybe a void function with a value return does keep the value in v0 in GCC 2.7.2? Our c3.c test dropped it though (score 19, 49 ins). Hmm, but in c3 the `return found;` was the last statement after the loop; GCC warned "return with a value"? It compiled. Did it emit? Score 19 vs 49 ins — no value kept.

Wait, maybe GCC's expand_return for void function emits the value into v0 anyway if the expression has side effects? No.

Hmm, so how did the original author get v0 without the pin? They wrote the pin because the TU extern is void. This is the same wall as func_800CD494 in this same overlay? No, different.

Let me check moves.md for func_80180A54.
