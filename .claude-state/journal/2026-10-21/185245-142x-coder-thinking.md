---
ts: 2026-10-22T00:52:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_oCD11kmUmqCsz776zi3H
---
func_8017EA24 is the same shape as func_8017D96C: two launders — one on v1 (the mode) and one on e (a pointer).

The cast on `e` is not value-preserving (e is a pointer). So I need a different replacement for the `e` site: the do-while only (no cast).

The posgen will cover that: combo ("dowcast", "dow") etc.

Let me run posgen for the remaining items once the sweep finishes. Actually, let me run posgen now for the two items (D96C, EA24) — the CPU can handle it.

Let me generate and score them.
