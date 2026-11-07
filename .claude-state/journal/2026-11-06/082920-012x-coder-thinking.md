---
ts: 2026-11-06T15:29:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_61yqKjczDKoR8yxZ5YCO
---
Now I have item 1's body. The launder is at line 3114:
```
mp = (u8 *)D_801D0FC0;
__asm__ __volatile__("" : "=r"(mp) : "0"(mp));  // !FAKE: launder
((void(*)(void *, unsigned))func_800233CC)(mp, 0x80);
```

The function is 385 ins and currently MATCH with launder. I need a lever-free body scoring 0.

Let me check dt.sh usage and the helpers. First let me understand the tooling: bin/dt.sh <itemdir> <body> [tail].

Let me look at the worked example notes to understand the workflow. Read .run/P40/T10/func_80181F4C/notes.md.
