---
ts: 2026-11-06T09:57:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rjgrAUQreQwuz56VyrS7
---
`--explain TU FN` reads one body's residual (no writes) — it explains the tree's body, not a candidate. But it prints the full listing maybe. Let me try `--explain` for CD314 to see the tree body's diff... but tree body is MATCH so no diff.

Better: write a scratch dump script. Let me see `_score_file` rest and what objects it uses. I'll write a small script that mimics _score_file with --keep then objdump both. Actually simpler: use `--try ... --keep` to keep candidate object, then `objdump -d` it, and for target use the baseline object from build/.

Hmm, but the diff display from SequenceMatcher with mnemonics is enough; I just need more context lines around mismatches. The printed diff shows only mismatched lines, not surrounding. Let me write a scratch script that prints both full instruction streams (mine and target) with indices. I'll import masked_diff and the compile machinery.

Let me look at the rest of _score_file to reuse.
