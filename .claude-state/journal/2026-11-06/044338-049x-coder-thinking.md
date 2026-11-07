---
ts: 2026-11-06T11:43:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PAfHHlM53DxRE9rK1XGF
---
MATCH! Score 0. The lever-free body with separate temps + do-while splits scores 0.

Let me verify the kinds are gone: no pins, no barrier. Yes: no `register`/`__asm__`, no barrier. `do{}while(0)` with the marker — allowed.

Now I need to check it scores 0 on EVERY includer (header item). The sc.sh only checks the primary includer? Actually delever_search --try for a header: does it check all includers? The MATCH line said "score 0 (OTHER...)" — but the brief says "header item (src/shared/ov/*.h): MATCH only if score 0 on every includer (tryinc.py k = 0..n-1)".

Let me check with tryinc.py. Usage: `.run/P40/T10/tryinc.py <k> <header> <fn> <body>`. Let me check its help/first lines.

Also, --try might already check all includers. Let me check the output more fully: dt.sh prints tail 2. Let me run the full --try to see if it reports "0 on N/N includers".

Let me run delever_search --try directly with more output.
