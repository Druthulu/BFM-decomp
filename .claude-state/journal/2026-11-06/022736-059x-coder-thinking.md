---
ts: 2026-11-06T09:27:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B7msXNTxhlmvd0TTo2IW
---
This alloc table is for the whole function; I need the fc/limit pseudos. fc is a register var pinned to $5 (a1) — the hard reg. In the .lreg dump, register variables show as `r?? a1`? Let me grep for a1/v1 rows with blk 15 (the first branch's block is 15?). Also the table is the *global* alloc table (greg) plus local. Let me grep the alloc file for 'a1' and 'a0' rows.

Actually this is getting deep. Time 02:29. Let me check the remaining rows mentioning "2 bytes" (s16 loads) — r137/r149 pri 7500, 2 bytes, conflicts v0,v1 — these are the limit loads? And fc (register var) doesn't appear in the greg order... The register variable fc pinned to a1 is a local reg; in .lreg it'd be `r?? a1`.

Let me grep the alloc file for a1.
