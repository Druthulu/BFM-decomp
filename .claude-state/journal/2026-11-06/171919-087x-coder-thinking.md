---
ts: 2026-11-07T00:19:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zitq8NLDBbPWJdtpbxWw
---
h01 (lever-free, tp in if): 24 (worse than 22), 82 insns. h02 failed to generate (the assertion failed on nopin.c because nopin has the launder line between, so `old` doesn't match).

Anyway, tp-in-if doesn't help (still 82 insns → const fold persists).

OK, item 4 is a WALL: cse-const-addr (launder) + global-pri-bank-order (pin).

I need ≥30 tries. Let me do the statement permutation batch (20) to reach ~37.

Let me run a permutation search on the lever-free body over the 5 leading statements (valid orders only).

Let me write it.
