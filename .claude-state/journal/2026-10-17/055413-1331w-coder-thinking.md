---
ts: 2026-10-17T11:54:13.055Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm tracing how CSE handles the subreg widening case—specifically when register j (HI mode) was set from a subreg of a wider pseudo 268, CSE has special logic to recognize that a later SI-mode subreg reference to j can be rewritten back to reference 268 directly.

Then I'm wondering what in the test case triggers this—maybe the duplicated increment across branches (`j++` in each arm jumping to a shared continue label) causes the increments to collapse into single instructions per arm, since CSE sees them as equivalent across the join point.

I'm tracing how combine handles the subreg chain: it substitutes the temp into the test via the log link, simplifying nested subregs down to just the temp register itself, while still keeping the original `j` assignment alive since it's used later at the loop header.

Since the combined pattern becomes a PARALLEL of two SETs rather than a single recognizable instruction, recog fails on the merged form, so combine has to fall back to splitting it back into two separate insns using I2DEST, which is the path that handles this two-set PARALLEL case.

I should think through whether cse would have already simplified this before flow and combine ever see it — if not, the test insn reads j through an ashift/subreg pattern, and I need to trace what combine does when it encounters that at this point in the pipeline.

Combine processes insns in order, so it would try merging 552 into 554 first (since tmp dies there), producing `j = j+1`. Then I need to check whether the later combination with 338 still happens the way I expect, or whether this ordering changes the outcome versus the dup case.

So if j's refs end up at 11 in the target, that means k's refcount must fall below the priority threshold for the given live range -- 11 refs needs a live range of at least 75 insns, 12 refs needs 82, 13 needs 89. k must be alive somewhere that j isn't, likely starting from its copy right after j=0 and extending through where t3v reads m.

I want to test a variant where t3v reads m directly instead of going through k3, to see how that changes k's inflation -- something like constructing ak plus a cast of m into k, then indexing x[m], and dumping the result to check the live ranges.
