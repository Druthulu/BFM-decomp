---
ts: 2026-11-06T05:18:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sgWAeCNhCEno8GIUag8G
---
Both have no `reg:SI 29` in the function RTL — because the frame pointer/sp adjustments are added later. So `vars=16` comes from `get_frame_size` = virtual stack slots. Let me grep both for `virtual-stack-vars` / `virtual_stack_vars_rtx` in the function region.

Actually the RTL dump uses `(reg/f:SI 29)` or `virtual-stack-vars`? GCC 2.7.2 dumps with `(reg:SI 29)` after instantiation, but at .rtl (pre-reload) it's `(virtual-stack-vars)`. Let me grep for "virtual" in the function.
