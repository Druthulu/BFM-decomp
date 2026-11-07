---
ts: 2026-11-06T16:59:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JlxvOQUVhe7ntIVjFcmR
---
The TU has many includes; the dump setup needs the include tree. It includes "../shared/ov/...". If I place the TU at $D/dumptu/ov_SC02_031/t.c and symlink $D/dumptu/shared -> src/shared, the "../shared/ov/..." resolves. Let me set that up.

Actually, maybe I don't need the full TU dump; I can use tools/cc1_dumps.sh on a self-contained body (it prepends common.h). The body uses Unkstruct_800B5CB8, CAST_WIDTH, func_ prototypes — common.h may not have them. Risky.

Let me try the TU dump with the shared symlink.
