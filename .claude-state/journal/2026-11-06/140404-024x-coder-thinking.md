---
ts: 2026-11-06T21:04:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iMaeIagAiQBtRFyrmZHZ
---
Confirmed: andi $16 (s0) directly. So `a`'s pin didn't survive; the pseudo merged.

Now let me find where the merge happens. Compare the .rtl dumps of orig vs w1 around the ang assignment. Actually, the pin `register asm("$4")` — in orig, `a` is (reg $4); in w1, is it still (reg $4)? Let's grep the rtl dump for "reg:SI 4" or the variable. The .rtl dump is big; let me look at the .combine and .cse. Better: compare the two .rtl files' first function.

Actually, let me check: in w1, does the andi write (reg:SI 4) and then copy to ang, and later combine folds? Let me grep the combine dump for "andi" or "0xfff".

Let me look at the flow dump (after combine) or the cse dump. Let's grep w1.i.combine for "0xfff" with context.

Hmm, the dump files are large. Let me grep.
