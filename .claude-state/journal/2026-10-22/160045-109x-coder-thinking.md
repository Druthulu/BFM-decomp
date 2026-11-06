---
ts: 2026-10-22T22:00:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qhkSreK4sm5JSPubFufa
---
The do-while is GONE from win.c! So my earlier `cp $D/u2.c $D/win.c`... wait, I never copied u2 to win.c! Let me check: after u2 scored 0, I ran dt.sh on u2.c (verified 0), then I ran the python that modified win.c (which was still the barrier-free non-do-while version). So the replacement didn't match and the file stayed the plain version, then sc.sh gave 3.

Right: win.c was never set to u2. But I deleted u2.c! Let me recreate it.

The tidied version:
```
    do {  // !FAKE: do-while
        t = D_801A9A88[a1 * 5];
        sp10[4] = t;
    } while (0);
```
Let me apply that to win.c and verify. If the comment position/indentation matters (it shouldn't), I'll revert to u2's exact text.
