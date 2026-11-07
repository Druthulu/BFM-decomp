---
ts: 2026-11-06T21:55:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ptkeErzijDJfUz641yBO
---
The shape: 
```
s16 tmp;
do {
    tmp = (s16)v;
    c = tmp;
} while (0);
```
where c is presumably s32. The whole copy pair inside a do-while. And `v` is a load (`lh`) — the source's range is unknown → the sign-extend is real.

In our case, the source is iVar2 with a known small range, so combine folds the sign-extend. But even so, if the do-while keeps the block boundary, combine can't merge the copy into the compare.

Let me test:
w6:
```
                {
                    s16 tmp;
                    do {
                        tmp = (s16)iVar2;
                        iv2c = tmp;
                    } while (0);  // !FAKE: do-while
                }
```
and w7: same without the s16 (just `do { iv2c = iVar2; } while (0);` — that's w1, failed).

Let me test w6. Also w8: `do { iv2c = (s16)iVar2; } while (0);`.

Let me create and score all three quickly with sc.sh.
