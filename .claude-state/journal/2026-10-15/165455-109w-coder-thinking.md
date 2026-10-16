---
ts: 2026-10-15T22:54:55.128Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
Since sites.jsonl is 223MB, I'm planning to scan it line by line with a quick string check for the type field before doing a full JSON parse, so this stays fast and only parses matching entries. I'm also noting that existing pre-T3 define rows like the Unkstruct pairs still count as define targets, which raises a question about whether the rule covering define targets in type_folds.tsv applies to them too.

I'll restrict the T3 band def condition to rows following a `# T3` comment block, since the cause text specifically refers to T3, even though the literal brief just says "a define target" — this is a minor deviation I should log. For testing, since struct_twins has no selftest itself, I'll add a pure helper function `t3_uses(fold_lines, site_lines)` that maps targets to their type and citations, and exercise it from restruct's selftest instead. Now I'm looking at where the existing decide_band test cases live in restruct's selftest to figure out where to slot this in.
