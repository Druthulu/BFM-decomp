---
ts: 2026-11-06T10:03:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Rcl0Pat4gGfMpFoDWo5P
---
Mine: f=a1, i1=a0, giv=v1, limit=a2.
Target: f=v1, i1=a0, giv=a1, limit=a2.

So i1 is a0 in both. The swap is f↔giv. The comment says counter vs giv, but empirically it's f vs giv. Whatever; maybe the comment refers to a different variant.

So: target wants giv in a1 (higher reg than v1). Mine gives giv v1 (lower). f gets a1 in mine, v1 in target.

In global-alloc, regs are assigned in priority order, picking the first free reg from REG_ALLOC_ORDER. If a1 is "better" than v1 in the order, the higher-priority pseudo gets a1.

Default REG_ALLOC_ORDER for MIPS in GCC 2.7.2: let me find the actual order. Since mips.h doesn't define REG_ALLOC_ORDER, the default is in regclass.c/hard-reg-set? Let me grep for the default definition.
