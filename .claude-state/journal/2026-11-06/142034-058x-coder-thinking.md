---
ts: 2026-11-06T21:20:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ryU6yejpQvqfJPTM78oZ
---
136 includers! MATCH requires score 0 on every includer. That's 136 compiles. The header item is expensive. Let me check how the scoring works: `tryinc.py k header fn body` rotates the includer list and takes the first (r[k]). But `--try` scores one includer. To check all, I'd run k=0..135 — 136 runs.

Hmm, maybe delever_search --try on a header scores the first includer only. The brief says "header item (src/shared/ov/*.h): MATCH only if score 0 on every includer (tryinc.py k = 0..n-1)". So I must run all 136. Each run ~ a few seconds (the objdump is 35 ms on the largest object, but the compile may take a second). 136 × ~2s ≈ 5 min. Doable but let me first find a body that scores 0 on includer 0.

Let me write the candidate (keepalive removed, pin kept) and score with tryinc.py k=0.

Note the header file itself contains the function definition (a shared body instantiated by #include). The `--body` mode replaces the function body within the header.

Let me test.
