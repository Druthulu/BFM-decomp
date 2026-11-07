---
ts: 2026-11-06T13:00:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xIpBnKzAfqDDWeTo7jus
---
Item 4: case 3 ends with a barrier then `goto TAIL;`. The barrier is between the `if (unk1C >= 0x10) goto C78;` and `goto TAIL`.

Note case 0 (lines ~60-66) has the same shape: `unk1C += 1; if (unk1C >= 0x10) goto C78; goto TAIL;` — WITHOUT a barrier! So case 0 and case 3 have identical tails; the barrier in case 3 prevents a cross-jump merge of the two tails.

So this is the same jump2-crossjump-arms class. Let me score.

Item 5 is the twin of item 2 (barrier keeping the y store above the 0x64808080 pair) — same as item 2's wall, plus the m24/op pins.

Let me score item 4's barrier-free body.
