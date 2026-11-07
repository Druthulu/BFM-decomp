---
ts: 2026-11-06T20:47:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dDO2Fqtb4YvsKNNJfdZv
---
No ov_SC04_011_shared.h. The TU includes "common.h" and "../shared/engine_prelude.h". "common.h" is found via -Isrc (tools/cc1_dumps_tu.sh adds -Isrc). So the splice should work directly. Let me dump.
