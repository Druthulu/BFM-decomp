---
ts: 2026-11-06T21:46:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YzJc4qnpeScvWUiFfrmR
---
recs_for needs by_src and inc. tryinc monkeypatches ds.recs_for. Too involved; but the Scorer class does all this. Let me instead write a script that constructs a Scorer like main does... Actually, easier: use the object file that the `--keep` run produced? No, that's the candidate.

Alternative: find the baseline object path directly. `oracle.baseline_path(obj)` where obj = the build object for the TU that defines the function. For a header item, the includer TU is src/ov_MAIN_012/ov_MAIN_012_jr_80171B4C.c → build/src/ov_MAIN_012/ov_MAIN_012_jr_80171B4C.o. Then baseline_path may map to a snapshot.

Let me check baseline_path.
