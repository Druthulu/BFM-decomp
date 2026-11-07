---
ts: 2026-11-07T00:01:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K23JQ55D95a4b35JthkH
---
Now item 2: func_8012DBD0 header. Levers: 3 pins (param_3 $21, param_4 $19, t $2) and 1 launder (iVar4).

This is a header item: MATCH requires score 0 on EVERY includer (tryinc.py k = 0..n-1). How many includers? 89 in the list.tsv (last column). Let me check what that number means: list.tsv has columns `dir file func kinds lines` — the last is 4, 89, 41, 34. Hmm, maybe "lines" is the function's line count in the header? For item 1, resident.c's function is 85 lines. Hmm, no.

Wait: list.tsv row: `func_800CFE60__resident  src/resident/resident.c  func_800CFE60  launder,pin  4`. Hmm, 4? The function is 85 lines. Maybe the last column is something else. For headers: 89, 41, 34. The header func_8012DBD0.h is 92 lines. Hmm.

Actually, maybe the last column is the number of... hmm. Let me check tryinc.py: `recs_for(tu, ...)` returns the includers. The number 89 might be the number of includers for func_8012DBD0. And 4 for func_800CFE60? resident.c is a TU, maybe "4" is... hmm.

Wait, for the resident TU, delever_search --try src/resident/resident.c — the "recs" are the recipes/includers. For a normal TU there's 1. Hmm.

Let me not worry; the interface says header items need score 0 on every includer via tryinc.py k=0..n-1.

First, let me establish the baseline: remove the pins and launder from the header body and score it.

Let me look at how to handle the header: the file src/shared/ov/func_8012DBD0.h contains the function definition. The "body" for --body is the function definition. For headers, tryinc.py uses the header as the TU and the k-th includer.

Let me check tryinc.py's usage: `tryinc.py <k> <header> <fn> <body.c>` → sys.argv = ["delever_search.py","--try"] + sys.argv[2:5] + ["--body"] = ["--try", header, fn, body, "--body"]. So it passes the header path as the TU and the body file.

So: `/usr/bin/python3 .run/P40/T10/tryinc.py 0 src/shared/ov/func_8012DBD0.h func_8012DBD0 win.c`.

Let me first create orig.c for item 2 (the function definition from the header) and a lever-free win.c.

The function definition in the header is lines 6-92 (from `s32 func_8012DBD0(...)` to the closing `}`). The externs at the top are outside the function. The body file should be just the definition.

Let me extract lines 6-92.

Let me check the header line count and extract.
