---
ts: 2026-10-15T03:32:25.925Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a705ed8352fdd0106
model: claude-opus-5-5[1m]
effort: medium
turnId: 7a67f1a0-185f-485c-896e-f31712674803
---
These are just matching techniques referencing ultracode for context, not actual mechanisms, so I'll keep the cookbook as-is and leave the WARN index be since restructuring isn't my job. Now I'm checking the ops docs for retired mechanisms, specifically the session-start-ritual and model-strategy-per-phase files which appear to reference things no longer in use.

I'm weighing whether to run `ops --sunset --gen` as a dry-run, but since it moves any unreferenced topics it could sweep up valid content too, so I'll skip it and just mention it in the recap instead. Moving to the card plan, I need to replace the TODO placeholders in the Developer section with actual details: the developer's identity and solo workflow, their reliance on Claude for domain knowledge since they can't read MIPS assembly, and the project domain (PS1 decompilation of Brave Fencer Musashi, which I'll confirm against PROJECT_CONTEXT). I'm also filling in the autonomy and notification settings, noting the harness operates autonomously within phases with gates only at plan approval and milestones.

I want to drop the drew-working-preferences bullet and replace it with concise working-style rules: how to handle recommendation requests, stop-rule negotiations, correcting misconceptions before costly steps, flagging new tool/dependency tradeoffs, executing within approved plans without per-step check-ins, ending turns with answers he's waiting on, treating the agent cap as his live dial, and asking him to run /mcp after Ghidra MCP restarts. I'm placing this under Developer since it's about working with him specifically, and I still need to add a commit rule to Conventions about one commit per task.

I also want to note that third-party tools should remain git submodules rather than vendored code, verify the .gitmodules file reflects that, and confirm the Claude state directory setup in settings.local.json actually matches what's documented. Separately, I need to fix the broken Tools row by pointing to the tool dictionary file instead, and clean up a leftover duplicate line about documenting disabled logic that's already covered in the skill.

For the paths and build sections, I should fill in the actual oracle definitions, generated path locations from the generation plan or Makefile, the real test gate command and its expected "218 passed, 0 failed" output, the correct run/clean commands per binary, and reference the version-pin summary doc along with the low-memory foreground guard quirk in tools-health. Overall length is tracking close to the 7000 character cap, so the refresh should stay roughly the same size.

I need to gather the actual facts before finalizing — things like the G1 submodule reference, the .gitmodules contents, the autoMemoryDirectory setting, the project context name, the tool dictionary path, and the real Makefile targets.
