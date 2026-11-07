---
ts: 2026-11-06T06:01:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_13Mf6aPXyE8ypcI4JL6q
---
The .run/P36/engine/score/ dirs — there are many per includer (from tryinc runs). The tool normally deletes them but --keep left some. The check_all runs used tryinc without --keep, so those should be cleaned automatically. The ones remaining are from my --keep calls (ov_MAIN_012__func_80150170, ov_MAIN_012__func_80175820, ov_MAIN_012__func_801758FC, ov_MAIN_012__func_801759D8, ov_SC04_018__func_80180D38). But I see ov_SC01_000__func_80150170 etc. — those are from the tryinc check_all runs? Without --keep, the tool should delete them. Hmm, maybe it leaves the per-call dirs. Let me check their size and remove the ones for my functions.

Wait — these are in .run/P36/engine/score/, which is the shared delever_search scratch. The brief says "--keep scratch is removed after use". Since these are my runs' scratch, let me remove the specific dirs for my 5 functions. But other shards might use the same engine dir concurrently. Removing dirs named `<tu>__<fn>` for my functions is safe.

Let me check the size first and then remove explicitly by name.
