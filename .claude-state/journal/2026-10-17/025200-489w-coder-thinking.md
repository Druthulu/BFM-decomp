---
ts: 2026-10-17T08:52:00.258Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad48947f967e77fd9
model: claude-opus-5-5[1m]
effort: medium
turnId: 5652b206-5bd1-470d-af6a-d1e28be458c3
---
I'm realizing delever's marker_edits strips out the author's meaningful !FAKE comments and replaces them with generic "NEEDED DIFFERS" placeholders — that violates the architect's rule to never drop comments, since it erases the author's explanation for why the lever exists. I want to preserve that judgment info rather than lose it, so I'm considering whether restoring the files (perhaps via delever --restore) is still viable once in-flight state has been cleared.

Since markers are just comments and nhash likely masks comment text, restoring the original comment for bodies where nothing was actually removed should be harmless to the ledger — but for bodies with real removals, I still want to preserve the author's comments on surviving code where possible. Rather than modifying the tool itself, I'm thinking a simpler fix is a post-pass script: diff each file, and wherever a changed line differs from the original only in the text after `// !FAKE:`, restore the original comment while keeping actual code removals intact.

However, I need to be careful not to blindly restore old comments when the tool regenerated a generic marker reflecting a real rejudge decision — those updates are legitimate tool output, not something to overwrite. The rule should be: restore old comment text only when it isn't one of the tool's generic patterns, since marker format and author rationale are distinguishable, and the census/ledger logic just checks for presence of `// !FAKE:`, not content. This feels like protecting a constraint rather than expanding scope, so I think it's reasonable to proceed with this safeguard.

Now I want to confirm there's no restriction against doing this one-line deviation, and that "written 2 files" only reflects marker changes. I'll draft a small script to restore comments by diffing against HEAD across the affected files.

The run worked, but I noticed delever's marker pass overwrites each surviving site's original `!FAKE:` comment with a generic "NEEDED DIFFERS," losing the author's rationale. I'll add a scratch pass after each batch to restore the original comments on unchanged lines, since the ledger (not marker text) carries the actual verdict and nhash ignores comments anyway.
