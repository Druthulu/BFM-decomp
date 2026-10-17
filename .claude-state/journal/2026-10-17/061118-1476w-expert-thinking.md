---
ts: 2026-10-17T12:11:18.586Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: afda95bec87dc8de3
model: claude-opus-5-5[1m]
effort: medium
turnId: b67fb1b4-2f89-4c7f-845b-5eb1efd86920
---
So 267 rows actually dropped from the head-class, with the remaining 133 coming from pin rows at 8013F350 tagged under a different class, likely a missing-parameter case. Now I'm setting up a second propagator pass for six cracks, tracking the specific addresses involved and noting where extern declaration changes and signature differences show up across the affected translation units.

I also need to account for classes that have duplicate copies under different function names—like the 7e3e signature appearing at both 80183A3C and 80187F4C—so each copy needs its own address tracking and the signature change has to propagate to that copy's definition plus every prototype in its includers and callers.
