---
ts: 2026-11-06T12:41:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_khNYyBch6qosP3s9XPFP
---
All 5 items are `barrier` kind. Baseline lines in list.tsv: last column 0, 0, 180, 121, 0. Wait the format: `dir file func kinds lines` — so last number is lines? Actually list.tsv format says "dir file func kinds lines". The last column is lines (function line count?). Let me check: `func_80180EC0... barrier 180`. Hmm, could be lines. Whatever.

Items:
1. func_80186CE0 (ov_SC02_027) barrier
2. func_8018BCD4 (ov_SC03_001) barrier
3. func_80180EC0 (ov_SC03_105) barrier
4. func_80181F74 (ov_SC03_112) barrier
5. func_8018893C (ov_SC03_124) barrier

Let me look at the item dir contents (fn, tu files) and the helper scripts.

Let me check bin/dt.sh usage, bin/sc.sh.
