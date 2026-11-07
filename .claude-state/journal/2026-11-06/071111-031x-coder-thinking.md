---
ts: 2026-11-06T14:11:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B7EQy1arF82GaJSstYb4
---
The --keep scratch is at .run/P36/engine/score/.../cand.o — but I need the TU source to run cc1. The scratch is removed after use? "--keep scratch is removed after use" per constraints — hmm the constraint says `--keep` scratch is removed after use. Actually it says "`--keep` scratch is removed after use". So maybe I should not rely on it.

Let me instead create my own TU copy for dumping. The include problem: the TU uses `#include "../shared/..."`? Let me check the top of the TU.
