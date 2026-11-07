---
ts: 2026-11-06T05:15:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Az7HTHiJI0xeYXSn4kQX
---
This is a different function (the RTL is the whole TU). Let me find the func_80175820 asm. The asm at 28418 references `src/shared/../shared/ov/func_80178004.h` — a different header. So the RTL dump is the TU's. I need to locate the right asm. Let me search for the asm in the function region. The function name won't appear in RTL. Hmm.

Alternative: the .frame vars=16 mystery. Let me test with a minimal C file using cc1_dumps_tu.sh. But that tool may expect a TU with certain setup. Let me check its usage.
