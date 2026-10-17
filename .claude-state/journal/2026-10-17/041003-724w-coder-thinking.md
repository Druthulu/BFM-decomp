---
ts: 2026-10-17T10:10:03.882Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed9b349dc2455822
model: claude-opus-5-5[1m]
effort: medium
turnId: dfd29141-6312-4a35-8baa-9537d6cb55c6
---
This confirms the explanation: at HEAD, those rows showed T7's refusal text since the pin was written before being read, excluding them from author/unjudged selection, while the regenerated working-tree residue now shows them as author/unjudged after T7's refusal text got replaced. I'm moving on to run apply and need to check the dirty tree requirement first.

Found that at HEAD these 4 rows originally read "T7 refused: pin written before read," getting skipped by the author/unjudged filter — only the working-tree residue rewrite changed them to "left by the author"/"not judged." Moving on to apply rung A next.
