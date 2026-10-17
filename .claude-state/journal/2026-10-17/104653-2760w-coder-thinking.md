---
ts: 2026-10-17T16:46:53.119Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
The output from ti.sh is way too verbose — I should make it print a summary instead, like a count of distinct scores plus a fail list, and add a fast mode that tests k0 first and stops at the first nonzero result. I'm also noticing the original func_80157BC8 itself fails on the MAIN_012 includer with score 7, which suggests MAIN_012 might have a different variant, maybe gated by an ifdef in the header.

Let me rewrite ti.sh to summarize output and parallelize with xargs. Also worth noting: func_801810F8 original printed "keepalive" as its kind but also carries pin $6 — since kinds only lists keepalive, the pin might just be a pre-existing attribute unrelated to the current issue, so that's fine.
