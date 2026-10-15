---
ts: 2026-10-15T03:46:22.721Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab979db8361de1187
model: claude-haiku-5-5[1m]
effort: medium
turnId: 243a97c8-7e46-4136-94de-b425c226ce82
---
I need to verify the discrepancy between the "top 81 types" figure cited across different sections and the total count numbers like 579, ~13k, and the 18,668 struct-map types figure to make sure they're consistent.

For the legacy items, I should grep LEGACY_INDEX.md and the older phase-end files for references to func_8016BF50, func_801A1E94, and similar function names, since my earlier grep was truncated and I need to narrow it down with file-match-only output and head limits.
