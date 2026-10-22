---
ts: 2026-10-22T05:46:31.520Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a933331c6d154adc4
model: claude-opus-5-5[1m]
effort: medium
turnId: d25270b4-e42b-432f-9435-484b642c2966
---
I'm noting that BANKING seems to hold the ext lane's oracle, which implies the ext scorer might wait while BANKING is active, so I want to check bin/sc.sh to confirm how that barrier logic actually works. The note about batching functions in groups of five or fewer also seems relevant to how this gets scheduled.
