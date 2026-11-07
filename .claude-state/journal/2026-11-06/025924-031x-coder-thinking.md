---
ts: 2026-11-06T09:59:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4FuvHf3EjCOmLLZWB6Lc
---
Good. Note the first item's orig.c was extracted earlier with sed 4999,5034 — verify it's current (FRESH check: diff against src). I'll do that at item start.

Now let me baseline the three and get target disassembly for each. Let me use --keep and objdump. I'll do them one at a time but batch commands.

Actually, let me first baseline scores.
