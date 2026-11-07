---
ts: 2026-11-06T19:00:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jljovdLZn9TWkV9YCsFI
---
The loop block (56..103) has priorities: 56 (1), 58 (2), 61 (2), 63 (3), 68 (3), 70 (4), 75 (4), 77 (5), 82 (5), 84 (6), 89 (6), 91 (7), 96 (7), 98 (8), 101 (1), 103 (branch).

The trace shows the scheduler picks by priority (higher first): 98 (8), then 101 (1)? Hmm, "ready list at T-2: 98 (8) 101 (1), now 98 101" — it picked 98 (priority 8). Then T-3: 101 (1) — hmm, 101 has priority 1 but was picked over 96 (7)? "launching 96 before 101 with no stalls at T-4" — it launched 96 before 101 (delay slot ordering).

This is the *new* scheduler's trace format (the one with priorities computed by the "dep" chain). The loop body: insns 56-98 are the body, 101 the branch.

Let me see the rest of the trace (T-10 onward) to find where the increments (a7/v1) are scheduled. The increments in the RTL: let me find their insn numbers. The a7 increment and v1 increment are around insns 84-96. 

Actually, the important thing: the priorities differ (1..8), so the scheduler picks the highest-priority insn first (the longest dependency chain to the branch). The increments' priorities: e.g., 96 (7), 98 (8).

Let me see the full trace and the RTL. Let me print the rest of the trace (T-10 to T-30) and the RTL for the loop block.
