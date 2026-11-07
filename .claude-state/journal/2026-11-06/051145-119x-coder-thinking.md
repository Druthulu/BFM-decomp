---
ts: 2026-11-06T12:11:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aWNvs90XHhvgIGWeGYKc
---
t04: score 0, asm IDENTICAL. No launder (the asm lines are all pins, which are allowed since this item's kinds are keepalive,launder).

Wait — I need to double check: t04 removed the launder and the keepalive (n = w7 minus launder, and w7 = orig minus keepalive + do-while). Yes: t04 has neither the keepalive nor the launder.

So this is a full MATCH! The moves:
1. keepalive → do-while around the two stores.
2. launder → declare iVar4 and nx as `short` (instead of int).

Let me verify t04 has no keepalive/launder: the grep shows only pins. Good.

But wait — the brief says "no new lever of any kind". Changing iVar4/nx to short is a width change (allowed: "s16/u8 widths"). The do-while is allowed with the marker.

Let me verify on all 141 includers.

Let me also double-check the `do {` count and that the loop still works.

Let me view the loop part of t04.c to confirm.
