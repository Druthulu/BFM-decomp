---
ts: 2026-11-06T14:59:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xHhU2y4Txk576arSmdyo
---
Now let's see the other two clones. They may be identical. Let me diff the function bodies quickly. Extract body from each file and diff.

Also need func_8017F2D4 (SC01_005) body at 2991.

Let me first check the tools and understand scoring. Run dt.sh on one item to see baseline score. But first I need to create orig.c copies. The FRESH instruction: diff <dir>/orig.c against the def in current src; orig.c doesn't exist yet (only fn, kinds, tu). So copy from src.

Let me extract the function body from src into <dir>/orig.c. What exactly does delever_search --body expect? A file containing the bare function definition. Let me check tools/delever_search.py usage and R3.40-013 helpers.
