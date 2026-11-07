---
ts: 2026-11-06T01:51:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TQiE0luDF6YyoAwb5xVp
---
The p3 dir is from 18:31 (old). The v1 --keep wrote to a different dir (p5, 18:42). So the scratch dir name varies (p3/p5). My dumps were of the wrong TU! That invalidates my earlier "orig" and "vA" dumps too? Let me check: the orig dump at 18:46 was p3 (old, barrier) — which was correct for orig by luck (p3 had orig? it has the barrier at 4176 but no `return;`). Wait p3 at 18:31 — that was the vA run? The TU shows the barrier and no `return;` → that's orig. Hmm, and vA's dump (dumps_vA) used p3 at that time which may have been vA. Confusing.

The important thing: the scratch dir is not reliably p3. I should get the actual candidate object path from --keep output and use its directory.

Let me redo v1's dump using the p5 path. Let me check p5.
