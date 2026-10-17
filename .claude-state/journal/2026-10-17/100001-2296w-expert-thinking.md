---
ts: 2026-10-17T16:00:01.008Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
Since function names can repeat across different files, I should namespace the scratch directory using the function name plus the overlay directory basename to avoid collisions, and set the TU field to the file path itself—including header files per T10. I also need to think about how blank-function barrier rows behave as file-scope barriers within a TU.

For those blank-function rows that aren't actually functions, I should check the TSV line and the source to figure out how to categorize them instead of treating them as singleton functions.
