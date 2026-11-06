---
ts: 2026-10-22T21:16:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s0ADgZW0Nwr6FUWf9lyi
---
So in the .jump dump both arms exist (235 and 414 regions) — that's the first jump pass, before cross-jump? The .jump dump is written after jump_optimize (which includes cross-jumping in 2.96? `jump_optimize` with `cross_jumping`...). Hmm, but the blocks both exist here. Maybe cross-jump happens in .jump2 (post-reload jump pass) — the tool comment says "c10's cross-jump only in .jump2".

So the merge happens in jump2 (post-reload). Let me check jump2.
