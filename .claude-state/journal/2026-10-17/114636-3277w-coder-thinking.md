---
ts: 2026-10-17T17:46:36.144Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af8c379eaae6cf6ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 4f5d1d7b-243b-4976-9079-51d9b9c05b4b
---
I should explain my approach before running anything, then move on to writing bank_rows.py. I'm working out the TSV matching logic: dropping rows with singleton causes, handling partial matches by dropping unused kinds, and keeping rows whose kind matches.

For the ALL case I'll rewrite every row matching the given kinds, and for WALL I'll pull wall column values from the results while keeping best/tries data intact for the partial-kept rows.

My approach: the swap tool will replace each banked function's definition with its win.c version (warning if it diverges from orig.c), while the rows tool rewrites lever_residue.tsv per (file, func, kind), updating MATCH/PARTIAL/WALL rows accordingly. I'll leave other non-singleton rows untouched unless strict flags them as unused, letting strict decide rather than guessing.
