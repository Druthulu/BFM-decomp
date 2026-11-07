---
ts: 2026-11-06T12:03:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gS505dw21qWhXQWGEjpY
---
- Removing only the keepalive: score 16, 165 insns (count matches).
- Removing only the launder: score 10, 163 insns (2 short).

Both contribute. Let me look at each diff.

For the keepalive (w2): 165 insns, so only scheduling/regalloc differs. Let me diff.

For the launder (w3): 163 insns, the sll/sra gone.

Let me start with the keepalive: if I can fix it with real C, then handle the launder.

Let me diff w2.
