---
ts: 2026-10-22T06:23:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_sVFtL13kOVU5UihPeKHp
---
280 tries. Best is still 2 (the u16/and/u8 cast aftervol+nest+volfirst+stmt).

Interesting: `sxleft` (sx | 0x3000 | vol) gives 3 (MIXED) with aftervol. And `flat`/`left`/`sxfirst` with the cast late give 5 (REG-caller).

Let me look at the "sxleft" 3 (MIXED) case: v2_u16_aftervol_sxleft_volfirst_stmt. MIXED means some register differences + something else. Let me diff it.

Also let me check the none-lever (plain) results in this sweep to see if any plain variant does better.

Let me grep the scores file for the "none" lever.
