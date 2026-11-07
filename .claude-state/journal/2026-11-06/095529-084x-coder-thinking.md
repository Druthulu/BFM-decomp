---
ts: 2026-11-06T16:55:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dxkFIGvVW6JUy86Heue5
---
- w2 (remove the keepalive and the q-launder, keep the s-launder): 4, 74 ins (one extra).
- w4 (remove the s-launder and keepalive, keep the q-launder): 21, 79 ins.
- w1 (remove all three): 23, 80 ins.
- w3 (remove the s-launder and q-launder, keep keepalive): 22, 80 ins.

Interesting: w2 = 4 (74 ins). w2 keeps the `s` launder, removes the keepalive and q-launder. So the s-launder is load-bearing for the copy block (removing it costs ~19 ins!). Let me isolate:
- s-launder alone removed: w3 vs orig? w3 removes s + q, keeps keepalive: 22. 
- Let me test removing ONLY the s-launder, ONLY the q-launder, ONLY the keepalive.

Let me do that.
