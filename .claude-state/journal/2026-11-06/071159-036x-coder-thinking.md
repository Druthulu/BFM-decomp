---
ts: 2026-11-06T14:11:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_W8qgEG59eVVBIH0ToCQR
---
There's a wall tag `greg-ref-count` — "global-alloc ref-count priority gives a hot pseudo a different hard reg (G26)". That's exactly our case. And `lreg-qty-priority` (local-alloc). And `global-pri-bank-order`.

Hmm. So this may be a known wall. But the task is to try to crack it with real C.

Let me look at how G26 handled greg-ref-count — was it cracked? Let me grep moves.md for greg-ref-count and lreg-qty-priority.
