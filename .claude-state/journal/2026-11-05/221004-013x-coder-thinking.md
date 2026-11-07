---
ts: 2026-11-06T05:10:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4kIH2ZTcMWXL5pV33UAl
---
Wait, careful: `__asm` might appear in strings or symbol names like `aB9A02 __asm__("D_800B9A02")`. For these 5 items, none have such alias? Let me check. The 5 headers: func_80150170 has only barriers. Others have only barriers. func_80180D38 has one barrier. So fine. But the strip script's check `'__asm' in code.replace('__asm__','')` would also catch `__asm`. Fine.

Let me run for item1.
