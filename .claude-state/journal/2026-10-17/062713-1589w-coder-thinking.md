---
ts: 2026-10-17T12:27:13.244Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a04bcca3508c8aa5c
model: claude-opus-5-5[1m]
effort: medium
turnId: b53b24c7-146b-4600-ac40-c2f9f65331a4
---
I recall those notes mentioned copies differ only by extern names, so I need to remap handles accordingly. I should check calibration staleness by running delever_oracle --calibrate and comparing against the prior commits, and also keep in mind another coder is working in a separate scratch directory simultaneously.

I'll run apply.sh first on non-W4 classes, excluding a88f and db4e, leaving 146 copies to process; since each apply-body does a compile and byte check, I want to time one run before committing to all of them.
