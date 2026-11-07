---
ts: 2026-11-06T16:57:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_upmQMDupzM2CigfCA2LI
---
Now write notes.md for each item dir and the log. Let me also clean up the dumps (the brief says cc1 dumps go under the item dir and are deleted as soon as read). I have:
- .run/P40/T11/W47x/func_800CB118__md_MAIN_041/dumps (dumps_base, dumps_r16)
- .run/P40/T11/W47x/func_8017E9A0.../dumps (dumps_base)
And the --keep scratch: .run/P36/engine/score/md_MAIN_041__func_800CB118/p3, .run/P36/engine/score/ov_SC03_112__func_8017E9A0/p3. I should remove those scratch dirs (the brief says --keep scratch is removed after use).

Also there are many candidate files in the item dirs (w*.c) — fine, they're small. But the shard dir must stay < 200 MB. The dumps are the big ones. Let me delete them.

Wait, before deleting, do I need any evidence? I have the mechanism. Delete.

Let me write notes.md for each item, then the log.

Item 1 notes:
- fresh: orig.c matches current src (checked at start, diff clean).
- kinds: pin. Lever-free = both $2/$3 pins removed.
- Tried 43 bodies; best 7 (u16 ret + zero-extend pseudo). SImode bodies all 8 (missing move v1,v0).
- Wall: lreg-callresult-copy-pref.

Item 2 notes:
- fresh: orig.c matches src.
- kinds: launder. Removed the asm launder; kept $4/$5 pins (not row kind).
- Twin func_8017DE00 in ov_SC02_039: a0 = s0 << 10 as loop head, no trailing copy, no launder → MATCH 0.

Item 3 notes:
- fresh: orig.c matches src.
- kinds: pin ($3 h). Removed pin.
- best 2 (r1 reassociation). Wall lreg-qty-priority.

Let me write these.
