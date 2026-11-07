---
ts: 2026-11-06T10:10:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DPDQRKwHor062f2MZs6Z
---
All still 6. The v0/v1 swap persists. Interesting — even b8 (tb reused for unk50) is 6. So the swap is robust.

Let me look at b12/b3 (separate u) diffs to see if the register part changed.

Actually, the swap: mine t=v1, tb=v0. None of the variants changed it. Hmm, but earlier v4 (separate u) had t=v1, tb=a1 — the register part changed but the schedule broke, still 6? v4 was 7. b12 = a5+separate u → 6. Let me check b12's diff.
