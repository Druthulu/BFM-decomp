---
ts: 2026-10-22T21:47:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TVKKrCqsMl9aGiJH5Xz7
---
Byte-identical, 32 ins. Now add the `// !FAKE: do-while` marker and re-verify (the comment shouldn't change codegen, but re-score). Then all includers.

Let me check the includer count for func_80177F84.h — my allinc.sh hardcodes 141. Let me count includers for this header: grep -rl gave at least 4. Let me count.
