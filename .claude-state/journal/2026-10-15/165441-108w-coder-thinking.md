---
ts: 2026-10-15T22:54:41.275Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I should insert the new dead-code entry at the end of the "Dead kept" section, right before the next heading or EOF, formatted as "- Name — cause". For item 3, I'm figuring out that during collection, unbound names matching define targets in type_folds.tsv should get U-keyed binds with cites pointing to binary/function addresses pulled from sites.jsonl entries matching the map type.

I'm working out where the explanatory cause text belongs — likely appended to the per-name line itself, something like "0 obj — T3 band def, dead until rung S; map type <mt>; TNC sites in <cites>". I need to verify that `uses()` correctly surfaces addresses into the cause field so the address regex matches, and I'm tracing how load_twins extracts the cause line to confirm this works. I also need to understand what counts as a TNC (type-not-canonical) body, since that requires the heavier residue-split logic combining sites and the ledger in struct_twins.

I'll simplify by treating sites whose `type` matches the map type as the use sites — since no canonical type exists before rung S, they're inherently TNC — capped at three, resolved to binary and function address via `binary_of` and `addr_of`, with addressed entries sorted first. I'm confirming struct_twins reads sites.jsonl from the given census directory, and I still need to check the sites.jsonl line format plus the type_folds.tsv schema (map_type, action, target, evidence, note) to see if struct_twins can parse that TSV directly itself.
