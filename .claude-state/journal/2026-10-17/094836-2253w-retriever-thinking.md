---
ts: 2026-10-17T15:48:36.398Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a92213cdfb705eea6
model: claude-haiku-5-5[1m]
effort: medium
turnId: 0b9dc8f2-e929-4e44-bc4f-f3370b69571f
---
I'm looking at the breakdown of kinds, noting pin at 589 and a scattering of others like barrier, launder, and instruction totaling 845, while also checking how often the oracle differs after removal.

Reconciling the counts: singleton (572), head-class (607), and missing-parameter (255) sum to 1434, and with the two agent-suffixed rows accounting for the rest, that fully explains the 1436 total. So the vast majority of cases (1416 of 1436) show the oracle differing on removal, with none marked as unjudged.

I don't have the budget to enumerate the remaining ~20 distinct cause strings exactly, especially the many distinct head-class prefixes — grepping with a head limit would just give me the first 15 lines rather than the most frequent ones, so that approach won't work well. Instead of forcing an imprecise answer, I think the better move is to write a small counting script to a file so the caller can run it themselves, since writing a helper script is within budget even though running it isn't.

I'll place the script under the planner's working directory, then separately write the actual report markdown to the pending research folder as instructed by REPORT: yes, naming it something like `retriever-code-lever-census-residue.md`. The system note discouraging report files seems to conflict with the brief's explicit REPORT: yes instruction, but since that's the specific task configuration, I'll follow it and also include the full findings directly in my handback message as a safeguard.

The script parses the TSV, validates row structure, and tallies counts by kind, cause prefix, instrument, and the top 15 full cause/instrument values, along with checking pass-word patterns and whether cause prefixes match an allowed classification set like singleton, head-class, missing-parameter, or similar categories.

I'm tracking down exact line numbers across the source file for each relevant function and block — residue loading, parsing, strict failure checks, cause classification, and the write/print logic — so I can reference them precisely in the final report before writing it and handing back to the subagent.

A key issue I'm flagging: the exit code logic doesn't actually account for unused residue entries, so the tool can print "OK" even when residue-unused is nonzero — meaning the milestone isn't truly enforced by the exit status. I'm also noting that the "names a compiler wall" rule as currently written would fail against essentially all 1436 rows, since the causes are class labels rather than actual pass names, so this needs to be called out as a major discrepancy. There's also a row-count mismatch (1436 vs. the expected 2,309) that I need to flag before finalizing. Now I'm moving to actually write the script.
