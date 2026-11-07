---
ts: 2026-11-06T15:33:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dnsL3jHZfeGaY1Y8Z3CP
---
The clones differ in:
- function name
- symbol names (D_801B03F8 vs D_801B3058 etc.)
- the V8_ type name (V8_8017FBEC vs V8_80186074)
- and presumably the type definitions are per-overlay.

So I can't just copy win.c; I need to apply the same *edit* to each item's orig.c: insert `vol = vol | 0x3000;` before the call. The rest stays as in each orig.c (which already has the right names).

So for items 4 and 5: take orig.c, remove the launder line, and insert `vol = vol | 0x3000;` before the func_8002D4C8 call.

Let me do item 4 (func_80186074, ov_SC03_089).

First FRESH check: orig.c was extracted at 07:59; the src hasn't changed (no banking). Let me re-extract to be safe and diff.

Then apply the edit and score.
