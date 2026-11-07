---
ts: 2026-11-06T05:22:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dpgi7rmmynom2217r7AN
---
No stack refs. The lreg dump has no `reg:SI 29` (sp) references. So the frame size 16 doesn't come from stack slots.

Hmm, then where? Let me look at the `.frame` in the *nobar* .s again — frame 0. And orig frame 16.

Could the difference be `current_function_outgoing_args_size` after all? Let me check the MIPS `.frame` directive generation: `mips.h` `ASM_OUTPUT_...`. Let me grep for "vars=" in mips.h or mips.c.
