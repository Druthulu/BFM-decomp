---
ts: 2026-11-06T22:38:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_daYLYXw7csyFirpB7IUv
---
74 ins (one fewer than target 75) — score 38. Hmm, the mask-in-place eliminated an instruction? The target has `andi $17,$17,0x0fff` and uses it; with mask-in-place there's still one andi. 74 vs 75 means something else got removed.

Let me dump and check the alloc/asm.
