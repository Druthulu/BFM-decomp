---
ts: 2026-10-20T01:10:16.593Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a05e0b52a09323442
model: claude-haiku-5-5[1m]
effort: medium
turnId: 4bc51f0a-5286-4e73-ac81-220bb3b35040
---
I'm checking which ledger files are actually referenced elsewhere: the P36 delever ledger is live-read by the progress tracker and cycle script, while the P37 restruct ledger ties into the residue coverage check, and the P37 census ledger connects to the type census and head types scripts.

For P36, I'm tracing the census, delever, and regen subfolders to see which scripts write vs. read each — the census is regenerated, the delever pack and ledger are live, and the regen engine reads body data for rebuilding. I'm also noting P33's verify output is tracked evidence, while P35 and P38's census and conversion folders still need their readers confirmed, and P39's census body-base-type file is what the restruct cycle actually depends on rather than P37's.

I still have several areas left to verify — the giants manifest and oracle dumps, the ghidra export/rebuild pipeline, the "auto" runtime state (which holds live locks and heartbeat data), and the P32 t3/t4e/t5x reports and tracked artifacts per gitignore exemptions. I'm planning the next batch of greps across these remaining paths and key docs to confirm which folders are live state versus regenerable, keeping to my budget of roughly 20 tool calls.
