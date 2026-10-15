---
ts: 2026-10-15T03:48:20.598Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a812a1cad2262a9e4
model: claude-haiku-5-5[1m]
effort: medium
turnId: bba3119c-0ef8-4738-a757-f239f5a71d3f
---
Finding the path in .git/index is strong evidence the file is tracked, since the index lists tracked entries. I don't have an easy way to get the exact byte size, but I can report the line count of 32,633 JSONL rows instead.

I'm trying to figure out why the map file isn't matching my pattern for the P37 census — maybe the file doesn't exist at that path, or my regex isn't catching the JSON formatting as expected. I should check directly with a targeted Glob for the specific path rather than guessing, and also look into the readability_progress.py script's timeline chart logic and the residue row shape in restruct.py, while keeping an eye on how many tool calls I've used so far.

Counting up my tool calls, I've now hit 21, which puts me over the 20-call cap I'm supposed to respect — I need to stop investigating and hand back with what I have. I'm weighing whether writing the required report file counts against that cap, but I think it's the necessary hand-off artifact regardless, so I'll write the report and then proceed to the subagent handback as the final steps.

Since the P39 census file doesn't exist, there's no scratch script to write, and the answer needs to stay under 40 lines. I'm pulling together what I've found: the CLI entry points and flags in type_census.py, the residue-cause predicates and their locations in restruct.py (FILE-SCOPE, NO-TYPE-IN-MAP, TYPE-NOT-VISIBLE, MISALIGNED/NO-EDIT, and the ABS-ADDR/GADDR/GLOBAL causes), and the writer logic that produces residue_census.json/.txt in the default output directory, along with the record's structure covering forms, causes, segments, and top types.

Now I'm checking the TNC site-counting logic, which only tallies covered sites annotated with that cause and ranks types by count — distinct types are just the length of that map. I can't verify the 291,819/13k claim since no P39 census exists, and no scratch script was written for it. For canonical types, I'm tracing canon_types() back to its struct/union definitions in the canonical headers, how it builds the struct map and related output files (struct_map.json, struct_map_top.json, body_base_type.json, struct-map.md), and the --check-structs tool entry point.

I'm now locating related tooling for struct layout resolution and the restruct CLI flags (--write-types, --audit-types, --check-ledger), but can't find lift_types/struct_twins tools in the repo. I still haven't pinned down exactly what action a TNC site needs — define a canonical type, fold a duplicate onto canonical, or respell a cast — just the possible options.

I'm mapping out restruct.py's CLI usage (plan/apply, rung flags, residue, forms, status, check-ledger), locating where the ledger path and JSONL row shape are defined, and confirming that the ledger stays untracked since the git add in restruct_cycle.sh doesn't force-add ignored .run files.

For the timeline, I'm tracing how readability_progress.py builds its TSV rows and columns, including the raw_casts field, and how snapshots get taken via the CLI. I'm also checking how progress.py pulls the check_casts block from residue_census.json into the progress JSON, though I never located any actual chart-drawing code despite the header comment mentioning one — so the uncovered series would need to be a new column computed from the by_form uncovered data.

For the delever ledger, I only confirmed the path appears once in the git index, without verifying tracked status via git ls-files, and I have the line count but not the byte size.

I've hit the 20-call cap, so now I need to write the final report. I'll save it concisely to the pending research directory under a slug describing the TNC canonical-residue census timeline work, keeping it under 40 lines, and make sure my handback message leads with the "REPORT: pending/<file>" reference.
