---
ts: 2026-11-06T13:22:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4HpCWxBTZZ7dyQ4GAuzG
---
Wait, v08 duplicates `aa = ...` because the block I split starts at `nn = (s32)buf;` — the `aa = (s32)(q+1);` line is BEFORE the block, so v08 would duplicate aa. Let me fix v08 to only re-wrap nn... Actually the do-while needs to include aa too; but aa is already before. Let me just change v08 to wrap nn only (same as v04). Remove v08 or make it "dw around aa+nn" by splitting earlier. Simpler: drop v08.

Also v09 moves nn after the store — that changes order; target has nn early, so unlikely, but tests the sink direction.

Let me edit v08 out.
