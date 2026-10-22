---
ts: 2026-10-21T23:40:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_psvSBOqr9DLNaebLT1bR
---
Very useful. Note: "If this insn introduces a 'constant' register, decrease the priority of that register." — the constant pseudo gets a lowered priority. That's exactly the mechanism for the -160 constant pseudo!

Let me read the priority comparison functions (lines ~1560-1700) to understand the ordering.
