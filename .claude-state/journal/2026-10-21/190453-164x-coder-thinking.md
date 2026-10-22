---
ts: 2026-10-22T01:04:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_1WqK63rCvpGuriWXndbG
---
The difference: in z8 the do-while comes BEFORE the re-computation; in ysame it comes AFTER (the do-while is inserted at the asm's position, which is after the original assignment... wait).

Hmm, in ysame: the else branch is:
```
                diff = sum - *(s16 *)(s1 + 0xA);     <- the original assignment
        do { } while (0);                            <- at the asm's position
                diff = sum - *(s16 *)(s1 + 0xA);     <- the re-computation
```
Hmm, and z8:
```
                diff = sum - *(s16 *)(s1 + 0xA);
                do { } while (0);
                diff = sum - *(s16 *)(s1 + 0xA);
```
The same order! The diff shows z8 has the do-while at line 36-37 and ysame at 37-38 — the *line numbers* differ but the content order looks the same...

Hmm, the diff says: lines 36-37 in z8 (do-while + the if-branch re-computation) are *deleted*, and after line 38 in ysame, the do-while + re-computation are *added*. So in ysame the do-while comes AFTER `if (diff < 0x10) {`?? Let me look at the actual files.

Let me print the relevant region of ysame.c.
