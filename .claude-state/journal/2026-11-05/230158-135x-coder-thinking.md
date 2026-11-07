---
ts: 2026-11-06T06:01:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uXu1gsJJxy6Ie26Oayzt
---
565 dirs for my functions, 25 MB total. The tool normally cleans per-call, but tryinc/check_all runs left them (or they're reused). 25 MB is not huge but the brief says --keep scratch removed. Since 565 dirs were created by my 141×5 checks, they may have accumulated. The tool's normal behavior deletes the scratch after each call unless --keep; but these exist, so maybe the delever_search keeps per-includer dirs intentionally (cache). Let me not delete other shards' stuff. I'll remove only the ones for my functions — they're mine. But 565 dirs... Let me check whether they're empty/cache. Actually, the p<pid> dirs inside may be removed, leaving the parent. Let me just remove the parent dirs matching my 5 function names. That's safe (they're scratch keyed by TU+function, only for my items).

Wait — careful: `ov_SC01_000__func_80175820` etc. are per-includer caches. Removing them is fine; they'd be regenerated if needed.

Let me do it explicitly with a find on the score dir restricted to those names. The TRAP warns about globs matching win.c — but that's for item dirs; here I'm removing engine scratch dirs by name. Let me use a Python script to remove exactly the dirs whose name contains one of my 5 function names. That's explicit and safe.
