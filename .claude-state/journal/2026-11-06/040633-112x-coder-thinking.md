---
ts: 2026-11-06T11:06:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WwHeg1zJ4h2RsNfezMU0
---
Item 4 behaves exactly like item 3: v_sa (struct alias + n as s16) = 4, same delay-slot diff.

So item 4 is the same wall. I need 30 tries on item 4. Let me run the same variant batches (x_, y_, z_) adapted to item 4. The calls differ (func_8018B478 instead of the cast). Let me write a generator quickly, reusing the structure.

The loop in item 4:
```
        do {
            if (D_80115158[i].h != 0) {
                __asm__("");
                ot = func_8018B478(ot, w, i);
            }
            i++;
            w++;
        } while (i < cnt);
```
And the n block:
```
    if (D_80115126 == 3) {
        if (D_8011511A == 3) {
            ot = func_8018B478(ot, &D_801C1568, 3);
            n = 3;
        } else { n = 4; }
    } else { n = 3; }
```
Wait, in item 4 the call is `ot = func_8018B478(ot, &D_801C1568, 3);` (declared as returning s32*).

Let me generate the same batch: x_ (loop variants), y_ (loop shapes), z_ (orders). Since the structure is the same, I can adapt with sed: replace the call text.

Let me write a generator that takes v_sa.c and applies the same transformations with the item-4 call text.
