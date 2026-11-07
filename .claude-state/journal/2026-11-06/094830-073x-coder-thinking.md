---
ts: 2026-11-06T16:48:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_73NppThPTet3WrZW0UNs
---
No shared header for this overlay; the TU only includes common.h and ../shared/engine_prelude.h. So I can place t.c anywhere with a `shared` symlink one level up. Put it at $D/dumptu/ov_SC07_006/t.c and $D/dumptu/shared -> src/shared. Good.
