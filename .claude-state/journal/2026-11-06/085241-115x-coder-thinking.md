---
ts: 2026-11-06T15:52:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K1dRjIsDheFhy48mCoD9
---
All 5 win.c score 0 after cleanup. 

Wait — I deleted the a7_tu.c etc. but those were copies. Fine.

Now, one concern: the final re-verify used --try without --keep, so the scratch dirs were cleaned by the tool. Good.

Now write notes.md for each item dir. Let me create them.

Also I should double check the FRESH requirement: each orig.c was extracted from the current src at item start (extract.py reads the src file fresh; item 4 via sed from the current src). And I didn't modify src. Good.

Let me write notes.md files with a script.
