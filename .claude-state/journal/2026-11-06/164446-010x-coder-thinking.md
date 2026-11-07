---
ts: 2026-11-06T23:44:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rPheI571trsu79Ew72vm
---
Let me copy headers to orig.c and set up. Also check how tryinc.py works, and sc.sh.

First, let me copy each orig.c, and generate a "nopin.c" (lever-free starting point) by simply removing the pin/launder lines. Then score each to see the baseline gap.

Let me write a script to produce lever-free versions automatically? Better do manually per item since removals need C semantics (removing `register ... __asm__` declarations and replacing with plain decls; removing asm launder lines).

For item 1: remove `register s32 mode __asm__("$19")` → `s32 mode;` and remove the `__asm__("" : "=r"(q) : "0"(q));` line.

For item 2 header: remove the three `register ... __asm__` pins → plain s32; remove launder line.

For item 3: remove pins x1, x0, white, remove launder line.

For item 4: remove tp pin, remove launder.

Let me create these. First let me check the tu file for header items: src/shared/ov/func_8012DBD0.h - so the tu is the header itself. tryinc.py k <header> <fn> <body> for k-th includer.

Let me check tryinc.py usage.
