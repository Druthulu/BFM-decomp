---
ts: 2026-11-06T10:04:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zZopBK8DQ0DlOBF1WxFP
---
The line 230 is in "Function func_800CCBC0", not func_800CD314! My sed -n '225,240p' shows the header at line 227. So alloc_table's section extraction for func_800CD314 is finding a different section, or these numbers came from the lreg dump (which has "Register 74 used 4 times...").

Actually the alloc_table output line said ".greg order: 72 74 76 77 73" — a 5-reg order. So the order line it used is elsewhere. Let me find the func_800CD314 section in greg and its order line.
