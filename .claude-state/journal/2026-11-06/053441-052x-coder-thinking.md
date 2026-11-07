---
ts: 2026-11-06T12:34:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WhAdGoeWpyTUiamiS2pc
---
Preferences come from local-alloc's reg_pref (REG_N_REFS etc.) — specifically `reg_preferred_class` and `reg_alternate_class` are set by local-alloc based on `REG_PREFERRED_CLASS`... In 2.7.2, `local-alloc.c` calls `reg_pref` heuristics? Actually `reg_pref` is in regclass.c: `reg_preferred_class()` returns based on `reg_pref[regno].prefclass`, set by `allocate_reg_info`/`regclass`. Hmm, this is getting deep.

Let me step back and be practical: the target has ret in v0. The pin forced it. Without a pin, what makes global-alloc pick v0 over a0? Possibly the register allocation order: REG_ALLOC_ORDER for MIPS in 2.7.2. Let me check mips.h.
