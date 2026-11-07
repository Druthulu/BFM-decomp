---
ts: 2026-11-06T16:52:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sUqyXUvT6MKzPUqZTtkk
---
t01/t02 = 9 but 65 ins (2 fewer). The two statements got combined (v1 <<= 16; v1 >>= 16 → maybe combine folded into one sra? or the shift pair was optimized). Let me look at t01's diff.

Hmm, 65 ins means something was eliminated. Let me diff.
