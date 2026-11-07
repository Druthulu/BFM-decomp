---
ts: 2026-11-06T05:25:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8dCyAwwmch5ZJcXiY9Wu
---
No outputs. The memory clobber is created later. Let me find where `(clobber (mem:BLK (scratch)))` is created in stmt.c: search "scratch". Earlier grep of stmt.c for "scratch" gave nothing except line 669? Let me grep again for "SCRATCH" case-insensitively.
