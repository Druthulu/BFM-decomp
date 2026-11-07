---
ts: 2026-11-06T08:54:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GYWqaOxQYbz9aUTzTNIv
---
Item 2 done at 01:54 (started ~01:41, 13 min). Now item 3: func_8017DC10 (ov_SC02_021), keepalive asm at line 3235:
`__asm__ __volatile__ ("" :: "r"((a[2] - z) * buf[5]));`
in the first if-block, after `func_8017E410(mode1, buf);`.

Note the kinds file says only "keepalive" — the pins ($4 idx, $4 otp) are "levers of other kinds the def already had" and may stay.

FRESH: copy src to orig.c, extract body. The body spans 3177-3348 (172 lines). Let me extract with sed.

Then score orig, then remove the asm and see the residual.

Start time: 01:54.
