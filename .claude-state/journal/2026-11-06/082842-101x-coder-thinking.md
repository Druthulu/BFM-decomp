---
ts: 2026-11-06T15:28:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QwTZXQDHN9Ycn1OeSMsa
---
Now write A1: replace line 88 (the comment was on the removed asm line? Actually the launder line was line 88 originally: `__asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder`. The sed removed that line, leaving the comment "/* lever 3: ... */" on line 88? Wait, the comment at 88 in nolaunder.c is "/* lever 3: sched1 otherwise hoists the PAN multiply ahead of this one */". In orig.c, line 6629 was that comment and 6630 was the asm. Let me check orig.c lines 87-89.

Actually in orig.c (from the earlier Read of src): 
```
6628            vol = ((0xA0 - av) * 0x7F) / 0xA0;
6629            /* lever 3: sched1 otherwise hoists the PAN multiply ahead of this one */
6630            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_tus2)
6631            sx = (sx + 0xA0) / 0x14;
```
So nolaunder.c line 87 = vol=..., 88 = comment, 89 = sx=...

Good. Now A1: insert after the vol line:
```
            vol = vol | 0x3000;
```
and change the call arg to `(vol | sx) & 0xFFFF`.

Let me create it.
