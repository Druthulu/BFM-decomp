---
ts: 2026-10-17T10:27:00.787Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: afda95bec87dc8de3
model: claude-opus-5-5[1m]
effort: medium
turnId: 1e35bd3f-abc8-4289-9a6e-6d49268d15f8
---
The grep against the cookbook didn't return useful results since the format differs, so I'll just name the entries directly for coders to reference. I'm noticing that a "head class" represents the same body text by hash across copies, even if function names differ by address — meaning identical code appears at different addresses across overlays. The row count dropped to 1059, seven fewer than before, reflecting changes from T8. Now I'm planning the first wave: assigning four coders to crack the six largest targets concurrently.

I'm assigning specific functions to each coder — one gets the keepalive+pin pair and its sibling, another gets the instruction function, another the launder function, and another the double-pin case, with two more functions queued next. I need to make sure crack coders only work in scratch space and use the right permuter lanes, checking whether concurrent writes to the outcomes log are safe and whether match_one requires a pre-built tree. I also need to figure out how to propagate a cracked body across all textually identical copies in the ~130 translation units, checking whether there's an apply-body tool and whether the banking mechanism will pick up manually-cracked wins or if propagation needs to happen separately per copy.

To keep this manageable, I'm deciding crack coders should only crack in scratch and never touch src, just returning the winning body file path, while a single serial propagation coder handles applying each cracked body to every copy, running the oracle check, cleaning, rewriting the TSV, and committing — keeping crack and propagation as separate roles rather than letting crack coders propagate themselves, since concurrent clean-makes would be chaotic. Now I should check the help output for match_one and delever.py to confirm these assumptions.
