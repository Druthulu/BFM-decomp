---
ts: 2026-11-06T15:19:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FZJDTPS3eeBSS35tuFuI
---
Wait, the base is nolaunder.c which still has the structure:
```
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            ...
        }
```
Yes, since nolaunder only removed the asm line, the `if (t != 3)` remains. Good.

But note: the original had `if (t == 5) {` and then the launder. So the block matches.

Let me run it.
