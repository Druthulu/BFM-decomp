---
ts: 2026-10-22T12:05:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_LFYMPFQ6wbxt2tutwzRm
---
`CAST_WIDTH(T, p, k) = (*(T *)((p) + (k)))` — so `CAST_WIDTH(s32, e, 4)` = `*(s32 *)(e + 4)` where e is an s32 used as a pointer. OK.

Let me see the struct's unk20 type.
