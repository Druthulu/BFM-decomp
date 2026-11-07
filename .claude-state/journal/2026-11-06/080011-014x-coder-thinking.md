---
ts: 2026-11-06T15:00:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GDMxiZdJzdNDfOYKiPDW
---
So body file is a bare function definition (with its own externs inside). Good.

Now let me create orig.c for item 1 by extracting the function from src. The function spans lines 3019-3120 (definition), and it needs the extern decls above (3003-3016) — but those are file-scope externs that the TU already has? Actually the body file is compiled as a replacement body within the TU? Let's check delever_search.py behavior. The body is inserted... Let's check.
