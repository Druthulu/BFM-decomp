---
ts: 2026-11-06T16:56:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mVD4BDPcAX0rgddO7yTG
---
y01 = 0! The q-launder is cracked with `q = 0;` (dead reset, C0414) — zero bytes, and the score is 0. That's the q launder replaced. y01 still has the keepalive and the s-launder.

Now:
- y02 (q cracked + keepalive removed, s-launder kept): 2 ORDER.
- y03 (all three removed): 21.
- y04 (q cracked + s-launder removed, keepalive kept): 19.

So the s-launder is the big one (removing costs ~19). And the keepalive costs 2 (ORDER).

Let me look at x1's diff (s-launder removed) to understand the s residual.
