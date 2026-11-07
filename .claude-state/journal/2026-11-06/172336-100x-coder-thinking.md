---
ts: 2026-11-07T00:23:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RjfM0MhD9cBCsgGcULav
---
All four win.c scores match the recorded best values.

Now let me write the log file `phase-ends/current/logs/T11.cG23x.md` with the timeline per item, moves that cracked, walls with evidence.

Note: I must not read phase-ends/current/logs/ bodies, but writing my own log is required.

Let me write it with:
- start/end time, minutes, tries per item
- moves that cracked (none)
- walls with evidence
- friction (the refused `../shared/...` path argument)

Timeline:
- Item 1 func_800CFE60 (resident.c): 16:44 → 17:01 (17 min), 47 tries. WALL global-pri-bank-order, best 14. Launder side cracked lever-free by `*q = val; p = q;` (store-before-copy) giving the target's 161-insn shape; remaining is the $s3/$s4 swap (base pri 1518 > mode 1204).
- Item 2 func_8012DBD0 (header): 17:01 → 17:09 (9 min), 58 tries (45 at decision + 13 after). WALL cse-copy-merge, best 31.
- Item 3 func_80136F3C (header): 17:10 → 17:15 (5 min), 122 tries. WALL lreg-qty-priority, best 22.
- Item 4 func_80188790 (header): 17:15 → ~17:35, 40 tries. WALL cse-const-addr, best 22.

Let me get the actual end time.

Also, the log should record the commands run and results. Let me write it.

Also, I should clean up: the shard dir must stay < 200 MB. Let me check the size. And the brief says cc1 dumps go under the item dir and are deleted (rm -rf that dump dir) as soon as I've read them. I have dumps_gno, dumps_w0, dumps_wo, dumps_x7, dumps_p14, dumps_wno etc. Let me delete them.

Also `--keep` scratch was removed after use (delever_search removes it unless --keep; I used --keep once for item 2's nolau, which printed .run/P36/engine/score/... — that's outside my shard but it's the tool's own scratch dir. The brief says "`--keep` scratch is removed after use". Let me remove that dir).

Let me first get the time and write the log, then clean up.

Let me check the shard size and the dump dirs.
