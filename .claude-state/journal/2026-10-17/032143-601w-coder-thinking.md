---
ts: 2026-10-17T09:21:43.504Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: d5f3c548-1279-4293-8954-e6ee5462dd24
---
All 136 SHB definitions are confirmed dead, so I can delete them all, while leaving comments that mention SHB intact since those are just stale references, not actual code. The census row count of 136 matches these per-translation-unit macro definitions, which lines up correctly.

I also need to check that the header preceding one definition doesn't rely on SHB — grep confirms it's clean. The prelude's ENGINE_SHB entry stays untouched since it's the canonical source, not a per-TU duplicate. Now I'm going through the remaining nine one-off macros, checking definition and usage counts for each.

All 136 SHB definitions are dead code—unused outside comments and their own defines—so removing them won't affect preprocessed output. Now I'll survey the one-off macros.
