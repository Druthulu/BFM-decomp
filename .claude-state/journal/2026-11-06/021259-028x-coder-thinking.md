---
ts: 2026-11-06T09:12:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_krygz1EAoVvT5HVxsHXy
---
Now notes.md for item 1. Write file.

Then item 2: func_8013A530. FRESH: diff orig.c against current src — need to regenerate orig.c. Let me do that.

Item 2 has 3 keepalives:
1. line 47: `__asm__("" :: "r"(bVar1));` after the sVar5 computations for param_1+0xa. bVar1 is pinned $8. The keepalive likely forces bVar1 to be reloaded/kept in $8.
2. line 58: `__asm__("" :: "r"(iVar7), "r"(t));` inside the else-if.
3. line 64: `__asm__("" :: "r"(fc));` before the call.

Need real C uses. Let's see what removing them does. First copy orig.c fresh, remove asm lines (keep the pins), score on includer 0 and diff.

Let me set up.
