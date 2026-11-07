---
ts: 2026-11-06T05:21:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_62kEolgSxxNCG3v66HtF
---
The dump contains many functions (the whole TU). I need to find our function's insns. The dump is per-TU. Our function is func_8014DF94. Let me find the function boundary in the dump and count the stores to `(plus (reg 29) (const_int 24))`.

Let me grep for the function name in the dump.
