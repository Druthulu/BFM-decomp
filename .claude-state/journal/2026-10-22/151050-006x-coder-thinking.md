---
ts: 2026-10-22T21:10:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FdleozJ19hyTWBHHaYoO
---
These four funcs are new. Let me look at the header defs in src. First, check whether orig.c already exists — no, item dirs have only fn/kinds/tu. So I need to copy the def from src.

Let me look at the header files. Each is a header item (src/shared/ov/*.h), so MATCH requires score 0 on every includer (tryinc.py k=0..n-1).

Wait — the "CHANGE" says "write a lever-free body of `func` in G16x/<dir>/win.c (bare definition)". For header items, need to check every includer.

Let me look at the defs.
