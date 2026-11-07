---
ts: 2026-11-06T11:52:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yjua0ckmf8SvVuCbElpp
---
Still 1. Hmm. Let me check the disassembly to confirm it's still the andi (forwarding).

Maybe the front-end doesn't set MEM_IN_STRUCT_P for a u8 field of a local struct? Or the hash ignores it.

Let me check w9's asm.
