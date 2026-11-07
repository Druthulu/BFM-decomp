---
ts: 2026-11-06T15:47:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KepKlmzj3ZEUL8JOANEp
---
Item 4 is a big function with 6 pins (c $18, vb $22, otz $17, mhi $23, q $2, qt $5) and 3 launders (arg, and the two 2-output launders on n/otz).

The kinds column says only "launder". So I must remove the launders (3 of them: arg at 3014, n/otz at 3111 and 3182). Pins are levers of another kind already in the def — may stay (never added). So PARTIAL:pin if I can't remove pins, but the goal is MATCH with launders gone.

The comment says the `arg` launder is load-bearing (C: "The zero-byte __asm__("" : "=r"(arg) : "0"(arg)) blocks that substitution; the call's argument copy becomes a no-op and is deleted.").

And the 2-output launders are "LOAD-BEARING" for cross-jump of the POLY/LINE tails.

So this item likely needs: remove 3 launders, replace with real C. Let me first extract and baseline.

Function body: 2972-3205. Extract.
