---
ts: 2026-10-17T09:32:24.592Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab0fc0b10970aee54
model: claude-opus-5-5[1m]
effort: medium
turnId: ef221782-c3d9-410d-b33f-6b22ff144117
---
I need to figure out which TUs actually need the --only flag for rejudge: the ones with live macro expansions. That narrows down to the one-off TUs with real body sites — SC06_008, SC06_010 (which has RTP_SND), SC06_018, 8017C24C, and 8019 — excluding the DRAW-only cases.

Counting them up, I land on 13 TUs total that need rejudging. Including the DRAW-only ones would be harmless but wasteful since they'd just rejudge unchanged bodies, so I'll stick with 13 and label this batch t8_mac1. I should run it in the background with run.sh since it might take a while, and set --batch 13 so everything processes in a single batch.
