---
ts: 2026-11-06T21:43:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ENBqmgVjF0YaQyz4uGU8
---
Everything checks out:
- 3 results rows (one per item).
- Item 1 win.c = 0 (MATCH).
- Item 2 win.c = 1 (WALL, best 1).
- Item 3 win.c = 0 (PARTIAL:pin; verified 141/141).
- No leftover dump dirs.
- Log written (2.7K).
- Shard dir 780K (<200MB).

Now, one final consideration: the item 3 win.c score shown here is via dt.sh (single includer rec[0]) = 0, and the full 141 verify = 0. Good.

Let me also double check the notes.md files exist for all three items. Item 1: I didn't write a notes.md! The brief says "Notes in <dir>/notes.md". Let me write one for item 1.

Item 1 notes: MATCH, keepalive gone, pin kept, the crack (pass `a` as the call arg). Let me write it.

Also item 2 notes.md exists. Item 3 notes.md exists. Let me write item 1 notes.md.
