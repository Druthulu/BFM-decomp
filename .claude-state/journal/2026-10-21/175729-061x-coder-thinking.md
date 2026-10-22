---
ts: 2026-10-21T23:57:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hyIrPTNQFMbcjmfbXQrW
---
M5/M6 got worse (14, 41 ins, extra frame). The hoisted result=0 before the call made `result` live across the call → gcc spilled it to $s1 ✗.

So the "result born before the call" idea fails (it must not be live across the call).

Back to M4 (39 ins, score 8): hoisted result=0 AFTER the call, single assignment. Let me see M4's diff to know what differs.

Let me printM4's full diff.
