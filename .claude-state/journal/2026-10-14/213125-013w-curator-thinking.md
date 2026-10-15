---
ts: 2026-10-15T03:31:25.669Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a705ed8352fdd0106
model: claude-opus-5-5[1m]
effort: medium
turnId: 7a67f1a0-185f-485c-896e-f31712674803
---
I'm thinking about how the deliverables project ships into an archived, finished state, while the retrospective work depends on capturing live context before transcripts disappear—PhaseEnds get assembled from task logs and summaries, preserving dead ends with their reasoning, costs, withdrawn claims, and dates as the skill guide describes.

Checking whether terse model-read style conflicts with that verbosity requirement, I conclude it doesn't—terseness governs wording, not what gets omitted. I'm routing phaseend-verbosity to a rule: PhaseEnd records must preserve dead ends, costs, withdrawn claims, and dates so the future retrospective can reconstruct history from git plus phase-ends, since the first month of transcripts is already lost. This feels close to the existing rule about phases naming and publishing the counts they move, so I need to check how a rule-routed memory's body actually gets used—whether the description becomes the headline and the rest becomes the body text.

The body references retired mechanisms like CURRENT_PHASE and checkpoints, which would be bad to bake into a rule verbatim, so instead I should archive the memory and hand-add a clean rule via the rules script after checking its help output. The tool-change-updates-siblings-and-docs item should get the same treatment—route to a rule with clean text, after confirming whether docs/SETUP.md still exists. For restoring the developer card bullets, I'd rather hand-edit the card's Developer section directly than let the automated route produce an ugly bullet line, since the items are already preserved in the genlegacy archive and a memory reindex will keep those archive pointers intact regardless.

I also need to actually exercise the migration path with --route and --gen 3.2, maybe using the mcp-reconnect-after-restart entry routed to ops since its body is reasonably clean. For tool-change-updates-siblings, the body itself seems fine as-is, so rules_add with clean text still seems like the better option once I check its help. I should also note that archiving something already in genlegacy doesn't make sense, and still need to check the cookbook for pass-j, parallel_gate, and fleet-parallelism references.
