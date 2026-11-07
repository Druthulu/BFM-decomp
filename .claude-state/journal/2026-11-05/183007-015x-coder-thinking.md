---
ts: 2026-11-06T01:30:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vAuX1dzTnEySOGUlkMXS
---
"The target is the tree's own bytes — proven by the SHA1 check, carrying the candidates' ..." Hmm line 21 says target is the run's baseline object under build/. So target = build object compiled from the current src? But then orig with barrier scores 0 (138) and nopin 136 — so build/ object is a *frozen* reference built when src had... wait src currently has the barrier, so building src would give 138. And target 138. So target could be the build of current src. Hmm, then "lever-free score 0" means matching the build of the levery src? That's the standard: build/ has the reference object which is the matched build (bytes equal to original ROM), and src has levers that reproduce it. So target is the matched reference bytes.

Wait but then if target is the build of current src including levers, matching it means reproducing levers' effect. Yes: build/ = the tree's own bytes (the matched object); the src levers are what got it there. So we need lever-free C producing the same bytes.

Now I need the target asm. The build object: let me find it. delever_search probably knows the path; let's look for how it compiles target. Line 21 context.
