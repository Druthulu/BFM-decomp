---
ts: 2026-11-06T21:02:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NNMLasYmAw9W1a6GJzTw
---
cc1_dumps_tu.sh can take a .c file. I can build a minimal TU containing just the function + declarations, then dump. But delever_search --try --keep probably already creates a scratch TU. Let me try --keep and look.

Actually simpler: for item 1, the TU is src/ov_SC01_077/ov_SC01_077_after.c (132k chars). I can create a small standalone TU in my item dir that includes the needed externs and the body, then run cc1_dumps_tu.sh on it. But the compile flags need the target struct definitions (Unkstruct_80126948). Let me check where those are defined.

Let me first just try the --keep option to see the candidate assembly.
