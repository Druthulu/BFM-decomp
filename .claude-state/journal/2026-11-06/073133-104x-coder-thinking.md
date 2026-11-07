---
ts: 2026-11-06T14:31:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OZMcwXu4frph1e3Lx74R
---
Now the next two items:
4. func_8017EB30 (ov_SC01_004) — launder, 200
5. func_80183130 (ov_SC04_004) — keepalive, 0

Let me start with func_80183130 (keepalive) since it's the same kind and might be similar. Actually, let me do them in list order: func_8017EB30 (launder) then func_80183130 (keepalive). The order doesn't matter much. Let me do func_80183130 first since it's keepalive (recent context).

Actually, let me follow the list order to be systematic: func_8017EB30 (launder) is next. Hmm, but the launder item is a different beast. Let me check the time: it's ~07:55 now. I have 2 items left. Let me budget ~25 min each.

Let me start with func_80183130 (keepalive) — the same kind, and I have fresh context on the global-alloc mechanism. Then func_8017EB30 (launder).

Wait, the list order is:
1. SC01_084 keepalive ✓
2. SC02_005 keepalive ✓
3. SC04_004 keepalive (func_80183130, score 0)
4. SC05_008 keepalive ✓
5. SC01_004 launder (func_8017EB30, score 200)

Let me do item 3 (func_80183130) next.

Let me read the item: fn func_80183130, tu src/ov_SC04_004/ov_SC04_004_jr_8017AE2C.c, kinds keepalive.

Let me locate and extract the function, check the baseline, and grep moves.md for the function.
