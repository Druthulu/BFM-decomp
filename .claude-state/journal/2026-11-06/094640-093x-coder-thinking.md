---
ts: 2026-11-06T16:46:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_keOpLaCRmEIkDFe9UZ9V
---
The fp residual is a full register-shift cascade (s0/s3/s4/s5/s6/s7 swapped) + 8-byte frame. This is a classic local-alloc priority puzzle: the fp pin forces fp into s0; without it, fp gets s3 (because s0 is used by something else?) and the cascade shifts everything.

Given the function's size and the cascade, cracking all three pins lever-free within budget is unlikely. But let me try a couple of C-level moves for fp: fp = (s8 *)prim + 0x22. The register allocation of the loop pointers is priority-driven. The pin $16=s0 forces fp=s0. Maybe declaring fp earlier/later, or changing its type (s8* vs u8*), or its first use, changes priority.

Also the frame difference: mine saves s7 (an extra callee-saved) — 8 bytes. Target uses s0-s6 (7 callee-saved?) Let me count: target prologue? Let me see the target's prologue.
