---
ts: 2026-10-17T04:22:31.136Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9545e292ce6b8e9d
model: claude-opus-5-5[1m]
effort: medium
turnId: 2945ba12-d858-46e9-8016-11c66319475a
---
I need to be careful here—functions at the same address across different overlays aren't necessarily copies of each other, since different overlays loaded at that address can hold entirely distinct code. The "same-address copies" idea likely refers to genuinely identical function bodies rather than just shared addresses, so I should verify whether the dedup criteria actually require agreement on a single signature across these instances.

The census's lying count doesn't cover return-type lies or the other done-when checks, so I'll need to investigate each flagged function individually rather than trust existing tooling. Given the scope, I'm thinking of splitting this into coder briefs: one for the md_SC07_004 pair and caller cascade, one for the three lying_exceptions callees, one for the ANSI prototype conflict, and one for hunting down same-address copies and return-type lies via the dedup classes. Before handing these off I want to check the dedup config file and confirm how type_census actually defines "lying," starting with the md_SC07_004 functions as a test case.
