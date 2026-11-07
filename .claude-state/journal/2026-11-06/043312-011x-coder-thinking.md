---
ts: 2026-11-06T11:33:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XKDYmPnXVSwuBGFma3MH
---
Now I understand the four items. I need to write lever-free bodies scoring 0. This is the "singleton crack" shard: for each item, remove the barrier/launder levers and find real C that reproduces the target. The item's kinds are barrier,launder; if I can get a lever-free body to score 0, MATCH. Otherwise WALL with best score of a lever-free body. Also PARTIAL if the win.c scores 0 keeping only some kinds.

Let me start with the first item, func_80015B6C. First copy orig.c from src (fresh diff). The brief says copy to <dir>/orig.c. Let me create the working bodies.

Approach for func_80015B6C: it's a GPU packet builder. The barriers/launders control ordering. Real C moves: temps, decl order, statement order etc.

Let me set up dir files. First copy orig.c. I'll write a small script? Use sed to extract line ranges. But the body needs the surrounding externs? dt.sh uses delever_search --try TU fn file --body, which presumably compiles the body with the TU context? Let me check how delever_search works — worked example .run/P40/T10/func_80181F4C/ has notes.md, win.c. Let me look at a win.c and notes to understand format (bare definition).
