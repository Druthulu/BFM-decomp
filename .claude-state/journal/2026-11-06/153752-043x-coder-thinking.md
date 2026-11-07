---
ts: 2026-11-06T22:37:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_x6WQ6HI22SmTkMNOQmxF
---
Interesting: "Making s1ang global (g1: mask in place) lifts its pri to 6363 > d 5185 -> still s1ang $s0." So they tried "mask in place" (which globalised s1ang) but it made s1ang's priority higher than d's, so s1ang took $s0 — the wrong direction. For our function, d's priority is 10000 (cap) and s1ang global would be ~2857, so d should win! Let me look at g1.c to see the move.
