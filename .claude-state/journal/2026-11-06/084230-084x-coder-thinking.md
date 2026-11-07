---
ts: 2026-11-06T15:42:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JlLAIrWoW7mM0mxdkH7w
---
Hmm, `grep -c launder` on orig_tu.c = 1 and a1_tu.c = 0. But orig_tu.c should have the launder line (1) — good. But wait, the a1 TU was copied from p5 which was the last --keep (a1). Good.

But careful: the orig_tu.c copy used `ls -td p* | head -1` which might be the a1 p5 dir (just modified). The --try orig ran after, creating a new p dir (p6?) with a newer mtime. `ls -td` sorts by mtime, so the newest is the orig run's dir. OK.

Now dump both.
