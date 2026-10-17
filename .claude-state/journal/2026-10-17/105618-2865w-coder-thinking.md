---
ts: 2026-10-17T16:56:18.361Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm realizing cse replaced subreg 77 with 74 since it recognized their equivalence, which caused h to disappear. For the copy to survive, it would need to live in the predecessor block in a way cse wouldn't collapse, which hinges on whether h's lifetime extends longer than v0's.

I'm trying different scenarios: maybe an intervening no-op assignment to v0 breaks the equivalence, or the test operates on a reloaded memory value cse treats as equal, or the subtraction gets computed twice in a way that lets cse merge things unexpectedly. None of these quite explain why v1 stays distinct from v0, so I need to keep searching for the right structural difference.
