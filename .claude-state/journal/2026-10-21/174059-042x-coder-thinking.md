---
ts: 2026-10-21T23:40:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mxLqUBzBIjbmhUpDcJ1Z
---
`include/common.h` defines s32. So my scratch TU can `#include "common.h"` (with -Iinclude). Let me check the includer TU's head to replicate its include set.

Let me look at src/ov_SC03_099/ov_SC03_099_jr_80140608.c head.
