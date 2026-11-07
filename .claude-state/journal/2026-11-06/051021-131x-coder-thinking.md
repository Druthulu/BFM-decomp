---
ts: 2026-11-06T12:10:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pvFXRs315Gv2d9ggbjjB
---
All win.c scores verified:
- func_80148AFC: 0 (PARTIAL:barrier)
- func_8017BEBC: 0 (PARTIAL:barrier)
- func_8017D174: 45 (WALL)
- func_80175AB8: 38 (WALL)

Now clean the --keep scratch dirs I created. The .run/P36/engine/score dir has many dirs from other shards — I must only remove mine: ov_SC01_077__func_80148AFC, ov_SC03_103__func_8017D174, ov_SC07_006__func_80175AB8. Let me remove those three.

Careful: other coders may be using the same tool concurrently with different functions. My dirs are keyed by TU__func, so removing mine is safe.

Let me remove them.
