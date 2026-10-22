---
ts: 2026-10-22T11:09:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_wMwRPiqKbYn9jtIGaDZS
---
Good. I can dump the RTL passes for a candidate TU. The `--try` in delever_search probably writes a scratch TU. Let me see how delever_search --try works — does it keep the scratch? There's `--keep` mentioned in constraints ("`--keep` scratch is removed after use").

Let me look at the delever_search --try code path to find the scratch dir.
