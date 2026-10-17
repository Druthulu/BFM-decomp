---
ts: 2026-10-17T04:25:19.149Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5605ba96cc5ff027
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c792287-f11f-4848-8566-c39a9bb058a0
---
I'm realizing that --body only rewrites the definition in that translation unit, so existing callers with no arguments would break if I add parameters—since --with can't target the def TU directly, I may need to pre-edit callers in the working tree before running the tool.

But I need to check whether the judge compares against the oracle ROM bytes or against a baseline build of the current working tree, since that determines whether my caller pre-edits are safe. I should look at judge_files to clarify what it's actually comparing against.
