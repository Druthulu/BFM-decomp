---
ts: 2026-11-06T06:03:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VAvi1E7syf4b7izueioH
---
The jump2 dump has no "cross" mention. Maybe cross-jump notes are only emitted with a flag, or the merge happens in jump (not jump2), or the dump text differs. Let me look at the jump2 dump around the function for "NOTE_INSN" or "deleting" messages.

Actually, in GCC 2.7.2 jump.c's cross-jumping is done in `jump_optimize` and prints "Cross jumping from..." only with `-dj`? Let me check jump.c for the message.

Let me grep jump.c in the reference for "Cross".
