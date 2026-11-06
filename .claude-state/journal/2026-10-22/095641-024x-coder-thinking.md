---
ts: 2026-10-22T15:56:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3wscduIMUK8bKZgpOp7J
---
func_80128158.h is a *different function*. So the TU ov_MAIN_012.c includes many headers; my dumped func_8012B4B8 region should be from the copy at... but the TU includes "../shared/ov/func_80128158.h" etc. Does it include func_8012B4B8.h? Let me grep the TU for 8012B4B8.

Wait, the cse2 dump's "Function func_8012B4B8" region showed the launder. Maybe the TU includes the *original* src/shared/ov/func_8012B4B8.h (via -Isrc/shared resolving `../shared/ov/...` relative to the p6 dir? No: the .c is in p6, `../shared/ov/func_80128158.h` = p6/../shared/ov/... = .run/P36/engine/score/.../shared/ov/ — the scratch's shared dir, which has my body at func_8012B4B8.h. But the TU doesn't include func_8012B4B8.h? Let me grep.
