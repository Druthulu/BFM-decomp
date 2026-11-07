---
ts: 2026-11-06T15:09:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_W4g2XXFkJIITfs51Eivf
---
c1.c is only 4611 bytes while orig.c is 4695. The function body is ~100 lines ≈ 4600 bytes. But sed 3103-3115 gave nothing since c1.c has only ~100 lines. Right, c1.c is a bare body (100 lines), not the whole TU. My sed range 3103 was out of range. Duh.

So tu_c1.c is the spliced TU — let me check its vol region again; it showed `vol = vol & 0xFFFF` which is b4. That means tu_c1.c is stale (from the b4 run). So command A's c1 --keep must have failed. Why? Let me check c1.c content around the vol line.
