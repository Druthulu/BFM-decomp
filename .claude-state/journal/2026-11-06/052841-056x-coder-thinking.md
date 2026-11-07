---
ts: 2026-11-06T12:28:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sipFhzCZ5zrfka69iS1p
---
orig scores 0. Now try stripping each lever.

Variant s1: remove the keepalive (line 4100).
Variant s2: remove the barrier at 4103.
Variant s3: remove the memory barrier at 4119.
Variant s4: remove the pin (zr) → replace `n + zr` with `n`, `cnt + zr` with `cnt`.
Variant s5: all removed (full lever-free attempt with plain C).

Let me construct with sed. The zr removal: `cnt = n + zr;` → `cnt = n;`; `lim = cnt + zr;` → `lim = cnt;`; remove the zr decl.

Let me do each individually and score.
