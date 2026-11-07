---
ts: 2026-11-06T04:44:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_08u9ai7g33SHIbWyVe14
---
The function func_8014A59C is in the header included by a member at slot 0x80128158. The bank/object name might be ov_MAIN_012__func_8014A59C. Let me find the object in build with that name.

Actually delever_search's scratch path was .run/P36/engine/score/ov_MAIN_012__func_8014A59C/. The target probably is build/src/ov_MAIN_012/ov_MAIN_012__func_8014A59C.o? Let me check.

Also for disassembly, maybe there's a mips toolchain objdump. Let me check how delever_search disassembles: grep for "objdump" in tools/delever_search.py.
