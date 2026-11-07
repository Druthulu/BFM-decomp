---
ts: 2026-11-06T09:12:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZYlNp2YRamQW45yHQdjQ
---
Item 2: void fn, target returns res (pointer) in v0: `res = 0; ... res = &D_801F832C; ...` keepalive. The target likely has `move v0,zero` / `lui v0` for res. This is another expand-void-return style: the value in v0 must be kept. Without pin, `res` would be a local pointer assigned 0 and &D_801F832C, used only by keepalive. With keepalive-only, res gets a callee-saved reg, not v0.

Hmm, so similar wall.

Item 3: ov_SC01_000 func_8017DD04 at 3267. Let me read.
