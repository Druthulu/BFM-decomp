---
ts: 2026-11-06T21:53:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JsC319VdORlutlvNCW1d
---
So dst is a variable used in 6 blocks (each 8 statements), tmp in several places. The pins force dst→$3 and tmp→$2.

Lever-free (drop pins) = 135, 709 ins (1 ins difference) with dst in a2 instead of v1, plus bank shifts.

This is a big function; the twin is the same. Cracking this could be hard. Let me first reproduce the lever-free score (drop pins) and see the diff. Then try moves.

Note: tmp→$2 (v0). In many places tmp is a call result or a load. $2 is the natural return register, so maybe tmp gets v0 naturally in most places; the pin might be redundant except somewhere.

Let me create w0.c: remove the two register lines → `s32 dst; s32 tmp;`. Score.
