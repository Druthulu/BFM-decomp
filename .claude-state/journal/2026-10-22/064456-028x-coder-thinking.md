---
ts: 2026-10-22T12:44:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_5hf3J3bPZzLlkqVdK4D5
---
The gcc source is available at tools/reference/gcc-2.7.2/cse.c. Let me look at cse_const and find_best_addr to understand the fold.

Let me grep for the fold of a register into a constant use.
