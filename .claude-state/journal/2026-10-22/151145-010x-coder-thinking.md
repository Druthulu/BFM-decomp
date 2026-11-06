---
ts: 2026-10-22T21:11:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_r6K33ChgbdAI6bugx4Ht
---
Interesting: dropping the launder line entirely still scores 0. Wait — nopin.c removed line 14 which is the asm line inside the block. So the body becomes:

```
{
    void *q = &sp18;
    ((void (*)(s32, void*, void*))func_8012F14C)(*(s32*)(arg0 + 0x20) + 0x34, &sp10, q);
}
```
And it still matches at 23 ins. 

But wait — for header items MATCH requires score 0 on every includer. dt.sh scores the header's... how does it pick includers? The score line says "the bank judges the whole object". tryinc.py k rotates includers. Let me check how many includers exist and whether the plain dt.sh already checks all.

Let me check delever_search's recs_for and whether the default tries all includers. The dt.sh output shows one line only. Let me test all includers with tryinc.py.

First get the count of includers.
