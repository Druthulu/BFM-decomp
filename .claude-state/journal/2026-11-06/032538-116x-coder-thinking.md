---
ts: 2026-11-06T10:25:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Zb4nHPbIhykHYH25AHSe
---
No improvement. f1/k1/k4 = score 5.

Let me make a final decision on item 3: WALL, best 5, tries ~34.

Now item 4. Let me look at it quickly. And item 2 needs more tries. And item 1 needs 30 tries.

Actually, wait. Let me reconsider whether I can crack item 3's keepalive by a real C construct. The keepalive anchors ang. What real C use of ang comes after `ang = ang - 0x400` and before the a-mask? `cur = ang & 0xFFF`. In the target, cur's andi is AFTER the a-mask. So ang's use (cur) is after the a-mask. That doesn't anchor ang before the a-mask.

Hmm, but the keepalive is between `ang = ang - 0x400` and `div = (s16)div`. It anchors ang right there. Without it, sched1 reorders.

What if I compute something from ang before the div sign-ext? E.g., `cur = ang & 0xFFF;` moved before the div sign-ext:
```
ang = ang - 0x400;
cur = ang & 0xFFF;
div = (s16)div;
a = a & 0xFFF;
```
Then the order would be ang, cur-andi, div-sll, a-andi. Target is ang, div-sll, a-andi, cur-andi. So no.

Hmm.

OK, item 3 wall. Let me move to item 4.

Item 4: src/shared/ov/func_801535F4.h. Let me look at the residual.
