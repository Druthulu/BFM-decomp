---
ts: 2026-11-06T15:18:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IT7dLZxdq5oxH15UchLA
---
All 5 MATCH. 

Wait — that output came from a command where the first `D=...` line was missing? No, I had `D=.run/...` first. Yes it's there.

Hmm, but the output didn't echo the D assignment (correct).

Now:
1. Append results rows for items 2-5.
2. Append moves.md lines for items 2-5.
3. Write notes.md for items 2-5.
4. Verify each win.c has no launder asm (only pins) — let me check each.
5. Clean up scratch: the --keep scratch dir .run/P36/engine/score/ov_SC03_099__func_801806D8 (created by the tool; brief says `--keep` scratch is removed after use). I should remove it.
6. Check shard size < 200 MB.

Also FRESH: I diffed orig.c only against the item-1 orig; the rule says diff <dir>/orig.c against the def in the current src — I extracted fresh from src for each, and the control scored 0 each time, which confirms the current src def. Good.

Let me verify each win.c's asm lines and diff win.c vs orig.c to confirm the only changes are the launder removal + the vol line.

Let me do a compact check for all 5.
