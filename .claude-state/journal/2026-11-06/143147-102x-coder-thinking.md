---
ts: 2026-11-06T21:31:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9ak9Kdlch3ho1dyg9d4x
---
dt.sh on the header works and scores 0 (MATCH). It says "the bank judges the whole object" — so for a header, the score 0 means byte-identical across... maybe it checks all includers internally. Let me see the full output (tail 3 showed the last line). Let me run with tail 10 to see if it reports per-includer.

Actually, the score line says "score 0 (OTHER; mine 75 ins, target 75)". The "OTHER" and "the bank judges the whole object" suggests it's the same as the TU items. For a header, the bank likely checks all includers. The brief says "header item: MATCH only if score 0 on every includer (tryinc.py k = 0..n-1)". So I should verify each includer.

But tryinc.py crashes. Let me investigate: maybe the recipes for the includers aren't loaded because the build system changed. Let me run a quick script to check `dl.includers()` and `by_src` for this header.

Actually, let me first check whether dt.sh's header scoring already iterates all includers. Let me look at delever_search.py's Scorer for a header (line 260: "the bank verdict: IDENTICAL on every recipe of the file (a twin's object; every includer of a header)"). Let me read around 240-300 and the --try header path (771-800).
