---
ts: 2026-11-06T01:29:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6pRuJ5PdZASlY9foM5xy
---
Interesting: the worked example uses a do{}while(0) as a real-C lever (with !FAKE comment presumably). OK.

Now for our item: barrier kind. The barrier is `__asm__ __volatile__("")`. We must remove it and use real C to prevent cross-jump. Options: reorder statements in the zero block; or make stores differ.

Let me get the target asm. Use tools/delever_search --explain TU FN? That reads residual. Or check build/ object disassembly. Let's see the "tgt" file in worked example.
