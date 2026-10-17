---
ts: 2026-10-17T11:00:47.758Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
Headers with prototypes ran fine, no conflicts there. Since the opaque-base hypothesis holds, I'm considering picking a user variable base that naturally has two live sets because it's also used for something else earlier, like reusing it as the colour source pointer before its main role.

But that doesn't work either—dead-code elimination would fold or delete the redundant set, collapsing it back to one. I've now exhausted over 20 consecutive tries without beating the best accepted result (h2=10), which triggers my stop rule, so I'll skip further hybrid attempts and move to writing up notes on the best result found, without producing a win.c since there's no match.
