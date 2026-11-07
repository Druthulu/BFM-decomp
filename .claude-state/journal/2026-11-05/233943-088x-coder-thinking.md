---
ts: 2026-11-06T06:39:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IjNOXzSFaod0ATJEr2sH
---
The diff is mostly a 4-byte shift (jump targets off by 4) because of the ONE extra instruction. Plus the `addiu s0,sp,24; move a1,s0` vs `addiu a1,sp,24` at 478 — that's a different issue (the sp10/m18 address).

So c2 has one extra insn somewhere early. Let me find where the extra `sw zero` is. Let me get the first diff lines (the head of the diff).

Let me run with a big tail and head.
