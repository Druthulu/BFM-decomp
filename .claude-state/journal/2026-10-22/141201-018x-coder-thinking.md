---
ts: 2026-10-22T20:12:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8SvRQZtBapSBOGCjxryu
---
I can dump a scratch TU. The `--try` path in delever_search produces a scratch copy; `--keep` keeps it. cand.sh uses --keep and prints the object path, then deletes. To dump, I need the spliced TU. Let me check delever_search.py for a --keep behavior and where it writes the TU.

Let me check `--try ... --keep` output and whether it keeps the t.c. Let me grep delever_search for "keep".
